 
#include "MMA8451Q.h"
 
#define REG_WHO_AM_I      0x0D
#define REG_CTRL_REG_1    0x2A
#define REG_OUT_X_MSB     0x01
#define REG_OUT_Y_MSB     0x03
#define REG_OUT_Z_MSB     0x05
#define REG_CTRL_REG_5    0x2E
#define REG_CTRL_REG_4    0x2D
#define PULSE_CFG         0x21
#define PULSE_LTCY        0x27
#define PULSE_THSZ        0x25
 
#define UINT14_MAX        16383
 
MMA8451Q::MMA8451Q(I2C* _i2c ): i2c(_i2c) {
    mode=true;
    changeMode(false);
    // activate the peripheral
    // uint8_t data[2] = {0x2A, 0x08};
    // writeRegs(data, 2);
    
    
    // uint8_t data3[2] = {0x21, 0x15};//activate flag single tap and ELE
    // writeRegs(data3, 2);
    
    // uint8_t data6[2] = {0x23, 0x19};//Set X Threshold to 1.575g
    // writeRegs(data6, 2);
    // uint8_t data7[2] = {0x24, 0x19};//Set X Threshold to 1.575g
    // writeRegs(data7, 2);
    // uint8_t data8[2] = {0x25, 0x2A};//Set X Threshold to 1.575g
    // writeRegs(data8, 2);

    // // uint8_t data9[2] = {0x26, 0x50};//Set X Threshold to 1.575g
    // // writeRegs(data9, 2);

    // // uint8_t data10[2] = {0x27, 0xF0};//Set X Threshold to 1.575g
    // // writeRegs(data10, 2);

    // uint8_t data12[2] = {0x15, 0xD8};//activate flag OEA =1
    // writeRegs(data12, 2);
    // uint8_t data13[2] = {0x17, 0x20};// 3g/0.063g = 48
    // writeRegs(data13, 2);
    // uint8_t data14[2] = {0x18, 0x0A};// 400 ms/10 ms 25count
    // writeRegs(data14, 2);

    // uint8_t data2[2] = {0x2D, 0x04};//activate freefall and motion and puls interrupt
    // writeRegs(data2, 2);

    // uint8_t data1[2] = {0x2E, 0x04};//activate interrupt for freefall and motion INT2 and for pulse INT1
    // writeRegs(data1, 2);

    

    // uint8_t data11[2]={0x2A,19};
    // writeRegs(data11, 2);


    // uint8_t data12[2] = {0x2A, 0x20};//activate flag OEA =1
    // writeRegs(data12, 2);
    // uint8_t data13[2] = {0x15, 0xB8};// 3g/0.063g = 48
    // writeRegs(data13, 2);
    // uint8_t data14[2] = {0x17, 0x03};// 400 ms/10 ms 25count
    // writeRegs(data14, 2);
    // uint8_t data22[2] = {0x18, 0x06};//activate freefall and motion and puls interrupt
    // writeRegs(data22, 2);
    // uint8_t data2[2] = {0x2D, 0x04};//activate freefall and motion and puls interrupt
    // writeRegs(data2, 2);

    // uint8_t data1[2] = {0x2E, 0x04};//activate interrupt for freefall and motion INT2 and for pulse INT1
    // writeRegs(data1, 2);

    // uint8_t data122[2] = {0x2A, 0x21};//activate flag OEA =1
    // writeRegs(data122, 2);



    // char t[1] = {0X2A};
    // i2c->write(m_addr, t, 1, true);
    // i2c->read(m_addr, (char *)data11, 1);
    // data11[0]=data11[0]| 0x01;
    // i2c->write(m_addr, (char *)data11, 1);

}
 
MMA8451Q::~MMA8451Q() { }
 
uint8_t MMA8451Q::getWhoAmI() {
    uint8_t who_am_i = 0;
    readRegs(REG_WHO_AM_I, &who_am_i, 1);
    return who_am_i;
}
uint8_t MMA8451Q::getState() {
    uint8_t who_am_i = 0;
    readRegs(REG_WHO_AM_I, &who_am_i, 1);
    readRegs(0x0b, &who_am_i, 1);
    return who_am_i;
}
 
float MMA8451Q::getAccX() {
    return (float(getAccAxis(REG_OUT_X_MSB))/4096.0);
}
 
float MMA8451Q::getAccY() {
    return (float(getAccAxis(REG_OUT_Y_MSB))/4096.0);
}
 
float MMA8451Q::getAccZ() {
    return (float(getAccAxis(REG_OUT_Z_MSB))/4096.0);
}
 
void MMA8451Q::getAccAllAxis(float * res) {
    res[0] = getAccX();
    res[1] = getAccY();
    res[2] = getAccZ();
}
 
int16_t MMA8451Q::getAccAxis(uint8_t addr) {
    int16_t acc;
    uint8_t res[2];
    readRegs(addr, res, 2);
 
    acc = (res[0] << 6) | (res[1] >> 2);
    if (acc > UINT14_MAX/2)
        acc -= UINT14_MAX;
 
    return acc;
}
 
void MMA8451Q::readRegs(int addr, uint8_t * data, int len) {
    char t[1] = {static_cast<char>(addr)};
    i2c->write(m_addr, t, 1, true);
    i2c->read(m_addr, (char *)data, len);
}
 
void MMA8451Q::writeRegs(uint8_t * data, int len) {
    i2c->write(m_addr, (char *)data, len);
}
 
void MMA8451Q::changeMode(bool _mode){

    if(_mode==mode)return;
    else if(_mode==false&&mode==true){
        mode=false;
        uint8_t data[2] = {0x2A, 0x08};
        writeRegs(data, 2);
        uint8_t data3[2] = {0x21, 0x15};//activate flag single tap and ELE
        writeRegs(data3, 2);
        uint8_t data6[2] = {0x23, 0x19};//Set X Threshold to 1.575g
        writeRegs(data6, 2);
        uint8_t data7[2] = {0x24, 0x19};//Set X Threshold to 1.575g
        writeRegs(data7, 2);
        uint8_t data8[2] = {0x25, 0x2A};//Set X Threshold to 1.575g
        writeRegs(data8, 2);
        uint8_t data9[2] = {0x26, 0x50};//Set X Threshold to 1.575g
        writeRegs(data9, 2);
        uint8_t data10[2] = {0x27, 0xF0};//Set X Threshold to 1.575g
        writeRegs(data10, 2);

        uint8_t data12[2] = {0x15, 0xD8};//activate flag OEA =1
        writeRegs(data12, 2);
        uint8_t data13[2] = {0x17, 0x20};// 3g/0.063g = 48
        writeRegs(data13, 2);
        uint8_t data14[2] = {0x18, 0x19};// 400 ms/10 ms 25count
        writeRegs(data14, 2);

        uint8_t data2[2] = {0x2D, 0x0C};//activate freefall and motion and puls interrupt
        writeRegs(data2, 2);
        uint8_t data1[2] = {0x2E, 0x08};//activate interrupt for freefall and motion INT2 and for pulse INT1
        writeRegs(data1, 2);
        uint8_t data122[2] = {0x2A, 0x09};//activate flag OEA =1
        writeRegs(data122, 2);
        
    }
    else if(_mode==true&&mode==false){
        mode=true;
        uint8_t data[2] = {0x2A, 0x08};
        writeRegs(data, 2);
        uint8_t data3[2] = {0x21, 0x15};//activate flag single tap and ELE
        writeRegs(data3, 2);
        uint8_t data6[2] = {0x23, 0x19};//Set X Threshold to 1.575g
        writeRegs(data6, 2);
        uint8_t data7[2] = {0x24, 0x19};//Set X Threshold to 1.575g
        writeRegs(data7, 2);
        uint8_t data8[2] = {0x25, 0x2A};//Set X Threshold to 1.575g
        writeRegs(data8, 2);
        uint8_t data9[2] = {0x26, 0x50};//Set X Threshold to 1.575g
        writeRegs(data9, 2);
        uint8_t data10[2] = {0x27, 0xF0};//Set X Threshold to 1.575g
        writeRegs(data10, 2);

        uint8_t data12[2] = {0x15, 0xB8};//activate flag OEA =1
        writeRegs(data12, 2);
        uint8_t data13[2] = {0x17, 0x03};// 3g/0.063g = 48
        writeRegs(data13, 2);
        uint8_t data14[2] = {0x18, 0x06};// 400 ms/10 ms 25count
        writeRegs(data14, 2);

        uint8_t data2[2] = {0x2D, 0x0C};//activate freefall and motion and puls interrupt
        writeRegs(data2, 2);
        uint8_t data1[2] = {0x2E, 0x08};//activate interrupt for freefall and motion INT2 and for pulse INT1
        writeRegs(data1, 2);
        uint8_t data122[2] = {0x2A, 0x09};//activate flag OEA =1
        writeRegs(data122, 2);
    }
    
}