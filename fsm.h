/*
 * fsm.h
 *
 *  Created on: Jan 26, 2016
 *      Author: Ray Kim
 */

#ifndef FSM_H_
#define FSM_H_

#include "register.h"
#include "alu.h"
#include "assembler.h"
#include "fms-micro.h"

typedef struct fsm_str {
    unsigned int pc;
    REGISTER_STR_p zero;
    REGISTER_STR_p at;
    REGISTER_STR_p v0;
    REGISTER_STR_p a1;
    REGISTER_STR_p a2;
    REGISTER_STR_p t0;
    REGISTER_STR_p t1;
    REGISTER_STR_p t2;
    REGISTER_STR_p s0;
    REGISTER_STR_p s1;
    REGISTER_STR_p k0;
    REGISTER_STR_p sp;
    REGISTER_STR_p fp;
    REGISTER_STR_p ra;

    
} FSM_STR;
typedef FSM_STR * FSM_STR_p;

typedef enum instruction {
    ADD,
    NAND,
    ADDI,
    LW,
    SW,
    BEQ,
    JALR,
    HALT,
    SUB,
    EI,
    DI,
    RETI,
    NOOP
} instruction_enum;

typedef void (*functionPtr) (REGISTER_STR_p, REGISTER_STR_p, REGISTER_STR_p);

/* Prototypes */
FSM_STR_p FSM_constructor (void);
void FSM_destructor (FSM_STR_p);
void fetch (FSM_STR_p, unsigned int *, unsigned int);
functionPtr * decode (FSM_STR_p, unsigned int, REGISTER_STR_p, REGISTER_STR_p, REGISTER_STR_p); //opcode
void execute (functionPtr, REGISTER_STR_p, REGISTER_STR_p, REGISTER_STR_p);
void interruptCheck (functionPtr); //

#endif /* FSM_H_ */
