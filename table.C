#define MAXN  1000
#include <iostream>
#include <cmath>
using std::cout;
void format(TH2 * table)
{
	table->GetXaxis()->CenterLabels();
	table->GetYaxis()->CenterLabels();
	table->GetYaxis()->SetNdivisions(110);
	table->GetXaxis()->SetNdivisions(110);
	table->GetYaxis()->SetTitle("N_{rec}");
	table->GetYaxis()->SetTitleSize(0.045);
	table->GetXaxis()->SetTitle("N_{gen}");
	table->GetXaxis()->SetTitleSize(0.045);
}
void table(string recofilename = "RecoTest.root"){
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
	int nbins = 10;
	int maxd = nbins;
	TH2I * probhist = new TH2I("Pw","# of tracks comparison",nbins,0,maxd ,nbins, 0, maxd );
	//TH2I * probhist_non = new TH2I("Pwo","# of tracks d_{IP}>1.0mm, |p_{b}|>15GeV, |cos#theta|<0.95",nbins,0,maxd , nbins,0, maxd );
	TH2I * probhist_non = new TH2I("Pwo","# of tracks btag > 0.8",nbins,0,maxd , nbins,0, maxd );
	
	TChain* T = new TChain("TaggedVertices");
	T->Add(recofilename.c_str());
	TChain* T3 = new TChain("Stats");
	T3->Add(recofilename.c_str());
	TChain* T2 = new TChain("Stats");
	T2->Add("MCTest.root");
	TChain* JETS = new TChain("Jets");
	JETS->Add(recofilename.c_str());

	int _bnumber = 0;
	int _bnvtx = 0;
	int _bbarnvtx = 0;
	int _bbarnumber = 0;
	int _btotalnumber = 0;
	int _bbarcharge = 0;
	int _bcharge = 0;
	int _cbarcharge = 0;
	int _ccharge = 0;
	int _bbarrecocharge = 0;
	int _brecocharge = 0;

	int _cnumber = 0;
	int _cbarnumber = 0;
	int _bbartotalnumber = 0;
	int _tag = 0;
	int _brecnumber = 0;
	int _bbarrecnumber = 0;
	int _boffsetnumber = 0;
	int _bbaroffsetnumber = 0;
	float _bdistance = 0.0;
	float _bbardistance = 0.0;
	float _bIPdistance = 0.0;
	float _bbarIPdistance = 0.0;

	float _bptmiss  = 0.0;
	float _bbarptmiss  = 0.0;
	float _bmomentum  = 0.0;
	float _bbarmomentum  = 0.0;
	float _bbarteta = 0.0;
	float _bcos = 0.0;
	float _bbarcos = 0.0;
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
	
	float _btag1 = 0.0;
	float _bbartag1 = 0.0;
	
	T3->SetBranchAddress("bnvtx", &_bnvtx);
	T3->SetBranchAddress("bbarnvtx", &_bbarnvtx);
	T3->SetBranchAddress("btag", &_btag1);
	T3->SetBranchAddress("bbartag", &_bbartag1);
	T3->SetBranchAddress("bnumber", &_brecnumber);
	T3->SetBranchAddress("bbarnumber", &_bbarrecnumber);
	T3->SetBranchAddress("bbarptmiss", &_bbarptmiss);
	T3->SetBranchAddress("bnoffsettracks", &_boffsetnumber);
	T3->SetBranchAddress("bbarnoffsettracks", &_bbaroffsetnumber);
	T3->SetBranchAddress("bptmiss", &_bptmiss);
	//T3->SetBranchAddress("bteta", &_bteta);
	//T3->SetBranchAddress("bbarteta", &_bbarteta);
	//T3->SetBranchAddress("bbarmomentum", &_bbarmomentum);
	//T3->SetBranchAddress("bmomentum", &_bmomentum);
	T3->SetBranchAddress("bIPdistance", &_bIPdistance);
	T3->SetBranchAddress("bbarIPdistance", &_bbarIPdistance);
	T3->SetBranchAddress("bcostheta", &_bcos);
	T3->SetBranchAddress("bbarcostheta", &_bbarcos);
	T3->SetBranchAddress("bcharge", &_brecocharge);
	T3->SetBranchAddress("bbarcharge", &_bbarrecocharge);



	T2->SetBranchAddress("bbarmomentum", &_bbarmomentum);
	T2->SetBranchAddress("bmomentum", &_bmomentum);
	T2->SetBranchAddress("btotalnumber", &_btotalnumber);
	T2->SetBranchAddress("bbartotalnumber", &_bbartotalnumber);
	T2->SetBranchAddress("bIPdistance", &_bdistance);
	T2->SetBranchAddress("bbarIPdistance", &_bbardistance);
	T2->SetBranchAddress("bnumber", &_bnumber);
	T2->SetBranchAddress("bbarnumber", &_bbarnumber);
	T2->SetBranchAddress("cnumber", &_cnumber);
	T2->SetBranchAddress("cbarnumber", &_cbarnumber);
	T2->SetBranchAddress("bcharge", &_bcharge);
	T2->SetBranchAddress("bbarcharge", &_bbarcharge);
	T2->SetBranchAddress("ccharge", &_ccharge);
	T2->SetBranchAddress("cbarcharge", &_cbarcharge);
	//T2->SetBranchAddress("cnumber_f", &_cnumber_f);
	//T2->SetBranchAddress("cbarnumber_f", &_cbarnumber_f);
	//T2->SetBranchAddress("bnumber_f", &_bnumber_f);
	//T2->SetBranchAddress("bbarnumber_f", &_bbarnumber_f);

	T2->SetBranchAddress("tag", &_tag);

	int mTotalNumberOfEvents = T2->GetEntries();
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
			//continue;
		}
		int bjets = 0;
		float btags[2];
		float btag = 0.0;
		float bbartag = 0.0;
		bbartag = _bbartag1;
		btag = _btag1;
		bn = _brecnumber;
		bbarn = _bbarrecnumber;
		if (bn > -1 && _bnumber > -1 ) 
		{
			probhist->Fill(_btotalnumber, bn);
			if (bn > 0) 
			{
				total++;
			}
			if (bn < 1) 
			{
				zerovtx++;
			}
			if (bn == _btotalnumber) 
			{
				totalgood++;
			}
		}
		if (bbarn > -1 && _bbarnumber > -1) 
		{
			probhist->Fill(_bbartotalnumber, bbarn);
			if (bbarn > 0) 
			{
				total++;
			}
			if (bbarn < 1) 
			{
				zerovtx++;
			}
			if (bbarn == _bbartotalnumber) 
			{
				totalgood++;
			}
		}
		float s = 0.90;
		float btagcut = 0.8;
		float pcut = 15.0;
		//std::cout << "cos: " << _bbarcos << "\n";
		if (bn > -1
		    && _btotalnumber > -1
		    //&& (_bcharge == _brecocharge )
		    //&& (_bcharge == 0 && _brecocharge == 0 || _bcharge * _brecocharge > 0)
		    //&& (abs(_bcharge) == 1 || abs(_bcharge) == 0)
		    //&& _boffsetnumber <= 0
		    //&& _bnumber > 1 && _cnumber > 1
		    //&& (float)bn/(float)_boffsetnumber > 0.95
		    //&& _btotalnumber < 7
		    //&& _bdistance > 1.0
		    //&& _bdistance < 35.0
		    && _bmomentum > pcut
		    //&& (_bnvtx == 2 || bn == 3)
		    //&& abs(_bcos) > s
		    //&& abs(_bcos) < s+0.046
		    //&& _bcos >  -s)
		    //&& bn < 8
		    && btag > btagcut
		    ) 
		{
			probhist_non->Fill(_btotalnumber, bn);
			if (bn > 0) 
			{
				aftercuts++;
			}
			if (bn == _btotalnumber) 
			{
				aftercutsgood++;
			}
		}
		if (bbarn > -1 
		    && _bbartotalnumber> -1
		    //&& _bbarnumber > 1 && _cbarnumber > 1
		    //&& (_bbarcharge == _bbarrecocharge)
		    //&& (_bbarcharge == 0 && _bbarrecocharge == 0 || _bbarcharge * _bbarrecocharge > 0)
		    //&& (abs(_bbarcharge) == 1 || abs(_bbarcharge) == 0)
		    //&& _bbaroffsetnumber <= 0
		    //&& (float)bbarn/(float)_bbaroffsetnumber > 0.95
		    //&& _bbartotalnumber < 7
		    //&& _bbardistance > 1.0
		    //&& _bbardistance < 35.0
		    && _bbarmomentum > pcut
		    //&& (_bbarnvtx == 2 || bbarn == 3)
		    //&& abs(_bbarcos) > s
		    //&& abs(_bbarcos) < s+0.046
		    //&& _bbarcos > 0-s )
		    //&& bbarn < 8
		    && bbartag > btagcut
		    ) 
		{
			probhist_non->Fill(_bbartotalnumber, bbarn);
			if (bbarn > 0) 
			{
				aftercuts++;
			}
			if (bbarn == _bbartotalnumber) 
			{
				aftercutsgood++;
			}
			if (bbarn == 0 && _bbartotalnumber == 3) 
			{
				/*std::cout << "i: " << i
					  //<< " B mc: " << _btotalnumber
					  //<< " B rec: " <<  bn //_brecnumber
					  << " Bbar mc: " << _bbartotalnumber
					  << " Bbar rec: " << _bbarrecnumber
					  << " Bbar cos: " << _bbarcos
					  << " Bbar dist: " << _bbardistance
					  << " Bbar p: " << _bbarmomentum
					  << " Bbar tag: " << bbartag
					  << std::endl;*/
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
	gStyle->SetPalette(1);
	c1->cd(1);
	gPad->SetGrid();
	string opt = "text";
	if (1) 
	{
		int max = 2300;
		probhist->SetMinimum(0);
		//probhist->SetMaximum(max);
		probhist_non->SetMinimum(0);
		//probhist_non->SetMaximum(max);
		opt = "colz";
	}
	format(probhist);
	probhist->SetStats(0);
	probhist->Draw(opt.c_str());
	c1->cd(2);
	gPad->SetGrid();
	format(probhist_non);
	probhist_non->SetStats(0);
	probhist_non->Draw(opt.c_str());
}
