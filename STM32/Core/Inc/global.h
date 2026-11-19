/*
 * global.h
 */
#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

#define MAX_BUFFER_SIZE 30

/* Shared between UART interrupt and main loop. */
extern volatile uint8_t buffer[MAX_BUFFER_SIZE];
extern volatile uint8_t buffer_head;
extern volatile uint8_t buffer_tail;

extern int isOK;
extern int isRST;

#endif /* INC_GLOBAL_H_ */
