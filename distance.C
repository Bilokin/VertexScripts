#define MAXN  10000
#include <iostream>

distance(int count){
	
	float _zvertex[MAXN];
	float _xvertex[MAXN];
	float _yvertex[MAXN];

	float _xendpoint[MAXN];
	float _yendpoint[MAXN];
	float _zendpoint[MAXN];

	float _energy[MAXN];
	float _distance[MAXN];
	float _zmomentum[MAXN];
	int _charge[MAXN];
	int _nMCparticles;

	gStyle->SetCanvasPreferGL(kTRUE);
	TCanvas * c1 = new TCanvas("mc", "MC",0,0,1000,500);
	c1->Divide(2,1);
	TH1F * Energy = new TH1F("Energy","ener", 20,0,11);
	TH1F * Distance = new TH1F("Distance","dist", 100,50,200);
	TChain* T = new TChain("MCParticles");
	T->Add("Test.root");
	int mTotalNumberOfEvents = T->GetEntries();
	T->SetBranchAddress("energy", _energy);
	T->SetBranchAddress("distance", _distance);

	T->SetBranchAddress("endX", _xendpoint);
	T->SetBranchAddress("endY", _yendpoint);
	T->SetBranchAddress("endZ", _zendpoint);

	T->SetBranchAddress("startX", _xvertex);
	T->SetBranchAddress("startY", _yvertex);
	T->SetBranchAddress("startZ", _zvertex);
	T->SetBranchAddress("zmomentum", _zmomentum);
	T->SetBranchAddress("charge", _charge);
	T->SetBranchAddress("nMCparticles", &_nMCparticles);
	cout << "mTotalNumberOfEvents: " << mTotalNumberOfEvents << '\n';
	//for (unsigned int i = 0; i < mTotalNumberOfEvents; i++)
	{
		T->GetEntry(count);
		for (int j = 0; j < _nMCparticles; j++) 
		{
			//main cuts
			if (_charge[j] != 0 && 
			    _zmomentum[j] > 0.0 && 
			    _zvertex[j] > 1300.0 && 
			    _zvertex[j] < 1500.0 && 
			    _distance[j]>30.0 && 
			    _energy[j] > 0.1) 
			{
			 	//cuts on collinear particles
				if (1) 
			 	{
			 			
			 	}
				Energy->Fill(_energy[j]);
				Distance->Fill(_distance[j]);
			}
		}
	}
	c1->cd(1);
	Distance->Draw();
	c1->cd(2);
	Energy->Draw();
}
