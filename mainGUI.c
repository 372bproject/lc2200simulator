#include "mainGUI.h"

FSM_STR_p GLOBAL_FSM_p;
MULT_GPOINTERS_STR_p GLOBAL_WIDGET_OBJECTS_p;

int main (int argc, char * argv []) {
	
	gtk_init(&argc, &argv);

	/*Create logical back end*/
	GLOBAL_FSM_p = FSM_constructor();

	GLOBAL_WIDGET_OBJECTS_p = (MULT_GPOINTERS_STR_p) malloc (sizeof(MULT_GPOINTERS_STR));
    GLOBAL_WIDGET_OBJECTS_p->absolute_path = (char *) malloc(sizeof(char) * 100);

	//if argument passed in, treat as filepath
	if (argc == 2) {
		if (argv[1][0] == '/') { //absolute path
			strcpy(GLOBAL_WIDGET_OBJECTS_p->absolute_path, argv[1]);
		} else { //relative path
			strcpy(GLOBAL_WIDGET_OBJECTS_p->absolute_path, "./");
			strcat(GLOBAL_WIDGET_OBJECTS_p->absolute_path, argv[1]);
		}
		GLOBAL_FSM_p = FSM_initialize(GLOBAL_FSM_p, GLOBAL_WIDGET_OBJECTS_p->absolute_path);
	}



	/*******************/
	/****GTK objects****/
	/*******************/
	GtkWidget* window;
	//boxes
	GtkWidget* outer_box;
	GtkWidget* upper_button_box;
	GtkWidget* upper_half_box;
	GtkWidget* instructions_box;
	GtkWidget* registers_box;
	GtkWidget* button_box;
	GtkWidget* lower_half_box;
	GtkWidget* heap_box;
	GtkWidget* stack_box;
	//labels
	GtkWidget* instructions_label;
	GtkWidget* registers_label;
	GtkWidget* heap_label;
	GtkWidget* stack_label;
	//tables
	GtkWidget* instructions_table;
	GtkWidget* registers_table;
	GtkWidget* heap_table;
	GtkWidget* stack_table;
	//buttons
	GtkWidget* select_file_b;
	GtkWidget* step_b;
	GtkWidget* run_through_b;
	GtkWidget* reset_b;


	/*******************/
	/**create widgets***/
	/*******************/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//boxes
	outer_box = gtk_vbox_new(0, 0);//homogenous, spacing, 
	upper_button_box = gtk_vbox_new(0, 50);
	upper_half_box = gtk_hbox_new(0, 0);
	instructions_box = gtk_vbox_new(0, 10); 
	registers_box = gtk_vbox_new(0, 0);
	button_box = gtk_hbox_new(0, 10);
	lower_half_box = gtk_hbox_new(0, 10);
	heap_box = gtk_vbox_new(0, 10);
	stack_box = gtk_vbox_new(0, 10);
	//labels
	instructions_label = gtk_label_new("INSTRUCTIONS");
	registers_label = gtk_label_new("REGISTERS");
	heap_label = gtk_label_new("HEAP (NOT AVAILABLE IN TRIAL VERSION)");
	stack_label = gtk_label_new("STACK");
	//tables
	instructions_table = gtk_table_new(15, 15, 0);
	registers_table = gtk_table_new(15, 2, 0);
	heap_table = gtk_table_new(20, 2, 0);
	stack_table = gtk_table_new(20, 2, 0);
	//buttons
	select_file_b = gtk_button_new_with_label("Select File (If this crashes, pass in file path as argument to ./mainGUI)");
	step_b = gtk_button_new_with_label("STEP");
	run_through_b = gtk_button_new_with_label("RUN THROUGH");
	reset_b = gtk_button_new_with_label("RESET");

	//save labels/tables to global struct
	GLOBAL_WIDGET_OBJECTS_p->instructions_table = instructions_table;
	GLOBAL_WIDGET_OBJECTS_p->registers_table = registers_table;
	GLOBAL_WIDGET_OBJECTS_p->heap_table = heap_table;
	GLOBAL_WIDGET_OBJECTS_p->stack_table = stack_table;

	/*********************/
	/*format & containers*/
	/*********************/
	//boxes gtk_box_pack_? (container, item, fully fill space, fill with itself, spacing)
	gtk_container_add(GTK_CONTAINER(window), outer_box);
	gtk_box_pack_start(GTK_BOX(outer_box), upper_button_box, 0, 1, 0); 
	gtk_box_pack_start(GTK_BOX(outer_box), upper_half_box, 0, 0, 50); 
	/*upper half box*/
	gtk_box_pack_start(GTK_BOX(upper_half_box), instructions_box, 0, 100, 0);
	gtk_box_pack_end(GTK_BOX(upper_half_box), registers_box, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(outer_box), button_box, 0, 0, 0); 
	/*lower half box*/
	gtk_box_pack_start(GTK_BOX(outer_box), lower_half_box, 0, 0, 50);
	gtk_box_pack_start(GTK_BOX(lower_half_box), heap_box, 0, 0, 0); 
	gtk_box_pack_end(GTK_BOX(lower_half_box), stack_box, 0, 0, 0); 

	//labels
	gtk_box_pack_start(GTK_BOX(instructions_box), instructions_label, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(registers_box), registers_label, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(heap_box), heap_label, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(stack_box), stack_label, 0, 0, 0);
	//tables
	gtk_box_pack_end(GTK_BOX(instructions_box), instructions_table, 0, 0, 0);
	gtk_box_pack_end(GTK_BOX(registers_box), registers_table, 0, 0, 0);
	gtk_box_pack_end(GTK_BOX(heap_box), heap_table, 0, 0, 0);
	gtk_box_pack_end(GTK_BOX(stack_box), stack_table, 0, 0, 0);
	set_up_tables();
	//buttons
	gtk_box_pack_start(GTK_BOX(upper_button_box), select_file_b, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(button_box), step_b, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(button_box), run_through_b, 0, 0, 0);
	gtk_box_pack_end(GTK_BOX(button_box), reset_b, 0, 0, 0);


	/*******************/
	/**connect signals**/
	/*******************/
	g_signal_connect(window, "delete-event", G_CALLBACK(quit), NULL);
	//buttons
	g_signal_connect(select_file_b, "clicked", G_CALLBACK(select_file), (gpointer)window);
	g_signal_connect(step_b, "clicked", G_CALLBACK(step), NULL);
	g_signal_connect(run_through_b, "clicked", G_CALLBACK(run_through), NULL);
	g_signal_connect(reset_b, "clicked", G_CALLBACK(reset), NULL);

	/***********************/
	/*set sizes and visuals*/
	/***********************/
	gtk_window_set_title(GTK_WINDOW(window), "LC2200 Knockoff Simulator");
	gtk_widget_set_size_request(window, 600, 800);
	gtk_widget_show_all(window);
	
	gtk_main();
	return 0;	
	
}

void set_up_tables() {

	GLOBAL_WIDGET_OBJECTS_p->pc = gtk_label_new("0");
	GLOBAL_WIDGET_OBJECTS_p->zero = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->at = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->v0 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->a0 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->a1 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->a2 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->t0 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->t1 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->t2 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->s0 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->s1 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->k0 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->sp = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->fp = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->ra = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->pc_label = gtk_label_new("pc:");
    GLOBAL_WIDGET_OBJECTS_p->zero_label = gtk_label_new("zero:");
    GLOBAL_WIDGET_OBJECTS_p->at_label = gtk_label_new("at:");
    GLOBAL_WIDGET_OBJECTS_p->v0_label = gtk_label_new("v0:");
    GLOBAL_WIDGET_OBJECTS_p->a0_label = gtk_label_new("a0:");
    GLOBAL_WIDGET_OBJECTS_p->a1_label = gtk_label_new("a1:");
    GLOBAL_WIDGET_OBJECTS_p->a2_label = gtk_label_new("a2:");
    GLOBAL_WIDGET_OBJECTS_p->t0_label = gtk_label_new("t0:");
    GLOBAL_WIDGET_OBJECTS_p->t1_label = gtk_label_new("t1:");
    GLOBAL_WIDGET_OBJECTS_p->t2_label = gtk_label_new("t2:");
    GLOBAL_WIDGET_OBJECTS_p->s0_label = gtk_label_new("s0:");
    GLOBAL_WIDGET_OBJECTS_p->s1_label = gtk_label_new("s1:");
    GLOBAL_WIDGET_OBJECTS_p->k0_label = gtk_label_new("k0:");
    GLOBAL_WIDGET_OBJECTS_p->sp_label = gtk_label_new("sp:");
    GLOBAL_WIDGET_OBJECTS_p->fp_label = gtk_label_new("fp:");
    GLOBAL_WIDGET_OBJECTS_p->ra_label = gtk_label_new("ra:");

	GLOBAL_WIDGET_OBJECTS_p->instr_addr_0 = gtk_label_new("Address");
	GLOBAL_WIDGET_OBJECTS_p->instr_addr_1 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_addr_2 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_addr_3 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_addr_4 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_addr_5 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_addr_6 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_addr_7 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_addr_8 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_addr_9 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_addr_10 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_addr_11 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_addr_12 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_addr_13 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_addr_14 = gtk_label_new("0");

	GLOBAL_WIDGET_OBJECTS_p->instr_val_0 = gtk_label_new("OPCODE");
	GLOBAL_WIDGET_OBJECTS_p->instr_val_1 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_val_2 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_val_3 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_val_4 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_val_5 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_val_6 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_val_7 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_val_8 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_val_9 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_val_10 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_val_11 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_val_12 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_val_13 = gtk_label_new("0");
    GLOBAL_WIDGET_OBJECTS_p->instr_val_14 = gtk_label_new("0");

	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->pc_label, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->zero_label, 0, 1, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->v0_label, 0, 1, 2, 3, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->a0_label, 0, 1, 4, 5, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->a1_label, 0, 1, 5, 6, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->a2_label, 0, 1, 6, 7, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->t0_label, 0, 1, 7, 8, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->t1_label, 0, 1, 8, 9, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->t2_label, 0, 1, 9, 10, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->s0_label, 0, 1, 10, 11, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->s1_label, 0, 1, 11, 12, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->k0_label, 0, 1, 12, 13, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->sp_label, 0, 1, 13, 14, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->fp_label, 0, 1, 14, 15, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->ra_label, 0, 1, 15, 16, GTK_FILL, GTK_FILL, 0, 0);

	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->pc, 1, 2, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->zero, 1, 2, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->v0, 1, 2, 2, 3, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->a0, 1, 2, 4, 5, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->a1, 1, 2, 5, 6, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->a2, 1, 2, 6, 7, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->t0, 1, 2, 7, 8, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->t1, 1, 2, 8, 9, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->t2, 1, 2, 9, 10, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->s0, 1, 2, 10, 11, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->s1, 1, 2, 11, 12, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->k0, 1, 2, 12, 13, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->sp, 1, 2, 13, 14, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->fp, 1, 2, 14, 15, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->registers_table), GLOBAL_WIDGET_OBJECTS_p->ra, 1, 2, 15, 16, GTK_FILL, GTK_FILL, 0, 0);

	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_addr_0, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_addr_1, 0, 1, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_addr_2, 0, 1, 2, 3, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_addr_3, 0, 1, 4, 5, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_addr_4, 0, 1, 5, 6, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_addr_5, 0, 1, 6, 7, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_addr_6, 0, 1, 7, 8, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_addr_7, 0, 1, 8, 9, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_addr_8, 0, 1, 9, 10, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_addr_9, 0, 1, 10, 11, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_addr_10, 0, 1, 11, 12, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_addr_11, 0, 1, 12, 13, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_addr_12, 0, 1, 13, 14, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_addr_13, 0, 1, 14, 15, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_addr_14, 0, 1, 15, 16, GTK_FILL, GTK_FILL, 0, 0);

	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_val_0, 14, 15, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_val_1, 14, 15, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_val_2, 14, 15, 2, 3, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_val_3, 14, 15, 4, 5, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_val_4, 14, 15, 5, 6, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_val_5, 14, 15, 6, 7, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_val_6, 14, 15, 7, 8, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_val_7, 14, 15, 8, 9, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_val_8, 14, 15, 9, 10, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_val_9, 14, 15, 10, 11, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_val_10, 14, 15, 11, 12, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_val_11, 14, 15, 12, 13, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_val_12, 14, 15, 13, 14, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_val_13, 14, 15, 14, 15, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(GLOBAL_WIDGET_OBJECTS_p->instructions_table), GLOBAL_WIDGET_OBJECTS_p->instr_val_14, 14, 15, 15, 16, GTK_FILL, GTK_FILL, 0, 0);
}

void select_file (GtkWidget* widget, gpointer window) {

	char * filename;
	GtkWidget * dialog;
	dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL); puts("hi");
	//gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), "/"); //set directory of chooser
	gtk_widget_show_all(dialog); 
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if (response == GTK_RESPONSE_ACCEPT) {

		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		sprintf(GLOBAL_WIDGET_OBJECTS_p->absolute_path, "%s", filename);		
		free(filename);
		if (GLOBAL_FSM_p->memory_module_p != NULL) {//if choosing a file for the second time
			FSM_destroy(GLOBAL_FSM_p);
		}
		GLOBAL_FSM_p = FSM_initialize(GLOBAL_FSM_p, GLOBAL_WIDGET_OBJECTS_p->absolute_path);
	} else {
		gtk_widget_destroy(dialog);
	}
}

void step (GtkWidget* widget, gpointer data) {

	//step 1 instruction
	if (FSM_step(GLOBAL_FSM_p)) {
		update_registers();
		update_instructions();
	} else {
		puts("Simulation Finished");
	}
	
}



void run_through (GtkWidget* widget, gpointer data) {

	FSM_run_through(GLOBAL_FSM_p);
	update_registers();
	update_instructions();
}



void update_registers() {

	char pc_val[15];
	char zero_val[15];
	char at_val[15];
	char v0_val[15];
	char a0_val[15];
	char a1_val[15];
	char a2_val[15];
	char t0_val[15];
	char t1_val[15];
	char t2_val[15];
	char s0_val[15];
	char s1_val[15];
	char k0_val[15];
	char sp_val[15];
	char fp_val[15];
	char ra_val[15];

	FSM_get_registers(GLOBAL_FSM_p, GLOBAL_WIDGET_OBJECTS_p->registers_array);

	sprintf(pc_val, "%6d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[0] + GLOBAL_FSM_p->start_address);
	sprintf(zero_val, "%4d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[1]);
	sprintf(at_val, "%4d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[2]);
	sprintf(v0_val, "%4d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[3]);
	sprintf(a0_val, "%4d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[4]);
	sprintf(a1_val, "%4d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[5]);
	sprintf(a2_val, "%4d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[6]);
	sprintf(t0_val, "%4d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[7]);
	sprintf(t1_val, "%4d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[8]);
	sprintf(t2_val, "%4d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[9]);
	sprintf(s0_val, "%4d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[10]);
	sprintf(s1_val, "%4d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[11]);
	sprintf(k0_val, "%4d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[12]);
	sprintf(sp_val, "%4d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[13]);
	sprintf(fp_val, "%4d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[14]);
	sprintf(ra_val, "%4d\0", GLOBAL_WIDGET_OBJECTS_p->registers_array[15]);

	//update view (registers view)
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->pc), pc_val);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->at), at_val);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->v0), v0_val);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->a0), a0_val);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->a1), a1_val);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->a2), a2_val);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->t0), t0_val);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->t1), t1_val);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->t2), t2_val);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->s0), s0_val);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->s1), s1_val);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->k0), k0_val);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->sp), sp_val);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->fp), fp_val);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->ra), ra_val);

}

void update_instructions() {

	int i;
	char instr_addr_array[14][14];
	char instr_val_array[14][14];

	for (i = 0; i < 15; i++) {
		sprintf(instr_addr_array[i], "%6d\0", GLOBAL_FSM_p->start_address + GLOBAL_FSM_p->pc + i);
		sprintf(instr_val_array[i], "%6d\0", GLOBAL_FSM_p->memory_module_p->address_start_p[GLOBAL_FSM_p->pc + i]);
	}

	//update view (instructions view)
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_addr_1), instr_addr_array[0]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_addr_2), instr_addr_array[1]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_addr_3), instr_addr_array[2]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_addr_4), instr_addr_array[3]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_addr_5), instr_addr_array[4]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_addr_6), instr_addr_array[5]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_addr_7), instr_addr_array[6]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_addr_8), instr_addr_array[7]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_addr_9), instr_addr_array[8]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_addr_10), instr_addr_array[9]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_addr_11), instr_addr_array[10]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_addr_12), instr_addr_array[11]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_addr_13), instr_addr_array[12]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_addr_14), instr_addr_array[13]);

	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_val_1), instr_val_array[0]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_val_2), instr_val_array[1]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_val_3), instr_val_array[2]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_val_4), instr_val_array[3]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_val_5), instr_val_array[4]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_val_6), instr_val_array[5]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_val_7), instr_val_array[6]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_val_8), instr_val_array[7]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_val_9), instr_val_array[8]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_val_10), instr_val_array[9]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_val_11), instr_val_array[10]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_val_12), instr_val_array[11]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_val_13), instr_val_array[12]);
	gtk_label_set_text(GTK_LABEL(GLOBAL_WIDGET_OBJECTS_p->instr_val_14), instr_val_array[13]);

}


void reset (GtkWidget* widget, gpointer data) {

	FSM_reset(GLOBAL_FSM_p);
	update_registers();
	update_instructions();

}

void quit (GtkWidget* widget, gpointer data) {

	//destroy all gtk widgets
	//gtk_widget_destroy();

	free(GLOBAL_WIDGET_OBJECTS_p);
	FSM_destroy(GLOBAL_FSM_p);
	FSM_destructor(GLOBAL_FSM_p);
	gtk_main_quit();
}
