/*****************************************************
 *                                                   *
 *      entry                                        *
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

GtkWidget  *entry1, *label1 ;

gboolean
func_button1 (GtkWidget  *w    ,
              gpointer    data )
{
  const gchar *str1 ;

  str1 = gtk_entry_get_text (GTK_ENTRY(entry1));
  gtk_label_set_text (GTK_LABEL(label1), str1);

  return FALSE;
}

gboolean
func_visivel (GtkWidget  *w     ,
              GtkWidget  *entry )
{
  if (gtk_entry_get_visibility (GTK_ENTRY(entry)))
    gtk_entry_set_visibility (GTK_ENTRY(entry), FALSE);
  else
    gtk_entry_set_visibility (GTK_ENTRY(entry), TRUE);

  return FALSE;
}

GtkWidget *
create_entry (void)
{
  GtkWidget  *entry ;
  
  entry = gtk_entry_new ();
  gtk_entry_set_max_length (GTK_ENTRY(entry), 10);
  gtk_entry_set_width_chars (GTK_ENTRY(entry), 20);
  gtk_widget_set_size_request (entry, 100, 29);
  gtk_entry_set_text (GTK_ENTRY(entry), "23");
  gtk_entry_set_visibility (GTK_ENTRY(entry), FALSE);
  
  gtk_entry_set_icon_from_icon_name (GTK_ENTRY(entry), GTK_ENTRY_ICON_PRIMARY, "face-smile");
  gtk_entry_set_icon_from_icon_name (GTK_ENTRY(entry), GTK_ENTRY_ICON_SECONDARY, "face-tired");

  return entry;
}

int
main (int argc, char **argv)
{
  GtkWidget  *window, *vbox, *hbox0, *hbox1, *hbox2 ;
  GtkWidget  *button1, *label0 ;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(window), 450, 300);
  gtk_widget_set_size_request (window, 400, 250);

  gtk_window_set_title (GTK_WINDOW (window), "GTK-Ex: Entrada de Dados");
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);

  g_signal_connect_swapped (G_OBJECT (window), "destroy",
                            G_CALLBACK(gtk_main_quit), NULL);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);

  // label0

  label0 = gtk_label_new ("Entry");
  gtk_box_pack_start (GTK_BOX (vbox), label0, FALSE, TRUE, 10);

  // entry

  hbox0 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox0, FALSE, TRUE, 50);

  entry1 = create_entry ();
  gtk_box_pack_start (GTK_BOX (hbox0), entry1, TRUE, FALSE, 10);
  
  // label1

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_homogeneous (GTK_BOX(hbox2), TRUE);
  gtk_box_pack_end (GTK_BOX (vbox), hbox2, FALSE, TRUE, 20);

  label1 = gtk_label_new ("Value");
  gtk_box_pack_start (GTK_BOX (hbox2), label1, FALSE, TRUE, 20);

  // button1

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
  gtk_box_pack_end (GTK_BOX (vbox), hbox1, FALSE, TRUE, 10);

  button1 = gtk_button_new_with_label ("Entry Value");
  gtk_widget_set_size_request (button1, 150, 30);
  g_signal_connect (button1, "clicked", G_CALLBACK (func_button1), NULL);
  gtk_box_pack_start (GTK_BOX (hbox1), button1, TRUE, FALSE, 10);

  button1 = gtk_button_new_with_label ("Visibilidade");
  gtk_widget_set_size_request (button1, 150, 30);
  g_signal_connect (button1, "clicked", G_CALLBACK (func_visivel), entry1);
  gtk_box_pack_end (GTK_BOX (hbox1), button1, TRUE, FALSE, 10);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
