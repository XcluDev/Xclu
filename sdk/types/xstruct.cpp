#include "xstruct.h"
#include "incl_cpp.h"


//---------------------------------------------------------------------
XStructRead::XStructRead(XStruct *object) {
    xclu_assert(object, "Nullptr object at XStructRead");
    object_ = object;
    object_->begin_access();
    accessed_ = true;
}

XStructRead::XStructRead(XStruct &object) {
    xclu_assert(&object, "Nullptr object at XStructRead");
    object_ = &object;
    object_->begin_access();
    accessed_ = true;
}


XStructRead::~XStructRead() {
    release();
}

void XStructRead::release() {             //если надо освободить объект, но он остается в зоне видимости
    if (accessed_) {
        object_->end_access();
    }
    accessed_ = false;
    object_ = nullptr;
}

//---------------------------------------------------------------------
XStructWrite::XStructWrite(XStruct *object)
    : XStructRead(object)
{
    object->set_changed();
}

XStructWrite::XStructWrite(XStruct &object)
    : XStructRead(object)
{
    object.set_changed();
}

//XStructWrite::~XStructWrite() {
//}

//---------------------------------------------------------------------
XStruct::XStruct(XStructType type)
{
    set_type(type);
}

//---------------------------------------------------------------------
XStruct::~XStruct() {

}

//---------------------------------------------------------------------
void XStruct::begin_access() {
    mutex_.lock();
}

//---------------------------------------------------------------------
void XStruct::end_access() {
    mutex_.unlock();
}

//---------------------------------------------------------------------
bool XStruct::was_changed() {     //показывает, было ли изменение после последнего запроса
    bool res = was_changed_;
    was_changed_ = false;
    return res;
}

//---------------------------------------------------------------------
void XStruct::reset_changed() {
    was_changed_ = false;
}

//---------------------------------------------------------------------
void XStruct::set_changed() {     //устанавливает флаг, что было изменение
    was_changed_ = true;
}

//---------------------------------------------------------------------
XStructType XStruct::type() const { //тип - image, array, strings, используется для того, чтобы можно было фильтровать и управлять визуализацией
    return type_;
}

//---------------------------------------------------------------------
void XStruct::set_type(XStructType type) {
    type_ = type;
    set_changed();
}

//---------------------------------------------------------------------
//проверить, что объект имеет конкретный тип, если нет - то выдаст expeption
void XStruct::assert_type(XStructType expected_type) const {
    xclu_assert(type() == expected_type,
            QString("Expected object of type '%1', but get %2")
                .arg(object_type_to_string(expected_type))
                .arg(object_type_to_string(type()))
            );
}

//---------------------------------------------------------------------
//размер данных, в байтах
quint32 XStruct::size_bytes() const {
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
void XStruct::clear() {
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
void XStruct::copy_to(XStruct *object) const {
    xclu_assert(object, "nullptr in XStruct::copy_to");

    //защищаем объект - пока существует obj, object никто другой не сможет изменить
    XStructWrite obj(object);

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
        XStruct *obj = object->create_object(name);
        i.value()->copy_to(obj);
    }

    //pointers
    //Их не копируем

}

//---------------------------------------------------------------------
/* Макрос для функций проверки наличия значения has_int, has_float, ...
bool XStruct::has_int(QString name) const {
    return int_.contains(name);
}
*/
#define XStruct_has_(TYPE_NAME) \
    bool XStruct::has_##TYPE_NAME(QString name) const { \
        return TYPE_NAME##_.contains(name); \
    }

XStruct_has_(int)
XStruct_has_(float)
XStruct_has_(string)
XStruct_has_(array)
XStruct_has_(strings)
XStruct_has_(object)
XStruct_has_(pointer)

//---------------------------------------------------------------------
/* Макрос для функций получения значения geti, getf, ...
QString XStruct::var_string(QString name, bool create_if_not_exists) const {
    xclu_assert(create_if_not_exists || has_float(name), "Object has no string '" + name + "'");
    return string_[name];
}
*/

#define XStruct_get_(SHORT_TYPE, TYPE_NAME, CPP_TYPE, FUN_CONST) \
    CPP_TYPE XStruct::get##SHORT_TYPE(QString name) FUN_CONST { \
        xclu_assert(has_##TYPE_NAME(name), "Object has no "#TYPE_NAME" '" + name + "'"); \
        return TYPE_NAME##_[name]; \
    }
#define XStruct_get_pointer_(TYPE_NAME, CPP_TYPE, FUN_CONST) \
    CPP_TYPE XStruct::get_##TYPE_NAME(QString name) FUN_CONST { \
        xclu_assert(has_##TYPE_NAME(name), "Object has no "#TYPE_NAME" '" + name + "'"); \
        auto result = TYPE_NAME##_[name]; \
        xclu_assert(result != nullptr, QString("Object "#TYPE_NAME" '%1' is nullptr during calling 'XStruct::get"));\
        return result; \
    }

XStruct_get_(i,int,int,const)
XStruct_get_(f,float,float,const)
XStruct_get_(s,string,QString,const)
XStruct_get_pointer_(array,const XArray *,const)
XStruct_get_pointer_(strings,const QStringList *,const)
XStruct_get_pointer_(object,const XStruct *,const)
XStruct_get_pointer_(pointer,void const *,const)
XStruct_get_pointer_(pointer,void *,)


//---------------------------------------------------------------------
/* Макрос для функций получения значения var_int, var_float, ...
QString &XStruct::var_string(QString name, bool create_if_not_exists) {
    xclu_assert(create_if_not_exists || has_float(name), "Object has no string '" + name + "'");
    return string_[name];
}
*/

#define XStruct_var_(TYPE_NAME, CPP_TYPE) \
    CPP_TYPE XStruct::var_##TYPE_NAME(QString name, bool create_if_not_exists) { \
        xclu_assert(create_if_not_exists || has_##TYPE_NAME(name), "Object has no "#TYPE_NAME" '" + name + "'"); \
        return TYPE_NAME##_[name]; \
    }

#define XStruct_var_pointer_(TYPE_NAME, CPP_TYPE) \
    CPP_TYPE XStruct::var_##TYPE_NAME(QString name, bool create_if_not_exists) { \
        bool has = has_##TYPE_NAME(name); \
        xclu_assert(create_if_not_exists || has, "Object has no "#TYPE_NAME" '" + name + "'"); \
        if (!has) { \
            TYPE_NAME##_.insert(name, create_##TYPE_NAME(name));      \
        }           \
        auto result = TYPE_NAME##_[name]; \
        xclu_assert(result != nullptr, QString("Object "#TYPE_NAME" '%1' is nullptr, during calling 'XStruct::var'"));\
        return TYPE_NAME##_[name]; \
    }

XStruct_var_(int,int &)
XStruct_var_(float,float &)
XStruct_var_(string,QString &)
XStruct_var_pointer_(array,XArray *)
XStruct_var_pointer_(strings,QStringList *)
XStruct_var_pointer_(object,XStruct *)

//---------------------------------------------------------------------
/* Макрос для функций установки значения seti, setf, ...
void XStruct::seti(QString name, int v) {
    int_[name] = v;
}
*/

#define XStruct_set_(SHORT_TYPE, TYPE_NAME, CPP_TYPE) \
    void XStruct::set##SHORT_TYPE(QString name, CPP_TYPE v) { \
        TYPE_NAME##_[name] = v; \
        set_changed(); \
    }

XStruct_set_(i, int, const int &)
XStruct_set_(f, float, const float &)
XStruct_set_(s, string, const QString &)

XStruct_set_(_pointer,pointer,void *)

XArray *XStruct::create_array(QString name) {
    xclu_assert(!has_array(name), QString("Array '%1' is already created in object").arg(name));
    XArray *array = new XArray();
    array_[name] = array;
    return array;
}

QStringList *XStruct::create_strings(QString name) {
    xclu_assert(!has_array(name), QString("Strings '%1' are already created in object").arg(name));
    QStringList *strings = new QStringList();
    strings_[name] = strings;
    return strings;
}

XStruct *XStruct::create_object(QString name, XStructType type) {
    xclu_assert(!has_object(name), QString("Subobject '%1' is already created in object").arg(name));
    XStruct *object = new XStruct(type);
    object_[name] = object;
    return object;
}
//---------------------------------------------------------------------


//---------------------------------------------------------------------
/* Макрос для функций получения всех значений данного типа all_ints, all_floats, ...
QMap<QString,int> &XStruct::all_ints() {
    return int_;
}
*/

#define XStruct_all_(TYPE_NAME, CPP_TYPE) \
    QMap<QString,CPP_TYPE> &XStruct::all_##TYPE_NAME##s() { \
        return TYPE_NAME##_; \
    }

XStruct_all_(int,int)
XStruct_all_(float,float)
XStruct_all_(string,QString)
XStruct_all_(array,XArray *)
XStruct_all_(strings,QStringList *)
XStruct_all_(object,XStruct *)
XStruct_all_(pointer,void *)

//---------------------------------------------------------------------
