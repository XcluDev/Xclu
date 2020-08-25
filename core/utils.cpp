#include "utils.h"

//-------------------------------------------------------
//x*x
float sqr(float x) {
	return x * x;
}

int sqri(int x) {
	return x * x; 
}


//-------------------------------------------------------
//x*x*x
float pow3(float x) {
	return x * x*x;
}

//-------------------------------------------------------
//min and max
float minf(float x, float y) {
    return (x < y) ? x : y;
}

float maxf(float x, float y) {
    return (x > y) ? x : y;
}

double mind(double x, double y) {
    return (x < y) ? x : y;
}

double maxd(double x, double y) {
    return (x > y) ? x : y;
}

int mini(int x, int y) {
    return (x < y) ? x : y;
}

int maxi(int x, int y) {
    return (x > y) ? x : y;
}

//-------------------------------------------------------
//clamp to range [a,b], including a and b
float clampf(float x, float a, float b) {
    if (b<a) std::swap(a,b);
    return ((x<a)?a : ((x>b)?b:x));
}
double clampd(double x, double a, double b) {
    if (b<a) std::swap(a,b);
    return ((x<a)?a : ((x>b)?b:x));
}
int clampi(int x, int a, int b) {
    if (b<a) std::swap(a,b);
    return ((x<a)?a : ((x>b)?b:x));
}

//-------------------------------------------------------
//linear interpolation
float mapf(float x, float a, float b, float A, float B) {
    return (x - a) / (b - a) * (B - A) + A;
}

double mapd(double x, double a, double b, double A, double B) {
    return (x - a) / (b - a) * (B - A) + A;
}

int mapi(int x, int a, int b, int A, int B) {
    //Need to use "long long..." to avoid overflow.
    //And so we obtain perfect int result of map !
    return ((long long int)(B-A)) * (x - a) / (b - a) + A;
}

//-------------------------------------------------------
//clamped linear interpolation
float mapf_clamped(float x, float a, float b, float A, float B) {
    return clampf(mapf(x,a,b,A,B),A,B);
}

double mapd_clamped(double x, double a, double b, double A, double B) {
    return clampd(mapd(x,a,b,A,B),A,B);
}

int mapi_clamped(int x, int a, int b, int A, int B) {
    return clampi(mapi(x,a,b,A,B),A,B);
}

//-------------------------------------------------------
