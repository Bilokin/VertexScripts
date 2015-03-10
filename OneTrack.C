#include <unistd.h>
#include <iostream>
#define MAXV 8
void OneTrack()
{
	//gStyle->SetCanvasPreferGL(kTRUE);
	int bin_e = 30;
	int max_e = 2;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * distmc = new TH1F("distmc", "E(Ntracks)", bin_e,0,max_e);
	TH1F * distreco = new TH1F("distreco", "tracks", bin_e,0,max_e);
	TH2F * erf = new TH2F("distrecoEff", "tracks2", bin_e,0,max_e, bin_e, 0, 1.01);
	distreco->Sumw2();
	distmc->Sumw2();
	TChain* MC = new TChain("Stats");
	MC->Add("TrashMCTest.root");
	TChain* RECO = new TChain("Stats");
	RECO->Add("TrashRecoTest.root");
	float _bdistance = 0.0;
	float _bbardistance = 0.0;
	int _bnumber = 0;
	int _bbarnumber = 0;
	int _btotalnumber = 0;
	int _bbartotalnumber = 0;
	MC->SetBranchAddress("bdistance", &_bdistance);
	MC->SetBranchAddress("bbardistance", &_bbardistance);
	MC->SetBranchAddress("bnumber", &_bnumber);
	MC->SetBranchAddress("bbarnumber", &_bbarnumber);
	MC->SetBranchAddress("bbartotalnumber", &_bbartotalnumber);
	MC->SetBranchAddress("btotalnumber", &_btotalnumber);

	int _numberOfTagged = 0;
	int _PDGreco[MAXV];
	int _bnumberreco = 0;
	int _bbarnumberreco = 0;
	

	//RECO->SetBranchAddress("numberOfTagged", &_numberOfTagged);
	//RECO->SetBranchAddress("PDG", _PDGreco);
	RECO->SetBranchAddress("bnumber", &_bnumberreco);
	RECO->SetBranchAddress("bbarnumber", &_bbarnumberreco);
	int mTotalNumberOfEvents1 = MC->GetEntries();
	for (int k = 0; k < mTotalNumberOfEvents1; k++)
	{
	        RECO->GetEntry(k);
	        MC->GetEntry(k);
		if (_bnumber == 1 && _bnumberreco > 0) 
		{
			float value = (float)_bnumberreco / (float)_btotalnumber;
			std::cout << "i: " << k
				  << " Distance: " << _bdistance
				  << " B Number Reco: " << _bnumberreco
				  << " B Number MC: " << _btotalnumber
				  << '\n';
			erf->Fill(_bdistance, value);
			distmc->Fill(_bdistance);
			if (value > 0.9) 
			{
				distreco->Fill(_bdistance);
			}
		}
		if (_bbarnumber == 1 && _bbarnumberreco > 0) 
		{
			float value = (float)_bbarnumberreco /  (float)_bbartotalnumber;
			std::cout << "i: " << k
				  << " Distance: " << _bbardistance
				  << " B Number Reco: " << _bbarnumberreco
				  << " B Number MC: " << _bbartotalnumber
				  << '\n';
			erf->Fill(_bbardistance, value);
			distmc->Fill(_bbardistance);
			if (value > 0.9) 
			{
				distreco->Fill(_bbardistance);
			}
		}
	}

	gStyle->SetPalette(1);
	erf->Draw("lego2z");
	distmc->Draw();
	distreco->Draw("psame");
	if (TEfficiency::CheckConsistency(*distreco, *distmc)) 
	{
		TEfficiency * eff = new TEfficiency(*distreco, *distmc);
	}
	eff->SetTitle("One track efficiency;B-D distance, mm");
	
	eff->Draw("AP");
}
