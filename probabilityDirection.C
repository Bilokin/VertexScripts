#define MAXN  1000
#include <iostream>
using std::cout;

void probabilityDirection(){
	int _vertex = 0;
	int _pdg[MAXN];
	float _probability[MAXN];
	float _chi2[MAXN];
	int _generation[MAXN];
	
	gStyle->SetCanvasPreferGL(kTRUE);
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,500);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadColor(kWhite);
	TPad *boxPad  = new TPad("box", "box", 0.02, 0.02, 0.48, 0.92);
	TPad *box1Pad = new TPad("box1", "box1", 0.52, 0.02, 0.98, 0.92);
	boxPad->Draw();
	box1Pad->Draw();
	int nbin = 40;
	TH1F * probhist = new TH1F("Phi","Phi",nbin,0,1.01 );
	TH1F * probhist_non = new TH1F("Teta","Teta",nbin,0,1.01  );
	probhist_non->Sumw2();
	TH1F * chihist= new TH1F("PhiD","PhiD",40,0,30 );
	TH1F * chihist_non = new TH1F("TetaD","TetaD",40,0,30  );
	chihist_non->Sumw2();

	TChain* T = new TChain("TaggedVertices");
	T->Add("TrashRecoTest.root");
	TChain* T2 = new TChain("Stats");
	T2->Add("TrashMCTest.root");

	int mTotalNumberOfEvents = T->GetEntries();
	T->SetBranchAddress("numberOfTagged", &_vertex);
	T->SetBranchAddress("PDG", _pdg);
	T->SetBranchAddress("generation", _generation);
	T->SetBranchAddress("chi2", _chi2);
	T->SetBranchAddress("probability", _probability);
	
	int _btotalnumber = 0;
	int _bbartotalnumber = 0;
	int _bnumber = 0;
	int _bbarnumber = 0;
	float _bdistance = 0.0;
	float _bbardistance = 0.0;
	float _bIPdistance = 0.0;
	float _bbarIPdistance = 0.0;
	T2->SetBranchAddress("btotalnumber", &_btotalnumber);
	T2->SetBranchAddress("bbartotalnumber", &_bbartotalnumber);
	T2->SetBranchAddress("bnumber", &_bnumber);
	T2->SetBranchAddress("bbarnumber", &_bbarnumber);
	T2->SetBranchAddress("bdistance", &_bdistance);
	T2->SetBranchAddress("bbardistance", &_bbardistance);
	T2->SetBranchAddress("bIPdistance", &_bIPdistance);
	T2->SetBranchAddress("bbarIPdistance", &_bbarIPdistance);
	cout << "mTotalNumberOfEvents: " << mTotalNumberOfEvents << '\n';
	int counter = 0;
	int totalcounter = 0;
	int num = 2;
	float distcut = .5;
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
			/*if (
			     _bbarIPdistance < 0.50 
			  || _bbartotalnumber > 5
			  || _bbartotalnumber < 3
			  || _bbarnumber < 2
			  || _bbartotalnumber - _bbarnumber < 2
			) 
			{
				continue;
			}*/
			if (bbars.size() > 1) 
			{
				std::cout << "Nb: " << i << '\n';
				probhist->Fill(_probability[bbars[k]]);
				chihist->Fill(_chi2[bbars[k]]);
			}
			else 
			{
				probhist_non->Fill(_probability[bbars[0]]);
				chihist_non->Fill(_chi2[bbars[0]]);
			} 
		}
		for (int m = 0; m < bs.size(); m++) 
		{
			/*if (
			     _bIPdistance < 0.50
			  || _btotalnumber > 5
			  //|| _btotalnumber < 3
			  || _bnumber < 2
			  || _btotalnumber - _bnumber < 2
			) 
			{
				continue;
			}*/
			if (bs.size() > 1) 
			{
				probhist->Fill(_probability[bs[m]]);
				chihist->Fill(_chi2[bs[m]]);
			}
			else 
			{
				probhist_non->Fill(_probability[bs[0]]);
				chihist_non->Fill(_chi2[bs[0]]);
			} 
		}
		if ( bbars.size() > 0) 
		{
			totalcounter++;
		}
		if ( bs.size() > 0) 
		{
			totalcounter++;
		}
	}
	boxPad->cd();
	probhist_non->SetMarkerStyle(20);
	chihist_non->SetMarkerStyle(20);
	chihist_non->SetMarkerColor(kBlack);
	chihist_non->SetMarkerSize(0.7);
	chihist_non->GetXaxis()->SetTitle("#chi^2");
	chihist->SetFillColor(kYellow);
	chihist->GetXaxis()->SetTitle("#chi^{2}");
	
	probhist_non->SetMarkerColor(kBlack);
	probhist_non->SetMarkerSize(0.7);
	probhist_non->GetXaxis()->SetTitle("P(V)");
	//probhist->GetYaxis()->SetRange(0,0.1);
	//probhist_non->GetYaxis()->SetRange(0,0.1);
	probhist->SetMaximum(2000);
	probhist_non->SetMaximum(2000);
	probhist_non->SetMinimum(0);
	probhist->SetMinimum(0);
	probhist->SetFillColor(kYellow);
	probhist->GetXaxis()->SetTitle("P(V)");
	probhist->DrawNormalized("same");
	probhist_non->DrawNormalized("ex0psame");
	boxPad->SetGrid();
	box1Pad->cd();
	box1Pad->SetLogy();
	chihist->DrawNormalized("");
	chihist_non->DrawNormalized("ex0psame",1);
	box1Pad->SetGrid();
	box1Pad->Modified();
	boxPad->Modified();
	std::cout << "Statistics: " << probhist->GetEntries() << " with ternary; " << probhist_non->GetEntries() << " without ternary; " << totalcounter << " total; " << counter << " discarded\n";
	std::cout << "Mean: " << probhist->GetMean() << " with ternary; " << probhist_non->GetMean() << " without ternary;\n";
}
