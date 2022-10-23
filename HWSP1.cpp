#include "mbed.h"
#include <cstdint>


class HWSP1{
    private:
    AnalogIn* analoginLightSensor;
    Serial* pc;
    
    public:
        HWSP1();
        HWSP1(AnalogIn* _analoginLightSensor,Serial* _pc){
            analoginLightSensor=_analoginLightSensor;
            pc=_pc;
        };
        float readValue(){
            float valueRead;
            valueRead = analoginLightSensor->read();
            return valueRead;
        };

        void printValues(){
             pc->printf("LightSensor ( %3.3f%%)\n", readValue());
        };
};

