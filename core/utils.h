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

//min and max
float minf(float x, float y);
float maxf(float x, float y);
double mind(double x, double y);
double maxd(double x, double y);
int mini(int x, int y);
int maxi(int x, int y);


//clamp to range [a,b], including a and b
float clampf(float x, float a, float b);
double clampd(double x, double a, double b);
int clampi(int x, int a, int b);

//linear interpolation
float mapf(float x, float a, float b, float A, float B);
double mapd(double x, double a, double b, double A, double B);
int mapi(int x, int a, int b, int A, int B);

//clamped linear interpolation
float mapf_clamped(float x, float a, float b, float A, float B);
double mapd_clamped(double x, double a, double b, double A, double B);
int mapi_clamped(int x, int a, int b, int A, int B);


//-------------------------------------------------------
