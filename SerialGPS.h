#include "mbed.h"
 
#ifndef MBED_GPS_H
#define MBED_GPS_H
 

class SerialGPS {
public:
 
  
    SerialGPS(PinName tx, PinName rx, int Baud);
    
    /** Intialize the incoming GPS data
     */
    int sample();
    
    /** The longitude*/
    float longitude;
 
    /** The latitude*/
    float latitude;
    
    /** The time*/
    float time;
    
    /** Number of satellites received */
    int sats;
    
    /** Horizontal dilusion of precision */
    float hdop;
    
    /** The altitude 
     */
    float alt;
    
    /** The geoid */
    float  geoid;
    
    /** The NMEA sentence */
    char msg[256];
    
    
private:
    float trunc(float v);
    void getline();
    
    Serial _gps;
};
 
#endif
            