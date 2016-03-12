/*
 * fsm-micro.h
 *
 *  Created on: Feb 17, 2016
 *      Author: Abdul Fiqi, Ray Kim
 */

#ifndef FSM_MICRO_H_
#define FSM_MICRO_H_

#include "fsm.h"
#include "alu.h"
#include "memory.h"

extern unsigned int EXTERN_GLOBAL_MICRO_STATES[][7];

/* prototypes */
unsigned int FSM_MICRO_execute (FSM_STR_p, unsigned int *, functionPtr, unsigned int, unsigned int, ALU_p);


















#endif /* FSM_MICRO_H_ */