#include "InBox1D.h"
#include <cstdio>
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1F.h"
using namespace std;

int main()  {

	double x0=5.0;
	double v0=10.0;
	double WR=10.0;
	double alpha=0.99;
	double t0=0.0;

	InBox1D Obj(x0, v0, WR, alpha);

	double ttime=10.0; //total run time
	double dt=0.05; //step time...

	//prepare to store the solution in vectors...
	vector<double> xobj;
	xobj.push_back(x0);
	vector<double> vobj;
	vobj.push_back(v0);
	vector<double> tobj;
	tobj.push_back(t0);

	cout << Obj.GetV() << endl;

	double tcur=t0; // current time

	while (tcur <= ttime)
	{
		xobj.push_back(Obj.GetX());
		cout << Obj.GetX() << "     ";
		vobj.push_back(Obj.GetV());
		cout << Obj.GetV() << "     ";
		tobj.push_back(tcur);
		cout << tcur << endl;
		Obj.StepInTime(dt);
		tcur += dt;
		//...update solution storage...
	}

	int npoints = xobj.size();
	double * xptr=new double [npoints];
	double * vptr=new double [npoints];
	double * tptr=new double [npoints];

	for (int i = 0; i < npoints; i++)
	{
		xptr[i] = xobj[i];
		vptr[i] = vobj[i];
		tptr[i] = tobj[i];
	}

	//...now transfer the time, psoition-X and velocity-V to pointer arrays


TCanvas *c = new TCanvas("c", "My_trajectory",0,0,500,1000);

TPad *pad1 = new TPad("pad1","pad1", 0.00, 0.50, 1.00, 1.00, 0);

  pad1->SetLeftMargin(0.133);
  pad1->SetBottomMargin(0.1326316);
  pad1->SetRightMargin(0.04);
  pad1->Draw();
  pad1->cd();

	TGraph *gr1  = new TGraph(npoints, tptr, vptr);
	gr1->Draw("AC");
	gr1->Draw("ALP");
	gr1->SetTitle("");
	gr1->GetXaxis()->SetTitle("t (s)");
	gr1->GetYaxis()->SetTitle("v (m/s)");
	gr1->GetXaxis()->CenterTitle();
	gr1->GetYaxis()->CenterTitle();

//	gPad->Update();
	c->Update();
	c->Modified();
	c->SaveAs("Trajectory_v.eps");

	//c->SetSelected(c2);

TCanvas *c2 = new TCanvas("c2", "My_trajectory2",0,0,500,1000);

TPad *pad2 = new TPad("pad2","pad2", 0.0, 0.00, 1.00, 1.00, 0);

	TGraph *gr2  = new TGraph(npoints, tptr, xptr);

	pad2->SetLeftMargin(0.3);
	pad2->SetRightMargin(0.3);
	pad2->Draw();
	pad2->cd();

	c2->Modified();
	c2->cd();
	c2->SetSelected(c);

	// create graph
//	TGraph *gr2  = new TGraph(npoints, tptr, vptr);
	gr2->Draw("C");
	gr2->Draw("ALP");
	gr2->SetTitle("");
	gr2->GetXaxis()->SetTitle("t (s)");
	gr2->GetYaxis()->SetTitle("x (m)");
	gr2->GetXaxis()->CenterTitle();
	gr2->GetYaxis()->CenterTitle();

	c2->Update();
	c2->Modified();
	c2->SaveAs("Trajectory_x.eps");

TCanvas *c1 = new TCanvas("c1", "My_trajectory2",0,0,500,1000);

	TPad *pad3 = new TPad("pad3","pad3", 0.00, 0.00, 1.0, 1.0, 0);
	pad3->SetLeftMargin(0.3);
	pad3->SetRightMargin(0.3);
	pad3->Draw();
	pad3->cd();

	c1->Modified();
	c1->cd();
	c1->SetSelected(c);

	// create graph
	TGraph *gr3  = new TGraph(npoints, tptr, vptr);
	gr3->Draw("C");
	gr3->Draw("ALP");
	gr3->SetTitle("");
	gr3->GetXaxis()->SetTitle("t (s)");
	gr3->GetYaxis()->SetTitle("v (m/s)");
	gr3->GetXaxis()->CenterTitle();
	gr3->GetYaxis()->CenterTitle();

	c1->Update();
	c1->Modified();
	c1->SaveAs("Trajectory_limits.eps");

	return 0;
}
