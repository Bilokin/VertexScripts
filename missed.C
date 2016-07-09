#define MAXN  100
#include <iostream>
using std::cout;

float sigma(float offset, float p, float theta)
{
	float a = 0.005;
	float b = 0.01;
	float sin43 = std::pow( std::sin(theta), 4.0/3.0);
	return offset;
	//return offset / a;
	//return offset /sqrt(a*a + b*b / p / p / sin43);//*1000;

}

void missed(string recofilename = "TrashRecoTest.root", string mcfilename = "TrashMCTest.root", string vtxfilename = "VertexRestorer.root")
{
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TFile * vtxfile = TFile::Open(vtxfilename.c_str());//, "read");
	TTree * primaryTree = Primaries;
	TTree * purgatoryTree = Purgatory;
	TFile * mcfile = TFile::Open(mcfilename.c_str());//, "read");
	TTree * mcTrackTree = Tracks;
	TFile * recofile = TFile::Open(recofilename.c_str());//, "read");
	TTree * missedTracks = MissedTracks;
	TTree * missedVtx = MissedVertex;
	int bin_e = 50;
	float min_e = 0;
	float max_e = 5;
	TH1F * missedhist = new TH1F("missedhist", ";#epsilon [mm]", bin_e,min_e,max_e);
	TH1F * genhist = new TH1F("genhist", ";#epsilon [mm]", bin_e,min_e,max_e);
	TH1F * purhist = new TH1F("purhist", ";#epsilon [mm]", bin_e,min_e,max_e);
	TH1F * primehist = new TH1F("primehist", ";#epsilon [mm]", bin_e,min_e,max_e);
	bool vtx = 0;
	bool ftd = 0;
	missedTracks->Project("missedhist","offsetMissed","offsetMissed < 5 && offsetMissed > 0");
	missedVtx->Project("+missedhist","offsetOfParticlesVtx","offsetOfParticlesVtx < 5 && offsetOfParticlesVtx > 0");
	purgatoryTree->Project("purhist","purgatoryOffset", "purgatoryOffset < 5");
	primaryTree->Project("primehist","primeOffset", "primeOffset < 5");
	if (vtx) 
	{
		purgatoryTree->Project("purhist","purgatoryOffset", "purgatoryOffset < 5 && purgatoryVtxHits > 3");
		primaryTree->Project("primehist","primeOffset", "primeOffset < 5 && primeVtxHits > 3");
	}
	if (ftd) 
	{
		purgatoryTree->Project("purhist","purgatoryOffset", "purgatoryOffset < 5 && purgatoryFtdHits > 1");
		primaryTree->Project("primehist","primeOffset", "primeOffset < 5 && primeFtdHits > 1");
	}
	mcTrackTree->Project("genhist", "coffsettrack", "coffsettrack < 5"); 
	mcTrackTree->Project("+genhist", "boffsettrack", "boffsettrack < 5"); 
	mcTrackTree->Project("+genhist", "cbaroffsettrack", "cbaroffsettrack < 5"); 
	mcTrackTree->Project("+genhist", "bbaroffsettrack", "bbaroffsettrack < 5"); 
	purhist->SetMarkerStyle(22);
	purhist->SetMarkerSize(1.2);
	purhist->SetMarkerColor(kRed+1);

	primehist->SetMarkerStyle(21);
	primehist->SetMarkerSize(1.0);
	primehist->SetMarkerColor(kRed+2);

	missedhist->SetLineColor(kRed);
	missedhist->SetLineWidth(3);
	
	genhist->SetStats(0);
	genhist->SetFillColor(kGreen);
	genhist->SetLineColor(kGreen+1);
	genhist->SetLineWidth(3);
	genhist->SetMaximum(primehist->GetBinContent(1) * 1.5);
	gPad->SetLogy();
	genhist->Draw();
	primehist->Draw("samep");
	purhist->Draw("samep");
	missedhist->Draw("sameh");
	TLegend *legendMean = new TLegend(0.47,0.6,0.85,0.82,NULL,"brNDC");
	legendMean->SetFillColor(kWhite);
	legendMean->SetBorderSize(0);
	legendMean->AddEntry(genhist,"generated SOT-Particles","fp");
	legendMean->AddEntry(missedhist,"LSOT-Particles","f");
	legendMean->AddEntry(primehist,"primary particles","p");
	legendMean->AddEntry(purhist,"no vertex particles","p");
	legendMean->Draw();
	gPad->Modified();
	//vtxfile->Close();
	//recofile->Close();
	//mcfile->Close();
}

