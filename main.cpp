#include "mbed.h"
#include "MMA8451Q.h"
#include "TCS34725.h"
#include "Si7021.h"
Serial pc(USBTX, USBRX);
I2C i2c(PB_9,PB_8);
int main(void) {
    //i2c.frequency(400000);
    MMA8451Q acc(&i2c);
    TCS34725 color(&i2c);
    pc.baud(115200);
    color.setGain(0);
    color.setTiming(0xf6);
    Si7021 TRHsensor(&i2c);
    while (true) {     

        // char buff[2];
        // char cmd[1]={0xe5};
        // i2c.write(0x80,cmd,1);
        // i2c.read(0x80,buff,2);
        // int temp=(buff[0]<<8)+buff[1];
        // float Temperatura=(175.72*temp/65536)-46.85;

        // char cmd1[1]={0xe3};
        // i2c.write(0x80,cmd1,1);
        // i2c.read(0x80,buff,2);
        // int RH=(buff[0]<<8)+buff[1];
        // float RelativeHumidity=(125.0*RH/65536)-6;

        pc.printf("RH:  %f %%, Temp:  %f \n",TRHsensor.get_humidity(),TRHsensor.get_temperature());
        //pc.printf("acc:\nx: %f, y: %f, z: %f\n",acc.getAccX(),acc.getAccY(),acc.getAccZ());
        //pc.printf("color:\nred: %d, green: %d, blue: %d\n",color.getFixedRed(),color.getFixedGreen(),color.getFixedBlue());
        //pc.printf("clear: %d, red: %d, green: %d, blue: %d\n",color.getValueClear(),color.getValueRed(),color.getValueGreen(),color.getValueBlue());
        wait(2);



    }
}