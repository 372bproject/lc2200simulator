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
//typedef struct cpu_ALU_type {
//    int operand_A;
//    int operand_B;
//    enum operation applied_operation;
//    int output;
//} ALU;
//typedef ALU * ALU_p;

/* Prototypes */
void add (REGISTER_STR_p, REGISTER_STR_p, REGISTER_STR_p);
void addi (REGISTER_STR_p, REGISTER_STR_p, REGISTER_STR_p); //char offset field ( 5 bit 2's compliment ) loaded into $a0 (last REGISTER_STR_p in arguments)
void sub (REGISTER_STR_p, REGISTER_STR_p, REGISTER_STR_p);
void and_operation (REGISTER_STR_p, REGISTER_STR_p, REGISTER_STR_p);
void not_operation (REGISTER_STR_p, REGISTER_STR_p, REGISTER_STR_p);
void sw (REGISTER_STR_p, REGISTER_STR_p, REGISTER_STR_p);
void lw (REGISTER_STR_p, REGISTER_STR_p, REGISTER_STR_p);
void beq (REGISTER_STR_p, REGISTER_STR_p, REGISTER_STR_p); //arguments = PC, operand_A, operand_B
void jalr (REGISTER_STR_p, REGISTER_STR_p); //arguments = register with jumped to address, return addres register (current pc)
void ret (REGISTER_STR_p); //argument = pc
void reti (REGISTER_STR_p); //argument = pc
void halt ();
void nop ();

#endif /* ALU_H_ */
