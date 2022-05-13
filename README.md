# Embedded-Frimware
GREENDZINE TECHNOLOGIES PVT LTD INTERNSHIP ASSIGNMENT

# The ISR will perform below functionality:
Read the real-time status of digital input pins from a global variable g_ReadDIpinSts. Here, each bit in g_ReadDIpinSts represents the status of one digital input pin.

Update the digital input status to a global variable g_AppDIpinSts, maintaining the bit position of digital inputs.

Condition for status update in g_AppDIpinSts is, "The pin state of a particular digital input has to be consistent for 10 consecutive ISR calls". Here, ISR is triggered every 100 mSec once.
