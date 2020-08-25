#include "xcluobject.h"
#include "incl_cpp.h"


//---------------------------------------------------------------------
ObjectRead::ObjectRead(XcluObject *object) {
    object_ = object;
    object_->begin_access();
    accessed_ = true;
}

ObjectRead::ObjectRead(XcluObject &object) {
    object_ = &object;
    object_->begin_access();
    accessed_ = true;
}


ObjectRead::~ObjectRead() {
    release();
}

void ObjectRead::release() {             //если надо освободить объект, но он остается в зоне видимости
    if (accessed_) {
        object_->end_access();
    }
    accessed_ = false;
    object_ = nullptr;
}

//---------------------------------------------------------------------
ObjectReadWrite::ObjectReadWrite(XcluObject *object)
    : ObjectRead(object)
{
    object->set_changed();
}

ObjectReadWrite::ObjectReadWrite(XcluObject &object)
    : ObjectRead(object)
{
    object.set_changed();
}

//ObjectReadWrite::~ObjectReadWrite() {
//}

//---------------------------------------------------------------------
XcluObject::XcluObject(XcluObjectType type)
{
    set_type(type);
}

//---------------------------------------------------------------------
XcluObject::~XcluObject() {

}

//---------------------------------------------------------------------
void XcluObject::begin_access() {
    mutex_.lock();
}

//---------------------------------------------------------------------
void XcluObject::end_access() {
    mutex_.unlock();
}

//---------------------------------------------------------------------
bool XcluObject::was_changed() {     //показывает, было ли изменение после последнего запроса
    bool res = was_changed_;
    was_changed_ = false;
    return res;
}

//---------------------------------------------------------------------
void XcluObject::reset_changed() {
    was_changed_ = false;
}

//---------------------------------------------------------------------
void XcluObject::set_changed() {     //устанавливает флаг, что было изменение
    was_changed_ = true;
}

//---------------------------------------------------------------------
XcluObjectType XcluObject::type() const { //тип - image, array, strings, используется для того, чтобы можно было фильтровать и управлять визуализацией
    return type_;
}

//---------------------------------------------------------------------
void XcluObject::set_type(XcluObjectType type) {
    type_ = type;
    set_changed();
}

//---------------------------------------------------------------------
//проверить, что объект имеет конкретный тип, если нет - то выдаст expeption
void XcluObject::assert_type(XcluObjectType expected_type) const {
    xclu_assert(type() == expected_type,
            QString("Expected object of type '%1', but get %2")
                .arg(object_type_to_string(expected_type))
                .arg(object_type_to_string(type()))
            );
}

//---------------------------------------------------------------------
//размер данных, в байтах
quint32 XcluObject::size_bytes() const {
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
void XcluObject::clear() {
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
void XcluObject::copy_to(XcluObject *object) const {
    xclu_assert(object, "nullptr in XcluObject::copy_to");

    //защищаем объект - пока существует obj, object никто другой не сможет изменить
    ObjectReadWrite obj(object);

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
        XcluObject *obj = object->create_object(name);
        i.value()->copy_to(obj);
    }

    //pointers
    //Их не копируем

}

//---------------------------------------------------------------------
/* Макрос для функций проверки наличия значения has_int, has_float, ...
bool XcluObject::has_int(QString name) const {
    return int_.contains(name);
}
*/
#define XcluObject_has_(TYPE_NAME) \
    bool XcluObject::has_##TYPE_NAME(QString name) const { \
        return TYPE_NAME##_.contains(name); \
    }

XcluObject_has_(int)
XcluObject_has_(float)
XcluObject_has_(string)
XcluObject_has_(array)
XcluObject_has_(strings)
XcluObject_has_(object)
XcluObject_has_(pointer)

//---------------------------------------------------------------------
/* Макрос для функций получения значения get_int, get_float, ...
QString XcluObject::var_string(QString name, bool create_if_not_exists) const {
    xclu_assert(create_if_not_exists || has_float(name), "Object has no string '" + name + "'");
    return string_[name];
}
*/

#define XcluObject_get_(TYPE_NAME, CPP_TYPE, FUN_CONST) \
    CPP_TYPE XcluObject::get_##TYPE_NAME(QString name) FUN_CONST { \
        xclu_assert(has_##TYPE_NAME(name), "Object has no "#TYPE_NAME" '" + name + "'"); \
        return TYPE_NAME##_[name]; \
    }
#define XcluObject_get_pointer_(TYPE_NAME, CPP_TYPE, FUN_CONST) \
    CPP_TYPE XcluObject::get_##TYPE_NAME(QString name) FUN_CONST { \
        xclu_assert(has_##TYPE_NAME(name), "Object has no "#TYPE_NAME" '" + name + "'"); \
        auto result = TYPE_NAME##_[name]; \
        xclu_assert(result != nullptr, QString("Object "#TYPE_NAME" '%1' is nullptr during calling 'XcluObject::get"));\
        return result; \
    }

XcluObject_get_(int,int,const)
XcluObject_get_(float,float,const)
XcluObject_get_(string,QString,const)
XcluObject_get_pointer_(array,const XcluArray *,const)
XcluObject_get_pointer_(strings,const QStringList *,const)
XcluObject_get_pointer_(object,const XcluObject *,const)
XcluObject_get_pointer_(pointer,void const *,const)
XcluObject_get_pointer_(pointer,void *,)


//---------------------------------------------------------------------
/* Макрос для функций получения значения var_int, var_float, ...
QString &XcluObject::var_string(QString name, bool create_if_not_exists) {
    xclu_assert(create_if_not_exists || has_float(name), "Object has no string '" + name + "'");
    return string_[name];
}
*/

#define XcluObject_var_(TYPE_NAME, CPP_TYPE) \
    CPP_TYPE XcluObject::var_##TYPE_NAME(QString name, bool create_if_not_exists) { \
        xclu_assert(create_if_not_exists || has_##TYPE_NAME(name), "Object has no "#TYPE_NAME" '" + name + "'"); \
        return TYPE_NAME##_[name]; \
    }

#define XcluObject_var_pointer_(TYPE_NAME, CPP_TYPE) \
    CPP_TYPE XcluObject::var_##TYPE_NAME(QString name, bool create_if_not_exists) { \
        bool has = has_##TYPE_NAME(name); \
        xclu_assert(create_if_not_exists || has, "Object has no "#TYPE_NAME" '" + name + "'"); \
        if (!has) { \
            TYPE_NAME##_.insert(name, create_##TYPE_NAME(name));      \
        }           \
        auto result = TYPE_NAME##_[name]; \
        xclu_assert(result != nullptr, QString("Object "#TYPE_NAME" '%1' is nullptr, during calling 'XcluObject::var'"));\
        return TYPE_NAME##_[name]; \
    }

XcluObject_var_(int,int &)
XcluObject_var_(float,float &)
XcluObject_var_(string,QString &)
XcluObject_var_pointer_(array,XcluArray *)
XcluObject_var_pointer_(strings,QStringList *)
XcluObject_var_pointer_(object,XcluObject *)

//---------------------------------------------------------------------
/* Макрос для функций установки значения set_int, set_float, ...
void XcluObject::set_int(QString name, int v) {
    int_[name] = v;
}
*/

#define XcluObject_set_(TYPE_NAME, CPP_TYPE) \
    void XcluObject::set_##TYPE_NAME(QString name, CPP_TYPE v) { \
        TYPE_NAME##_[name] = v; \
        set_changed(); \
    }

XcluObject_set_(int, const int &)
XcluObject_set_(float, const float &)
XcluObject_set_(string, const QString &)

XcluObject_set_(pointer,void *)

XcluArray *XcluObject::create_array(QString name) {
    xclu_assert(!has_array(name), QString("Array '%1' is already created in object").arg(name));
    XcluArray *array = new XcluArray();
    array_[name] = array;
    return array;
}

QStringList *XcluObject::create_strings(QString name) {
    xclu_assert(!has_array(name), QString("Strings '%1' are already created in object").arg(name));
    QStringList *strings = new QStringList();
    strings_[name] = strings;
    return strings;
}

XcluObject *XcluObject::create_object(QString name, XcluObjectType type) {
    xclu_assert(!has_object(name), QString("Subobject '%1' is already created in object").arg(name));
    XcluObject *object = new XcluObject(type);
    object_[name] = object;
    return object;
}
//---------------------------------------------------------------------


//---------------------------------------------------------------------
/* Макрос для функций получения всех значений данного типа all_ints, all_floats, ...
QMap<QString,int> &XcluObject::all_ints() {
    return int_;
}
*/

#define XcluObject_all_(TYPE_NAME, CPP_TYPE) \
    QMap<QString,CPP_TYPE> &XcluObject::all_##TYPE_NAME##s() { \
        return TYPE_NAME##_; \
    }

XcluObject_all_(int,int)
XcluObject_all_(float,float)
XcluObject_all_(string,QString)
XcluObject_all_(array,XcluArray *)
XcluObject_all_(strings,QStringList *)
XcluObject_all_(object,XcluObject *)
XcluObject_all_(pointer,void *)

//---------------------------------------------------------------------
