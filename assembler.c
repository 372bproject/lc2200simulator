/*
 * assembler.c
 *
 *  Created on: Feb 2, 2016
 *      Author: Ray Kim
 */

#include "assember.h"

int main () {
    ASSEMBLER_STR_p this = ASSEMBLER_constructor();
    
    //print_keyset(this->operations_map);
    map_t map_clone = this->operations_map;
    
    int temp;
    hashmap_get(this->operations_map, "halt", &temp);
    
    printf("%d\n", temp);
    
    map_clone = this->registers_map;
    hashmap_get(map_clone, "at", &temp);
    
    printf("%d\n", temp);
    
    map_clone = this->registers_map;
    hashmap_get(map_clone, "zero", &temp);
    
    printf("%d\n", temp);
}


/*
 * ASSEMBLER_constructor
 *
 * Creates all symbol_table_map, operations_map and registers_map hashmaps used in
 * conversion of assembly into bitcode.
 *
 * params:  none
 *
 * return:  ASSEMBLER_STR_p pointer to object fields struct
 */
ASSEMBLER_STR_p ASSEMBLER_constructor() {
    ASSEMBLER_STR_p this = (ASSEMBLER_STR_p) malloc(sizeof(ASSEMBLER_STR_p));
    
    //declare maps
    map_t symbolTable = hashmap_new();
    map_t operationsMap = hashmap_new();
    map_t registersMap = hashmap_new();
    
    /********** populate maps **********/
    //note any_t is type void *
    //you must caste to specific type of pointer after retrieving value via hashmap_get
    
    //operations
    int i;
    int num_elements_in_operations_arr = sizeof(operations_arr) / (sizeof(char) * GLOBAL_OP_REG_STRING_SIZE);
    for (i = 0; i < num_elements_in_operations_arr; i++) {
        hashmap_put(operationsMap, operations_arr[i], index_to_int_ptr[i]);
    }
    
    //registers
    int num_elements_in_registers_arr = sizeof(registers_arr) / (sizeof(char *));
    for (i = 0; i < num_elements_in_registers_arr; i++) {
        //printf("%s\n", registers_arr[i]);
        hashmap_put(registersMap, registers_arr[i], index_to_int_ptr[i]);
    }

    this->symbol_table_map = symbolTable;
    this->operations_map = operationsMap;
    this->registers_map = registersMap;
    
    return this;
}

/*
 * assemble
 *
 * Calls firstParse to replace symbols.
 *
 * params:  ASSEMBLER_STR_p
 *          char *
 *          char *
 * 
 * return:
 */