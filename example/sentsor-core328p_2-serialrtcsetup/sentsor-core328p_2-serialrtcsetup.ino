/* =====================================================================
   __  __      _____  ______  _   _  _______   _____   ____   _____ 
   \ \ \ \    / ____||  ____|| \ | ||__   __| / ____| / __ \ |  __ \    
 __ \ \ \ \  | (___  | |__   |  \| |   | |   | (___  | |  | || |__) |   
 \ \ \ \ \_\  \___ \ |  __|  |     |   | |    \___ \ | |  | ||  _  /    
  \ \ \ \     ____) || |____ | |\  |   | |    ____) || |__| || | \ \    
   \_\ \_\   |_____/ |______||_| \_|   |_|   |_____/  \____/ |_|  \_\   

 Project      : Core Board 328P - Serial RTC Setup
 Description  : Manually adjust RTC timestamp via serial command
 Author       : SENTSOR
 Version      : 1.0.0 - Initial Build
 Note         : Using ATmega328P with Arduino Nano bootloader
 
===================================================================== */

#define DEBUG_OUT(msg) Serial.print(msg)
#define onboardLed 2

#include <RTClib.h>

RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600,SERIAL_8N1); 
  
  pinMode(onboardLed,OUTPUT);
  
  if(!rtc.begin()) {
    DEBUG_OUT(F("DEBUG >> RTC not initialized\n"));
    DEBUG_OUT(F("DEBUG >> Halt program\n"));
    while(1) {
      //Do nothing if RTC failed to initialized
      heartbeat(3);
      delay(500);
    }
  }
}

void loop() {
  //Wait serial input as command
  //Remember to set input as "No line ending" (a.k.a. not including \n and \r with the string)
  if(Serial.available()) {
    String cmd=Serial.readString();
    if(cmd.startsWith("RTCSET:") && (cmd.length()==26)) {
      //Accepted command:
      //RTCSET:yyyy,mm,dd,hh,mm,ss ex:RTCSET:2020,01,11,10,02,02 (leading 0 if value<10)
      //01234567890123456789012345
      //0         1         2
      uint16_t YYYY=cmd.substring(7,11).toInt();
      uint8_t MM=cmd.substring(12,14).toInt();
      uint8_t DD=cmd.substring(15,17).toInt();
      uint8_t hh=cmd.substring(18,20).toInt();
      uint8_t mm=cmd.substring(21,23).toInt();
      uint8_t ss=cmd.substring(24,26).toInt();

      //Adjust RTC timestamp
      rtc.adjust(DateTime(YYYY,MM,DD,hh,mm,ss));
      DateTime time=rtc.now();
      DEBUG_OUT(F("RTC adjusted to "));
      DEBUG_OUT(time.timestamp(DateTime::TIMESTAMP_DATE)); DEBUG_OUT(F(" "));
      DEBUG_OUT(time.timestamp(DateTime::TIMESTAMP_TIME)); DEBUG_OUT(F("\n"));
    }
    else {
      DEBUG_OUT(F("Command invalid"));
    }
  }
  
  //Read RTC data
  DateTime time=rtc.now();
  DEBUG_OUT(time.timestamp(DateTime::TIMESTAMP_DATE)); DEBUG_OUT(F(" "));
  DEBUG_OUT(time.timestamp(DateTime::TIMESTAMP_TIME)); DEBUG_OUT(F("\n"));
  heartbeat(1);
  
  delay(1000);
}

void heartbeat(uint8_t n) {
  //Blink indicator LED for n-times
  while(n>0) {
    digitalWrite(onboardLed,HIGH);
    delay(10);
    digitalWrite(onboardLed,LOW);
    delay(100);
    n--;
  }
}

// End of File [SENTSOR]
