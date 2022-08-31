#include "xsoundtypes.h"

//---------------------------------------------------------------------
XSoundFormat::XSoundFormat() {}
XSoundFormat::XSoundFormat(int sample_rate0, int channels0) {
    sample_rate = sample_rate0;
    channels = channels0;
}

//---------------------------------------------------------------------
XSoundBuffer::XSoundBuffer() {

}
XSoundBuffer::XSoundBuffer(const XSoundFormat &format0, int samples0) {
    allocate(format0, samples0);
}

void XSoundBuffer::allocate(const XSoundFormat &format0, int samples0) {
    format = format0;
    samples = samples0;
    buffer.allocate<float32>(samples*format.channels);

}
//---------------------------------------------------------------------

