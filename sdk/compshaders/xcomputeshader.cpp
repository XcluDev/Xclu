#include "xcomputeshader.h"

#include <QtGui/QOpenGLContext>
#include <QOpenGLExtraFunctions>
#include <QDebug>

#include "incl_cpp.h"

//---------------------------------------------------------------------
//XGlCommon
//---------------------------------------------------------------------
void XGlCommon::setup(XGlContext *context) {
    context_ = context;
    activate_context();
}

//---------------------------------------------------------------------
void XGlCommon::gl_assert(QString message) { //Check openGL error
    if (context_) context_->gl_assert(message);
}

//---------------------------------------------------------------------
void XGlCommon::xassert(bool condition, QString message) { //Check Qt wrapper error
    if (context_) context_->xassert(condition, message);
}

//---------------------------------------------------------------------
void XGlCommon::activate_context() {
    if (context_) context_->activate_context();
}

//---------------------------------------------------------------------
QOpenGLFunctions_4_3_Core *XGlCommon::gl() {
    return context_->gl();
}

//---------------------------------------------------------------------
//XShaderBuffer
//---------------------------------------------------------------------
XShaderBuffer::XShaderBuffer(XGlContext *context) {
    setup(context);

    activate_context();
    xassert(shader_buffer_.create(), "Error at shader_buffer_.create()");

    shader_buffer_.setUsagePattern(QOpenGLBuffer::DynamicDraw); //DynamicCopy);
}

//---------------------------------------------------------------------
void XShaderBuffer::bind() {
    xassert(shader_buffer_.bind(), "Error at shader_buffer_.bind()");
}

//---------------------------------------------------------------------
void XShaderBuffer::unbind() {
    shader_buffer_.release();
}

//---------------------------------------------------------------------
 //Put data to GPU
void XShaderBuffer::allocate(void *data, int size_bytes) {
    activate_context();
    //we must always bind/unbind buffer for the most operations - it's not made by Qt!
    bind();
    shader_buffer_.allocate(data, size_bytes);
    unbind();
}

//---------------------------------------------------------------------
void XShaderBuffer::allocate(int size_bytes) {
    activate_context();
    shader_buffer_.allocate(size_bytes);
}

//---------------------------------------------------------------------
void XShaderBuffer::clear() {
    activate_context();
    shader_buffer_.destroy();
}

//---------------------------------------------------------------------
//Copy data to CPU
void XShaderBuffer::read_to_cpu(void *data, int size_bytes) {
    xc_assert(data, "XShaderBuffer::read_to_cpu - bad input pointer");

    activate_context();

    bind();
    xc_assert(shader_buffer_.read(0, data, size_bytes), "XShaderBuffer::read_to_cpu - error reading buffer");

    //void *ptr = shader_buffer_.map(QOpenGLBuffer::ReadOnly);
    //xc_assert(ptr, "XShaderBuffer::read_to_cpu - can't map to CPU");
    //memcpy(data, ptr, size_bytes);
    //xc_assert(shader_buffer_.unmap(), "XShaderBuffer::read_to_cpu - can't unmap");

    unbind();
}

//---------------------------------------------------------------------
//Bind buffer to shader by specifying its binding index:
//Shader:
//    layout(std430, binding = 0) buffer Buf
//    { float buf[]; };
void XShaderBuffer::bind_for_shader(int binding_index) {
    activate_context();
    context_->gl()->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding_index, shader_buffer_.bufferId());
    gl_assert("Error at glBindBufferBase");
}

//---------------------------------------------------------------------
//XComputeShader
//---------------------------------------------------------------------
//Initialize OpenGL context and load shader, must be called before computing
XComputeShader::XComputeShader(QString shader_file, XGlContext *context) {
    setup(context);

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
//Perform computing with compute shader.
//Note: it calls glFinish(), so waits until computing will be finished
void XComputeShader::compute(int NX, int NY, int NZ) {
    gl()->glDispatchCompute(NX, NY, NZ);		//Run computation
    gl_assert("glDispatchCompute error");

    //gl()->glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    //gl_assert("glMemoryBarrier error");

    //Wait to complete the computing
    gl()->glFinish();
}

//---------------------------------------------------------------------
//Call after computing end
void XComputeShader::end() {
    program_.release();
}

//---------------------------------------------------------------------
//XGlContext
//---------------------------------------------------------------------
//Note: QOffscreenSurface can work in non-main thread,
//but its "create" must be called from main thread

//Initialize OpenGL context
XGlContext::XGlContext()
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
    m_context->setFormat(format); //requestedFormat());
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
XGlContext::~XGlContext()
{

}

//---------------------------------------------------------------------
//Check openGL error
void XGlContext::gl_assert(QString message) {

    GLenum error = gl43->glGetError();
    if (error != GL_NO_ERROR) {
        QStringList errors;
        //read all error codes
        do {
            errors.push_back(QString::number(error));
            error = gl43->glGetError();
        } while (error != GL_NO_ERROR);
        xc_exception("XGlContext " + message + ", OpenGL error code(s): " + errors.join(","));
    }

}

//---------------------------------------------------------------------
//Check Qt wrapper error
void XGlContext::xassert(bool condition, QString message) {
    xc_assert(condition, "XGlContext + " + message);
}

//---------------------------------------------------------------------
//Switch to OpenGL context - required before most operations
void XGlContext::activate_context() {
    xassert(m_context, "OpenGL context is not inited");
    if (!m_context) return;
    m_context->makeCurrent(this);
}

//---------------------------------------------------------------------

