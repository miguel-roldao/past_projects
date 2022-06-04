/*****************************************************
 *                                                   *
 *      Uso de "css" para atribuição de cor:         *
 *          Window, Label                            *
 *                                                   *
 *      GTK+ 3                                       *
 *      Versao: 1.0                                  *
 *      Samuel Eleuterio 2016                        *
 *                                                   *
 *      Exemplo inspirado no 'The GTK+ tutorial'     *
 *                                                   *
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <gtk/gtk.h>

GtkWindowType       winType     = GTK_WINDOW_TOPLEVEL ;
GtkWindowPosition   winPos      = GTK_WIN_POS_CENTER  ;

gchar              *winTitle    = "GTK-Ex: box, buttons, label" ;
gchar               chlabel[32] = "Valor actual: " ;

gint                xlen        = 400 ;
gint                ylen        = 230 ;
gint                contador    = 0   ;
gint                len_chlabel       ;

#if GTK_CHECK_VERSION(3,22,0)
gchar *cssData = "window {background-color: Wheat1; border-radius: 30px; border-color: #000;box-shadow: 0 0 5px #333 inset; margin: 10px;}\n"
                 ".label_Main {color: #ab0567; font-family: Tahoma; font-weight: bold; font-size: 16px;}\n"
                 ".btminus label {background-color: red; color: cyan; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n"
                 ".btplus label {background-color: blue; color: yellow; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n";
#else
gchar *cssData = "GtkWindow {background-color: Wheat1; border-radius: 30px; border-color: #000;box-shadow: 0 0 5px #333 inset; margin: 10px;}\n"
                 ".label_Main {color: #ab0567; font-family: Tahoma; font-weight: bold; font-size: 16px;}\n"
                 ".btminus GtkLabel {background-color: red; color: cyan; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n"
                 ".btplus GtkLabel {background-color: blue; color: yellow; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n";
#endif

void
provider_create (gchar *chData)
{
  GtkCssProvider *provider ;
  GdkDisplay     *display  ;
  GdkScreen      *screen   ;

  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);

  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);

  gtk_css_provider_load_from_data (GTK_CSS_PROVIDER (provider), chData, -1, NULL);
  g_object_unref (provider);
}

gboolean 
cb_plus (GtkWidget *widget , 
         gpointer   label  )
{
  ++contador;
  sprintf (&chlabel[len_chlabel], "%d", contador);
  gtk_label_set_text(label, chlabel);

  return FALSE;
}

gboolean 
cb_minus (GtkWidget *widget , 
          gpointer   label  )
{
  --contador;
  sprintf (&chlabel[len_chlabel], "%d", contador);
  gtk_label_set_text(label, chlabel);

  return FALSE;
}

int
main (int argc, char **argv)
{
  GtkWidget *window, *vbox, *hbox1, *hbox2, *bplus, *bminus, *label ;
  GtkStyleContext  *context ;
  int  len ;
  char ch_minus[8] ;

  setlocale (LC_ALL, "");
  len = wctomb (ch_minus, 8210);
  ch_minus[len] = 0;

  len_chlabel = strlen (chlabel);
  sprintf (&chlabel[len_chlabel], "%d", contador);

  gtk_init (&argc, &argv);
  provider_create (cssData);

  window = gtk_window_new (winType);
  gtk_window_set_default_size (GTK_WINDOW(window), xlen, ylen);
  gtk_window_set_title (GTK_WINDOW(window), winTitle);
  gtk_window_set_position (GTK_WINDOW(window), winPos);

  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(window), vbox);

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX(vbox), hbox1, TRUE, TRUE, 0);

  label = gtk_label_new (chlabel);
  context = gtk_widget_get_style_context (label);
  gtk_style_context_add_class (context, "label_Main");
  gtk_box_pack_start (GTK_BOX(hbox1), label, TRUE, FALSE, 0);

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end (GTK_BOX(vbox), hbox2, FALSE, TRUE, 20);

  bminus = gtk_button_new_with_label (ch_minus);
  context = gtk_widget_get_style_context (bminus);
  gtk_style_context_add_class (context, "btminus");
  gtk_widget_set_size_request (bminus, 80, 35);
  g_signal_connect (bminus, "clicked", G_CALLBACK(cb_minus), label);
  gtk_box_pack_start (GTK_BOX(hbox2), bminus, FALSE, TRUE, 20);

  bplus = gtk_button_new_with_label ("+");
  gtk_style_context_add_class (gtk_widget_get_style_context (bplus), "btplus");
  gtk_widget_set_size_request (bplus, 80, 35);
  g_signal_connect (bplus, "clicked", G_CALLBACK(cb_plus), label);
  gtk_box_pack_end (GTK_BOX(hbox2), bplus, FALSE, TRUE, 20);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
