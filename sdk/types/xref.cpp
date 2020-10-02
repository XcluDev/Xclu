#include "xref.h"

#include "incl_cpp.h"

//---------------------------------------------------------------------
template<typename T>
XRef<T>::XRef() {

}

//---------------------------------------------------------------------
template<typename T>
void XRef<T>::release() {
    pointer_ = nullptr;
    data_.reset();
}

//---------------------------------------------------------------------
//set link to object
template<typename T>
void XRef<T>::link(T *object) {
    release();
    pointer_ = object;
    is_owner_ = false;

}

//---------------------------------------------------------------------
//become owner of the object
template<typename T>
void XRef<T>::own(T *object) {
    data_.reset(object);
    pointer_ = object;
    is_owner_ = true;
}

//---------------------------------------------------------------------
template<typename T>
bool XRef<T>::is_empty() {
    return pointer_ != nullptr;
}

//---------------------------------------------------------------------
template<typename T>
bool XRef<T>::is_link() {
    xclu_assert(!is_empty(), "Calling 'is_link' of unitialized XRef object");
    return !is_owner_;
}

//---------------------------------------------------------------------
template<typename T>
bool XRef<T>::is_owner() {
    xclu_assert(!is_empty(), "Calling 'is_owner' of unitialized XRef object");
    return is_owner_;
}

//---------------------------------------------------------------------
//get data
//raises exception if empty
template<typename T>
T* XRef<T>::data() {
    xclu_assert(!is_empty(), "Calling 'data' of unitialized XRef object");
    return pointer_;
}

//---------------------------------------------------------------------
