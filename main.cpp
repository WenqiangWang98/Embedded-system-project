#include "mbed.h"
#include "TCS34725.h"
#include "HWSP1.h"
#include "LED.h"
#include "SEN13322.h"
#include "SerialGPS.h"
#include "MMA8451Q.h"
#include "Si7021.h"
#include <cstdint>
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
int index = 0;
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);


// parameter aux to calculate
float *soilValues;
float *lightValues;
float *tempValues;
float *humValues;

int *colorValues;

float * xValues;
float * yValues;
float * zValues;

Timeout to;






 //initizased
LED led(&ledRGB);
SEN13322 soilSensor(&analoginSoilMoisture);
HWSP1 lightSensor(&analoginLightSensor);
SerialGPS sensorGPS(PA_9, PA_10,9600);
TCS34725 colorSensor(&i2c);
MMA8451Q accelerometer(&i2c);
Si7021 tempHum(&i2c);


void printAllMeasuredTestMode(){
    pc.printf("Soil Moisture (%2.1f%%)\n", soilSensor.readValue());

    pc.printf("Light:(%2.1f%%)\n",lightSensor.readValue());

    sensorGPS.sample();
    string time = std::to_string( sensorGPS.time);
    string hour, min,sec;
    hour = time.substr(0,2);
    min = time.substr(2,2);
    sec = time.substr(5,2);
 
    printf("GPS: Sats: %d, Lat(UTC): %2.3f, Long(UTC): %2.3f, Altitude: %.1fm, GPS_Time %s:%s:%s  \n",
    sensorGPS.sats, 
    sensorGPS.latitude,  
    sensorGPS.longitude,     
    sensorGPS.alt,
    hour.c_str(),min.c_str(),sec.c_str()
    );

    string colorDomStr;
    int16_t colorRed=  colorSensor.getValueRed();
    int16_t colorGreen = colorSensor.getValueGreen();
    int16_t colorBlue = colorSensor.getValueBlue();
    int16_t colorClear = colorSensor.getValueClear();

   

    if(colorRed>colorGreen){
        if(colorRed>colorBlue){
            colorDomStr="Red";
            ledColor = 6; // 110 001
        }
        else {
            colorDomStr="Blue";
            
            ledColor = 3; //011 100
        }
    }
    else {
        if(colorGreen>colorBlue){
            colorDomStr="Green";
            ledColor = 5; // 101 010
        }
        else {
            colorDomStr="Blue";
            ledColor = 3;
        }
    }

    pc.printf("Color Senor: Red: %d, Green: %d, Blue: %d, Clear: %d     --Dominat color:%s \n",
    colorSensor.getFixedRed(),
    colorSensor.getFixedGreen(),
    colorSensor.getFixedBlue(),
    colorSensor.getValueClear(),
    colorDomStr.c_str()
    );

    pc.printf("ACCELEROMETER: X_axis: %2.1f, Y_axis: %2.1f, Z_axis: %2.1f\n",
    accelerometer.getAccX(),
    accelerometer.getAccY(),
    accelerometer.getAccZ()

    );

    pc.printf("TEMP/HUM: Temperature: %2.1fC, Relative Humidity: %2.1f %% \n\n",
    tempHum.get_temperature(),
    tempHum.get_humidity()
    );


}















void printAllMeasuredNormalMode(){

    ledColor = 7;

    float soilValue= soilSensor.readValue();
    soilValues[index]=soilValue; // save value
    if(soilValue<= 100 & soilValue >= 0){ // Soil moisture in %, corresponding 0% to total dryness and 100% to maximum moisture.
        pc.printf("Soil Moisture (%2.1f%%)\n", soilValue);
    }
    else{
        ledColor = 4;// 100 011 yellow
    }
  


    float lightValue = lightSensor.readValue();
    lightValues[index]=lightValue; // save value
    if (lightValue<= 100 & lightValue >= 0){ //Ambient light in %, corresponding 0% to total darkness and 100% to maximum light.
        pc.printf("Light:(%2.1f%%)\n",lightValue);
    }
    else {
        ledColor = 1;// 001 110 cyna
    }
    


    if (true){ //The global location of the plant should be registered. The GPS module also offers the current time (only time, the date is optional), that will be used to timestamp all the measurements taken by the system.
        sensorGPS.sample();
        string time = std::to_string( sensorGPS.time);
        string hour, min,sec;
        hour = time.substr(0,2);
        min = time.substr(2,2);
        sec = time.substr(5,2);
    
        printf("GPS: Sats: %d, Lat(UTC): %2.3f, Long(UTC): %2.3f, Altitude: %.1fm, GPS_Time %s:%s:%s  \n",
        sensorGPS.sats, 
        sensorGPS.latitude,  
        sensorGPS.longitude,     
        sensorGPS.alt,
        hour.c_str(),min.c_str(),sec.c_str()
        );

    }
    else {
        ledColor = 3;// 011 100 Blue
    }




    string colorDomStr;
    int16_t colorRed=  colorSensor.getFixedRed();
    int16_t colorGreen = colorSensor.getFixedGreen();
    int16_t colorBlue = colorSensor.getFixedBlue();
    int16_t colorClear = colorSensor.getValueClear();
    if(colorRed<=255 & colorRed>=0 & colorGreen<=255 & colorGreen>=0 & colorBlue<=255 & colorBlue>=0 ){
        if(colorRed>colorGreen){
            if(colorRed>colorBlue){
                colorDomStr="Red";
                colorValues[index]=0; //red
            }
            else {
                colorDomStr="Blue";
                colorValues[index]=1; //blue
            }
        }
        else {
            if(colorGreen>colorBlue){
                colorDomStr="Green";
                colorValues[index]=2; //green
            }
            else {
                colorDomStr="Blue";
                colorValues[index]=1; //blue
            }
        }

        pc.printf("Color Senor: Red: %d, Green: %d, Blue: %d, Clear: %d     --Dominat color:%s \n",
        colorSensor.getFixedRed(),
        colorSensor.getFixedGreen(),
        colorSensor.getFixedBlue(),
        colorSensor.getValueClear(),
        colorDomStr.c_str()
        );
    }
    else{
         ledColor = 5; // 101 010 Green
    }

   
    float xValue = accelerometer.getAccX();
    float yValue = accelerometer.getAccY();
    float zValue = accelerometer.getAccZ();
    xValues[index] = xValue;
    yValues[index] = yValue;
    zValues[index] = zValue;
    if(true){
        
        pc.printf("ACCELEROMETER: X_axis: %2.1f, Y_axis: %2.1f, Z_axis: %2.1f\n",
        xValue,
        yValue,
        zValue
        );
    }
    else{
        ledColor = 6; // 110 001 Red
    }


    float tempHumTemp = tempHum.get_temperature();
    float tempHumHum = tempHum.get_humidity();
    tempValues[index]=tempHumTemp; // save value
    humValues[index]=tempHumHum; // save value
    if(tempHumTemp<=50& tempHumTemp>= -10 & tempHumHum<=75 & tempHumHum >=25){
        pc.printf("TEMP/HUM: Temperature: %2.1fC, Relative Humidity: %2.1f %% \n\n",
        tempHumTemp,
        tempHumHum
        );
    }
    else{
        ledColor = 2; // 010 101 Purple
    }

   
    index++;
    pc.printf("index: %d \n\n",index);
}


void printMeanMaxMin(float * values,string name,int length){
    float mean=0;
    float min=0;
    float max=0;
    for(int i=1; i< length;i++){
        mean+=values[i];
        if(values[i]>max){
            max = values[i];
        }
        if(values[i]<min){
            min = values[i];
        }
    }
    mean= mean/length;


    printf("     %s Mean: %.2f Max: %.2f Min: %.2f \n",name.c_str(),mean,max,min);
}

void printColorDom(int * values,int length){
    int colorRed=0; //0
    int colorGreen=0; //2
    int colorBlue=0; //1
    for(int i=1; i< length;i++){
        
        if(values[i]==0){
            colorRed++;
        }
        else if(values[i]==2){
            colorGreen++;
        }
        else{
            colorBlue++;
        }
    }
    printf("%d %d %d\n",colorRed,colorBlue,colorGreen);
    string colorDomStr;
    if(colorRed>colorGreen){
        if(colorRed>colorBlue){
            colorDomStr="Red";
            colorValues[index]=0; //red
        }
        else {
            colorDomStr="Blue";
            colorValues[index]=2; //blue
        }
    }
    else {
        if(colorGreen>colorBlue){
            colorDomStr="Green";
            colorValues[index]=2; //green
        }
        else {
            colorDomStr="Blue";
            colorValues[index]=1; //blue
        }
    }

    printf("     Color Domiant %s \n",colorDomStr.c_str());

}




void printAllCalculated(){
    printf("\n\n\nCalculated Value of %d Values: \n\n",index);

    printMeanMaxMin(tempValues, "temperature",index+1);
    printMeanMaxMin(humValues, "relative humidity",index+1);
    printMeanMaxMin(lightValues, "ambient light",index+1);
    printMeanMaxMin(soilValues, "soil moisture",index+1);
    ThisThread::sleep_for(2000);
    // for (int i=1; i<index+1; i++) {
    //     printf("test %f \n",xValues[i]);
    // }
    //  for (int i=1; i<index+1; i++) {
    //     printf("test %f \n",yValues[i]);
    // }
    //  for (int i=1; i<index+1; i++) {
    //     printf("test %f \n",zValues[i]);
    // }


    printMeanMaxMin(xValues, "X axes",index+1);
    printMeanMaxMin(yValues, "Y axes",index+1);
    printMeanMaxMin(zValues, "Z axes",index+1);
    ThisThread::sleep_for(1000);
    printColorDom(colorValues,index+1);

    

    printf("\n\nValue Printed Completed \n\n\n");
    
   
   
}



    


void resetValues(){
     // reset values
    index=0;
    delete soilValues;
    delete lightValues;
    delete tempValues;
    delete humValues;
    delete colorValues;
    delete xValues;
    delete yValues;
    delete zValues;
    soilValues = new float;
    lightValues= new float;
    tempValues= new float;
    humValues= new float;

    xValues= new float;
    yValues= new float;
    zValues= new float;

    colorValues = new int ;

}

   




void testMode(){
    // ledColor = 1;
    // printf("color : %d \n",ledColor);
    // printf("test mode : %d \n",mode);
    pc.printf("TEST MODE\n");
    printAllMeasuredTestMode();
    led.writeAndChangeColor(ledColor);// change led color using the dominant colour detected by the sensor
    ThisThread::sleep_for(2000); // every 2 seconds


}

void normalMode(){
    // ledColor = 5;
    // printf("color : %d \n",ledColor);
    // printf("normal mode : %d \n",mode);
    
    
    if(index == 5){ // 1 hours / 30 seconds = 120 index
        printAllCalculated();
        ThisThread::sleep_for(2000);
        resetValues();
    }
    pc.printf("NORMAL MODE\n");
    printAllMeasuredNormalMode();
    
    led.writeAndChangeColor(ledColor);// change led color using the dominant colour detected by the sensor
    ThisThread::sleep_for(3000); // every 30 seconds
}

void advancedMode(){
    // ledColor = 6;
    // printf("color : %d \n",ledColor);
    // printf("advanced mode : %d \n",mode);
    pc.printf("ADVANCED MODE\n");
}

void button_pressed(void){
    pressed = true;
}



int main() {
 
    //initialize
    
    
    mode =0;
    resetValues();

    

    printf("start!\n");

    //test mode
    testMode();
    led.writeAndChangeColor(7); // no color
    led1= 1; //led 1 open
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
        led1 = 0;
        led2 = 0;
        led3 = 0;
        
        switch (mode) {
            case 0:
                testMode();
                led1=1;
                index = 0 ; //reset index normal mode
                break;
            case 1:

                normalMode();
                led2=1;
                break;
            case 2:
                advancedMode();
                index = 0 ; //reset index normal mode
                led3= 1;
                break;
        }
   

        //  ThisThread::sleep_for(1000); //  1 seconds
      
    }
    
}