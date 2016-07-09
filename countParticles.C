#include <unistd.h>
#include <iostream>
#define MAXV 15
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
	TH1F * kaons = new TH1F("kaons","N",5,0,5);
	distreco->Sumw2();
	distmc->Sumw2();
	TChain* MC = new TChain("Stats");
	MC->Add("MCTest.root");
	TChain* RECO = new TChain("TaggedVertices");
	RECO->Add("RecoTest.root");
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
	float _bdistance = 0.0;
	float _bbardistance = 0.0;

	MC->SetBranchAddress("bdistance", &_bdistance);
	MC->SetBranchAddress("bbardistance", &_bbardistance);

	int _numberOfTagged = 0;
	int _PDGreco[MAXV];
	int _nparticles[MAXV];
	int _type[MAXV][MAXV];

	RECO->SetBranchAddress("numberOfTagged", &_numberOfTagged);
	RECO->SetBranchAddress("numberOfParticles", &_nparticles);
	RECO->SetBranchAddress("trueTypeOfParticles", &_type);
	RECO->SetBranchAddress("PDG", _PDGreco);
	int mTotalNumberOfEvents1 = MC->GetEntries();
	int totalnumber = 0;
	int totalb = 0;
	int kaonnumber = 0;
	int pionnumber = 0;
	for (int k = 0; k < mTotalNumberOfEvents1; k++)
	{
	        RECO->GetEntry(k);
	        MC->GetEntry(k);
		int bvtxnumber = 0;
		int bbarvtxnumber = 0;
		for (int i = 0; i < _numberOfTagged; i++) 
		{
			int knumber = 0;
			if (_nparticles[i] < 1 ) 
			{
				continue;
			}
			if (_PDGreco[i] > 0) 
			{
				bvtxnumber ++;
			}
			if (_PDGreco[i] < 0) 
			{
				bbarvtxnumber ++;
			}
			for (int j = 0; j < _nparticles[i]; j++) 
			{
				if (abs(_type[i][j]) == 321) 
				{
					knumber++;
				}
				if (abs(_type[i][j]) == 211) 
				{
					pionnumber++;
				}
				totalnumber++;
			}
			kaonnumber += knumber;
			kaons->Fill(knumber);
		}
		if (bvtxnumber) 
		{
			totalb++;
		}
		if (bbarvtxnumber) 
		{
			totalb++;
		}
	}
	cout << "Nparticles: " << totalb << " Nkaons: " << kaonnumber << " (" << (float)kaonnumber/totalb*100 << "%)\n" ;
	cout << "\tNpions: " << pionnumber << " (" << (float)pionnumber/totalb*100 << "%)\n" ;
	cout << "\tNpions: " << totalnumber << " (" << (float)totalnumber/totalb*100 << "%)\n" ;
	kaons->Scale(1./totalb);
	kaons->Draw("htext");
}
