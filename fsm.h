/*
 * fsm.h
 *
 *  Created on: Jan 26, 2016
 *      Author: Ray Kim
 */

#ifndef FSM_H_
#define FSM_H_

#include "memory.h"
#include "register.h"
#include "alu.h"
#include "interrupts.h"

typedef void (*functionPtr) (REGISTER_STR_p, REGISTER_STR_p, REGISTER_STR_p);

/* Prototypes */
void fetch (MEMORY_MODULE_STR_p);
functionPtr * decode (unsigned int, REGISTER_STR_p, REGISTER_STR_p, REGISTER_STR_p); //opcode, output register, operandA, operandB, returns pointer to function
void execute (functionPtr, unsigned int *, unsigned int *, unsigned int *); //function to be executed, and three arguments to functions, which are absolute addresses


#endif /* FSM_H_ */
