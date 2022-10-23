#include "mbed.h"


extern BusOut myleds;
extern AnalogIn analoginLightSensor; //PAO
extern bool pressed;
extern bool powerOn_Off;
void thread_modeNormal(void) {
    
    float numberAnalogin;
    while(1){
        if (pressed == 1 && powerOn_Off == 1){
            numberAnalogin=analoginLightSensor.read();
            if (numberAnalogin < 0.33f){
                myleds.write(3); // red
                printf("lightSensor: %3.3f%% Mode: red\n",numberAnalogin*100);
            }
            else if(0.33 <= numberAnalogin && numberAnalogin < 0.66){
                myleds.write(1); // yellow
                printf("lightSensor: %3.3f%% Mode: yellow\n",numberAnalogin*100);
            }
            else{
                myleds.write(5); //green
                printf("lightSensor: %3.3f%% Mode: green\n",numberAnalogin*100);
            }
            ThisThread::sleep_for(2000);

        }
       

    }
   
            

}