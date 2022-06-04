#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

gint i = 20;

gboolean add (GtkLabel *label, gpointer pointer)
 {
   i += 1;
   gchar str2[5];
   strcpy(str2, (char*) atoi(i));
   gtk_label_set_text(label, str2);

   return TRUE;
 }

int main(int argc, char **argv)
  {
    gchar str1[5];
    GtkWidget *window, *vbox, *n, *hbox, *bt1, *bt2, *bt3, *bt4;

    strcpy(str1, argv[1]);
    
    gtk_init(&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);
    gtk_window_set_title (GTK_WINDOW(window), "Programa 09_2");
    gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    
    g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add (GTK_CONTAINER(window), vbox);

    // button = gtk_button_new_with_label (str1);
    n = gtk_label_new(str1);
    //gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, TRUE, 20);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_add (GTK_CONTAINER(vbox), hbox);

    bt1 = gtk_button_new_with_label ("+");
    gtk_box_pack_start(GTK_BOX (hbox), bt1, FALSE, TRUE, 30);
    g_signal_connect (G_OBJECT (bt1), "clicked", G_CALLBACK(add), NULL);
    
    bt2 = gtk_button_new_with_label ("-");
    gtk_box_pack_start(GTK_BOX (hbox), bt2, FALSE, TRUE, 50);
    
    bt3 = gtk_button_new_with_label ("x");
    gtk_box_pack_start(GTK_BOX (hbox), bt3, FALSE, TRUE, 30);

    
    bt4 = gtk_button_new_with_label ("/");
    gtk_box_pack_start(GTK_BOX (hbox), bt4, FALSE, TRUE, 30);
    
    gtk_widget_show_all (window);
    gtk_main();

    return 0;
  }
