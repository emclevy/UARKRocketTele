//#include FreeRTOS files

typedef enum{
    S0,
    S1,
    S2,
    S3
} State;

State state = S0;

void dataFSM(){
    switch(state){
    }
}


//check if data is ready
    //if so load in usable data
    //MUST BE IN SAME ORDER EVERY TIME
//When all has been sent to transceiver
    //wait 10 ms
//Repeat