/*
 * register.h
 *
 *  Created on: Jan 26, 2016
 *      Author: Ray Kim
 */

#ifndef REGISTER_H_
#define REGISTER_H_

/* CPU_register
 *
 */
typedef struct cpu_register_type {
    char reg_name[5];
    unsigned int reg_value;     /* stores value held within register */
} CPU_REGISTER;
typedef CPU_REGISTER * REGISTER_p;


/* Prototypes */


#endif /* REGISTER_H_ */
