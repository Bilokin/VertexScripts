#include <unistd.h>
#include <iostream>
#define MAXV 8
float getDistance(float * v1, float * v2, int number)
{
	float diff;
	for (int i = 0; i < 3; i++) 
	{
		diff += (v1[number][i] - v2[number][i]) * (v1[number][i] - v2[number][i]);
	}

	return sqrt(diff);
}
TEfficiency * getEfficiency(TH1 * good, TH1 * total, bool same, int color, string title)
{
	if (TEfficiency::CheckConsistency(*good, *total)) 
	{
		TEfficiency * eff2 = new TEfficiency(*good, *total);
	}
	eff2->SetTitle(title.c_str());
	eff2->SetLineColor(color);
	eff2->SetMarkerSize(0.5);

	eff2->SetMarkerStyle(20);
	eff2->SetMarkerColor(color);
	string draw = (same)? "Psame": "AP";
	eff2->Draw(draw.c_str());
	
}
void chargeEfficiency(string recofilename = "TrashRecoTest.root", int color = kBlack, TCanvas * c1 = NULL)
//void chargeEfficiency()
{
	//gStyle->SetCanvasPreferGL(kTRUE);
	int bin_e = 6;
	int max_e = 3;
	bool same = true;
	if (!c1) 
	{
		c1 = new TCanvas("c1", "Data-MC",0,0,800,800);
		c1->Divide(2,2);
		same = false;
	}
	TH1F * chargemc = new TH1F("distmc", "Generator charge", bin_e,-3,max_e);
	TH1F * chargereco = new TH1F("distreco", "Reconstructed charge", bin_e,-3,max_e);
	int nbins = 25;
	int maxp = 120;
	int maxd = 20;
	TH1F * momentumreco = new TH1F("numberreco2", "Reconstructed particles", nbins,0,maxp);
	TH1F * momentumrecototal = new TH1F("numbercreco", "Reconstructed particles", nbins,0,maxp);
	TH1F * distreco = new TH1F("disteco2", "Reconstructed particles", nbins,0,maxd);
	TH1F * distrecototal = new TH1F("distreco", "Reconstructed particles", nbins,0,maxd);
	TH1F * btagreco = new TH1F("breco2", "Reconstructed particles", nbins,0,1);
	TH1F * btagrecototal = new TH1F("breco", "Reconstructed particles", nbins,0,1);
	TH1F * numberreco = new TH1F("bn2", "Reconstructed particles", 12,0,12);
	TH1F * numberrecototal = new TH1F("bn", "Reconstructed particles", 12,0,12);
	TH1F * numbergen = new TH1F("bgenn2", "Reconstructed particles", 12,0,12);
	TH1F * numbergentotal = new TH1F("bgenn", "Reconstructed particles", 12,0,12);


	chargereco->Sumw2();
	chargemc->Sumw2();
	TChain* MC2 = new TChain("Stats");
	MC2->Add("TrashMCTest.root");
	//TChain* MC = new TChain("Vertices");
	//MC->Add("TrashMCTest.root");
	TChain* RECO = new TChain("Stats");
	RECO->Add(recofilename.c_str());
	int _numberOfVertexes = 0;
	int _tag = 0;
	float _coordinates[MAXV][3];
	int _PDG[MAXV];
	int _generation[MAXV];
	int _distance[MAXV];
	int _charge[MAXV];
	
	int _brecocharge = 0;
	int _bbarrecocharge = 0;
	int _bcharge = 0;
	int _bbarcharge = 0;
	float _bdistance = 0.0;
	float _bbardistance = 0.0;
	float _bmomentum = 0.0;
	float _bbarmomentum = 0.0;
	int _bnumber = 0;
	int _bbarnumber = 0;
	int _cnumber = 0;
	int _cbarnumber = 0;
	float _bIPdistance = 0.0;
	float _bbarIPdistance = 0.0;
	float _bptmiss = 0.0;
	float _bbarptmiss = 0.0;
	float _bteta = 0.0;
	float _bbarteta = 0.0;
	int _breconumber = 0;
	int _bbarreconumber = 0;
	float _btag = 0.0;
	float _bbartag = 0.0;

	//MC2->SetBranchAddress("bmomentum", &_bmomentum);
	//MC2->SetBranchAddress("bbarmomentum", &_bbarmomentum);
	//MC2->SetBranchAddress("bdistance", &_bdistance);
	//MC2->SetBranchAddress("bbardistance", &_bbardistance);
	MC2->SetBranchAddress("bcharge", &_bcharge);
	MC2->SetBranchAddress("bbarcharge", &_bbarcharge);
	MC2->SetBranchAddress("btotalnumber", &_bnumber);
	MC2->SetBranchAddress("bbartotalnumber", &_bbarnumber);
	MC2->SetBranchAddress("cbarnumber", &_cbarnumber);
	MC2->SetBranchAddress("cnumber", &_cnumber);
	MC2->SetBranchAddress("bIPdistance", &_bdistance);
	MC2->SetBranchAddress("bbarIPdistance", &_bbardistance);

	int _numberOfTagged = 0;
	int _PDGreco[MAXV];
	int _generationreco[MAXV];
	int _chargereco[MAXV];
	int _numberOfParticles[MAXV];

	//RECO->SetBranchAddress("numberOfTagged", &_numberOfTagged);
	//RECO->SetBranchAddress("PDG", _PDGreco);
	//RECO->SetBranchAddress("charge", _chargereco);
	//RECO->SetBranchAddress("generation", _generationreco);
	//RECO->SetBranchAddress("numberOfParticles", _numberOfParticles);
	RECO->SetBranchAddress("bbarptmiss", &_bbarptmiss);
	RECO->SetBranchAddress("bptmiss", &_bptmiss);
	RECO->SetBranchAddress("bteta", &_bteta);
	RECO->SetBranchAddress("bbarteta", &_bbarteta);
	RECO->SetBranchAddress("bbarmomentum", &_bbarmomentum);
	RECO->SetBranchAddress("bmomentum", &_bmomentum);
	RECO->SetBranchAddress("bIPdistance", &_bIPdistance);
	RECO->SetBranchAddress("bbarIPdistance", &_bbarIPdistance);
	RECO->SetBranchAddress("bcharge", &_brecocharge);
	RECO->SetBranchAddress("bbarcharge", &_bbarrecocharge);
	RECO->SetBranchAddress("bnumber", &_breconumber);
	RECO->SetBranchAddress("bbarnumber", &_bbarreconumber);
	RECO->SetBranchAddress("btag", &_btag);
	RECO->SetBranchAddress("bbartag", &_bbartag);
	int mTotalNumberOfEvents1 = MC2->GetEntries();
	int counter = 0;
	int total = 0;
	int num = 1;
	float dist = 8.0;
	for (int k = 0; k < mTotalNumberOfEvents1; k++)
	{
	        RECO->GetEntry(k);
	        MC2->GetEntry(k);
		//chargemc->Fill(bbarcharge);
		bool bexist = false;
		bool bbarexist = false;
		//std::cout << "i: " << k << '\n';
		if (_bbarnumber >  -1
		   // && _bbarreconumber == _bbarnumber
		    //&&_bbarmomentum > 15
		    //&&_bbartag > 0.3
		    //&& _bbarreconumber < 7
		    && _bbarreconumber > 0
		    )
		{
			momentumrecototal->Fill(_bbarmomentum);
			distrecototal->Fill(_bbardistance);
			btagrecototal->Fill(_bbartag);
			numbergentotal->Fill(_bbarnumber);
			numberrecototal->Fill(_bbarreconumber);
			total++;
			//std::cout << "Reco bbar charge: " << _bbarrecocharge << '\n';
			//if(_bbarrecocharge == _bbarcharge)
			if ((_bbarrecocharge * _bbarcharge > 0.0) || (_bbarrecocharge ==0 && _bbarcharge == 0)) 
			{
				momentumreco->Fill(_bbarmomentum);
				distreco->Fill(_bbardistance);
				btagreco->Fill(_bbartag);
				numbergen->Fill(_bbarnumber);
				numberreco->Fill(_bbarreconumber);
				counter++;
			}
		}
		if (_bnumber > -1 
		    //&& _breconumber == _bbarnumber
		    //&& _bmomentum > 15
		    //&& _btag > 0.3
		    //&& _breconumber < 7
		    && _breconumber > 0
		    ) 
		{
			momentumrecototal->Fill(_bmomentum);
			distrecototal->Fill(_bdistance);
			btagrecototal->Fill(_btag);
			numbergentotal->Fill(_bnumber);
			numberrecototal->Fill(_breconumber);
			total++;
			//if(_brecocharge == _bcharge)
			if ((_brecocharge * _bcharge > 0.0) || (_brecocharge ==0 && _bcharge == 0)) 
			{
				momentumreco->Fill(_bmomentum);
				distreco->Fill(_bdistance);
				btagreco->Fill(_btag);
				numberreco->Fill(_breconumber);
				numbergen->Fill(_bnumber);
				counter++;

			}
		}
	}
	gStyle->SetPalette(1);
	c1->cd(1);
	//momentumrecototal->Draw("p");
	//momentumreco->Draw("same");
	//distrecototal->Draw("p");
	//distreco->Draw("same");
	getEfficiency(btagreco, btagrecototal, same, color, "Purity by btag;btag;#epsilon(btag)");
	c1->cd(2);
	getEfficiency(momentumreco, momentumrecototal, same, color, "Purity by momentum;|p|_{B};#epsilon(|p|_{B})");
	c1->cd(3);
	getEfficiency(numberreco, numberrecototal, same, color, "Purity by N_{reco};N_{reco};#epsilon(N_{reco})");

	c1->cd(4);
	getEfficiency(numbergen, numbergentotal, same, color,  "Purity by N_{gen};N_{gen};#epsilon(N_{gen})");
	std::cout << "Correct charge : " << counter << " out of " << total << " (" << (float)counter/(float)total*100. << "%)" <<'\n';
	//chargereco->Draw("psame");
}
