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

void XSoundFormat::clear() {
    *this = XSoundFormat();
}

//---------------------------------------------------------------------
XSoundBuffer::XSoundBuffer() {

}
XSoundBuffer::XSoundBuffer(const XSoundFormat &format, int samples) {
    allocate(format, samples);
}

void XSoundBuffer::allocate(const XSoundFormat &format, int samples, bool set_zero) {
    this->format = format;
    this->samples = samples;
    buffer.resize(samples * format.channels);
    if (set_zero) {
        buffer.fill(0);
    }
}

void XSoundBuffer::clear() {
    *this = XSoundBuffer();
}

//---------------------------------------------------------------------

