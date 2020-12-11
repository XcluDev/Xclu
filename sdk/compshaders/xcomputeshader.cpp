#include "xcomputeshader.h"

#include <QtCore/QCoreApplication>

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include <QOpenGLExtraFunctions>
#include <QDebug>

#include "incl_cpp.h"

//---------------------------------------------------------------------
//XComputeCommon
//---------------------------------------------------------------------
void XComputeCommon::setup_surface(XComputeSurface *surface) {
    surface_ = surface;
    activate_context();
}

//---------------------------------------------------------------------
void XComputeCommon::gl_assert(QString message) { //Check openGL error
    if (surface_) surface_->gl_assert(message);
}

//---------------------------------------------------------------------
void XComputeCommon::xassert(bool condition, QString message) { //Check Qt wrapper error
    if (surface_) surface_->xassert(condition, message);
}

//---------------------------------------------------------------------
void XComputeCommon::activate_context() {
    if (surface_) surface_->activate_context();
}

//---------------------------------------------------------------------
QOpenGLFunctions_4_3_Core *XComputeCommon::gl() {
    return surface_->gl();
}

//---------------------------------------------------------------------
//XComputeBuffer
//---------------------------------------------------------------------
XComputeBuffer::XComputeBuffer(XComputeSurface *surface) {
    setup_surface(surface);

    activate_context();
    xassert(shader_buffer_.create(), "Error at shader_buffer_.create()");
    xassert(shader_buffer_.bind(), "Error at shader_buffer_.bind()");
    shader_buffer_.setUsagePattern(QOpenGLBuffer::DynamicCopy);
}

//---------------------------------------------------------------------
 //Put data to GPU
void XComputeBuffer::allocate(void *data, int size_bytes) {
    activate_context();
    shader_buffer_.allocate(data, size_bytes);
}

//---------------------------------------------------------------------
void XComputeBuffer::clear() {
    activate_context();
    shader_buffer_.destroy();
}

//---------------------------------------------------------------------
//Copy data to CPU
void XComputeBuffer::read_to_cpu(void *data, int size_bytes) {
    activate_context();
    //Read buffer
    memcpy(data, shader_buffer_.map(QOpenGLBuffer::ReadWrite), size_bytes);

}

//---------------------------------------------------------------------
//Bind buffer to shader by specifying its binding index:
//Shader:
//    layout(std430, binding = 0) buffer Buf
//    { float buf[]; };
void XComputeBuffer::bind_for_shader(int binding_index) {
    surface_->gl()->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding_index, shader_buffer_.bufferId());
    gl_assert("Error at glBindBufferBase");
}

//---------------------------------------------------------------------
//Unbind - not tested
void XComputeBuffer::unbind() {
    shader_buffer_.release();
}

//---------------------------------------------------------------------
//XComputeShader
//---------------------------------------------------------------------
//Initialize OpenGL context and load shader, must be called before computing
XComputeShader::XComputeShader(QString shader_file, XComputeSurface *surface) {
    setup_surface(surface);

    //Not sure if it's required for loading shader...
    activate_context();
    //Load compute shader
    xassert(program_.addShaderFromSourceFile(QOpenGLShader::Compute, shader_file),
            "Can't load shader file " + shader_file);

    //compute_shader->addShaderFromSourceCode(QOpenGLShader::Compute, text);
    xassert(program_.link(), "Can't link compute shader");
}

//---------------------------------------------------------------------
//Call this to set up uniforms
void XComputeShader::begin() {
    activate_context();
    xassert(program_.bind(), "Can't bind compute shader");
}

//---------------------------------------------------------------------
//Access this to set up uniforms
QOpenGLShaderProgram &XComputeShader::program() {
    return program_;
}

//---------------------------------------------------------------------
//Call this to perform computing
//Based on https://forum.qt.io/topic/104448/about-buffer-for-compute-shader/6
void XComputeShader::compute(int NX, int NY, int NZ) {
    gl()->glDispatchCompute(NX, NY, NZ);		//Run computation
    gl_assert("glDispatchCompute error");
    gl()->glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);	//Wait finish computation
    gl_assert("glMemoryBarrier error");
}

//---------------------------------------------------------------------
//Call after computing end
void XComputeShader::end() {
    program_.release();
}

//---------------------------------------------------------------------
//XComputeSurface
//---------------------------------------------------------------------
//Note: QOffscreenSurface can work in non-main thread,
//but its "create" must be called from main thread

//Initialize OpenGL context
XComputeSurface::XComputeSurface()
    : QOffscreenSurface()
    , m_context(0)
{
    QSurfaceFormat format;
    //Request OpenGL 4.3
    format.setMajorVersion(4);
    format.setMinorVersion(3);

    //format.setSamples(16); //antialiasing samples
    //format.setProfile(QSurfaceFormat::CoreProfile);
    //format.setOption(QSurfaceFormat::DebugContext);
    setFormat(format);

    //Create Qt surface
    create();

    //Create OpenGL context
    m_context = new QOpenGLContext(this);
    m_context->setFormat(requestedFormat());  //it's our "format"
    m_context->create();

    //Switch to OpenGL context
    activate_context();

    //Initialize OpenGL functions
    initializeOpenGLFunctions();

    //Get pointer to extra functions of 4.3
    gl43 = m_context->versionFunctions<QOpenGLFunctions_4_3_Core>();
    gl_assert("Error creating gl43");

}
//---------------------------------------------------------------------
XComputeSurface::~XComputeSurface()
{

}

//---------------------------------------------------------------------
//Check openGL error
void XComputeSurface::gl_assert(QString message) {

    GLenum error = gl43->glGetError();
    if (error != GL_NO_ERROR) {
        QStringList errors;
        //read all error codes
        do {
            errors.push_back(QString::number(error));
            error = gl43->glGetError();
        } while (error != GL_NO_ERROR);
        xclu_exception("XComputeSurface " + message + ", OpenGL error code(s): " + errors.join(","));
    }

}

//---------------------------------------------------------------------
//Check Qt wrapper error
void XComputeSurface::xassert(bool condition, QString message) {
    xclu_assert(condition, "XComputeSurface + " + message);
}

//---------------------------------------------------------------------
//Switch to OpenGL context - required before most operations
void XComputeSurface::activate_context() {
    xassert(m_context, "OpenGL context is not inited");
    if (!m_context) return;
    m_context->makeCurrent(this);
}

//---------------------------------------------------------------------

