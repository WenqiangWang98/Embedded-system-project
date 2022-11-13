#ifndef SI7021_H
#define SI7021_H
 
#include "mbed.h"
 
 
 
class Si7021
{
public:
    Si7021(I2C* _i2c);
    ~Si7021();
    
    float get_temperature();
    float get_humidity();
    
    
private:
    I2C* i2c;
    int sensor_addr=0x40 << 1;
    void readRegs(int addr, uint8_t * data, int len);
    void writeRegs(uint8_t * data, int len);
};
 
#endif