#ifndef XCLASS_H
#define XCLASS_H

//XClass - Xclu base class for implementing stuff for modules.
//It provides access for runtime information and module's values
//So XClass is not module itself, but some "helper" class.
/* Usage: you need to specify Module in constructor or later, by calling set_module(module) or set_module(this):

  ...
void CosmoOsc::setup(Module *module, int index) {
    set_module(module);
  ...

 */

#include "incl_h.h"

class Module;
class XcluObject;

class XClass
{
public:
    //Constructor requires providing underlying module pointer
    //for accessing its GUI values
    XClass() {}
    XClass(Module *module);

    void set_module(Module *module);

    //Underlying module
    Module *module();

    //Variables access
    //get int, set int
    int geti(QString name, int index1 = -1, int index2 = -1);
    void seti(QString name, int v);

    //get float, st float
    float getf(QString name, int index1 = -1, int index2 = -1);
    void setf(QString name, float v);

    //get string, set string
    QString gets(QString name, int index1 = -1, int index2 = -1);
    void sets(QString name, QString v);
    QStringList get_strings(QString name);     //splits text using "\n"

    //get object - for particular access, you need to use ObjectRead or Object ReadWrite
    XcluObject *get_object(QString name);

protected:
    Module *module_;

};

#endif // XCLASS_H
