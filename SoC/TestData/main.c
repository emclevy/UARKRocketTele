#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define fileName "dataFile.csv"
#define timeColumn 0
#define AltitudeColumn 1
#define VelocityColumn 2
#define AccelerationColumn 3


int parseFlag = 1;
float dataSet[23][450];
char TelemNames[23];
volatile float package[5]; //T, Alt, Veloc, AccelG
int row = 0;

float getValue(int row_p, int dataCol){

    int row = 0;
    //int timeCol = 0;
    char line[1024];
    char *token;
    float data[23];
    int cur_col = 0;
    FILE *dataFile = fopen(fileName, "r");
    if (dataFile == NULL){
        printf("error opening file");
    } else {
        while (fgets(line, 1024, dataFile) != NULL){
            token = strtok(line, ",");
            cur_col = 0;
            while (token != NULL && cur_col < 23) {

                data[cur_col] = atof(token);
                cur_col++;
                token = strtok(NULL, ",");
            }
            if(row == row_p) {
                //printf("time value is %.2f\n", data[dataCol]);
                return data[dataCol];

            }
            row++;
        }
        //fclose(fileName);
    }
}

void getTime(int row_p){
    //todo: read current value from system clock on msp430
    printf("Time: %f\n", getValue(row_p, timeColumn));
}

void getAcceleration(int row_p){
    //todo: read current value from accelerometer on msp430
    printf("Acceleration: %f\n", getValue(row_p, AccelerationColumn));
}

void getVelocity(int row_p){
    //todo: read current velocity from msp430
    printf("Velocity: %f\n", getValue(row_p, VelocityColumn));
}

void getAltitude(int row_p){
    //todo: read current altitude from msp430
    printf("Acceleration: %f\n", getValue(row_p, AltitudeColumn));
}

void getGPS(){

}

void getEMatchStates() {

}

void scheduler(int row_p) {

    getTime(row_p);
    getAltitude(row_p);
    getVelocity(row_p);
    getAcceleration(row_p);

}

int main() {
    //clock_t start_time = clock();
    printf("Hello, World!\n");
    for (int i = 0; i <=10; i++){
        printf("data at %i\n", i);
        scheduler(i);
    }
    //scheduler();


        //sleep(5);
    return 0;
}
