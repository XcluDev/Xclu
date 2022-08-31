#pragma once

// Visualizer for sound buffer object.

#include "xobjectvis.h"

class XObjectVisSoundBuffer : public XObjectVis
{
public:
    XObjectVisSoundBuffer(const XObject *object);
    virtual QStringList short_description() const;
    virtual int detailed_description_size() const;
    virtual QString detailed_description(int i) const;
    virtual bool is_thumbnail_exists() const;
    virtual void draw_thumbnail(QPainter &p, int w, int h) const;
};

