#define MAXN  1000
#include <iostream>
using std::cout;

void nrecngen(){
	int _vertex = 0;
	
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,500);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadColor(kWhite);
	c1->Divide(2,1);
	int nbins = 7;
	int maxd = nbins;
	TH2F * probhist = new TH2F("Pw","P()",nbins,0,maxd ,nbins, 0, maxd );
	TH2F * probhist_non = new TH2F("Pwo","P()",nbins,0,maxd , nbins,0, maxd );
	TH1F * diff = new TH1F("Diff","Difference",nbins,0,maxd);
	TH1F * diff2 = new TH1F("Diff2","Difference filtered",nbins,0,maxd);
	diff->Sumw2();
	diff2->Sumw2();
	TChain* T3 = new TChain("Stats1");
	T3->Add("TrashRecoTest.root");
	TChain* T2 = new TChain("Stats");
	T2->Add("TrashMCTest.root");

	int _bnumber = 0;
	int _bbarnumber = 0;
	int _btotalnumber = 0;
	int _bbartotalnumber = 0;
	int _tag = 0;
	int _brecnumber = 0;
	int _bbarrecnumber = 0;
	float _bdistance = 0.0;
	float _bbardistance = 0.0;
	
	T3->SetBranchAddress("bnumber1", &_brecnumber);
	T3->SetBranchAddress("bbarnumber1", &_bbarrecnumber);

	T2->SetBranchAddress("btotalnumber", &_btotalnumber);
	T2->SetBranchAddress("bbartotalnumber", &_bbartotalnumber);
	T2->SetBranchAddress("bnumber", &_bnumber);
	T2->SetBranchAddress("bbarnumber", &_bbarnumber);
	T2->SetBranchAddress("bIPdistance", &_bdistance);
	T2->SetBranchAddress("bbarIPdistance", &_bbardistance);

	T2->SetBranchAddress("tag", &_tag);

	int mTotalNumberOfEvents = T2->GetEntries();
	
	cout << "mTotalNumberOfEvents: " << mTotalNumberOfEvents << '\n';
	int counter = 0;
	int num = 0;
	for (unsigned int i = 0; i < mTotalNumberOfEvents; i += 1)
	{
		T2->GetEntry(i);
		T3->GetEntry(i);
		std::cout << "i: " << i
			  << " B mc: " << _btotalnumber
			  << " B rec: " <<  _brecnumber
			  << " Bbar mc: " << _bbartotalnumber
			  << " Bbar rec: " << _bbarrecnumber
			  << std::endl;
		if (_btotalnumber > 0  && _brecnumber > 0) 
		{
			diff->Fill(_btotalnumber - _brecnumber);
		}
		if (_bbartotalnumber > 0 && _bbarrecnumber > 0) 
		{
			diff->Fill(_bbartotalnumber - _bbarrecnumber);
		}
		if (_btotalnumber > 0  && _brecnumber > 0 && _bnumber > 1 && _bdistance > 0.0 && _btotalnumber < 7) 
		{
			diff2->Fill(_btotalnumber - _brecnumber);
		}
		if (_bbartotalnumber > 0 && _bbarrecnumber > 0 && _bbarnumber > 1 && _bbardistance > 0.0 && _bbartotalnumber < 7) 
		{
			diff2->Fill(_bbartotalnumber - _bbarrecnumber);
		}
	}
	
//	probhist_non->GetXaxis()->SetTitle("N_{gen}");
//	probhist->GetXaxis()->SetTitle("N_{gen}");
//	probhist_non->GetYaxis()->SetTitle("N_{rec}");
//	probhist->GetYaxis()->SetTitle("N_{rec}");
	gStyle->SetPalette(1);
	c1->cd(1);
	gPad->SetGrid();
	diff->Draw("p");
	c1->cd(2);
	gPad->SetGrid();
	diff2->Draw("p");

}
