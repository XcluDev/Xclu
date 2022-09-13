#pragma once

//Original: "utils" from Qt "Spectrum Example"
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

#include <QtCore/qglobal.h>
#include <QDebug>

#include "sdk_h.h"

QT_FORWARD_DECLARE_CLASS(QAudioFormat)

//-----------------------------------------------------------------------------
// Miscellaneous utility functions aboud audio:
//- QAudioFormat workaround,
//- computing sound envelope
//-----------------------------------------------------------------------------

//--------------------------------------------------
namespace xc_audio {
//--------------------------------------------------

qint64 audio_duration(const QAudioFormat &format, qint64 bytes);
qint64 audio_length(const QAudioFormat &format, qint64 microSeconds);

QString format_to_string(const QAudioFormat &format);

qreal nyquist_frequency(const QAudioFormat &format);

// Scale PCM value to [-1.0, 1.0]
qreal pcm_to_real(qint16 pcm);

// Scale real value in [-1.0, 1.0] to PCM
qint16 real_to_pcm(qreal real);

// Check whether the audio format is PCM
bool is_PCM(const QAudioFormat &format);

// Check whether the audio format is signed, little-endian, 16-bit PCM
bool is_PCMS16LE(const QAudioFormat &format);

// Compile-time calculation of powers of two

template<int N> class PowerOfTwo
{ public: static const int Result = PowerOfTwo<N-1>::Result * 2; };

template<> class PowerOfTwo<0>
{ public: static const int Result = 1; };

//Envelope for 1-channel sound
//set decimate to -1 and size to >0 to obtain envelope of the fixed size
template<typename T>
QVector<T> make_envelope(const QVector<T> &sound, int decimate = 64, int size = -1) {

    if (sound.isEmpty()) {
        return QVector<T>();
    }
    int n = sound.size();
    int m;  //size of the envelope
    if (decimate > 0) {
        m = qMax(n / decimate, 1);
    }
    else {
        xc_assert(size > 0, "xc_audio::envelope - if 'decimate' <= 0, then used 'size', which must be >0");
        m = size;
    }

    QVector<T> env(m, 0);
    for (int i=0; i<n; i++) {
        auto &v = env[i*m/n];
        v = qMax(v, qAbs(sound[i]));
    }
    return env;
}

QVector<float> make_float_envelope(const QVector<int16> &sound, int decimate = 64, int size = -1);


//--------------------------------------------------
} //namespace
//--------------------------------------------------
