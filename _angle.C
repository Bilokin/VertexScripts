#define MAXN  1000
#include <iostream>
using std::cout;

void _angle(){
	TFile * file = TFile::Open("VertexRestorer.root");
	int bin_e = 50;
	float max_e = 0.5;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * alpha = new TH1F("alpha", "Momentum misreco;|p|", bin_e,0.0,max_e);
	TH1F * alphar = new TH1F("alphar", "Momentum misreco;|p|", bin_e,0.0,max_e);
	Test->Project("alphar","test1");
	Stats->Project("alpha","missedAngle");
	alphar->SetLineWidth(3);
	alphar->SetLineColor(kGray+1);
	alphar->SetFillColor(kGray);
	alpha->SetLineWidth(3);
	alpha->SetLineColor(kBlue);
	gPad->SetLogy();
	alphar->Draw();
	alpha->Draw("same");
}
