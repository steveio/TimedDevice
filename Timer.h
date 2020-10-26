/**

Timer.h

Timer serves to provide a schedule for device activation / deactivation
by defining periods when a device is on or off

This version implements bitmask based timer strategy
Granularity is hour (of day) and day (of week or month) unit

Timer is recurring and repeats every day or for specified days only

*/

#ifndef TIMER_H_
#define TIMER_H_

#include <Arduino.h>


// timer type - Hour of Day and (optionally) Day of Week or Day of Month
#define TIMER_HOUR_OF_DAY 0
#define TIMER_DAY_OF_WEEK 1
#define TIMER_DAY_OF_MONTH 2


class Timer {
    public:

      Timer();
      void init(int type, long * h);
      bool isScheduled(int h, int d);
      void printSchedule(Stream &s);
      int getNextEvent(int h);

    protected:

      // Timer type: Hour of Day + (optionally) Day of Week OR Day or Month
      int type;

      // Timer 32 bit bitmask defines hours (from 24h clock) on / off
      // 0b 00000000 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
      long * timerHour;

      // Timer bit bitmask defines days of week, bits (0 - 6 Sun - Sat)
      // 0b 00000000000000000000000000000 6 5 4 3 2 1 0
      long * timerDayOfWeek;

      // Timer 32 bit bitmask defines days of month
      // 0b 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
      long * timerDayOfMonth;

    private:
        bool checkBitSet(int n, long * l);
        void setBit(int n);
};

#endif
