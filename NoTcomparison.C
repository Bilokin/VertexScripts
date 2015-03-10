void NoTcomparison()
{
	TFile * file1 = TFile::Open("TrashMCTest.root");
	TTree * mctree = Stats;
	TFile * file2 = TFile::Open("TrashRecoTest.root");
	TTree * recotree = Stats;
	int bins = 14;
	int high = 14;
	TH1F * charged = new TH1F("charged", "charged hist", bins, 0, high);
	TH1F * neutral = new TH1F("neutral", "neutral hist", bins, 0, high);
	mctree->Draw("btotalnumber","");
	recotree->SetMarkerStyle(20);
	recotree->SetMarkerSize(0.4);
	//recotree->SetMarkerColor(kGray);
	htemp->GetXaxis()->SetTitle("N_{prongs}");
	recotree->Draw("bnumber","bnumber > 0","samee");
	gPad->Modified();
}
