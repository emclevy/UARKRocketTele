//#include FreeRTOS files




typedef enum{
    S0,
    S1,
    S2,
    S3,
    S4
} State;

State state = S4;
int engineSwitchStart;
int engineSwitchCompleted;

void engineSwitchFSM(){
    switch(state){
        case S4:
            holdState();
        case S0:
            pinCheck();
        case S1:
            launch_Engine2();
        case S2:
            launch_Engine3();
        case S3:
            engineSwitchCompleted = completed();
    }
}

void holdState(){
    while(engineSwitchStart != 1) {}
    state = S0;
}

void pinCheck(){
    //Check to see which pin to activate
    //Either based off activation of Pins 1/2
    //Or off of something else. Talk to ELEG
    //if(X)
    //  state = S1;
    //else
    //  state = S2;
}

void launch_Engine2(){
    //set pin 21 to 1;
    P21SEL |= 1;
    state = S3;
}

void launch_Engine3(){
    //set pin 22 to 1;
    P22SEL |= 1;
    state = S3;
}

int completed(){
    //add to Main count ?!?!?!?!?
    //Say engineSwitch_Finished
    return 1;
}


