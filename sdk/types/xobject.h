#ifndef XSTRUCT_H
#define XSTRUCT_H

// XObject - basic Xclu type for passing data between modules;
// use only when you are sure in that; normally use its safe wrapper XProtectedObject.

// XProtectedObject - thread-safe object wrapper on XObject.
// It applies mutexes for safe write and read operations.

#include "incl_h.h"
#include "xarray.h"
#include "xprotecteddata.h"
#include "xpointer.h"


//Object - complex type which can store many items such as scalars and arrays
//----------------------------------------------------------------
class XObject
{
public:
    //создает объект заданного типа, по описанию из object_types
    XObject(XObjectType type = XObjectTypeEmpty);
    virtual ~XObject();

    //void begin_access();
    //void end_access();

    //тип - очищается при clear
    XObjectType type() const;
    void set_type(XObjectType);
    //проверить, что объект имеет конкретный тип, если нет - то выдаст exception
    void assert_type(XObjectType expected_type) const;
    bool has_type(XObjectType expected_type) const;


    //размер данных, в байтах
    quint32 size_bytes() const;

    //очистка и копирование
    void clear();
    void copy_to(XObject *object) const;

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
    const XArray *get_array(QString name) const;
    //используйте var_array для изменения массива
    XArray *var_array(QString name, bool create_if_not_exists = false);
    XArray *create_array(QString name);
    QMap<QString,XArray *> &all_arrays();

    bool has_strings(QString name) const;
    const QStringList *get_strings(QString name) const;
    //используйте var_strings для изменения strings
    QStringList *var_strings(QString name, bool create_if_not_exists = false);
    QStringList *create_strings(QString name);
    QMap<QString,QStringList *> &all_stringss();  //любопытное название

    bool has_object(QString name) const;
    XObject const *get_object(QString name) const;
    //используйте var_strings для изменения объекта
    XObject *var_object(QString name, bool create_if_not_exists = false);
    //создает объект, затем его можно наполнять - например, скопировать другой объект
    XObject *create_object(QString name, XObjectType type = XObjectTypeEmpty);
    QMap<QString,XObject *> &all_objects();

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
    XObjectType type_;

    //мютекс для доступа
    //QMutex mutex_;

    //списки, точнее, maps переменных - доступ по имени:
    //int
    QMap<QString,int> int_;

    //float
    QMap<QString,float> float_;

    //string
    QMap<QString,QString> string_;

    //array XArray
    QMap<QString,XArray *> array_;

    //strings   QStringList
    QMap<QString,QStringList *> strings_;

    //object
    QMap<QString,XObject *> object_;
    //то есть, объектов может быть много - но к ним доступ по имени, а не как к массиву

    //pointer - для хранения системных объектов типа FBO
    QMap<QString, void*> pointer_;

};


//protected XObject
typedef XProtectedData_<XObject> XProtectedObject;
typedef XPointer<XObject> XObjectPointer;




#endif // XSTRUCT_H
