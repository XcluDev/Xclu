#pragma once

//Utility functions and includes

//------ Math --------------------------------------------------
//Pi
const float  PI_F = float(3.14159265358979323846);
const double  PI_D = 3.14159265358979323846;
const float RAD_TO_DEG_F = 180.0f / PI_F;
const double RAD_TO_DEG_D = 180.0 / PI_D;
const float DEG_TO_RAD_F = PI_F / 180.0f;
const double DEG_TO_RAD_D = PI_D / 180.0;
//also can use glm::radians(angle_in_degrees)

//x*x
float xsqrf(float x);
int xsqri(int x);

//x*x*x
float xpow3f(float x);

//min and max
float xminf(float x, float y);
float xmaxf(float x, float y);
double xmind(double x, double y);
double xmaxd(double x, double y);
int xmini(int x, int y);
int xmaxi(int x, int y);


//Clamp to range [a,b], including a and b
float xclampf(float x, float a, float b);
double xclampd(double x, double a, double b);
int clampi(int x, int a, int b);

//Linear interpolation from [0,1]
float xlerpf(float A, float B, float x); //x = 0..1
double xlerpd(double A, double B, double x);

//Linear interpolation
float xmapf(float x, float a, float b, float A, float B); //x = a..b
double xmapd(double x, double a, double b, double A, double B);
int xmapi(int x, int a, int b, int A, int B);

//clamped linear interpolation
float xmapf_clamped(float x, float a, float b, float A, float B);
double xmapd_clamped(double x, double a, double b, double A, double B);
int xmapi_clamped(int x, int a, int b, int A, int B);

//random
int xrandomi(int a, int b);
float xrandomf(float a, float b);

//-------------------------------------------------------
