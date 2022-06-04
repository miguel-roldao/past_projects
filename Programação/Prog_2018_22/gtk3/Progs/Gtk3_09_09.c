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
#include <time.h>
#include <gtk/gtk.h>

GtkWindowType       winType     = GTK_WINDOW_TOPLEVEL ;
GtkWindowPosition   winPos      = GTK_WIN_POS_CENTER  ;

gchar              *winTitle    = "GTK-Ex: box, buttons, label" ;
gchar               chlabel[32] = "Valor actual: " ;

gint                xlen        = 400 ;
gint                ylen        = 230 ;
gint                contador    = 0   ;
gint                len_chlabel       ;

gchar *cssData = "@define-color color1 #ab0567;\n"
                 "#window {background-color: Wheat1;}\n"
                 ".label_Main {font-family: Tahoma; font-weight: bold; font-size: 16px;}\n"
                 ".LabelColor1 {color: @color1;}\n"
#if GTK_CHECK_VERSION(3,22,0)
                 ".btminus label {background-color: red; color: cyan; border: 1px solid cyan; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n"
                 ".btminus:hover label {background-color: DarkSalmon; color: cyan; border: 1px solid red; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n"
                 ".btminus:active label {background-color: cyan; color: red; border: 1px solid red; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n"

                 ".btplus label {background-color: blue; color: yellow; border: 1px solid yellow; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n"
                 ".btplus:hover label {background-color: SteelBlue3; color: yellow; border: 1px solid blue; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n"
                 ".btplus:active label {background-color: yellow; color: blue; border: 1px solid blue; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n";
#else
                 ".btminus GtkLabel {background-color: red; color: cyan; border: 1px solid cyan; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n"
                 ".btminus:hover GtkLabel {background-color: DarkSalmon; color: cyan; border: 1px solid red; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n"
                 ".btminus:active GtkLabel {background-color: cyan; color: red; border: 1px solid red; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n"

                 ".btplus GtkLabel {background-color: blue; color: yellow; border: 1px solid yellow; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n"
                 ".btplus:hover GtkLabel {background-color: SteelBlue3; color: yellow; border: 1px solid blue; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n"
                 ".btplus:active GtkLabel {background-color: yellow; color: blue; border: 1px solid blue; font-family: Tahoma; font-weight: bold; font-size: 18px;}\n";
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

void
change_color_label (GtkWidget  *label)
{
  int               n1, n2 ;
  gchar             ch1[8], cssData2[32] ;
  gchar            *chhex = "0123456789ABCDEF" ;
  GtkStyleContext  *context ;

  ch1[0] = '#';
  for (n1 = 1 ; n1 <= 6 ; ++n1)
    {
      n2 = rand () % 16;
      ch1[n1] = chhex[n2];
    }
  ch1[n1] = 0;
  sprintf (cssData2, ".LabelColor1 {color: %s;}", ch1);

  provider_create (cssData2);
  context = gtk_widget_get_style_context (label);
  gtk_style_context_add_class (context, "LabelColor1");
}

gboolean 
cb_plus (GtkWidget *widget , 
         gpointer   label  )
{
  ++contador;
  sprintf (&chlabel[len_chlabel], "%d", contador);
  gtk_label_set_text(label, chlabel);
  change_color_label (label);

  return FALSE;
}

gboolean 
cb_minus (GtkWidget *widget , 
          gpointer   label  )
{
  --contador;
  sprintf (&chlabel[len_chlabel], "%d", contador);
  gtk_label_set_text(label, chlabel);
  change_color_label (label);

  return FALSE;
}

int
main (int argc, char **argv)
{
  GtkWidget        *window, *vbox, *hbox1, *hbox2, *bplus, *bminus, *label ;
  GtkStyleContext  *context ;
  int               len ;
  char              ch_minus[8] ;

  srand (time(NULL));
  
  setlocale (LC_ALL, "");
  len = wctomb (ch_minus, 8210);
  ch_minus[len] = 0;

  len_chlabel = strlen (chlabel);
  sprintf (&chlabel[len_chlabel], "%d", contador);

  gtk_init (&argc, &argv);
  provider_create (cssData);

  window = gtk_window_new (winType);
  gtk_widget_set_name (GTK_WIDGET(window), "window");
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
  gtk_style_context_add_class (context, "LabelColor1");
  gtk_box_pack_start (GTK_BOX(hbox1), label, TRUE, FALSE, 0);

  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_end (GTK_BOX(vbox), hbox2, FALSE, TRUE, 20);

  bminus = gtk_button_new_with_label (ch_minus);
  gtk_style_context_add_class (gtk_widget_get_style_context (bminus), "btminus");
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
