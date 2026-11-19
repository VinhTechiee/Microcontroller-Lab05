/*
 * software_timer.c
 */
#include "software_timer.h"

volatile int timer_flag = 0;
volatile int timer_counter = 0;
int TIMER_CYCLE = 10;

void setTimer(int duration)
{
    if (duration <= 0) {
        timer_counter = 0;
        timer_flag = 1;
        return;
    }

    timer_flag = 0;
    timer_counter = (duration + TIMER_CYCLE - 1) / TIMER_CYCLE;
}

void timerRun(void)
{
    /* Stop at zero; do not let the counter underflow. */
    if (timer_counter > 0) {
        timer_counter--;

        if (timer_counter == 0) {
            timer_flag = 1;
        }
    }
}
