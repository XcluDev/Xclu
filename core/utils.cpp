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
//linear interpolation
float mapf(float x, float a, float b, float A, float B) {
	return (x - a) / (b - a)*(B - A) + A;
}

double mapd(double x, double a, double b, double A, double B) {
	return (x - a) / (b - a)*(B - A) + A;
}

//-------------------------------------------------------
//int to_range(int x, int a, int b) {
//    return qMin(qMax(x, a), b);
//}

//-------------------------------------------------------
