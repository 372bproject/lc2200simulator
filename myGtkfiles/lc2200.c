#include <gtk/gtk.h>

	enum
	{
	col_zero = 0,
	col_at,
	col_v0,
	col_a0,
	NUM_COLS = 4
	} ;


	static GtkTreeModel *createModel (void)
	{
	GtkListStore *store;
	GtkTreeIter    iter;
	store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING );
	
	/*
	*Append a row and fill in some data
	*/
	
	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter,
	col_zero, "00100",
	col_at, "10100",
	col_v0, "10011",
	col_a0, "00010",
	-1);
	
	/*
	*append another row and fill in some data
	*/
	
	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter,
	col_zero, "00000",
	col_at, "11001",
	col_v0, "11111",
	col_a0, "00000",
	-1);
	
	/*
	*... and a third row
	*/
	
	

	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter,
	col_zero, "01110",
	col_at, "11000",
	col_v0, "11110",
	col_a0, "00001",
	-1);

	return GTK_TREE_MODEL (store);
	}

	static GtkWidget *createViewModel (void)
	{
	GtkCellRenderer *renderer;
	GtkTreeModel *model;
	GtkWidget *view;
	view = gtk_tree_view_new ();

	
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
	-1,
	"$Zero",
	renderer,
	"text", col_zero,
	NULL);
	
	
	
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
	-1,
	"$at",
	renderer,
	"text", col_at,
	NULL);
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
	-1,
	"$v0",
	renderer,
	"text", col_v0,
	NULL);

	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
	-1,
	"$a0",
	renderer,
	"text", col_a0,
	NULL);

	model = createModel ();
	gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);
	
	/*
	*The tree view has acquired its own reference to the
	*
	*model, so we can drop ours. That way the model will
	*
	*be freed automatically when the tree view is destroyed
	*/
	
	g_object_unref (model);
	return view;
	}




static void run(GtkWidget *widget, gpointer item){
 g_print ("Hello World\n");
}
/*
static void reset(GtkWidget *widget, gpointer item){
 
}

static void step(GtkWidget *widget, gpointer item){
 
}

static void stop(GtkWidget *widget, gpointer item){
 
}
*/
/**
static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}
*/

int
main (int   argc,
      char *argv[])
{
  GtkBuilder *builder;



  GObject *window;
  GObject *button;
  GObject *view;
  GObject *scrol;

  gtk_init (&argc, &argv);

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new ();
  gtk_builder_add_from_file (builder, "lc2200.glade", NULL);

	
  /* Connect signal handlers to the constructed widgets. */
  window = gtk_builder_get_object (builder, "window1");
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  scrol = gtk_builder_get_object(builder, "scrolledwindow1");
  view = createViewModel();
  gtk_container_add (GTK_CONTAINER (scrol), view);
  gtk_widget_show_all (view);
/*
  
  g_signal_connect(view, "activate", G_CALLBACK(createViewModel), NULL);
*/
  button = gtk_builder_get_object (builder, "runB");
  g_signal_connect (button, "clicked", G_CALLBACK (run), NULL);

  button = gtk_builder_get_object (builder, "stepB");
  g_signal_connect (button, "clicked", G_CALLBACK (run), NULL);

  button = gtk_builder_get_object (builder, "stopB");
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

/*
  button = gtk_builder_get_object (builder, "load");
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);
*/

  button = gtk_builder_get_object (builder, "resetB");
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);
/**
  txtview = gtk_builder_object(builder, "textview2");
  g_signal_connect(txtview, "activate", G_CALLBACK(run), NULL);
*/

  gtk_main ();

  return 0;
}
