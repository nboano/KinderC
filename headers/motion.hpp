#pragma once
#include "../kinderc.hpp"

struct MotionAccelerationData {

    double x;

    double y;

    double z;

};

struct MotionData {

    MotionAccelerationData Acceleration;
};

class Motion {
    public:

    static void Watch(void(*sh)(MotionData&));

    static void Stop();
};