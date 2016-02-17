/*
 * fsm-micro.c
 *
 *  Created on: Feb 17, 2016
 *      Author: Abdul Fiqi, Ray Kim
 */

EXTERN_GLOBAL_MICRO_STATES[] = {
    {1088, 1056, 2049, 0}, //add
    {1088, 1056, 2049, 0}, //nand
    {1088, 288, 2049, 0}, //addi
    {1088, 288, 2064, 513, 0}, //lw
    {1088, 288, 2064, 1026, 0}, //sw
    {1088, 1056, 2052, 4160, 288, 2176, 0}, //beq
    {4097, 1152, 0}, //jalr
    {3, 0}, //halt
    {0}, //sub
    {0}, //ei
    {0}, //di
    {0}, //reti
    {1088, 1056, 2049, 0} //noop
}


/*
 *  Function: FSM-MICRO_execute
 *  ----------------------------
 *
 *  This function executes the microstates
 *
 *  params: FSM_STR_p fsm_object finite state machine object
 *          unsigned int instruction bitcode
 *          unsigned int control signal number for micro instruction
 *          REGISTER_STR_p reg_A
 *          REGISTER_STR_p reg_B
 *          REGISTER_STR_p reg_C
 *
 *  return: none
 */
void FSM-MICRO_execute (FSM_STR_p fsm_object,  unsigned int instruction, unsigned int control_signal, REGISTER_STR_p reg_A, REGISTER_STR_p reg_B, REGISTER_STR_p reg_C) {
    
    switch (control_signal) {
        case 1088:
            //TODO use mask to get appropriate register, then set register as operand (set reg_A to appropriate register
            break;
        case 1056:
            <#statements#>
            break;
        case 2049:
            <#statements#>
            break;
        case 288:
            statements
            break;
        case 2064:
            <#statements#>
            break;
        case 513:
            <#statements#>
            break;
        case 1026:
            <#statements#>
            break;
        case 2052:
            <#statements#>
            break;
        case 4160:
            <#statements#>
            break;
        case 2176:
            <#statements#>
            break;
        case 1152:
            <#statements#>
            break;
            
        case 3:
            <#statements#>
            break;
        default:
            break;
    }
}