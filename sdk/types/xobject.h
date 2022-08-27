#ifndef XSTRUCT_H
#define XSTRUCT_H

// XObject - basic Xclu type for passing data between modules;
// Create visualizer for object using XObjectVis* XObjectVis::new_vis(object)

#include "incl_h.h"
#include "xprotecteddata.h"
#include "xpointer.h"
#include "xraster.h"

//Типы для объектов XObject
//При добавлении новых типов объектов дописывать их визуализацию в систему XObjectWrapper
enum class XObjectType : int {
    Empty = 0,                  // пустой объект
    Custom = 1,                 // some custom object; use "subtype" at XObject to differenciate them
    Array = 2,                  // Array
    Image = 3,                  // изображение
    SoundFormat = 4,            // формат звука
    SoundBuffer = 5,             // звуковой буфер
    N = 6
};

QString XObjectType_to_string(XObjectType type);
XObjectType string_to_XObjectType(QString type_str);


//----------------------------------------------------------------
class XObject
{
public:
    XObject();
    virtual ~XObject();

    /// Setup object by given data and type. Object not own the data.
    void setup(void *data, XObjectType type, QString subtype = "");

    /// Implemented for XArray, XRaster, XSoundFormat, XSoundBuffer
    template <class T> void setup(T *data);

    XObjectType type() const;
    bool has_type(XObjectType expected_type) const;
    void assert_type(XObjectType expected_type) const;

    QString subtype() const;        // Name of the subtype, used for differenciating objects of "Custom" type

    void* data();
    const void* data() const;

    /// Useful for getting typed values. Implemented for XArray, XRaster, XSoundFormat, XSoundBuffer
    /// Usage: const XRaster* raster = object->data<XRaster>();
    template <class T> T* data();
    template <class T> const T* data() const;


protected:
    XObjectType type_ = XObjectType::Empty;
    QString subtype_;

    void* data_ = nullptr;
};


//protected XObject
typedef XProtectedData_<XObject> XProtectedObject;


#endif // XSTRUCT_H
