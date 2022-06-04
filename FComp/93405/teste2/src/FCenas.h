#include "TGraph.h"
#include "Groot.h"

void DrawTGraph(int npoints, double * x, double * y, TCanvas *c, const char *title = "", const char *xtitle = "", const char *ytitle = "", const char *filename = "plot.eps", int marker_style = 7, const char *DrawOption = "AC");
void DrawTGraph(int npoints, double * x, double * y, TCanvas *c, double xmin, double xmax, double ymin, double ymax, const char *title = "", const char *xtitle = "", const char *ytitle = "", const char *filename = "plot.eps", int marker_style = 7, const char *DrawOption = "AC");
void DrawTGraph(int npoints, double * x, double * y, TCanvas *c, int pad, const char *title = "", const char *xtitle = "", const char *ytitle = "", int marker_style = 7, const char *DrawOption = "AC");
void DrawTGraph(int npoints, double * x, double * y, TCanvas *c, int pad, double xmin, double xmax, double ymin, double ymax, const char *title = "", const char *xtitle = "", const char *ytitle = "", int marker_style = 7, const char *DrawOption = "AC");


void DrawHistogram(int nbins, double * bincontent, TCanvas *c, const char * xtitle = "", const char * ytitle = "", const char *filename = "plot.eps", double line_width = 2, Color_t color = kRed, const char *DrawOption = "L");
void DrawHistogram(int nbins, double * bincontent, TCanvas *c, int pad, const char * xtitle = "", const char * ytitle = "", double line_width = 2, Color_t color = kRed, const char *DrawOption = "L");
