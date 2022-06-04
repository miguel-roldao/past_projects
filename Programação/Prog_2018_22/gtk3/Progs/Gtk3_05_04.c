/*****************************************************
 *                                                   *
 *      Toolbar                                      *
 *                                                   *
 *      GTK+ 3                                       *
 *      Versao: 1.0                                  *
 *      Samuel Eleuterio 2015                        *
 *                                                   *
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

GtkWindowType       winType     = GTK_WINDOW_TOPLEVEL ;
GtkWindowPosition   winPos      = GTK_WIN_POS_CENTER  ;

gchar              *winTitle    = "Toolbar: Troca Orientação" ;
gint                xlen        = 350 ;
gint                ylen        = 270 ;

GtkWidget *box, *sep ;

GtkWidget *
cria_toolbar (void)
{
  GtkWidget *toolbar ;
  GtkToolItem *tb_new, *tb_open, *tb_save, *tb_sep, *tb_exit ;

  toolbar = gtk_toolbar_new ();
  gtk_toolbar_set_style (GTK_TOOLBAR(toolbar), GTK_TOOLBAR_BOTH);
  gtk_toolbar_set_show_arrow (GTK_TOOLBAR(toolbar), FALSE);
  gtk_container_set_border_width(GTK_CONTAINER (toolbar), 2);

  tb_new = gtk_tool_button_new (NULL, "New");
  gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON(tb_new), "document-new");
  gtk_toolbar_insert (GTK_TOOLBAR(toolbar), tb_new, -1);

  tb_open = gtk_tool_button_new (NULL, "Open");
  gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON(tb_open), "document-open");
  gtk_toolbar_insert (GTK_TOOLBAR(toolbar), tb_open, -1);

  tb_save = gtk_tool_button_new (NULL, "Save");
  gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON(tb_save), "document-save");
  gtk_toolbar_insert (GTK_TOOLBAR(toolbar), tb_save, -1);

  tb_sep = gtk_separator_tool_item_new ();
  gtk_toolbar_insert (GTK_TOOLBAR(toolbar), tb_sep, -1); 

  tb_exit = gtk_tool_button_new (NULL, "Quit");
  gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON(tb_exit), "application-exit");
  gtk_toolbar_insert (GTK_TOOLBAR(toolbar), tb_exit, -1);

  g_signal_connect (G_OBJECT(tb_exit), "clicked", G_CALLBACK(gtk_main_quit), NULL);

  return toolbar;
}

gboolean
exec_change (GtkWidget *widget ,
             GtkWidget *tbar   )
{
  if (gtk_orientable_get_orientation (GTK_ORIENTABLE(tbar)) == GTK_ORIENTATION_VERTICAL)
    {
      gtk_orientable_set_orientation (GTK_ORIENTABLE(tbar), GTK_ORIENTATION_HORIZONTAL);
      gtk_orientable_set_orientation (GTK_ORIENTABLE(sep), GTK_ORIENTATION_HORIZONTAL);
      gtk_orientable_set_orientation (GTK_ORIENTABLE(box), GTK_ORIENTATION_VERTICAL);
    }
  else
    {
      gtk_orientable_set_orientation (GTK_ORIENTABLE(tbar), GTK_ORIENTATION_VERTICAL);
      gtk_orientable_set_orientation (GTK_ORIENTABLE(sep), GTK_ORIENTATION_VERTICAL);
      gtk_orientable_set_orientation (GTK_ORIENTABLE(box), GTK_ORIENTATION_HORIZONTAL);
    }

  return FALSE;
}

int
main (int argc, char **argv)
{
  GtkWidget *window, *toolbar, *hbox, *vbox1, *button ;

  gtk_init (&argc, &argv);

  window = gtk_window_new (winType);
  gtk_window_set_default_size (GTK_WINDOW(window), xlen, ylen);
  gtk_window_set_title (GTK_WINDOW(window), winTitle);
  gtk_window_set_position (GTK_WINDOW(window), winPos);

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(window), box);

  // Cria toolbar

  toolbar = cria_toolbar ();
  gtk_box_pack_start (GTK_BOX(box), toolbar, FALSE, FALSE, 3);

  sep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX(box), sep, FALSE, TRUE, 0);

  // Cria troca

  vbox1 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_end (GTK_BOX(box), vbox1, FALSE, TRUE, 0);
  
  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end (GTK_BOX(vbox1), hbox, FALSE, TRUE, 0);

  button = gtk_button_new_with_label (" Troca ");
  g_signal_connect (G_OBJECT(button), "clicked", G_CALLBACK(exec_change), toolbar);
  gtk_container_set_border_width (GTK_CONTAINER(button), 10);
  gtk_box_pack_end (GTK_BOX(hbox), button, FALSE, TRUE, 0);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
