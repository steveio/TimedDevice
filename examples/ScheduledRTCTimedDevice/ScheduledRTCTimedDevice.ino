/**
 * 
 * ScheduledRTCTimedDevice.ino
 * 
 * Demonstrates 3 devices (a lamp, two pumps) operated on defined timer schedules
 * 
 * Bitmask schedules (hour of day / day of week / month) define on|off times
 * 
 * Optimised for low memory footprint
 * 
 * Link - https://github.com/steveio/TimedDevice
 * Copyright (C) 2020  Steven G Edwards
 * 
 */
#include <Wire.h>
#include "RTClib.h"
#include "Pump.h"
#include "Relay.h"

RTC_DS1307 rtc;
DateTime dt;
char dtm[32], buf[2];
int nextEvent;


// GPIO Pins & mapping to devices
const int r1Pin = 10; // pump relay #1
const int r2Pin = 11; // pump relay #2
const int r3Pin = 12; // lamp relay


// master on/off switches
bool pumpEnabled = false;
bool lampEnabled = true;

// Timer 32 bit bitmask defines hours (24h) device is on | off
// 0b 00000000 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0

Timer lamp1Timer;
long lamp1TimerBitmask =0b00000000000111111111111111000000; // 6am - 9pm
Relay lamp1(r3Pin);

// Pump schedule includes <duration> (length of activation) and <delay> (interval-between-activations)
long pumpDuration = 600000; // 1 min activation (equals approx 1 litre)
long pumpDelay = 3600000; // 1 hour delay between activations
long pumpTimerHourBitmask = 0b00000000010000000000010000000000; // 9am + 9pm watering cycle

// Pump1 activates only on specific days of week
// day of week (bit index 0 = Sunday - 6 Saturday)
long pump1DayOfWeekBitmask = 0b0101010;

// Pump2 activates only on specific days of month 
// 0b 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
long pump2DayOfMonthBitmask =0b01111111100000000111111110000000;


Timer pump1Timer;
Pump pump1(r1Pin, pumpDuration, pumpDelay);

Timer pump2Timer;
Pump pump2(r2Pin, pumpDuration, pumpDelay);


// Outputs device status: <active> / <scheduled> / <next-event>
void displaySerial()
{

    Serial.println("");
    sprintf(dtm, "%02d/%02d/%02d %02d:%02d" , dt.day(),dt.month(),dt.year(),dt.hour(),dt.minute());
    Serial.println(dtm);

    // LAMP 1
    Serial.print(F("Lamp1: "));
    if (lamp1.isActive())
    {
      Serial.print("1");
    } else {
      Serial.print("0");
    }

    Serial.print(F(" / "));

    if (lamp1.timer.isScheduled(dt.hour()))
    {
      Serial.print("1");
    } else {
      Serial.print("0");
    }

    Serial.print(F(" / "));

    nextEvent = lamp1.timer.getNextEvent(dt.hour());
    sprintf(buf,"%02d",nextEvent);
    Serial.print(buf);
    Serial.println(":00");

    // PUMP 1
    Serial.print(F("Pump1: "));
    if (pump1.isActive())
    {
      Serial.print("1");
    } else {
      Serial.print("0");
    }

    Serial.print(F(" / "));

    if (pump1.timer.isScheduled(dt.hour()))
    {
      Serial.print("1");
    } else {
      Serial.print("0");
    }

    Serial.print(F(" / "));

    nextEvent = pump1.timer.getNextEvent(dt.hour());
    sprintf(buf,"%02d",nextEvent);
    Serial.print(buf);
    Serial.println(":00");

    // PUMP 2
    Serial.print(F("Pump2: "));
    if (pump2.isActive())
    {
      Serial.print("1");
    } else {
      Serial.print("0");
    }

    Serial.print(F(" / "));

    if (pump2.timer.isScheduled(dt.hour()))
    {
      Serial.print("1");
    } else {
      Serial.print("0");
    }

    Serial.print(F(" / "));

    nextEvent = pump2.timer.getNextEvent(dt.hour());
    sprintf(buf,"%02d",nextEvent);
    Serial.print(buf);
    Serial.println(":00");

}


void setup() {

  Serial.begin(115200);

  Wire.begin();
  Wire.setClock(400000L);

  rtc.begin();
  dt = rtc.now();
  DateTime arduino_t = DateTime(__DATE__, __TIME__);

  // sync RTC w/ arduino time @ compile time
  if (dt.unixtime() != arduino_t.unixtime())
  {
    rtc.adjust(arduino_t.unixtime());
  }

  // setup GPIO pins
  pinMode(r1Pin, OUTPUT);
  digitalWrite(r1Pin, HIGH);
  pinMode(r2Pin, OUTPUT);
  digitalWrite(r2Pin, HIGH);
  pinMode(r3Pin, OUTPUT);
  pinMode(r3Pin, HIGH);

  // init device timers

  // Lamp1 timer activates at specific hours recurring every day
  lamp1Timer.init(TIMER_HOUR_OF_DAY, &lamp1TimerBitmask);
  lamp1.initTimer(lamp1Timer);

  // Pump1 timer activates at specific hours on specific weekdays only
  pump1Timer.init(TIMER_HOUR_OF_DAY, &pumpTimerHourBitmask, &pump1DayOfWeekBitmask);
  pump1.initTimer(pump1Timer);

  // Pump2 timer activates at specific hours on specific days of month
  pump2Timer.init(TIMER_HOUR_OF_DAY, &pumpTimerHourBitmask, &pump2DayOfMonthBitmask);
  pump2.initTimer(pump2Timer);

}


void loop() {

  // check schedule & activate/deactivate timed devices
  dt = rtc.now();

  if (lampEnabled)
  {
    lamp1.update(dt.unixtime());
  }

  if (pumpEnabled)
  {
    pump1.update(dt.unixtime());
    pump2.update(dt.unixtime());
  }

}
