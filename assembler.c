/*
 * assembler.c
 *
 *  Created on: Feb 2, 2016
 *      Author: Ray Kim
 */

#include "assembler.h"

int main () {
    char * absolute_path = malloc(sizeof(char) * 100);
    strcpy(absolute_path, "/Users/temp/Documents/tcss_372/git_repo/lc2200simulator/test.assem");
    assemble(absolute_path);
    
    free(absolute_path);
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
 * ASSEMBLER_destructor
 *
 * Destroys elements within ASSEMBLER_STR_p
 *
 * params:  ASSEMBLER_STR_p
 *
 * return:  None
 */
void ASSEMBLER_destructor(ASSEMBLER_STR_p this) {
    //hashmap_free(this->symbol_table_map); //hashmap_free poorly written
    //hashmap_free(this->operations_map);
    //hashmap_free(this->registers_map);
    free(this);
    
}

/*
 * assemble
 *
 * Calls firstParse to replace symbols.
 *
 * params:  char * String location of assembly file
 * 
 * return:  none
 */
void assemble (char * loc_assem_file) {
    
    FILE * rfp; //read file pointer
    FILE * wfp;
    int line_buffer_size = sizeof(char) * 40;
    int opcode;
    char * loc_object_file;
    char * line_ptr = malloc(line_buffer_size);
    char * line_ptr_copy;
    char * token;
    char * token2;
    ssize_t num_char_read;
    unsigned int token_in_bits; //uint32_t token_in_bits;
    unsigned int bit_instruct_32; //uint32_t bit_instruct_32;
    map_t map_clone;
    
    //open assembly source
    rfp = fopen(loc_assem_file, "r");
    if (rfp == NULL)
        exit(EXIT_FAILURE);
    
    //create file name for output object file
    loc_object_file = malloc(sizeof(char) * 100);
    strcpy(loc_object_file, strtok(loc_assem_file, "."));
    strcat(loc_object_file, ".object");
    
    //open object file to write to
    wfp = fopen(loc_object_file, "w");
    if (wfp == NULL)
        exit(EXIT_FAILURE);
    
    ASSEMBLER_STR_p this = ASSEMBLER_constructor();
    
    while (fgets(line_ptr, line_buffer_size, rfp)) {
        line_ptr_copy = line_ptr;
        bit_instruct_32 = 0;
        token = strsep(&line_ptr_copy, " ");
        
        //take opcode, put it in bit form
        map_clone = this->operations_map;
        hashmap_get(map_clone, token, &token_in_bits);
        
        //bitshift to appropriate position in 32 bit bitcode
        opcode = token_in_bits;
        bit_instruct_32 = token_in_bits << 28; //bits 0-3
        
        int bitshift = 24;
        while (line_ptr_copy != NULL) {
            if (strstr(line_ptr_copy, ",") != NULL) { //if contains comma
                token = strsep(&line_ptr_copy, ",");
                line_ptr_copy = trimwhitespace(line_ptr_copy);
            } else {
                token = line_ptr_copy;
                line_ptr_copy = NULL;
            }
            
            if (line_ptr_copy == NULL && (opcode == 3 || opcode == 4)) { //lw and sw instructions like lw $a0, 20($a1)
                line_ptr_copy = token;
                token = strsep(&line_ptr_copy, "(");
                token2 = strsep(&line_ptr_copy, ")");
                map_clone = this->registers_map;
                hashmap_get(map_clone, token2, &token_in_bits);
                bit_instruct_32 = bit_instruct_32 | (token_in_bits << bitshift);
                token_in_bits = atoi(token);
                bit_instruct_32 = bit_instruct_32 | token_in_bits;
                line_ptr_copy = NULL;
            } else if (isdigit(token)) { //if immediate value
                token_in_bits = atoi(token);
                //write 16 bit number into last 32 bits of bit_instruct_32
                bit_instruct_32 = bit_instruct_32 | token_in_bits;
            } else { // else if register
                map_clone = this->registers_map;
                hashmap_get(map_clone, token, &token_in_bits);
                bit_instruct_32 = bit_instruct_32 | (token_in_bits << bitshift);
            }
            
            bitshift -= 4;
        }

        //write bitcode to object file
        fprintf(wfp, "%08x", bit_instruct_32);
        printf("%08x\n", bit_instruct_32);
    }
    
    fclose(rfp);
    fclose(wfp);
    free(line_ptr);
    free(loc_object_file);
    
    ASSEMBLER_destructor(this);
    //print_keyset(this->operations_map);
    //map_t map_clone = this->operations_map;
    
}


// Note: This function returns a pointer to a substring of the original string.
// If the given string was allocated dynamically, the caller must not overwrite
// that pointer with the returned value, since the original pointer must be
// deallocated using the same allocator with which it was allocated.  The return
// value must NOT be deallocated using free() etc.
char * trimwhitespace(char * str)
{
    char *end;
    
    // Trim leading space
    while(isspace(*str)) str++;
    
    if(*str == 0)  // All spaces?
        return str;
    
    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace(*end)) end--;
    
    // Write new null terminator
    *(end+1) = 0;
    
    return str;
}