#ifndef XREF_H
#define XREF_H

//Template class storing object or reference to object.
//It's used for uniform representing objects and links to the objects

#include "incl_h.h"
#include "xcluprotecteddata.h"

template<typename T>
class XRef
{
public:
    XRef();

    //set link to object
    void link(T *object);

    //become owner of the object
    void own(T *object);

    //free
    void release();

    //properties
    bool is_empty();
    bool is_link();   //raises exception if empty
    bool is_owner();  //raises  exception if empty

    //get data
    //raises  exception if empty
    T* data();
protected:
    bool is_owner_ = false;
    T* pointer_ = nullptr;
    QScopedPointer<T> data_;
};


#endif // XREF_H
