#pragma once

#include <QVector>
#include "xtype.h"

//--------------------------------------------------
/// XArray - array class.
//--------------------------------------------------
class XArray {
public:
    XArray() {}
    int n = 0;
    int sizeofitem = 0;
    XType type = XType::none; // To change this value you must call call set_type()
protected:
    bool is_owner = false;   // Does raster hold its own memory, or use external source
    quint8 *data_pointer_ = nullptr;
    QVector<quint8> internal_data_;        // Internal storage

    // Внимание: При добавлении членов - корректировать operator=
public:
    XArray(const XArray& other);
    XArray& operator=(const XArray& other);

    void set_type(XType type); // Must be called instead of directly changing type
    void assert_type(XType type) const;

    bool is_empty() const;

    // Checks only internal images
    bool is_valid() const;

    void* data_pointer();
    const void* data_pointer() const;
    int data_size_in_bytes() const;

    template<class T> T* data();
    template<class T> const T* data() const;

    // Типизированный доступ к элементам
    // - Для безопасности - стараться проверять assert_type().
    template<class T> T& item_unsafe(int i);
    template<class T> const T& item_unsafe(int i) const;

    template<class T> void set_item_unsafe(int i, const T &value); // Note: value size must be sizeofitem

    // Нетипизированный доступ к элементам используется для универсальных операций
    void* item_unsafe_ptr(int i);
    const void* item_unsafe_ptr(int i) const;

    void set_item_unsafe_ptr(int i, const void *value); // Note: value size must be sizeofitem


    /// Заполнить растр значениями
    template<class T> void set(const T &value);

    //----------------------------------------------------------------------------
    // Allocating - allocate own memory for raster
    //----------------------------------------------------------------------------

    // If 'reallocate is true - then old vector will be cleared.
    // It's useful for clearing memory when image size if significantly reduced, but works slower.
    void allocate(int n, XType type, bool reallocate = false);

    template<class T> void allocate(int n, bool reallocate = false);


    void clear();

    //----------------------------------------------------------------------------
    // Copying
    //----------------------------------------------------------------------------
    void copy_from(void* data, int n, XType type);
    template<class T> void copy_from(T* data, int n);

    //----------------------------------------------------------------------------
    // Linking - using external source of pixels, not copying it.
    // Use this mode carefully and control the source data exists while this XRaster is used!
    //----------------------------------------------------------------------------
    void link_data(void* data, int n, XType type);
    template<class T> void link_data(T* data, int n);

    // Operations
    void add_inplace(const XArray &a);
    void mult_inplace(const XArray &a);
    XArray crop(int i0, int n0) const;
};

//----------------------------------------------------------------------------
template<class T> T& XArray::item_unsafe(int i) {
    return *(T*)&data_pointer_[sizeofitem*(i)];
}
template<class T> const T& XArray::item_unsafe(int i) const {
    return *(const T*)&data_pointer_[sizeofitem*(i)];
}
template<class T> void XArray::set_item_unsafe(int i, const T &value) { // Note: value size must be sizeofitem
    memcpy(item_unsafe<void*>(i), &value, sizeofitem);
}

//---------------------------------------------------------------------
template<class T> void XArray::set(const T &value) {
    assert_type(cpptype_to_XType());
    for (int i=0; i<n; i++) {
        set_item_unsafe<T>(i, value);
    }
}

//---------------------------------------------------------------------


