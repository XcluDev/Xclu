#pragma once

//Classes for checking that value was changed
#include "xtypes.h"

//Type for storing frame number. I use uint32 instead uint16 just to be absolutely sure it's enough
typedef uint32 XWasChangedFrame;

//Class which used for check if the original value was changed
class XWasChangedChecker
{
public:
    void set_frame(XWasChangedFrame frame, XWasChangedFrame frame_level2=0) { _checker_frame_ = frame; _checker_frame2_ = frame_level2; }
    void reset() { set_frame(0, 0); }

    XWasChangedFrame checker_frame() const { return _checker_frame_; }
    XWasChangedFrame checker_frame2() const { return _checker_frame2_; }
protected:
    XWasChangedFrame _checker_frame_ = 0;   //frame which increases when value was changed
    XWasChangedFrame _checker_frame2_ = 0;   //level 2 of changes
};

//Class which is stores each moment when variable was changed
class XWasChangedKeeper
{
public:
    void was_updated() { touch(); }        // почетить, что было изменение
    void touch() { _keeper_frame_++; }    //call to mark that value was changed
    //functions for tracking second-level changes
    void touch2() { _keeper_frame2_++; }    //call to mark that value was changed
    void copy_from_level1(const XWasChangedKeeper &keeper) {
        _keeper_frame_ = keeper._keeper_frame_;
    }

    //checking changes
    bool was_changed(XWasChangedChecker &checker) const {
        if ((checker.checker_frame() != _keeper_frame_)
                || (checker.checker_frame2() != _keeper_frame2_)
                ) {
            checker.set_frame(_keeper_frame_, _keeper_frame2_);
            return true;
        }
        return false;
    }

protected:
    //frame which increases when value was changed
    //Note: we set it to 1, to have all checkers update for the very first time
    XWasChangedFrame _keeper_frame_ = 1;
    XWasChangedFrame _keeper_frame2_ = 1;   //level 2 of changes
};

