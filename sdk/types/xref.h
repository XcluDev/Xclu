#ifndef XREF_H
#define XREF_H

//Template class storing object or reference to object.
//It's used for uniform representing objects and links to the objects

#include "incl_h.h"

template<typename T>
class XRef
{
public:
    XRef();

    //set link to object
    void link(T *object);

    //create object
    void create();

    bool is_empty();

    //get data
    //returns exception if empty
    T* data();
protected:
    T* pointer_ = nullptr;
    QScopedPointer<T> data_;

};

#endif // XREF_H
