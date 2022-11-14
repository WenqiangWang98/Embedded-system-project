 
#ifndef MMA8451Q_H
#define MMA8451Q_H
 
#include "mbed.h"
class MMA8451Q
{
public:
  MMA8451Q(I2C* i2c);
  ~MMA8451Q();
  uint8_t getWhoAmI();
  uint8_t getState();
  float getAccX();
  float getAccY();
  float getAccZ();
  void getAccAllAxis(float * res);
  void changeMode(bool mode);
  bool mode=0;//0=motion,1 freefall
private:
  I2C* i2c;
  int m_addr=0x1c<<1;
  
  void readRegs(int addr, uint8_t * data, int len);
  void writeRegs(uint8_t * data, int len);
  int16_t getAccAxis(uint8_t addr);
};
 
#endif
 