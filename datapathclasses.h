/*
 * datapathclasses.h
 *
 *  Created on: Jan 25, 2016
 *      Author: Ray Kim
 */

#ifndef DATAPATHCLASSES_H_
#define DATAPATHCLASSES_H_

/* Supported operations
 *
 */
enum operation {add, sub, and, not, sw, lw, lea, beq, ret, halt, nop};

/* CPU_register
 *
 */
typedef struct cpu_register_type {
    char reg_name[5];
    unsigned int reg_value;     /* stores value held within register */
} cpu_register;
typedef cpu_register * cpu_register_p;

/* CPU_memory
 *
 */
typedef struct cpu_memory_module_type {
    unsigned int MAR;
    unsigned int MDR;
} cpu_memory_module;
typedef cpu_memory_module * cpu_memory_module_p;

/* CPU_ALU
 *
 */
typedef struct cpu_ALU_type {
    unsigned int operand_A;
    unsigned int operand_B;
    enum operation applied_operation;
    unsigned int output;
} cpu_ALU;
typedef cpu_ALU * cpu_ALU_p;

/* Prototypes */


#endif /* DATAPATHCLASSES_H */
