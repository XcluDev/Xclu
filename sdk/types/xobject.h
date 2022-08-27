#ifndef XSTRUCT_H
#define XSTRUCT_H

// XObject - basic Xclu type for passing data between modules;
// use only when you are sure in that; normally use its safe wrapper XProtectedObject.
// Create visualizer for object using XObjectVis* XObjectVis::new_vis(object)

#include "incl_h.h"
#include "xprotecteddata.h"
#include "xpointer.h"
#include "xraster.h"



//Object - opaque type
/*
интерфейсы:
   - тип
   - получение краткого и подробного описания
   - краткая визуализация - генерация картинки и текстового описания
   - подробная визуализация (окно).
   //- запись и считывание в файл (строку, JSON).

   и уже для каждого типа специфические команды, наприммер, конвертирование изображения в растр и обратно

Типы:
  - изображения - разнообразных типов.
    Для каждого вводим свое имя, и в templates их реализуем.
  - звуковой буфер
  - JSON
  - custom data - массив с данными

Это позволит передавать их из модулей в виде ссылок, а не копировать каждый раз (преобразуя в raster).
А значит, сделает разработку модулей более понятной и более эффективной.
*/

//Типы для объектов XObject
//При добавлении новых типов объектов дописывать их визуализацию в систему XObjectWrapper
enum class XObjectType : int {
    Empty = 0,                  // пустой объект
    Custom = 1,                 // some custom object; use "subtype" at XObject to differenciate them
    Image = 2,                  // изображение
    SoundFormat = 3,            // формат звука
    SoundBuffer = 4,             // звуковой буфер
    N = 5
};

QString XObjectType_to_string(XObjectType type);
XObjectType string_to_XObjectType(QString type_str);


//----------------------------------------------------------------
class XObject
{
public:
    XObject(XObjectType type = XObjectType::Empty);
    virtual ~XObject();

    // Setters
    void set_image(const XRaster &raster);
    void set_sound_format(const XSoundFormat &format);
    void set_sound_buffer(const XSoundBuffer &buffer);

    XObjectType type() const;
    bool has_type(XObjectType expected_type) const;
    void assert_type(XObjectType expected_type) const;

    QString subtype() const;        // Name of the subtype, used for differenciating objects of "Custom" type


protected:
    XObjectType type_ = XObjectType::Empty;
    QString subtype_;

    // Data storing inside object
    QString str;
    XRaster raster;
    void* pointer = nullptr;
};


//protected XObject
typedef XProtectedData_<XObject> XProtectedObject;


#endif // XSTRUCT_H
