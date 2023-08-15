## Xclu classes for working with compute shaders
Xclu SDK contains classes for running compute shaders, purely to compute something without graphics: 

1. `XShaderBuffer` - shader buffer, you can copy to it data from CPU and load back to CPU after computations.
2. `XComputeShader` - compute shader, you can load its code from file, set uniforms and run computations.
3. `XGlContext` - this is Qt-based support for OpenGL context.
You need to have this to work with buffers and compute shaders.
It's good idea to have alone context in the project. Though it supports multithreading too, and you may use several context for such case.

### Note about std430 layout specifier in shader
You may use, for example, array of 23 floats, together with std430 layout specifier
in shader's buffer declaration. Such array works and we are not required to align data to 4*float.
But nevertheless you should't use vec3 anyway in shader buffer, because it's aligned itself to 16 floats anyway!
See details here:
https://stackoverflow.com/questions/38172696/should-i-ever-use-a-vec3-inside-of-a-uniform-buffer-or-shader-storage-buffer-o


## Example

The example creates buffer of 23 floats, passes it to compute shader for processing, reads back and prints to console.

### C++ code

```
QScopedPointer<XGlContext> context;
QScopedPointer<XComputeShader> shader;
QScopedPointer<XShaderBuffer> buffer;

...

//Context - for create and maintaing OpenGL context
context.reset(new XGlContext());

//Compute shader
QString shader_file = ":/shader.csh";
shader.reset(new XComputeShader(shader_file, context.data()));

int N = 23;    
QVector<float> buf(N);
for (int i=0; i<N; i++) {
    buf[i] = i;
}

buffer.reset(new XComputeBuffer(context.data()));
buffer->allocate(buf); //can use raw pointer or any QVector here

//Compute
buffer->bind_for_shader(0); //bind buffer, 0 - index in shader's buffer binding
shader->begin();                  //bind
shader->program().setUniformValue("coeff", 0.5f); //set uniforms
shader->compute(N);           //compute
shader->end();                      //unbind

//Download result to CPU
buffer->read_to_cpu(buf);  //can use raw pointer or any QVector here

qDebug() << "Output buffer: ";
for (int i=0; i<N; i++) {
    qDebug() << "  " << buf[i];
}
```

### Including shader file to project resources

Create shader file:
1. Shader should be put to `shaders/shader.csh` file
2. Should be created resource file `shaders.qrc` and added to Qt project with the following text:
```
<RCC>
    <qresource prefix="/">
        <file alias="shader.csh">shaders/shader.csh</file>
    </qresource>
</RCC>
```

Please note attribute `alias="shader.csh"` here, so you may refer to this file simply as resource file `:/shader.csh` without specifying folder. See details at https://doc.qt.io/qt-5/resources.html.

### Shader code 
```
#version 430

//Example of uniform parameter 
uniform float coeff=1;    

//Buffer for processing
layout(std430, binding = 0) buffer Buf 
{  float buf[];  };

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

void main(void)
{
    uint id = gl_GlobalInvocationID.x;    
    float value = buf[id];  //read input
    value += id*coeff;      //change 
    buf[id] = value;          //write output  
}
```

## Implementation without Xclu

The classes were tested on my Qt example without Xclu:
https://github.com/perevalovds/qtcomputeshader

So if you need implementation of compute shaders in Qt, see it.


## Important notes on using compute shaders

1. Use RGBA images, RGB will not work.
2. Use std140 with 16-byte alignment, or use std430 without it.
3. Local group sizes must be greater than 1 to work fast, now will consider it in details.  

### Local group sizes must be > 1

#### It works slow:
```
w=1920;
h=1080;
dispatch(shader,w,h,1);
```
with shader 
```
...
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
...
```
#### It works much faster:
```
w=1920;
h=1080;
dispatch(shader,w/8,h/8,1);
```
with shader 
```
...
layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;
...
```
