/*
 * fsm-micro.c
 *
 *  Created on: Feb 17, 2016
 *      Author: Abdul Fiqi, Ray Kim
 */

#include "fsm-micro.h"


unsigned int EXTERN_GLOBAL_MICRO_STATES[][7] = {
    {1088, 1056, 2049, 0}, //add
    {1088, 1056, 2049, 0}, //nand
    {1088, 288, 2049, 0}, //addi
    {1088, 288, 2064, 513, 0}, //lw
    {1088, 288, 2064, 1026, 0}, //sw
    {1057, 1056, 2052, 4160, 288, 2176, 0}, //beq
    {4097, 1152, 0}, //jalr
    {3, 0}, //halt
    {1088, 1056, 2049, 0}, //sub
    {0}, //ei
    {0}, //di
    {0}, //reti
    {1088, 1056, 2049, 0} //noop
};


/*
 *  Function: FSM-MICRO_execute
 *  ----------------------------
 *
 *  This function executes the microstates
 *
 *  params: FSM_STR_p fsm_object finite state machine object
 *          unsigned int * memory start loc pointer
 *          unsigned int instruction bitcode
 *          unsigned int control signal number for micro instruction
 *          ALU_p        alu object containing alu registers
 *
 *  return: unsigned int    1 for stop current microstate chain, 0 for continue
 */
unsigned int FSM_MICRO_execute (FSM_STR_p fsm_object_p, unsigned int * memory_start_p, functionPtr operation, unsigned int instruction, unsigned int control_signal, ALU_p alu_p) {
    
    unsigned int register_num;
    char * base = (char *) (&(fsm_object_p->pc)) + sizeof(REGISTER_STR_p); //printf("%p\t", base);printf("%p\t", &(fsm_object_p->zero)); printf("%p\t", &(fsm_object_p->at));printf("%p\t", &(fsm_object_p->v0));printf("%p\t", &(fsm_object_p->a0));puts("");
	REGISTER_STR_p * reg_reference_p;
    REGISTER_STR_p reg_reference;
    
    
    //OPCODE Rx, Ry, Rz
    //OPCODE A, B, C
    switch (control_signal) {
        case 1088: //set A = Ry
            register_num = instruction & 0x00F00000;
            register_num = register_num >> 20; //printf("%d\n", register_num);
            reg_reference_p = (REGISTER_STR_p *)(base + (sizeof(REGISTER_STR_p) * register_num)); //16 seems to be the offset from register pointer to register pointer within FSM_STR. register pointers may be reduced to 16 vs 32 or 64 by the optimizer
//            printf("%x\n", base);
//            printf("%x\n", fsm_object_p->a0->reg_name);
//            printf("%x\n", reg_B->reg_name);
			reg_reference = (REGISTER_STR_p)(*reg_reference_p);
            alu_p->A->reg_value = reg_reference->reg_value;//printf("alu_p->A: %d\n", alu_p->A->reg_value);
            break;
        case 1057: //set B = Rx (this instruction is kinda wrong since technically for BEQ, A = Rx, B = Ry)
            register_num = instruction & 0x0F000000;
            register_num = register_num >> 24;
            reg_reference_p = (REGISTER_STR_p *)(base + (sizeof(REGISTER_STR_p) * register_num));
			reg_reference = (REGISTER_STR_p)(*reg_reference_p);
            alu_p->B->reg_value = reg_reference->reg_value; //printf("alu_p->B: %d\n", alu_p->B->reg_value);
            break;
        case 1056: //set B = Rz
            register_num = instruction & 0x000F0000;
            register_num = register_num >> 16;
            reg_reference_p = (REGISTER_STR_p *)(base + (sizeof(REGISTER_STR_p) * register_num));
			reg_reference = (REGISTER_STR_p)(*reg_reference_p);
            alu_p->B->reg_value = reg_reference->reg_value; //printf("alu_p->B: %d\n", alu_p->B->reg_value);
            break;
        case 2049: //Rx = A (operation) B
            register_num = instruction & 0x0F000000;
            register_num = register_num >> 24;
            reg_reference_p = (REGISTER_STR_p *)(base + (sizeof(REGISTER_STR_p) * register_num));
			reg_reference = (REGISTER_STR_p)(*reg_reference_p);
            operation(alu_p);
            reg_reference->reg_value = alu_p->output->reg_value; 
//printf("%d\n", reg_reference->reg_value);
//printf("%s\n", reg_reference->reg_name);
            break;
        case 288: //set B = immediate value
            alu_p->B->reg_value = instruction & 0x0000FFFF;
            //sign extension for negative values
            if (alu_p->B->reg_value & 0x00008000) { //masked bit equaling 1 results in true
                alu_p->B->reg_value = alu_p->B->reg_value | 0xFFFF0000;
            }
            break;
        case 2064: //set alu_p->output = calculate base + offset
            alu_p->output->reg_value = alu_p->A->reg_value + alu_p->B->reg_value;
            break;
        case 513: //(lw) set Rx = Ry + offset
            register_num = instruction & 0x0F000000;
            register_num = register_num >> 24;
            reg_reference_p = (REGISTER_STR_p *)(base + (sizeof(REGISTER_STR_p) * register_num));
			reg_reference = (REGISTER_STR_p)(*reg_reference_p);
            reg_reference->reg_value = memory_start_p[alu_p->output->reg_value];
            break;
        case 1026: //(sw) set Ry + offset = Rx
            register_num = instruction & 0x0F000000;
            register_num = register_num >> 24;
            reg_reference_p = (REGISTER_STR_p *)(base + (sizeof(REGISTER_STR_p) * register_num));
			reg_reference = (REGISTER_STR_p)(*reg_reference_p);
            memory_start_p[alu_p->output->reg_value] = reg_reference->reg_value;
            break;
        case 2052: //A - B comparison, then detect if result is 0
//            printf("A = %d\n", alu_p->A->reg_value);
//            printf("B = %d\n", alu_p->B->reg_value);
            if (alu_p->B->reg_value - alu_p->A->reg_value) { //B holds Rx, A holds Ry
                return 1; //stop microstate execution chain
            }
            break;
        case 4160: //set A = PC
            alu_p->A->reg_value = fsm_object_p->pc;
            break;
        case 2176: //set PC = A + B
            fsm_object_p->pc = alu_p->A->reg_value + alu_p->B->reg_value;
            break;
        case 4097: //save current pc to return register
            fsm_object_p->ra->reg_value = fsm_object_p->pc;
            break;
        case 1152: //set pc = Rx
            register_num = instruction & 0x0F000000;
            register_num = register_num >> 24;
            reg_reference_p = (REGISTER_STR_p *)(base + (sizeof(REGISTER_STR_p) * register_num));
			reg_reference = (REGISTER_STR_p)(*reg_reference_p);
            fsm_object_p->pc = reg_reference->reg_value;
            break;
            
        case 3: //halt
            
            break;
        default:
            break;
    }
    return 0;
}
