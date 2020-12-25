#include "xobject.h"
#include "incl_cpp.h"


//---------------------------------------------------------------------
XObject::XObject(XObjectType type)
{
    set_type(type);
}

//---------------------------------------------------------------------
XObject::~XObject() {

}

//---------------------------------------------------------------------
//void XObject::begin_access() {
//    mutex_.lock();
//}

//---------------------------------------------------------------------
//void XObject::end_access() {
//    mutex_.unlock();
//}

//---------------------------------------------------------------------
XObjectType XObject::type() const { //тип - image, array, strings, используется для того, чтобы можно было фильтровать и управлять визуализацией
    return type_;
}

//---------------------------------------------------------------------
void XObject::set_type(XObjectType type) {
    type_ = type;
    //set_changed();
}

//---------------------------------------------------------------------
//проверить, что объект имеет конкретный тип, если нет - то выдаст expeption
void XObject::assert_type(XObjectType expected_type) const {
    xc_assert(type() == expected_type,
            QString("Expected object of type '%1', but get %2")
                .arg(object_type_to_string(expected_type))
                .arg(object_type_to_string(type()))
            );
}

//---------------------------------------------------------------------
//размер данных, в байтах
quint32 XObject::size_bytes() const {
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
void XObject::clear() {
    type_ = XObjectTypeEmpty;
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

    //set_changed();
}

//---------------------------------------------------------------------
void XObject::copy_to(XObject *object) const {
    xc_assert(object, "nullptr in XObject::copy_to");

    XObject &obj = *object;

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
        XObject *obj = object->create_object(name);
        i.value()->copy_to(obj);
    }

    //pointers
    //Их не копируем

}

//---------------------------------------------------------------------
/* Макрос для функций проверки наличия значения has_int, has_float, ...
bool XObject::has_int(QString name) const {
    return int_.contains(name);
}
*/
#define XObject_has_(TYPE_NAME) \
    bool XObject::has_##TYPE_NAME(QString name) const { \
        return TYPE_NAME##_.contains(name); \
    }

XObject_has_(int)
XObject_has_(float)
XObject_has_(string)
XObject_has_(array)
XObject_has_(strings)
XObject_has_(object)
XObject_has_(pointer)

//---------------------------------------------------------------------
/* Макрос для функций получения значения geti, getf, ...
QString XObject::var_string(QString name, bool create_if_not_exists) const {
    xc_assert(create_if_not_exists || has_float(name), "Object has no string '" + name + "'");
    return string_[name];
}
*/

#define XObject_get_(SHORT_TYPE, TYPE_NAME, CPP_TYPE, FUN_CONST) \
    CPP_TYPE XObject::get##SHORT_TYPE(QString name) FUN_CONST { \
        xc_assert(has_##TYPE_NAME(name), "Object has no "#TYPE_NAME" '" + name + "'"); \
        return TYPE_NAME##_[name]; \
    }
#define XObject_get_pointer_(TYPE_NAME, CPP_TYPE, FUN_CONST) \
    CPP_TYPE XObject::get_##TYPE_NAME(QString name) FUN_CONST { \
        xc_assert(has_##TYPE_NAME(name), "Object has no "#TYPE_NAME" '" + name + "'"); \
        auto result = TYPE_NAME##_[name]; \
        xc_assert(result != nullptr, QString("Object "#TYPE_NAME" '%1' is nullptr during calling 'XObject::get"));\
        return result; \
    }

XObject_get_(i,int,int,const)
XObject_get_(f,float,float,const)
XObject_get_(s,string,QString,const)
XObject_get_pointer_(array,const XArray *,const)
XObject_get_pointer_(strings,const QStringList *,const)
XObject_get_pointer_(object,const XObject *,const)
XObject_get_pointer_(pointer,void const *,const)
XObject_get_pointer_(pointer,void *,)


//---------------------------------------------------------------------
/* Макрос для функций получения значения var_int, var_float, ...
QString &XObject::var_string(QString name, bool create_if_not_exists) {
    xc_assert(create_if_not_exists || has_float(name), "Object has no string '" + name + "'");
    return string_[name];
}
*/

#define XObject_var_(TYPE_NAME, CPP_TYPE) \
    CPP_TYPE XObject::var_##TYPE_NAME(QString name, bool create_if_not_exists) { \
        xc_assert(create_if_not_exists || has_##TYPE_NAME(name), "Object has no "#TYPE_NAME" '" + name + "'"); \
        return TYPE_NAME##_[name]; \
    }

#define XObject_var_pointer_(TYPE_NAME, CPP_TYPE) \
    CPP_TYPE XObject::var_##TYPE_NAME(QString name, bool create_if_not_exists) { \
        bool has = has_##TYPE_NAME(name); \
        xc_assert(create_if_not_exists || has, "Object has no "#TYPE_NAME" '" + name + "'"); \
        if (!has) { \
            TYPE_NAME##_.insert(name, create_##TYPE_NAME(name));      \
        }           \
        auto result = TYPE_NAME##_[name]; \
        xc_assert(result != nullptr, QString("Object "#TYPE_NAME" '%1' is nullptr, during calling 'XObject::var'"));\
        return TYPE_NAME##_[name]; \
    }

XObject_var_(int,int &)
XObject_var_(float,float &)
XObject_var_(string,QString &)
XObject_var_pointer_(array,XArray *)
XObject_var_pointer_(strings,QStringList *)
XObject_var_pointer_(object,XObject *)

//---------------------------------------------------------------------
/* Макрос для функций установки значения seti, setf, ...
void XObject::seti(QString name, int v) {
    int_[name] = v;
}
*/

#define XObject_set_(SHORT_TYPE, TYPE_NAME, CPP_TYPE) \
    void XObject::set##SHORT_TYPE(QString name, CPP_TYPE v) { \
        TYPE_NAME##_[name] = v; \
        /*set_changed();*/\
    }

XObject_set_(i, int, const int &)
XObject_set_(f, float, const float &)
XObject_set_(s, string, const QString &)

XObject_set_(_pointer,pointer,void *)

XArray *XObject::create_array(QString name) {
    xc_assert(!has_array(name), QString("Array '%1' is already created in object").arg(name));
    XArray *array = new XArray();
    array_[name] = array;
    return array;
}

QStringList *XObject::create_strings(QString name) {
    xc_assert(!has_array(name), QString("Strings '%1' are already created in object").arg(name));
    QStringList *strings = new QStringList();
    strings_[name] = strings;
    return strings;
}

XObject *XObject::create_object(QString name, XObjectType type) {
    xc_assert(!has_object(name), QString("Subobject '%1' is already created in object").arg(name));
    XObject *object = new XObject(type);
    object_[name] = object;
    return object;
}
//---------------------------------------------------------------------


//---------------------------------------------------------------------
/* Макрос для функций получения всех значений данного типа all_ints, all_floats, ...
QMap<QString,int> &XObject::all_ints() {
    return int_;
}
*/

#define XObject_all_(TYPE_NAME, CPP_TYPE) \
    QMap<QString,CPP_TYPE> &XObject::all_##TYPE_NAME##s() { \
        return TYPE_NAME##_; \
    }

XObject_all_(int,int)
XObject_all_(float,float)
XObject_all_(string,QString)
XObject_all_(array,XArray *)
XObject_all_(strings,QStringList *)
XObject_all_(object,XObject *)
XObject_all_(pointer,void *)

//---------------------------------------------------------------------
