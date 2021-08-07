#include "xtimemeasure.h"

#include "incl_cpp.h"
#include "xc_project.h"

//---------------------------------------------------------------------
XTimeMeasure::XTimeMeasure()
{
    time_ = xc_elapsed_time_sec();
}

//---------------------------------------------------------------------
float XTimeMeasure::sec() {
    return xc_elapsed_time_sec() - time_;
}

//---------------------------------------------------------------------
int XTimeMeasure::millis() {
    return int((xc_elapsed_time_sec() - time_)*1000);
}

//---------------------------------------------------------------------

