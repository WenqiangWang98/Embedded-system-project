#ifndef SEN13322_H
#define SEN13322_H
 
#include "mbed.h"


class SEN13322{
    private:
    AnalogIn* analoginSoilMoisture;
    
    public:
        SEN13322(AnalogIn* _analoginSoilMoisture);
        ~SEN13322();
        float readValue();
};
#endif
