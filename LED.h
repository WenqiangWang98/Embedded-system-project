#ifndef LED_H
#define LED_H

#include "mbed.h"



class LED{
    private:
    BusOut* myleds;

    
    public:
        ~LED();
        LED(BusOut* _myleds);

        void writeAndChangeColor(int ledRGB);

   
};

#endif