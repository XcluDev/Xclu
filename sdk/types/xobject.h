#pragma once

// XObject - basic Xclu type for passing data between modules;
// Create visualizer for object using XObjectVis* XObjectVis::new_vis(object)

#include "incl_h.h"
#include "xprotecteddata.h"
#include "xpointer.h"
#include "xraster.h"

//----------------------------------------------------------------
class XObject
{
public:
    XObject();
    virtual ~XObject();

    void clear();

    /// Link object to given data and type. Object not own the data.
    void link(void *data, XType type, QString subtype = "");

    /// Implemented for XArray, XRaster, XSoundFormat, XSoundBuffer
    template <class T> void link(T &data);

    XType type() const;
    bool has_type(XType expected_type) const;
    void assert_type(XType expected_type) const;

    QString subtype() const;        // Name of the subtype, used for differenciating objects of "Custom" type

    /// Typed return of the value. If requested type not equal to actual, returns nullptr.
    /// Implemented for void (means any type), XArray, XRaster, XSoundFormat, XSoundBuffer
    /// Usage: const XRaster* raster = object->data<XRaster>();
    ///        if (raster) ...
    template <class T> T* data();
    template <class T> const T* data() const;

    /// Cast to the type with copying - useful to copy values from XProtectedObject<XObject>
    template <class T> bool cast_copy_to(T &data);
    template <class T> bool cast_copy_to(const T &data) const;

protected:
    XType type_ = XType::none;
    QString subtype_;

    void* data_ = nullptr;
};

//protected XObject
typedef XProtectedData_<XObject> XProtectedObject;

