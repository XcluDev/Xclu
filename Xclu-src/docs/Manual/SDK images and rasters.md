Include header for working with rasters:

    #include "xraster.h"
    #include "xcluobjectimage.h"

For working with images and rasters are used the following classes:

* `XRaster_u8` - grayscale 1-channel 8-bit image, 
* `XRaster_u8c3` - color 3-channel 8-bit image, 
* `XRaster_u16` - grayscale 1-channel 16-bit image,                       
* `XRaster_float` - grayscale 1-channel 8-bit image,                     
* `XRaster_vec2` - 2-dimensional float vector (`glm::vec2`) image,                   
* `XRaster_vec3` - 3-dimensional float vector (`glm::vec3`) image,                  
* `XRaster` - class containing static functions `convert`, `load`, `save` for converting color rasters to grayscale and back, to `QImage` and back, and also save and load rasters to disk.

## Full list:
    
    typedef XRaster_<uint8> XRaster_u8;
    typedef XRaster_<rgb_u8> XRaster_u8c3; //color image
    typedef XRaster_<sint8> XRaster_s8;
    typedef XRaster_<int16> XRaster_int16;
    typedef XRaster_<u16> XRaster_u16;
    typedef XRaster_<u32> XRaster_u32;
    typedef XRaster_<int32> XRaster_int32;
    typedef XRaster_<float> XRaster_float;
    typedef XRaster_<rgb_float> XRaster_float3; //see XRaster_vec3 below!
    typedef XRaster_<double> XRaster_double;
    typedef XRaster_<glm::vec2> XRaster_vec2;
    typedef XRaster_<glm::vec3> XRaster_vec3;
    typedef XRaster_<int2> XRaster_int2;

## Converting rasters

Rasters can be converted from QImage by copying or linking:
* `XObjectImage::to_raster(reader.data(), input_);`
* `XRaster::link(...)`
### Read raster from "in" image
Example: 

    #include "xraster.h"
    #include "xcluobjectimage.h"
    
    ...

    auto reader = getobject_input_image()->read();

    //no image yet
    if (reader.data().type() != XObjectTypeImage) return;

    //define raster
    XRaster_u8 input_;  //grayscale
     //XRaster_u8c3 input_; //color
   
    //read GUI image to raster
    //color image will be converted to grayscale if required
    XObjectImage::to_raster(reader.data(), input_);

See `XModuleMotionDetector` and `XModuleSynthFromImage` modules implementation as example.

### Set raster to "out" image

Example:

    #include "xraster.h"
    #include "xcluobjectimage.h"
    
    class ... {
        XProtectedObject out_image_gui_;  //define imterface image, will link to GUI
        XRaster_u8 out_image_;       //define GUI raster 
    }
    
    void ...::impl_start() {
        //link `output_image` xgui item to `out_image_gui_`
        setobject_output_image(&out_image_gui_); 
        //clear image
        out_image_.write().data().clear();
        ...
    }

    void ...::impl_update() {
        //make out_image_
        ...
        //set out_image_ to gui object
        XObjectImage::create_from_raster(out_image_gui_.write().data(), out_image_);

    }

Note: also you can load object directly load from image file:

        XObjectImage::load(out_image_gui_.write().data(), file_name);


See `ImageLoader` and `XModuleMotionDetector` modules implementation as example.