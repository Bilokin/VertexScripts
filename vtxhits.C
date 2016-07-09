
#define MAXN  1000
#include <iostream>
using std::cout;

void vtxhits(){
	TFile * file = TFile::Open("RecoTest.root");
	int bin_e = 200;
	float max_e =3.14;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * vtxTotal = new TH1F("vtxTotal", ";#phi", bin_e,0.0,max_e);
	TH1F * vtx4 = new TH1F("vtx4", "", bin_e,0.0,max_e);
	TH1F * vtx6 = new TH1F("vtx6", "", bin_e,0.0,max_e);
	TH1F * vtxTotaloff = new TH1F("vtxTotaloff", ";#phi", bin_e,0.0,max_e);
	TH1F * vtx4off = new TH1F("vtx4off", ";offset [mm]", bin_e,0.0,max_e);
	TH1F * vtx6off = new TH1F("vtx6off", "", bin_e,0.0,max_e);
	//TH1F * vtx09 = new TH1F("vtx09", "", bin_e,0.0,max_e);
	TTree * tree =MissedTracks;
	TaggedVertices->Project("vtxTotal","phiOfParticles", "phiOfParticles > -1 && abs(costhetaOfParticles) < 0.9" );
	TaggedVertices->Project("vtx4","phiOfParticles", "phiOfParticles > -1 && abs(costhetaOfParticles) < 0.9 && vtxHitsOfParticles==4" );
	TaggedVertices->Project("vtx6","phiOfParticles", "phiOfParticles > -1 && abs(costhetaOfParticles) < 0.9 && vtxHitsOfParticles==6" );
	//
	//TaggedVertices->Project("vtx09","vtxHitsOfParticles", "abs(costhetaOfParticles) < 0.95 && abs(costhetaOfParticles) > 0.9" );
	//tree->Project("vtxTotal","distanceIPMissed * sqrt( 1 - costhetaMissed*costhetaMissed)", "abs(costhetaMissed) < .72 && isrecoMissed > -1 && hastrackMissed == 1 && vtxHitsMissed == 6");
	//tree->Project("vtxTotald","distanceIPMissed * sqrt( 1 - costhetaMissed*costhetaMissed)", " abs(costhetaMissed) < 0.72 && isrecoMissed > -1 && hastrackMissed == 1 && vtxHitsMissed  == 0");
	vtxTotal->SetLineWidth(3);
	vtxTotal->SetLineColor(kGray);
	vtxTotal->SetMinimum(0);
	vtxTotal->SetStats(0);
	vtxTotal->Draw("");
	vtx4->SetLineWidth(3);
	vtx4->SetLineColor(kGreen);
	vtx4->Draw("same");
	vtx6->SetLineWidth(3);
	vtx6->SetLineColor(kBlue);
	vtx6->Draw("same");
	TLegend *legendMean2 = new TLegend(0.25,0.7,0.75,0.85,NULL,"brNDC");
        legendMean2->SetFillColor(kWhite);
        legendMean2->SetBorderSize(0);
        legendMean2->AddEntry(vtxTotal,"All particles","f");
        legendMean2->AddEntry(vtx6,"N_{VXD} = 6","f");
        legendMean2->AddEntry(vtx4,"N_{VXD} = 4","f");
	legendMean2->Draw();
	TCanvas * c2 = new TCanvas("c2", "Data-MC",0,0,500,500);
	TaggedVertices->Project("vtxTotaloff","offsetOfParticles", "offsetOfParticles > -1 && abs(costhetaOfParticles) < 0.9 && distanceIP < 16 && momentumOfParticles > 1.0" );
	TaggedVertices->Project("vtx4off","offsetOfParticles", "offsetOfParticles > -1 && abs(costhetaOfParticles) < 0.9 && vtxHitsOfParticles==4  && distanceIP < 16 && momentumOfParticles > 1.0" );
	TaggedVertices->Project("vtx6off","offsetOfParticles", "offsetOfParticles > -1 && abs(costhetaOfParticles) < 0.9 && vtxHitsOfParticles==6  && distanceIP < 16 && momentumOfParticles > 1.0" );
	makePretty(vtxTotaloff, kGray);
	makePretty(vtx4off, kGreen);
	makePretty(vtx6off, kBlue);
	vtx4off->Divide(vtxTotaloff);
	vtx6off->Divide(vtxTotaloff);
	//vtxTotaloff->Draw("");
	vtx4off->Draw("same");
	vtx6off->Draw("same");
	TLegend *legendMean2 = new TLegend(0.25,0.7,0.55,0.8,NULL,"brNDC");
        legendMean2->SetFillColor(kWhite);
        legendMean2->SetBorderSize(0);
 //       legendMean2->AddEntry(vtxTotal,"All particles","f");
        legendMean2->AddEntry(vtx6off,"N_{VXD} = 6","f");
        legendMean2->AddEntry(vtx4off,"N_{VXD} = 4","f");
	legendMean2->Draw();
	//vtx09->Draw("same");
	//stackp->Add(vtxTotald);
	//stackp->Draw();

}
void makePretty(TH1 * vtxTotal, int color)
{
	vtxTotal->SetLineWidth(3);
	vtxTotal->SetLineColor(color);
	vtxTotal->SetMinimum(0);
	vtxTotal->SetStats(0);
}
