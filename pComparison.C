void pComparison()
{
	//TFile * file1 = TFile::Open("TrashMCTest.root");
	//TTree * mctree = Stats;
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,500);
	c1->Divide(2,1);
	TFile * file2 = TFile::Open("TrashRecoTest.root");
	TTree * normaltree = TaggedVertices;
	TTree * missedtree = MissedTracks;
	int bins = 50;
	int high = 30;
	TH1F * missed = new TH1F("missed", "missed hist", bins, 0, high);
	TH1F * normal = new TH1F("normal", "Momentum", bins, 0, high);
	TH1F * miscos = new TH1F("miscos", "missed cos hist", bins, -1.0, 1.0);
	TH1F * norcos = new TH1F("norcos", "cos#theta", bins, -1.0, 1.0);
	//gPad->SetGridx();
	//gPad->SetGridy();
	c1->cd(1);
	normaltree->Draw("momentumOfParticles >> normal","momentumOfParticles > 0.0");
	missed->SetMarkerStyle(20);
	missed->SetMarkerSize(0.4);
	//recotree->SetMarkerColor(kGray);
	normal->GetXaxis()->SetTitle("|p|_{prongs}, GeV");
	missedtree->Draw("momentumMissed >> missed","","samee");
	gPad->Modified();
	c1->cd(2);
	normaltree->Draw("costhetaOfParticles >> norcos", "costhetaOfParticles > -1.0");
	miscos->SetMarkerStyle(20);
	miscos->SetMarkerSize(0.4);
	norcos->GetXaxis()->SetTitle("cos#theta_{prongs}");
	missedtree->Draw("costhetaMissed >> miscos","","samee");
	gPad->Modified();
}
