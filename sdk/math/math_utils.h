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
float sqrf(float x);
int sqri(int x);

//x*x*x
float pow3f(float x);

//min and max
float minf(float x, float y);
float maxf(float x, float y);
double mind(double x, double y);
double maxd(double x, double y);
int mini(int x, int y);
int maxi(int x, int y);


//Clamp to range [a,b], including a and b
float clampf(float x, float a, float b);
double clampd(double x, double a, double b);
int clampi(int x, int a, int b);

//Linear interpolation from [0,1]
float lerpf(float A, float B, float x); //x = 0..1
double lerpd(double A, double B, double x);

//Linear interpolation
float mapf(float x, float a, float b, float A, float B); //x = a..b
double mapd(double x, double a, double b, double A, double B);
int mapi(int x, int a, int b, int A, int B);

//clamped linear interpolation
float mapf_clamped(float x, float a, float b, float A, float B);
double mapd_clamped(double x, double a, double b, double A, double B);
int mapi_clamped(int x, int a, int b, int A, int B);

//random
int randomi(int a, int b);
float randomf(float a, float b);

//-------------------------------------------------------
