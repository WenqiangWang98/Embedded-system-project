#ifndef TCS34725_H
#define TCS34725_H
 
#include "mbed.h"

 class TCS34725
{
public:
  TCS34725(I2C* _i2c);
  ~TCS34725();
  float getValueClear();
  float getValueRed();
  float getValueGreen();
  float getValueBlue();
  void getAllColors(float * res);
  float getFixedRed();
  float getFixedGreen();
  float getFixedBlue();
  void getFixedColors(float * res);
  void setGain(int gain);
 
private:
  I2C* i2c;
  int sensor_addr=41 << 1;
  void readRegs(int addr, uint8_t * data, int len);
  void writeRegs(uint8_t * data, int len);
  int16_t getValueColor(uint8_t addr);
 
};
#endif