Creating a more or less serious project with Xclu requires C++ programming. (In future it’s expected that Xclu will be extendable by JS and DLLs.) 

For that, you may need to develop a one or several modules.

Xclu supports two types of modules: 
* *built-in modules*, which are inside Xclu folder and are intended to use other Xclu users,
* *custom modules*, which are developed for special (private) projects and are stores separately from Xclu.
Here are described general steps for creating both types of modules.

For developing module you should create your own descendant of `XModule` class (or `XModuleVisual` if module should draw something and respond to the mouse/keyboard, see the details below). Here is consists of the four following steps:
1. Create folder for module. If module is built-in, then put it into `builtin_modules` folder into some caegory subfolder. If module is custom (intended for your own projects), then you can place it anythere.
 
2. Put there `description.gui` file and edit it using NotePad++ and testing it using Xclu's menu command *Developer - Test module interface...*. For more details see https://forum.xclu.dev/t/xgui/19
For debugging xgui it's useful to enable showing components names by menu command *View - Show Commands Names*.

3. Export module interface as `auto.h` file using *Export .h file* button in *Test module interface...* dialog, see https://forum.xclu.dev/t/export-modules-xgui-interface-as-h-file/38 and add it to Qt project (just for faster consulting there).

4. Register module. For built-in module you should add `description.gui` file to `xclu.qrc` file. For details about registering custom module see https://forum.xclu.dev/t/adding-custom-modules/28. After registering, check that you see your module at modules list when adding new module to Xclu project. 

5. Implement module. Currently, only C++ implementation is supported. For that, create `.cpp` and `.h` files, which define class inherited from `XModule` class. Inside of this you can create additional classes, which are recommended to inherit from `XClass` class to have access to Xclu SDK. It's a good idea to start developing by copying and renaming some existing module.

Also, add `#include auto.h` inside your class difinition to have access to module's items.

6. After creating .h and .cpp files, add them into Qt. For built-in module it's enough to add the files to Xclu_buiultin.pri file. For registering custom modules implementation files, see https://forum.xclu.dev/t/details-on-developing-a-private-module/28
When implementing module, it's useful to enable showing components names by menu command *View - Show Commands Names*.

### Drawing on the screen
If you need to draw something and respond to mouse and keyboard, consider create module as subclass of `XModule` with `draw()` defined, and connect it to `RenderArea`, which connect to `Window` at Xclu project.


### XModuleWidget - module which create widget for rendering and responds to mouse and keyboard

If you need a module which draws something and responds to mouse and keyboard, use `XModuleWidget` base class:
1. Inherit `XModuleWidget` class instead `XModule`.
2. Add `module_accept_calls=create_widget` to `description.xgui` file.

3. Implement virtual function `void draw(QPainter &painter, int w, int h)`, and call `set_screen_size(int2)` for resizing widget and `redraw()` for repaint widget, which will call your `draw()`. 

4. Implement functions for mouse and/or keyboard handling - see prototypes in `XModuleVisual` class definition.

After that, connect this module to `Window` module content.

See `TestDrawing` module implementation for example how to do all of this.