#ifndef __GB_AUXIL_H__
#define __GB_AUXIL_H__ 1

#include <gtk/gtk.h>

#include "ShowGtkBox.h"

extern GtkWidget *
gb_label_new (ShowGtkBoxStruct  *gb   ,
              gchar             *text ,
              GtkWidget         *box  ,
              gboolean           flag );

#endif  /* __GB_AUXIL_H__ */
