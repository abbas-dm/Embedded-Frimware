#include <avr/io.h>
#include <avr/interrupt.h>

// unsigned char uint8_t
uint8_t g_ReadDIpinSts = 0;
uint8_t g_AppDIpinSts = 0;

/* 
 * counter to check whether values are changed or not
 * resets to zero every time new input has come or counter > 10 
*/
uint8_t counter = 0;

/*
 * assuming the below array is the digital pins data
 * received from CAN bus
 * 
 * In real this array will be updated from real CAN Bus
*/
uint8_t readDigitalPins[8] = {0,1,0,1,0,1,1,1};

// Implementing Interrupt Service Routine function
void ISR_DIsampling() {

    for (int i = 0; i < 8; i++) {
        if (readDigitalPins[i] == 1) {
            g_ReadDIpinSts |= (1 << i); // Set the bit to 1
        } else {
            g_ReadDIpinSts &= ~(1 << i); // Clear the bit to 0
        }
    } 

    for (int pin = 0; pin < 8; pin++) {
        // Read the status of the pin from g_ReadDIpinSts
        uint16_t currentStatus = (g_ReadDIpinSts >> pin) & 0x1;

        // Check if the current status matches the previous status
        if (currentStatus == ((g_AppDIpinSts >> pin) & 0x1)) {
            // Increment the consecutive consistent readings counter for this pin
            g_ConsistentCount[pin]++;

            // Check if the threshold for consecutive consistent readings is reached
            if (g_ConsistentCount[pin] >= 10) {
                // Update the corresponding bit in g_AppDIpinSts
                g_AppDIpinSts |= (currentStatus << pin);

                // Reset the consecutive consistent readings counter for this pin
                g_ConsistentCount[pin] = 0;
            }
        } else {
            // Reset the consecutive consistent readings counter for this pin
            g_ConsistentCount[pin] = 0;
        }
    }  
}

// Timer1 compare match ISR
ISR(TIMER1_COMPA_vect) {
    // Call the function to be executed every 100 ms
    ISR_DIsampling();
}

int main() {

    // Initialize hardware and configure timer (Timer1 in this case)
    // For example, configure Timer1 for CTC mode and prescaler 1024
    TCCR1B |= (1 << WGM12);    // Set CTC mode
    OCR1A = 1562;             // Set compare value for 100 ms at 16 MHz (Prescaler 1024)
    TIMSK1 |= (1 << OCIE1A);   // Enable compare match interrupt
    sei();

    // While loop to run continuously
    while (1) {
        
    }

    return 0;
}
