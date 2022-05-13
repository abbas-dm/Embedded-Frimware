#include <stdio.h>
#include <stdint.h>
#include <time.h>

// typedef unsigned char uint8_t
uint8_t g_ReadDIpinSts = 255;
uint8_t g_AppDIpinSts = 0;

// Global Variables to be used in the logic of ISR function
int count[8] = {0,0,0,0,0,0,0,0};
int Readpins[8] = {0,0,0,0,0,0,0,0};

// Implementing the function to find bit in a given position
int bitFind(int n) {

    int bit;
    bit = (( g_ReadDIpinSts & (1 << (n) ) ) ? 1 : 0 );

    return bit;
}

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
            if (bitFind(i) == Readpins[i]) {
                count[i]++;
            }
            else {
                count[i] = 1;
            }
        }
    }

    // Storing the current Digital pin status into Readpins 
    for (int i=0; i<8; i++) {
        Readpins[i] = bitFind(i);
    }

    // Updating the g_AppDIpinSts variable
    for (int i=0; i<8; i++) {
        if(count[i] >= 10) {
            if(bitFind(i) == 1) {
                g_AppDIpinSts |= 1 << (i);
            }
            else {
                g_AppDIpinSts &= ~(1 << (i));
            }
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
        printf("g_AppDIpinSts value after every ISR call is :: %d", g_AppDIpinSts);
        printf("\n\n");
    }

    return 0;
}
