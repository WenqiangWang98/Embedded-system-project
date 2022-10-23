/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <cstdint>


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms


int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);
    AnalogIn analoginLightSensor(PA_0); //PAO
    DigitalOut led1(D0);
    DigitalOut led2(D1);
    DigitalOut led3(D2);
    float numberAnalogin;
    while (true) {
        // led = !led;
        // ThisThread::sleep_for(BLINKING_RATE);

        //lightSensor
        // numberAnalogin=analoginLightSensor.read();
        // printf("lightSensor: %f \n",numberAnalogin);
        // ThisThread::sleep_for(BLINKING_RATE);
        
        //LED
        
        led2.write(0);
        led3.write(0);
        led1.write(1);
        ThisThread::sleep_for(BLINKING_RATE);


        led1.write(0);
        led3.write(0);
        led2.write(1);

        ThisThread::sleep_for(BLINKING_RATE);

        led1.write(0);
        led2.write(0);
        led3.write(1);
        ThisThread::sleep_for(BLINKING_RATE);

    }

    
}
