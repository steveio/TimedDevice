/**

Timer.h

Timer serves to provide a schedule for device activation / deactivation
by defining periods when a device is on or off

This version implements bitmask based timer strategy
Granularity is hour (of day) and day (of week or month) unit

Timer is recurring and repeats every day or for specified days only

Todo -




Link - https://github.com/steveio/TimedDevice
Copyright (C) 2020  Steven G Edwards

*/

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include <stddef.h>
#include <math.h>

#if !defined(__time_t_defined) // avoid conflict with newlib or other posix libc
typedef unsigned long time_t;
#endif


/* Useful Macros for converting elapsed time to a time_t */
#define SECS_PER_MIN  ((time_t)(60UL))
#define SECS_PER_HOUR ((time_t)(3600UL))
#define SECS_PER_DAY  ((time_t)(SECS_PER_HOUR * 24UL))


// BITMASK TIMER TYPES - Precision of 1 Hour Intervals
// Recurring Hour and (optionally) Day of Week or Day of Month
#define TIMER_HOUR_OF_DAY 0x02
#define TIMER_DAY_OF_WEEK 0x04
#define TIMER_DAY_OF_MONTH 0x06


// TIME BASED TIMER - Specify On times minute precision
#define TIMER_MINUTE 0x16


#define CALLBACK_ARR_SZ  4

// timer event callbacks
#define CALLBACK_TIMER_INIT  4
#define CALLBACK_TIMER_ACTIVE  3
#define CALLBACK_TIMER_TIMEOUT  2

typedef void (*pt2Function)();


// time element - HH:MM (Hour must be specified as 24 hour clock)
typedef struct tmElements_t {
  uint8_t Sec;
  uint8_t Min;
  uint8_t Hour;
  //uint8_t Day;
  //uint8_t Month;
  //uint8_t Year;   // offset from 1970;
};

#define SZ_TIME_ELEMENT 3

// container for n pairs of on/off times
typedef struct tmElementArray_t {
  size_t n;
  int Wday;   // bitmap - days of week (bit index 0 = Sun -> 6 Sat)
  struct tmElements_t onTime[SZ_TIME_ELEMENT];
  struct tmElements_t offTime[SZ_TIME_ELEMENT];
};


class Timer {
    public:

      Timer();

      // initialise a timer (hour/day of week bitmask or on time),
      // then check timer status by calling isScheduled()
      void init(int type, long * h);
      void init(int type, long * h, long * d);
      void init(int type, struct tmElementArray_t * onTime);

      bool isScheduled(int h);
      bool isScheduled(int h, int d);
      bool isScheduled(int m, int h, int d);
      bool isScheduled(unsigned long ts);


      // schedule a callback event -
      // recursively call a function (or class method wrapped in a function) according to a timer schedule

      // recurring timer (every day at specific time)
      bool schedule(unsigned long ts, struct tmElementArray_t * onTime, void (*function)(void));
      // recurring timer (specific weekdays at specific time
      bool schedule(unsigned long ts, struct tmElementArray_t * onTime, long * d, void (*function)(void));

      struct tmElementArray_t * getTimeArray();
      int getType();

      // return time of next on/off event from an hour bitmask timer definition
      int getNextEvent(int h, bool type = NULL);
      //void printSchedule();

      // given a timestamp return hour (relative to unix epoch GMT)
      int getHourGMTFromTS(unsigned long ts);
      int getDayOfWeekFromTS(unsigned long ts);

      void setCallback(pt2Function ptCallback, const int idx)
      {
        _callbackArr[idx] = ptCallback;
      		//this->function_callback = function;
    	}

      // set timer active time (millisecs)
      void setDuration(unsigned long t);

    protected:

      // Timer type: Hour of Day + (optionally) Day of Week OR Day or Month
      int _type;

      // Timer 32 bit bitmask defines hours (from 24h clock) on / off
      // 0b 00000000 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
      long * _timerHour;

      // Timer bit bitmask defines days of week, bits (0 - 6 Sun - Sat)
      // 0b 00000000000000000000000000000 6 5 4 3 2 1 0
      long * _timerDayOfWeek;

      // Timer 32 bit bitmask defines days of month
      // 0b 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
      long * _timerDayOfMonth;

      // Array specifying 1..n on times
      struct tmElementArray_t * _timeArray;

      bool _checkBitSet(int n, long * l);

      virtual void call(const int idx);

      int _callbackArrIdx = CALLBACK_ARR_SZ;
      pt2Function _callbackArr[CALLBACK_ARR_SZ] = {NULL};

      bool _active = false; // timer status
      unsigned long _lastActivation = 0; // timestamp of last activation
      unsigned long  _duration = 0;     // (optional) timer active duration

    private:
        bool _checkTimer(int m, int h, int d);
        bool _checkTimeArray(unsigned long ts);
        bool _checkDayOfWeek(int d);
        void _setBit(int n);


};


// TimerClassTemplate<MyClass> timer(&instance, &MyClass::callMethod);

template <class Obj>

class TimerClassTemplate: public Timer {
public:
	TimerClassTemplate(Obj *object, void (Obj::*callback)(void)) {
		this->object = object;
		this->method = callback;
	}

	virtual void call() {
		return (object->*method)();
	}

private:
	Obj *object;
	void (Obj::*method)(void);
};
#endif
