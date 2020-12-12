#include "xtimemeasure.h"

#include "incl_cpp.h"
#include "xcore.h"

//---------------------------------------------------------------------
XTimeMeasure::XTimeMeasure()
{
    time_ = XCORE.elapsed_time_sec();
}

//---------------------------------------------------------------------
float XTimeMeasure::sec() {
    return XCORE.elapsed_time_sec() - time_;
}

//---------------------------------------------------------------------
int XTimeMeasure::millis() {
    return int((XCORE.elapsed_time_sec() - time_)*1000);
}

//---------------------------------------------------------------------

