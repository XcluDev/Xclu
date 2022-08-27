#ifndef XOBJECTDATA_H
#define XOBJECTDATA_H

// Data stored by XObject
#include "xtypes.h"
#include <QScopedPointer>

class XObjectData
{
public:
    XObjectData();
    virtual ~XObjectData();
};

class XObjectDataImage: public
{
public:
    XObjectDataImage();
    virtual ~XObjectDataImage();


};


#endif // XOBJECTDATA_H
