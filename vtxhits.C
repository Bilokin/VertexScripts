
#define MAXN  1000
#include <iostream>
using std::cout;

void vtxhits(){
	TFile * file = TFile::Open("TrashRecoTest.root");
	int bin_e = 50;
	float max_e =60;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,1000,500);
	TH1F * disthist = new TH1F("disthist", "", bin_e,0.0,max_e);
	TH1F * disthistd = new TH1F("disthistd", "", bin_e,0.0,max_e);
	TTree * tree = MissedTracks;
	tree->Project("disthist","distanceIPMissed * sqrt( 1 - costhetaMissed*costhetaMissed)", "abs(costhetaMissed) < .72 && isrecoMissed > -1 && hastrackMissed == 1 && vtxHitsMissed == 6");
	tree->Project("disthistd","distanceIPMissed * sqrt( 1 - costhetaMissed*costhetaMissed)", " abs(costhetaMissed) < 0.72 && isrecoMissed > -1 && hastrackMissed == 1 && vtxHitsMissed  == 0");
	disthist->SetLineWidth(3);
	disthist->SetLineColor(kBlue);
	disthist->Draw("same");
	disthistd->SetLineWidth(3);
	disthistd->SetLineColor(kGreen);
	disthistd->Draw("same");
	THStack * stackp = new THStack("satck","d_t;d_t, mm");
	stackp->Add(disthist);
	stackp->Add(disthistd);
	stackp->Draw();

}
