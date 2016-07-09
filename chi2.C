#include <unistd.h>
#include <iostream>
#define MAXV 8
void chi2()
{
	TFile * file2 = TFile::Open("VertexRestorer.root");
	//TTree * prime = Primaries;
	int bin_e = 30;
	float max_e =2.0;
	int vtxmax = 7;
	TH1F * chi2prime = new TH1F("chi2prime", "E(Ntracks)", bin_e,0.50,max_e);
	TH1F * vtxprime = new TH1F("vtxprime", "FTD hits;N_{hits}^{ftd}", 8,0.0,vtxmax);
	//prime->Draw("primeChi2 >> chi2prime","primeChi2 > 0", "samee");
	//prime->Draw("primeVtxHits >> vtxprime","primeChi2 > 0", "samee");
	//file2->Close();
	TFile * file = TFile::Open("TrashRecoTest.root");
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,1000,500);
	c1->Divide(2,1);
	TH1F * chi2all = new TH1F("chi2all", "Normalized #chi^{2};#chi^{2} / N_{df}", bin_e,0.50,max_e);
	TH1F * chi2miss = new TH1F("chi2miss", "E(Ntracks)", bin_e,0.50,max_e);
	TTree * tree = MissedTracks;
	chi2all->SetLineColor(kGray+2);
	chi2all->SetFillColor(kGray);
	chi2miss->SetLineColor(kRed);
	chi2all->SetLineWidth(3);
	chi2miss->SetLineWidth(3);
	tree->Project("chi2miss","chi2Missed", "chi2Missed > 0 && ptMissed > .00");
	TTree * ttree = TaggedVertices;
	ttree->Project("chi2all","chi2OfParticles", "chi2OfParticles > 0 && ptOfParticles > .0");
	c1->cd(1);
	//file2->cd();
	chi2prime->SetMarkerStyle(21);
	chi2prime->SetMarkerSize(1.0);
	chi2prime->SetMarkerColor(kRed+2);
	chi2all->DrawNormalized("");
	chi2miss->DrawNormalized("same");
	//chi2prime->DrawNormalized("samee");

	bin_e = 8;
	max_e = bin_e;
	TH1F * vtxall = new TH1F("vtxall", "FTD hits;N_{hits}^{vxd}", vtxmax,0.0,vtxmax);
	TH1F * vtxmiss = new TH1F("vtxmiss", ";N_{hits}^{ftd}", vtxmax,0.0,vtxmax);
	TH2F * miss = new TH2F("miss", "E(Ntracks)", 8,0,8,225,0,225 );
	tree->Project("vtxmiss","vtxHitsMissed", "vtxHitsMissed > -1 && ptMissed > .50");
	//tree->Project("vtxmiss","ftdHitsMissed", "ftdHitsMissed > -1 && ptMissed > .50 && abs(costhetaMissed) > 0.95 && abs(costhetaMissed) < 0.99");
	vtxall->SetLineColor(kGray+2);
	vtxall->SetFillColor(kGray);
	vtxall->SetLineWidth(3);
	vtxmiss->SetLineColor(kRed);
	vtxmiss->SetLineWidth(3);
	vtxprime->SetMarkerStyle(21);
	vtxprime->SetMarkerSize(1.0);
	vtxprime->SetMarkerColor(kRed+2);
	//ttree->Project("vtxall","ftdHitsOfParticles", "ftdHitsOfParticles > -1 && ptOfParticles > .50 && abs(costhetaOfParticles) > 0.95 && abs(costhetaOfParticles) < 0.99");
	ttree->Project("vtxall","vtxHitsOfParticles", "vtxHitsOfParticles > -1 && ptOfParticles > .50");
	tree->Project("miss","tpcHitsMissed:vtxHitsMissed","vtxHitsMissed > -1");
	c1->cd(2);
	//gPad->SetLogy();
	vtxprime->SetMinimum(1);
	//vtxprime->Draw("e");
	vtxall->Draw("same");
	vtxmiss->Draw("same");
	TLegend *legendMean = new TLegend(0.27,0.7,0.7,0.82,NULL,"brNDC");
        legendMean->SetFillColor(kWhite);
        legendMean->SetBorderSize(0);
        legendMean->AddEntry(vtxall,"reconstructed B-particles","fp");
        legendMean->AddEntry(vtxmiss,"Lost B-particles","fp");
        //legendMean->AddEntry(vtxprime,"primary tracks","fp");
	legendMean->Draw();
	gPad->Modified();
	//miss->Draw("colz");*/
}
