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
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * chargemc = new TH1F("distmc", "Generator charge", bin_e,-3,max_e);
	TH1F * chargereco = new TH1F("distreco", "Reconstructed charge", bin_e,-3,max_e);
	int nbins = 20;
	int maxp = 165;
	TH1F * momentumreco = new TH1F("numberreco2", "Reconstructed particles", nbins,0,maxp);
	TH1F * momentumrecototal = new TH1F("numbercreco", "Reconstructed particles", nbins,0,maxp);

	chargereco->Sumw2();
	chargemc->Sumw2();
	TChain* MC2 = new TChain("Stats");
	MC2->Add("TrashMCTest.root");
	TChain* MC = new TChain("Vertexes");
	MC->Add("TrashMCTest.root");
	TChain* RECO = new TChain("TaggedVertices");
	RECO->Add("TrashRecoTest.root");
	int _numberOfVertexes = 0;
	int _tag = 0;
	float _coordinates[MAXV][3];
	int _PDG[MAXV];
	int _generation[MAXV];
	int _distance[MAXV];
	int _charge[MAXV];
	
	float _bmomentum = 0.0;
	float _bbarmomentum = 0.0;

	MC2->SetBranchAddress("bmomentum", &_bmomentum);
	MC2->SetBranchAddress("bbarmomentum", &_bbarmomentum);

	MC->SetBranchAddress("numberOfVertexes", &_numberOfVertexes);
	MC->SetBranchAddress("tag", &_tag);
	MC->SetBranchAddress("charge", _charge);
	MC->SetBranchAddress("PDG", _PDG);
	MC->SetBranchAddress("generation", _generation);
	//MC->SetBranchAddress("coordinates", _coordinates);
	/*float _bdistance = 0.0;
	float _bbardistance = 0.0;

	MC->SetBranchAddress("bdistance", &_bdistance);
	MC->SetBranchAddress("bbardistance", &_bbardistance);
	*/
	int _numberOfTagged = 0;
	int _PDGreco[MAXV];
	int _generationreco[MAXV];
	int _chargereco[MAXV];
	int _numberOfParticles[MAXV];

	RECO->SetBranchAddress("numberOfTagged", &_numberOfTagged);
	RECO->SetBranchAddress("PDG", _PDGreco);
	RECO->SetBranchAddress("charge", _chargereco);
	RECO->SetBranchAddress("generation", _generationreco);
	RECO->SetBranchAddress("numberOfParticles", _numberOfParticles);
	int mTotalNumberOfEvents1 = MC->GetEntries();
	int counter = 0;
	int total = 0;
	for (int k = 0; k < mTotalNumberOfEvents1; k++)
	{
	        RECO->GetEntry(k);
	        MC->GetEntry(k);
	        MC2->GetEntry(k);
		int bcharge = 100;
		int bbarcharge = 100;
		total += (float)_numberOfVertexes/2.0;
		for (int i = 0; i < _numberOfVertexes; i++) 
		{
			if (_PDG[i] == 5 && _generation[i] == 2) 
			{
				bcharge = _charge[i];
				chargemc->Fill(_charge[i]);
			}
			if (_PDG[i] == -5 && _generation[i] == 2) 
			{
				bbarcharge = _charge[i];
				chargemc->Fill(_charge[i]);
			}
		}
		if (_numberOfVertexes == 0) 
		{
			continue;
		}
		//chargemc->Fill(bbarcharge);
		int recobcharge = 0;
		int recobbarcharge = 0;
		for (int j = 0; j < _numberOfTagged; j++) 
		{
			if (_PDGreco[j] == 5) 
			{
				recobcharge += _chargereco[j];
			}
			if (_PDGreco[j] == -5) 
			{
				recobbarcharge += _chargereco[j];
			}
		}
		if (bbarcharge < 2) 
		{
			momentumrecototal->Fill(_bbarmomentum);
		}
		if (bcharge < 2) 
		{
			 momentumrecototal->Fill(_bmomentum);
		}
		if (recobbarcharge * bbarcharge > 0.0 && bbarcharge < 2) 
		{
			momentumreco->Fill(_bbarmomentum);
			counter++;
		}
		if (recobcharge * bcharge > 0.0 && bcharge < 2) 
		{
			momentumreco->Fill(_bmomentum);
			counter++;
		}
		if (recobcharge == 0 && bcharge == 0) 
		{
			momentumreco->Fill(_bmomentum);
			counter++;
		}
		if (recobbarcharge ==0 && bbarcharge == 0) 
		{
			momentumreco->Fill(_bbarmomentum);
			counter++;
		}
		chargereco->Fill(recobbarcharge);
	}
	gStyle->SetPalette(1);
	momentumrecototal->Draw("p");
	momentumreco->Draw("same");
	std::cout << "Correct charge : " << counter << " out of " << total << " (" << (float)counter/(float)total << "%)" <<'\n';
	//chargereco->Draw("psame");
	if (TEfficiency::CheckConsistency(*momentumreco, *momentumrecototal)) 
	{
		TEfficiency * eff = new TEfficiency(*momentumreco, *momentumrecototal);
	}
	eff->SetTitle("Charge efficiency;|p|_{B};#epsilon(|p|_{B})");
	eff->Draw("AP");
}
