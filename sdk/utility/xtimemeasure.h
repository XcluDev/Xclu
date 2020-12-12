#ifndef XTIMEMEASURE_H
#define XTIMEMEASURE_H

//Utility class for measuring time.
//Constructor stores current time, and then you can call elapsed()

class XTimeMeasure {
public:
    //Constructor stores time of creation, so it's starting point
    XTimeMeasure();

    //Elapsed seconds
    float sec();

    //Elapsed milliseconds
    int millis();
protected:
    double time_ = 0;
};

#endif // XTIMEMEASURE_H
