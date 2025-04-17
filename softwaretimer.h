
#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define MAX 10

#ifdef __cplusplus
extern "C"
{
#endif


int isTimerExpired(int index);
void setTimer(int index, int _counter);
void timerRun();


#ifdef __cplusplus
}
#endif


#endif /* INC_SOFTWARE_TIMER_H_ */