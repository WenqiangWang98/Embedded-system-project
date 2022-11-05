#include "TCS34725.h"
#include <cstdint>
 
#define REG_TIMING          0x81
#define REG_CTRL            0x8F
#define REG_ENABLE          0x80
#define REG_CLEAR_DATA      0x94
#define REG_TIMING          0x81    
#define REG_RED_DATA        0x96
#define REG_GREEN_DATA      0x98
#define REG_BLUE_DATA       0x9A

TCS34725::TCS34725(I2C* _i2c):i2c(_i2c){
    //enable
    uint8_t enable_register[2] = {REG_ENABLE,3};
    writeRegs(enable_register, 2);
}
TCS34725::~TCS34725(){};
int16_t TCS34725::getValueClear(){
    return (getValueColor(REG_CLEAR_DATA));
}
int16_t TCS34725::getValueRed(){
    return (getValueColor(REG_RED_DATA));
}
int16_t TCS34725::getValueGreen(){
    return (getValueColor(REG_GREEN_DATA));
}
int16_t TCS34725::getValueBlue(){
    return (getValueColor(REG_BLUE_DATA));
}
int16_t * TCS34725::getAllColors() {
    int16_t * res;
    res[0] = getValueClear();
    res[1] = getValueRed();
    res[2] = getValueGreen();
    res[3] = getValueBlue();
    return res;
}
int16_t TCS34725::getFixedRed(){
    return ((getValueColor(REG_RED_DATA))*255/getValueClear());
}
int16_t TCS34725::getFixedGreen(){
    return ((getValueColor(REG_GREEN_DATA))*255/getValueClear());
}
int16_t TCS34725::getFixedBlue(){
    return ((getValueColor(REG_BLUE_DATA))*255/getValueClear());
}
int16_t * TCS34725::getFixedColors() {
    int16_t * res ;
    res[0] = getValueClear();
    res[1] = getFixedRed();
    res[2] = getFixedGreen();
    res[3] = getFixedBlue();
    return res;
}
void TCS34725::setGain(int16_t gain){
    uint8_t control_register[2] = {REG_CTRL,static_cast<uint8_t>(gain)};
    writeRegs(control_register, 2);
}
void TCS34725::setTiming(int16_t timing){
    uint8_t control_register[2] = {REG_TIMING,static_cast<uint8_t>(timing)};
    writeRegs(control_register, 2);
}

int16_t TCS34725::getValueColor(uint8_t addr){
    int16_t color;
    uint8_t res[2] ;
    readRegs(addr,res,2);
    color= ((int)res[1] << 8) | res[0];
    return color;
}
void TCS34725::readRegs(int addr, uint8_t * data, int len) {
    char t[1] = {static_cast<char>(addr)};
    i2c->write(sensor_addr, t, 1, true);
    i2c->read(sensor_addr, (char *)data, len);
}
 
void TCS34725::writeRegs(uint8_t * data, int len) {
    i2c->write(sensor_addr, (char *)data, len);
}