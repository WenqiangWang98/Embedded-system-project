#include "TCS34725.cpp"
I2C i2c(PB_9, PB_8); //pins for I2C communication (SDA, SCL)
Serial pc(USBTX, USBRX);  
DigitalOut led(PB_7);
int main() {
    TCS34725 colorSensor(&i2c,&pc,&led);
    colorSensor.init();
    colorSensor.setGain(3);
    while (true) { 
        colorSensor.printFixedValues();
        ThisThread::sleep_for(1000);
    }
    
}