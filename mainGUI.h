
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fsm.h"

typedef struct mult_gpointers_str {
	
	char * absolute_path;
    GtkWidget* instructions_table;	
    GtkWidget* registers_table;
	GtkWidget* heap_table;
	GtkWidget* stack_table;
	int registers_array[16];
	GtkWidget* pc;
	GtkWidget* zero;
    GtkWidget* at;
    GtkWidget* v0;
    GtkWidget* a0;
    GtkWidget* a1;
    GtkWidget* a2;
    GtkWidget* t0;
    GtkWidget* t1;
    GtkWidget* t2;
    GtkWidget* s0;
    GtkWidget* s1;
    GtkWidget* k0;
    GtkWidget* sp;
    GtkWidget* fp;
    GtkWidget* ra;

	GtkWidget* pc_label;
	GtkWidget* zero_label;
	GtkWidget* at_label;
	GtkWidget* v0_label;
	GtkWidget* a0_label;
	GtkWidget* a1_label;
	GtkWidget* a2_label;
	GtkWidget* t0_label;
	GtkWidget* t1_label;
	GtkWidget* t2_label;
	GtkWidget* s0_label;
	GtkWidget* s1_label;
	GtkWidget* k0_label;
	GtkWidget* sp_label;
	GtkWidget* fp_label;
	GtkWidget* ra_label;

	GtkWidget* instr_addr_0;
	GtkWidget* instr_addr_1;
    GtkWidget* instr_addr_2;
    GtkWidget* instr_addr_3;
    GtkWidget* instr_addr_4;
    GtkWidget* instr_addr_5;
    GtkWidget* instr_addr_6;
    GtkWidget* instr_addr_7;
    GtkWidget* instr_addr_8;
    GtkWidget* instr_addr_9;
    GtkWidget* instr_addr_10;
    GtkWidget* instr_addr_11;
    GtkWidget* instr_addr_12;
    GtkWidget* instr_addr_13;
    GtkWidget* instr_addr_14;

	GtkWidget* instr_val_0;
	GtkWidget* instr_val_1;
    GtkWidget* instr_val_2;
    GtkWidget* instr_val_3;
    GtkWidget* instr_val_4;
    GtkWidget* instr_val_5;
    GtkWidget* instr_val_6;
    GtkWidget* instr_val_7;
    GtkWidget* instr_val_8;
    GtkWidget* instr_val_9;
    GtkWidget* instr_val_10;
    GtkWidget* instr_val_11;
    GtkWidget* instr_val_12;
    GtkWidget* instr_val_13;
    GtkWidget* instr_val_14;
    
} MULT_GPOINTERS_STR;
typedef MULT_GPOINTERS_STR * MULT_GPOINTERS_STR_p;


/*prototypes*/
void set_up_tables();
void select_file(GtkWidget *, gpointer);
void step(GtkWidget *, gpointer);
void run_through(GtkWidget *, gpointer);
void update_registers(void);
void update_instructions(void);
void reset(GtkWidget *, gpointer);
void quit(GtkWidget *, gpointer);


