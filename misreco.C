#define MAXN  1000
#include <iostream>
using std::cout;

void misreco(){
	int _ntrack = 0;
	int nbins = 7;
	int maxd = nbins;
	TH2F * misshist = new TH2F("Pw","P()",nbins,0,maxd ,nbins, 0, maxd );
	TChain* T2 = new TChain("MisReco");
	T2->Add("TrashMCTest.root");
	T2->SetBranchAddress("misreconumber", &_ntrack);

	int mTotalNumberOfEvents = T2->GetEntries();	
	for (int i = 0; i < mTotalNumberOfEvents; i++) 
	{
		T2->GetEntry(i);

	}

}
