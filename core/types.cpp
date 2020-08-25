#include "types.h"

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
