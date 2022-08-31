#pragma once

//Template class storing pointer to protected object.
//It's used for uniform representing objects items.
//Also, it keeps tracking changes
//If no objct is set - returns default object

#include "incl_h.h"
#include "xerrorhandling.h"
#include "xprotecteddata.h"
#include "xwaschanged.h"

template<typename T>
class XPointer
{
public:
    XPointer() {}

    void set_pointer(XProtectedData_<T> *object) { pointer_ = object; keeper_.touch2(); }
    void reset() { pointer_ = nullptr; keeper_.touch2(); }

    //properties
    bool is_empty() const {     return pointer_ == nullptr; }

    //get data
    //raises  exception if empty
    XProtectedData_<T>* pointer() {    if (is_empty()) return &default_object_;
                                return pointer_; }

    bool was_changed(XWasChangedChecker &checker) {
        //copy changes on the first level (object)
        if (!is_empty()) {
            keeper_.copy_from_level1(*pointer_);
        }
        else {
            keeper_.copy_from_level1(default_object_);
        }
        return keeper_.was_changed(checker);
    }
protected:
    XProtectedData_<T>* pointer_ = nullptr;

    XProtectedData_<T> default_object_;

    //keeper stores changes of pointer on the second level
    XWasChangedKeeper keeper_;
};

