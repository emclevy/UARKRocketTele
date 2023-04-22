#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define fileName "RawData.csv"
#define outputFile "realtime.csv"
#define timeColumn 0
#define AltitudeColumn 1
#define VelocityColumn 2
#define AccelerationColumn 3
#define VerticalOri 4
#define LateralOri 5

float maxAlt;
float maxVel;
float maxAcc;
float curTime;
float elapsed_time = 0;
float prevTime = 0;
int parseFlag = 1;
float dataSet[23][450];
char TelemNames[23];
volatile float package[5]; //T, Alt, Veloc, AccelG
int row = 0;

void delay(int milli_seconds);

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
            while (token != NULL && cur_col < 6) {

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

void getTime(int row_p, FILE *fp){
    //todo: read current value from system clock on msp430
    curTime = getValue(row_p, timeColumn) * 1000;
    delay((curTime - prevTime) * 1000);
    printf("Time: %.2f\n", getValue(row_p, timeColumn));
    fprintf(fp, "%.2f,", getValue(row_p, timeColumn));
    prevTime = curTime;
}

void getAcceleration(int row_p, FILE *fp){
    //todo: read current value from accelerometer on msp430
    float accel = getValue(row_p, AccelerationColumn);
    printf("Acceleration: %.2f\n", accel);
    fprintf(fp, "%.2f,", getValue(row_p, AccelerationColumn));
    if (accel > maxAcc){
        maxAcc = accel;
    }
}

void getVelocity(int row_p, FILE *fp){
    //todo: read current velocity from msp430
    float velocity = getValue(row_p, VelocityColumn);
    fprintf(fp, "%.2f,", getValue(row_p, VelocityColumn));
    printf("Velocity: %.2f\n", velocity);
    if (velocity > maxVel){
        maxVel = velocity;
    }
}

void getAltitude(int row_p, FILE *fp){
    //todo: read current altitude from msp430
    float altitude = getValue(row_p, AltitudeColumn);
    fprintf(fp, "%.2f,", getValue(row_p, AltitudeColumn));
    printf("Altitude: %.2f\n", altitude);
    if (altitude > maxAlt){
        maxAlt = altitude;
    }
}

void getVertOri(int row_p, FILE *fp){
    //todo: read current value from system clock on msp430
    printf("Vertical Orientation: %.2f\n", getValue(row_p, VerticalOri));
    fprintf(fp, "%.2f,", getValue(row_p, VerticalOri));
}

void getLatOri(int row_p, FILE *fp){
    //todo: read current value from system clock on msp430
    printf("Lateral Orientation: %.2f\n", getValue(row_p, LateralOri));
    fprintf(fp, "%.2f\n", getValue(row_p, LateralOri));
}

void getGPS(){

}

void getEMatchStates() {

}

void scheduler(int row_p, FILE *fp) {

    getTime(row_p, fp);
    getAltitude(row_p, fp);
    getVelocity(row_p, fp);
    getAcceleration(row_p, fp);
    getVertOri(row_p, fp);
    getLatOri(row_p, fp);
    fflush(fp); //write data to disk immediately

}



void delay(int milli_seconds) {
    // Converting time into milli_seconds
    //int milli_seconds = 1000 * number_of_milliseconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}


int main() {
    FILE *output = fopen(outputFile, "w");
    if(output == NULL){
        printf("error");
    }
    fprintf(output, "Time, Altitude, Velocity, Acceleration, vertical orientation, lateral orientation\n");
    //clock_t start_time = clock();
    printf("Hello, World!\n");
    for (int i = 0; i <=645; i++){
        printf("\n \ndata at %i\n", i);
        scheduler(i, output);
        //delay(100000);
    }
    printf("Max alt: %f \n", maxAlt);
    printf("Max vel: %f \n", maxVel);
    printf("Max acc: %f \n", maxAcc);

    //sleep(1000);
    return 0;
}
