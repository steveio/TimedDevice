
#include "Pump.h"
#include "Relay.h"


Timer lamp1Timer;
// Timer 32 bit bitmask defines hours (from 24h hours) device is on | off
// 0b 00000000 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
long lamp1TimerBitmask =0b00000000001111111111111111100000;

Timer lamp2Timer;
long lamp2TimerBitmask =0b00000011111000000000011111100000;
// day of week (bit index 0 = Sunday - 6 Saturday)
long lamp2TimerDayOfWeekBitmask = 0b0101010;


Timer lamp3Timer;
long lamp3TimerBitmask =0b00000011111000000000011111100000;
// day(s) of month 0-31
long lamp3TimerDayOfMonthBitmask =0b01111111100000000111111110000000;


#define SZ_TIME_ELEMENT 3

Timer lamp4Timer;
// create variables to define on/off time pairs
struct tmElements_t t1_on, t1_off, t2_on, t2_off, t3_on, t3_off;
struct tmElementArray_t timeArray;


Relay lamp1(12);
Relay lamp2(13);
Relay lamp3(14);
Relay lamp4(15);



// Pump1 (GPIO 10) - 6 Activations  / Duration (Timeout) 30 secs
Timer pump1Timer;
long pump1TimerBitmask =0b00000000001110000000000011100000;
Pump pump1(10, 30000);



void setup() {

  Serial.begin(115200);

  lamp1Timer.init(TIMER_HOUR_OF_DAY, &lamp1TimerBitmask);
  lamp1.initTimer();

  lamp2Timer.init(TIMER_DAY_OF_WEEK, &lamp1TimerBitmask, &lamp2TimerDayOfWeekBitmask);
  lamp2.initTimer(lamp2Timer);

  lamp3Timer.init(TIMER_DAY_OF_MONTH, &lamp3TimerBitmask, &lamp3TimerDayOfMonthBitmask);
  lamp3.initTimer(lamp3Timer);


  // On/Off times and DayOfWeek
  t1_on.Hour = 9;
  t1_on.Min = 0;
  t1_off.Hour = 9;
  t1_off.Min = 10;

  t2_on.Hour = 17;
  t2_on.Min = 0;
  t2_off.Hour = 17;
  t2_off.Min = 10;

  timeArray.n = 2;
  timeArray.Wday = 0b11111111; // define which days of week timer is active on

  timeArray.onTime[0] = t1_on;
  timeArray.offTime[0] = t1_off;
  timeArray.onTime[1] = t2_on;
  timeArray.offTime[1] = t2_off;

  lamp4Timer.init(TIMER_MINUTE, &timeArray);
  lamp4.initTimer(lamp4Timer);

  /*
  lamp1Timer.init(TIMER_HOUR_OF_DAY, &lamp1TimerBitmask);
  lamp1.initTimer(lamp1Timer);

  pump1Timer.init(TIMER_HOUR_OF_DAY, &pump1TimerBitmask);
  pump1.initTimer(pump1Timer);

  pump2Timer.init(TIMER_HOUR_OF_DAY, &pump2TimerBitmask);
  pump2.initTimer(pump2Timer);
  */

}


void loop() {

  bool isActive, uled;

  Serial.println("Lamp1 schedule: ");
  lamp1.timer.printSchedule(Serial);

  Serial.println("Lamp2 schedule: ");
  lamp2.timer.printSchedule(Serial);


  /*
  Serial.print("Pump1 Status: ");
  Serial.println(pump1.isActive());

  Serial.println("Pump2 Status: ");
  Serial.println(pump2.isActive());

  Serial.println("Lamp1 Status: ");
  Serial.println(lamp1.isActive());

  Serial.println("Pump1 schedule: ");
  pump1.timer.printSchedule(Serial);
  */

  // check device status at time when schedule is "on"

  Serial.println("Lamp1 isScheduled 09:00 ");
  Serial.println(lamp1.timer.isScheduled(9, NULL));

  Serial.println("Lamp2 isScheduled Mon 09:00 ");
  Serial.println(lamp2.timer.isScheduled(9, 1));

  Serial.println("Lamp3 isScheduled Month 8th day (08/MM)  09:00 ");
  Serial.println(lamp3.timer.isScheduled(9, 8));

  Serial.println("Lamp4 isScheduled 09:05 Mon ");
  Serial.println(lamp4.timer.isScheduled(5, 9, 1));

  Serial.println("Lamp4 isScheduled 17:05 Tue ");
  Serial.println(lamp4.timer.isScheduled(5, 17, 2));

  // check device status at time when schedule is "off"

  Serial.println("Lamp1 isScheduled 02:00 ");
  Serial.println(lamp1.timer.isScheduled(2, NULL));

  Serial.println("Lamp2 isScheduled Tue 09:00 ");
  Serial.println(lamp2.timer.isScheduled(9, 2));

  Serial.println("Lamp3 isScheduled Month day 03 (03/MM)  09:00 ");
  Serial.println(lamp3.timer.isScheduled(9, 3));

  Serial.println("Lamp4 isScheduled 08:0 Mon ");
  Serial.println(lamp4.timer.isScheduled(0, 8, 1));




  delay(5000);
}
