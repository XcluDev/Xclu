#include "slowbit.h"

//--------------------------------------------------------------
void SlowBit::setup(float time00, float time01, float time10, float time11) {
    
	update_times(time00, time01, time10, time11);
    _state = 0;
    _lastState = _state;
    _value = _state;
}

//--------------------------------------------------------------
void SlowBit::update_times( float time00, float time01, float time10, float time11 ) {
    time00 = qMax(time00, 0.000001f);
    time01 = qMax(time01, 0.000001f);
    time10 = qMax(time10, 0.000001f);
    time11 = qMax(time11, 0.000001f);
    speed00 = 1.0 / time00;
    speed01 = 1.0 / time01;
    speed10 = 1.0 / time10;
    speed11 = 1.0 / time11;
}

//--------------------------------------------------------------
void SlowBit::update_times(float fade_in_sec, float fade_out_sec) {
    update_times(fade_out_sec, fade_in_sec, fade_out_sec, fade_in_sec);
}

//--------------------------------------------------------------
void SlowBit::update_times(float fade_sec) {
    update_times(fade_sec, fade_sec);
}

//--------------------------------------------------------------
void SlowBit::reset0()
{
    reset( 0 );
}

//--------------------------------------------------------------
void SlowBit::reset( int value )
{
    _state = value;
    _lastState = _state;
    _value = _state;
}

//--------------------------------------------------------------
void SlowBit::update( float dt, int target )
{
    _lastState = _state;
    
    float d = 0;
    if ( _state == 0 ) {
        if ( target == 0 ) { d = -speed00; }
        else { d = speed01; }
    }
    else {
        if ( target == 0 ) { d = -speed10; }
        else { d = speed11; }
    }
    
    _value += d * dt;
    if ( _value >= 1 ) { _state = 1; }
    if ( _value <= 0 ) { _state = 0; }
    
    _value = clampf(_value, 0, 1 );
}

//--------------------------------------------------------------
int SlowBit::state()
{
    return _state;
}

//--------------------------------------------------------------
bool SlowBit::became0()     //изменился в 0
{
    return ( changed() && _state == 0 );
}

//--------------------------------------------------------------
bool SlowBit::became1()     //изменился в 1
{
    return ( changed() && _state == 1 );
}

//--------------------------------------------------------------
bool SlowBit::changed()     //изменился (сравнивать с предыдущим состоянием)
{
    return ( _state != _lastState );
}

//--------------------------------------------------------------
