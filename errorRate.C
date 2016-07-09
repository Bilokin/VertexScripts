
void errorRate(string recofile = "RecoTest.root")
{
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,500,500);
	TFile * file2 = TFile::Open(recofile.c_str());
	int nbins = 100;
	TH1F * miscos = new TH1F("miscos", "missed cos hist", nbins, .0, 1.0);
	TH1F * vtxcos = new TH1F("vtxcos", "missed cos hist", nbins, .0, 1.0);
	TH1F * fakecos = new TH1F("fakecos", "missed cos hist", nbins, .0, 1.0);
	TTree * missedtree = MissedTracks;
	TTree * taggedtree = TaggedVertices;
	makePretty(miscos, kRed);
	makePretty(vtxcos, kGray);
	makePretty(fakecos, kBlack);
	taggedtree->Draw("abs(costhetaVtx) >> vtxcos","","same");
	taggedtree->Draw("abs(costhetaOfParticles) >> fakecos","abs(costhetaOfParticles) < 1 && isProngOfParticles == 0","same");
	missedtree->Draw("abs(costhetaMissed) >> miscos","","same");
	for (int i = 1; i < nbins+1; i++) 
	{
		float missedbin = miscos->GetBinContent(i);
		float fakebin = fakecos->GetBinContent(i);
		float taggedbin = vtxcos->GetBinContent(i);
		miscos->SetBinContent(i, missedbin/taggedbin);
		fakecos->SetBinContent(i, fakebin/taggedbin);
	}
	miscos->Draw();
	fakecos->Draw("same");
}
void makePretty(TH1 * vtxTotal, int color)
{
	vtxTotal->SetLineWidth(3);
	vtxTotal->SetLineColor(color);
	vtxTotal->SetMinimum(0);
	vtxTotal->SetStats(0);
}
