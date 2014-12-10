#include <unistd.h>
#include <iostream>
float getDistance(float * v1, float * v2, int number)
{
	float diff;
	for (int i = 0; i < 3; i++) 
	{
		diff += (v1[number][i] - v2[number][i]) * (v1[number][i] - v2[number][i]);
	}

	return sqrt(diff);
}
void distEfficiency()
{
	//gStyle->SetCanvasPreferGL(kTRUE);
	int bin_e = 20;
	int max_e = 30;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * distmc = new TH1F("distmc", "E(Ntracks)", bin_e,0,max_e);
	TH1F * distreco = new TH1F("distreco", "tracks", bin_e,0,max_e);
	distreco->Sumw2();
	distmc->Sumw2();
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
	
	MC->SetBranchAddress("bdistance", &_bdistance);
	MC->SetBranchAddress("bbardistance", &_bbardistance);

	int _numberOfTagged = 0;
	int _PDGreco[MAXV];
	

	RECO->SetBranchAddress("numberOfTagged", _numberOfTagged);
	RECO->SetBranchAddress("PDGreco", _PDGreco);
	int mTotalNumberOfEvents1 = MC->GetEntries();
	for (int k = 0; k < mTotalNumberOfEvents1; k++)
	{
	        RECO->GetEntry(k);
	        MC->GetEntry(k);
		if (_tag == 0) 
		{
			continue;
		}
		vector<int> bs;
		vector<int> bbars;
		for (int i = 0; i < _numberOfTagged; i++) 
		{
			if (_PDGreco[i] == 5) 
			{
				bs.push_back(i);
			}
			else 
			{
				bbars.push_back(i);
			}
		}
		distmc->Fill(_bdistance);
		distmc->Fill(_bbardistance);
		if (bs.size() == 2) 
		{
			distreco->Fill(_bdistance);
		}
		if (bbars.size() == 2) 
		{
			distreco->Fill(_bbardistance);
		}
	}
	gStyle->SetPalette(1);
	distmc->Draw();
	if (TEfficiency::CheckConsistency(*distmc, *distreco)) 
	{
		TEfficiency * eff = new TEfficiency(*distmc, *distreco);
	}
}
