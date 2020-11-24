#include "xnoise.h"

//Simplex noise
//Adaptation of xNoise functions from openFrameworks of_v0.10.1_vs2017_release,
//openframeworks.cc

#include "ofNoise.h"

//--------------------------------------------------
float xNoise(float x){
    return _slang_library_noise1(x)*0.5f + 0.5f;
}

//--------------------------------------------------
float xNoise(float x, float y){
    return _slang_library_noise2(x,y)*0.5f + 0.5f;
}

//--------------------------------------------------
float xNoise(const glm::vec2& p){
    return xNoise( p.x, p.y );
}

//--------------------------------------------------
float xNoise(float x, float y, float z){
    return _slang_library_noise3(x,y,z)*0.5f + 0.5f;
}

//--------------------------------------------------
float xNoise(const glm::vec3& p){
    return xNoise( p.x, p.y, p.z );
}

//--------------------------------------------------
float xNoise(float x, float y, float z, float w){
    return _slang_library_noise4(x,y,z,w)*0.5f + 0.5f;
}

//--------------------------------------------------
float xNoise(const glm::vec4& p){
    return xNoise( p.x, p.y, p.z, p.w );
}

//--------------------------------------------------
float xSignedNoise(float x){
    return _slang_library_noise1(x);
}

//--------------------------------------------------
float xSignedNoise(float x, float y){
    return _slang_library_noise2(x,y);
}

//--------------------------------------------------
float xSignedNoise(const glm::vec2& p){
    return xSignedNoise( p.x, p.y );
}

//--------------------------------------------------
float xSignedNoise(float x, float y, float z){
    return _slang_library_noise3(x,y,z);
}

//--------------------------------------------------
float xSignedNoise(const glm::vec3& p){
    return xSignedNoise( p.x, p.y, p.z );
}

//--------------------------------------------------
float xSignedNoise(float x, float y, float z, float w){
    return _slang_library_noise4(x,y,z,w);
}

//--------------------------------------------------
float xSignedNoise(const glm::vec4& p){
    return xSignedNoise( p.x, p.y, p.z, p.w );
}


//---------------------------------------------------------------------
