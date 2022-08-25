#ifndef XSTRUCT_H
#define XSTRUCT_H

// XObject - basic Xclu type for passing data between modules;
// use only when you are sure in that; normally use its safe wrapper XProtectedObject.

// XProtectedObject - thread-safe object wrapper on XObject.
// It applies mutexes for safe write and read operations.

#include "incl_h.h"
#include "xprotecteddata.h"
#include "xpointer.h"


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

//----------------------------------------------------------------
class XObject
{
public:
    XObject(XObjectType type = XObjectType::Empty);
    virtual ~XObject();

    XObjectType type() const;
    bool has_type(XObjectType expected_type) const;
    void assert_type(XObjectType expected_type) const;

    QString subtype() const;        // Name of the subtype, used for differenciating objects of "Custom" type

    // Short text description for UI
    virtual QStringList short_description() const { return QStringList(); }

    // Detailed description for UI, for example all image pixels values
    virtual int detailed_description_size() const { return 0; }
    virtual QString detailed_description(int /*i*/) const { return ""; }

    // Thumbnail draw
    virtual bool thumbnail_exists() const { return false; }
    virtual void draw_thumbnail(class QPainter &/*p*/, int /*w*/, int /*h*/) const {}
protected:
    XObjectType type_ = XObjectType::Empty;
    QString subtype_;
};


//protected XObject
typedef XProtectedData_<XObject> XProtectedObject;


#endif // XSTRUCT_H
