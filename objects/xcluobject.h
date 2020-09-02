#ifndef XCLUOBJECT_H
#define XCLUOBJECT_H

//Тип данных "объект", которых хранит скаляры, строки, численные массивы и списки строк, и объекты.

#include "incl_h.h"

#include "xcluarray.h"
#include <QMutex>

//Объект
//Типы объектов заданы в XcluObjectType
//Управление визуализацией в редакторе конкретных объектов,
//а также работа с их элементами осуществляется через XcluObjectWrapper

//в объектах есть mutex, поэтому, при начале изменения нужно вызвать begin_access, а затем end_access

//ObjectRead - класс для безопасного доступа к объекту, кратко называется ObjectRead:
//    ObjectRead access(object);
//для быстрого доступа к одному элементу объекта:
//    ObjectRead(object).type()
//- конструктор вызовет object->begin_access(), а деструктор object->end_access()
//все операции можно проводить только через него
//Но, нельзя кратко в одной строке делать доступ, так как деструктор не вызывается:
//QString("%1\n%2 byte(s)")
//    .arg(object_type_to_string(ObjectRead(object()).type()))
//    .arg(ObjectRead(object()).size_bytes()));   ---- так нельзя, mutex приведет к зависанию

//TODO как-то усовершенствовать код, а то все одно и то же дублируется - использовать макросы


//----------------------------------------------------------------
class ObjectRead;
class ObjectReadWrite;

//Класс объекта
class XcluObject
{
public:
    //создает объект заданного типа, по описанию из object_types
    XcluObject(XcluObjectType type = XcluObjectTypeEmpty);
    virtual ~XcluObject();


protected:
    //эти функции доступны из ObjectRead, ObjectReadWrite
    friend ObjectRead;
    friend ObjectReadWrite;

    void begin_access();
    void end_access();

    bool was_changed();     //показывает, было ли изменение после последнего запроса "was_changed"
    void set_changed();     //устанавливает флаг, что было изменение
    void reset_changed();   //сброс флага, что было изменение

    //тип - не очищается при clear
    XcluObjectType type() const;
    void set_type(XcluObjectType);
    //проверить, что объект имеет конкретный тип, если нет - то выдаст exception
    void assert_type(XcluObjectType expected_type) const;

    //размер данных, в байтах
    quint32 size_bytes() const;

    //очистка и копирование
    void clear();
    void copy_to(XcluObject *object) const;

    //доступ к переменным
    bool has_int(QString name) const;
    int geti(QString name) const;
    //используйте var_int для изменения переменной
    int &var_int(QString name, bool create_if_not_exists = false);
    void seti(QString name, const int &v);
    QMap<QString,int> &all_ints();

    bool has_float(QString name) const;
    float getf(QString name) const;
    //используйте var_float для изменения переменной
    float &var_float(QString name, bool create_if_not_exists = false);
    void setf(QString name, const float &v);
    QMap<QString,float> &all_floats();

    bool has_string(QString name) const;
    QString gets(QString name) const;
    //используйте var_string для изменения переменной
    QString &var_string(QString name, bool create_if_not_exists = false);
    void sets(QString name, const QString &v);
    QMap<QString,QString> &all_strings();

    bool has_array(QString name) const;
    const XcluArray *get_array(QString name) const;
    //используйте var_array для изменения массива
    XcluArray *var_array(QString name, bool create_if_not_exists = false);
    XcluArray *create_array(QString name);
    QMap<QString,XcluArray *> &all_arrays();

    bool has_strings(QString name) const;
    const QStringList *get_strings(QString name) const;
    //используйте var_strings для изменения strings
    QStringList *var_strings(QString name, bool create_if_not_exists = false);
    QStringList *create_strings(QString name);
    QMap<QString,QStringList *> &all_stringss();  //любопытное название

    bool has_object(QString name) const;
    XcluObject const *get_object(QString name) const;
    //используйте var_strings для изменения объекта
    XcluObject *var_object(QString name, bool create_if_not_exists = false);
    //создает объект, затем его можно наполнять - например, скопировать другой объект
    XcluObject *create_object(QString name, XcluObjectType type = XcluObjectTypeEmpty);
    QMap<QString,XcluObject *> &all_objects();

    //Указатели - например, для хранения FBO или передачи виджетов QWidget *.
    //В отличие от полноценного объекта, у указателя одна задача - хранить что-то системное, что мы не можем хранить как набор скаляров и массивов.
    //pointer создается как наследник XcluPointer, который умеет, например, копировать объекты (через виртуальную функцию наследника).
    bool has_pointer(QString name) const;
    void const *get_pointer(QString name) const;
    void *get_pointer(QString name);
    void set_pointer(QString name, void *pointer);
    QMap<QString, void*> &all_pointers();


protected:
    //встроенные поля
    XcluObjectType type_;

    //мютекс для доступа
    QMutex mutex_;

    //было ли изменение
    bool was_changed_ = false;

    //списки, точнее, maps переменных - доступ по имени:
    //int
    QMap<QString,int> int_;

    //float
    QMap<QString,float> float_;

    //string
    QMap<QString,QString> string_;

    //array XcluArray
    QMap<QString,XcluArray *> array_;

    //strings   QStringList
    QMap<QString,QStringList *> strings_;

    //object
    QMap<QString,XcluObject *> object_;
    //то есть, объектов может быть много - но к ним доступ по имени, а не как к массиву

    //pointer - для хранения системных объектов типа FBO
    QMap<QString, void*> pointer_;

};

//----------------------------------------------------------------
//ObjectRead, ObjectReadWrite - классы для безопасного доступа к объекту,
//только считываниеи на считывание и запись:
//    ObjectRead access(object);
//для быстрого доступа к одному элементу объекта:
//    ObjectRead(object).type()
//- конструктор вызовет object->begin_access(), а деструктор object->end_access()
//все операции можно проводить только через него
//Кроме деструктора - можно вызывать access.release() для освобождения объекта
//Важно: следует стараться, чтобы доступ был как можно короче - то есть только когда он нужен
//для того, чтобы многопоточные операции типа получение кадра с камеры не зависали
//Но, нельзя кратко в одной строке делать доступ, так как деструктор не вызывается:
//QString("%1\n%2 byte(s)")
//    .arg(object_type_to_string(ObjectRead(object()).type()))
//    .arg(ObjectRead(object()).size_bytes()));   ---- так нельзя, mutex приведет к зависанию
//   Внимание: если был доступ на запись, то автоматически ставится пометка, что объект был изменен

//ВАЖНО: ObjectRead все же меняет состояние объекта - а именно, его was_changed
//(при его запросе сбрасывается флажок)

class ObjectRead {
public:
    ObjectRead(XcluObject *object);
    ObjectRead(XcluObject &object);
    virtual ~ObjectRead();

    void release();             //если надо освободить объект, но он остается в зоне видимости
    //bool assert_is_correct();  //проверка, что объект соответствует его формальному описанию
private:
    ObjectRead(ObjectRead &){}   //запрещаем создавать копию объекта, чтобы не вызывали ObjectRead(ObjectAcess(...))
    bool accessed_ = false;
public:
    //Все эти функции вызывают соответствующие функции объекта
    //но тут они защищены

    //показывает, было ли изменение объекта после последнего запроса "was_changed"
    //Важно, что, несмотря на то, что это ObjectRead, эти две функции меняют объект
    //так как показатель изменения - это внешняя характеристика объекта, которая, например, не записывается в файл
    bool was_changed() { return object_->was_changed(); }
    void reset_changed() { object_->reset_changed(); }

    //тип - не очищается при clear
    XcluObjectType type()               { return object_->type(); }
    //проверить, что объект имеет конкретный тип, если нет - то выдаст exception
    void assert_type(XcluObjectType expected_type)  { object_->assert_type(expected_type); }

    //размер данных, в байтах
    quint32 size_bytes()                { return object_->size_bytes(); }

    //очистка и копирование
    void copy_to(XcluObject *object)    { return object_->copy_to(object); }

    //доступ к переменным
    bool has_int(QString name)          { return object_->has_int(name); }
    int geti(QString name)           { return object_->var_int(name); }

    bool has_float(QString name)        { return object_->has_float(name); }
    float getf(QString name)        { return object_->var_float(name); }

    bool has_string(QString name)           { return object_->has_string(name); }
    QString gets(QString name)       { return object_->gets(name); }

    bool has_array(QString name)           { return object_->has_array(name); }
    XcluArray const *get_array(QString name) { return object_->get_array(name); }

    bool has_strings(QString name)          { return object_->has_strings(name); }
    QStringList const *get_strings(QString name) { return object_->get_strings(name); }

    bool has_object(QString name)            { return object_->has_object(name); }
    XcluObject const *get_object(QString name) { return object_->get_object(name); }

    bool has_pointer(QString name)            { return object_->has_pointer(name); }
    void const *get_pointer(QString name)     { return object_->get_pointer(name); }


protected:
    XcluObject *object_;
};


//Класс для изменения объекта
//При создании сразу помечаем, что объект был изменен
class ObjectReadWrite: public ObjectRead {
public:
    ObjectReadWrite(XcluObject *object);
    ObjectReadWrite(XcluObject &object);
    //virtual ~ObjectReadWrite();

    //bool assert_is_correct();  //проверка, что объект соответствует его формальному описанию
private:
//    ObjectReadWrite(ObjectReadWrite &a): ObjectRead(a) {}   //запрещаем создавать копию объекта, чтобы не вызывали ObjectRead(ObjectAcess(...))
public:
    //Все эти функции вызывают соответствующие функции объекта
    //но тут они защищены

    //тип - не очищается при clear
    void set_type(XcluObjectType type)  { object_->set_type(type); }
    //проверить, что объект имеет конкретный тип, если нет - то выдаст expeption

    //очистка и копирование
    void clear()                        { object_->clear(); }

    //доступ к переменным
    int &var_int(QString name, bool create_if_not_exists = false) { return object_->var_int(name, create_if_not_exists); }
    void seti(QString name, const int &v) { object_->seti(name, v); }
    QMap<QString,int> &all_ints()           { return object_->all_ints(); }

    float &var_float(QString name, bool create_if_not_exists = false)  { return object_->var_float(name, create_if_not_exists); }
    void setf(QString name, const float &v) { object_->setf(name, v); }
    QMap<QString,float> &all_floats()       { return object_->all_floats(); }

    QString &var_string(QString name, bool create_if_not_exists = false) { return object_->var_string(name, create_if_not_exists); }
    void sets(QString name, const QString &v) { object_->sets(name, v); }
    QMap<QString,QString> &all_strings()        { return object_->all_strings(); }

    //используйте var_array для изменения массива
    XcluArray *var_array(QString name, bool create_if_not_exists = false) { return object_->var_array(name, create_if_not_exists); }
    XcluArray *create_array(QString name) { return object_->create_array(name); }
    QMap<QString,XcluArray *> &all_arrays()   { return object_->all_arrays(); }

    //используйте var_strings для изменения strings
    QStringList *var_strings(QString name, bool create_if_not_exists = false) { return object_->var_strings(name, create_if_not_exists); }
    QStringList *create_strings(QString name) { return object_->create_strings(name); }
    QMap<QString,QStringList *> &all_stringss()  { return object_->all_stringss(); }  //любопытное название

    //используйте var_object для изменения подобъектов
    XcluObject *var_object(QString name, bool create_if_not_exists = false) { return object_->var_object(name, create_if_not_exists); }
    XcluObject *create_object(QString name, XcluObjectType type = XcluObjectTypeEmpty)  { return object_->create_object(name, type); }
    QMap<QString,XcluObject *> &all_objects() { return object_->all_objects(); }

    void *get_pointer(QString name)                    { return object_->get_pointer(name); }
    void set_pointer(QString name, void *pointer)     { object_->set_pointer(name, pointer); }


protected:

};


#endif // XCLUOBJECT_H
