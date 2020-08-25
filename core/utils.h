#pragma once

//Utility functions and includes
#include "types.h"

//------ Math --------------------------------------------------
//Pi
const float  PI_F = float(3.14159265358979323846);
const double  PI_D = 3.14159265358979323846;
const double RAD_TO_DEG_D = 180.0 / PI_D;
const double DEG_TO_RAD_D = PI_D / 180.0;

//x*x
float sqr(float x);
int sqri(int x);

//x*x*x
float pow3(float x);

//linear interpolation
float mapf(float x, float a, float b, float A, float B);
double mapd(double x, double a, double b, double A, double B);
int to_range(int x, int a, int b);

//-------------------------------------------------------
