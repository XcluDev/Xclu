XClu allows to export definitions for C++ access of all module's items. This gives opportunity not to use string literals for variables names, and so perform compiling-time checking of errors of modules variables nemaes, which is extremely useful during initial development and further module updating. It's made using export interface capabilty, which is implemented in `ExportInterface` class and is called from menu *Developer - Test Module interface...*, *Export .h* file button.

Pressing the button generates .h file which can be included directly inside your XClass or XModule subclass, related to your module:
    
    class XModuleMyModule {
    ...
    #include "auto.h"
    ...
    };

The `auto.h` file contains all definitions for strict access to module's items:

    //C++ -------------------------
    //function generates function or functions definitions
    //for using inside C++ class module definition
    /*
    //----------------------------------------------------
    //Page Main
    //...

    //Folder to scan.
    QString gets_folder() {...}      
    void sets_folder(QString value) {...}

    //Enum Position
    //Position of the window.  
    enum enum_position {
        position_Default = 0,
        position_Custom = 1,
        position_Screen_Center = 2,
        position_N__ = 3
    };
    bool was_changed_position() { ... }
    enum_position gete_position() { ... }

Function names begin with prefix denoting type of the item as the following:

* `geti_...`, `seti_...` - int, button, checkbox
* `gete_...`, `sete_...`, `gets_...` - enum
* `getf_...`,`setf_...` - float
* `gets_...`, `sets_...` - string, text
* `getstruct_...` - structure

Also are defined the following useful functions:
* `was_changed_...` - all items,
* `get_strings_...` - string, text
* `clear_string_...`, `append_string_...` - out string, out text,
* `increase_int_...` - out int,
* `QString button_...` - button, for using in `impl_button_pressed()`
* `repaint_...` - applicable to all out items, it refreshes the associated GUI widget; applied for `out` variables for informing user about status during long operations.