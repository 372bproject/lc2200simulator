/*
 * memory.c
 *
 *  Created on: Feb 25, 2016
 *      Author: Ray Kim
 */

#include "memory.h"

/*
 *  Function: MEMORY_MODULE_constructor
 *  ----------------------------
 *
 *  params: unsigned int size of memory
 *  return: MEMORY_MODULE_STR_p   this
 */
MEMORY_MODULE_STR_p MEMORY_MODULE_constructor (unsigned int memory_allocation_size) {
    
    MEMORY_MODULE_STR_p this = (MEMORY_MODULE_STR_p) malloc(sizeof(memory_module_str));
    
    this->allocation_size = memory_allocation_size;
    
    this->address_start_p = calloc(memory_allocation_size, sizeof(unsigned int));
    
    return this;
    
}

/*
 *  Function: MEMORY_MODULE_destructor
 *  ----------------------------
 *
 *  params: MEMORY_MODULE_STR_p   this
 *  return:
 */
void MEMORY_MODULE_destructor (MEMORY_MODULE_STR_p this) {
    
    free(this->address_start_p);
    
    free(this);
    
}
