
#include "Pump.h"
#include "Relay.h"


Timer pump1Timer;
long pump1TimerBitmask =0b00000000001110000000000111100000;
Pump pump1(10, 30000, 300000);

Timer pump2Timer;
long pump2TimerBitmask =0b00000000000000000000000111110000;
Pump pump2(11, 50000, 5000000);


Timer lamp1Timer;
long lamp1TimerBitmask =0b00000000001111111111111111100000;


Relay lamp1(12);


void setup() {

  Serial.begin(115200);
  
  pump1Timer.init(TIMER_HOUR_OF_DAY, &pump1TimerBitmask);
  pump1.initTimer(pump1Timer);

  pump2Timer.init(TIMER_HOUR_OF_DAY, &pump2TimerBitmask);
  pump2.initTimer(pump2Timer);

  lamp1Timer.init(TIMER_HOUR_OF_DAY, &lamp1TimerBitmask);
  lamp1.initTimer(lamp1Timer);

}


void loop() {

  bool isActive, isScheduled;

  Serial.print("Pump1 Status: ");
  Serial.println(pump1.isActive());

  Serial.println("Pump2 Status: ");
  Serial.println(pump2.isActive());

  Serial.println("Lamp1 Status: ");
  Serial.println(lamp1.isActive());

  Serial.println("Pump1 schedule: ");
  pump1.timer.printSchedule(Serial);

  Serial.println("Lamp1 schedule: ");
  lamp1.timer.printSchedule(Serial);

  // check device status at time when schedule is "on"

  Serial.println("Pump1 isScheduled 19:00: ");
  Serial.println(pump1.timer.isScheduled(19, NULL));

  Serial.println("Lamp1 isScheduled 09:00: ");
  Serial.println(lamp1.timer.isScheduled(9, NULL));

  // check device status at time when schedule is "off"

  Serial.println("Pump1 isScheduled 02:00: ");
  Serial.println(pump1.timer.isScheduled(2, NULL));

  Serial.println("Lamp1 isScheduled 02:00: ");
  Serial.println(lamp1.timer.isScheduled(2, NULL));


  delay(5000);
}
