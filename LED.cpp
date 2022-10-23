#include "mbed.h"
#include <cstdint>


class LED{
    private:
    BusOut* myleds;
    Serial* pc;

    
    public:
        LED();
        LED(BusOut* _myleds,Serial* _pc){
            myleds=_myleds;
            pc=_pc;

        };

        
        void writeAndChangeColor(int ledRGB){
            myleds->write(ledRGB);
        };

   
};

