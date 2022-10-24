#include "mbed.h"
#include "MMA8451Q.h"
#include "TCS34725.h"
 
 #define MMA8451_I2C_ADDRESS (0x1c<<1)
Serial pc(USBTX, USBRX);
I2C i2c(PB_9,PB_8);
int main(void) {
    i2c.frequency(400000);
    MMA8451Q acc(&i2c);
    TCS34725 color(&i2c);
    pc.baud(115200);
    color.setGain(0);
    color.setTiming(0xf6);
    while (true) {     

        //pc.printf("acc:\nx: %f, y: %f, z: %f\n",acc.getAccX(),acc.getAccY(),acc.getAccZ());
        pc.printf("color:\nred: %d, green: %d, blue: %d\n",color.getFixedRed(),color.getFixedGreen(),color.getFixedBlue());
        pc.printf("clear: %d, red: %d, green: %d, blue: %d\n",color.getValueClear(),color.getValueRed(),color.getValueGreen(),color.getValueBlue());
        wait(2);
    }
}