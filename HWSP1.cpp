#include "HWSP1.h"

HWSP1::HWSP1(AnalogIn* _analoginLightSensor):analoginLightSensor(_analoginLightSensor){};
HWSP1::~HWSP1(){};

float HWSP1::readValue(){
    float valueRead;
    valueRead = analoginLightSensor->read();
    return valueRead*100;
};



