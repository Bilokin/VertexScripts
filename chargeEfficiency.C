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
void chargeEfficiency()
{
	//gStyle->SetCanvasPreferGL(kTRUE);
	int bin_e = 6;
	int max_e = 3;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,1000,500);
	c1->Divide(2,1);
	TH1F * chargemc = new TH1F("distmc", "Generator charge", bin_e,-3,max_e);
	TH1F * chargereco = new TH1F("distreco", "Reconstructed charge", bin_e,-3,max_e);
	int nbins = 30;
	int maxp = 165;
	int maxd = 20;
	TH1F * momentumreco = new TH1F("numberreco2", "Reconstructed particles", nbins,0,maxp);
	TH1F * momentumrecototal = new TH1F("numbercreco", "Reconstructed particles", nbins,0,maxp);
	TH1F * distreco = new TH1F("disteco2", "Reconstructed particles", nbins,0,maxd);
	TH1F * distrecototal = new TH1F("distreco", "Reconstructed particles", nbins,0,maxd);

	chargereco->Sumw2();
	chargemc->Sumw2();
	TChain* MC2 = new TChain("Stats");
	MC2->Add("TrashMCTest.root");
	//TChain* MC = new TChain("Vertices");
	//MC->Add("TrashMCTest.root");
	TChain* RECO = new TChain("Stats");
	RECO->Add("TrashRecoTest.root");
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

	//MC2->SetBranchAddress("bmomentum", &_bmomentum);
	//MC2->SetBranchAddress("bbarmomentum", &_bbarmomentum);
	//MC2->SetBranchAddress("bdistance", &_bdistance);
	//MC2->SetBranchAddress("bbardistance", &_bbardistance);
	MC2->SetBranchAddress("bcharge", &_bcharge);
	MC2->SetBranchAddress("bbarcharge", &_bbarcharge);
	MC2->SetBranchAddress("bnumber", &_bnumber);
	MC2->SetBranchAddress("bbarnumber", &_bbarnumber);
	/*MC2->SetBranchAddress("cbarnumber", &_cbarnumber);
	MC2->SetBranchAddress("cnumber", &_cnumber);
	MC2->SetBranchAddress("bIPdistance", &_bdistance);
	MC2->SetBranchAddress("bbarIPdistance", &_bbardistance);*/

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
		/*for (int j = 0; j < _numberOfTagged; j++) 
		{
			if (_PDGreco[j] == 5) 
			{
				recobcharge += _chargereco[j];
				bexist = true;
			}
			if (_PDGreco[j] == -5) 
			{
				recobbarcharge += _chargereco[j];
				bbarexist = true;
			}
		}
		if (!bexist && !bbarexist) 
		{
			continue;
		}*/
		std::cout << "i: " << k << '\n';

		std::cout << "Reco b charge: " << _brecocharge 
			  << '(' << bexist << ')'
			  <<"\t Gen b charge: " << _bcharge 
			  << '\n';
		std::cout << "Reco bbar charge: " << _bbarrecocharge 
			  << '(' << bbarexist << ')'
			  <<"\t Gen bbar charge: " << _bbarcharge 
			  << '\n';
		if (_bbarIPdistance > 0.0 
		    && _bbarreconumber == _bbarnumber
		    //&& _bbarreconumber > 2
		    //&& _bbarptmiss < 10
		    //&& _bbarIPdistance < 30.0
		    //&& ( _bbarmomentum > (_bbarteta-1.57)*(_bbarteta-1.57)*10.0+10.0  )
		    )
		{
			momentumrecototal->Fill(_bbarmomentum);
			distrecototal->Fill(_bbarIPdistance);
			total++;
			if(_bbarrecocharge == _bbarcharge)
			//if ((_bbarrecocharge * _bbarcharge > 0.0) || (_bbarrecocharge ==0 && _bbarcharge == 0)) 
			{
				momentumreco->Fill(_bbarmomentum);
				distreco->Fill(_bbarIPdistance);
				counter++;
			}
		}
		if (_bIPdistance > 0.0 
		    && _breconumber == _bnumber
		    //&& _breconumber > 2
		    //&& _bptmiss < 10
		    //&& _bIPdistance < 30.0
		    //&& ( _bmomentum > (_bteta-1.57)*(_bteta-1.57)*10.0+10.  )
		    ) 
		{
			momentumrecototal->Fill(_bmomentum);
			distrecototal->Fill(_bIPdistance);
			total++;
			if(_brecocharge == _bcharge)
			//if ((_brecocharge * _bcharge > 0.0) || (_brecocharge ==0 && _bcharge == 0)) 
			{
				momentumreco->Fill(_bmomentum);
				distreco->Fill(_bIPdistance);
				counter++;

			}
		}
	}
	gStyle->SetPalette(1);
	c1->cd(1);
	//momentumrecototal->Draw("p");
	//momentumreco->Draw("same");
	distrecototal->Draw("p");
	distreco->Draw("same");
	if (TEfficiency::CheckConsistency(*distreco, *distrecototal)) 
	{
		TEfficiency * eff = new TEfficiency(*distreco, *distrecototal);
	}
	eff->SetTitle("Charge efficiency;d_{BD};#epsilon(d_{BD})");
	eff->Draw("AP");
	c1->cd(2);
	std::cout << "Correct charge : " << counter << " out of " << total << " (" << (float)counter/(float)total*100. << "%)" <<'\n';
	//chargereco->Draw("psame");
	if (TEfficiency::CheckConsistency(*momentumreco, *momentumrecototal)) 
	{
		TEfficiency * eff = new TEfficiency(*momentumreco, *momentumrecototal);
	}
	eff->SetTitle("Charge efficiency;|p|_{B};#epsilon(|p|_{B})");
	eff->Draw("AP");
	
}
