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

