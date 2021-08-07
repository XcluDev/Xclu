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
#include "xobject.h"

class Module;

class XClass
{
public:
    //Constructor requires providing underlying module pointer
    //for accessing its GUI values
    XClass() {}
    XClass(Module *module);

    //----------------------------------------------
    //Underlying module
    //----------------------------------------------
    void set_module(Module *module);
    Module *module();

    //----------------------------------------------
    //Variables access
    //they are marked with "_" at end, because it's proposed use them using "auto.h" file,
    //see https://forum.xclu.dev/t/export-modules-xgui-interface-as-h-file/38
    //----------------------------------------------
    //Check if value was changed
    //It's important, that for objects this function obtain access using XObjectRead,
    //hence it should not be called for already active XObjectRead[Write] for this object
    bool was_changed_(QString name, XWasChangedChecker &checker);

    //This was_changed is checks changes between `update` calls
    bool was_changed_(QString name);

    //Repaint - force GUI widget to refresh, useful for long operations for updating numbers/texts
    void repaint_(QString name);

    //int, checkbox, button, enum (rawtext), string, text
    //index>=0: string, text separated by ' ' - no error if no such string!
    //index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
    QString gets_(QString name, int index = -1, int index2 = -1);
    //splits text using "\n"
    QStringList get_strings_(QString name);

    void sets_(QString name, QString v); //только out: int, checkbox, enum (rawtext), string, text
    void clear_string_(QString name);
    void append_string_(QString name, QString v, int extra_new_lines_count = 0); //дописать к строке, применимо где sets
    void append_string_(QString name, QStringList v, int extra_new_lines_count = 0); //дописать к строке, применимо где sets

    //int, checkbox, button, enum (index)
    //index>=0: string, text separated by ' ' - no error if no such string!
    //index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
    int geti_(QString name, int index = -1, int index2 = -1);

    void seti_(QString name, int v); //только out: int, checkbox, enum (index)
    void increase_int_(QString name, int increase = 1); //увеличение значения

    //float
    //index>=0: string, text separated by ' ' - no error if no such string!
    //index2>=0: string, text separated by '\n' and ' ' - no error if no such string!
    float getf_(QString name, int index = -1, int index2 = -1);
    void setf_(QString name, float v);  //out: float

    QString getraw_(QString name);  //enum (rawtext)
    void set_raw_(QString name, QString v); //out: enum (rawtext)

    QString get_title_value_(QString name);  //enum (title)
    void set_title_value_(QString name, QString v); //out: enum (title)

    //Access to objects is only by pointers - because we are required not to copy data, it can be large
    XProtectedObject *get_object_(QString name);
    //Set pointer to object
    //Note: object must be persistent, because only pointer to it is stored
    void set_object_(QString name, XProtectedObject *object);
    //Set reference to object
    //Note: object must be persistent, because only pointer to it is stored
    void set_object_(QString name, XProtectedObject &object);

protected:
    Module *module_ = nullptr;

};

#endif // XCLASS_H
