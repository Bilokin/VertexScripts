#define MAXN  1000
#include <iostream>
using std::cout;

void trackRecovery(){
	
	int _fake = 0;
	int _missed = 0;

	float _fakeDeviation[MAXN];
	float _missedDeviation[MAXN];
	
	float _fakeMomentum[MAXN];
	float _missedMomentum[MAXN];
	gStyle->SetPalette(1);
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,500);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadColor(kWhite);
	c1->Divide(2,1);
	int nbins = 30;
	int maxx = 30;
	int maxy = 20;
	TH2F * fakehist = new TH2F("fake","Fake",nbins,0,maxx,nbins, 0, maxy );
	TH2F * missedhist= new TH2F("missed","Missed",nbins,0,maxx, nbins,0, maxy );
	TChain* T = new TChain("Stats");
	T->Add("VertexRestorer.root");

	float _bdistance = 0.0;
	float _bbardistance = 0.0;

	T->SetBranchAddress("fakeDetected", &_fake);
	T->SetBranchAddress("missedDetected", &_missed);

	T->SetBranchAddress("missedMomentum", _missedMomentum);
	T->SetBranchAddress("missedDeviation", _missedDeviation);
	T->SetBranchAddress("fakeMomentum", _fakeMomentum);
	T->SetBranchAddress("fakeDeviation", _fakeDeviation);
	int mTotalNumberOfEvents = T->GetEntries();
	cout << "mTotalNumberOfEvents: " << mTotalNumberOfEvents << '\n';
	int counter = 0;
	int num = 0;
	for (unsigned int i = 0; i < mTotalNumberOfEvents; i += 1)
	{
		T->GetEntry(i);
		for (int j = 0; j < _fake; j++) 
		{
			fakehist->Fill(_fakeMomentum[j], _fakeDeviation[j]);
		}
		for (int k = 0; k < _missed; k++) 
		{
			missedhist->Fill(_missedMomentum[k], _missedDeviation[k]);
		}
	}
	
	missedhist->GetXaxis()->SetTitle("|p|,GeV");
	missedhist->GetYaxis()->SetTitle("#epsilon deviation");
	
	fakehist->GetXaxis()->SetTitle("|p|, GeV");
	fakehist->GetYaxis()->SetTitle("#epsilon deviation");
	
	c1->cd(1);
	TF1 * f = new TF1("f","2+15.0/(x+1.0/12.0)",0, 30);
	fakehist->Draw("colz");
	c1->cd(2);
	missedhist->Draw("colz");
	//f->Draw("same");
}
