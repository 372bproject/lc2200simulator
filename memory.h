/*
 * memory.h
 *
 *  Created on: Jan 26, 2016
 *      Author: Ray Kim
 */

#ifndef CPU_MEMORY_H_
#define CPU_MEMORY_H_

#include <stdlib.h>

/* CPU_memory
 *
 */
typedef struct memory_module_str {
    unsigned int MAR;
    unsigned int MDR;
    unsigned int * address_start_p;
    unsigned int allocation_size;
} memory_module_str;
typedef memory_module_str * MEMORY_MODULE_STR_p;


/* Prototypes */
MEMORY_MODULE_STR_p MEMORY_MODULE_constructor (unsigned int);
void MEMORY_MODULE_destructor (MEMORY_MODULE_STR_p);
void load (MEMORY_MODULE_STR_p);
void store (MEMORY_MODULE_STR_p);

#endif /* CPU_MEMORY_H_ */
