#include <Streaming.h>
#include "Wifi.h"

 char sssid[] = "SSID";
 char pass[] = "password";
void setup(){
  delay(3000);

  Serial1.begin(9600);
  Serial.begin(9600);
  delay(1000);
  Serial.println("START");
  delay(1000);

  if(cmdMode())
    Serial << "CMD mode" << endl;
  else{
    Serial << "command mode Error" << endl;
    delay(9000);
    cmdMode();
    serEcho();
  }

  if(command("set uart mode 1")) // set module not to echo commands
    Serial << "uart set" << endl;
  else
    Serial << "uart mode error" << endl;
    
  if(command("set wlan rate 0")) // lower bitrate means greater range
    Serial << "Wlan rate set" << endl;
    
    
  if(command("set w p "+pass))
     Serial << "password set" << endl;
  else
    Serial << "password error" << endl;
    
  int timer = millis() + 2000;
  while(!joinWifi(sssid) && millis() < timer){
    Serial << "connecting..." << endl;
  }

  Serial << "Connected!" << endl;

  Serial1.flush();
  delay(500);

  if(command("set dns name example.com"))
    Serial << "DNS set" << endl;

  //  Serial1.println("set ip address 0");
  //out();

  if(command("set ip address 0"))
    Serial << "ip address set" << endl;

  //  Serial1.println("set ip remote 80");
  //out();

  if(command("set ip remote 80"))
    Serial << "remote IP set" << endl;


  if(command("set com remote 0")) // prevent thers from connecting 
    Serial << "com remote set" << endl;

  delay(100);
  Serial1.flush();
  delay(100);

  if(openWifi())
    Serial << "Success open" << endl;
  else{
    Serial << "fail to open"<< endl;
  }

  delay(100);
  String one;
  one = (ipCmdr("GET /example.php?test=1234 "));

  Serial << one;
  Serial << endl;
  Serial << "Test sequence finished" << endl;
    Serial1 << "$$$";
}


void loop(){


  if(Serial.available()){
    Serial1.print(Serial.read(), BYTE);
  }

  if(Serial1.available()){
    Serial.print(Serial1.read(), BYTE);
  }

}



