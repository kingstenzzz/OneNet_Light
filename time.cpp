#include <NTPClient.h>
#include <stdio.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
#include "time.h"
//const char *ssid     = "kingsten";
//const char *password = "23622033";

WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP);
NTPClient timeClient(ntpUDP, "ntp1.aliyun.com",60*60*8, 30*60*1000);


void time_setup(){
  
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

int Get_Time() {
  int hour;
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());
   //Serial.print ( timeClient.getHours());
   hour=timeClient.getHours();
  return hour;

  
}
