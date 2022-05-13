#include <stdio.h>
#include <time.h>

int g_ReadDIpinSts[8] = {1,1,0,0,0,1,0,1};
int g_AppDIpinSts[8] = {0,0,0,0,0,0,0,0};

// Global Variables to be used in the logic of ISR function
int count[8] = {0,0,0,0,0,0,0,0};
int Readpins[8] = {0,0,0,0,0,0,0,0};

// Implementing Interrupt Service Routine function
int ISR_DIsampling() {

    // Write your code here
    for (int i=0; i<8; i++) {
        //Checking count values for the first time
        //if count[i] == 0, update it to 1
        //else checking for condition to increase count[i] or to store 1 in count[i]
        if (count[i] == 0) {
            count[i] = 1;
        }
        else {
            if (g_ReadDIpinSts[i] == Readpins[i]) {
                count[i]++;
            }
            else {
                count[i] = 1;
            }
        }
    }

    // Storing the current Digital pin status into Readpins 
    for (int i=0; i<8; i++) {
        Readpins[i] = g_ReadDIpinSts[i];
    }

    // Updating the g_AppDIpinSts variable
    for (int i=0; i<8; i++) {
        if(count[i] >= 10) {
            g_AppDIpinSts[i] = g_ReadDIpinSts[i];
        }
    }

    return 0;
}

// Implementing Delay function for 100 milli seconds
void delay(int number_of_ms) {

    // Set start_time to current time
    clock_t start_time = clock();
  
    // Loop untill the desired delay is reached
    while (clock() < start_time + number_of_ms)   
    ;
}

int main() {

    printf("\nPrinting g_AppDIpinSts values after every ISR Call :- \n");

    // While loop to run continuosly
    while (1) {
        // ISR function calling
        ISR_DIsampling();   

        // 100 ms delay to trigger the ISR
        delay(100);

        // Printing the g_AppDIpinSts data after every ISR call
        for (int i=0; i<8; i++) {
            printf("%d ", g_AppDIpinSts[i]);
        }
        printf("\n\n");
    }

    return 0;
}
