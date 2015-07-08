#define MAXN  1000
#include <iostream>
using std::cout;

void misreco(){
	TFile * file = TFile::Open("TrashRecoTest.root");
	int bin_e = 50;
	float max_e = 1.5;
	float max_p = 20;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,1000,500);
	c1->Divide(2,1);
	TH1F * phist = new TH1F("phist", "Momentum misreco;|p|", bin_e,0.0,max_p);
	TH1F * phistd = new TH1F("phistd", "Momentum misreco;|p|", bin_e,0.0,max_p);
	//phist->Sumw2();
	TH1F * coshist = new TH1F("coshist", "cos#theta misreco;cos#theta", bin_e,-1.0,1);
	TH1F * coshistd = new TH1F("coshistd", "cos#theta misreco;cos#theta", bin_e,-1.0,1);
	//coshist->Sumw2();
	TTree * tree = MissedTracks;
	bool bytracks = 0;
	if (bytracks) 
	{
		tree->Project("phist","momentumMissed", "momentumMissed > 0 && isrecoMissed == 0 && hastrackMissed == 0");
		tree->Project("coshist","costhetaMissed", "momentumMissed > 0 && isrecoMissed == 0 && hastrackMissed == 0");
		tree->Project("phistd","momentumMissed", "momentumMissed > 0 && isrecoMissed == 0 && hastrackMissed == 1");
		tree->Project("coshistd","costhetaMissed", "momentumMissed > 0 && isrecoMissed == 0 && hastrackMissed == 1");
	}
	else 
	{
		tree->Project("phist","momentumMissed", "momentumMissed > 0 && isrecoMissed == 0 && interactedMissed == 1");
		tree->Project("coshist","costhetaMissed", "momentumMissed > 0 && isrecoMissed == 0 && interactedMissed == 1");
		tree->Project("phistd","momentumMissed", "momentumMissed > 0 && isrecoMissed == 0 && interactedMissed == 0");
		tree->Project("coshistd","costhetaMissed", "momentumMissed > 0 && isrecoMissed == 0 && interactedMissed == 0");
	}
	//tree->Project("phist","momentumMissed", "momentumMissed > 0 && vtxHitsMissed == 0");
	//tree->Project("coshist","costhetaMissed", "momentumMissed > 0 && vtxHitsMissed == 0");
	phist->SetLineColor(kRed);
	phist->SetFillColor(kRed+1);
	phist->SetLineWidth(3);
	coshist->SetLineColor(kRed);
	coshist->SetFillColor(kRed+1);
	coshist->SetLineWidth(3);
	phistd->SetLineColor(kYellow+1);
	phistd->SetFillColor(kYellow);
	phistd->SetLineWidth(3);
	coshistd->SetLineColor(kYellow+1);
	coshistd->SetFillColor(kYellow);
	coshistd->SetLineWidth(3);
	THStack * stackcos = new THStack("satckc","cos#theta misreco;cos#theta");
	THStack * stackp = new THStack("satck","Momentum misreco;|p|");
	stackp->Add(phistd);
	stackp->Add(phist);
	stackcos->Add(coshistd);
	stackcos->Add(coshist);
	c1->cd(1);
	stackp->Draw("");
	TLegend *legendMean = new TLegend(0.17,0.7,0.5,0.92,NULL,"brNDC");
	legendMean->SetFillColor(kWhite);
	legendMean->SetBorderSize(0);
	if (bytracks) 
	{
		legendMean->AddEntry(coshist,"No tracking information","fp");
		legendMean->AddEntry(coshistd,"Has tracking information","fp");

	}
	else 
	{
		legendMean->AddEntry(coshist,"Reached ECal","fp");
		legendMean->AddEntry(coshistd,"Decayed before ECal","fp");
	}
	legendMean->Draw();
	gPad->Modified();
	c1->cd(2);
	stackcos->Draw("");

	

}
