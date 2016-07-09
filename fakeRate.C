
#include "../vertex/ratioplot.C"
void fakeRate(string recofile = "RecoTest.root")
{
	int bin_e = 50;
	float max_e = 1;
	float min_e = 0;
	TFile *_file0 = TFile::Open(recofile.c_str());
	TH1F * allTracks = new TH1F("allTracks", "Reco;cos#theta", bin_e,min_e,max_e);
	TH1F * fakeTracks = new TH1F("fakeTracks", "Reco;cos#theta", bin_e,min_e,max_e);
	makePretty(allTracks,kBlue);
	makePretty(fakeTracks,kRed);
	TaggedVertices->Draw("abs(costhetaOfParticles) >> allTracks", "abs(costhetaOfParticles) < 2" );
	TaggedVertices->Draw("abs(costhetaOfParticles) >> fakeTracks", "abs(costhetaOfParticles) < 2 && isProngOfParticles  == 0" ,"same");
	ratioplot(fakeTracks, allTracks, c1);
}
void makePretty(TH1 * vtxTotal, int color)
{
	vtxTotal->SetLineWidth(3);
	vtxTotal->SetLineColor(color);
	vtxTotal->SetMinimum(0);
	vtxTotal->SetStats(0);
}
