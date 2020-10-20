#ifndef XWASCHANGED_H
#define XWASCHANGED_H

//Classes for checking that value was changed
#include "types.h"

//Type for storing frame number. I use u32 instead u16 just to be absolutely sure it's enough
typedef u32 XWasChangedFrame;

//Class which used for check if the original value was changed
class XWasChangedChecker
{
public:
    void set_frame(XWasChangedFrame frame) { _checker_frame_ = frame; }
    void reset() { set_frame(0); }

    XWasChangedFrame checker_frame() const { return _checker_frame_; }
protected:
    XWasChangedFrame _checker_frame_ = 0;   //frame which increases when value was changed
};

//Class which is stores each moment when variable was changed
class XWasChangedKeeper
{
public:
    void touch() { _keeper_frame_++; }    //call to mark that value was changed
    bool was_changed(XWasChangedChecker &checker) const {
        if (checker.checker_frame() != _keeper_frame_) {
            checker.set_frame(_keeper_frame_);
            return true;
        }
        return false;
    }
    //XWasChangedFrame keeper_frame() const { return _keeper_frame_; }
protected:
    //frame which increases when value was changed
    //Note: we set it to 1, to have all checkers update for the very first time
    XWasChangedFrame _keeper_frame_ = 1;
};



#endif // XWASCHANGED_H
