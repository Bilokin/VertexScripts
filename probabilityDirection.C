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
	TH1F * probhist = new TH1F("Phi","Phi",50,0,1.0 );
	TH1F * probhist_non = new TH1F("Teta","Teta",50,0,1.0  );
	probhist_non->Sumw2();
	TH1F * chihist= new TH1F("PhiD","PhiD",50,0,30 );
	TH1F * chihist_non = new TH1F("TetaD","TetaD",50,0,30  );
	chihist_non->Sumw2();
	TChain* T = new TChain("TaggedVertices");
	T->Add("TrashRecoTest.root");

	int mTotalNumberOfEvents = T->GetEntries();
	T->SetBranchAddress("numberOfTagged", &_vertex);
	T->SetBranchAddress("PDG", _pdg);
	T->SetBranchAddress("generation", _generation);
	T->SetBranchAddress("chi2", _chi2);
	T->SetBranchAddress("probability", _probability);
	
	cout << "mTotalNumberOfEvents: " << mTotalNumberOfEvents << '\n';
	int counter = 0;
	int num = 0;
	for (unsigned int i = 0; i < mTotalNumberOfEvents; i += 1)
	{
		T->GetEntry(i);
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
	}
	boxPad->cd();
	probhist_non->SetMarkerStyle(20);
	chihist_non->SetMarkerStyle(20);
	chihist_non->SetMarkerColor(kBlack);
	chihist_non->SetMarkerSize(0.5);
	chihist_non->GetXaxis()->SetTitle("#chi^2");
	chihist->SetFillColor(kYellow);
	chihist->GetXaxis()->SetTitle("#chi^{2}");
	
	probhist_non->SetMarkerColor(kBlack);
	probhist_non->SetMarkerSize(0.5);
	probhist_non->GetXaxis()->SetTitle("P(V)");
	//probhist->GetYaxis()->SetRange(0,0.1);
	//probhist_non->GetYaxis()->SetRange(0,0.1);
	probhist->SetMaximum(80);
	probhist_non->SetMaximum(80);
	probhist->SetFillColor(kYellow);
	probhist->GetXaxis()->SetTitle("P(V)");
	probhist->DrawNormalized("same",1);
	probhist_non->DrawNormalized("ex0psame",1);
	boxPad->SetGrid();
	box1Pad->cd();
	chihist->DrawNormalized("");
	chihist_non->DrawNormalized("ex0psame",1);
	box1Pad->SetGrid();
	box1Pad->Modified();
	boxPad->Modified();
	std::cout << "Statistics: " << probhist->GetEntries() << " with ternary; " << probhist_non->GetEntries() << " without ternary; " << counter << " total\n";
	std::cout << "Mean: " << probhist->GetMean() << " with ternary; " << probhist_non->GetMean() << " without ternary;\n";
}
float getIsotropy(TH1F * histogram)
{
	float derivative = 0.0;
	int number = histogram->GetXaxis()->GetNbins();
	float dphi =(histogram->GetXaxis()->GetXmax() - histogram->GetXaxis()->GetXmin()) / (float) number;
	for (int count = 2; count < number+1; count++)
	{
	        float f1 = histogram->GetBinContent(count-1);
		float f2 = histogram->GetBinContent(count);
		derivative += (f2 - f1) / dphi;
	}
	derivative += (histogram->GetBinContent(1) - histogram->GetBinContent(number+1)) / dphi;
	cout <<"Derivative: " << derivative << '\n';
	return fabs(derivative);
}
float fit(TH1F * histogram)
{
	TCanvas * c2 = new TCanvas("c2", "fit",0,0,500,500);
	TF1 *f1 = new TF1("f1","[0]*exp(-0.5*((x-[1])/[2])^2)",0,1);
	//f1->SetParameters(1,0.25,0.03,0);
	histogram->Fit("f1","R");
	c2->cd();
	f1->Draw();
}
