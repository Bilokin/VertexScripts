#include <unistd.h>
#include <iostream>
#define MAXV 8
void totalNoT()
{
	//gStyle->SetCanvasPreferGL(kTRUE);
	int bin_e = 14;
	int max_e = bin_e;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * numbermc = new TH1F("numbermc", "\#_sec", bin_e,0,max_e);
	TH1F * numberreco = new TH1F("numberreco", "P_{b}^{reco}", bin_e,0,max_e);
	numberreco->Sumw2();
	numbermc->Sumw2();
	TChain* MC = new TChain("Stats");
	MC->Add("TrashMCTest.root");
	TChain* RECO = new TChain("TaggedVertices");
	RECO->Add("TrashRecoTest.root");
	//T1->Add("~/Processors/Analysis/TestProcessor/build/test/Data_10_GeV/Test.root");
	/*int _numberOfVertexes = 0;
	int _tag = 0;
	const int MAXV = 8;
	float _coordinates[MAXV][3];
	int _PDG[MAXV];
	int _generation[MAXV];
	int _distance[MAXV];
	
	MC->SetBranchAddress("numberOfVertexes", &_numberOfVertexes);
	MC->SetBranchAddress("tag", &_tag);
	MC->SetBranchAddress("coordinates", _coordinates);
	MC->SetBranchAddress("distance", _distance);
	MC->SetBranchAddress("PDG", _PDG);
	MC->SetBranchAddress("generation", _generation);*/
	//MC->SetBranchAddress("coordinates", _coordinates);
	int _bnumber = 0;
	int _bbarnumber = 0;
	int _cnumber = 0;
	int _cbarnumber = 0;

	MC->SetBranchAddress("bnumber", &_bnumber);
	MC->SetBranchAddress("bbarnumber", &_bbarnumber);
	MC->SetBranchAddress("cnumber", &_cnumber);
	MC->SetBranchAddress("cbarnumber", &_cbarnumber);

	int _numberOfTagged = 0;
	int _PDGreco[MAXV];
	

	RECO->SetBranchAddress("numberOfTagged", &_numberOfTagged);
	RECO->SetBranchAddress("PDG", _PDGreco);
	int mTotalNumberOfEvents1 = MC->GetEntries();
	for (int k = 0; k < mTotalNumberOfEvents1; k++)
	{
	        RECO->GetEntry(k);
	        MC->GetEntry(k);
		/*if (_tag == 0) 
		{
			continue;
		}*/
		/*vector<int> bs;
		vector<int> bbars;
		std::cout << "N = " << _numberOfTagged << '\n';
		for (int i = 0; i < _numberOfTagged; i++) 
		{
			std::cout << "PDG = " << _PDGreco[i] << '\n';
			if (_PDGreco[i] == 5) 
			{
				bs.push_back(i);
			}
			else 
			{
				bbars.push_back(i);
			}
		}
		numbermc->Fill(_bmomentum);
		numbermc->Fill(_bbarmomentum);
		if (bs.size() > 1) 
		{
			numberreco->Fill(_bmomentum);
		}
		if (bbars.size() > 1) 
		{
			numberreco->Fill(_bbarmomentum);
		}*/
		if (_cbarnumber > -1 && _bbarnumber > -1) 
		{
			numbermc->Fill(_cbarnumber + _bbarnumber);
		}
		if (_cnumber > -1 && _bnumber > -1) 
		{
			numbermc->Fill(_cnumber + _bnumber);
		}
	}
	gStyle->SetPalette(1);
	//numbermc->SetMarkerStyle(20);
	//numbermc->SetMarkerColor(kBlack);
	//numbermc->SetMarkerSize(1);
	numbermc->SetFillColor(kYellow);
	numbermc->Draw();
}
