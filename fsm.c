/*
 * fsm.c
 *
 *  Created on: Jan 26, 2016
 *      Author: Ray Kim
 */

#include "fsm.h"
#include "fsm-micro.h"

//GLOBALS


int main () {
    unsigned int instruction;
    unsigned int start_loc;
    MEMORY_MODULE_STR_p memory_module_p = MEMORY_MODULE_constructor(MEMORY_SIZE);
    
    char * absolute_path = malloc(sizeof(char) * 100);
    
    FSM_STR_p this = FSM_constructor();
    this->sp->reg_value = MEMORY_SIZE - 1; //set stack pointer value

    ALU_p alu_p = ALU_constructor();

    
    strcpy(absolute_path, "/Users/temp/Documents/tcss_372/git_repo/lc2200simulator/test2.assem");
    start_loc = assemble(absolute_path, memory_module_p->address_start_p);
    
    /***** Instruction cycle *****/
    while (fetch(memory_module_p->address_start_p, this->pc)) {
        this->pc++;
        //fetch
        instruction = fetch(memory_module_p->address_start_p, this->pc - 1);
printf("instruction: %08x\n", instruction);
        //decode and execute
        decode(this, memory_module_p->address_start_p, instruction, alu_p);
        
        //printf("%08x\n", instruction);
        printAllRegisters(this);
        
        
    }
    
    //free resources
    MEMORY_MODULE_destructor(memory_module_p);
    free(absolute_path);
    FSM_destructor(this);
    ALU_destructor(alu_p);

}

/*
 *  Function: fetch
 *  ----------------------------
 *
 *  params: unsigned int * memory_array array containing instructions (.text)
 *          unsigned int pc
 *  return: unsigned int    instruction opcode for that cycle
 */
unsigned int fetch (unsigned int * memory_array, unsigned int pc) {
    
    return memory_array[pc];
    
}

/*
 *  Function: decode
 *  ----------------------------
 *
 *  Runs opcode through finite state machine's micro states
 *  This function designates operand registers based on the given opcode
 *  This function then returns a pointer to the function associated with the opcode
 *
 *  params: FSM_STR_p this
 *          unsigned int * memory start loc pointer
 *          unsigned int instruction opcode for this cycle
 *          ALU_p   contains all alu registers
 *          pointer that will be loaded with the appropiate register for the current opcode, then passed to execute
 *  return: functionPtr *
 */
void decode (FSM_STR_p this, unsigned int * memory_start_p, unsigned int instruction, ALU_p alu_p) {
    
    unsigned int microstate_return_code; //1 equals stop microstate chain, 0 means continue
    unsigned int micro_state_num = 0;
    unsigned int opcode = instruction & 0xF0000000; //get the most significant hex
    opcode = opcode >> 28; //push opcode to right-most position
    
    while (EXTERN_GLOBAL_MICRO_STATES[opcode][micro_state_num]) { //last microstate is zero, thus terminating loop
        
        switch (opcode) {
            case 1: //nand
                microstate_return_code = FSM_MICRO_execute(this, memory_start_p, ALU_nand, instruction, EXTERN_GLOBAL_MICRO_STATES[opcode][micro_state_num], alu_p);
                break;
            case 8: //sub
                microstate_return_code = FSM_MICRO_execute(this, memory_start_p, ALU_sub, instruction, EXTERN_GLOBAL_MICRO_STATES[opcode][micro_state_num], alu_p);
                break;
            default: //case 0 and 2 (add and addi) and all other cases
                microstate_return_code = FSM_MICRO_execute(this, memory_start_p, ALU_add, instruction, EXTERN_GLOBAL_MICRO_STATES[opcode][micro_state_num], alu_p);
                break;
        }
        
        if (microstate_return_code) { //stop microstate chain
            return;
        }

        micro_state_num++;
    }
}

/*
 *  Function: FSM_constructor
 *  ----------------------------
 *
 *  params:
 *  return: FSM_STR_p   this
 */
FSM_STR_p FSM_constructor () {
    
    FSM_STR_p this = (FSM_STR_p) malloc(sizeof(FSM_STR));

    this->zero = REGISTER_constructor("zero");
    this->at = REGISTER_constructor("at");
    this->v0 = REGISTER_constructor("v0");
    this->a0 = REGISTER_constructor("a0");
    this->a1 = REGISTER_constructor("a1");
    this->a2 = REGISTER_constructor("a2");
    this->t0 = REGISTER_constructor("t0");
    this->t1 = REGISTER_constructor("t1");
    this->t2 = REGISTER_constructor("t2");
    this->s0 = REGISTER_constructor("s0");
    this->s1 = REGISTER_constructor("s1");
    this->k0 = REGISTER_constructor("k0");
    this->sp = REGISTER_constructor("sp");
    this->fp = REGISTER_constructor("fp");
    this->ra = REGISTER_constructor("ra");
//    this->pc = REGISTER_constructor("ir"); //instruction register
    this->pc = 0;
    
    return this;
    
}

/*
 *  Function: FSM_destructor
 *  ----------------------------
 *
 *  params: FSM_STR_p   this
 *  return:
 */
void FSM_destructor (FSM_STR_p this) {

    REGISTER_destructor(this->zero);
    REGISTER_destructor(this->at);
    REGISTER_destructor(this->v0);
    REGISTER_destructor(this->a0);
    REGISTER_destructor(this->a1);
    REGISTER_destructor(this->a2);
    REGISTER_destructor(this->t0);
    REGISTER_destructor(this->t1);
    REGISTER_destructor(this->t2);
    REGISTER_destructor(this->s0);
    REGISTER_destructor(this->s1);
    REGISTER_destructor(this->k0);
    REGISTER_destructor(this->sp);
    REGISTER_destructor(this->fp);
    REGISTER_destructor(this->ra);
    
    free(this);
    
}

/*
 *  Function: printAllRegisters
 *  ----------------------------
 *
 *  Prints all registers and PC
 *
 *  params: FSM_STR_p   this
 *  return: none
 */
void printAllRegisters(FSM_STR_p this) {
    printf("zero = %d\n", this->zero->reg_value);
    printf("at = %d\n", this->at->reg_value);
    printf("v0 = %d\n", this->v0->reg_value);
    printf("a0 = %d\n", this->a0->reg_value);
    printf("a1 = %d\n", this->a1->reg_value);
    printf("a2 = %d\n", this->a2->reg_value);
    printf("t0 = %d\n", this->t0->reg_value);
    printf("t1 = %d\n", this->t1->reg_value);
    printf("t2 = %d\n", this->t2->reg_value);
    printf("s0 = %d\n", this->s0->reg_value);
    printf("s1 = %d\n", this->s1->reg_value);
    printf("k0 = %d\n", this->k0->reg_value);
    printf("sp = %d\n", this->sp->reg_value);
    printf("fp = %d\n", this->fp->reg_value);
    printf("ra = %d\n", this->ra->reg_value);
    printf("pc = %d\n\n", this->pc);
    
    
}

