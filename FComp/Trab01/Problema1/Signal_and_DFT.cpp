#include <iostream>
#include <vector>
#include "Signal.h"
#include "DFT.h"
#include "FCtools.h"
#include "vec.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TApplication.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TPaletteAxis.h"

using namespace std;

int main()  {
	Signal s1=Signal("Signal.txt");
	s1.Plot("Signal_s1"); //Produce figure Signal_s1.eps

	cout << s1.GetTime().at(10) << endl;
	cout << s1[10].first << endl; //same objective of previous line but using in syntax s1[10]
	cout <<"s1.Size = "<<s1.Size()<<endl;

	Signal s2;
	s2=s1;
	s2.Plot("Signal_s2"); //Produce figure Signal_s2.eps

	Signal s3(s1*5.0);
	s3.Plot("Signal_s3"); //Produce figure Signal_s3.eps

	Signal s4;
	s4=s1*s3;
	s4.Plot("Signal_s4"); //Produce figure Signal_s4.eps

	DFT DFT1(s1);
	double fs=s1.Sampling_freq();
	cout << "Sampling Frequency = " << fs << endl;

	int nfreq=1000;
	double * freq = new double [nfreq];
	double * PS = new double [nfreq];
	for (int i = 0; i < nfreq; i++)
	{
		freq[i]=(((double)i)*18/999) + 2; //frequencies between 2 and 20Hz.
		PS[i]=DFT1.GetAmpSpec(freq[i]);
		//cout<<freq[i]<<"-"<<PS[i]<<endl;
	}

	TApplication *myapp=new TApplication("myapp",0,0);

	TCanvas* c = new TCanvas("c", "my canvas", 500, 500);
  //gStyle->SetOptStat(0);

	TMultiGraph *mg = new TMultiGraph();
	TGraph *g1 = new TGraph(nfreq, freq, PS);
	mg->Add(g1);
	mg->SetTitle("Amp(Freq(s1))"); g1->SetLineWidth(3); g1->SetLineColor(2);
	mg->GetXaxis()->SetTitle("Freq (Hz)");
	mg->GetYaxis()->SetTitle("Amplitude (a.u.)");
	mg->Draw("AL");

	gPad->Modified();

	c->Modified();
	c->SaveAs("MySpectra.eps");
    //Generate a plot of the Amplitude of the spectra with:
    // - The correct title to the plot and figure file generated
    // - X-Axis label "Freq (Hz)", y-axis label "Amplitude (a.u.)"
    // - Axis, scatter points and smooth curve connecting the points
    //...
	myapp->Run();
	delete[] freq;
	delete[] PS;

	return 0;
}
