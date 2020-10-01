#include "xref.h"

#include "incl_cpp.h"

//---------------------------------------------------------------------
template<typename T>
XRef<T>::XRef() {

}


//T* pointer_ = nullptr;
//QScopedPointer<T> data_;

//---------------------------------------------------------------------
//set link to object
template<typename T>
void XRef<T>::link(T *object) {

}

//---------------------------------------------------------------------
//create object
template<typename T>
void XRef<T>::create() {

}

//---------------------------------------------------------------------
template<typename T>
bool XRef<T>::is_empty() {
    return pointer_ != nullptr;
}

//---------------------------------------------------------------------
//get data
//returns exception if empty
template<typename T>
T* XRef<T>::data() {
    xclu_assert(!is_empty(), "Trying to access unitialized XRef object");
    return pointer_;
}

//---------------------------------------------------------------------
