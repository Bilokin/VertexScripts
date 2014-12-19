#define MAXN  1000
#include <iostream>
using std::cout;

void accuracy(){
	int _vertex = 0;
	int _pdg[MAXN];
	float _probability[MAXN];
	float _chi2[MAXN];
	int _generation[MAXN];

	float _bIPdistance = 0.0;
	float _bbarIPdistance = 0.0;

	float _bdistance = 0.0;
	float _bbardistance = 0.0;
	float _baccuracy = 0.0;
	float _bbaraccuracy = 0.0;
	float _caccuracy = 0.0;
	float _cbaraccuracy = 0.0;
	
	int _bnumber;
	int _bbarnumber;
	int _cnumber;
	int _cbarnumber;

	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,500);
	c1->Divide(2,1);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadColor(kWhite);
	TH1F * distanceAbove = new TH1F("da","Distance above",50,0,15.0 );
	TH1F * distanceBelow = new TH1F("db","Distance below",50,0,15.0 );
	TH1F * cdistanceAbove = new TH1F("cda","Distance above",50,0,15.0 );
	TH1F * cdistanceBelow = new TH1F("cdb","Distance below",50,0,15.0 );
	TH1F * accuracy = new TH1F("accuracy","accuracy",50,5e-3,5.5e-1 );
	TH1F * caccuracy = new TH1F("caccuracy","accuracy",50,5e-3,5.5e-1 );
	TChain* T = new TChain("Stats");
	T->Add("TrashMCTest.root");

	int mTotalNumberOfEvents = T->GetEntries();
	T->SetBranchAddress("bIPdistance", &_bIPdistance);
	T->SetBranchAddress("bbarIPdistance", &_bbarIPdistance);
	T->SetBranchAddress("bdistance", &_bdistance);
	T->SetBranchAddress("bbardistance", &_bbardistance);
	
	T->SetBranchAddress("bbaraccuracy", &_bbaraccuracy);
	T->SetBranchAddress("baccuracy", &_baccuracy);
	T->SetBranchAddress("cbaraccuracy", &_cbaraccuracy);
	T->SetBranchAddress("caccuracy", &_caccuracy);
	
	T->SetBranchAddress("bnumber", &_bnumber);
	T->SetBranchAddress("cnumber", &_cnumber);
	T->SetBranchAddress("bbarnumber", &_bbarnumber);
	T->SetBranchAddress("cbarnumber", &_cbarnumber);
	cout << "mTotalNumberOfEvents: " << mTotalNumberOfEvents << '\n';
	int counter = 0;
	int num = 0;
	for (unsigned int i = 0; i < mTotalNumberOfEvents; i += 1)
	{
		T->GetEntry(i);
		accuracy->Fill(_baccuracy);
		accuracy->Fill(_bbaraccuracy);
		caccuracy->Fill(_caccuracy);
		caccuracy->Fill(_cbaraccuracy);
		//_bnumber = 500; _bbarnumber = 500;
		//_cnumber = 500; _cbarnumber = 500;
		if (_bIPdistance > _baccuracy && _bnumber > 1 && _bnumber > -1) 
		{
			distanceAbove->Fill(_bIPdistance);
		}
		if (_bIPdistance < _baccuracy || _bnumber < 2 && _bnumber > -1) 
		{
			distanceBelow->Fill(_bIPdistance);
		}
		if (_bbarIPdistance > _bbaraccuracy && _bbarnumber > 1 && _bbarnumber > -1) 
		{
			distanceAbove->Fill(_bbarIPdistance);
		}
		if (_bbarIPdistance < _bbaraccuracy || _bbarnumber < 2 && _bbarnumber > -1) 
		{
			distanceBelow->Fill(_bbarIPdistance);
		}
		if (_bdistance > _caccuracy && _cnumber > 1 && _cnumber > -1) 
		{
			cdistanceAbove->Fill(_bdistance);
		}
		if (_bdistance < _caccuracy || _cnumber < 2 && _cnumber > -1) 
		{
			cdistanceBelow->Fill(_bdistance);
		}
		if (_bbardistance > _cbaraccuracy && _cbarnumber > 1 && _cbarnumber > -1) 
		{
			cdistanceAbove->Fill(_bbardistance);
		}
		if (_bbardistance < _cbaraccuracy || _cbarnumber < 2 && _cbarnumber > -1) 
		{
			cdistanceBelow->Fill(_bbardistance);
		}
		if (_bdistance < _caccuracy || _bbardistance < _cbaraccuracy) 
		{
			counter ++;
		}
	}
	c1->cd(1);
	distanceBelow->SetFillColor(kYellow);
	distanceBelow->GetXaxis()->SetTitle("distance, mm");
	distanceAbove->SetFillColor(kBlue);
	cdistanceBelow->SetFillColor(kYellow);
	cdistanceAbove->SetFillColor(kBlue);
	cdistanceBelow->GetXaxis()->SetTitle("distance, mm");
	accuracy->SetFillColor(kGreen);
	caccuracy->SetFillColor(kGreen);
	//distanceBelow->Draw();
	//gPad->SetLogy();accuracy->Draw();
	THStack * stack = new THStack("Distance" , "b-vertex");
	stack->Add(distanceAbove);
	stack->Add(distanceBelow);
	//gPad->SetLogy();
	stack->Draw();
	stack->GetXaxis()->SetTitle("distance, mm");
	gPad->Modified();
	c1->cd(2);
	THStack * cstack = new THStack("cDistance" , "c-vertex");
	cstack->Add(cdistanceAbove);
	cstack->Add(cdistanceBelow);
	//gPad->SetLogy();
	//gPad->SetLogy();caccuracy->Draw();
	cstack->Draw();
	std::cout << "Due to accuracy: " << counter << '\n';
	std::cout << "Fraction of detectable b-verticies: " << distanceAbove->GetEntries() / (distanceAbove->GetEntries()+distanceBelow->GetEntries()) << '\n';
	std::cout << "Fraction of detectable c-verticies: " << cdistanceAbove->GetEntries() / (cdistanceAbove->GetEntries()+cdistanceBelow->GetEntries()) << '\n';
	TLegend *legendMean = new TLegend(0.17,0.7,0.5,0.92,NULL,"brNDC");
	legendMean->SetBorderSize(0);
	legendMean->AddEntry(cdistanceAbove,"Detectable","f");
	legendMean->AddEntry(cdistanceBelow,"Invisible","f");
	legendMean->Draw();
	cstack->GetXaxis()->SetTitle("distance, mm");
	gPad->Modified();

}
