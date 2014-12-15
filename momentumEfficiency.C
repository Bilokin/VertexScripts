#include <unistd.h>
#include <iostream>
#define MAXV 8
void momentumEfficiency()
{
	//gStyle->SetCanvasPreferGL(kTRUE);
	int bin_e = 20;
	int max_e = 165;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * momentummc = new TH1F("momentummc", "P_{b}^{mc}", bin_e,0,max_e);
	TH1F * momentumreco = new TH1F("momentumreco", "P_{b}^{reco}", bin_e,0,max_e);
	momentumreco->Sumw2();
	momentummc->Sumw2();
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
	float _bmomentum = 0.0;
	float _bbarmomentum = 0.0;

	MC->SetBranchAddress("bmomentum", &_bmomentum);
	MC->SetBranchAddress("bbarmomentum", &_bbarmomentum);

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
		vector<int> bs;
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
		momentummc->Fill(_bmomentum);
		momentummc->Fill(_bbarmomentum);
		if (bs.size() > 1) 
		{
			momentumreco->Fill(_bmomentum);
		}
		if (bbars.size() > 1) 
		{
			momentumreco->Fill(_bbarmomentum);
		}
	}
	gStyle->SetPalette(1);
	//momentummc->Draw();
	momentumreco->Draw("psame");
	if (TEfficiency::CheckConsistency(*momentumreco, *momentummc)) 
	{
		TEfficiency * eff = new TEfficiency(*momentumreco, *momentummc);
	}
	eff->Draw("AP");
}
