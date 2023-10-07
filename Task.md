## Problem Statement

In a vehicle control architecture, multiple Electronic Control Units (ECUs) are connected through a CAN protocol. Each ECU is programmed to take care of specific
functionality. MCB is one such ECU in the architecture that performs the following tasks:

- Measure 8 Digital Inputs from multiple switches / sensors in the vehicle
- Perform defined actions based on the status of digital inputs
- Communication with other ECUs through CAN protocol

As part of this assignment, you have to write an Interrupt Service Routine (ISR) in C
language, for Sampling the Digital Inputs. The ISR should perform below functionality:

- Read the real-time status of digital input pins from a global variable **g_ReadDIpinSts**. Here, each bit in **g_ReadDIpinSts** represents the status of one digital input pin.
- Update the digital input status to a global variable **g_AppDIpinSts**, maintaining the bit position of digital inputs.
- The condition for a status update in **g_AppDIpinSts** is, "The pin state of a particular digital input has to be consistent for 10 consecutive ISR calls". Here, ISR is triggered every 100 mSec once.

### Expected Output

- Code uploaded in GitHub (Share the link). Use the below function prototype.
  - int ISR_DIsampling(){
  -   //Write your code here
  - }
