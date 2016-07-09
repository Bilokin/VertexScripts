
#include <unistd.h>
#include <iostream>
#define MAXV 8
void OneTrack2(string filename = "RecoTest.root")
{
	TFile * file = TFile::Open(filename.c_str());
	int bin_e = 50;
	int max_e = 1;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,1000,500);
	c1->Divide(2,1);
	TH1F * cosReco = new TH1F("cosOne", "E(Ntracks)", bin_e,.0,max_e);
	TH1F * cosOne = new TH1F("cosOne", "E(Ntracks)", bin_e,.0,max_e);
	TH1F * cosOtherLow = new TH1F("cosOtherLow", "tracks", bin_e,.0,max_e);
	TH1F * cosOtherHigh = new TH1F("cosOtherHigh", "tracks", bin_e,.0,max_e);
	TH1F * cosOtherLowDist = new TH1F("cosOtherLowDist", "tracks", bin_e,.0,max_e);
	TH1F * cosAll = new TH1F("cosAll", "E(Ntracks)", bin_e,.0,max_e);

	c1->cd(2);
	TTree * normaltree = MissedVertex;
	cosOne->SetLineColor(kBlue);
	cosOne->SetLineWidth(3);
	//cosOtherLow->SetLineColor(kMagenta);
	//cosOtherLow->SetLineWidth(3);
	cosOtherHigh->SetLineColor(kRed);
	cosOtherHigh->SetLineWidth(3);
	cosOtherLowDist->SetLineColor(kGreen);
	cosOtherLowDist->SetLineWidth(3);
	//cosOne->SetFillColor(kBlue);
	//cosOtherLow->SetFillColor(kMagenta);
	//cosOtherHigh->SetFillColor(kRed);
	//cosOtherLowDist->SetFillColor(kGreen);
	cosOtherLowDist->SetTitle("|cos#theta_{vertex}|");
	int reconumber = TaggedVertices->Draw("abs(costhetaOfParticles) >> cosReco","momentumOfParticles > 0");
	normaltree->Draw("abs(costhetaMissedVtx) >> cosOne","numberOfTracksMissedVtx < 2");
	//normaltree->Draw("costhetaMissedVtx >> cosOtherLow","numberOfTracksMissedVtx > 1 && momentumMissedVtx < 15.0 && distanceMissedVtx > 0.8");
	normaltree->Draw("abs(costhetaMissedVtx) >> cosOtherHigh","numberOfTracksMissedVtx > 1 && momentumMissedVtx > 15.0 && distanceMissedVtx > .30");
	normaltree->Draw("abs(costhetaMissedVtx) >> cosOtherLowDist","numberOfTracksMissedVtx > 1 && ( momentumMissedVtx < 15.0 || distanceMissedVtx < .30)");
	THStack * stack = new THStack("stack","LSOT Vertex");
	//stack->Add(cosOtherLow);
	stack->Add(cosOtherLowDist);
	stack->Add(cosOne);
	stack->Add(cosOtherHigh);
	stack->Draw();
	TLegend *legendMean = new TLegend(0.25,0.6,0.75,0.85,NULL,"brNDC");
        legendMean->SetFillColor(kWhite);
        legendMean->SetBorderSize(0);
        legendMean->AddEntry(cosOtherHigh,"good SOT-Vertices","f");
        legendMean->AddEntry(cosOne,"0-1 track decay","f");
        legendMean->AddEntry(cosOtherLowDist,"d_{IP} < .30 mm or |p|_{B} < 15 GeV","f");
        //legendMean->AddEntry(cosOtherLow,"|p|_{B} < 15 GeV","fp");
	legendMean->Draw();
	stack->GetXaxis()->SetTitle("|cos#theta|");
	gPad->Modified();
	c1->cd(1);
	TTree * tree = MissedTracks;
	//TH1F * cosLowtr = new TH1F("cosLowtr", "tracks", bin_e,-1.0,max_e);
	TH1F * cosGoodTracks = new TH1F("cosGoodTracks", "tracks", bin_e,.0,max_e);
	TH1F * cosNoPFO = new TH1F("cosNoPFO", "tracks", bin_e,.0,max_e);
	TH1F * cosNoVTX = new TH1F("cosNoVTX", "tracks", bin_e,.0,max_e);
	TH1F * cosNoTrack = new TH1F("cosNoTrack", "tracks", bin_e,.0,max_e);
	TH1F * cosBtag = new TH1F("cosBtag", "tracks", bin_e,.0,max_e);
	cosGoodTracks->SetLineColor(kRed);
	cosGoodTracks->SetLineWidth(3);
	cosBtag->SetLineColor(kOrange);
	cosBtag->SetLineWidth(3);
	cosNoVTX->SetLineColor(kBlue);
	cosNoVTX->SetLineWidth(3);
	cosNoTrack->SetLineColor(kBlack);
	cosNoTrack->SetLineWidth(3);
	//cosLowtr->SetLineColor(kMagenta);
	//cosLowtr->SetLineWidth(3);
	cosNoPFO->SetLineColor(kGreen);
	cosNoPFO->SetLineWidth(3);
	//tree->Draw("costhetaMissed >> cosGoodTracks","momentumMissed > 1.0 && offsetMissed > 3*sqrt(0.005*0.005+0.01*0.01/momentumMissed/momentumMissed)");
	//tree->Draw("abs(costhetaMissed) >> cosGoodTracks","isrecoMissed > 0 && (vtxHitsMissed > 0 || ftdHitsMissed > 0 ) && (btagMissed > 0.8)");
	tree->Draw("abs(costhetaMissed) >> cosGoodTracks","isrecoMissed > 0 && (vtxHitsMissed > 0 || ftdHitsMissed > 0 )");
	//tree->Draw("costhetaMissed >> cosLowtr","momentumMissed < 1.0 && offsetMissed > 0.015");
	tree->Draw("abs(costhetaMissed) >> cosNoPFO","isrecoMissed == 0 && hastrackMissed == 1");
	tree->Draw("abs(costhetaMissed) >> cosNoTrack","hastrackMissed == 0");
	tree->Draw("abs(costhetaMissed) >> cosNoVTX"," vtxHitsMissed == 0 && ftdHitsMissed == 0 && isrecoMissed == 1");
	//tree->Draw("abs(costhetaMissed) >> cosBtag"," (vtxHitsMissed > 0 || ftdHitsMissed > 0) && isrecoMissed == 1 && btagMissed < 0.8");
	tree->Draw("abs(costhetaMissed) >> cosBtag"," (vtxHitsMissed > 0 || ftdHitsMissed > 0) && isrecoMissed == 1 && (btagMissed < 0.8)");
	std::cout << "Vertex total: " << cosNoTrack->Integral()+cosNoVTX->Integral()+cosNoPFO->Integral()+cosGoodTracks->Integral()
		  << " no track: " << cosNoTrack->Integral()
		  << " no vxd hits: " << cosNoVTX->Integral()
		  << " no PFO: " << cosNoPFO->Integral()
		  << " recoverable: " <<  cosGoodTracks->Integral()// +cosNoPFO->Integral()
		  << " \n";
	cosGoodTracks->Scale(1./reconumber);
	cosBtag->Scale(1./reconumber);
	cosNoVTX->Scale(1./reconumber);
	cosNoTrack->Scale(1./reconumber);
	cosNoPFO->Scale(1./reconumber);
	THStack * stack = new THStack("stack2","LSOT-VTX tracks");
	//stack->Add(cosLowtr);
	stack->Add(cosNoTrack);
	stack->Add(cosNoVTX);
	stack->Add(cosNoPFO);
	//stack->Add(cosBtag);
	stack->Add(cosGoodTracks);
	stack->Draw();
	TLegend *legendMean2 = new TLegend(0.13,0.6,0.63,0.85,NULL,"brNDC");
        legendMean2->SetFillColor(kWhite);
        legendMean2->SetBorderSize(0);
        legendMean2->AddEntry(cosGoodTracks,"Has hits in VXD or FTD","f");
        //legendMean2->AddEntry(cosBtag,"Low d_{IP} or low p_{t}","f");
        legendMean2->AddEntry(cosNoPFO,"Nonreconstructed PFO","f");
        legendMean2->AddEntry(cosNoVTX,"No hits in VXD and FTD","f");
        legendMean2->AddEntry(cosNoTrack,"No tracking information","f");
	legendMean2->Draw();
	stack2->GetXaxis()->SetTitle("|cos#theta|");
	gPad->Modified();
	std::cout << "Novertex total: " << cosOne->Integral()+cosOtherLowDist->Integral()+cosOtherHigh->Integral()
		  << " one track: " << cosOne->Integral()
		  << " others: " << cosOtherLowDist->Integral()+cosOtherHigh->Integral()
		  << " \n";
	//tree->Draw("costhetaMissed >> cosAll","","same");
}
