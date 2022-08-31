#pragma once

#include <qoscvalue.h>

class QOscBundle;
class QOscBundlePrivate
{
public:
    QOscBundlePrivate(QOscBundle* q);

    void write(QIODevice* dev) const;

    void load(QIODevice* dev);

    QOscBundle* q_ptr;
    Q_DECLARE_PUBLIC(QOscBundle)

    QOscValue time;
};

