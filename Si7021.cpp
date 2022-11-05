#include "Si7021.h"
#include <cstdint>
#define REG_TEMP        0xE3 /* Read previous T data from RH measurement command*/
/** Si7012 Read RH Command */
#define REG_RH          0xE5 /* Perform RH (and T) measurement. */
Si7021::Si7021(I2C* _i2c):i2c(_i2c)
{
}
 
Si7021::~Si7021()
{
}
 
float Si7021::get_temperature()
{
    uint8_t buff[2];
    readRegs(REG_TEMP,buff, 2);
    int16_t temp=(buff[0]<<8)+buff[1];
    float temperature=(175.72*temp/65536)-46.85;
    return temperature;
}
 
float Si7021::get_humidity()
{
    uint8_t buff[2];
    readRegs(REG_RH,buff, 2);
    int16_t RH_DATA=(buff[0]<<8)+buff[1];
    float RH=(125.0*RH_DATA/65536)-6;
    return RH;
}

void Si7021::readRegs(int addr, uint8_t * data, int len) {
    char t[1] = {static_cast<char>(addr)};
    i2c->write(sensor_addr, t, 1, true);
    i2c->read(sensor_addr, (char *)data, len);
}
 
void Si7021::writeRegs(uint8_t * data, int len) {
    i2c->write(sensor_addr, (char *)data, len);
}
 