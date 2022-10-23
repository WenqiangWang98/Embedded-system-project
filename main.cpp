#include "TCS34725.cpp"
#include "HWSP1.cpp"
#include "LED.cpp"
#include "SEN13322.cpp"
#include "FPGMMOPA6C.cpp"
#include "SerialGPS.h"
//For Color Senor TCS34725
I2C i2c(PB_9, PB_8); //pins for I2C communication (SDA, SCL)
Serial pc(USBTX, USBRX);  
DigitalOut led(PB_7);

//For LightSensor HW5P-1
AnalogIn analoginLightSensor(PA_4); 

// FOR Soil moisture
AnalogIn analoginSoilMoisture(PA_0);

//For Led RGB
BusOut ledRGB(PH_0,PH_1,PB_13); // R,G,B



int main() {

    //For Color Senor TCS34725
    // TCS34725 colorSensor(&i2c,&pc,&led);
    // colorSensor.init();
    // colorSensor.setGain(3);
    // while (true) { 
    //     colorSensor.printFixedValues();
    //     ThisThread::sleep_for(1000);
    // }

    // //For LightSensor
    // HWSP1 lightSensor(&analoginLightSensor,&pc);
    // lightSensor.readValue();
    // lightSensor.printValues();

    // //FOR LED
    // LED led(&ledRGB,&pc);
    // led.writeAndChangeColor(0);


    // // FOR Soil moisture
    // SEN13322 soilSensor(&analoginSoilMoisture,&pc);
    // while(true){
    //     soilSensor.printValues();
    //     ThisThread::sleep_for(1000);
    // }
    

    //For GPS sensor
    // FPGMMOPA6C gpsSensor(&pc);
    // while (true) {
    //     gpsSensor.readValue();
    //     ThisThread::sleep_for(1000);
    // }
    SerialGPS sensorGPS(USBTX, USBRX,9600);
    while (1) {
        // sensorGPS.sample();
        printf("Lat %f Lon %f Time %f ", sensorGPS.latitude,sensorGPS.longitude,sensorGPS.time);
        
        ThisThread::sleep_for(1000);
    }

    
}