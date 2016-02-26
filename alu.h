/*
 * alu.h
 *
 *  Created on: Jan 26, 2016
 *      Author: Ray Kim
 */

#ifndef ALU_H_
#define ALU_H_

#include "register.h"

/* CPU_ALU
 *
 */
typedef struct cpu_ALU_type {
    REGISTER_STR_p A;
    REGISTER_STR_p B;
    REGISTER_STR_p output;
} ALU_STR;
typedef ALU_STR * ALU_p;

//stack overflow 8562694
typedef void (*functionPtr) (ALU_p);

/* Prototypes */
ALU_p ALU_constructor (void);
void ALU_destructor (ALU_p);

void ALU_add (ALU_p);
void ALU_nand (ALU_p);
void ALU_sub (ALU_p);


void ALU_sw (ALU_p);
void ALU_lw (ALU_p);
void ALU_beq (ALU_p); //arguments = PC, operand_A, operand_B
void ALU_jalr (ALU_p); //arguments = register with jumped to address, return addres register (current pc)
void ALU_ret (ALU_p); //argument = pc
void ALU_reti (ALU_p); //argument = pc
void ALU_halt (ALU_p);
void ALU_nop (ALU_p);

#endif /* ALU_H_ */
