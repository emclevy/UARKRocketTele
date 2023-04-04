//#include FreeRTOS files
#include "engineSwitchFSM.c"
#include "drogueFSM.c"
#include "parachuteFSM.c"
#include "dataFSM.c"


typedef enum{
    S0,
    S1,
    S2,
    S3,
    S4
} State;

State state = S0;
int counter;

void mainFSM(){
    switch(state){
        case S0:
            wifiSwitchWaiting();

        case S1:
            switch(counter){
                case 1:
                case 2: /**/
                    
                case 3:
                case 4: /**/

                case 5:
                case 6: /**/

                case 7: /**/

                default:
                    counter = 1;

            }
    }
}


void wifiSwitchWaiting() {
    //waiting for the wifi switch to be on, then can continue
    while(1 /*Wifi switch stuff*/) {}
    state = S1;
}