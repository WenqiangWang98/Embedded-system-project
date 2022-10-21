 #include "mbed.h"
 
I2C i2c(PB_9, PB_8); //pins for I2C communication (SDA, SCL)
Serial pc(USBTX, USBRX);    //Used to view the colors that are read in
 
int sensor_addr = 41 << 1;
 
//DigitalOut green(LED1);
DigitalOut led(PB_7);

class TCS34725 {
    private:
    I2C* i2c;
    Serial* pc;
    DigitalOut* led;
    public:
        TCS34725();
        TCS34725(I2C* _i2c,Serial* _pc,DigitalOut* _led){
            i2c=_i2c;
            pc=_pc;
            led=_led;
        };
        void init(){
            pc->baud(115200);
            i2c->frequency(400000);
            char timing_register[2] = {129,0};
            i2c->write(sensor_addr,timing_register,2,false);
    
            char control_register[2] = {143,0};
            i2c->write(sensor_addr,control_register,2,false);
    
            char enable_register[2] = {128,3};
            i2c->write(sensor_addr,enable_register,2,false);
            *led = 1;
        };
        int readValueClear(){
            char clear_reg[1] = {148};
            char clear_data[2] = {0,0};
            i2c->write(sensor_addr,clear_reg,1, true);
            i2c->read(sensor_addr,clear_data,2, false);
        
            int clear_value = ((int)clear_data[1] << 8) | clear_data[0];
            return clear_value;
        };
        int readValueRed(){
            char red_reg[1] = {150};
            char red_data[2] = {0,0};
            i2c->write(sensor_addr,red_reg,1, true);
            i2c->read(sensor_addr,red_data,2, false);
        
            int red_value = ((int)red_data[1] << 8) | red_data[0];
            return red_value;
        };
        int readValueGreen(){
            char green_reg[1] = {152};
            char green_data[2] = {0,0};
            i2c->write(sensor_addr,green_reg,1, true);
            i2c->read(sensor_addr,green_data,2, false);
        
            int green_value = ((int)green_data[1] << 8) | green_data[0];
            return green_value;
        };
        int readValueBlue(){
            char blue_reg[1] = {154};
            char blue_data[2] = {0,0};
            i2c->write(sensor_addr,blue_reg,1, true);
            i2c->read(sensor_addr,blue_data,2, false);
        
            int blue_value = ((int)blue_data[1] << 8) | blue_data[0];
            return blue_value;
        };
        void printValues(){
            pc->printf("Clear (%d), Red (%d), Green (%d), Blue (%d)\n", readValueClear(), readValueRed(), readValueGreen(), readValueBlue());
        }
        
        
};

int main() {
    //pc.baud(115200);
    //green = 1; // off
    TCS34725 colorSensor(&i2c,&pc,&led);
    // Connect to the Color sensor and verify
    colorSensor.init();
    
    //i2c.frequency(400000);
    
    // char id_regval[1] = {146};
    // char data[1] = {0};
    // i2c.write(sensor_addr,id_regval,1, true);
    // i2c.read(sensor_addr,data,1,false);
    
    // if (data[0]==68) {
    //     green = 0;
    //     wait (2); 
    //     green = 1;
    //     } else {
    //     green = 1; 
    // }
    
    // Initialize color sensor
    
    // char timing_register[2] = {129,0};
    // i2c.write(sensor_addr,timing_register,2,false);
    
    // char control_register[2] = {143,0};
    // i2c.write(sensor_addr,control_register,2,false);
    
    // char enable_register[2] = {128,3};
    // i2c.write(sensor_addr,enable_register,2,false);
    
    // Read data from color sensor (Clear/Red/Green/Blue)
    //led = 1;
    while (true) { 
        // char clear_reg[1] = {148};
        // char clear_data[2] = {0,0};
        // i2c.write(sensor_addr,clear_reg,1, true);
        // i2c.read(sensor_addr,clear_data,2, false);
        
        // int clear_value = ((int)clear_data[1] << 8) | clear_data[0];
        
        // char red_reg[1] = {150};
        // char red_data[2] = {0,0};
        // i2c.write(sensor_addr,red_reg,1, true);
        // i2c.read(sensor_addr,red_data,2, false);
        
        // int red_value = ((int)red_data[1] << 8) | red_data[0];
        
        // char green_reg[1] = {152};
        // char green_data[2] = {0,0};
        // i2c.write(sensor_addr,green_reg,1, true);
        // i2c.read(sensor_addr,green_data,2, false);
        
        // int green_value = ((int)green_data[1] << 8) | green_data[0];
        
        // char blue_reg[1] = {154};
        // char blue_data[2] = {0,0};
        // i2c.write(sensor_addr,blue_reg,1, true);
        // i2c.read(sensor_addr,blue_data,2, false);
        
        // int blue_value = ((int)blue_data[1] << 8) | blue_data[0];
        
        // print sensor readings
        
        //pc.printf("Clear (%d), Red (%d), Green (%d), Blue (%d)\n", colorSensor.readValueClear(), colorSensor.readValueRed(), colorSensor.readValueGreen(), colorSensor.readValueBlue());
        //The above code displays the red, green, and blue values read in by the color sensor.
        colorSensor.printValues();
        ThisThread::sleep_for(1000);
    }
    
}
