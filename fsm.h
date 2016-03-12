/*
 * fsm.h
 *
 *  Created on: Jan 26, 2016
 *      Author: Ray Kim
 */

#ifndef FSM_H_
#define FSM_H_

#define MEMORY_SIZE 5000

#include "register.h"
#include "alu.h"
#include "assembler.h"

#include "memory.h"

typedef struct fsm_str {
    REGISTER_STR_p zero;
    REGISTER_STR_p at;
    REGISTER_STR_p v0;
    REGISTER_STR_p a0;
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
    unsigned int pc;
    
//    REGISTER_STR_p pc;

    
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



/* Prototypes */
FSM_STR_p FSM_constructor (void);
void FSM_destructor (FSM_STR_p);
unsigned int fetch (unsigned int *, unsigned int);
void decode (FSM_STR_p, unsigned int *, unsigned int, ALU_p); //opcode
void interruptCheck (functionPtr); //
void printAllRegisters(FSM_STR_p);

#endif /* FSM_H_ */
