/*
 * assembler.h
 *
 *  Created on: Jan 26, 2016
 *      Author: Ray Kim
 */

#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap.h"

#define GLOBAL_OP_REG_STRING_SIZE 6

/* CPU_assembler
 *
 */
typedef struct assembler_str {
    map_t sacrificial_bugged_map;
    map_t operations_map;
    map_t registers_map;
    map_t symbol_table_map;
} ASSEMBLER_STR;
typedef ASSEMBLER_STR * ASSEMBLER_STR_p;



/* Supported operations
 *
 */
    static char operations_arr[][GLOBAL_OP_REG_STRING_SIZE] = {
    "add", //0000
    "nand", //0001
    "addi", //0010
    "lw", //0011
    "sw", //0100
    "beq", //0101
    "jalr", //0110
    "halt", //0111
    "sub", //1000
    "ei", //1001 enable interrupts
    "di", //1010 disable interrupts
    "reti", //1011
    "noop", //1100
    ".word" //1101 fill the word with a value. Ex.: fill the current location with the 32-bit representation of the nubmer "32"
    
}; //note: each string is 5 bytes long, \0 may be automatically added to end of each string

static char * registers_arr[] = {
    "$zero", //0000
    "$at", //0001
    "$v0", //0010
    "$a0", //0011
    "$a1", //0100
    "$a2", //0101
    "$t0", //0110
    "$t1", //0111
    "$t2", //1000
    "$s0", //1001
    "$s1", //1010
    "$k0", //1011
    "$sp", //1100
    "$fp", //1101
    "$ra" //1101
};

static int * index_to_int_ptr[] = {
    0, //0000
    1, //0001
    2, //0010
    3, //0011
    4, //0100
    5, //0101
    6, //0110
    7, //0111
    8, //1000
    9, //1001
    10, //1010
    11, //1011
    12, //1100
    13, //1101
    14, //1101
    15  //1111
};

/* Prototypes */
ASSEMBLER_STR_p ASSEMBLER_constructor();
void ASSEMBLER_destructor(ASSEMBLER_STR_p);
void assemble (char *);
void firstParse (ASSEMBLER_STR_p, FILE *); //gathers all labels and assigns them addresses
char * trimwhitespace (char *);
void stringToLowerCase(char *);

#endif /* ASSEMBLER_H_ */
