#include "types.h"
#include "math_utils.h"

//-------------------------------------------------------
void rect_int::crop(int w0, int h0) {
    int x0 = clampi(x, 0, w0-1);
    int y0 = clampi(y, 0, h0-1);
    int x1 = clampi(x + w, 1, w0);
    int y1 = clampi(y + h, 1, h0);
    *this = rect_int(x0,y0, x1-x0, y1-y0);
};

//-------------------------------------------------------
//convert int -> float points
glm::vec2 to_vec2(const int2 &p) {
	return glm::vec2(p.x, p.y);
}

//-------------------------------------------------------
int2 to_int2_truncate(const glm::vec2 &p) {
	return int2(int(p.x), int(p.y));
}

//-------------------------------------------------------
