#ifndef TCS34725_H
#define TCS34725_H
 
#include "mbed.h"

 class TCS34725
{
public:
  TCS34725(I2C* _i2c);
  ~TCS34725();
  int16_t getValueClear();
  int16_t getValueRed();
  int16_t getValueGreen();
  int16_t getValueBlue();
  int16_t * getAllColors();
  int16_t getFixedRed();
  int16_t getFixedGreen();
  int16_t getFixedBlue();
  int16_t * getFixedColors();
  void setGain(int16_t gain);
  void setTiming(int16_t timing);
 
private:
  I2C* i2c;
  int sensor_addr=41 << 1;
  void readRegs(int addr, uint8_t * data, int len);
  void writeRegs(uint8_t * data, int len);
  int16_t getValueColor(uint8_t addr);
 
};
#endif