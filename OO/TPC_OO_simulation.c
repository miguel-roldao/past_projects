#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>
#include <string.h>

gdouble dt          = 0.5  ;
gdouble dt_max      = 10. ;
GtkWidget *scale1, *scale2, *scale3, *scale4;
double A, B, C, D; //modos normais

gboolean
press_click (GtkWidget       *widget ,
	     GdkEventButton  *event  ,
             gpointer         data   )
{
  /* if (event->button == 1)
    dt = dt + 1.;
  else if (event->button == 3)
    dt = dt - 1.;
  else
    dt = 1.;

  if (dt > dt_max)
    dt = 1.;
  else if (dt <= 0)
  dt = dt_max;*/
  dt = 0.5;

  return TRUE;
}

gboolean 
cb_draw_event (GtkWidget  *darea , 
               cairo_t    *cr    , 
	       gpointer    data )
{
  int i;
  gchar          texto[128] ;
  static double t = 0.;
  double h, g, l, m, k, amp, x1ini = 130;
  double x2ini = 300;
  double  normal1, normal2, normal3, normal4;
  double  pos1x, pos1y = 150.;
  double  pos2x, pos2y = 250.;
  double  pos3x, pos3y = 150.;
  double  pos4x, pos4y = 250.;
  GtkAllocation  alloc1 ;

  gtk_widget_get_allocation (darea, &alloc1);

  cairo_move_to (cr, 20, 20);
  cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size (cr, 18);
  cairo_set_source_rgb (cr, 0., 0., 1.);
  sprintf (texto, "Duplo Pêndulo Duplo Acoplado");
  cairo_show_text (cr, texto);
  cairo_move_to (cr, 20, alloc1.height - 50);
  strcpy (texto, "Combinar modos normais ---->");
  cairo_show_text (cr, texto);
  cairo_stroke (cr);

  A = gtk_range_get_value (GTK_RANGE(scale1));
  B = gtk_range_get_value (GTK_RANGE(scale2));
  C = gtk_range_get_value (GTK_RANGE(scale3));
  D = gtk_range_get_value (GTK_RANGE(scale4));

  amp = 10;
  
  g = 10;
  l = 0.1;
  m = 2;
  k = 2;
   
  // Calculo das posicoes

  t = t + 0.003*dt;

  normal1 = cos((2-sqrt(2))*(g/l)*t);
  normal2 = cos((2*k/m+(2-sqrt(2))*g/l)*t);
  normal3 = cos((2+sqrt(2))*(g/l)*t);
  normal4 = cos((2*k/m +(2+sqrt(2))*g/l)*t);

  pos1x = x1ini + amp * (A * (sqrt(2)-1) * normal1 + B *(1-sqrt(2)) * normal2 + C * (-1-sqrt(2)) * normal3 + D * (1+sqrt(2)) * normal4);

  pos2x = x1ini + amp * (A * normal1 + B *(-normal2) + C * normal3 + D * (-normal4));

  pos3x = x2ini + amp * (A * (sqrt(2)-1) * normal1 + B * (sqrt(2)-1) * normal2 + C * (-1-sqrt(2)) * normal3 + D * (-1-sqrt(2)) * normal4);

  pos4x = x2ini + amp * (A * normal1 + B * normal2 + C * normal3 + D * normal4);

  // printf("%lf-%lf-%lf-%lf-", pos1x, pos2x, pos3x, pos4x);


  //L1

  cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
  cairo_set_line_width (cr, 2);
  cairo_move_to (cr, x1ini, 50); 
  cairo_line_to(cr, pos1x, pos1y);
  cairo_stroke(cr);

  //L2
  cairo_set_source_rgb (cr, 0., 0., 0.);
  cairo_set_line_width (cr, 2);
  cairo_move_to (cr, pos1x, pos1y);
  cairo_line_to (cr, pos2x, pos2y);
  cairo_stroke (cr);

  //L3
  cairo_set_source_rgb (cr, 0., 0., 0.);
  cairo_set_line_width (cr, 2);
  cairo_move_to (cr, x2ini, 50);
  cairo_line_to (cr, pos3x, pos3y);
  cairo_stroke (cr);

  //L4
  cairo_set_source_rgb (cr, 0., 0., 0.);
  cairo_set_line_width (cr, 2);
  cairo_move_to (cr, pos3x, pos3y);
  cairo_line_to (cr, pos4x, pos4y);
  cairo_stroke (cr);


  //m1
  cairo_move_to (cr, pos1x, pos1y);
  cairo_arc (cr, pos1x, pos1y, 15, 0, 2. * M_PI);
  cairo_fill (cr);
  cairo_stroke (cr);

  //m2
  cairo_move_to (cr, pos2x, pos2y);
  cairo_arc (cr, pos2x, pos2y, 15, 0, 2. * M_PI);
  cairo_fill (cr);
  cairo_stroke (cr);

  //m3
  cairo_move_to (cr, pos3x, pos3y);
  cairo_arc (cr, pos3x, pos3y, 15, 0, 2. * M_PI);
  cairo_fill (cr);
  cairo_stroke (cr);

  //m4
  cairo_move_to (cr, pos4x, pos4y);
  cairo_arc (cr, pos4x, pos4y, 15, 0, 2. * M_PI);
  cairo_fill (cr);
  cairo_stroke (cr);

  //molas
  
  h = 10;

 cairo_move_to(cr, pos1x, pos1y);
 
 for (i=1; i<10; i++)
    {
      cairo_line_to (cr, pos1x + i*(pos3x-pos1x)/10, pos1y + i*(pos3y-pos1y)/10 + h);
      h = - h;
    }
 
  cairo_line_to (cr, pos3x, pos3y);
  cairo_stroke(cr);

 cairo_move_to(cr, pos2x, pos2y);
 
 for (i=1; i<10; i++)
    {
      cairo_line_to (cr, pos2x + i*(pos4x-pos2x)/10, pos2y + i*(pos4y-pos2y)/10 + h);
      h = - h;
    }
 
  cairo_line_to (cr, pos4x, pos4y);
  cairo_stroke(cr);

  return FALSE;
}

gboolean 
time_handler (GtkWidget *widget)
{  
  if ((!GTK_IS_WIDGET(widget)) || (!gtk_widget_get_window (widget)))
    return FALSE;

  gtk_widget_queue_draw(widget);

  return TRUE;
}


int main (int argc, char **argv)
{
  GtkWidget  *window, *overlay, *swingbox, *setbox, *darea;

 // Inicialização da biblioteca GTK+

  

  gtk_init (&argc, &argv);
  
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(window), 700,500);
  gtk_window_set_title (GTK_WINDOW(window), "TPC_OO");
  gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_resizable (GTK_WINDOW(window), TRUE);
  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  overlay = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add (GTK_CONTAINER(window), overlay);

  swingbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start (GTK_BOX(overlay), swingbox, TRUE, TRUE, 0);

  setbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start (GTK_BOX(overlay), setbox, TRUE, TRUE, 2);
  
  scale1 = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL,-1,1,0.1);
  gtk_box_pack_start (GTK_BOX(setbox), scale1, TRUE, TRUE, 2);
  gtk_range_set_value (GTK_RANGE(scale1), 0);
 			   
  scale2 = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL,-1,1,0.1);
  gtk_box_pack_start (GTK_BOX(setbox), scale2, TRUE, TRUE, 2);
  gtk_range_set_value (GTK_RANGE(scale2), 0);
  
  scale3 = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL,-1,1,0.1);
  gtk_box_pack_start (GTK_BOX(setbox), scale3, TRUE, TRUE, 2);
  gtk_range_set_value (GTK_RANGE(scale3), 0);
  
  scale4 = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL,-1,1,0.1);
  gtk_box_pack_start (GTK_BOX(setbox), scale4, TRUE, TRUE, 2);
  gtk_range_set_value (GTK_RANGE(scale4), 0);

  
  darea = gtk_drawing_area_new ();
  gtk_widget_set_size_request (darea, 500, 500);
  gtk_container_add (GTK_CONTAINER (swingbox), darea);
  
 
  g_signal_connect (G_OBJECT(darea), "draw", G_CALLBACK(cb_draw_event), NULL);
  //  g_signal_connect (G_OBJECT(darea), "draw", G_CALLBACK(desenha_mola, NULL);  
  g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect (G_OBJECT(window), "button_press_event", G_CALLBACK(press_click), NULL); 

  g_timeout_add (10, (GSourceFunc) time_handler, darea);

  
  gtk_widget_show_all(window);
  gtk_main ();
   
return 0;

}
