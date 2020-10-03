#ifndef XREF_H
#define XREF_H

//Template class storing object or reference to object.
//It's used for uniform representing objects and links to the objects

#include "incl_h.h"
#include "console.h"
#include "xcluprotecteddata.h"

template<typename T>
class XRef
{
public:
    XRef() {}

    //set link to object
    void link(T *object) {  release();
                            pointer_ = object;
                            is_owner_ = false; }

    //become owner of the object
    void own(T *object) {     data_.reset(object);
                              pointer_ = object;
                              is_owner_ = true; }

    //free
    void release() {     pointer_ = nullptr;
                         data_.reset(); }

    //properties
    bool is_empty() {     return pointer_ == nullptr; }

    //raises exception if empty
    bool is_link() {     xclu_assert(!is_empty(), "Calling 'is_link' of unitialized XRef object");
                         return !is_owner_; }

    //raises  exception if empty
    bool is_owner() {     xclu_assert(!is_empty(), "Calling 'is_owner' of unitialized XRef object");
                          return is_owner_; }

    //get data
    //raises  exception if empty
    T* data() {     xclu_assert(!is_empty(), "Calling 'data' of unitialized XRef object");
                    return pointer_; }
protected:
    bool is_owner_ = false;
    T* pointer_ = nullptr;
    QScopedPointer<T> data_;
};


#endif // XREF_H
