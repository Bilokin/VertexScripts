#define MAXN  1000
#include <iostream>
using std::cout;

void NoT2D(){
	int _vertex = 0;
	int _pdg[MAXN];
	float _probability[MAXN];
	float _chi2[MAXN];
	int _generation[MAXN];
	int _numberOfParticles[MAXN];
	
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,500,500);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadColor(kWhite);
	c1->Divide(2,2);
	/*TPad *boxPad  = new TPad("box", "box", 0.02, 0.02, 0.48, 0.92);
	TPad *box1Pad = new TPad("box1", "box1", 0.52, 0.02, 0.98, 0.92);
	boxPad->Draw();
	box1Pad->Draw();*/
	int nbins = 10;
	int maxd = 10;
	TH2F * probhist = new TH2F("Pw","P()",nbins,0,1.0 ,nbins, 0, maxd );
	TH2F * probhist_non = new TH2F("Pwo","P()",nbins,0,1.0 , nbins,0, maxd );
	probhist_non->Sumw2();
	TH2F * chihist= new TH2F("Chiw","Chi()",nbins,0,30, nbins,0, maxd );
	TH2F * chihist_non = new TH2F("Chiwo","Chi()",nbins,0,30, nbins, 0, maxd);
	chihist_non->Sumw2();
	TChain* T = new TChain("TaggedVertices");
	T->Add("TrashRecoTest.root");
	TChain* T2 = new TChain("Stats");
	T2->Add("TrashMCTest.root");

	float _bdistance = 0.0;
	float _bbardistance = 0.0;

	T2->SetBranchAddress("bdistance", &_bdistance);
	T2->SetBranchAddress("bbardistance", &_bbardistance);

	int mTotalNumberOfEvents = T->GetEntries();
	T->SetBranchAddress("numberOfTagged", &_vertex);
	T->SetBranchAddress("PDG", _pdg);
	T->SetBranchAddress("generation", _generation);
	T->SetBranchAddress("chi2", _chi2);
	T->SetBranchAddress("probability", _probability);
	T->SetBranchAddress("numberOfParticles", _numberOfParticles);
	
	cout << "mTotalNumberOfEvents: " << mTotalNumberOfEvents << '\n';
	int counter = 0;
	int num = 0;
	for (unsigned int i = 0; i < mTotalNumberOfEvents; i += 1)
	{
		T->GetEntry(i);
		T2->GetEntry(i);
		vector<int> bs;
		vector<int> bbars;
		for (int j = 0; j < _vertex; j++) 
		{
			if (_pdg[j] == 5) 
			{
				bs.push_back(j);
			}
			else//if (_pdg[j] == -5) 
			{
				bbars.push_back(j);
			}
		}
		for (int k = 0; k < bbars.size(); k++) 
		{
			if (bbars.size() > 1) 
			{
				probhist->Fill(_probability[bbars[k]], _numberOfParticles[bbars[k]]);
				chihist->Fill(_chi2[bbars[k]], _numberOfParticles[bbars[k]]);
			}
			else 
			{
				probhist_non->Fill(_probability[bbars[0]], _numberOfParticles[bbars[0]]);
				chihist_non->Fill(_chi2[bbars[0]], _numberOfParticles[bbars[0]]);
			}
		}
		for (int m = 0; m < bs.size(); m++) 
		{
			if (bs.size() > 1) 
			{
				probhist->Fill(_probability[bs[m]], _numberOfParticles[bs[m]]);
				chihist->Fill(_chi2[bs[m]], _numberOfParticles[bs[m]]);
			}
			else 
			{
				probhist_non->Fill(_probability[bs[0]], _numberOfParticles[bs[0]]);
				chihist_non->Fill(_chi2[bs[0]], _numberOfParticles[bs[0]]);
			}
		}
	}
	
	chihist_non->GetXaxis()->SetTitle("#chi^{2}");
	chihist->GetXaxis()->SetTitle("#chi^{2}");
	
	probhist_non->GetXaxis()->SetTitle("P(V)");
	probhist->GetXaxis()->SetTitle("P(V)");
	gStyle->SetPalette(1);
	c1->cd(1);
	probhist->Draw("colz");
	c1->cd(3);
	probhist_non->Draw("colz");
	c1->cd(2);
	chihist->Draw("colz");
	c1->cd(4);
	chihist_non->Draw("colz");
	std::cout << "Statistics: " << probhist->GetEntries() << " with ternary; " << probhist_non->GetEntries() << " without ternary; " << counter << " total\n";
	std::cout << "Mean: " << probhist->GetMean() << " with ternary; " << probhist_non->GetMean() << " without ternary;\n";
}
