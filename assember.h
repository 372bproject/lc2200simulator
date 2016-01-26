/*
 * assembler.h
 *
 *  Created on: Jan 26, 2016
 *      Author: Ray Kim
 */

#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

/* Supported operations
 *
 */
static char * operations[] = {
    "add\0", //0000
    "not\0", //0001
    "addi", //0010
    "lw\0\0", //0011
    "sw\0\0", //0100
    "beq\0", //0101
    "jalr", //0110
    "halt", //0111
    "sub\0", //1000
    "and\0", //1001
    "ret\0", //1010
    "reti", //1011
    "sub\0", //1100
    "nop\0" //1101
    
} //note: each string is 5 bytes long, \0 may be automatically added to end of each string

static char * registers[] = {
    "zero", //0000
    "at\0\0", //0001
    "v0\0\0", //0010
    "a0\0\0", //0011
    "a1\0\0", //0100
    "a2\0\0", //0101
    "t0\0\0", //0110
    "t1\0\0", //0111
    "t2\0\0", //1000
    "s0\0\0", //1001
    "s1\0\0", //1010
    "k0\0\0", //1011
    "sp\0\0", //1100
    "fp\0\0", //1101
    "ra\0\0" //1101
}

//inner class
typedef struct node_str {
    struct node_str * next_node;
    char * label_p;
    unsigned int label_address;
    
} NODE_STR;
typedef NODE_STR * NODE_STR_p;

/* CPU_assembler
 *
 */
typedef struct assembler_type {
    NODE_STR_p symbolTable_head;
    NODE_STR_p symbolTable_tail;
    unsigned int num_of_symbols;
} ASSEMBLER;
typedef ASSEMBLER * ASSEMBLER_p;

/* Prototypes */
void firstParse (ASSEMBLER_p); //gathers all labels and assigns them addresses
void assemble (ASSEMBLER_p);

#endif /* ASSEMBLER_H_ */
