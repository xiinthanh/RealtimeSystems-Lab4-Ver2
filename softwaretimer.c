#include "softwaretimer.h"

int timer_counter[MAX];
int timer_flag[MAX];

#ifdef __cplusplus
extern "C"
{
#endif

void setTimer(int index, int _counter)
{
    timer_counter[index] = _counter;
    timer_flag[index] = 0;
}

int isTimerExpired(int index)
{
  if (timer_flag[index] == 1)
  {
    timer_flag[index] = 0;
    return 1;
  }
  return 0;
}

void timerRun()
{
    for (int i = 0; i < MAX; i++)
    {
        if (timer_counter[i] > 0)
        {
            timer_counter[i]--;
            if (timer_counter[i] == 0)
                timer_flag[i] = 1;
        }
    }
}


#ifdef __cplusplus
}
#endif