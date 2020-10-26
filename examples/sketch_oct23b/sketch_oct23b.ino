
#include "TimedDevice.h"


Timer timer();
TimedDevice timedDevice();


void setup() {

  long timerHour = 0b00000000000000000000000000000000;

  timer::init(TIMER_HOUR_OF_DAY, timerHour, null);
  timedDevice::initTimer(timer);#


}

void loop() {
  // put your main code here, to run repeatedly:

}
