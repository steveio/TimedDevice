#include <stdlib.h>
#include <stdio.h>
#include <sys/timeb.h>

#include <Timer.h>
#include <RecurringTimer.h>


using namespace std;

timeb t_start;
RecurringTimer timer;

unsigned long millis() {
  timeb t_now;
  ftime(&t_now);
  return (t_now.time  - t_start.time) * 1000 + (t_now.millitm - t_start.millitm);
}

void delay(unsigned long ms) {
  unsigned long start = millis();
  while(millis() - start < ms){}
}


void setup()
{
  printf("RecurringTimer test\n");

  struct tmElements_t t1_on;

  t1_on.Hour = 9;
  t1_on.Min = 0;
  t1_on.Sec = 0;

  unsigned long ts = millis() / 1000;
  unsigned long interval = 1000 * 5;

  //timer.init(TIMER_MILLIS_RECURRING, ts, &t1_on, interval);


  timer.init(TIMER_MILLIS_RECURRING, ts, interval);

  // init as object pointer
  //RecurringTimer* timer = new RecurringTimer();
  //timer->init(TIMER_MILLIS_RECURRING, ts, &t1_on, interval);

}

void loop()
{
  printf("timer.update()...\n");

  unsigned long ts = millis() / 1000;

  if (timer.update(ts))
  {
    printf("Active\n");
  }

  delay(1000);
}

int main()
{
  setup();

  while(1)
  {
    loop();
  }

}
