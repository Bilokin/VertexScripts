#define MAXN  30
#include <iostream>
using std::cout;

void tracks(){
	int _bnumber = 0;
	int _bbarnumber = 0;
	float _boffsettrack[MAXN];
	float _bbaroffsettrack[MAXN];
	float _betatrack[MAXN];
	float _bbaretatrack[MAXN];
	float _bptrack[MAXN];
	float _bbarptrack[MAXN];
	int _breconumber = 0;
	int _bbarreconumber = 0;
	float _bptmiss;
	float _bbarptmiss;
	float _bmomentum;
	float _bteta;
	float _bbarteta;
	float _bIPdistance;
	float _bprobmean;
	float _bchimean;

	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,500);
	c1->Divide(2,1);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadColor(kWhite);
	int nbin = 100;

	float maxteta = 3.14;
	float maxy = 50.0;
	float maxpt = 30;
	float maxp = 14;
	TH2F * good = new TH2F("good","Matched", nbin, 0, maxteta, nbin, 0, maxy );
	TH2F * lost = new TH2F("lost","Lost", nbin, 0, maxteta, nbin, 0, maxy );
	TH2F * lostpt = new TH2F("ptlost","Lostpt", nbin,0, maxpt, nbin, 0, maxp);
	TH2F * goodpt = new TH2F("ptgood","goodpt", nbin,0, maxpt, nbin, 0, maxp);
	goodpt->Sumw2();
	lostpt->Sumw2();
	TChain* T = new TChain("Tracks");
	T->Add("TrashMCTest.root");
	TChain* T1 = new TChain("Stats");
	T1->Add("TrashRecoTest.root");
	TChain* T2 = new TChain("Stats");
	T2->Add("TrashMCTest.root");

	int mTotalNumberOfEvents = T->GetEntries();
	T->SetBranchAddress("bnumber", &_bnumber);
	T->SetBranchAddress("bbarnumber", &_bbarnumber);
	T->SetBranchAddress("boffsettrack", _boffsettrack);
	T->SetBranchAddress("bbaroffsettrack", _bbaroffsettrack);
	T->SetBranchAddress("betatrack", _betatrack);
	T->SetBranchAddress("bbaretatrack", _bbaretatrack);
	T->SetBranchAddress("bptrack", _bptrack);

	T1->SetBranchAddress("bteta", &_bteta);
	T1->SetBranchAddress("bbarteta", &_bbarteta);
	T1->SetBranchAddress("bnumber", &_breconumber);
	T1->SetBranchAddress("bbarnumber", &_bbarreconumber);
	T1->SetBranchAddress("bptmiss", &_bptmiss);
	T1->SetBranchAddress("bbarptmiss", &_bbarptmiss);
	T1->SetBranchAddress("bIPdistance", &_bIPdistance);
	T1->SetBranchAddress("bprobmean", &_bprobmean);
	T1->SetBranchAddress("bchimean", &_bchimean);
	
	T1->SetBranchAddress("bmomentum", &_bmomentum);
	cout << "mTotalNumberOfEvents: " << mTotalNumberOfEvents << '\n';
	int counter = 0;
	int num = 0;
	for (unsigned int i = 0; i < mTotalNumberOfEvents; i += 1)
	{
		T->GetEntry(i);
		T1->GetEntry(i);
		T2->GetEntry(i);
		if (_bnumber < 1 || _bnumber > 15) 
		{
			continue;
		}
		if (_breconumber > 15) 
		{
			continue;
		}
		if (_bnumber == _breconumber) 
		{
			for (int j = 0; j < _bnumber; j++)
			{//_bIPdistance_bIPdistance
			//        good->Fill(_betatrack[j], _boffsettrack[j]);
			}
			goodpt->Fill(_bchimean, _breconumber);
			good->Fill(_bteta, _bmomentum);
		}
		else 
		{
			lostpt->Fill(_bchimean, _breconumber);
			lost->Fill(_bteta, _bmomentum);
			int filter = 0;
			for (int m = 0; m < _bnumber; m++) 
			{
				if (
				    _betatrack[m] < 0.3 
				    || _betatrack[m] > 2.9
				    || _bptrack[m] < 0.2
				    || _boffsettrack[m] < 0.01
				   ) 
				{
					filter++;
				}
			}
			if (filter > 0) 
			{
			//	continue;
			}
			for (int k = 0; k < _bnumber; k++) 
			{
			//	lost->Fill(_betatrack[k], _boffsettrack[k]);
			}
		}
	}
	c1->cd(1);
	TF1 *fa1 = new TF1("fa1","(x-1.57)*(x-1.57)*10+10",0,3.14);

	good->GetXaxis()->SetTitle("#theta");
	good->GetYaxis()->SetTitle("|p_{B}|");
	lost->GetXaxis()->SetTitle("#theta");
	lost->GetYaxis()->SetTitle("|p_{B}|");
	goodpt->GetXaxis()->SetTitle("|p_{B}|");
	goodpt->GetYaxis()->SetTitle("d_{IP-2vx}");
	lostpt->GetXaxis()->SetTitle("|p_{B}|");
	lostpt->GetYaxis()->SetTitle("d_{IP-2vx}");
	lost->SetMarkerColor(kRed);
	lost->SetMarkerSize(0.4);
	lost->SetMarkerStyle(20);
	good->SetMarkerSize(0.4);
	good->SetMarkerStyle(20);
	good->SetMarkerColor(kBlue);
	lost->Draw("same");
	good->Draw("same");
	gPad->SetGridy();
	gPad->SetGridx();
	fa1->Draw("same");
	c1->cd(2);
	lostpt->SetMarkerColor(kRed);
	lostpt->SetMarkerSize(0.4);
	lostpt->SetMarkerStyle(20);
	goodpt->SetMarkerSize(0.4);
	goodpt->SetMarkerStyle(20);
	goodpt->SetMarkerColor(kBlue);
	//lostpt->SetMarkerColor(kRed);
	//lostpt->SetMarkerStyle(20);
	lostpt->Draw("samep");
	goodpt->Draw("same");

}
