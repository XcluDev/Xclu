Modules are communicated between theirself using several ways:

1. Module gets values from other modules using "links" to values: `webcamera->image1`, to space-separated string items: `module1->line(2)`, to tables: `module1->table(2,3)`.
C++: `RUNTIME.get_string_by_link(link_str);`

2. Module can send button presses using link: `module1->play_button`  
C++: `RUNTIME.press_button_by_link(link_str);`

3. *Only C++* Module can internally set variable in other modules with `out` qualifier.

4. *Only C++* Module can internally call other's module function, for example request of sound buffer or widget pointer.