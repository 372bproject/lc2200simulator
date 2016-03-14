/*
 * assembler.c
 *
 *  Created on: Feb 2, 2016
 *      Author: Ray Kim
 */

#include "assembler.h"

//int main () {
//    
//    char * absolute_path = malloc(sizeof(char) * 100);
//    unsigned int * memory_array = calloc(100, sizeof(unsigned int));
//    int i = 0;
//    
//    strcpy(absolute_path, "/Users/temp/Documents/tcss_372/git_repo/lc2200simulator/test2.assem");
//    assemble(absolute_path, memory_array);
//    
//    /***** Instruction cycle *****/
//    while (memory_array[i]) {
//        
//        printf("%08x\n", memory_array[i]);
//        
//        i++;
//    }
//    
//    //free resources
//    free(memory_array);
//    free(absolute_path);
//}

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
    map_t sacrificial_bugged_map = hashmap_new();
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
    
    this->sacrificial_bugged_map = sacrificial_bugged_map;
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
    //free(this);
    
}

/*
 * assemble
 *
 * Calls firstParse to replace symbols.
 *
 * params:  char * String location of assembly file
 * 
 * return:  start location of instructions
 */
unsigned int assemble (char * loc_assem_file, unsigned int * instructions_array) {
    
    FILE * rfp; //read file pointer
//    FILE * wfp;
    int line_buffer_size = sizeof(char) * 100;
    unsigned int start_loc;
    unsigned int opcode;
    int line_num = 0;
    char * loc_object_file;
    char * line_ptr = malloc(line_buffer_size);
    char * line_ptr_copy;
    char * line_malloc_loc = line_ptr;
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
//    wfp = fopen("./test.object", "w");
//    if (wfp == NULL)
//        exit(EXIT_FAILURE);
    
    ASSEMBLER_STR_p this = ASSEMBLER_constructor();
    
    //first parse (for labels)
    firstParse(this, rfp);
    
    
    while (fgets(line_ptr, line_buffer_size, rfp)) {
        line_ptr = trimwhitespace(line_ptr);
        
        //if contains label, remove label
        if (strstr(line_ptr, ":") != '\0') {
            strsep(&line_ptr, ":");
            //if instructions follow ":", don't use "continue"
            line_ptr = trimwhitespace(line_ptr);
            if (line_ptr == '\0' || line_ptr[0] == ';') {
                continue;
            }
        }
        
        //skip directives and comments
        if (line_ptr[0] == '.' || line_ptr[0] == ';' || line_ptr[0] == '\0') {
            continue;
        }
        
        line_ptr_copy = line_ptr;
        bit_instruct_32 = 0;
        token = strsep(&line_ptr_copy, " ");
        stringToLowerCase(token);
        line_ptr = line_ptr_copy;
        
        //take opcode, put it in bit form
        map_clone = this->operations_map; 
        hashmap_get(map_clone, token, &token_in_bits); 
        
        //bitshift to appropriate position in 32 bit bitcode
        opcode = token_in_bits;
        bit_instruct_32 = token_in_bits << 28; //bits 0-3
        
        line_ptr_copy = line_ptr;

        int bitshift = 24; 
        while (line_ptr_copy != NULL) { 
            if (strstr(line_ptr_copy, ",") != NULL) { //if contains comma
                token = strsep(&line_ptr_copy, ","); 
                stringToLowerCase(token); 
                line_ptr_copy = trimwhitespace(line_ptr_copy);
                line_ptr = line_ptr_copy;
            } else { //in the case of last element
                if (strstr(line_ptr_copy, ";") != NULL) { //if contains comment ";"
                    token = strsep(&line_ptr_copy, ";");
                } else {
                    token = line_ptr_copy;
                }
                token = trimwhitespace(token);
                stringToLowerCase(token);
                line_ptr_copy = NULL;
            }

            if (line_ptr_copy == NULL && (opcode == 3 || opcode == 4)) { //lw and sw instructions like lw $a0, 20($a1)
                line_ptr_copy = token;
                line_ptr = line_ptr_copy;
                token = strsep(&line_ptr_copy, "(");
                token2 = strsep(&line_ptr_copy, ")");
                map_clone = this->registers_map;
                hashmap_get(map_clone, token2, &token_in_bits);
                line_ptr_copy = line_ptr;
                bit_instruct_32 = bit_instruct_32 | (token_in_bits << bitshift);
                token_in_bits = atoi(token);
                bit_instruct_32 = bit_instruct_32 | token_in_bits;
                line_ptr_copy = NULL;
            } else if (line_ptr_copy == NULL && opcode == 5) { //if last object is label
                line_ptr = line_ptr_copy;
                int *label_line_offset;
                stringToLowerCase(token);
                map_clone = this->symbol_table_map;
                hashmap_get(map_clone, token, &label_line_offset); //printf("%d\n\n",*label_line_offset);
                line_ptr_copy = line_ptr;
                bit_instruct_32 = bit_instruct_32 | (0x0000FFFF & (*label_line_offset - line_num - 1)); //copy offset from current instruct line num into bit_instruct_32
                line_ptr_copy = NULL;
            } else if (line_ptr_copy == NULL && opcode == 6) { //if instruction is jalr
                line_ptr = line_ptr_copy;
                int *label_line_offset;
                stringToLowerCase(token);
                map_clone = this->registers_map;
                hashmap_get(map_clone, token, &token_in_bits);
                line_ptr_copy = line_ptr;
                bit_instruct_32 = bit_instruct_32 | (0x0F000000 & (token_in_bits << bitshift));
                line_ptr_copy = NULL;
            }else if (token[0] != '$') { //if immediate value
                line_ptr = line_ptr_copy;
                token_in_bits = atoi(token); 
                //write 16 bit number into last 32 bits of bit_instruct_32
                token_in_bits = token_in_bits & 0x0000FFFF;
                bit_instruct_32 = bit_instruct_32 | token_in_bits;
                line_ptr_copy = line_ptr;
            } else { // else if register
                line_ptr = line_ptr_copy;
                stringToLowerCase(token);
                map_clone = this->registers_map; 
                hashmap_get(map_clone, token, &token_in_bits); 
                bit_instruct_32 = bit_instruct_32 | (token_in_bits << bitshift); 
                line_ptr_copy = line_ptr;
            }
            
            bitshift -= 4; //printf("%d\n", this->start_loc);
        }

        //write bitcode to object file
//        fprintf(wfp, "%08x", bit_instruct_32); 
//        printf("%08x\n", bit_instruct_32);
        instructions_array[line_num] = bit_instruct_32;
        
        
        line_num += 1;
        line_ptr = line_malloc_loc;
    }
    
    start_loc = this->start_loc;
    
    fclose(rfp);
//    fclose(wfp);
    //free(line_ptr);
    //free(loc_object_file);
    
    ASSEMBLER_destructor(this);
    //print_keyset(this->operations_map);
    //print_keyset(this->symbol_table_map);
    //print_keyset(this->registers_map);
    
    return start_loc;
}

/*
 * firstParse
 *
 * Maps offset of labels from first instruction (in source assembly file).
 *
 * params:  ASSEMBLER_STR_p this
 *          FILE *          file pointer for source assembly file
 *
 * return:  none
 */
void firstParse(ASSEMBLER_STR_p this, FILE * source_file_ptr) {
    
    int line_buffer_size = sizeof(char) * 100;
    int line_num = 0;
    int * label_offset_ptr;
    char * token;
    char * line_ptr = (char *) malloc(line_buffer_size);
    char * line_ptr_orig = line_ptr;
    
    while (fgets(line_ptr, line_buffer_size, source_file_ptr)) {
        
        line_ptr = trimwhitespace(line_ptr);
        stringToLowerCase(line_ptr);
        //printf("%s\n", line_ptr);
        if (line_ptr[0] == '\0') {
            continue;
        } else if (strstr(line_ptr, ":") != NULL) { //search for formatting of LABEL:
            token = (char *) malloc(sizeof(char) * 27);
            strcpy(token, strsep(&line_ptr, ":"));
            stringToLowerCase(token);
            label_offset_ptr = (int *) malloc(sizeof(int));
            *label_offset_ptr = line_num;
            hashmap_put(this->symbol_table_map, token, label_offset_ptr);
            
            //if there are any other characters that follow label, then this line contains more instructions or a comment
            line_ptr = trimwhitespace(line_ptr);
            if (line_ptr != '\0' && line_ptr[0] != ';') {
                line_num += 1;
            }

        } else if (line_ptr[0] == '.') { //assembler directives
            //grab start number after .orig
            if (strstr(line_ptr, "orig") != NULL) {
                strsep(&line_ptr, " ");
                line_ptr = trimwhitespace(line_ptr);
                this->start_loc = atoi(line_ptr);
            }
            
            continue;
        } else if (line_ptr[0] == ';') {
            continue;
        } else { //lines with labels do not count as their own lines
            line_num += 1;
            
        }
        //printf("%d\n", line_num);
        line_ptr = line_ptr_orig; //reset pointer to original buffer start location
    }
    
    //reset source_file_ptr to beginning of source assembly file
    rewind(source_file_ptr);
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

/* stringToLowerCase
 *
 * Converts string to lower case
 * Changes input string
 *
 * params:  char *       string that is to be converted to lower case
 *
 * return:  none
 */
void stringToLowerCase(char * str) {
    int i;
    for (i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
