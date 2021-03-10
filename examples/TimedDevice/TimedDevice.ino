
#include "Pump.h"
#include "Relay.h"


Timer lamp1Timer;
// hour of day (bit index 0 = 00:00 )
long lamp1TimerBitmask =0b00000000001111111111111111100000;

Timer lamp2Timer;
// hour of day (bit index 0 = 00:00 )
long lamp2TimerBitmask =0b00000011111000000000011111100000;
// day of week (bit index 0 = Sunday - 6 Saturday)
long lamp2TimerDayOfWeekBitmask = 0b0101010;


Timer lamp3Timer;
// hour of day (bit index 0 = 00:00 )
long lamp3TimerBitmask =0b00000011111000000000011111100000;
// day(s) of month 0-31
long lamp3TimerDayOfMonthBitmask =0b01111111100000000111111110000000;


Relay lamp1(12);
Relay lamp2(13);
Relay lamp3(14);


Timer pump1Timer;
long pump1TimerBitmask =0b00000000001110000000000111100000;
Pump pump1(10, 30000, 300000);

Timer pump2Timer;
long pump2TimerBitmask =0b00000000000000000000000111110000;
Pump pump2(11, 50000, 5000000);


void setup() {

  Serial.begin(115200);

  lamp1Timer.init(TIMER_HOUR_OF_DAY, &lamp1TimerBitmask);
  lamp1.initTimer(lamp1Timer);

  lamp2Timer.init(TIMER_DAY_OF_WEEK, &lamp1TimerBitmask, &lamp2TimerDayOfWeekBitmask);
  lamp2.initTimer(lamp2Timer);

  lamp3Timer.init(TIMER_DAY_OF_MONTH, &lamp3TimerBitmask, &lamp3TimerDayOfMonthBitmask);
  lamp3.initTimer(lamp3Timer);

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

  bool isActive, isScheduled;

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

  Serial.println("Lamp3 isScheduled Month day 08 (08/MM)  09:00 ");
  Serial.println(lamp3.timer.isScheduled(9, 8));

  // check device status at time when schedule is "off"

  Serial.println("Lamp1 isScheduled 02:00 ");
  Serial.println(lamp1.timer.isScheduled(2, NULL));

  Serial.println("Lamp2 isScheduled Tue 09:00 ");
  Serial.println(lamp2.timer.isScheduled(9, 2));

  Serial.println("Lamp3 isScheduled Month day 03 (03/MM)  09:00 ");
  Serial.println(lamp3.timer.isScheduled(9, 3));


  /*
  Serial.println("Pump1 isScheduled 19:00: ");
  Serial.println(pump1.timer.isScheduled(19, NULL));

  Serial.println("Pump1 isScheduled 02:00: ");
  Serial.println(pump1.timer.isScheduled(2, NULL));
  */


  delay(5000);
}
