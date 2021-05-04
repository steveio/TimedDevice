#include <Wire.h>
#include "RTClib.h"
#include "Relay.h" // from TimedDevice

RTC_DS1307 rtc;
DateTime dt;

// Solenoid Valve
#define GPIO_VALVE1 3

Relay valve1(GPIO_VALVE1);

Timer timer;

#define SZ_TIME_ELEMENT 3

struct tmElements_t t1_on, t1_off, t2_on, t2_off, t3_on, t3_off;
struct tmElementArray_t timeArray;


void setup() {

  Serial.begin(115200);

  // setup and sync Real Time Clock (RTC)
  Wire.begin();
  Wire.setClock(400000L);

  if (!rtc.begin())
  {
    Serial.println(F("Could not init RTC"));
    while(1);
  }
  dt = rtc.now();
  DateTime arduino_t = DateTime(__DATE__, __TIME__);

  // sync RTC w/ arduino time (set at sketch upload)
  if (dt.unixtime() != arduino_t.unixtime())
  {
    rtc.adjust(arduino_t.unixtime());
  }

  pinMode(GPIO_VALVE1, OUTPUT);

  // Define On/Off times and DayOfWeek
  t1_on.Hour = 8;
  t1_on.Min = 0;
  t1_off.Hour = 8;
  t1_off.Min = 10;

  t2_on.Hour = 19;
  t2_on.Min = 0;
  t2_off.Hour = 19;
  t2_off.Min = 10;

  timeArray.n = 1;
  timeArray.Wday = 0b01111111; // define which days of week timer is active on

  timeArray.onTime[0] = t1_on;
  timeArray.offTime[0] = t1_off;

  // setup timer
  timer.init(TIMER_MINUTE, &timeArray);

  // set valve timer
  valve1.initTimer(timer);

}

void loop() {

  dt = rtc.now();
  
  if (valve1.timer.isScheduled(dt.unixtime()))
  {
    Serial.println(F("Valve:\t on"));
    valve1.on();
  } else {
    Serial.println(F("Valve:\t off"));
    valve1.off();
  }

}
