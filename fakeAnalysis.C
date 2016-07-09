void fakeAnalysis(string filename = "VertexRestorer.root")
{
	//TFile * file1 = TFile::Open("TrashMCTest.root");
	//TTree * mctree = Stats;
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,500);
	c1->Divide(2,1);
	//c1->Divide(2,1);
	TFile * file2 = TFile::Open(filename.c_str());
	TTree * normaltree = Stats;
	int bins = 50;
	float high = 50;
	float low = 0.;


	
	TH1F * missed = new TH1F("missed", "; z_{0}/#sigma_{z_{0}}", bins, low, high);
	TH1F * fake = new TH1F("fake", "Angle", bins, low, high);
	TH1F * missedcos = new TH1F("missedcos", "; |cos#theta|", bins, low, 1.0);
	TH1F * fakecos = new TH1F("fakecos", "Angle", bins, low, 1.0);
	//gPad->SetGridx();
	//gPad->SetGridy();
	//c1->cd(1);
	makePretty(missed, false);
	makePretty(fake, true);
	makePretty(missedcos, false);
	makePretty(fakecos, true);
	c1->cd(1);
	//recotree->SetMarkerColor(kGray);
	//normaltree->Draw("fakeAngle / fakeObs >> fake","","samee");
	//normaltree->Draw("fakeObs >> fake","fakeMomentum > 10","e");
	//normaltree->Draw("abs(fakeCostheta) >> fake","fakeVtxHits  < 3","samee");
	normaltree->Draw("missedAngle >> missed", "missedMomentum > 0.0","");
	normaltree->Draw("fakeAngle >> fake","fakeMomentum > 0.0","samee");
	normaltree->Draw("missedZ0Deviation >> missed", "missedMomentum > 0.0","");
	normaltree->Draw("fakeZ0Deviation >> fake","fakeMomentum > 0.0","samee");
	//normaltree->Draw("missedAngle / missedObs >> missed","");
	//normaltree->Draw("missedObs >> missed","missedMomentum > 10", "same");
	//normaltree->Draw("abs(missedCostheta) >> missed","missedVtxHits < 3");
	//missed->GetXaxis()->SetTitle("#alpha");
	TLegend *legendMean = new TLegend(0.57,0.7,0.85,0.85,NULL,"brNDC");
        legendMean->SetFillColor(kWhite);
        legendMean->SetBorderSize(0);
        legendMean->AddEntry(missed,"recovered","fp");
        legendMean->AddEntry(fake,"fake","fp");
	legendMean->Draw();
	gPad->Modified();
	std::cout << "Recovered: " << missed->GetEntries() 
		  << " fake: " << fake->GetEntries()
		  << " purity: " << (float) missed->GetEntries() / (float)( missed->GetEntries() + fake->GetEntries())*100.
		  << "%\n";
	/*c1->cd(2);
	normaltree->Draw("costhetaOfParticles >> norcos", "costhetaOfParticles > -1.0");
	miscos->SetMarkerStyle(20);
	miscos->SetMarkerSize(0.4);
	norcos->GetXaxis()->SetTitle("cos#theta_{prongs}");
	missedtree->Draw("costhetaMissed >> miscos","","samee");
	gPad->Modified();*/
	c1->cd(2);
	normaltree->Draw("abs(missedCostheta) >> missedcos", "missedMomentum > 0.0","");
	normaltree->Draw("abs(fakeCostheta) >> fakecos","fakeMomentum > 0.0","samee");
	legendMean->Draw();
}
void makePretty(TH1F * missed, bool fake)
{
	missed->SetMinimum(0);
	missed->SetStats(0);
	if (fake) 
	{
		missed->SetMarkerStyle(21);
		missed->SetMarkerColor(kRed);
		missed->SetMarkerSize(1.0);
	}
	else 
	{
		missed->SetLineColor(kBlue);
		missed->SetLineWidth(2);
	}
}
