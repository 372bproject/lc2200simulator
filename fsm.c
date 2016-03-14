/*
 * fsm.c
 *
 *  Created on: Jan 26, 2016
 *      Author: Ray Kim
 */

#include "fsm.h"
#include "fsm-micro.h"

//GLOBALS

/*
 *  Function: FSM_initialize
 *  ----------------------------
 *
 *	initializes all variables for FSM
 *
 *  params: unsigned char * absolute address
 *			
 *  return: unsigned int    start address of simulation
 */
FSM_STR_p FSM_initialize (FSM_STR_p this, char * absolute_path) {

    this->memory_module_p = MEMORY_MODULE_constructor(MEMORY_SIZE);
    
    this->sp->reg_value = MEMORY_SIZE - 1; //set stack pointer value

    this->alu_p = ALU_constructor();

    this->start_address = assemble(absolute_path, this->memory_module_p->address_start_p);

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
	this->start_address = 0;
	this->alu_p = NULL;
	this->memory_module_p = NULL;
    
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
    printf("%s(%p) = %d\n", this->zero->reg_name,this->zero, this->zero->reg_value);
    printf("%s(%p) = %d\n", this->at->reg_name, this->at, this->at->reg_value);
    printf("%s(%p) = %d\n", this->v0->reg_name, this->v0, this->v0->reg_value);
    printf("%s(%p) = %d\n", this->a0->reg_name, this->a0, this->a0->reg_value);
    printf("%s(%p) = %d\n", this->a1->reg_name, this->a1, this->a1->reg_value);
    printf("%s(%p) = %d\n", this->a2->reg_name, this->a2, this->a2->reg_value);
    printf("%s(%p) = %d\n", this->t0->reg_name, this->t0, this->t0->reg_value);
    printf("%s(%p) = %d\n", this->t1->reg_name, this->t1, this->t1->reg_value);
    printf("%s(%p) = %d\n", this->t2->reg_name, this->t2, this->t2->reg_value);
    printf("%s(%p) = %d\n", this->s0->reg_name, this->s0, this->s0->reg_value);
    printf("%s(%p) = %d\n", this->s1->reg_name, this->s1, this->s1->reg_value);
    printf("%s(%p) = %d\n", this->k0->reg_name, this->k0, this->k0->reg_value);
    printf("%s(%p) = %d\n", this->sp->reg_name, this->sp, this->sp->reg_value);
    printf("%s(%p) = %d\n", this->fp->reg_name, this->fp, this->fp->reg_value);
    printf("%s(%p) = %d\n", this->ra->reg_name, this->ra, this->ra->reg_value);
    printf("pc = %d\n\n", this->pc);
    //printf("register p size: %d", (unsigned int) sizeof(REGISTER_STR_p));
    
}

/*
 *  Function: FSM_get_registers
 *  ----------------------------
 *
 *  places register data into given array
 *
 *  params: FSM_STR_p this
 *			int * array that will contain register values
 *  return: none
 */
void FSM_get_registers(FSM_STR_p this, int * registers_array){
	
	registers_array[0] = this->pc;
	registers_array[1] = this->zero->reg_value;
	registers_array[2] = this->at->reg_value;
	registers_array[3] = this->v0->reg_value;
	registers_array[4] = this->a0->reg_value;
	registers_array[5] = this->a1->reg_value;
	registers_array[6] = this->a2->reg_value;
	registers_array[7] = this->t0->reg_value;
	registers_array[8] = this->t1->reg_value;
	registers_array[9] = this->t2->reg_value;
	registers_array[10] = this->s0->reg_value;
	registers_array[11] = this->s1->reg_value;
	registers_array[12] = this->k0->reg_value;
	registers_array[13] = this->sp->reg_value;
	registers_array[14] = this->fp->reg_value;
	registers_array[15] = this->ra->reg_value;


}

/*
 *  Function: FMS_step
 *  ----------------------------
 *
 *  Steps through each instruction
 *
 *  params: FSM_STR_p   this
 *  return: unsigned int	0 if last "step" performed was last instruction, otherwise return instruction index num
 */
unsigned int FSM_step(FSM_STR_p this) {
	unsigned int instruction;

    /***** Instruction cycle *****/
    if (fetch(this->memory_module_p->address_start_p, this->pc)) {
        this->pc++;
        //fetch
        instruction = fetch(this->memory_module_p->address_start_p, this->pc - 1);
//printf("instruction: %08x\n", instruction);
        //decode and execute
        decode(this, this->memory_module_p->address_start_p, instruction, this->alu_p);
        
        
//printAllRegisters(this);
        
		return instruction;
        
    } else {
		return 0;
	}

}


/*
 *  Function: FSM_run_through
 *  ----------------------------
 *
 *  Runs through all of the rest of the remaining steps
 *
 *  params: FSM_STR_p this
 *  return: unsigned int	return instruction index
 */
void FSM_run_through(FSM_STR_p this) {
	unsigned int instruction;

    /***** Instruction cycle *****/
    while (fetch(this->memory_module_p->address_start_p, this->pc)) {
        this->pc++;
        //fetch
        instruction = fetch(this->memory_module_p->address_start_p, this->pc - 1);
//printf("instruction: %08x\n", instruction);
        //decode and execute
        decode(this, this->memory_module_p->address_start_p, instruction, this->alu_p);
        
        //printf("%08x\n", instruction);
//printAllRegisters(this);
        
    }

}

/*
 *  Function: FSM_reset
 *  ----------------------------
 *
 *  resets logical back end
 *
 *  params: FSM_STR_p this
 *  return: unsigned int	return instruction index
 */
void FSM_reset(FSM_STR_p this) {

	this->zero->reg_value = 0;
    this->at->reg_value = 0;
    this->v0->reg_value = 0;
    this->a0->reg_value = 0;
    this->a1->reg_value = 0;
    this->a2->reg_value = 0;
    this->t0->reg_value = 0;
    this->t1->reg_value = 0;
    this->t2->reg_value = 0;
    this->s0->reg_value = 0;
    this->s1->reg_value = 0;
    this->k0->reg_value = 0;
    this->sp->reg_value = 0;
    this->fp->reg_value = 0;
    this->ra->reg_value = 0;
    this->pc = 0;

}


/*
 *  Function: FSM_destroy
 *  ----------------------------
 *
 *  Release all assets created in initialize
 *
 *  params: FSM_STR_p this
 *  return: unsigned int	return instruction index
 */
void FSM_destroy(FSM_STR_p this){
	//free resources
    MEMORY_MODULE_destructor(this->memory_module_p);
    //FSM_destructor(this);
    ALU_destructor(this->alu_p);

}

