/*
 * register.h
 *
 *  Created on: Jan 26, 2016
 *      Author: Ray Kim
 */

#ifndef REGISTER_H_
#define REGISTER_H_

#include <string.h>
#include <stdlib.h>

/* CPU_register
 *
 */
typedef struct cpu_register_str {
    char reg_name[5];
    unsigned int reg_value;     /* stores value held within register */
} REGISTER_STR;
typedef REGISTER_STR * REGISTER_STR_p;


/* Prototypes */
REGISTER_STR_p REGISTER_constructor (char *);
void REGISTER_destructor (REGISTER_STR_p);

#endif /* REGISTER_H_ */
