Arduino Timed Device Library

Simple & lightweight timer based scheduling for on/off devices

Supports recurring timers:

Bitmap timers w/ hour precision
On time + Duration w/ timeout
On/Off timers w/ hour and minute precision
Day of Week/Month scheduling
Device classes extend a base class TimedDevice. Timer class defines a schedule for when a device is on/off

class maintains attributes to track number of activations, time of last activation.

Device classes (lamps, pumps etc) extend TimedDevice implementing required domain specific functionality.

Supported on Arduino & ESP8266/32 microcontroller platforms

Optimisation is for low memory ATMega328p devices, typical sketch memory useage for a single device is 1.7k to 4k for a complex sketch with multiple devices.

Overview

This library was written to emulate a simple plug in timer for an electrical device, where pins in a ring are set to define hour/minute device status.

Arduino ATMega328 and related embedded microcontrollers provide internal high precision clock based timers suitable for events with second, millisecond and fine granularity (upto 8 / 16 mhz).

Cases where lower precision is required, recurring timers for example, where an event should occur on a specific minute, hour or day of week, can be achieved with a lightweight implementation.  Storage for internal data structures can be optimised, a significant win factor on embedded systems where memory use is constrained.

Example use cases:

- Switch lights or any electrical relay device on/off
- Activate a pump or valve
- Open/Close blinds, curtains or shutters
- Control a fan, heat source or air conditioning

In C time.h the tm structure has the following definition −

struct tm {
   int tm_sec;         /* seconds,  range 0 to 59          */
   int tm_min;         /* minutes, range 0 to 59           */
   int tm_hour;        /* hours, range 0 to 23             */
   int tm_mday;        /* day of the month, range 1 to 31  */
   int tm_mon;         /* month, range 0 to 11             */
   int tm_year;        /* The number of years since 1900   */
   int tm_wday;        /* day of the week, range 0 to 6    */
   int tm_yday;        /* day in the year, range 0 to 365  */
   int tm_isdst;       /* daylight saving time             */
};

While this structure is useful for point in time defined events, in case of a recurring timers this can be simplified.

If hour precision is sufficient, a single 32 bit mask can be used:

// Bitmask defines hours (from 24h hours) device is on (1) or off (0)
// 0b 00000000 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
long hourTimerBitmask =0b00000000001111111111111111100000;

Day of week (bit index 0 = Sunday - 6 Saturday) can be defined similarly:

long dayOfWeekTimerBitmask = 0b0101010;

With bitmasks we can determine if an event is scheduled using bit shifts:

// Check if bit at pos n is set in 32bit long l
bool Timer::_checkBitSet(int n, long * l)
{
  bool b = (*l >> (long) n) & 1U;
  return b;
}

To check if an hour timer bitmask is on/off for 7am:

bool isSet = _checkBitSet(7, hourTimerBitmask)

An on / off time occuring at specific (hour:minute) intervals can be defined as:

typedef struct tmElements_t {
  uint8_t Min;
  uint8_t Hour;
};

We can use a struct as container for n pairs of on/off times occuring on specified weekdays:

#define SZ_TIME_ELEMENT 2

typedef struct tmElementArray_t {
  unsigned long Wday;   // bitmap - days of week (bit index 0 = Sun - 6 Sat)
  struct tmElements_t onTime[SZ_TIME_ELEMENT];
  struct tmElements_t offTime[SZ_TIME_ELEMENT];
};

Setting up a single on/off time configuration is then:

t1_on.Hour = 8;
t1_on.Min = 0;
t1_off.Hour = 8;
t1_off.Min = 10;

t2_on.Hour = 19;
t2_on.Min = 0;
t2_off.Hour = 19;
t2_off.Min = 10;

timeArray1Cycle.n = 1; // number of time pairs
timeArray1Cycle.Wday = 0b01111111; // define which days of week timer is active on

timeArray1Cycle.onTime[0] = t1_on;
timeArray1Cycle.offTime[0] = t1_off;

Check if a recurring timer is set

How we check a timer (whether bitmask or time based) depends on the type of time source we have.  

Most familiar time source on Arduino is millis() function providing elapsed time in milliseconds since device reset / startup.

While this can be useful for timing events at recurring intervals:

if (millis() >= sampleTimer + sampleInterval)
{
  ... do something
  sampleTimer = millis();
}

More typically micrcontroller is combined with a Real Time Clock, providing a battery backed timesource or current time.

In C function overloading can be used to provide multiple interfaces to an isScheduled() method according to timer precision / time source type :

bool isScheduled(int h);
bool isScheduled(int h, int d);
bool isScheduled(int m, int h, int d);
bool isScheduled(unsigned long ts);

(Where h = hour, m = minute, d = week day)

Most users of Unix based systems are familiar with timestamp representing elapsed seconds since a fixed point in time, the Unix Epoch which occured 1970-01-01 00:00:00 UTC.

We can obtain this on Linux via command line with date command:

stevee@ideapad-530S:~$ date +%s
1620155520

Arduino DS1307/3231 RTC modules have supporting libraries to set and obtain current time usually in form of:

DateTime now = rtc.now();

Where DateTime object provides an API to return specific time elements:

Serial.print(now.hour());
Serial.print(':');
Serial.println(now.minute());
Serial.print(now.dayOfTheWeek());

So havin current timestamp, how can we check if an event is scheduled to occur?

The first question might be how to obtain weekday (from elapsed seconds since epoch)?

int weekday = (floor((ts / 86400)) + 4) % 7;

1970-01-01 was a Thursday, dividing timestamp by 86400 (number of seconds in a day: 24 * 60 * 60) gives number of days since epoch, adding 4 shifts start day to Sun and modulo 7 returns day of week.

To check a timestamp within range of an on/off time pair specified in hh:mm format (as uint8_t Min; uint8_t Hour;) first we convert to elapsed seconds.

// convert fully qualified timestamp to elapsed secs from previous midnight
unsigned long elapsedTime = ts % SECS_PER_DAY;

unsigned long s1, s2, onTime, offTime;

// check each timeArray on/off pair
for (int i = 0; i < _timeArray->n; i++)
{
  s1 = _timeArray->onTime[i].Min * SECS_PER_MIN;
  s2 = _timeArray->onTime[i].Hour * SECS_PER_HOUR;
  onTime = s1 + s2;
  s1 = _timeArray->offTime[i].Min * SECS_PER_MIN;
  s2 = _timeArray->offTime[i].Hour * SECS_PER_HOUR;
  offTime = s1 + s2;

  if (elapsedTime >= onTime && elapsedTime <= offTime)
  {
    return true;
  }
}
