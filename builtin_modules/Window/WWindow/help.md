## Window #################  

Window module creates a window with specified layouts and widgets.  
## 
    
#### Features

* You may set window position and size. 
* Maximized, minimized and full screen modes are supported.

  
##   
#### Window structure
Window can contain of several nested layouts and widgets.
## 
The window content is described in text format at `Content` tab. Here is the example of putting two images
to the window center:

    HorizontalLayout
      Stretch 1
      VerticalLayout
        wimage1
        wimage2
      Stretch 1
  
Another example:
  
    HorizontalLayout
      Tabs 5
        Tab Tab_1
          HorizontalLayout
            wnumber1
            wnumber2
        Tab Tab_2
        Tab Tab_3
      VerticalLayout 0
        wbutton1 0
        wbutton2 0
        Stretch 1
    #First number means stretch

Here:
* Spaces are indentation and means nesting, so buttons and `Stretch` are inside vertical layout which is inside
horizontal layout. Any number of spaces can be used for indent, but indentation on the same level must have equal number of spaces.
* `HorizontalLayout`, `VerticalLayout`, `Tabs` are layouts.
* `Stretch` is stretchable filler.
* `intgui1`,`2`, `buttongui1`,`2` are widgets, which created as separated modules. In our example, 
it's `WidgetInt` and `WidgetButton` modules.
* After each element, except `Tab`, can go optional number for stretch, `0` is a default value.
* `#` means comment.
* By default, VerticalLayout is used as a root node and as a layout if is not specified. 

##   
#### Unique node without indentation
Note, there is must be only one widget or layout of the first level, that is node without indentation.

##   
####
Currently there are supported the following layouts:

* `HorizontalLayout` - horizontal layout.
* `VerticalLayout` - vertical layout.
* `Tabs` - tabs, with `Tab NAME` for each tab. Here `NAME` can't have spaces, use '_' for them.

