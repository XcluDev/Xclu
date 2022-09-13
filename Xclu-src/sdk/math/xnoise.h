#pragma once

//Simplex noise
//Adaptation of xNoise functions from openFrameworks of_v0.10.1_vs2017_release,
//openframeworks.cc

#include "xmath.h"

/// \brief Calculates a one dimensional Perlin noise value between 0.0...1.0.
float xNoise(float x);

/// \brief Calculates a two dimensional Perlin noise value between 0.0...1.0.
float xNoise(float x, float y);

/// \brief Calculates a two dimensional Perlin noise value between 0.0...1.0.
float xNoise(const vec2& p);

/// \brief Calculates a three dimensional Perlin noise value between 0.0...1.0.
float xNoise(float x, float y, float z);

/// \brief Calculates a three dimensional Perlin noise value between 0.0...1.0.
float xNoise(const vec3& p);

/// \brief Calculates a four dimensional Perlin noise value between 0.0...1.0.
float xNoise(float x, float y, float z, float w);

/// \brief Calculates a four dimensional Perlin noise value between 0.0...1.0.
float xNoise(const vec4& p);

/// \brief Calculates a one dimensional Perlin noise value between -1.0...1.0.
float xSignedNoise(float x);

/// \brief Calculates a two dimensional Perlin noise value between -1.0...1.0.
float xSignedNoise(float x, float y);

/// \brief Calculates a two dimensional Perlin noise value between -1.0...1.0.
float xSignedNoise(const vec2& p);

/// \brief Calculates a three dimensional Perlin noise value between -1.0...1.0.
float xSignedNoise(float x, float y, float z);

/// \brief Calculates a three dimensional Perlin noise value between -1.0...1.0.
float xSignedNoise(const vec3& p);

/// \brief Calculates a four dimensional Perlin noise value between -1.0...1.0.
float xSignedNoise(float x, float y, float z, float w);

/// \brief Calculates a four dimensional Perlin noise value between -1.0...1.0.
float xSignedNoise(const vec4 & p);
