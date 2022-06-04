#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "Gtk3_CssAux.h"

void create_style_from_data (gchar *cssData)
{
  GtkCssProvider *provider;
  GdkDisplay *display;
  GdkScreen *screen;

  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);

  // GTK_STYLE_PROVIDER_PRIORITY_USER (~/.gtk-3.0.css)
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  gtk_css_provider_load_from_data (GTK_CSS_PROVIDER (provider), cssData, -1, NULL);

  g_object_unref (provider);
}


void create_style_from_file (gchar *cssFile)
{
  gsize   bytes_written, bytes_read;
  GError *error = 0;
  gchar  *fileUTF8 ;

  GtkCssProvider *provider = gtk_css_provider_new ();
  GdkDisplay *display = gdk_display_get_default ();
  GdkScreen *screen = gdk_display_get_default_screen (display);

  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider),
					     GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  fileUTF8 = g_filename_to_utf8 (cssFile, strlen(cssFile), &bytes_read, &bytes_written, &error);
  
  gtk_css_provider_load_from_path (provider, fileUTF8, NULL);
  
  free (fileUTF8);
  
  g_object_unref (provider);
}
