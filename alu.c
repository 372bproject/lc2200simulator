/*
 * alu.h
 *
 *  Created on: Feb 25, 2016
 *      Author: Ray Kim
 */

#include "alu.h"

/*
 *  Function: ALU_constructor
 *  ----------------------------
 *
 *  adds A and B of ALU
 *
 *  params: none
 *
 *  return: ALU_p   this
 */
ALU_p ALU_constructor(){
    
    ALU_p this = (ALU_p) malloc(sizeof(ALU_STR));
    
    this->A = (REGISTER_STR_p) REGISTER_constructor("A");
    this->B = (REGISTER_STR_p) REGISTER_constructor("B");
    this->output = (REGISTER_STR_p) REGISTER_constructor("output");
    
    return this;
}


/*
 *  Function: ALU_destructor
 *  ----------------------------
 *
 *
 *  params: ALU_p   this
 *
 *  return: none
 */
void ALU_destructor(ALU_p this){
    
    REGISTER_destructor(this->A);
    REGISTER_destructor(this->B);
    REGISTER_destructor(this->output);
    
    free(this);
    
}


/*
 *  Function: ALU_add
 *  ----------------------------
 *
 *  adds A and B of ALU
 *
 *  params: ALU_p this
 *
 *  return: none
 */
void ALU_add (ALU_p this){
    
    this->output->reg_value = this->A->reg_value + this->B->reg_value;
    
}

/*
 *  Function: ALU_nand
 *  ----------------------------
 *
 *  nands A and B of ALU
 *
 *  params: ALU_p this
 *
 *  return: none
 */
void ALU_nand (ALU_p this){
    
    this->output->reg_value = (this->A->reg_value & this->B->reg_value) * -1;
    
}


/*
 *  Function: ALU_sub
 *  ----------------------------
 *
 *  subtracts A and B of ALU
 *
 *  params: ALU_p this
 *
 *  return: none
 */
void ALU_sub (ALU_p this){
    
    this->output->reg_value = this->A->reg_value - this->B->reg_value;
    
}