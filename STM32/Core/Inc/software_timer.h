/*
 * software_timer.h
 */
#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

/* Shared between TIM2 interrupt and main loop. */
extern volatile int timer_flag;
extern volatile int timer_counter;
extern int TIMER_CYCLE;

void setTimer(int duration);
void timerRun(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
