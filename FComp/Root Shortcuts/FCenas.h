#include "Groot.h"

void DrawTGraph(int npoints, double * x, double * y, TCanvas *c, const char *title = "", const char *xtitle = "", const char *ytitle = "", const char *filename = "plot.eps", int marker_style = 7, const char *DrawOption = "AC");
void DrawTGraph(int npoints, double * x, double * y, TCanvas *c, double xmin, double xmax, double ymin, double ymax, const char *title = "", const char *xtitle = "", const char *ytitle = "", const char *filename = "plot.eps", int marker_style = 7, const char *DrawOption = "AC");
void DrawTGraph(int npoints, double * x, double * y, TCanvas *c, int pad, const char *title = "", const char *xtitle = "", const char *ytitle = "", int marker_style = 7, const char *DrawOption = "AC");
void DrawTGraph(int npoints, double * x, double * y, TCanvas *c, int pad, double xmin, double xmax, double ymin, double ymax, const char *title = "", const char *xtitle = "", const char *ytitle = "", int marker_style = 7, const char *DrawOption = "AC");

void DrawHistogram(int nbins, double * bincontent, double min, double max, TCanvas *c, const char * title = "", const char * xtitle = "", const char * ytitle = "", const char *filename = "plot.eps", double line_width = 2, Color_t color = kRed, const char *DrawOption = "L");
void DrawHistogram(int nbins, double * bincontent, double min, double max, TCanvas *c, int pad,  const char * title = "",  const char * xtitle = "", const char * ytitle = "", double line_width = 2, Color_t color = kRed, const char *DrawOption = "L");

void DrawTGraph2D(int npoints, double * x, double * y, double * z, TCanvas *c, const char *title = "", const char *xtitle = "", const char *ytitle = "", const char *ztitle = "", const char *filename = "plot.eps", int marker_style = 7, const char *DrawOption = "LINE");
void DrawTGraph2D(int npoints, double * x, double * y, double * z, TCanvas *c, double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, const char *title = "", const char *xtitle = "", const char *ytitle = "", const char *ztitle = "", const char *filename = "plot.eps", int marker_style = 7, const char *DrawOption = "LINE");
void DrawTGraph2D(int npoints, double * x, double * y, double * z, TCanvas *c, int pad, const char *title = "", const char *xtitle = "", const char *ytitle = "", const char *ztitle = "", int marker_style = 7, const char *DrawOption = "LINE");
void DrawTGraph2D(int npoints, double * x, double * y, double * z, TCanvas *c, int pad, double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, const char *title = "", const char *xtitle = "", const char *ytitle = "", const char *ztitle = "", int marker_style = 7, const char *DrawOption = "LINE");

void AddToMultiGraph(TMultiGraph * mg, int npoints, double * x, double * y, TCanvas *c, const char *title = "", const char *xtitle = "", const char *ytitle = "", const char *filename = "plot.eps", int marker_style = 7, const char *DrawOption = "AP");
void AddToMultiGraph(TMultiGraph * mg, int npoints, double * x, double * y, TCanvas *c, double xmin, double xmax, double ymin, double ymax, const char *title = "", const char *xtitle = "", const char *ytitle = "", const char *filename = "plot.eps", int marker_style = 7, const char *DrawOption = "AP");
void AddToMultiGraph(TMultiGraph * mg, int npoints, double * x, double * y, TCanvas *c, int pad, const char *title = "", const char *xtitle = "", const char *ytitle = "", int marker_style = 7, const char *DrawOption = "AP");
void AddToMultiGraph(TMultiGraph * mg, int npoints, double * x, double * y, TCanvas *c, int pad, double xmin, double xmax, double ymin, double ymax, const char *title = "", const char *xtitle = "", const char *ytitle = "", int marker_style = 7, const char *DrawOption = "AP");

void DrawHistogram2D(int nbinsx, int nbinsy, double ** bincontent, double xmin, double xmax, double ymin, double ymax, TCanvas *c, const char * title = "", const char * xtitle = "", const char * ytitle = "", const char *filename = "plot.eps", double line_width = 2, Color_t color = kRed, const char *DrawOption = "L");
void DrawHistogram2D(int nbinsx, int nbinsy, double ** bincontent, double xmin, double xmax, double ymin, double ymax, TCanvas *c, int pad, const char * title = "", const char * xtitle = "", const char * ytitle = "", double line_width = 2, Color_t color = kRed, const char *DrawOption = "L");

// Hist2D
// Multi-Graph with Errors
// a TLegend ?? para a canvas, pode ser sempre acrescentada
