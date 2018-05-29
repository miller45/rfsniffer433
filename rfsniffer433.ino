/*
   RF Sniffer (C) Elia Yehuda 2014

   This program was coded.

   No warranty whatsoever.
   Using this program will cause something, most likely problems.

*/

#include <RCSwitch.h>
#include "RTClib.h"
#include "homeeasycodes.h";
#include "carfob.h";


// ye, thats the led pin #
#define LED_PIN 13

// class for 434 receiver & transmitter
RCSwitch rf434Switch = RCSwitch();

RTC_Millis rtc;

boolean LR = false;
boolean LG = false;
boolean LB = false;

void setup()
{
  Serial.begin(115200);
  rtc.begin(DateTime(__DATE__, __TIME__));
  if (rtc.isrunning()) {
    Serial.println("RTC IS RUNNING");
  } else {
    Serial.println("RTC is NOT running! ");
  }
  // print fast to console



  // 434 receiver on interrupt #0 (pin #2)
  rf434Switch.enableReceive(0);


  Serial.println("[+] Listening");
}

// simple decimal-to-binary-ascii procedure
char *tobin32(unsigned long x)
{
  static char b[33];
  b[32] = '\0';

  for ( int z = 0; z < 32; z++) {
    b[31 - z] = ((x >> z) & 0x1) ? '1' : '0';
  }

  return b;
}

void process_rf_value(RCSwitch rfswitch, int rf)
{
  char str[120];
  unsigned long value;

  // flash a light to show transmission
  digitalWrite(LED_PIN, true);

  value = rfswitch.getReceivedValue();
  if (value) {
    sprintf(str, "[+] %d Received: %s / %010lu / %02d bit / Protocol = %d",
            rf, tobin32(value), value, rfswitch.getReceivedBitlength(), rfswitch.getReceivedProtocol() );
  } else {
    sprintf(str, "[-] %d Received: Unknown encoding (0)", rf);
  }
  SerialPrintTime();
  Serial.print(str);

  if (TryDisplayHomeEasy(value)) {
    FlipRGBLED(true, false, false);
  }
  if (TryDisplayCarFob(value)) {
    FlipRGBLED(false, true, false);
  }
  Serial.println();

  // reset the switch to allow more data to come
  rfswitch.resetAvailable();
  // stop light to show end of transmission
  digitalWrite(LED_PIN, false);
}

void SerialPrintTime() {
  DateTime now = rtc.now();
  if (now.hour() < 10) Serial.print(" ");
  Serial.print(now.hour());
  Serial.print(":");
  if (now.minute() < 10) Serial.print("0");
  Serial.print(now.minute());
  Serial.print(":");
  if (now.second() < 10) Serial.print("0");
  Serial.print(now.second());
  Serial.print (" ");
}

void FlipRGBLED(boolean r, boolean g, boolean b) {
  if (r) {
    LR = !LR;
  }
  if (g) {
    LG = !LG;
  }
  if (b) {
    LB = !LB;
  }
  SetRGBLED(LR, LG, LB);
}

void SetRGBLED(boolean r, boolean g, boolean b) {
  if (r) {
    pinMode(5, OUTPUT);
  } else {
    pinMode(5, INPUT);
  }
  if (g) {
    pinMode(6, OUTPUT);
  } else {
    pinMode(6, INPUT);
  }
  if (b) {
    pinMode(7, OUTPUT);
  } else {
    pinMode(7, INPUT);
  }
}


void loop()
{

  if (rf434Switch.available()) {
    process_rf_value(rf434Switch, 434);
  }
}


