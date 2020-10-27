#include "math_utils.h"
#include <random>
#include <QRandomGenerator>

//-------------------------------------------------------
//x*x
float sqrf(float x) {
	return x * x;
}

int sqri(int x) {
	return x * x; 
}


//-------------------------------------------------------
//x*x*x
float pow3f(float x) {
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
//Linear interpolation from [0,1]
float lerpf(float A, float B, float x) { //x = 0..1
    return A*(1-x) + B*x;
}

float lerpd(float A, float B, float x) {
    return A*(1-x) + B*x;
}

//-------------------------------------------------------
//Linear interpolation
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
//https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
//std::random_device randomi_rd_;  //Will be used to obtain a seed for the random number engine

//https://doc.qt.io/qt-5/qrandomgenerator.html#details
int randomi(int a, int b) {
    std::uniform_real_distribution<> dist(a, b);
    return dist(*QRandomGenerator::global());

    //std::mt19937 gen(randomi_rd_()); //Standard mersenne_twister_engine seeded with rd()
    //std::uniform_int_distribution<> distrib(a, b);
    //return distrib(gen);
}

//-------------------------------------------------------
float randomf(float a, float b) {
    std::uniform_real_distribution<> dist(a, b);
    return dist(*QRandomGenerator::global());
}

//-------------------------------------------------------
