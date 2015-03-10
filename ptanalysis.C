void ptanalysis()
{
	//TDirectory *where = gDirectory;
	TFile * file = TFile::Open("TrashMCTest.root");
	TTree * mctree = Stats;
	int bins = 100;
	int high = 10;
	TH1F * charged = new TH1F("charged", "charged hist", bins, 0, high);
	TH1F * neutral = new TH1F("neutral", "neutral hist", bins, 0, high);
	//where->cd();
	mctree->Project("charged", "bptmiss", "bcharge == -1");
	mctree->Project("neutral", "bptmiss", "bcharge == 0");
	neutral->SetFillColor(kYellow);
	neutral->GetXaxis()->SetTitle("p_{Tmiss}, GeV");
	charged->GetXaxis()->SetTitle("p_{Tmiss}, GeV");
	charged->SetFillColor(kBlue);
	THStack * stack = new THStack("Transverse" , "p_{Tmiss}");
	stack->Add(charged);
	stack->Add(neutral);
	stack->Draw();
	stack->GetXaxis()->SetTitle("p_{Tmiss}, GeV");
	gPad->Modified();
}
