#pragma once

#include "xobject.h"
#include <QPainter>

// XObjectVis provides description for a given object
// It creates dynamically depending on the object class

class XObjectVis {
public:
    XObjectVis(class XObject *object);

    // Text description
    virtual QStringList short_description() const;
    virtual int detailed_description_size() const;
    virtual QString detailed_description(int i) const;

    // Thumbnail draw
    virtual bool is_thumbnail_exists() const;
    virtual void draw_thumbnail(QPainter &p, int w, int h) const; 

protected:
    class XObject *object_ = nullptr;
};

