#include "SEN13322.h"



SEN13322::~SEN13322(){};
SEN13322::SEN13322(AnalogIn* _analoginSoilMoisture):analoginSoilMoisture(_analoginSoilMoisture){};
float SEN13322::readValue(){
    float valueRead;
    valueRead = analoginSoilMoisture->read();
    return valueRead*100;
};


