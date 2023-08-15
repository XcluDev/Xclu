The described functions are mainly at `utils.h` and `types.h`, `xcore.h`, as well inside **Qt** and **glm**.

### Scalar and vector types
* `uint8`, `sint8`, `int16`, `u16`, `u32`, `int32` - basic types
* vectors: `QVector<>`, for example, `QVector<float>`. It behaves much like `std::vector`, but has `data()` member for data access.
Note, that `QVector::clear()` remains keeps allocated memory, so for clear `QVector` use `swap()`:
    `QVector<float>().swap(my_vec);`.

* 2d float point: `glm::vec(0,0)`. Please note: you *must* call constructor, because by default it has junk values.
* 3d float point: `glm::vec3(0,0,0)`. Please note: you *must* call constructor, because by default it has junk values.
* 2d integer point: `int2(0,0)`.
* integer rectangle: `rect_int`.

### Data protection
For multithreaded cases, use `XProtectedData_<>` class. It provides multiple read, single write access, and changing detection.

### Math functions
* Linear interpolation from [0,1]: `xlerpf()`, `xlerpd()`  
* Linear interpolation: `xmapf()`, `xmapd()`, `xmapi()`, `xmapf_clamped()`, `xmapd_clamped()`, `xmapi_clamped()`
* Clamping: `xclampf()`, `xclampd()`, `xclampi()`
* Min/max: `minf|d|i()`, `maxf|d|i()`, 
   `qMin()`, `qMax()`
* Sin/cos: `qSin(), qCos()` 
* Swap: `qSwap()`, `std::swap()`
* Random: `xrandomi(int a, int b)`, `xrandomf(float a, float b)`, 
* Distance: `glm::distance(veca, vecb)`, squared: `glm::distance2(veca, vecb)`
* Vector length: `glm::length(veca, vecb)`, squared: `glm::length2(veca, vecb)`

### Noise
Simplex noise: xNoise(), xSignedNoise().

### Strings
Use `QString` class. 

### String to numbers and time conversion utilities
* `xparse_float()` - string to float with error handling
* `xparse_int()` - string to int with error handling
* `xparse_seconds_to_hms(double seconds)` seconds -> HMS, that is 00:00:00:0
* Example of converting int or float to string with specified format string: `QString("value is %1").arg(value)`

### Pointers
Use `QScopedPointer<T> data;` for auto-deleting pointer out of scope.

### Rasters
* `XRaster_u8`      
* `XRaster_u8c3`, `XRaster_u8c4`   
* `XRaster_u16`   
* `XRaster_float`    
* `XRaster_vec2` 
* `XRaster_vec3`
* converting: `XRaster::convert()` - between `XRaster_` and `QImage`,
`XObjectImage::create_from_QImage() ` - fast convert QImage to GUI's Object Image.
* drawing: `XRaster::draw()` draws to QPainter 
* load, save: `XRaster::load()`, `XRaster::save()`
* blur: `XRaster::blur()`
(See "SDK: images and rasters")

### Logic
* `XSlowbit` - 1/0 switch with given times.

### Time
* Seconds from project start: `xc_elapsed_time_sec()`.
* Time step between frames: `xc_dt()`.

### Paths
* `xc_project_folder()` - full path to the current project folder. 

* `xc_app_folder()` - path to the folder with Xclu executable.

* `xc_absolute_path_from_project()` - convert relative path to absolute. For example, use it for loading files specified related to the project.


### Files
* `xc_file_exists()`, `xc_folder_exists()` - check if file/folder exists.
* `xc_write_text_file()`, `xc_read_text_file()` - write and read text files represented as `QStringList`.
* `xc_write_binary_file()`, `xc_read_binary_file()` - write and read binary file, optionally appending it.

### Bat/bash script execution
`xc_exec_batch()` function allows to execute bat/bash scripts represented as string lists.
It's used in ML_Execute module.
1. Script is parsed: variable {var_name} replaced by var_value           
for example:                                                              
    in `python dataset_tool.py create_from_images {datasets_folder} {images_folder} ` 
    `{datasets_folder} and `{image_folder}` will be replaced by values of variables `datasets_folder` and `image_folder` passed to the function.
2. Script is saved as file with specified name.                                                
3. Script is executed.                                                     

### WAV files
Working with WAV files and utilities - see at `xc_audio` namespace, `sdk/audio` folder.
See `XModuleSoundSamplesML` class for usage example.

### Sending bangs
    
Module can send "bangs", that is signal to perform update or press a button.
Normally, user specify the list of bangs in text component, and module call this as `xc_bang(get_strings_bang_list());`

Namely, the mechanism for bang sending is implemented by two steps:
1. Create a text component, for example, `bang_list`. User can fill it with a module names or buttons links:

       module1
       module2->play_button
       #module3->stop_button  - it's comment

In the code, when required, for example, if motion detector switched on, call `xc_bang()` function with argument containing QStringList:

    xc_bang(get_strings_bang_list());

It will scan the list and call corresponding bangs.