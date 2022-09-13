#pragma once

// Visualizer for image object.

#include "xobjectvis.h"

class XObjectVisImage : public XObjectVis
{
public:
    XObjectVisImage(const XObject *object);
    virtual QStringList short_description() const;
    virtual int detailed_description_size() const;
    virtual QString detailed_description(int i) const;
    virtual bool is_thumbnail_exists() const;
    virtual void draw_thumbnail(QPainter &p, int w, int h) const;
};

