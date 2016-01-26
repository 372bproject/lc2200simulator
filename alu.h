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
void add (register_p, register_p, register_p);
void addi (register_p, register_p, REGISTER_p); //char offset field ( 5 bit 2's compliment ) loaded into $a0 (last REGISTER_p in arguments)
void sub (register_p, register_p, register_p);
void and_operation (register_p, register_p, register_p);
void not_operation (register_p, register_p, register_p);
void sw (register_p, register_p, register_p);
void lw (register_p, register_p, register_p);
void beq (register_p, register_p, register_p); //arguments = PC, operand_A, operand_B
void jalr (register_p, register_p); //arguments = register with jumped to address, return addres register (current pc)
void ret (register_p); //argument = pc
void reti (register_p); //argument = pc
void halt ();
void nop ();

#endif /* ALU_H_ */
