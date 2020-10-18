#pragma once

//Basic includes and types

#include <string>
#include<iostream>
#include <algorithm>

//Geometry
#include "int2.h"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>


typedef unsigned char uint8;
typedef char sint8;
typedef short int16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int int32;

const int max_u16 = 65535;
const int u16_n = 65536;
typedef unsigned long long int uint64;

//rectangle
struct rect_int {
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
    rect_int() {}
	rect_int(int x0, int y0, int w0, int h0) : x(x0),y(y0),w(w0),h(h0) {}
	rect_int(int2 pos, int2 size) : x(pos.x), y(pos.y), w(size.x), h(size.y) {}
    bool is_inside(int w0, int h0) {
        return (x >= 0 && y >= 0 && w >= 0 && h >= 0 && x + w <= w0 && y + h <= h0);
    }
    void crop(int w0, int h0);
};

//convert int <-> float points
glm::vec2 to_vec2(const int2 &p);
int2 to_int2_truncate(const glm::vec2 &p);

