#include "DigitalOut.h"
#include "PinNames.h"
#include "PwmOut.h"
#include "Thread.h"
#include "mbed.h"

Thread *threadLed;

DigitalOut myLed1(LED1);
PwmOut ledPwm(LED2);

void led_thread(){
    static float val;
    while(true){
        for(val=0.0f; val<1.0; val+=0.05){
            ledPwm = val;
            thread_sleep_for(50);
        }
        for(val=0.0f; val<1.0; val+=0.05){
            ledPwm = 1.0f-val;
            thread_sleep_for(10);
        }        
    }
}

// main() runs in its own thread in the OS
int main()
{
    threadLed = new Thread(osPriorityNormal, 512, nullptr, "LED Tread" );
    threadLed->start(led_thread);

    while (true) {
        myLed1 = 0;
        thread_sleep_for(500);
        myLed1 = 1;
        thread_sleep_for(50);
        myLed1 = 0;
        thread_sleep_for(50);    
        myLed1 = 1;
        thread_sleep_for(50);            
    }
}

