#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>
#include "Gtk3_CssAux.h"

/*  Programação, Instituto Superior Técnico

    *     *   * * *   * * * *  * * * *
    * * * *   *       *           *
    *  *  *   * **    * * *       *
    *     *   *       *           *
    *     *   * * *   *           *    

 Alexandre Barbosa e Miguel Roldão, 2018-2019  */

/***    TODO: 

  2. CSS

     a. Formatação do Texto, Botões e Scales

  3. GERAL

     a. H -> ajuda (abre o ficheiro .pdf)

     b. Ícone!

   
f. ALLOCS E CENAS (OU SERÁ UM FALSE7TRUE)?
                                                                         ***/
/* Macros */

#define QUAD(x) (x * x)

/* Estruturas */

typedef struct
{
  gboolean      start; 
  gboolean      pausa;  
  double        time;
  GtkWidget     *restart_bt;
  GtkWidget     *pause_play_bt;
} status;
  

typedef struct
{
  GtkWidget *garea;
  double    *x[2], *y[2];
  double    scale[2];
  double    rgb[2][3];
  gdouble   ZOOM_X, ZOOM_Y;
  int       n; // dimensão do vetor onde são guardados os valores
  char      id[2];  // identifica a escolha da combobox
  char      active_graph[2];// identifica os valores de que gráficos é que serão mostrados
  gboolean  show_value; // identifica se algum valor será mostrado
} graph;

typedef struct
{ 
  double          m[3];  // Massas (m1, m2, m3)
  double          l[3];  // Comprimentos (L1, L2, L3)
  double          phi;
  double          phi0;
  double          dphi;  // derivada de phi
  double          dphi0;
  double          theta;
  double          theta0;
  double          w;     // freq angular
  double          K;     // energia cinetica
  double          U;     // energia potencial
  double          t;
  double          dt;    // incremento de t (para efeitos de cálculo)
  double          time;  // permite alterar o fluxo de tempo
  double          g;
  double          color[3][3];
  char            active_radio;
  gboolean        move       ;    // Permite so haver movimento com o timer
  graph           *graph;
  status          *stat;
  GtkWidget       *darea     ;    // é necessário fazer parte da struct porque time_handler só pode receber um arg por causa de g_timeout-add
  GtkWidget       *window;
  gdouble          win_xlen, win_ylen;
} data ;

typedef struct
{
  GtkWidget  *scale;
  GtkWidget *label;
  gdouble ScaleInitValue; // Valor inicial
  char *ch_LabelValue;
  gdouble min;
  gdouble max;
  gdouble step;
  char id;       // Identifica a estrutura e daí o valor que vai alterar
  data *pdata; // Ponteiro para a estrutura cujo valor vai alterar
} Scale ;

/* Funções */

void def_dimensoes (data *pinfo)
{

#if GTK_CHECK_VERSION(3,22,0)
  GdkDisplay *display = gdk_display_get_default ();
  GdkMonitor *monitor = gdk_display_get_primary_monitor(display);
  GdkRectangle geom;  //estrutura que guarda a geometria do ecra

  gdk_monitor_get_geometry(monitor, &geom);

  pinfo->win_xlen = geom.width/(3.5);
  pinfo->win_ylen = geom.height/2;

#else

  GdkScreen *s1 ;

  s1 = gdk_screen_get_default ();

  pinfo->win_xlen=(gdk_screen_get_width (s1))/(3.7);
  pinfo->win_ylen=(gdk_screen_get_height (s1))/2;

#endif

}


void limpa_graficos (GtkWidget *btn, graph *g, char qual)
{
  int i;

  if (qual == 1)
    {
      for (i = 0; i < g->n; i++)
	{
	  g->x[0][i] = 0;
	  g->y[0][i] = 0;
	}
    }
  
  else if (qual == 2)
    {
      for (i = 0; i < g->n; i++)
	{
	  g->x[1][i] = 0;
	  g->y[1][i] = 0;
	}
    }

  else
    {
      for (i = 0; i < g->n; i++)
	{
	  g->x[0][i] = 0;
	  g->y[0][i] = 0;
	  g->x[1][i] = 0;
	  g->y[1][i] = 0;
	}
    }
}

void restart_fun (GtkWidget *btn, status *stat)
{
  stat->start = 1;
}

void pause_play_fun (GtkWidget *btn, data *d)
{
  
  if (d->stat->pausa == 0)
    {
      d->stat->pausa = 1;
      gtk_button_set_label (GTK_BUTTON(d->stat->pause_play_bt), "\u25B6");
    }

  else
    {
      d->stat->pausa = 0;
      gtk_button_set_label (GTK_BUTTON(d->stat->pause_play_bt), "| |");
    }
}


gboolean error_handler (GtkWidget *win, data *pdata)
{
  GtkWidget *dialog, *label;
  gchar     *message = "\n\n  O valor de \u03C6 atingido é demasiado grande para o modelo usado ser válido!";
  gint       resultado ;

  pause_play_fun (pdata->stat->pause_play_bt, pdata);
  
  dialog = gtk_dialog_new_with_buttons ("** ERRO **", GTK_WINDOW(win), 
					GTK_DIALOG_DESTROY_WITH_PARENT,
					"_Reiniciar", GTK_RESPONSE_OK,
					NULL);
  
  gtk_window_set_default_size (GTK_WINDOW(dialog), 50, 150);
  gtk_window_set_modal (GTK_WINDOW(dialog), TRUE);
  gtk_window_set_transient_for (GTK_WINDOW(dialog), GTK_WINDOW(win));
  
  label = gtk_label_new (message);
  gtk_box_pack_start (GTK_BOX(gtk_bin_get_child (GTK_BIN(dialog))), label, TRUE, FALSE, 0);
  gtk_widget_show_all (dialog);

  resultado = gtk_dialog_run (GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

  if (resultado == GTK_RESPONSE_OK)
      restart_fun(pdata->stat->restart_bt, pdata->stat);

  return FALSE;
}

void Euler_Cromer (data *pdata)
{
    double M, I[2], N;
    double A, B, C, D;
    double dtheta, d2theta, d2phi;
    gboolean t = 0;
    int i;

    M = pdata->m[0] + pdata->m[1] + pdata->m[2];
    I[0] = M * QUAD(pdata->l[0]);
    I[1] = pdata->m[1] * QUAD(pdata->l[1]) + pdata->m[2] * QUAD(pdata->l[2]);
    N = pdata->m[2] * pdata->l[2] - pdata->m[1]* pdata->l[1];
      

    for (i = 0; i < pdata->time; i++)
      
      {
	
	pdata->theta = pdata->theta0 * cos(pdata->w * pdata->t);
	dtheta = -pdata->theta0 * pdata->w * sin(pdata->w*pdata->t);
	d2theta = -pdata->theta * QUAD(pdata->w);
      
	A = I[0] + I[1] - 2 * pdata->l[0] * N * cos(pdata->theta);
	B = d2theta * (I[1] - pdata->l[0] * N * cos(pdata->theta));
	C = pdata->l[0] * N * sin(pdata->theta) * dtheta;
	D = M * pdata->g * pdata->l[0];

	// Euler-Cromer
      
	d2phi = (B + C * (2 * pdata->dphi + dtheta) + D * sin(pdata->phi) - N * pdata->g * sin(pdata->phi + pdata->theta)) / A;
	pdata->dphi = pdata->dphi - (pdata->dt * d2phi);
	pdata->phi = pdata->phi + pdata->dphi * pdata->dt;

	if (fabs (pdata->phi) > 1.8 && t == 0) // para amplitudes de phi > 1.8 rad, já não é um oscilador harmónico forçado
	  {
	    pdata->move = 0;
	    error_handler(pdata->window, pdata);
	    t = 1;
	  }

	pdata->K = 0.5 * I[0] * pdata->dphi * pdata->dphi + 0.5 * I[1] * (pdata->dphi + dtheta) * (pdata->dphi + dtheta) - pdata->l[0] * N * cos(pdata->theta) * (pdata->dphi + dtheta) * pdata->dphi;
      
	pdata->U = -M * pdata->g * pdata->l[0] * cos(pdata->phi) + N * pdata->g * cos(pdata->phi + pdata->theta);
      
	pdata->t += pdata->dt;

      }

} 
  

gboolean on_draw_event (GtkWidget *drawing_area, cairo_t *cr, data *pdata)
{
  
  GdkRectangle da;
  GdkWindow *window = gtk_widget_get_window(drawing_area);
  double x, y, x2, y2, x3, y3;
  char text1[32], text2[32], text3[32], text4[32], dummy;
  GdkPixbuf *pixbuf;

  /* Legenda */

  if (pdata->graph->show_value)
    {
      cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
      cairo_set_source_rgb (cr, .1, .1, .1);
      cairo_set_font_size(cr, 14);

      switch (pdata->graph->active_graph[0])
	{

       case 1:
	  sprintf(text1, "\u03C6 :  %4.2lf º", fmod(pdata->phi * 57.3, 360.0));
	  break;

	case 2:
	  sprintf(text1, "\u03C6\u0307 :  %4.2lf rad/s", pdata->dphi);
	  break;
	  
	case 3:
	  sprintf(text1, "\u03B8 :  %4.2lf º", pdata->theta * 57.3);
	  break;

	case 4:
	  sprintf(text1, "\u03C6 :  %4.2lf º", fmod(pdata->phi * 57.3, 360.0)); 
	  sprintf(text2, "\u03B8 :  %4.2lf º", pdata->theta * 57.3);
	  dummy = 1;
	  break;

	case 5:
	  sprintf(text1, "K:  %4.1lf J", pdata->K);
	  break;

        case 6:
	  sprintf(text1, "U:  %4.1lf J", pdata->U + 540);
	  break;

	case 7:
	  sprintf(text1, "E:  %4.1lf J", pdata->K + pdata->U + 540);
	  break;

	default:
	  sprintf(text1, "\u03C6 :  %4.2lf º", fmod(pdata->phi * 57.3, 360.0));
	  break;
	  
	}

      // Desenha o texto na 'drawing area' (gráfico 1)
      
      if (pdata->graph->active_graph[0] != 10)
	{

	  sprintf(text4, " t :   %3.2lf s", pdata->t);
	  cairo_move_to(cr, 30, 20);
	  cairo_show_text(cr, text1);

	  if (dummy == 1)
	    {
	      cairo_move_to(cr, 30, 38);
	      cairo_show_text(cr, text2);
	    }

	  else
	    {
	      cairo_move_to(cr, 30, 38);
	      cairo_show_text(cr, text4);
	    }
	}

      switch (pdata->graph->active_graph[1])
	{

       case 1:
	  sprintf(text3, "\u03C6 :  %4.2lf º", fmod(pdata->phi * 57.3, 360.0));
	  break;

	case 2:
	  sprintf(text3, "\u03C6\u0307 :  %4.2lf rad/s", pdata->dphi);
	  break;
	  
	case 3:
	  sprintf(text3, "\u03B8 :  %4.2lf º", pdata->theta * 57.3);
	  break;

	case 4:
	  sprintf(text3, "\u03C6 :  %4.2lf º", fmod(pdata->phi * 57.3, 360.0)); 
	  sprintf(text2, "\u03B8 :  %4.2lf º", pdata->theta * 57.3);
	  dummy = 2;
	  break;

	case 5:
	  sprintf(text3, "K:  %4.1lf J", pdata->K);
	  break;

        case 6:
	  sprintf(text3, "U : %4.1lf J", pdata->U + 540);
	  break;

	case 7:
	  sprintf(text3, "E:  %4.1lf J", pdata->K + pdata->U + 540);
	  break;

	default:
	  sprintf(text3, "\u03C6 :  %4.2lf º", fmod(pdata->phi * 57.3, 360.0));
	  break;
	  
	}

      // Desenha o texto na 'drawing area' (gráfico 2) - mas apenas se for diferente do gráfico 1

      if (pdata->graph->active_graph[1] != 0 && pdata->graph->active_graph[1] != pdata->graph->active_graph[0])
	{

	  if (dummy != 2) 
	    {
	      cairo_move_to(cr, 30, 56);
	      cairo_show_text(cr, text3);
	    }

	  if (dummy == 1)
	    {
	      cairo_move_to(cr, 30, 72);
	      cairo_show_text(cr, text4);
	    }

	  else if (dummy == 2)
	    {
	      cairo_move_to(cr, 30, 56);
	      cairo_show_text(cr, text2);

	      cairo_move_to(cr, 30, 72);
	      cairo_show_text(cr, text3);
	    }
	}
      
    }
  
  /* Escala:  Massas       -  1 kg <---> 1 px² 
              Comprimentos -  1 m  <---> 100 px  */

   gdk_window_get_geometry (window,
			   &da.x,
			   &da.y,
			   &da.width,
			   &da.height);

     /* L1 */

  x = pdata->l[0] * 100 * sin(pdata->phi) + da.width/2; 
  y = pdata->l[0] * 100 * cos(pdata->phi) + 50;
  
 cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
  cairo_set_line_width (cr, 2);
  cairo_arc (cr, da.width/2, 50, 3.5, 0., 2.*M_PI);
  cairo_fill (cr);
  cairo_move_to (cr, da.width/2, 50); 
  cairo_line_to(cr, x, y);
  cairo_stroke(cr);

      /* L2 */

  x2 = x + pdata->l[1] * 100 * sin(pdata->phi+pdata->theta);
  y2 = y + pdata->l[1] * 100 * cos(pdata->phi+pdata->theta);

  cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
  cairo_set_line_width (cr, 2);
  cairo_move_to (cr, x, y); 
  cairo_line_to(cr, x2, y2);
  cairo_stroke(cr);

    /* L3 */

  x3 = x - pdata->l[2] * 100 * sin(pdata->phi+pdata->theta);
  y3 = y - pdata->l[2] * 100 * cos(pdata->phi+pdata->theta);

  cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
  cairo_set_line_width (cr, 2);
  cairo_move_to (cr, x, y);
  cairo_line_to(cr, x3, y3);
  cairo_stroke(cr);
   
   /* m1 */

  cairo_set_source_rgb (cr, pdata->color[0][0], pdata->color[0][1], pdata->color[0][2]);
  cairo_arc (cr, x, y, pdata->m[0], 0., 2. * M_PI);
  cairo_fill (cr);
  cairo_stroke (cr);

    /* m2 */

  cairo_set_source_rgb (cr, pdata->color[1][0], pdata->color[1][1], pdata->color[1][2]);

  cairo_arc (cr, x2, y2, pdata->m[1], 0., 2. * M_PI);
  cairo_fill (cr);
  cairo_stroke (cr);

     /* m3 */

  cairo_set_source_rgb (cr, pdata->color[2][0], pdata->color[2][1], pdata->color[2][2]);

  cairo_arc (cr, x3, y3, pdata->m[2], 0., 2. * M_PI);
  cairo_fill (cr);
  cairo_stroke (cr);

  /* Movimento */

  if (pdata->move == 1) 
    {

      if (pdata->stat->start == 1)
	{
	  pdata->t = 0;
	  pdata->phi = pdata->phi0; 
	  pdata->dphi = pdata->dphi0;
	  pdata->theta = pdata->theta0;
	  pdata->stat->start = 0;
	}
      

      if (pdata->stat->pausa == 1)
	{
	  if(pdata->dt != 0)
	    {
	      pdata->stat->time = pdata->dt;
	      pdata->dt = 0;
	      pdata->stat->pausa = 0;
	    }
	  
	  else
	    {
	      pdata->dt = pdata->stat->time;
	      pdata->stat->pausa = 0;
	    }
	
	}

      Euler_Cromer(pdata);
   
    }

  pdata->move=0;
  
  if (pdata->stat->pausa == 1)
    {
      pixbuf = gdk_pixbuf_new_from_file ("swing.png", NULL);
      gdk_cairo_set_source_pixbuf(cr, pixbuf, 10, 80);
      cairo_paint(cr);
      cairo_fill (cr);
      cairo_stroke (cr);
    }
  
  return FALSE;
  
}

gboolean time_handler (data *data)
{
  if (data->stat->pausa == 0)
    {
      data->move = 1;
      gtk_widget_queue_draw (data->graph->garea);
    }

  gtk_widget_queue_draw (data->darea);

  if (data->stat->start == 1)
    limpa_graficos (data->stat->restart_bt, data->graph, 0);
      
  return TRUE;
  
}

GtkWidget *cria_scale (Scale *s)
{
  GtkWidget *w ;

  w = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, s->min, s->max, s->step);
  gtk_scale_set_digits (GTK_SCALE(w), 2); // n_show_digits = 2;
  gtk_scale_set_value_pos (GTK_SCALE(w), GTK_POS_TOP); // GTK_POS_LEFT, GTK_POS_RIGHT, GTK_POS_TOP, GTK_POS_BOTTOM;
  gtk_scale_set_draw_value (GTK_SCALE(w), FALSE);
  gtk_range_set_value (GTK_RANGE(w), s->ScaleInitValue); // (n_show_value ? TRUE; FALSE);
  
  return w;
}


gboolean cb_change_scale (GtkWidget *w, Scale *s)  
{
  char        str1[32] ; 

  switch (s->id)
    {
      
    case 1:
      s->pdata->m[0] = gtk_range_get_value (GTK_RANGE(s->scale));
      sprintf(str1, s->ch_LabelValue, s->pdata->m[0]);
      break;

    case 2:
      s->pdata->m[1] = gtk_range_get_value (GTK_RANGE(s->scale));
      sprintf(str1, s->ch_LabelValue, s->pdata->m[1]);
      break;

    case 3:
      s->pdata->m[2] = gtk_range_get_value (GTK_RANGE(s->scale));
      sprintf(str1, s->ch_LabelValue, s->pdata->m[2]);
      break;

    case 4:
      s->pdata->l[0] = gtk_range_get_value (GTK_RANGE(s->scale));
      sprintf(str1, s->ch_LabelValue, s->pdata->l[0]);
      break;

    case 5:
      s->pdata->l[1] = gtk_range_get_value (GTK_RANGE(s->scale));
      sprintf(str1, s->ch_LabelValue, s->pdata->l[1]);
      break;

    case 6:
      s->pdata->l[2] = gtk_range_get_value (GTK_RANGE(s->scale));
      sprintf(str1, s->ch_LabelValue, s->pdata->l[2]);
      break;

    case 7:
      restart_fun(s->pdata->stat->restart_bt, s->pdata->stat); 
      s->pdata->theta0 = gtk_range_get_value (GTK_RANGE(s->scale)) / 57.3; // converte de º para rad
      sprintf(str1, s->ch_LabelValue, s->pdata->theta0 * 57.3); // converte de rad para º
      break;     

    case 8:
      s->pdata->w = gtk_range_get_value (GTK_RANGE(s->scale));
      sprintf(str1, s->ch_LabelValue, s->pdata->w);
      break;

    case 9:
      restart_fun(s->pdata->stat->restart_bt, s->pdata->stat); 
      s->pdata->phi0 = gtk_range_get_value (GTK_RANGE(s->scale));
      sprintf(str1, s->ch_LabelValue, s->pdata->phi0 * 57.3);
      break;

    case 10:
      restart_fun(s->pdata->stat->restart_bt, s->pdata->stat); 
      s->pdata->dphi0 = gtk_range_get_value (GTK_RANGE(s->scale));
      sprintf(str1, s->ch_LabelValue, s->pdata->dphi0);
      break;

    case 11:
      s->pdata->g = gtk_range_get_value (GTK_RANGE(s->scale));
      sprintf(str1, s->ch_LabelValue, s->pdata->g);
      break;

    case 12:
      
      if (s->pdata->dt ==0)
	{
	  s->pdata->stat->time =  0.1 * gtk_range_get_value (GTK_RANGE(s->scale));
	  sprintf(str1, s->ch_LabelValue, 10 * s->pdata->stat->time);
	}
      
      else
	{
	  s->pdata->time = 1e3 * gtk_range_get_value (GTK_RANGE(s->scale));
	  sprintf(str1, s->ch_LabelValue, 1e-3*s->pdata->time);
	}
      break;

    case 13:
      s->pdata->graph->ZOOM_Y = gtk_range_get_value (GTK_RANGE(s->scale)) * 60;
      sprintf(str1, s->ch_LabelValue, s->pdata->graph->ZOOM_Y / 60);
      break;

    case 14:
      s->pdata->graph->ZOOM_X = gtk_range_get_value (GTK_RANGE(s->scale)) + 0.5;
      sprintf(str1, s->ch_LabelValue, s->pdata->graph->ZOOM_X - 0.5);
      break;
      
    default:
      printf("** ERRO: Nenhum valor de 'id' das 'scales' alteradas foi lido. \n\n **");
      break;
    }

  gtk_label_set_text (GTK_LABEL(s->label), str1);

  return FALSE;
}

/* Desenha os gráficos */

gboolean draw_graph (GtkWidget *garea, cairo_t *cr, data *gdata)
{
  GdkRectangle da;             /* dimensões da drawing area */
  gdouble dx, dy = 2.0;        /* pixéis entre cada ponto  */
  static int i;
  double fator;
  int j, k;
  gdouble  clip_x1 = 0.0, clip_y1 = 0.0, clip_x2 = 0.0, clip_y2 = 0.0;
  GdkWindow *window = gtk_widget_get_window(garea);

  dx = gdata->dt * 10000; // mudar

 
  
  // Determina as dimensões da Drawing Area 
  gdk_window_get_geometry (window,
			   &da.x,
			   &da.y,
			   &da.width,
			   &da.height);
 
  /* Define a cor do fundo */
  /* cairo_set_source_rgb (cr, 2, 2, 2);
     cairo_paint (cr); */
  
  fator = da.width/ 569.;  // fator de escala que atua no resize da janela

  // gdata->graph->ZOOM_X = 1;
  /* Zoom (matriz de transformação) */
  cairo_translate (cr, 0, da.height / 2);
  cairo_scale (cr, 100, -1 * gdata->graph->ZOOM_Y);
  
  /* Determina os pontos na 'clipping zone' */
  cairo_device_to_user_distance (cr, &dx, &dy);
  cairo_clip_extents (cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2);
  // cairo_set_line_width (cr, dx);

  /*  Desenha os eixos xx e yy   */
  cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
  cairo_set_line_width (cr, 0.6/gdata->graph->ZOOM_Y);
  cairo_move_to (cr, clip_x1, 0.0);
  cairo_line_to (cr, clip_x2, 0.0);
  /* cairo_move_to (cr, 0.0, clip_y1);
     cairo_line_to (cr, 0.0, clip_y2);*/
  cairo_stroke (cr);

  //  printf("%lf\n", clip_x2);
  /* Preenche os vetores */

  clip_x2 = 5.69;
  
  for(j = 0; j < 2; j++)
    {

      if(gdata->stat->pausa == 0)
	{
	  switch (gdata->graph->id[j])
	    {
	    case 0:
	      gdata->graph->x[j][gdata->graph->n-1] = clip_x2;
	      gdata->graph->y[j][gdata->graph->n-1] = gdata->phi * gdata->graph->scale[j];
	      break;
	      
	    case 1:
	      gdata->graph->x[j][gdata->graph->n-1] = clip_x2;
	      gdata->graph->y[j][gdata->graph->n-1] = gdata->dphi * gdata->graph->scale[j];
	      break;
	      
	    case 2:
	      gdata->graph->x[j][gdata->graph->n-1] = clip_x2;
	      gdata->graph->y[j][gdata->graph->n-1] = gdata->theta * gdata->graph->scale[j];
	      break;
	      
	    case 3:
	      gdata->graph->x[j][gdata->graph->n-1] = gdata->theta + 2.7; 
	      gdata->graph->y[j][gdata->graph->n-1] = gdata->phi * gdata->graph->scale[j];
	      break;
	      
	    case 4:
	      gdata->graph->x[j][gdata->graph->n-1] = clip_x2;
	      gdata->graph->y[j][gdata->graph->n-1] = gdata->K * gdata->graph->scale[j];
	      break;
	      
	    case 5:
	      gdata->graph->x[j][gdata->graph->n-1] = clip_x2;
	      gdata->graph->y[j][gdata->graph->n-1] = (gdata->U + 540) * gdata->graph->scale[j]; // somar uma constante para tornar visível
	      break;
	      
	    case 6:
	      gdata->graph->x[j][gdata->graph->n-1] = clip_x2;
	      gdata->graph->y[j][gdata->graph->n-1] = (gdata->U + gdata->K + 540) * gdata->graph->scale[j]; // somar uma constante para tornar visível
	      break;
	      
	      // case 7 (---Selecionar---)
	      
	    case 7:
	      cairo_stroke(cr);
	      
	    default:
	      gdata->graph->x[j][gdata->graph->n-1] = clip_x2;
	      gdata->graph->y[j][gdata->graph->n-1] = gdata->phi * gdata->graph->scale[j];
	      break;
	    }
	  
	  /* Escala xx não temporal phi(theta) */
	  
	  if(gdata->graph->id[j] == 3)
	    {
	      for(k=0; k < gdata->graph->n-1; k++)
		{
		  gdata->graph->x[j][k] = gdata->graph->x[j][k+1];
		  gdata->graph->y[j][k] = gdata->graph->y[j][k+1];
		}
	      
	      cairo_move_to (cr, gdata->graph->x[j][gdata->graph->n-1], gdata->graph->y[j][gdata->graph->n-1]);
	    }
	  
	  else if(gdata->graph->id[j] == 7)
	    cairo_stroke (cr);
	  
	  else
	    {
	      for (k=0; k < gdata->graph->n-1; k++)
		{
		  gdata->graph->x[j][k] = gdata->graph->x[j][k+1] - dx * gdata->time/1000;
		  gdata->graph->y[j][k] = gdata->graph->y[j][k+1];
		}
	    }
	}
      
      /* Desenhar gráfico */

      
      //   printf("%lf\n", gdata->graph->ZOOM_X);

      cairo_set_line_width (cr, 0.01);
      
      for (k = gdata->graph->n-1; k >= 0; k--)
	{
	  
	  if (gdata->graph->x[j][k] <= 0)
	    k--;

	  else if (k == gdata->graph->n-1)
	    cairo_move_to (cr, gdata->graph->x[j][k] * fator, gdata->graph->y[j][k]);

	  else if (gdata->graph->id[j] != 3)
	    cairo_line_to (cr, gdata->graph->x[j][k] * fator - (gdata->graph->ZOOM_X - 1)*(clip_x2 - gdata->graph->x[j][k]), gdata->graph->y[j][k]);

	  else
	    cairo_line_to (cr, gdata->graph->x[j][k] * fator, gdata->graph->y[j][k]);

	}


      switch(j)
	{
	case 0:
	  cairo_set_source_rgba (cr, gdata->graph->rgb[0][0], gdata->graph->rgb[0][1], gdata->graph->rgb[0][2], 1.0);
	  cairo_stroke (cr);
	  break;
	  
	case 1:
	  cairo_set_source_rgba (cr, gdata->graph->rgb[1][0], gdata->graph->rgb[1][1], gdata->graph->rgb[1][2], 1.0);
	  cairo_stroke (cr);
	  break;
	  
	default:
	  cairo_stroke (cr);
	}
    }
  
  i++;                 // funciona como um 'for' gigante
   
  return FALSE;
}

gboolean 
cb_combobox_function (GtkWidget *w, graph *g)
{
  
  g->id[0] = gtk_combo_box_get_active (GTK_COMBO_BOX (w));
  limpa_graficos(w, g, 1);
    
   switch (g->id[0])
    {
      // phi(t)
      
       case 0:
	 g->scale[0] = 2;
	 g->active_graph[0] = 1;
	 break;

       // dphi(t)
	 
       case 1:
	 g->scale[0] = 2;
	 g->active_graph[0] = 2;
	 break;

	// theta(t)
	
       case 2:
	 g->scale[0] = 2;
	 g->active_graph[0] = 3;
	 break;

	// phi(theta)

       case 3:
	 g->scale[0] = 3.5;
	 g->active_graph[0] = 4;
	 break;

	// energia cinética

       case 4:
	 g->scale[0] = 0.05;
	 g->active_graph[0] = 5;
	 break;

	// energia potencial

       case 5:
	 g->scale[0] = 0.05;
	 g->active_graph[0] = 6;
	 break;

	// energia

       case 6:
	 g->scale[0] = 0.05;
	 g->active_graph[0] = 7;
	 break;

       case 7:
	 g->active_graph[0] = 10;
	 break;
	
      default:
	g->scale[0] = 1;
	break;
    }

   return FALSE;
}

gboolean 
cb_combobox2_function (GtkWidget *w, graph *g)
{
  
  g->id[1] = gtk_combo_box_get_active (GTK_COMBO_BOX (w));

  limpa_graficos(w, g, 2);
    
  switch (g->id[1])
    {
      // phi(t)
      
    case 0:
      g->scale[1] = 2;
      g->active_graph[1] = 1;
      break;
	
      // dphi(t)

    case 1:
      g->scale[1] = 2;
      g->active_graph[1] = 2;
      break;
	
      // theta(t)
	
    case 2:
      g->scale[1] = 2;
      g->active_graph[1] = 3;
      break;
	
      // phi(theta)

    case 3:
      g->scale[1] = 3.5;
      g->active_graph[1] = 4;
      break;
	
      // energia cinética

    case 4:
      g->scale[1] = 0.1;
      g->active_graph[1] = 5;
      break;
	
      // energia potencial

    case 5:
      g->scale[1] = 0.05;
      g->active_graph[1] = 6;
      break;
	
      // energia

    case 6:
      g->scale[1] = 0.05;
      g->active_graph[1] = 7;
      break;

    case 7:
      g->active_graph[0] = 0;
      break;
	
    default:
      g->scale[1] = 1;
      break;
    }
  
  return FALSE;
}

gboolean 
cb_combobox3_function (GtkWidget *w, Scale *s)
{
  char        str1[32] ;
  
  switch (gtk_combo_box_get_active (GTK_COMBO_BOX (w)))
    {

     case 0: // Criança 
       
       if (s->id == 1)
	 {
	   gtk_range_set_value (GTK_RANGE(s->scale), 12.);
           sprintf(str1, s->ch_LabelValue, 12.);
	 }
       
       if (s->id == 2)
	 {
	   gtk_range_set_value (GTK_RANGE(s->scale), 6.);
           sprintf(str1, s->ch_LabelValue, 6.);
	 }

       if (s->id == 3)
	 {
	   gtk_range_set_value (GTK_RANGE(s->scale), 12.);
           sprintf(str1, s->ch_LabelValue, 12.);
	 }

	if (s->id == 4)
	 {
	   gtk_range_set_value (GTK_RANGE(s->scale), 2.);
           sprintf(str1, s->ch_LabelValue, 2.);
	 }

	if (s->id == 5)
	 {
	   gtk_range_set_value (GTK_RANGE(s->scale), .6);
           sprintf(str1, s->ch_LabelValue, .6);
	 }

	if (s->id == 6)
	 {
	   gtk_range_set_value (GTK_RANGE(s->scale), .6);
           sprintf(str1, s->ch_LabelValue, .6);
	 }

       break;

    case 1: // Adulto
       
       if (s->id == 1)
	 {
	   gtk_range_set_value (GTK_RANGE(s->scale), 30.);
           sprintf(str1, s->ch_LabelValue, 30.);
	 }
       
       if (s->id == 2)
	 {
	   gtk_range_set_value (GTK_RANGE(s->scale), 15.);
           sprintf(str1, s->ch_LabelValue, 15.);
	 }

       if (s->id == 3)
	 {
	   gtk_range_set_value (GTK_RANGE(s->scale), 30.);
           sprintf(str1, s->ch_LabelValue, 30.);
	 }

	if (s->id == 4)
	 {
	   gtk_range_set_value (GTK_RANGE(s->scale), 2.5);
           sprintf(str1, s->ch_LabelValue, 2.5);
	 }

	if (s->id == 5)
	 {
	   gtk_range_set_value (GTK_RANGE(s->scale), .8);
           sprintf(str1, s->ch_LabelValue, .6);
	 }

	if (s->id == 6)
	 {
	   gtk_range_set_value (GTK_RANGE(s->scale), .8);
           sprintf(str1, s->ch_LabelValue, .6);
	 }

       break;
      
    }
  
  
  return FALSE;
}

gboolean 
cb_combobox4_function (GtkWidget *w, Scale *s)
{
  char        str1[32] ;
  
  switch (gtk_combo_box_get_active (GTK_COMBO_BOX (w)))
    {

    case 0: // Mercúrio
      gtk_range_set_value (GTK_RANGE(s->scale), 3.7);
      sprintf(str1, s->ch_LabelValue, 3.7);
      break;

    case 1: // Vénus
      gtk_range_set_value (GTK_RANGE(s->scale), 8.8);
      sprintf(str1, s->ch_LabelValue, 8.8);
      break;

    case 2: // Terra
      gtk_range_set_value (GTK_RANGE(s->scale), 9.8);
      sprintf(str1, s->ch_LabelValue, 9.8);
      break;

    case 3: // Lua
      gtk_range_set_value (GTK_RANGE(s->scale), 1.6);
      sprintf(str1, s->ch_LabelValue, 1.6);
      break;

    case 4: // Marte
      gtk_range_set_value (GTK_RANGE(s->scale), 3.7);
      sprintf(str1, s->ch_LabelValue, 3.7);
      break;

    case 5: // Júpiter
      gtk_range_set_value (GTK_RANGE(s->scale), 24.8);
      sprintf(str1, s->ch_LabelValue, 24.8);
      break;

     case 6: // Urano
      gtk_range_set_value (GTK_RANGE(s->scale), 8.7);
      sprintf(str1, s->ch_LabelValue, 8.7);
      break;

     case 7: // Neptuno
      gtk_range_set_value (GTK_RANGE(s->scale), 11.2);
      sprintf(str1, s->ch_LabelValue, 11.2);
      break;
	 
    default:
      gtk_range_set_value (GTK_RANGE(s->scale), 9.8);
      sprintf(str1, s->ch_LabelValue, 9.8);
      break;
    }

  return FALSE;
}

gboolean Check (GtkWidget *w, graph *g)
{
  if (g->show_value == 1)
    g->show_value = 0;

  else
    g->show_value = 1;

  return FALSE;
}

gboolean Radio_Ga_Ga (GtkWidget *w, data *pdata)
{
  if (strcmp(gtk_widget_get_name (w), "radio_1") == 0)
    pdata->active_radio = 1;

  else if (strcmp(gtk_widget_get_name (w), "radio_2") == 0)
    pdata->active_radio = 2;

  else if (strcmp(gtk_widget_get_name (w), "radio_3") == 0)
    pdata->active_radio = 3;
    
  return FALSE;
}

gboolean
color_chooser (GtkWidget *w, data *pdata)
{
  gchar       *c1 ;
  // gchar      *str1 = "#label1 {color: #%2.2X%2.2X%2.2X; font-family: Tahoma; font-weight: bold; font-size: 18px;}";
  int         r1, g1, b1, t1, res    ;
  GdkRGBA     color1 ;
  GtkWidget  *dialog ;

  dialog = gtk_color_chooser_dialog_new ("Escolha uma Cor", GTK_WINDOW(pdata->window));
  res = gtk_dialog_run (GTK_DIALOG(dialog));

  if (res == GTK_RESPONSE_OK)
    {
     
      gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(dialog), &color1);

      c1 = gdk_rgba_to_string (&color1);
      t1 = sscanf (c1, "rgb(%d,%d,%d)", &r1, &g1, &b1);
      
      if (t1 != 3)
	r1 = g1 = b1 = 0;
      
      if (strcmp(gtk_widget_get_name (w), "Color_1") == 0)
	{
	  pdata->graph->rgb[0][0] = (double) r1 / (double) 255;
	  pdata->graph->rgb[0][1] = (double) g1 / (double) 255;
	  pdata->graph->rgb[0][2] = (double) b1 / (double) 255;
	}

      else if (strcmp(gtk_widget_get_name (w), "Color_2") == 0)
	{
	  pdata->graph->rgb[1][0] = (double) r1 / (double) 255;
	  pdata->graph->rgb[1][1] = (double) g1 / (double) 255;
	  pdata->graph->rgb[1][2] = (double) b1 / (double) 255;
	}

      else if (strcmp(gtk_widget_get_name (w), "Color_3") == 0)
	{
	  if (pdata->active_radio == 1)
	    {
	      pdata->color[0][0] = (double) r1 / (double) 255;
	      pdata->color[0][1] = (double) g1 / (double) 255;
	      pdata->color[0][2] = (double) b1 / (double) 255;
	    }

	  else if (pdata->active_radio == 2)
	    {
	      pdata->color[1][0] = (double) r1 / (double) 255;
	      pdata->color[1][1] = (double) g1 / (double) 255;
	      pdata->color[1][2] = (double) b1 / (double) 255;
	    }

	  else if (pdata->active_radio == 3)
	    {
	      pdata->color[2][0] = (double) r1 / (double) 255;
	      pdata->color[2][1] = (double) g1 / (double) 255;
	      pdata->color[2][2] = (double) b1 / (double) 255;
	    }
	}

      free (c1);
    }
  

  gtk_widget_destroy (dialog);

  return FALSE;
}

int main (int argc, char **argv)
{
  GtkWidget *overlay, *swingbox, *settingsbox, *setbox, *initsetbox, *graphsetbox, *sbox[24], *frame[3], *restart, *combo[4], *label[2], *radio[3], *clean_bt, *check_button, *color_button[4]; 
  data *pdata;
  Scale *m[3], *l[3], *theta, *omega, *phi, *dphi, *g, *t, *yy_scale, *xx_scale;
  char str[14][32];
  char pause_play_lb[10] = "\u25B6";
  char limpar_lb[18] = "Apagar Gr\u00E1ficos";
  char cb_text[8][64] = {"                   \u03C6(t)       ", "                   \u03C6\u0307(t)       ", "                   \u03B8(t)       ", "                   \u03C6(\u03B8)       ", "                   K(t)       ", "                   U(t)       ", "                   E(t)       ",  "            Selecionar        "}; // não há nenhuma forma razóavel e rápida de centrar o texto numa 'combo box'
  char default_set[2][18] = {"Crian\u00E7a", "Adulto"};
  char planets[9][18] = {"Merc\u00FArio", "V\u00E9nus", "Terra", "Lua", "Marte", "J\u00FApiter", "Saturno", "\u00DArano", "Neptuno"};
  int i;

  // Alocação de memória para as estruturas
  
  pdata = (data *) calloc (1, sizeof (data));

  for (i = 0; i < 3; i++)
    {
      m[i] = (Scale *) calloc (1, sizeof (Scale));
      l[i] = (Scale *) calloc (1, sizeof (Scale));
    }

  theta    = (Scale *) calloc (1, sizeof (Scale));
  omega    = (Scale *) calloc (1, sizeof (Scale));
  phi      = (Scale *) calloc (1, sizeof (Scale));
  dphi     = (Scale *) calloc (1, sizeof (Scale));
  g        = (Scale *) calloc (1, sizeof (Scale));
  t        = (Scale *) calloc (1, sizeof (Scale));
  yy_scale = (Scale *) calloc (1, sizeof (Scale));
  xx_scale = (Scale *) calloc (1, sizeof (Scale));  
  
  pdata->graph  = (graph *)  calloc (1, sizeof (graph));
  pdata->stat   = (status *) calloc (1, sizeof (status));

  // Alocação de memória para os gráficos

  pdata->graph->n = 2000;

  // Inicialização da biblioteca GTK+

  gtk_init (&argc, &argv);

  // Determina as dimensões da janela
  def_dimensoes (pdata);
  
  pdata->win_xlen = 900;
  pdata->win_ylen = 700;
  
  pdata->graph->x[0] = (double *) malloc (pdata->graph->n * sizeof(double));
  pdata->graph->x[1] = (double *) malloc (pdata->graph->n * sizeof(double));  
  pdata->graph->y[0] = (double *) malloc (pdata->graph->n * sizeof(double));
  pdata->graph->y[1] = (double *) malloc (pdata->graph->n * sizeof(double));

  limpa_graficos(pdata->stat->restart_bt, pdata->graph, 0); // garante que os vetores estão a zeros no início.

  // Criação e definição da janela

  pdata->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(pdata->window), pdata->win_xlen, pdata->win_ylen);
  gtk_window_set_title (GTK_WINDOW(pdata->window), "Baloiço");
  gtk_window_set_position (GTK_WINDOW(pdata->window), GTK_WIN_POS_CENTER);
  gtk_window_set_resizable (GTK_WINDOW(pdata->window), TRUE);

   /* Usa-se a macro definida em GObject para atuar em objetos em determinados eventos 

     A função gtk_main_quit() funciona como um break para o ciclo gtk_main() */

  // g_signal_connect(instance, detailed signal [ver apêndice Events and Signals], c handler [função do tipo GCallback], data (ponteiro);

  g_signal_connect (G_OBJECT(pdata->window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  // Criação do contentor vertical (onde serão colocados todos os elementos visíveis)

  overlay = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add (GTK_CONTAINER(pdata->window), overlay);

  // Criação do contentor onde será mostrado o baloiço

  swingbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start (GTK_BOX(overlay), swingbox, TRUE, TRUE, 0);

  // Criação do contentor para as condições iniciais e definições dos gráficos

  setbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start (GTK_BOX(overlay), setbox, TRUE, TRUE, 2);

  // Criação da frame para as definições
  
  frame[0] = gtk_frame_new ("  Painel de Controlo");
  gtk_box_pack_start (GTK_BOX(overlay), frame[0], TRUE, TRUE, 3);
  gtk_frame_set_label_align (GTK_FRAME(frame[0]), 0.5 , 0.5);

  // Criação da frame para as condições iniciais

  frame[1] = gtk_frame_new (" Condi\u00E7\u00F5es Iniciais");
  gtk_box_pack_start (GTK_BOX(setbox), frame[1], TRUE, TRUE, 0);
  gtk_frame_set_label_align (GTK_FRAME(frame[1]), 0.5 , 0.5);

  // Criação da frame para as definições dos gráficos

  frame[2] = gtk_frame_new ("  Gr\u00E1ficos");
  gtk_box_pack_start (GTK_BOX(setbox), frame[2], TRUE, TRUE, 0);
  gtk_frame_set_label_align (GTK_FRAME(frame[2]), 0.5 , 0.5);
  
  // Criação do contentor onde serão mostradas as definições

  settingsbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(frame[0]), settingsbox);

  // Criação do contentor onde serão mostradas as condições iniciais

  initsetbox =  gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(frame[1]), initsetbox);

  // Criação do contentor onde serão mostradas as definições dos gráficos
  
  graphsetbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(frame[2]), graphsetbox);

  // Criação dos contentores ('boxes')

  for (i = 0; i < 24; i++)
    {
      if (i == 20 || i == 21)
	sbox[i] = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 3);
      
      else
	sbox[i] = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
      
       gtk_container_set_border_width (GTK_CONTAINER (sbox[i]), 5);

       if ((i > 5 && i < 10 && i != 7) || (i > 20 && i != 23))
         gtk_container_add (GTK_CONTAINER(initsetbox), sbox[i]);

       else
	 {
	   if ((i > 13 && i < 19) || i == 23)
	      gtk_container_add (GTK_CONTAINER(graphsetbox), sbox[i]);

	   else
	      gtk_container_add (GTK_CONTAINER(settingsbox), sbox[i]);
	 }
    }

  // Criação da 'Combo Box' para as Geometrias 'Default'

  combo[2] = gtk_combo_box_text_new();
  gtk_widget_set_size_request (combo[2], 52, 29);
  
  for (i = 0; i < 2; i++)
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(combo[2]), default_set[i]); 

  gtk_combo_box_set_active (GTK_COMBO_BOX(combo[2]), 0);
  gtk_box_pack_start (GTK_BOX (sbox[12]), combo[2], FALSE, TRUE, 0);

  for (i = 0; i < 3; i++)
    {
      g_signal_connect (G_OBJECT (combo[2]), "changed", G_CALLBACK (cb_combobox3_function), m[i]);
      g_signal_connect (G_OBJECT (combo[2]), "changed", G_CALLBACK (cb_combobox3_function), l[i]);
    }

  // Criação da 'Combo Box' para os Planetas

  combo[3] = gtk_combo_box_text_new();
  gtk_widget_set_size_request (combo[3], 52, 29);
  
  for (i = 0; i < 9; i++)
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(combo[3]), planets[i]); 

  gtk_combo_box_set_active (GTK_COMBO_BOX(combo[3]), 2);
  gtk_box_pack_start (GTK_BOX (sbox[12]), combo[3], FALSE, TRUE, 0);
  g_signal_connect (G_OBJECT (combo[3]), "changed", G_CALLBACK (cb_combobox4_function), g);

  //  Pause/Play button  : Semelhante ao funcionamento do Restart Button!
  pdata->stat->pause_play_bt = gtk_button_new_with_label(pause_play_lb);
  gtk_box_pack_start (GTK_BOX(sbox[20]), pdata->stat->pause_play_bt, TRUE, TRUE, 0);
  gtk_widget_set_size_request (pdata->stat->pause_play_bt, 40, 40);
  g_signal_connect (G_OBJECT(pdata->stat->pause_play_bt), "clicked", G_CALLBACK(pause_play_fun), pdata);

  //  Restart button : A função 'restart_fun' apenas altera o valor de pdata->stat->start para 1;
  pdata->stat->restart_bt = gtk_button_new();
  restart = gtk_image_new_from_file ("./restart.png");
  gtk_button_set_image (GTK_BUTTON(pdata->stat->restart_bt), restart);
  gtk_box_pack_start (GTK_BOX(sbox[20]), pdata->stat->restart_bt, TRUE, TRUE, 0);
  gtk_widget_set_size_request (pdata->stat->restart_bt, 40, 40);
  g_signal_connect (G_OBJECT(pdata->stat->restart_bt), "clicked", G_CALLBACK(restart_fun), pdata->stat);

  // Criação do botão para limpar os gráficos
  
  clean_bt = gtk_button_new_with_label(limpar_lb);
  gtk_box_pack_start (GTK_BOX(sbox[23]), clean_bt, TRUE, TRUE, 0);
  gtk_widget_set_size_request (clean_bt, 50, 30);
  g_signal_connect (G_OBJECT(clean_bt), "clicked", G_CALLBACK(limpa_graficos), pdata->graph);
  
  // Condições Iniciais (Default)
  
  pdata->l[0] = 2;
  pdata->l[1] = 0.6;
  pdata->l[2] = 0.6;
  pdata->phi = pdata->phi0  = 0.; 
  pdata->dphi = pdata->dphi0 = 0.;
  pdata->theta0 = pdata->theta = 0.3; 
  pdata->m[0] = 12;
  pdata->m[1] = 6;
  pdata->m[2] = 12; 
  pdata->w = 2;
  pdata->t = 0;
  pdata->dt = 1e-4;
  pdata->time = 1000;
  pdata->g = 9.8;
  pdata->active_radio = 1;
  pdata->stat->pausa  = 1;
  pdata->color[1][0] = 1;
  pdata->color[2][0] = 0.361;
  pdata->color[2][1] = 0.741;
  pdata->color[2][2] = 0.918;

  // Valores Iniciais (Gráfico)

  pdata->graph->scale[0] = pdata->graph->scale[1] = 2.5;
  pdata->graph->ZOOM_X = 1.5;
  pdata->graph->ZOOM_Y = 60;
  pdata->graph->rgb[0][0] = 1;
  pdata->graph->rgb[1][2] = 1;
  pdata->graph->active_graph[0] = 1;
  pdata->graph->show_value = 1;
  
  // Valores Iniciais (Scale)

  for (i = 0; i < 3; i++)
    {
      m[i]->min             = 2;
      m[i]->max             = 35;
      m[i]->step            = 1;
      l[i]->min             = 0.2;
      l[i]->max             = 2.5;
      l[i]->step            = 0.1;
    }

  m[0]->ch_LabelValue   = "m1:  %2.1lf kg" ;
  m[0]->ScaleInitValue  = 12.0;
  m[1]->ch_LabelValue   = "m2:  %2.1lf kg" ;
  m[1]->ScaleInitValue  = 6.0;
  m[2]->ch_LabelValue   = "m3:  %2.1lf kg" ;
  m[2]->ScaleInitValue  = 12.0;

  l[0]->ch_LabelValue   = "l1:  %2.1lf m" ;
  l[0]->ScaleInitValue  = 2;
  l[1]->ch_LabelValue   = "l2:  %2.1lf m" ;
  l[1]->ScaleInitValue  = 0.6;
  l[2]->ch_LabelValue   = "l3:  %2.1lf m" ;
  l[2]->ScaleInitValue  = 0.6;

  theta->ch_LabelValue   = "\u03B8\u2080 :  %2.1lf º" ; // em graus!
  theta->ScaleInitValue  = 17.2;
  theta->min             = 0.0;
  theta->max             = 40.0;
  theta->step            = 0.1;

  omega->ch_LabelValue   = "\u03C9:  %1.2lf rad/s" ;
  omega->ScaleInitValue  = 2;
  omega->min             = 0.1;
  omega->max             = 5;
  omega->step            = 0.1;

  phi->ch_LabelValue   = "\u03C6\u2080 :  %2.1lf º" ;
  phi->ScaleInitValue  = 0.;
  phi->min             = 0.0;
  phi->max             = 0.6;
  phi->step            = 0.1;

  dphi->ch_LabelValue   = "\u03C6\u0307\u2080 :  %1.2lf rad/s" ;
  dphi->ScaleInitValue  = 0.;
  dphi->min             = 0.1;
  dphi->max             = 0.2;
  dphi->step            = 0.01;

  g->ch_LabelValue   = "g:  %2.1lf m/s\u00B2" ;
  g->ScaleInitValue  = 9.8;
  g->min             = 1.0;
  g->max             = 25;
  g->step            = 0.1;

  t->ch_LabelValue   = "Tempo:  %1.2lf x \n" ;
  t->ScaleInitValue  = 1;
  t->min             = 0.1;
  t->max             = 3;
  t->step            = 0.1;

  yy_scale->ch_LabelValue   = "Escala Vertical: %1.2lf x" ;
  yy_scale->ScaleInitValue  = 1;
  yy_scale->min             = 0.05;
  yy_scale->max             = 3;
  yy_scale->step            = 0.1;

  xx_scale->ch_LabelValue   = "Escala do Tempo: %1.2lf x" ;
  xx_scale->ScaleInitValue  = 1;
  xx_scale->min             = 0.5;
  xx_scale->max             = 2.5;
  xx_scale->step            = 0.05;
  
  // Criação das 'scales'

  for (i = 0; i < 3; i++)
    {
      m[i]->scale = cria_scale (m[i]);
      m[i]->id = i + 1;
      m[i]->pdata = pdata;
      gtk_box_pack_start (GTK_BOX(sbox[i]), m[i]->scale, TRUE, TRUE, 3);
      sprintf (str[i], m[i]->ch_LabelValue, m[i]->ScaleInitValue);
      m[i]->label = gtk_label_new (str[i]);
      gtk_box_pack_start (GTK_BOX(sbox[i]), m[i]->label, TRUE, TRUE, 0);
      g_signal_connect (G_OBJECT(m[i]->scale), "value-changed", G_CALLBACK(cb_change_scale), m[i]);
    }

  for (i = 0; i < 3; i++)
    {
      l[i]->scale = cria_scale (l[i]);
      l[i]->id = i + 4;
      l[i]->pdata = pdata;
      gtk_box_pack_start (GTK_BOX(sbox[i+3]), l[i]->scale, TRUE, TRUE, 3);
      sprintf (str[i+3], l[i]->ch_LabelValue, l[i]->ScaleInitValue);
      l[i]->label = gtk_label_new (str[i+3]);
      gtk_box_pack_start (GTK_BOX(sbox[i+3]), l[i]->label, TRUE, TRUE, 0);
      g_signal_connect (G_OBJECT(l[i]->scale), "value-changed", G_CALLBACK(cb_change_scale), l[i]);
    }
  
  theta->scale = cria_scale (theta);
  theta->id = 7;
  theta->pdata = pdata;
  gtk_box_pack_start (GTK_BOX(sbox[6]), theta->scale, TRUE, TRUE, 3);
  sprintf (str[6], theta->ch_LabelValue, theta->ScaleInitValue);
  theta->label = gtk_label_new (str[6]);
  gtk_box_pack_start (GTK_BOX(sbox[6]), theta->label, TRUE, TRUE, 0);
  g_signal_connect (G_OBJECT(theta->scale), "value-changed", G_CALLBACK(cb_change_scale), theta);

  omega->scale = cria_scale (omega);
  omega->id = 8;
  omega->pdata = pdata;
  gtk_box_pack_start (GTK_BOX(sbox[7]), omega->scale, TRUE, TRUE, 3);
  sprintf (str[7], omega->ch_LabelValue, omega->ScaleInitValue);
  omega->label = gtk_label_new (str[7]);
  gtk_box_pack_start (GTK_BOX(sbox[7]), omega->label, TRUE, TRUE, 0);
  g_signal_connect (G_OBJECT(omega->scale), "value-changed", G_CALLBACK(cb_change_scale), omega);

  phi->scale = cria_scale (phi);
  phi->id = 9;
  phi->pdata = pdata;
  gtk_box_pack_start (GTK_BOX(sbox[8]), phi->scale, TRUE, TRUE, 3);
  sprintf (str[8], phi->ch_LabelValue, phi->ScaleInitValue);
  phi->label = gtk_label_new (str[8]);
  gtk_box_pack_start (GTK_BOX(sbox[8]), phi->label, TRUE, TRUE, 0);
  g_signal_connect (G_OBJECT(phi->scale), "value-changed", G_CALLBACK(cb_change_scale), phi);

  dphi->scale = cria_scale (dphi);
  dphi->id = 10;
  dphi->pdata = pdata;
  gtk_box_pack_start (GTK_BOX(sbox[9]), dphi->scale, TRUE, TRUE, 3);
  sprintf (str[9], dphi->ch_LabelValue, dphi->ScaleInitValue);
  dphi->label = gtk_label_new (str[9]);
  gtk_box_pack_start (GTK_BOX(sbox[9]), dphi->label, TRUE, TRUE, 0);
  g_signal_connect (G_OBJECT(dphi->scale), "value-changed", G_CALLBACK(cb_change_scale), dphi);

  g->scale = cria_scale (g);
  g->id = 11;
  g->pdata = pdata;
  gtk_box_pack_start (GTK_BOX(sbox[10]), g->scale, TRUE, TRUE, 3);
  sprintf (str[10], g->ch_LabelValue, g->ScaleInitValue);
  g->label = gtk_label_new (str[10]);
  gtk_box_pack_start (GTK_BOX(sbox[10]), g->label, TRUE, TRUE, 0);
  g_signal_connect (G_OBJECT(g->scale), "value-changed", G_CALLBACK(cb_change_scale), g);

  t->scale = cria_scale (t);
  t->id = 12;
  t->pdata = pdata;
  gtk_box_pack_start (GTK_BOX(sbox[11]), t->scale, TRUE, TRUE, 3);
  sprintf (str[11], t->ch_LabelValue, t->ScaleInitValue);
  t->label = gtk_label_new (str[11]);
  gtk_box_pack_start (GTK_BOX(sbox[11]), t->label, TRUE, TRUE, 0);
  g_signal_connect (G_OBJECT(t->scale), "value-changed", G_CALLBACK(cb_change_scale), t);

  yy_scale->scale = cria_scale (yy_scale);
  yy_scale->id = 13;
  yy_scale->pdata = pdata;
  sprintf (str[12], yy_scale->ch_LabelValue, yy_scale->ScaleInitValue);
  yy_scale->label = gtk_label_new (str[12]);
  gtk_box_pack_start (GTK_BOX(sbox[17]), yy_scale->scale, TRUE, TRUE, 3);
  gtk_box_pack_start (GTK_BOX(sbox[17]), yy_scale->label, TRUE, TRUE, 0);
  g_signal_connect (G_OBJECT(yy_scale->scale), "value-changed", G_CALLBACK(cb_change_scale), yy_scale);

  xx_scale->scale = cria_scale (xx_scale);
  xx_scale->id = 14;
  xx_scale->pdata = pdata;
  sprintf (str[13], xx_scale->ch_LabelValue, xx_scale->ScaleInitValue);
  xx_scale->label = gtk_label_new (str[13]);
  gtk_box_pack_start (GTK_BOX(sbox[18]), xx_scale->scale, TRUE, TRUE, 3);
  gtk_box_pack_start (GTK_BOX(sbox[18]), xx_scale->label, TRUE, TRUE, 0);
  g_signal_connect (G_OBJECT(xx_scale->scale), "value-changed", G_CALLBACK(cb_change_scale), xx_scale);
  
 // Criação da 'label' para o Gráfico 1

  label[0] = gtk_label_new ("  Gr\u00E1fico 1");
   gtk_box_pack_start (GTK_BOX (sbox[15]), label[0], FALSE, TRUE, 0);
  
  // Criação da 'Combo Box' para o gráfico 1
  
  combo[0] = gtk_combo_box_text_new();
  gtk_widget_set_size_request (combo[0], 52, 29);
  
  for(i = 0; i < 8; i++)
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(combo[0]), cb_text[i]);     // A lista de opções aparece centrada na escolhida anteriormente

  gtk_combo_box_set_active (GTK_COMBO_BOX(combo[0]), 0);
  gtk_box_pack_start (GTK_BOX (sbox[15]), combo[0], FALSE, TRUE, 0);
  g_signal_connect (G_OBJECT (combo[0]), "changed", G_CALLBACK (cb_combobox_function), pdata->graph);

  // Criação do botão para alterar as cores do gráfico 1

  color_button[0] = gtk_button_new_with_label ("Cor");
  gtk_widget_set_name (GTK_WIDGET(color_button[0]), "Color_1");
  gtk_widget_set_size_request (color_button[0], 100, 22);
  gtk_box_pack_start (GTK_BOX (sbox[15]), color_button[0], FALSE, TRUE, 0);
  g_signal_connect (color_button[0], "clicked", G_CALLBACK(color_chooser), pdata);

  // Criação da 'label' para o Gráfico 2

  label[1] = gtk_label_new ("\n  Gr\u00E1fico 2");
  gtk_box_pack_start (GTK_BOX (sbox[16]), label[1], FALSE, TRUE, 0);

  // Criação da 'Combo Box' para o gráfico 2
  
  combo[1] = gtk_combo_box_text_new();
  gtk_widget_set_size_request (combo[1], 52, 29);
  
  for(i = 0; i < 8; i++)
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(combo[1]), cb_text[i]);     // A lista de opções aparece centrada na escolhida anteriormente

  pdata->graph->id[1] = 7;  
  gtk_combo_box_set_active (GTK_COMBO_BOX(combo[1]), 7);
  gtk_box_pack_start (GTK_BOX (sbox[16]), combo[1], FALSE, TRUE, 0);
  g_signal_connect (G_OBJECT (combo[1]), "changed", G_CALLBACK (cb_combobox2_function), pdata->graph);

  // Criação do botão para alterar as cores do gráfico 2

  color_button[1] = gtk_button_new_with_label ("Cor");
  gtk_widget_set_name (GTK_WIDGET(color_button[1]), "Color_2");
  gtk_widget_set_size_request (color_button[1], 100, 22);
  gtk_box_pack_start (GTK_BOX (sbox[16]), color_button[1], FALSE, TRUE, 0);
  g_signal_connect (color_button[1], "clicked", G_CALLBACK(color_chooser), pdata);

  // Criação do 'check button' para mostrar os valores dos gráficos

  check_button = gtk_check_button_new_with_label ("Mostrar Valores");
  gtk_box_pack_start (GTK_BOX (sbox[16]), check_button, FALSE, TRUE, 0);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(check_button), TRUE); // um check_button é uma 'subclasse' do toggle button
  g_signal_connect (GTK_CHECK_BUTTON(check_button), "toggled", G_CALLBACK(Check), pdata->graph);
  
  // Cria um 'radio button'

  radio[0] = gtk_radio_button_new (NULL);
  radio[0] = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio[0]), "m1");

  // Create a radio button with a label
  radio[1] = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio[0]), "m2");
  radio[2] = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio[0]), "m3");

  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radio[0]), TRUE);

  gtk_widget_set_name (GTK_WIDGET(radio[0]), "radio_1");
  gtk_widget_set_name (GTK_WIDGET(radio[1]), "radio_2");
  gtk_widget_set_name (GTK_WIDGET(radio[2]), "radio_3");

  g_signal_connect (GTK_TOGGLE_BUTTON(radio[0]), "toggled", G_CALLBACK(Radio_Ga_Ga), pdata);
  g_signal_connect (GTK_TOGGLE_BUTTON(radio[1]), "toggled", G_CALLBACK(Radio_Ga_Ga), pdata);
  g_signal_connect (GTK_TOGGLE_BUTTON(radio[2]), "toggled", G_CALLBACK(Radio_Ga_Ga), pdata);
  
  gtk_box_pack_start (GTK_BOX (sbox[21]), radio[0], FALSE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (sbox[21]), radio[1], FALSE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (sbox[21]), radio[2], FALSE, TRUE, 0);

  // Criação do botão para alterar as cores das massas

  color_button[2] = gtk_button_new_with_label ("Cor");
  gtk_widget_set_name (GTK_WIDGET(color_button[2]), "Color_3");
  gtk_widget_set_size_request (color_button[2], 80, 12);
  gtk_box_pack_start (GTK_BOX (sbox[22]), color_button[2], FALSE, TRUE, 0);
  g_signal_connect (color_button[2], "clicked", G_CALLBACK(color_chooser), pdata);

  // Criação da drawing area onde estará o baloiço

  pdata->darea = gtk_drawing_area_new ();
  gtk_widget_set_size_request (pdata->darea, 500, 500);
  gtk_container_add (GTK_CONTAINER (swingbox), pdata->darea);
  
  g_signal_connect (G_OBJECT(pdata->darea), "draw", G_CALLBACK(on_draw_event), pdata);

  g_timeout_add (50, (GSourceFunc) time_handler, pdata);

  // Criação da drawing area onde estarão os gráficos

  pdata->graph->garea = gtk_drawing_area_new (),
  gtk_widget_set_size_request (pdata->graph->garea, 200, 200);
  gtk_container_add (GTK_CONTAINER (swingbox), pdata->graph->garea);

  g_signal_connect(G_OBJECT(pdata->graph->garea), "draw", G_CALLBACK(draw_graph), pdata);

  // Mostra a janela e todos os objetos
  
  gtk_widget_show_all(pdata->window);

  // Entra no ciclo de criação dos objetos
  
  gtk_main ();

  /** Libertar memória  **/
  
  for(i = 0; i < 2; i++)
    {
      free(pdata->graph->x[i]);
      free(pdata->graph->y[i]);
    }

  for(i = 0; i < 3; i++)
    {
      free(m[i]);
      free(l[i]);
    }

  free(pdata->graph);
  free(pdata->stat);
  free(theta);
  free(omega);
  free(phi);
  free(dphi);    
  free(pdata);
  free(g);
  free(t);
  free(yy_scale);

  return 0;
}
