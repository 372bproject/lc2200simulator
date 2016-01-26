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
typedef struct memory_module_type {
    unsigned int MAR;
    unsigned int MDR;
    int * address_space;
    int allocation_size;
} cpu_memory_module;
typedef memory_module * MEMORY_MODULE_p;


/* Prototypes */
void load (MEMORY_MODULE_p);
void store (MEMORY_MODULE_p);

#endif /* CPU_MEMORY_H_ */
