/*
 * loader.c
 *
 *  Created on: Jan 26, 2016
 *      Author: Ray Kim
 */

#include "fsm.h"

//GLOBALS
FSM_STR_p GLOBAL_fsm = FSM_constructor();

int main () {
    unsigned int instruction;
    unsigned int pc = 0;
    
    char * absolute_path = malloc(sizeof(char) * 100);
    unsigned int * memory_array = calloc(100, sizeof(unsigned int));
    
    REGISTER_STR_p reg_1;
    REGISTER_STR_p reg_2;
    REGISTER_STR_p reg_3;
    
    strcpy(absolute_path, "/Users/temp/Documents/tcss_372/git_repo/lc2200simulator/test.assem");
    assemble(absolute_path, memory_array);
    
    /***** Instruction cycle *****/
    while (1) {
        //fetch
        instruction = fetch(memory_array, pc);
        
        if (instruction == 0) {
            break;
        }
        
        //decode and execute
        execute(decode(instruction, reg_1, reg_2, reg_3), reg_1, reg_2, reg_3);
        
        //printf("%08x\n", instruction);
        
        pc++;
    }
    
    //free resources
    free(memory_array);
    free(absolute_path);
    FSM_destructor(GLOBAL_fsm);
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
    
    FSM_STR_p->zero = REGISTER_constructor("zero");
    FSM_STR_p->at = REGISTER_constructor("at");
    FSM_STR_p->v0 = REGISTER_constructor("v0");
    FSM_STR_p->a1 = REGISTER_constructor("a1");
    FSM_STR_p->a2 = REGISTER_constructor("a2");
    FSM_STR_p->t0 = REGISTER_constructor("t0");
    FSM_STR_p->t1 = REGISTER_constructor("t1");
    FSM_STR_p->t2 = REGISTER_constructor("t2");
    FSM_STR_p->s0 = REGISTER_constructor("s0");
    FSM_STR_p->s1 = REGISTER_constructor("s1");
    FSM_STR_p->k0 = REGISTER_constructor("k0");
    FSM_STR_p->sp = REGISTER_constructor("sp");
    FSM_STR_p->fp = REGISTER_constructor("fp");
    FSM_STR_p->ra = REGISTER_constructor("ra");
    
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

    REGISTER_destructor(FSM_STR_p->zero);
    REGISTER_destructor(FSM_STR_p->at);
    REGISTER_destructor(FSM_STR_p->v0);
    REGISTER_destructor(FSM_STR_p->a1);
    REGISTER_destructor(FSM_STR_p->a2);
    REGISTER_destructor(FSM_STR_p->t0);
    REGISTER_destructor(FSM_STR_p->t1);
    REGISTER_destructor(FSM_STR_p->t2);
    REGISTER_destructor(FSM_STR_p->s0);
    REGISTER_destructor(FSM_STR_p->s1);
    REGISTER_destructor(FSM_STR_p->k0);
    REGISTER_destructor(FSM_STR_p->sp);
    REGISTER_destructor(FSM_STR_p->fp);
    REGISTER_destructor(FSM_STR_p->ra);
    
    free(this);
    
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
 *  This function populates registers with the appropriate data for the given opcode
 *  This function then returns a pointer to the function associated with the opcode
 *
 *  params: unsigned int instruction opcode for this cycle
 *          REGISTER_STR_p reg_A
 *          REGISTER_STR_p reg_B
 *          REGISTER_STR_p reg_C
 *          pointer that will be loaded with the appropiate register for the current opcode, then passed to execute
 *  return: functionPtr *
 */
functionPtr * decode (unsigned int instruction, REGISTER_STR_p reg_A, REGISTER_STR_p reg_B, REGISTER_STR_p reg_C) {
    
    
    reg_A = GLOBAL_fsm->zero;
    reg_B =
    reg_C =
    
    
}



/*
 *  Function: execute
 *  ----------------------------
 *
 *  Calls the function associated with the function pointer and passes the 
 *  given registers as arguments.
 *
 *  params: functionPtr     function pointer that contains the function appropriate for the current opcode
 *          REGISTER_STR_p reg_A
 *          REGISTER_STR_p reg_B
 *          REGISTER_STR_p reg_C
 *          registers passed to functionPtr function
 *  return: functionPtr *
 */
void execute (functionPtr instructionFunction, REGISTER_STR_p reg_A, REGISTER_STR_p reg_B, REGISTER_STR_p reg_C) {
    
    instructionFunction(reg_A, reg_B, reg_C);
    
    
    
}