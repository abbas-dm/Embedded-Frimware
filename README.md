# Embedded-Frimware
GREENDZINE TECHNOLOGIES PVT LTD INTERNSHIP ASSIGNMENT

# The ISR will perform below functionality:
Read the real-time status of digital input pins from a global variable g_ReadDIpinSts. Here, each bit in g_ReadDIpinSts represents the status of one digital input pin (I have assigned value to the g_ReadDIpinSts directly in code).

Update the digital input status to a global variable g_AppDIpinSts, maintaining the bit position of digital inputs.

Condition for status update in g_AppDIpinSts is, "The pin state of a particular digital input has to be consistent for 10 consecutive ISR calls". Here, ISR is triggered every 100 mSec once.

# About the Code
I have implemented the code in such a way, when we execute the code it will run continuosly (to stop we can use "Crlt+C") and calls ISR for every 100ms. The function ISR_DIsampling() will perform the comparing of bits in g_ReadDIpinSts and updating of global variable g_AppDIpinSts. I have also used bitFind() function to find the bit values present in the given position of the number. To define a variable of size 8 bits, I have used 'uint8_t' which means 'typedef unsigned char' for global variables g_ReadDIpinSts and g_AppDIpinSts.
