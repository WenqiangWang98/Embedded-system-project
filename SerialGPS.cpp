#include "SerialGPS.h"
 
SerialGPS::SerialGPS(PinName tx, PinName rx, int Baud) : _gps(tx, rx) {
    _gps.baud(Baud);    
    longitude = 0.0;
    latitude = 0.0;        
}
 
int SerialGPS::sample() {
    char ns, ew, unit;
    int lock;
 
    while(1) {        
        getline();
 
        // Check if it is a GPGGA msg (matches both locked and non-locked msg)
        if(sscanf(msg, "GPGGA,%f,%f,%c,%f,%c,%d,%d,%f,%f,%c,%f", &time, &latitude, &ns, &longitude, &ew, &lock, &sats, &hdop, &alt, &unit, &geoid) >= 1) { 
            if(!lock) {
                time = 0.0;
                longitude = 0.0;
                latitude = 0.0;
                sats = 0;
                hdop = 0.0;
                alt = 0.0;
                geoid = 0.0;        
                return 0;
            } else {
            
                // time (float), lat (f), (N/S) (c), long (f), (E/W) (c), fix (d), sats (d),
                // hdop (float), altitude (float), M, geoid (float), M, , ,  
                
                if(ns == 'S') {    latitude  *= -1.0; }
                if(ew == 'W') {    longitude *= -1.0; }
                float degrees = trunc(latitude / 100.0f);
                float minutes = latitude - (degrees * 100.0f);
                latitude = degrees + minutes / 60.0f;    
                degrees = trunc(longitude / 100.0f * 0.01f);
                minutes = longitude - (degrees * 100.0f);
                longitude = degrees + minutes / 60.0f;
                return 1;
            }
        }
    }
}
 
float SerialGPS::trunc(float v) {
    if(v < 0.0) {
        v*= -1.0;
        v = floor(v);
        v*=-1.0;
    } else {
        v = floor(v);
    }
    return v;
}
 
void SerialGPS::getline() {
    while(_gps.getc() != '$');    // wait for the start of a line
 
    for(int i=0; i<256; i++) {
        msg[i] = _gps.getc();
        if(msg[i] == '\r') {
            msg[i] = 0;
            return;
        }
    }
    error("Overflowed message limit");
}
            