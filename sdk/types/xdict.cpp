#include "xdict.h"
#include "incl_cpp.h"


//---------------------------------------------------------------------
XDictRead::XDictRead(XDict *object) {
    xclu_assert(object, "Nullptr object at XDictRead");
    object_ = object;
    object_->begin_access();
    accessed_ = true;
}

XDictRead::XDictRead(XDict &object) {
    xclu_assert(&object, "Nullptr object at XDictRead");
    object_ = &object;
    object_->begin_access();
    accessed_ = true;
}


XDictRead::~XDictRead() {
    release();
}

void XDictRead::release() {             //если надо освободить объект, но он остается в зоне видимости
    if (accessed_) {
        object_->end_access();
    }
    accessed_ = false;
    object_ = nullptr;
}

//---------------------------------------------------------------------
XDictWrite::XDictWrite(XDict *object)
    : XDictRead(object)
{
    object->set_changed();
}

XDictWrite::XDictWrite(XDict &object)
    : XDictRead(object)
{
    object.set_changed();
}

//XDictWrite::~XDictWrite() {
//}

//---------------------------------------------------------------------
XDict::XDict(XDictType type)
{
    set_type(type);
}

//---------------------------------------------------------------------
XDict::~XDict() {

}

//---------------------------------------------------------------------
void XDict::begin_access() {
    mutex_.lock();
}

//---------------------------------------------------------------------
void XDict::end_access() {
    mutex_.unlock();
}

//---------------------------------------------------------------------
bool XDict::was_changed() {     //показывает, было ли изменение после последнего запроса
    bool res = was_changed_;
    was_changed_ = false;
    return res;
}

//---------------------------------------------------------------------
void XDict::reset_changed() {
    was_changed_ = false;
}

//---------------------------------------------------------------------
void XDict::set_changed() {     //устанавливает флаг, что было изменение
    was_changed_ = true;
}

//---------------------------------------------------------------------
XDictType XDict::type() const { //тип - image, array, strings, используется для того, чтобы можно было фильтровать и управлять визуализацией
    return type_;
}

//---------------------------------------------------------------------
void XDict::set_type(XDictType type) {
    type_ = type;
    set_changed();
}

//---------------------------------------------------------------------
//проверить, что объект имеет конкретный тип, если нет - то выдаст expeption
void XDict::assert_type(XDictType expected_type) const {
    xclu_assert(type() == expected_type,
            QString("Expected object of type '%1', but get %2")
                .arg(object_type_to_string(expected_type))
                .arg(object_type_to_string(type()))
            );
}

//---------------------------------------------------------------------
//размер данных, в байтах
quint32 XDict::size_bytes() const {
    quint32 size = 0;
    size += int_.size() * 4;
    size += float_.size() * 4;

    for (auto i = array_.begin(); i != array_.end(); ++i) {
        size += i.value()->size_bytes();
    }

    for (auto i = strings_.begin(); i != strings_.end(); ++i) {
        size += i.value()->length() * 2; //так как UTF //TODO возможно оценка неточная
    }

    for (auto i = object_.begin(); i != object_.end(); ++i) {
        size += i.value()->size_bytes();
    }
    return size;
}

//---------------------------------------------------------------------
void XDict::clear() {
    int_.clear();
    float_.clear();
    string_.clear();

    //arrays
    for (auto i = array_.begin(); i != array_.end(); ++i) {
        delete i.value();
    }
    array_.clear();

    //strings
    for (auto i = strings_.begin(); i != strings_.end(); ++i) {
        delete i.value();
    }
    strings_.clear();

    //objects
    for (auto i = object_.begin(); i != object_.end(); ++i) {
        delete i.value();
    }
    object_.clear();

    set_changed();
}

//---------------------------------------------------------------------
void XDict::copy_to(XDict *object) const {
    xclu_assert(object, "nullptr in XDict::copy_to");

    //защищаем объект - пока существует obj, object никто другой не сможет изменить
    XDictWrite obj(object);

    object->clear();

    object->set_type(type());
    object->all_ints() = int_;
    object->all_floats() = float_;
    object->all_strings() = string_;

    //arrays, strings, objects - указатели нужно скопировать поэлементно
    //arrays
    for (auto i = array_.begin(); i != array_.end(); ++i) {
        QString name = i.key();
        *obj.var_array(name, true) = *i.value();
    }

    //strings
    for (auto i = strings_.begin(); i != strings_.end(); ++i) {
        QString name = i.key();
        *obj.var_strings(name, true) = *i.value();
    }

    //objects
    for (auto i = object_.begin(); i != object_.end(); ++i) {
        QString name = i.key();
        XDict *obj = object->create_object(name);
        i.value()->copy_to(obj);
    }

    //pointers
    //Их не копируем

}

//---------------------------------------------------------------------
/* Макрос для функций проверки наличия значения has_int, has_float, ...
bool XDict::has_int(QString name) const {
    return int_.contains(name);
}
*/
#define XDict_has_(TYPE_NAME) \
    bool XDict::has_##TYPE_NAME(QString name) const { \
        return TYPE_NAME##_.contains(name); \
    }

XDict_has_(int)
XDict_has_(float)
XDict_has_(string)
XDict_has_(array)
XDict_has_(strings)
XDict_has_(object)
XDict_has_(pointer)

//---------------------------------------------------------------------
/* Макрос для функций получения значения geti, getf, ...
QString XDict::var_string(QString name, bool create_if_not_exists) const {
    xclu_assert(create_if_not_exists || has_float(name), "Object has no string '" + name + "'");
    return string_[name];
}
*/

#define XDict_get_(SHORT_TYPE, TYPE_NAME, CPP_TYPE, FUN_CONST) \
    CPP_TYPE XDict::get##SHORT_TYPE(QString name) FUN_CONST { \
        xclu_assert(has_##TYPE_NAME(name), "Object has no "#TYPE_NAME" '" + name + "'"); \
        return TYPE_NAME##_[name]; \
    }
#define XDict_get_pointer_(TYPE_NAME, CPP_TYPE, FUN_CONST) \
    CPP_TYPE XDict::get_##TYPE_NAME(QString name) FUN_CONST { \
        xclu_assert(has_##TYPE_NAME(name), "Object has no "#TYPE_NAME" '" + name + "'"); \
        auto result = TYPE_NAME##_[name]; \
        xclu_assert(result != nullptr, QString("Object "#TYPE_NAME" '%1' is nullptr during calling 'XDict::get"));\
        return result; \
    }

XDict_get_(i,int,int,const)
XDict_get_(f,float,float,const)
XDict_get_(s,string,QString,const)
XDict_get_pointer_(array,const XArray *,const)
XDict_get_pointer_(strings,const QStringList *,const)
XDict_get_pointer_(object,const XDict *,const)
XDict_get_pointer_(pointer,void const *,const)
XDict_get_pointer_(pointer,void *,)


//---------------------------------------------------------------------
/* Макрос для функций получения значения var_int, var_float, ...
QString &XDict::var_string(QString name, bool create_if_not_exists) {
    xclu_assert(create_if_not_exists || has_float(name), "Object has no string '" + name + "'");
    return string_[name];
}
*/

#define XDict_var_(TYPE_NAME, CPP_TYPE) \
    CPP_TYPE XDict::var_##TYPE_NAME(QString name, bool create_if_not_exists) { \
        xclu_assert(create_if_not_exists || has_##TYPE_NAME(name), "Object has no "#TYPE_NAME" '" + name + "'"); \
        return TYPE_NAME##_[name]; \
    }

#define XDict_var_pointer_(TYPE_NAME, CPP_TYPE) \
    CPP_TYPE XDict::var_##TYPE_NAME(QString name, bool create_if_not_exists) { \
        bool has = has_##TYPE_NAME(name); \
        xclu_assert(create_if_not_exists || has, "Object has no "#TYPE_NAME" '" + name + "'"); \
        if (!has) { \
            TYPE_NAME##_.insert(name, create_##TYPE_NAME(name));      \
        }           \
        auto result = TYPE_NAME##_[name]; \
        xclu_assert(result != nullptr, QString("Object "#TYPE_NAME" '%1' is nullptr, during calling 'XDict::var'"));\
        return TYPE_NAME##_[name]; \
    }

XDict_var_(int,int &)
XDict_var_(float,float &)
XDict_var_(string,QString &)
XDict_var_pointer_(array,XArray *)
XDict_var_pointer_(strings,QStringList *)
XDict_var_pointer_(object,XDict *)

//---------------------------------------------------------------------
/* Макрос для функций установки значения seti, setf, ...
void XDict::seti(QString name, int v) {
    int_[name] = v;
}
*/

#define XDict_set_(SHORT_TYPE, TYPE_NAME, CPP_TYPE) \
    void XDict::set##SHORT_TYPE(QString name, CPP_TYPE v) { \
        TYPE_NAME##_[name] = v; \
        set_changed(); \
    }

XDict_set_(i, int, const int &)
XDict_set_(f, float, const float &)
XDict_set_(s, string, const QString &)

XDict_set_(_pointer,pointer,void *)

XArray *XDict::create_array(QString name) {
    xclu_assert(!has_array(name), QString("Array '%1' is already created in object").arg(name));
    XArray *array = new XArray();
    array_[name] = array;
    return array;
}

QStringList *XDict::create_strings(QString name) {
    xclu_assert(!has_array(name), QString("Strings '%1' are already created in object").arg(name));
    QStringList *strings = new QStringList();
    strings_[name] = strings;
    return strings;
}

XDict *XDict::create_object(QString name, XDictType type) {
    xclu_assert(!has_object(name), QString("Subobject '%1' is already created in object").arg(name));
    XDict *object = new XDict(type);
    object_[name] = object;
    return object;
}
//---------------------------------------------------------------------


//---------------------------------------------------------------------
/* Макрос для функций получения всех значений данного типа all_ints, all_floats, ...
QMap<QString,int> &XDict::all_ints() {
    return int_;
}
*/

#define XDict_all_(TYPE_NAME, CPP_TYPE) \
    QMap<QString,CPP_TYPE> &XDict::all_##TYPE_NAME##s() { \
        return TYPE_NAME##_; \
    }

XDict_all_(int,int)
XDict_all_(float,float)
XDict_all_(string,QString)
XDict_all_(array,XArray *)
XDict_all_(strings,QStringList *)
XDict_all_(object,XDict *)
XDict_all_(pointer,void *)

//---------------------------------------------------------------------
