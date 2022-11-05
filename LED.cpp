#include "LED.h"


LED::LED(BusOut* _myleds):myleds(_myleds){};
LED::~LED(){};
void LED::writeAndChangeColor(int ledRGB){
    myleds->write(ledRGB);
};

   

