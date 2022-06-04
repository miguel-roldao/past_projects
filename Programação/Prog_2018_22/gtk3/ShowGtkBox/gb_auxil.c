/*  gb_auxil.c  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>

#include "ShowGtkBox.h"
#include "gb_auxil.h"

GtkWidget *
gb_label_new (ShowGtkBoxStruct  *gb   ,
              gchar             *text ,
              GtkWidget         *box  ,
              gboolean           flag )
{
  GtkWidget *label ;

  label = gtk_label_new(text);

  if (flag)
    gtk_container_add(GTK_CONTAINER(box), label);

  return label;
}
