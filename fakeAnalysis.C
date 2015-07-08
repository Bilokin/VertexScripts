void fakeAnalysis()
{
	//TFile * file1 = TFile::Open("TrashMCTest.root");
	//TTree * mctree = Stats;
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,500,500);
	//c1->Divide(2,1);
	TFile * file2 = TFile::Open("VertexRestorer.root");
	TTree * normaltree = Stats;
	int bins = 30;
	float high = .125;
	float low = 0.;


	
	TH1F * missed = new TH1F("missed", "missed hist", bins, low, high);
	TH1F * fake = new TH1F("fake", "Angle", bins, low, high);
	//gPad->SetGridx();
	//gPad->SetGridy();
	//c1->cd(1);
	missed->SetLineColor(kBlue);
	missed->SetLineWidth(2);
	normaltree->Draw("missedAngle >> missed","");
//	normaltree->Draw("missedObs >> missed","");
	fake->SetMarkerStyle(21);
	fake->SetMarkerColor(kRed);
	fake->SetMarkerSize(1.0);
	//recotree->SetMarkerColor(kGray);
	missed->GetXaxis()->SetTitle("#alpha");
//	normaltree->Draw("fakeObs >> fake","","samee");
	normaltree->Draw("fakeAngle >> fake","","samee");
	TLegend *legendMean = new TLegend(0.17,0.7,0.5,0.92,NULL,"brNDC");
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
}
