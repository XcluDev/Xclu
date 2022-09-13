#pragma once

//XSlowbit - slowly switched bit, from ofxKu.
//It holds float _value = 0..1, which gradually between from 0 to 1.

#include "incl_h.h"


struct XSlowbit {
    //time00: time for 0->0
    //time01: time for 0->1
    //time10: time for 1->0
    //time11: time for 1->1
    void setup( float time00, float time01, float time10, float time11);
    void update( float dt, int target ); //target - state to go
    void update_times(float time00, float time01, float time10, float time11);
    void update_times(float fade_in_sec, float fade_out_sec);
    void update_times(float fade_sec);

    int state();       //current state
    float stateFloat() { return _value; }   //current state as float
    bool became0();     //state became 0
    bool became1();     //state became 1
    bool changed();     //state was changes

    void reset0();
    void reset( int value );
    
private:
	//transition speeds
    float speed00 = 1;
    float speed01 = 1;
    float speed10 = 1;
    float speed11 = 1;

    int _state = 0;
    int _lastState = 0;
    float _value = 0;

};


