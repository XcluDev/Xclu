//Original: "wavfile" from Qt "Spectrum Example"
/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#ifndef XAUDIO_WAVFILE_H
#define XAUDIO_WAVFILE_H


#include <QObject>
#include <QFile>
#include <QAudioFormat>

//--------------------------------------------------
namespace xc_audio {
//--------------------------------------------------
//WavFile class for loading WAV files.
//It's derived from QFile, so can use QFile methods for loading

//Example of usage (see more at XModuleSoundSamplesML):
/*
    xc_audio::WavFile wav;

    //The code of loading WAV is based on the "Spectrum" Qt example
    xc_assert(wav.open(wav_file), "Could not open WAV file '" + wav_file + "'");
    auto &format = wav.fileFormat();

    //We support only 16 bit signed, Little Endian
    xc_assert(xc_audio::isPCMS16LE(format),
              "Audio format '" + xc_audio::formatToString(format) + "' not supported, expected signed int16, Little Endian");

    //Actually we don't need 44100, but just fixed sample rate
    int sample_rate = format.sampleRate();
    xc_assert(sample_rate == geti_join_sample_rate(),
              QString("Bad sample rate in '" + wav_file + "': %1, but expected %2 Hz")
              .arg(sample_rate).arg(geti_join_sample_rate()));

    int channels = format.channelCount();
    xc_assert(channels <= 2, "Only 1 and 2 channels are supported, but '" + wav_file + "' is multi-channel");

    QByteArray bytes = wav.readAll();
    int size = bytes.size() / (2*channels);
    xc_assert(bytes.size() > 0, "Empty WAV file '" + wav_file + "'");

    int16* data = (int16 *)bytes.constData();
    //now use data - packed channel1, channel2, channel1, channel2...

    //Useful functions for int16 <-> real:
    xc_audio::pcmToReal(qint16 pcm);
    xc_audio::realToPcm(qreal real);

*/



class WavFile : public QFile
{
public:
    WavFile(QObject *parent = 0);

    using QFile::open;
    bool open(const QString &fileName);
    const QAudioFormat &fileFormat() const;
    qint64 headerLength() const;

private:
    bool readHeader();

private:
    QAudioFormat m_fileFormat;
    qint64 m_headerLength;
};

//--------------------------------------------------
} //namespace
//--------------------------------------------------


#endif // XAUDIO_WAVFILE_H
