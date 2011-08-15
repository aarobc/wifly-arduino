//Arduino wifi library

#ifndef Wifi_h
#define Wifi_h

#include "WProgram.h"


// to enter command mode
boolean cmdMode();


// send commands to the wifly module
boolean command(char* todo);

// to scan for a specific string
boolean scanSer(char* stering);

// send ssid, will attempt to join
boolean joinWifi(char* ssid);

// forward communication to the main serial
void out();

//open connection
boolean openWifi();

// send querey over IP, returns whatever querey recieved.
String ipCmdr(char* out);

// thourougly clears out the second serial, 
// is not needed on hardware uarts
//void superFlush();

// endless echo loop for debugging
void serEcho();

#endif

