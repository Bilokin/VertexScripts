#define MAXN  1000
#include <iostream>
using std::cout;

void table(){
	int _vertex = 0;
	int _pdg[MAXN];
	float _probability[MAXN];
	float _chi2[MAXN];
	int _generation[MAXN];
	int _numberOfParticles[MAXN];
	
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,500);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadColor(kWhite);
	c1->Divide(2,1);
	/*TPad *boxPad  = new TPad("box", "box", 0.02, 0.02, 0.48, 0.92);
	TPad *box1Pad = new TPad("box1", "box1", 0.52, 0.02, 0.98, 0.92);
	boxPad->Draw();
	box1Pad->Draw();*/
	int nbins = 8;
	int maxd = nbins;
	TH2I * probhist = new TH2I("Pw","# of tracks comparison",nbins,0,maxd ,nbins, 0, maxd );
	TH2I * probhist_non = new TH2I("Pwo","# of tracks filtered",nbins,0,maxd , nbins,0, maxd );
	
	TChain* T = new TChain("TaggedVertices");
	T->Add("TrashRecoTest.root");
	TChain* T3 = new TChain("Stats");
	T3->Add("TrashRecoTest.root");
	TChain* T2 = new TChain("Stats");
	T2->Add("TrashMCTest.root");
	TChain* JETS = new TChain("Jets");
	JETS->Add("TrashRecoTest.root");

	int _bnumber = 0;
	int _bexists = 0;
	int _bbarexists = 0;
	int _bbarnumber = 0;
	int _btotalnumber = 0;

	int _cnumber = 0;
	int _cbarnumber = 0;
	int _bbartotalnumber = 0;
	int _tag = 0;
	int _brecnumber = 0;
	int _bbarrecnumber = 0;
	float _bdistance = 0.0;
	float _bbardistance = 0.0;
	float _bIPdistance = 0.0;
	float _bbarIPdistance = 0.0;

	float _bptmiss  = 0.0;
	float _bbarptmiss  = 0.0;
	float _bmomentum  = 0.0;
	float _bbarmomentum  = 0.0;
	float _bbarteta = 0.0;
	float _bteta = 0.0;
	int _jetnumber = 0;
	int _nvtx[MAXN];
	float _btag[MAXN];
	int _mctag[MAXN];
	int _cnumber_f = 0;
	int _cbarnumber_f = 0;
	int _bnumber_f = 0;
	int _bbarnumber_f = 0;
	JETS->SetBranchAddress("numberOfJets", &_jetnumber);
	JETS->SetBranchAddress("numberOfVertices", _nvtx);
	JETS->SetBranchAddress("btags", _btag);
	JETS->SetBranchAddress("mcpdg", _mctag);

	
	T3->SetBranchAddress("bexists", &_bexists);
	T3->SetBranchAddress("bbarexists", &_bbarexists);
	T3->SetBranchAddress("bnumber", &_brecnumber);
	T3->SetBranchAddress("bbarnumber", &_bbarrecnumber);
	T3->SetBranchAddress("bbarptmiss", &_bbarptmiss);
	T3->SetBranchAddress("bptmiss", &_bptmiss);
	T3->SetBranchAddress("bteta", &_bteta);
	T3->SetBranchAddress("bbarteta", &_bbarteta);
	T3->SetBranchAddress("bbarmomentum", &_bbarmomentum);
	T3->SetBranchAddress("bmomentum", &_bmomentum);
	T3->SetBranchAddress("bIPdistance", &_bIPdistance);
	T3->SetBranchAddress("bbarIPdistance", &_bbarIPdistance);



	T2->SetBranchAddress("btotalnumber", &_btotalnumber);
	T2->SetBranchAddress("bbartotalnumber", &_bbartotalnumber);
	T2->SetBranchAddress("bdistance", &_bdistance);
	T2->SetBranchAddress("bbardistance", &_bbardistance);
	T2->SetBranchAddress("bnumber", &_bnumber);
	T2->SetBranchAddress("bbarnumber", &_bbarnumber);
	T2->SetBranchAddress("cnumber", &_cnumber);
	T2->SetBranchAddress("cbarnumber", &_cbarnumber);
	T2->SetBranchAddress("cnumber_f", &_cnumber_f);
	T2->SetBranchAddress("cbarnumber_f", &_cbarnumber_f);
	T2->SetBranchAddress("bnumber_f", &_bnumber_f);
	T2->SetBranchAddress("bbarnumber_f", &_bbarnumber_f);

	T2->SetBranchAddress("tag", &_tag);

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
	int goodevents = 0;
	int totalevents = 0;
	
	int total = 0;
	int aftercuts = 0;
	int totalgood = 0;
	int aftercutsgood = 0;
	int zerovtx = 0;
	for (unsigned int i = 0; i < mTotalNumberOfEvents; i += 1)
	{
		T->GetEntry(i);
		T2->GetEntry(i);
		T3->GetEntry(i);
		JETS->GetEntry(i);
		vector<int> bs;
		vector<int> bbars;
		int bn = 0;
		int bbarn = 0;
		if (_tag == 0) 
		{
			continue;
		}
		int bjets = 0;
		float btags[2];
		float btag = 0.0;
		float bbartag = 0.0;
		/*for (int jet = 0; jet < _jetnumber; jet++) 
		{
			if (abs(_mctag[jet]) > 0) 
			{
				btags[bjets++] = _btag[jet];

			}
			if (_mctag[jet] < 0) 
			{
				btag  = _btag[jet];
				std::cout << "btag: " << btag << '\n';
			}
			if (_mctag[jet] > 0) 
			{
				bbartag  = _btag[jet];
				std::cout << "bbartag: " << bbartag << '\n';
			}
		}
		if (bjets < 2) 
		{
			continue;
		}*/
		for (int j = 0; j < _vertex; j++) 
		{
			if (_pdg[j] == 5) 
			{
				bs.push_back(j);
				bn += _numberOfParticles[j];
			}
			if (_pdg[j] == -5) 
			{
				bbars.push_back(j);
				bbarn += _numberOfParticles[j];
			}
		}
		//_btotalnumber = _bnumber + _cnumber;
		//_bbartotalnumber = _bbarnumber + _cbarnumber;
		if (bn > -1 && _bnumber > -1 ) 
		{
			probhist->Fill(_btotalnumber, bn);
			if (bn > 0) 
			{
				total++;
			}
			if (bn == 0) 
			{
				zerovtx++;
			}
			if (bn == _btotalnumber) 
			{
				totalgood++;
			}
			else 
			{
				/*std::cout << "i: " << i
					  << " B mc: " << _btotalnumber
					  << " B rec: " <<  _brecnumber
					  << " B rec ex: " <<  _bexists
					  << " Bbar mc: " << _bbartotalnumber
					  << " Bbar rec: " << _bbarrecnumber
					  << " Bbar ex: " << _bbarexists
					  << std::endl;*/
			}
		}
		if (bbarn > -1 && _bbarnumber > -1) 
		{
			probhist->Fill(_bbartotalnumber, bbarn);
			if (bbarn > 0) 
			{
				total++;
			}
			if (bbarn == 0) 
			{
				zerovtx++;
			}
			if (bbarn == _bbartotalnumber) 
			{
				totalgood++;
			}
		}
		float s = 0.0;
		if (bn > -1
		    && _bnumber_f > -1
		    //&& btag > 0.8
		    ) 
		{
			probhist_non->Fill(_cnumber_f+_bnumber_f, bn);
			if (bn > 0) 
			{
				aftercuts++;
			}
			if (bn == _cnumber_f+_bnumber_f) 
			{
				aftercutsgood++;
			}
		}
		if (bbarn > -1 
		    && _bbarnumber_f > -1
		    //&& bbartag > 0.8
		    ) 
		{
			probhist_non->Fill(_cbarnumber_f+_bbarnumber_f, bbarn);
			if (bbarn > 0) 
			{
				aftercuts++;
			}
			if (bbarn == _cbarnumber_f+_bbarnumber_f) 
			{
				aftercutsgood++;
			}
		}
		if ( _bnumber > 0 && _bbarnumber > 0) 
		{
			totalevents++;
			if (bn > 0 && bbarn > 0) 
			{
				goodevents++;
			}
		}
	}
	cout << "Statistics: \n"
	     << "Total vertices : " << total
	     << " total after cuts: " << aftercuts << '(' << (float)aftercuts/(float)total*100.0 << "%)" 
	     << "\nTotal good vertices : " << totalgood << '(' << (float)totalgood/(float)total*100.0 << "%)"
	     << " total good after cuts: " << aftercutsgood << '(' << (float)aftercutsgood/(float)aftercuts*100.0 << "%)" 
	     << " \nTotal no reco vertex: " << zerovtx << '(' << (float)zerovtx/(float)total*100.0 << "%)"

	     << endl;
	cout << "Total events with 2 gen vertices: " << totalevents << " # events with 2 rec vertices: " << goodevents 
		<< '(' << (float)goodevents/(float)totalevents*100.0 << "%)"
		<< '\n';
	probhist_non->GetXaxis()->SetTitle("N_{gen}");
	probhist->GetXaxis()->SetTitle("N_{gen}");
	probhist_non->GetYaxis()->SetTitle("N_{rec}");
	probhist->GetYaxis()->SetTitle("N_{rec}");
	gStyle->SetPalette(1);
	c1->cd(1);
	gPad->SetGrid();
	probhist->Draw("text");
	c1->cd(2);
	gPad->SetGrid();
	probhist_non->Draw("text");
}
