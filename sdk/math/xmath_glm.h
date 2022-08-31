#pragma once

// Glm types and functions

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/glm.hpp>
//vector norm glm::length, glm::length2
#include <glm/gtx/norm.hpp>
//rotation matrix mat4 glm::eulerAngleYXZ(float yaw, float pitch, float roll);
//   and mat3x3 glm::orientate3(vec3 const &angles); - here yaw -> z, pitch -> y, roll -> x
#include <glm/gtx/euler_angles.hpp>

typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
