/* =====================================================================
   __  __      _____  ______  _   _  _______   _____   ____   _____
   \ \ \ \    / ____||  ____|| \ | ||__   __| / ____| / __ \ |  __ \
 __ \ \ \ \  | (___  | |__   |  \| |   | |   | (___  | |  | || |__) |
 \ \ \ \ \_\  \___ \ |  __|  |     |   | |    \___ \ | |  | ||  _  /
  \ \ \ \     ____) || |____ | |\  |   | |    ____) || |__| || | \ \
   \_\ \_\   |_____/ |______||_| \_|   |_|   |_____/  \____/ |_|  \_\

 Project      : Core Board 328P - Serial Stream
 Description  : Read voltage from ADC and stream the data via serial
 Author       : SENTSOR
 Note         : Using ATmega328P with Arduino Nano bootloader

===================================================================== */

#define DEBUG_OUT(msg) Serial.print(msg)
#define onboardLed 2
#define ADC0 A0
#define ADC1 A1
#define ADC2 A2
#define ADC3 A3
#define ADC4 A6
#define ADC5 A7

#include <RTClib.h>

float voltage[6];
String data;

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
}

void loop() {
  //Read RTC data
  DateTime time = rtc.now();

  //Read ADC and convert it to voltage (V=ADC*VREF/(2^n)
  voltage[0] = (float)analogRead(ADC0) * 5.0F / 1024.0F;
  voltage[1] = (float)analogRead(ADC1) * 5.0F / 1024.0F;
  voltage[2] = (float)analogRead(ADC2) * 5.0F / 1024.0F;
  voltage[3] = (float)analogRead(ADC3) * 5.0F / 1024.0F;
  voltage[4] = (float)analogRead(ADC4) * 5.0F / 1024.0F;
  voltage[5] = (float)analogRead(ADC5) * 5.0F / 1024.0F;

  //Format the data as comma-separated values (CSV)
  //Standard timestamp format is "YYYY-MM-DD hh:mm:ss"
  data = String(time.timestamp(DateTime::TIMESTAMP_DATE)) + " " + String(time.timestamp(DateTime::TIMESTAMP_TIME)) + ",";

  //Convert float to string with n-digit precision (digit after decimal places)
  const uint8_t n = 2;
  data += String(voltage[0], n) + "," + String(voltage[1], n) + "," + String(voltage[2], n) + "," + String(voltage[3], n) + ",";
  data += String(voltage[4], n) + "," + String(voltage[5], n);

  //Print data to serial
  Serial.println(data);
  heartbeat(1);
  delay(1000);
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
