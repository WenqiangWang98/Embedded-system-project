#ifndef HWSP1_H
#define HWSP1_H

#include "mbed.h"



class HWSP1{
    private:
    AnalogIn* analoginLightSensor;

    
    public:
       
        ~HWSP1();
        HWSP1(AnalogIn* _analoginLightSensor);
        float readValue();

};

#endif