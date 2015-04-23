#define MAXN  100
#include <iostream>
using std::cout;

float sigma(float offset, float p, float theta)
{
	float a = 0.005;
	float b = 0.01;
	float sin43 = std::pow( std::sin(theta), 4.0/3.0);
	//return p;
	//return offset;
	//return offset / a;
	return offset /sqrt(a*a + b*b / p / p / sin43);//*1000;

}

void missed(){
	int _tag = 0;
	int _bnumber = 0;
	int _bbarnumber = 0;
	int _cnumber = 0;
	int _cbarnumber = 0;
	float _boffsettrack[MAXN];
	float _bbaroffsettrack[MAXN];
	float _betatrack[MAXN];
	float _bbaretatrack[MAXN];
	float _bptrack[MAXN];
	float _betatrack[MAXN];
	float _bbarptrack[MAXN];
	float _bbaretatrack[MAXN];
	float _coffsettrack[MAXN];
	float _cbaroffsettrack[MAXN];
	float _cptrack[MAXN];
	float _cetatrack[MAXN];
	float _cbarptrack[MAXN];
	float _cbaretatrack[MAXN];
	int _breconumber = 0;
	int _bbarreconumber = 0;
	float _bptmiss;
	float _bbarptmiss;
	float _bmomentum;
	float _bteta;
	float _bbarteta;
	float _bIPdistance;
	float _bbarIPdistance;
	float _bprobmean;
	float _bchimean;
	gStyle->SetPalette(1);
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,500);
	c1->Divide(2,1);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadColor(kWhite);
	int nbin = 50;
	
	float maxp = 15;
	float maxep = 0.50;
	TH2F * lostpt = new TH2F("pelost","Lostpe", nbin,0, maxp, nbin, 0, maxep);
	TH2F * goodpt = new TH2F("pegood","goodpe", nbin,0, maxp, nbin, 0, maxep);
	int nbine = 30;
	float maxe = nbine;	
	TH1F * esmissed = new TH1F("ep", "#epsilon / #sigma;#epsilon / #sigma", nbine,0.0, maxe);
	TH1F * esgood = new TH1F("epgood", "#epsilon / #sigma;#epsilon / #sigma", nbine,0.0, maxe);
	TH1F * esprime = new TH1F("epprime", "#epsilon / #sigma;#epsilon / #sigma", nbine,0.0, maxe);
	esmissed->Sumw2();
	esprime->Sumw2();
	//esgood->Sumw2();
	goodpt->Sumw2();
	lostpt->Sumw2();
	TChain* T = new TChain("Tracks");
	T->Add("TrashMCTest.root");
	TChain* T1 = new TChain("Stats");
	T1->Add("TrashRecoTest.root");
	TChain* T2 = new TChain("Stats");
	T2->Add("TrashMCTest.root");
	TChain* T3 = new TChain("MissedTracks");
	T3->Add("TrashRecoTest.root");
	TChain* T5 = new TChain("MissedVertex");
	T5->Add("TrashRecoTest.root");
	TChain* T4 = new TChain("Primaries");
	T4->Add("VertexRestorer.root");

	int mTotalNumberOfEvents = T->GetEntries();
	T->SetBranchAddress("bnumber", &_bnumber);
	T->SetBranchAddress("bbarnumber", &_bbarnumber);
	T->SetBranchAddress("cnumber", &_cnumber);
	T->SetBranchAddress("cbarnumber", &_cbarnumber);
	T->SetBranchAddress("boffsettrack", _boffsettrack);
	T->SetBranchAddress("bbaroffsettrack", _bbaroffsettrack);
	T->SetBranchAddress("betatrack", _betatrack);
	T->SetBranchAddress("bbaretatrack", _bbaretatrack);
	T->SetBranchAddress("bptrack", _bptrack);
	T->SetBranchAddress("betatrack", _betatrack);
	T->SetBranchAddress("bbarptrack", _bbarptrack);
	T->SetBranchAddress("bbaretatrack", _bbaretatrack);
	T->SetBranchAddress("coffsettrack", _coffsettrack);
	T->SetBranchAddress("cbaroffsettrack", _cbaroffsettrack);
	T->SetBranchAddress("cptrack", _cptrack);
	T->SetBranchAddress("cetatrack", _cetatrack);
	T->SetBranchAddress("cbarptrack", _cbarptrack);
	T->SetBranchAddress("cbaretatrack", _cbaretatrack);

	T2->SetBranchAddress("tag", &_tag);
	T2->SetBranchAddress("bIPdistance", &_bIPdistance);
	T2->SetBranchAddress("bbarIPdistance", &_bbarIPdistance);

	int _numberOfMissed = 0;
	float _offsetMissed[MAXN];
	float _momentumMissed[MAXN];
	float _thetaMissed[MAXN];

	T3->SetBranchAddress("numberOfMissed", &_numberOfMissed);
	T3->SetBranchAddress("offsetMissed", _offsetMissed);
	T3->SetBranchAddress("momentumMissed", _momentumMissed);
	T3->SetBranchAddress("thetaMissed", _thetaMissed);
	int _numberOfMissedVtx = 0;
	int _numberOfTracksVtx[MAXN];
	float _offsetMissedVtx[MAXN];//[MAXN];
	float _momentumMissedVtx[MAXN];//[MAXN];
	float _costhetaMissedVtx[MAXN];//[MAXN];

	T5->SetBranchAddress("numberOfMissedVtx",&_numberOfMissedVtx);
	T5->SetBranchAddress("numberOfTracksMissedVtx", _numberOfTracksVtx);
	T5->SetBranchAddress("offsetOfParticlesVtx", _offsetMissedVtx);
	T5->SetBranchAddress("momentumOfParticlesVtx", _momentumMissedVtx);
	T5->SetBranchAddress("costhetaOfParticlesVtx", _costhetaMissedVtx);
	//T5->SetBranchAddress("thetaMissedVtx", _thetaMissedVtx);
	int _nprime = 0;
	float _primeDeviation[MAXN];
	T4->SetBranchAddress("primariesTotal", &_nprime);
	T4->SetBranchAddress("primeDeviation", _primeDeviation);
	cout << "mTotalNumberOfEvents: " << mTotalNumberOfEvents << '\n';
	int counter = 0;
	int num = 0;
	TFile * file = TFile::Open("TrashRecoTest.root");
	//MissedVertex->Project("sigma(offsetOfParticlesVtx, momentumOfParticlesVtx, acos(costhetaOfParticlesVtx)) >> +ep" , "offsetOfParticlesVtx > 0.0");
	for (unsigned int i = 0; i < mTotalNumberOfEvents; i += 1)
	{
		T->GetEntry(i);
		//T1->GetEntry(i);
		T2->GetEntry(i);
		T3->GetEntry(i);
		T4->GetEntry(i);
		T5->GetEntry(i);
		if (_breconumber > 15) 
		{
		//	continue;
		}
		if (!_tag) 
		{
			continue;
		}
		for (int j = 0; j < _numberOfMissedVtx; j++) 
		{
			for (int k = 0; k < _numberOfTracksVtx[j]; k++) 
			{
				if (_offsetMissedVtx[j*20+k] < -0.9) 
				{
					continue;
				}
					//cout << "Event: " << i << " i " << j << " k " << k <<" number: " << _numberOfTracksVtx[j] << " offset: " << _offsetMissedVtx[j][k] << " cos: " << _costhetaMissedVtx[j][k] << "\n";
				if (_offsetMissedVtx[j*20+k] <= 0.000000000000000) 
				{
					continue;
				}
				esmissed->Fill(sigma(_offsetMissedVtx[j*20+k], _momentumMissedVtx[j*20+k], std::acos(_costhetaMissedVtx[j*20+k])));
			}
		}
		for (int s = 0; s < _numberOfMissed; s++)
		{
			esmissed->Fill(sigma(_offsetMissed[s], _momentumMissed[s], _thetaMissed[s])); 
			lostpt->Fill(_momentumMissed[s], _offsetMissed[s]);
		}
		for (int k = 0; k < _nprime; k++) 
		{
			esprime->Fill(_primeDeviation[k]);
			//cout << "Event: " << i << " track: " << k << " p: " << _primeDeviation[k] << endl;
		}
		if (_bnumber > 0)// && _bnumber > 15) 
		{
			for (int k = 0; k < _bnumber; k++) 
			{
				goodpt->Fill(_bptrack[k], _boffsettrack[k]);
				//goodpt->Fill(_bIPdistance, _boffsettrack[k]);
				esgood->Fill(sigma(_boffsettrack[k] , _bptrack[k], _betatrack[k]));
			}
			for (int n = 0; n < _cnumber; n++) 
			{
				goodpt->Fill(_cptrack[n], _coffsettrack[n]);
				//goodpt->Fill(_bIPdistance, _coffsettrack[n]);
				esgood->Fill(sigma(_coffsettrack[n], _cptrack[n], _cetatrack[n]));
			}
		}
		if (_bbarnumber > 0)// || _bbarnumber > 15) 
		{
			for (int m = 0; m < _bbarnumber; m++) 
			{
				//goodpt->Fill(_bbarIPdistance, _bbaroffsettrack[m]);
				goodpt->Fill(_bbarptrack[m], _bbaroffsettrack[m]);
				//esgood->Fill(_bbaroffsettrack[m] / sigma(_bbarptrack[m]));
				esgood->Fill(sigma(_bbaroffsettrack[m], _bbarptrack[m], _bbaretatrack[m]));
			}
			for (int o = 0; o < _cbarnumber; o++) 
			{
				//goodpt->Fill(_bbarIPdistance, _cbaroffsettrack[o]);
				goodpt->Fill(_cbarptrack[o], _cbaroffsettrack[o]);
				esgood->Fill(sigma(_cbaroffsettrack[o], _cbarptrack[o], _cbaretatrack[o]));
			}
		}
	}
	c1->cd(1);
	TF1 *fa1 = new TF1("fa1","(x-1.57)*(x-1.57)*10+10",0,3.14);

	goodpt->GetXaxis()->SetTitle("|p_{B}|");
	goodpt->GetYaxis()->SetTitle("#epsilon");
	lostpt->GetXaxis()->SetTitle("|p_{B}|");
	lostpt->GetYaxis()->SetTitle("#epsilon");
	
	//lost->Draw("same");
	//good->Draw("same");
	gPad->SetGridy();
	gPad->SetLogy();
	gPad->SetGridx();
	esmissed->SetMarkerStyle(20);
	esmissed->SetMarkerSize(0.4);
	esprime->SetMarkerStyle(21);
	esprime->SetMarkerSize(1.0);
	esprime->SetMarkerColor(kRed);
	//esprime->Scale(esgood->GetBinContent(1)/esprime->GetBinContent(1));
	//esmissed->SetMaximum(1200);
	//esgood->SetMaximum(1200);
	esgood->SetFillColor(kGreen);
	esgood->SetLineWidth(1);
esgood->Draw("same");
	esmissed->Draw("samep");
	esprime->Draw("samep");
	TLegend *legendMean = new TLegend(0.17,0.7,0.5,0.92,NULL,"brNDC");
        legendMean->SetFillColor(kWhite);
        legendMean->SetBorderSize(0);
        legendMean->AddEntry(esgood,"generated SOT-Tracks","fp");
        legendMean->AddEntry(esmissed,"LSOT-Tracks","fp");
        legendMean->AddEntry(esprime,"primary tracks","fp");
	legendMean->Draw();
	gPad->Modified();


	//fa1->Draw("same");
	c1->cd(2);
	lostpt->SetMarkerColor(kRed);
	lostpt->SetMarkerSize(0.4);
	lostpt->SetMarkerStyle(20);
	goodpt->SetMarkerSize(0.4);
	goodpt->SetMarkerStyle(20);
	goodpt->SetMarkerColor(kBlue);
	//lostpt->SetMarkerColor(kRed);
	//lostpt->SetMarkerStyle(20);
	//TF1 *fa2 = new TF1("fa1","sqrt(0.025*0.025+0.01*0.01/x/x)",0,15);
	TF1 *fa2 = new TF1("fa1","0.001+0.1/x",0, maxp);
	//goodpt->Draw("sameCOLZ");
	lostpt->Draw("sameCOLZ");
	//goodpt->Add(lostpt, -1.0);
	//goodpt->Draw("COLZ");
	fa2->SetLineColor(kBlack);
	//fa2->Draw("same");

}
