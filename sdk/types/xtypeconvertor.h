#pragma once

// В этом модуле определяется функция cpptype_to_XType
// Она используется другими классами, работающими с XType,
// поэтому мы не могли определить ее в xtype.h

#include "xbasictypes.h"
#include "xtype.h"

/// Template function converting C++ type to XType
/// Примеры применения:
/// template<class T> void XRaster::copy_from(T* input_img, int w, int h) {
///     copy_from(input_img, w, h, cpptype_to_XType<T>());
/// }
/// template<class T> ... { assert_type(cpptype_to_XType()); ...}
template<class T> XType cpptype_to_XType();



