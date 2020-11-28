/* =====================================================================
   __  __      _____  ______  _   _  _______   _____   ____   _____
   \ \ \ \    / ____||  ____|| \ | ||__   __| / ____| / __ \ |  __ \
 __ \ \ \ \  | (___  | |__   |  \| |   | |   | (___  | |  | || |__) |
 \ \ \ \ \_\  \___ \ |  __|  |     |   | |    \___ \ | |  | ||  _  /
  \ \ \ \     ____) || |____ | |\  |   | |    ____) || |__| || | \ \
   \_\ \_\   |_____/ |______||_| \_|   |_|   |_____/  \____/ |_|  \_\

 Project      : Core Board 328P - Datalog Variable Name
 Description  : Log data to memory card in in CSV format with variable
                filename
 Author       : SENTSOR
 Note         : Using ATmega328P with Arduino Nano bootloader

===================================================================== */

#define DEBUG_OUT(msg) Serial.print(msg)
#define onboardLed 2
#define ssPin 10
#define ADC0 A0
#define ADC1 A1
#define ADC2 A2
#define ADC3 A3
#define ADC4 A6
#define ADC5 A7
//Set sampling interval, unit in milliseconds unsigned long
#define SAMPLING_INTERVAL 1000UL

#include <SdFat.h>
#include <RTClib.h>

float voltage[6];
String data, filename;

SdFile file;
SdFat sd;
RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600, SERIAL_8N1);

  pinMode(onboardLed, OUTPUT);
  pinMode(ADC0, INPUT);
  pinMode(ADC1, INPUT);
  pinMode(ADC2, INPUT);
  pinMode(ADC3, INPUT);
  pinMode(ADC4, INPUT);
  pinMode(ADC5, INPUT);

  if (!rtc.begin()) {
    DEBUG_OUT(F("DEBUG >> RTC not initialized\n"));
    DEBUG_OUT(F("DEBUG >> Halt program\n"));
    while (1) {
      //Do nothing if RTC failed to initialized
      heartbeat(3);
      delay(500);
    }
  }

  if (!sd.begin(ssPin)) {
    DEBUG_OUT(F("DEBUG >> Memory card not initialized\n"));
    DEBUG_OUT(F("DEBUG >> Halt program\n"));
    while (1) {
      //Do nothing if memory card failed to initialized
      heartbeat(3);
      delay(500);
    }
  }
}

void loop() {
  static uint32_t lastMillis;

  //Execute sampling and datalogging every SAMPLING_INTERVAL milliseconds
  if (millis() - lastMillis >= SAMPLING_INTERVAL) {
    lastMillis = millis();

    //Read data
    DateTime time = rtc.now();
    voltage[0] = (float)analogRead(ADC0) * 5.0F / 1024.0F;
    voltage[1] = (float)analogRead(ADC1) * 5.0F / 1024.0F;
    voltage[2] = (float)analogRead(ADC2) * 5.0F / 1024.0F;
    voltage[3] = (float)analogRead(ADC3) * 5.0F / 1024.0F;
    voltage[4] = (float)analogRead(ADC4) * 5.0F / 1024.0F;
    voltage[5] = (float)analogRead(ADC5) * 5.0F / 1024.0F;

    //Format the data as comma-separated values (CSV)
    data = String(time.timestamp(DateTime::TIMESTAMP_DATE)) + " " + String(time.timestamp(DateTime::TIMESTAMP_TIME)) + ",";
    const uint8_t n = 2;
    data += String(voltage[0], n) + "," + String(voltage[1], n) + "," + String(voltage[2], n) + "," + String(voltage[3], n) + ",";
    data += String(voltage[4], n) + "," + String(voltage[5], n);

    //Format variable filename
    //Ex: Log data to new file everyday, filename is "YYYYMMDDdatalog.csv"
    filename = String(time.year());
    if (time.month() < 10) filename += "0"; filename += String(time.month());
    if (time.day() < 10) filename += "0"; filename += String(time.day()) + "datalog.csv";

    //Write data to memory card
    if (file.open(filename.c_str(), FILE_WRITE)) {
      file.println(data);
      file.close();

      DEBUG_OUT(F("DEBUG >> Writing data OK\n"));
      heartbeat(1);
    }
    else {
      DEBUG_OUT(F("DEBUG >> Writing data FAILED\n"));
      heartbeat(3);
    }
  }
}

void heartbeat(uint8_t n) {
  //Blink indicator LED for n-times
  while (n > 0) {
    digitalWrite(onboardLed, HIGH);
    delay(10);
    digitalWrite(onboardLed, LOW);
    delay(100);
    n--;
  }
}

// End of File [SENTSOR]
