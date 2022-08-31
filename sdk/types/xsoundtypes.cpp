#include "xsoundtypes.h"

//---------------------------------------------------------------------
XSoundFormat::XSoundFormat() {}
XSoundFormat::XSoundFormat(int sample_rate, int channels) {
    setup(sample_rate, channels);
}

void XSoundFormat::setup(int sample_rate, int channels) {
    this->sample_rate = sample_rate;
    this->channels = channels;
}

//---------------------------------------------------------------------
XSoundBuffer::XSoundBuffer() {

}
XSoundBuffer::XSoundBuffer(const XSoundFormat &format, int samples) {
    allocate(format, samples);
}

void XSoundBuffer::allocate(const XSoundFormat &format, int samples) {
    this->format = format;
    this->samples = samples;
    buffer.allocate<float32>(samples*format.channels);

}
//---------------------------------------------------------------------

