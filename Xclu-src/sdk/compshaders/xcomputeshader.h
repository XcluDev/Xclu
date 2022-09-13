#pragma once

/*
Here are helper classes supporting using compute shaders without graphics rendering.

* XShaderBuffer - shader buffer, you can copy to it data from CPU and load back to CPU after computations.
* XComputeShader - compute shader, you can load its code from file, set uniforms and run computations.
* XGlContext - this is Qt-based support for OpenGL context.
You need to have this to work with buffers and compute shaders.
It's good idea to have alone context in the project.
Though it supports multithreading too, and you may use several context for such case

I tested this classes on small example without Xclu,
so if you need use compute shaders outside Xclu, use this: https://github.com/perevalovds/qtcomputeshader

See more details in Xclu documentation:
https://forum.xclu.dev/t/using-compute-shaders/44

### Credits
The code is made using ideas from the following codes:
*    The basis is "openglwindow" Qt example
*    Qt and shader connection is based on https://forum.qt.io/topic/104448/about-buffer-for-compute-shader/6
*    Compute shader text contains fragments from https://github.com/1DIce/Qt3D_compute_particles_cpp

Useful links:
*    Khronos docs about shader buffers:
     https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object
     https://www.khronos.org/opengl/wiki/Buffer_Object
*    Qt QOpenGLBuffer sources which show me that I must use bind/unbind often,
     because this buffer really doesn't do it (but should...):
     https://code.woboq.org/qt5/qtbase/src/gui/opengl/qopenglbuffer.cpp.html


### Note about std430 layout specifier in shader
You may use, for example, array of 23 floats, together with std430 layout specifier
in shader's buffer declaration. Such array works and we are not required to align data to 4*float.
But nevertheless you should't use vec3 anyway in shader buffer, because it's aligned itself to 16 floats anyway!
See details here:
https://stackoverflow.com/questions/38172696/should-i-ever-use-a-vec3-inside-of-a-uniform-buffer-or-shader-storage-buffer-o

### C++ code
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

xcassert(N /% 64 == 0, "To use GPU potential, you need at least 64 local groups, so N must be visible by 64);
int Nuse = N / 64;

//Compute
buffer->bind_for_shader(0); //bind buffer, 0 - index in shader's buffer binding
shader->begin(); //bind
shader->program().setUniformValue("coeff", 0.5f); //set uniforms
shader->compute(Nuse); //compute N/64, to fast compations!
shader->end(); //unbind

//Download result to CPU
buffer->read_to_cpu(buf);  //can use raw pointer or any QVector here

qDebug() << "Output buffer: ";
for (int i=0; i<N; i++) {
    qDebug() << "  " << buf[i];
}
```

### Shader code
#version 430

//Example of uniform parameter
uniform float coeff=1;

//Buffer for processing
layout(std430, binding = 0) buffer Buf
{ float buf[]; };


//Note: we use local size x 64 to speedup!
//https://stackoverflow.com/questions/62598804/slow-compute-shader-global-vs-local-work-groups
layout(local_size_x = 64, local_size_y = 1, local_size_z = 1) in;

void main(void)
{
    uint id = gl_GlobalInvocationID.x;
    float value = buf[id];  //read input
    value += id*coeff;      //change
    buf[id] = value;        //write output
}
//---------------------------------------------------------------------
*/

#include <QOffscreenSurface>
#include <QtGui/QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>
#include "incl_h.h"

QT_BEGIN_NAMESPACE
class QOpenGLContext;
QT_END_NAMESPACE


class XGlContext;

//---------------------------------------------------------------------
//XGlCommon
//Class storing GL context and QOffscreenSurface and manages errors handling.
//It's inherited by ShaderBuffer and ComputeShader
//Used in XShaderBuffer and XComputeShader
//---------------------------------------------------------------------
class XGlCommon {
public:

protected:
    void setup(XGlContext *context);
    XGlContext *context_ = nullptr;

    void gl_assert(QString message); //Check openGL error
    void xassert(bool condition, QString message); //Check Qt wrapper error
    void activate_context();

    QOpenGLFunctions_4_3_Core *gl();
};

//---------------------------------------------------------------------
//XShaderBuffer
//Class for warping GPU buffer, will it with values from CPU and load to CPU after computations
//---------------------------------------------------------------------
class XShaderBuffer: public XGlCommon {
public:
    explicit XShaderBuffer(XGlContext *context);

    //Put data to GPU
    //Can use raw pointer or any QVector here
    void allocate(void *data, int size_bytes);
    template<typename T>
    void allocate(QVector<T> data) {
        if (data.isEmpty()) {
            allocate(nullptr, 0);
        }
        else {
            allocate(data.data(), data.size() * sizeof(T));
        }
    }
    void allocate(int size_bytes);

    //Copy data to CPU
    //Can use raw pointer or any QVector here
    //TODO: for faster approach, it may be interfaced using map which gives "raw" pointer without copying
    void read_to_cpu(void *data, int size_bytes);
    template<typename T>
    void read_to_cpu(QVector<T> &data) { //data must be allocated for required size
        int size_bytes = data.size() * sizeof(T);
        read_to_cpu(data.data(), size_bytes);
    }

    void clear();

    //Bind buffer to shader by specifying its binding index:
    //Shader:
    //    layout(std430, binding = 0) buffer Buf
    //    { float buf[]; };
    void bind_for_shader(int binding_index);

protected:
    QOpenGLBuffer shader_buffer_;

    //We must always bind/unbind buffer for the most operations - it's not made by Qt!
    //See the details at Qt code:
    //https://code.woboq.org/qt5/qtbase/src/gui/opengl/qopenglbuffer.cpp.html
    //Khronos about shader buffers:
    //https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object

    void bind();
    void unbind();
};

//---------------------------------------------------------------------
//XComputeShader
//Class for maintaining compute shaders
//---------------------------------------------------------------------
class XComputeShader: public XGlCommon {
public:
    explicit XComputeShader(QString shader_file, XGlContext *context);

    //Call this to set up uniforms
    void begin();

    //Access this to set up uniforms
    QOpenGLShaderProgram &program();

    //Perform computing with compute shader.
    //Note 1: it calls glFinish(), so waits until computing will be finished
    //Note 2: please use local groups divisible by 64 to use GPU speedup, and so NX/64, and check NX % 64 == 0
    //        https://stackoverflow.com/questions/62598804/slow-compute-shader-global-vs-local-work-groups
    void compute(int NX, int NY = 1, int NZ = 1);   //NX,NY,NZ - number of groups in X,Y,Z dimensions

    //Call after computing end
    void end();

protected:
    QOpenGLShaderProgram program_;
};

//---------------------------------------------------------------------
//XGlContext
//Surface for maintaining OpenGL context
//Compute shaders and buffers will use it for enabling OpenGL context at operations
//It's subclass of QOffscreenSurface, it's required to have such thing by Qt work with OpenGL
//(Also can use QWindow, but in our case it's not needed, we want non-graphical computations)
//Note: QOffscreenSurface can work in non-main thread,
//but its "create" must be called from main thread
//---------------------------------------------------------------------
class XGlContext: public QOffscreenSurface, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    //Initialize OpenGL context
    explicit XGlContext();
    virtual ~XGlContext();

    //Switch to OpenGL context - required before most operations
    void activate_context();

    void gl_assert(QString message); //Check openGL error
    void xassert(bool condition, QString message); //Check Qt wrapper error

    QOpenGLFunctions_4_3_Core *gl() { return gl43; }
private:
    //OpenGL context
    QOpenGLContext *m_context = nullptr;        //will be deleted automatically
    //OpenGL extra functions
    QOpenGLFunctions_4_3_Core *gl43 = nullptr;  //should't delete this!
};

