#pragma once

// XObject - класс для хранения "сложных данных" в модулях,
// например растров и звуковых буферов
// Структура класса такова, что предполагает простую передачу
// данных между DLL, поэтому мы не наследуем сам XObject,
// и он сам не хранит данные, а по факту служит указателем с типом.
// "subtype" используется для хранения дополнительной информации
// в случае Custom-объекта.

// XProtectedObject - XObject с оберткой для защиты данных

// XObjectVis* XObjectVis::new_vis(object) - создание визуализатора объекта
// для GUI

#include "incl_h.h"
#include "xprotecteddata.h"
#include "xpointer.h"
#include "xraster.h"

class XObject
{
public:
    XObject();
    virtual ~XObject();

    void clear();

    /// Link object to given data and type. Object not own the data.
    void link(void *data, XType type, QString subtype = "");

    /// Типизированная линковка - C++ сам определяет какой тип
    /// Может использоваться в виде .link<TRaster>(raster), так и link(raster)
    template <class T> void link(T &data);

    XType type() const;
    bool has_type(XType expected_type) const;
    void assert_type(XType expected_type) const;

    QString subtype() const;   // Name of the subtype, used for differenciating objects of "Custom" type

    /// Typed return of the value. If requested type not equal to actual, returns nullptr.
    /// Implemented for void (means any type), XArray, XRaster, XSoundFormat, XSoundBuffer
    /// Usage: const XRaster* raster = object->data<XRaster>();
    ///        if (raster) ...
    template<class T> T* data();
    template<class T> const T* data() const;

    /// Cast to the type with copying - useful to copy values from XProtectedObject<XObject>
    template<class T> bool cast_copy_to(T &data) const;

protected:
    XType type_ = XType::none;
    QString subtype_;

    void* data_ = nullptr;
};

//protected XObject
typedef XProtectedData_<XObject> XProtectedObject;


//---------------------------------------------------------------------
template<class T> void XObject::link(T &data) {
    auto type = cpptype_to_XType<T>();
    xc_assert(type != XType::none, "XObject::link - can't typed link void *")
    link(&data, type);
}

//---------------------------------------------------------------------
template<class T> T* XObject::data() {
    if (!data_ || !has_type(cpptype_to_XType<T>())) return nullptr;
    return (T *)data_;
}

template<class T> const T* XObject::data() const {
    if (!data_ || !has_type(cpptype_to_XType<T>())) return nullptr;
    return (T *)data_;
}

//---------------------------------------------------------------------
/// Cast to the type with copying - useful to copy values from XProtectedObject<XObject>
template<class T> bool XObject::cast_copy_to(T &data) const {
    auto *d = this->data<T>();
    if (d) {
        data = *d;
        return true;
    }
    return false;
}

//---------------------------------------------------------------------
