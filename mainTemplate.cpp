#include "mbed.h"
#include "TCS34725.h"
#include "HWSP1.h"
#include "LED.h"
#include "SEN13322.h"
#include "SerialGPS.h"
#include "MMA8451Q.h"
#include "Si7021.h"
#include <cstdio>
#include <string>


//For Color Senor TCS34725
I2C i2c(PB_9, PB_8); //pins for I2C communication (SDA, SCL)
Serial pc(USBTX, USBRX);  


//For LightSensor HW5P-1
AnalogIn analoginLightSensor(PA_4); 

// FOR Soil moisture
AnalogIn analoginSoilMoisture(PA_0);

//For Led RGB
BusOut ledRGB(PH_0,PH_1,PB_13); // R,G,B

//For accelerator

//For GPS
Serial pcGPS(PA_9,PA_10);

// blue button
InterruptIn button(USER_BUTTON);


// general

int mode = 0;
int ledColor = 0;
bool pressed = false;

 //initizased
    LED led(&ledRGB);
    SEN13322 soilSensor(&analoginSoilMoisture);
    HWSP1 lightSensor(&analoginLightSensor);
    SerialGPS sensorGPS(PA_9, PA_10,9600);
    TCS34725 colorSensor(&i2c);
    MMA8451Q accelerometer(&i2c);
    Si7021 tempHum(&i2c);


void printAllMeasured(){
    pc.printf("Soil Moisture (%2.1f%%)\n", soilSensor.readValue());

    pc.printf("Light:(%2.1f%%)\n",lightSensor.readValue());

    sensorGPS.sample();
    string time = std::to_string((int) sensorGPS.time);
    int hour,min,sec;
    sscanf(time.c_str(),"%2d%2d%2d", &hour,&min,&sec);    
    printf("GPS: Sats: %d, Lat(UTC): (%2.3f%%), Long(UTC): (%2.3f%%), Altitude: (%.1f%%)m, GPS_Time %d:%d:%d  \n ",
    sensorGPS.sats, 
    sensorGPS.latitude,  
    sensorGPS.longitude,     
    sensorGPS.alt,
    hour,min,sec);

    float* colorDom;  
    colorSensor.getAllColors(colorDom);
    string colorDomStr;
    if(colorDom[1]>colorDom[2]){
        if(colorDom[1]>colorDom[3]){
            colorDomStr="Red";
        }
        else {
            colorDomStr="Blue";
        }
    }
    else {
        if(colorDom[2]>colorDom[3]){
            colorDomStr="Green";
        }
        else {
            colorDomStr="Blue";
        }
    }

    pc.printf("Color Senor: Red: %f, Green: %f, Blue: %f, Clear: %f     --Dominat color:%s \n",
    colorSensor.getFixedRed(),
    colorSensor.getFixedGreen(),
    colorSensor.getFixedBlue(),
    colorSensor.getValueClear(),
    colorDomStr.c_str()
    );

    pc.printf("ACCELEROMETER: X_axis: (%2.1f%%), Y_axis: (%2.1f%%), Z_axis: (%2.1f%%)",
    accelerometer.getAccX(),
    accelerometer.getAccY(),
    accelerometer.getAccZ()

    )


}


void testMode(){
    ledColor = 1;
    // printf("color : %d \n",ledColor);
    // printf("test mode : %d \n",mode);
    pc.printf("TEST MODE\n");


}

void normalMode(){
    ledColor = 5;
    // printf("color : %d \n",ledColor);
    // printf("normal mode : %d \n",mode);
    pc.printf("NORMAL MODE\n");
}

void advancedMode(){
    ledColor = 6;
    // printf("color : %d \n",ledColor);
    // printf("advanced mode : %d \n",mode);
    pc.printf("ADVANCED MODE\n");
}

void button_pressed(void){
    pressed = true;
}



int main() {


    // template
    // i2c.frequency(400000);
    // MMA8451Q acc(&i2c);
    // TCS34725 color(&i2c);
    // pc.baud(115200);
    // color.setGain(1);
    // while (true) {     

    //     //pc.printf("acc:\nx: %f, y: %f, z: %f\n",acc.getAccX(),acc.getAccY(),acc.getAccZ());
    //     pc.printf("color:\nred: %f, green: %f, blue: %f\n",color.getFixedRed(),color.getFixedGreen(),color.getFixedBlue());
    //     pc.printf("clear: %f, red: %f, green: %f, blue: %f\n",color.getValueClear(),color.getValueRed(),color.getValueGreen(),color.getValueBlue());
    //     wait(2);
    // }





    //For Color Senor TCS34725
    // TCS34725 colorSensor(&i2c,&pc,&led);
    // colorSensor.init();
    // colorSensor.setGain(3);
    // while (true) { 
    //     colorSensor.printFixedValues();
    //     ThisThread::sleep_for(1000);
    // }

    // //For LightSensor
    // HWSP1 lightSensor(&analoginLightSensor);
    // pc.printf("light:%f\n",lightSensor.readValue());

    // //FOR LED
    // LED led(&ledRGB);
    // led.writeAndChangeColor(0);


    // // FOR Soil moisture
    // SEN13322 soilSensor(&analoginSoilMoisture);
    // while(true){
    //     pc.printf("Soil Moisture ( %3.3f%%)\n", soilSensor.readValue());
    //     ThisThread::sleep_for(1000);
    // }
    

    //For GPS sensor

    // SerialGPS sensorGPS(PA_9, PA_10,9600);
    // while (1) {
    //     sensorGPS.sample();
    //     int time = (int) sensorGPS.time;
    //     char str[6];
    //     sprintf(str, "%d", time);
    //     char hour[2] = {str[0],str[1]};
    //     char min[2] = {str[2],str[3]};
    //     char sec[2] = {str[4],str[5]};
        
    //     printf("Lat %f Lon %f Time %2s:%s:%s TIME RIGHT %d \n ", sensorGPS.latitude,sensorGPS.longitude,hour,min,sec,time);
        
    //     ThisThread::sleep_for(1000);
    // }



    mode =0;

   
    //initialize
    



   
    //test mode
    testMode();
    led.writeAndChangeColor(ledColor);
    printf("start!\n");
    ThisThread::sleep_for(1000);
    button.mode(PullDown);
    button.fall(button_pressed);




    while (1) {
        
        if(pressed){
            pressed= false;
            mode++;
            if(mode > 2){
                mode = 0;
            }
   
        }
        
        
        switch (mode) {
            case 0:
                testMode();//blue 

                break;
            case 1:
                normalMode();//Green
                break;
            case 2:
                advancedMode();//red
                break;
        }
        led.writeAndChangeColor(ledColor);


        ThisThread::sleep_for(2000); // every 2 seconds
    }
    
}