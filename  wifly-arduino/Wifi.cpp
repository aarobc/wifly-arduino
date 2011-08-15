// Wifly module library by Aaron Christiansen
// allows boolean response from common comands.

#include "Wifi.h"
#include "Wprogram.h"
#include <Streaming.h>

// enter command mode, will return when command mode entered successuflly.
boolean cmdMode(){
  delay(300);
  Serial1.print("$$$");
  if(scanSer("CMD"))
    return true;
  else
    return false;
}


// scan for a specific serial response that's passed in.
// if the string that's beeing looked for isn't found within
// 10 seconds then the function returns false. 
boolean scanSer(char* stering){
  int timer = millis() + 20000;
  String temp = "a";
  
  while(temp.indexOf(stering) == -1 && timer > millis()){
    while(Serial1.available()){
      temp += (char)Serial1.read();
    }
    delay(300);
  }
  
  Serial1.flush();
  if(temp.indexOf(stering) > -1)
    return true;
  else
    return false;
}

// forwards serial data out through the other serial.
// usefull for debugging.
void out(){
  delay(10);
  while(Serial1.available()){
    Serial.print(Serial1.read(), BYTE);
  }
}

// this function is for sending commands to the wifi module
boolean command(char* todo){
  Serial1.println(todo);
  delay(10);
  
  if(scanSer(">"))
    return true;
  else
    return false;
}

// Join the network in the variable
boolean joinWifi(char* ssid){
  int timer = millis() + 10000;
  Serial1 << "join " << ssid << '\r';
  delay(100);
  Serial1.flush();
  delay(100);
  Serial1 << "show connection" << '\r'; // check if connection was successful
  
  if(scanSer("cb30"))
    return true;
  else
    return false;
  }


// sends a command then returns everything forwarded as
// a string. 
String ipCmdr(char* out){
  int timer = millis() + 9000;  
  String fin = "1";

  Serial1 << out << '\n'<<'\n' << endl;
  while(millis() < timer && fin.indexOf("S*") == -1){
  
    while(Serial1.available()){
      fin += (char)Serial1.read();
    }
    delay(400);
  }

  if(fin.indexOf("*CLOS*") > -1){
    fin = fin.substring( 0, fin.indexOf("*"));
  }
  delay(100);
  return fin;
}

// is needed if program is being used with sofware serial. 

//void superFlush(){
//
//  Serial1.end();
//  delay(50);
//  Serial1.begin(9600);
//  delay(10);
//  Serial1.flush();
//  delay(10);
//  while(Serial1.available()){
//    Serial1.flush();
//    delay(10);
//  }
//}


// open tcp connection
boolean openWifi(){
  
  Serial1 << "open" << '\r';  
  
  if(scanSer("*OPEN*"))
    return true;
  else return false;

}


void serEcho(){
 
    
      if(Serial.available()){
    Serial1.print(Serial.read(), BYTE);
  }

  if(Serial1.available()){
    Serial.print(Serial1.read(), BYTE);
  }
  
  
}
