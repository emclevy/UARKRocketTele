//#include FreeRTOS files



typedef enum{
    S0,
    S1,
    S2,
    S3,
    S4
} State;

State state = S4;
int drogueStart;
int drogueCompleted;

void drogueFSM(int x){
    switch(state){
        case S4:
            holdState();
        case S0:
            launchDrogue(x);
        case S1:
            mainLaunch();
        case S2:
            backupLaunch();
        case S3:
            drogueCompleted = completed();
    }
}

void holdState(){
    while(drogueStart != 1) {}
    state = S0;
}

void launchDrogue(int x){
    //check if main or backup is flipped
    //set accordingly
    if(x == 1) //main channel
        state = S1;
    else if(x == 2) //backup channel
        state = S2;
    else //NULL value
        state = S0;
}


void mainLaunch(){
    //set pin 23 to 1
    P23SEL |= 1;
    state = S3;
}


void backupLaunch(){
    //set pin 24 to 1
    P24SEL |= 1;
    state = S3;
}

int completed(){
    //add to main count !?!?!?!?
    //say drogueCompleted = 1
    return 1;
}