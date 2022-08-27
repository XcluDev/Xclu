#pragma once

#include "xobject.h"
#include <QPainter>

// XObjectVis provides description and visualization for a given object.
// It creates dynamically depending on the object class.
// Create visualizer for object using XObjectVis* XObjectVis::new_vis(object)

class XObjectVis {
public:
    /// Create object visualizer depending on its type. Delete after use.
    static XObjectVis* new_vis(const XObject *object);

    XObjectVis(const XObject *object);

    // Text description
    virtual QStringList short_description() const;
    virtual int detailed_description_size() const;
    virtual QString detailed_description(int i) const;

    // Thumbnail draw
    virtual bool is_thumbnail_exists() const;
    virtual void draw_thumbnail(QPainter &p, int w, int h) const; 

protected:
    const XObject *object_ = nullptr;
};

