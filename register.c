/*
 * register.c
 *
 *  Created on: Jan 26, 2016
 *      Author: Ray Kim
 */

/*
 *  Function: REGISTER_constructor
 *  ----------------------------
 *
 *  params:
 *  return: REGISTER_STR_p   this
 */
REGISTER_STR_p REGISTER_constructor (char * reg_name) {
    
    REGISTER_STR_p this = (REGISTER_STR_p) malloc(sizeof(REGISTER_STR));
    
    strcpy(this->reg_name, reg_name);
    
    return this;
    
}

/*
 *  Function: REGISTER_destructor
 *  ----------------------------
 *
 *  params: REGISTER_STR_p   this
 *  return:
 */
void REGISTER_destructor (REGISTER_STR_p this) {
    
    free(this);
    
}