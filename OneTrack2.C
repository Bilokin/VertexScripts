
#include <unistd.h>
#include <iostream>
#define MAXV 8
void OneTrack2()
{
	TFile * file = TFile::Open("TrashRecoTest.root");
	int bin_e = 25;
	int max_e = 1;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * cosOne = new TH1F("cosOne", "E(Ntracks)", bin_e,-1.0,max_e);
	TH1F * cosOtherLow = new TH1F("cosOtherLow", "tracks", bin_e,-1.0,max_e);
	TH1F * cosOtherHigh = new TH1F("cosOtherHigh", "tracks", bin_e,-1.0,max_e);
	TH1F * cosOtherLowDist = new TH1F("cosOtherLowDist", "tracks", bin_e,-1.0,max_e);

	
	TTree * normaltree = MissedVertex;
	cosOne->SetFillColor(kBlue);
	cosOtherLow->SetFillColor(kYellow);
	cosOtherHigh->SetFillColor(kGreen);
	cosOtherLowDist->SetFillColor(kCyan);
	normaltree->Draw("costhetaMissedVtx >> cosOne","numberOfTracksMissedVtx < 2");
	normaltree->Draw("costhetaMissedVtx >> cosOtherLow","numberOfTracksMissedVtx > 1 && momentumMissedVtx < 15.0 && distanceMissedVtx > 0.8");
	normaltree->Draw("costhetaMissedVtx >> cosOtherHigh","numberOfTracksMissedVtx > 1 && momentumMissedVtx > 15.0 && distanceMissedVtx > 0.8");
	normaltree->Draw("costhetaMissedVtx >> cosOtherLowDist","numberOfTracksMissedVtx > 1 && momentumMissedVtx > 15.0 && distanceMissedVtx < 0.8");
	THStack * stack = new THStack("stack","cos#theta");
	stack->Add(cosOtherLow);
	stack->Add(cosOtherLowDist);
	stack->Add(cosOne);
	stack->Add(cosOtherHigh);
	stack->Draw();
	gPad->Modified();
}
