#include "../vertex/ratioplot.C"
#define MAXN  1000
void TVCM(string filename = "RecoTest.root")
{
	int bin_e = 50;
	float max_e = 20;
	float min_e = 0;

	int _nvertex = 0;
	int _pdg[MAXN];
	float _probability[MAXN];
	float _chi2[MAXN];
	float _distanceIP[MAXN];
	int _generation[MAXN];
	int _numberOfParticles[15];
	int _trueTypeOfParticles[15][15];

	TChain* T = new TChain("TaggedVertices");
	T->Add(filename.c_str());

	T->SetBranchAddress("numberOfTagged", &_nvertex);
	T->SetBranchAddress("PDG", _pdg);
	T->SetBranchAddress("generation", _generation);
	T->SetBranchAddress("distanceIP", _distanceIP);
	T->SetBranchAddress("chi2", _chi2);
	T->SetBranchAddress("probability", _probability);
	T->SetBranchAddress("numberOfParticles", _numberOfParticles);
	T->SetBranchAddress("trueTypeOfParticles", _trueTypeOfParticles);

	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,500,600);
	int mTotalNumberOfEvents = T->GetEntries();
	TH1F * allDist = new TH1F("allDist", "Reco;d_{B}, mm", bin_e,min_e,max_e);
	TH1F * badDist = new TH1F("badDist", "Reco;d_{B}, mm", bin_e,min_e,max_e);

	for (unsigned int i = 0; i < mTotalNumberOfEvents; i += 1)
	{
		T->GetEntry(i);
		for (int j = 0; j < _nvertex; j++) 
		{
			//cout << "Ntracks: "  << _numberOfParticles[j] << endl;
			int kaoncount = 0;
			int kaonpdg = 0;
			if (_generation[j] != 3) 
			{
				continue;
			}
			for (int k = 0; k < _numberOfParticles[j]; k++) 
			{
				if (abs(_trueTypeOfParticles[j][k]) == 321) 
				{
					kaoncount++;
					kaonpdg = _trueTypeOfParticles[j][k];
				}
			}
			//cout << "Generation: " << _generation[j]  << " PDG: " << kaonpdg << " count " << kaoncount << endl;
			if (kaoncount == 1) 
			{
				allDist->Fill(_distanceIP[j]);
				if (kaonpdg * _pdg[j] > 0) 
				{
					badDist->Fill(_distanceIP[j]);
				}
			}
		}
	}
	makePretty(allDist,kBlue);
	makePretty(badDist,kBlack);
	ratioplot(badDist,allDist, c1);
	//allDist->Draw();
	//badDist->Draw("same");
}
void makePretty(TH1 * vtxTotal, int color)
{
	vtxTotal->SetLineWidth(3);
	vtxTotal->SetLineColor(color);
	vtxTotal->SetMinimum(0);
	vtxTotal->SetStats(0);
}
