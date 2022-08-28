#ifndef XARRAY_H
#define XARRAY_H

#include <QVector>
#include "xtypeid.h"

//--------------------------------------------------
/// XArray - array class.
//--------------------------------------------------
class XArray {
public:
    XArray() {}
    int n = 0;
    int sizeofitem = 0;
    XTypeId type_id = XTypeId::none; // To change this value you must call call set_type()

    void set_type(XTypeId type_id); // Must be called instead of directly changing type_id
    void assert_type(XTypeId type) const;
protected:
    bool is_owner = false;   // Does raster hold its own memory, or use external source
    quint8 *data_pointer_ = nullptr;
    QVector<quint8> internal_data_;        // Internal storage

public:
    bool is_empty() const;

    // Checks only internal images
    bool is_valid() const;

    void* data_pointer();
    const void* data_pointer() const;
    int data_size() const;

    // items access
    void* item_unsafe(int i);
    const void* item_unsafe(int i) const;
    void item_unsafe(int i, void* &value);
    void item_unsafe(int i, const void* &value) const;

    void set_item_unsafe(int i, const void *value); // Note: value size must be sizeofitem

    //----------------------------------------------------------------------------
    // Allocating - allocate own memory for array
    //----------------------------------------------------------------------------

    // If 'reallocate is true - then old vector will be cleared.
    // It's useful for clearing memory when image size if significantly reduced, but works slower.
    void allocate(int n, XTypeId Type_id, bool reallocate = false);

    void copy_from(void* input_data, int n, XTypeId Type_id);

    void clear();

    //----------------------------------------------------------------------------
    // Linking - using external source of pixels, not copying it.
    // Use this mode carefully and control the source data exists while this XRaster is used!
    //----------------------------------------------------------------------------
    void link_data(int n, void* data, XTypeId type);

    // Operations
    void set(const void* value);

    void add_inplace(const XArray &a);

    void mult_inplace(const XArray &a);

    XArray crop(int i0, int n0) const;
};

#endif // XARRAY_H
