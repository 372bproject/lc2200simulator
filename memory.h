/*
 * memory.h
 *
 *  Created on: Jan 26, 2016
 *      Author: Ray Kim
 */

#ifndef CPU_MEMORY_H_
#define CPU_MEMORY_H_


/* CPU_memory
 *
 */
typedef struct memory_module_str {
    unsigned int MAR;
    unsigned int MDR;
    int * address_space;
    int allocation_size;
} cpu_memory_module_str;
typedef memory_module_str * MEMORY_MODULE_STR_p;


/* Prototypes */
void load (MEMORY_MODULE_STR_p);
void store (MEMORY_MODULE_STR_p);

#endif /* CPU_MEMORY_H_ */
