//#include FreeRTOS files



typedef enum{
    S0,
    S1,
    S2,
    S3,
    S4
} State;

State state = S4;
int paraStart;
int paraCompleted;

void paraFSM(int x){
    switch(state){
        case S4:
            holdState();
        case S0:
            launchPara(x);
        case S1:
            mainLaunch();
        case S2:
            backupLaunch();
        case S3:
            paraCompleted = completed();
    }
}

void holdState(){
    while(paraStart != 1) {}
    state = S0;
}

void launchPara(int x){
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
    //set pin 25 to 1
    P25SEL |= 1;
    state = S3;
}


void backupLaunch(){
    //set pin 26 to 1
    P26SEL |= 1;
    state = S3;
}

int completed(){
    //add to main count ?!?!?!?!?!?!?!?
    //say paraCompleted = 1
    return 1;
}