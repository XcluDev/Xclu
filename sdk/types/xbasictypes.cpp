#include "xbasictypes.h"
#include "xmath.h"

//-------------------------------------------------------
//convert int -> float points
vec2 to_vec2(const int2 &p) {
    return vec2(p.x, p.y);
}

//-------------------------------------------------------
int2 to_int2_truncate(const vec2 &p) {
    return int2(int(p.x), int(p.y));
}

//-------------------------------------------------------
void rect_int::crop(int w0, int h0) {
    int x0 = xclampi(x, 0, w0-1);
    int y0 = xclampi(y, 0, h0-1);
    int x1 = xclampi(x + w, 1, w0);
    int y1 = xclampi(y + h, 1, h0);
    *this = rect_int(x0,y0, x1-x0, y1-y0);
};

//---------------------------------------------------------------------
template<typename T>
rgb_<T> rgb_<T>::operator+(const rgb_<T>& vec) const {
    return rgb_<T>(v[0] + vec.v[0], v[1] + vec.v[1], v[2] + vec.v[2]);
}

template<typename T>
rgb_<T>& rgb_<T>::operator+=(const rgb_<T>& vec) {
    v[0] += vec.v[0];
    v[1] += vec.v[1];
    v[2] += vec.v[2];
    return *this;
}

template<typename T>
rgb_<T> rgb_<T>::operator-(const rgb_<T>& vec) const {
    return rgb_<T>(v[0] - vec.v[0], v[1] - vec.v[1], v[2] - vec.v[2]);
}

template<typename T>
rgb_<T>& rgb_<T>::operator-=(const rgb_<T>& vec) {
    v[0] -= vec.v[0];
    v[1] -= vec.v[1];
    v[2] -= vec.v[2];
    return *this;
}

template<typename T>
rgb_<T> rgb_<T>::operator*(const rgb_<T>& vec) const {
    return rgb_<T>(v[0] * vec.v[0], v[1] * vec.v[1], v[2] * vec.v[2]);
}

template<typename T>
rgb_<T>& rgb_<T>::operator*=(const rgb_<T>& vec) {
    v[0] *= vec.v[0];
    v[1] *= vec.v[1];
    v[2] *= vec.v[2];
    return *this;
}

//---------------------------------------------------------------------
template<typename T>
rgba_<T> rgba_<T>::operator+(const rgba_<T>& vec) const {
    return rgba_<T>(v[0] + vec.v[0], v[1] + vec.v[1], v[2] + vec.v[2], v[3] + vec.v[3]);
}

template<typename T>
rgba_<T>& rgba_<T>::operator+=(const rgba_<T>& vec) {
    v[0] += vec.v[0];
    v[1] += vec.v[1];
    v[2] += vec.v[2];
    v[3] += vec.v[3];
    return *this;
}

template<typename T>
rgba_<T> rgba_<T>::operator-(const rgba_<T>& vec) const {
    return rgba_<T>(v[0] - vec.v[0], v[1] - vec.v[1], v[2] - vec.v[2], v[3] - vec.v[3]);
}

template<typename T>
rgba_<T>& rgba_<T>::operator-=(const rgba_<T>& vec) {
    v[0] -= vec.v[0];
    v[1] -= vec.v[1];
    v[2] -= vec.v[2];
    v[3] -= vec.v[3];
    return *this;
}

template<typename T>
rgba_<T> rgba_<T>::operator*(const rgba_<T>& vec) const {
    return rgba_<T>(v[0] * vec.v[0], v[1] * vec.v[1], v[2] * vec.v[2], v[3] * vec.v[3]);
}

template<typename T>
rgba_<T>& rgba_<T>::operator*=(const rgba_<T>& vec) {
    v[0] *= vec.v[0];
    v[1] *= vec.v[1];
    v[2] *= vec.v[2];
    v[3] *= vec.v[3];
    return *this;
}

//---------------------------------------------------------------------
