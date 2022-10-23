#include "mbed.h"
#include <cstdint>


class SEN13322{
    private:
    AnalogIn* analoginSoilMoisture;
    Serial* pc;
    
    public:
        SEN13322();
        SEN13322(AnalogIn* _analoginSoilMoisture,Serial* _pc){
            analoginSoilMoisture=_analoginSoilMoisture;
            pc=_pc;
        };
        float readValue(){
            float valueRead;
            valueRead = analoginSoilMoisture->read();
            return valueRead;
        };

        void printValues(){
             pc->printf("Soil Moisture ( %3.3f%%)\n", readValue());
        };
};

