/* =====================================================================
   __  __      _____  ______  _   _  _______   _____   ____   _____
   \ \ \ \    / ____||  ____|| \ | ||__   __| / ____| / __ \ |  __ \
 __ \ \ \ \  | (___  | |__   |  \| |   | |   | (___  | |  | || |__) |
 \ \ \ \ \_\  \___ \ |  __|  |     |   | |    \___ \ | |  | ||  _  /
  \ \ \ \     ____) || |____ | |\  |   | |    ____) || |__| || | \ \
   \_\ \_\   |_____/ |______||_| \_|   |_|   |_____/  \____/ |_|  \_\

 Project      : Core Board 328P - Self test
 Description  : Do basic test to check built-in functionality
 Author       : SENTSOR
 Note         : Using ATmega328P with Arduino Nano bootloader

===================================================================== */

#define DEBUG_OUT(msg) Serial.print(msg)
#define onboardLed 2
#define ssPin 10

#include <SD.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup() {
  //Start serial and begin the test
  Serial.begin(9600, SERIAL_8N1);
  DEBUG_OUT(F("\n\nSENTSOR Core Board 328P Self-Test\n"));
  delay(500);

  //RTC test: RTC init, check RTC timekeep, print current timestamp
  DEBUG_OUT(F("DEBUG >> Initializing RTC... "));
  if (rtc.begin()) {
    DEBUG_OUT(F("OK\n"));
    delay(500);

    DEBUG_OUT(F("DEBUG >> Checking RTC timekeep... "));
    if (rtc.lostPower()) {
      //It means our RTC didn't keeping time, usually because the battery is removed or dead
      DEBUG_OUT(F("FAILED\n"));
      DEBUG_OUT(F("DEBUG >> Reseting RTC to sketch upload time\n"));
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    else {
      DEBUG_OUT(F("OK\n"));
    }
    DEBUG_OUT(F("DEBUG >> RTC timestamp is "));
    DateTime time = rtc.now();
    DEBUG_OUT(time.timestamp(DateTime::TIMESTAMP_DATE)); DEBUG_OUT(F(" "));
    DEBUG_OUT(time.timestamp(DateTime::TIMESTAMP_TIME)); DEBUG_OUT(F("\n"));
    delay(500);
  }
  else {
    DEBUG_OUT(F("FAILED\n"));
    DEBUG_OUT(F("DEBUG >> RTC not initialized\n"));
    delay(500);
  }

  //SD test: SD init with slave select (SS) at pin 10, write/read/delete file
  DEBUG_OUT(F("DEBUG >> Initializing memory card... "));
  if (SD.begin(ssPin)) {
    DEBUG_OUT(F("OK\n"));
    delay(500);

    File file;
    const char filename[15] = "sentsor.txt";
    char text[30] = "Hello from SENTSOR Board!";

    DEBUG_OUT(F("DEBUG >> Writing test file... "));
    file = SD.open(filename, FILE_WRITE);
    if (file) {
      DEBUG_OUT(F("\"")); DEBUG_OUT(text); DEBUG_OUT(F("\" "));
      file.print(text);
      file.close();
      DEBUG_OUT(F("OK\n"));
      delay(500);

      DEBUG_OUT(F("DEBUG >> Reading test file... "));
      file = SD.open(filename, FILE_READ);
      if (file) {
        file.read(text, 30);
        DEBUG_OUT(F("\"")); DEBUG_OUT(text); DEBUG_OUT(F("\" "));
        file.close();
        DEBUG_OUT(F("OK\n"));
        delay(500);
      }
      else {
        DEBUG_OUT(F("FAILED\n"));
        DEBUG_OUT(F("DEBUG >> Unable to read file\n"));
        delay(500);
      }

      DEBUG_OUT(F("DEBUG >> Removing test file... "));
      if (SD.remove(filename)) {
        DEBUG_OUT(F("OK\n"));
        delay(500);
      }
      else {
        DEBUG_OUT(F("FAILED\n"));
        DEBUG_OUT(F("DEBUG >> Unable to remove file\n"));
        delay(500);
      }
    }
    else {
      DEBUG_OUT(F("FAILED\n"));
      DEBUG_OUT(F("DEBUG >> Unable to write file\n"));
      delay(500);
    }
  }
  else {
    //SD.begin return false if didn't detect the MicroSD card
    DEBUG_OUT(F("FAILED\n"));
    DEBUG_OUT(F("DEBUG >> Memory card not initialized\n"));
    delay(500);
  }

  //Blink onboard LED at pin 2
  DEBUG_OUT(F("DEBUG >> Configuring pin D2 as output for onboard LED\n"));
  pinMode(onboardLed, OUTPUT);
  DEBUG_OUT(F("DEBUG >> Onboard LED should blink 3 times"));
  for (uint8_t i = 0; i < 3; i++) {
    DEBUG_OUT(F("."));
    digitalWrite(onboardLed, HIGH);
    delay(1000);
    digitalWrite(onboardLed, LOW);
    delay(1000);
  }
  DEBUG_OUT(F(" OK\n"));

  DEBUG_OUT(F("DEBUG >> Self-test complete\n"));
  DEBUG_OUT(F("DEBUG >> Entering standby mode\n"));
  delay(500);
}

void loop() {
  //Idle by just blinking LED
  static uint32_t lastMillis;
  if (millis() - lastMillis >= 500L) {
    lastMillis = millis();
    digitalWrite(onboardLed, HIGH);
    delay(100);
    digitalWrite(onboardLed, LOW);
  }
}

// End of File [SENTSOR]
