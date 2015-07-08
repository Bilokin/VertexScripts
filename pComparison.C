void pComparison()
{
	//TFile * file1 = TFile::Open("TrashMCTest.root");
	//TTree * mctree = Stats;
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,500);
	c1->Divide(2,1);
	TFile * file2 = TFile::Open("TrashRecoTest.root");
	TTree * normaltree = TaggedVertices;
	TTree * missedtree = MissedTracks;
	TTree * missedvertextree = MissedVertex;
	int bins = 50;
	int high = 30;
	TH1F * missed = new TH1F("missed", "missed hist", bins, 0, high);
	TH1F * normal = new TH1F("normal", "Momentum", bins, 0, high);
	TH1F * miscos = new TH1F("miscos", "missed cos hist", bins, -1.0, 1.0);
	TH1F * norcos = new TH1F("norcos", "cos#theta", bins, -1.0, 1.0);
	//gPad->SetGridx();
	//gPad->SetGridy();
	c1->cd(1);
	normal->SetFillColor(kGray);
	normal->SetLineColor(kGray+2);
	normal->SetLineWidth(3);
	//normaltree->Draw("momentumOfParticles >> normal","momentumOfParticles > 0.0");
	normaltree->Draw("ptOfParticles >> normal","momentumOfParticles > 0.0");
	//missed->SetMarkerStyle(20);
	//missed->SetMarkerSize(0.8);
	missed->SetLineColor(kRed);
	missed->SetLineWidth(3);

	//recotree->SetMarkerColor(kGray);
	normal->GetXaxis()->SetTitle("|p|_{prongs}, GeV");
	norcos->SetMinimum(0);
	missedtree->Draw("momentumMissed >> missed","","samee");
//	missedtree->Draw("ptMissed >> missed","","same");
	missedvertextree->Draw("momentumOfParticlesVtx >> +missed", "momentumOfParticlesVtx > -1.0", "samee");
//	missedvertextree->Draw("ptOfParticlesVtx >> +missed", "ptOfParticlesVtx > -1.0", "same");
	TLegend *legendMean = new TLegend(0.17,0.7,0.5,0.92,NULL,"brNDC");
        legendMean->SetFillColor(kWhite);
        legendMean->SetBorderSize(0);
        legendMean->AddEntry(normal,"reconstructed SOT-Tracks","fp");
        legendMean->AddEntry(missed,"LSOT-Tracks","fp");
	legendMean->Draw();
	gPad->Modified();
	c1->cd(2);
	norcos->SetFillColor(kGray);
	norcos->SetLineColor(kGray+2);
	norcos->SetLineWidth(3);
	normaltree->Draw("costhetaOfParticles >> norcos", "costhetaOfParticles > -1.0");
	//miscos->SetMarkerStyle(20);
	//miscos->SetMarkerSize(0.8);
	miscos->SetLineColor(kRed);
	miscos->SetLineWidth(3);

	norcos->GetXaxis()->SetTitle("cos#theta_{prongs}");
	missedvertextree->Draw("costhetaOfParticlesVtx >> +miscos", "costhetaOfParticlesVtx > -1.0", "same");
	missedtree->Draw("costhetaMissed >> +miscos","","same");
	miscos->Draw("same");
	gPad->Modified();
}
