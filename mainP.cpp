
#include "mbed.h"
// #include "thread_modeNormal.cpp"

bool pressed;
bool powerOn_Off=1;
bool holding;
Thread thread1;
BusOut myleds(D2, D3, D7);
InterruptIn button(USER_BUTTON);
AnalogIn analoginLightSensor(PA_0); //PAO
Timeout tOut;
int countPrint;

void thread_modeNormal(void);


void button_hold(void){
    if (holding)powerOn_Off = !powerOn_Off;
    
}

void button_pressed(void){
    holding = 1;
    tOut.attach(button_hold,5);
    pressed = !pressed;
    
}
void button_under(void){
    holding = 0;
}


// main() runs in its own thread in the OS
int main()
{
    button.mode(PullDown);
    button.fall(button_pressed);
    button.rise(button_under);
    float numberAnalogin;
    countPrint = 0;
    thread1.start(thread_modeNormal);
    
    while (true) {
        
        if(powerOn_Off == 0){
            myleds.write(7);
            if(countPrint == 0) {
                printf("System Off\n");
                countPrint++;
             }

        }
        else {
            countPrint = 0;
             //mode normal
            if (pressed == 1){

            }
            else{ // mode blue
                myleds.write(6); // blue
                printf("lightSensor: Closed Mode: blue\n");
                ThisThread::sleep_for(2000);
            }
        }
       
      

    }
    
}

