#define MAXN  100000
#include <iostream>
using std::cout;

void splitVtx(){
	int _vertex = 0;
	int _pdg[MAXN];
	int _status[MAXN];
	float _probability[MAXN];
	float _angle[MAXN];
	float _chi2[MAXN];
	int _generation[MAXN];
	int _number[MAXN];
	float _offsets[MAXN];
	float _momentums[MAXN];
	float _alphas[MAXN];
	
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,500,500);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadColor(kWhite);
	c1->Divide(2,2);
	/*TPad *boxPad  = new TPad("box", "box", 0.02, 0.02, 0.48, 0.92);
	TPad *box1Pad = new TPad("box1", "box1", 0.52, 0.02, 0.98, 0.92);
	boxPad->Draw();
	box1Pad->Draw();*/
	int nbins = 200;
	float maxd = 1;
	TH1F * offsethist = new TH1F("Pw","",nbins, 0, maxd );
	TH1F * offsethist2 = new TH1F("Pw2","",nbins, 0, maxd );
	TChain* T = new TChain("TaggedVertices");
	T->Add("RecoTest.root");
	TChain* T2 = new TChain("Stats");
	T2->Add("MCTest.root");

	float _bdistance = 0.0;
	float _bbardistance = 0.0;

	T2->SetBranchAddress("bdistance", &_bdistance);
	T2->SetBranchAddress("bbardistance", &_bbardistance);

	int mTotalNumberOfEvents = T->GetEntries();
	T->SetBranchAddress("numberOfTagged", &_vertex);
	T->SetBranchAddress("PDG", _pdg);
	T->SetBranchAddress("generation", _generation);
	T->SetBranchAddress("angle", _angle);
	T->SetBranchAddress("chi2", _chi2);
	T->SetBranchAddress("status", _status);
	T->SetBranchAddress("probability", _probability);
	T->SetBranchAddress("numberOfParticles", _number);
	T->SetBranchAddress("offsetOfParticles", _offsets);
	T->SetBranchAddress("momentumOfParticles", _momentums);
	T->SetBranchAddress("angleOfParticles", _alphas);
	
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
			//if (_status[j] == 2) 
			{
				if (_number[j] > 4) 
				{
					float sum = 0;
					for (int k = 0; k < _number[j]; k++) 
					{
						//if (sin( _alphas[j][k]) == 0) 
						{
							//continue;
						}
						//cout << "Value: " <<  cos( _alphas[j][k]) << endl;
						float sin = sqrt(1-cos( _alphas[j*15+k])*cos( _alphas[j*15+k]));
						sum +=exp(_offsets[j*15+k] / _momentums[j*15+k]);
						//offsethist->Fill(_offsets[j][k]);
					}
					for (int k = 0; k < _number[j]; k++) 
					{
						//if (sin( _alphas[j][k]) == 0) 
						{
							//continue;
						}
						float sin = sqrt(1-cos( _alphas[j*15+k])*cos( _alphas[j*15+k]));
						if (_status[j] == 2) 
						{
							offsethist->Fill(exp(_offsets[j*15+k]/ _momentums[j*15+k])/sum);
						}
						if (_status[j] == 3) 
						{
							offsethist2->Fill(exp(_offsets[j*15+k] / _momentums[j*15+k])/sum);
						}
					}
					break;
					//offsethist->Fill(sum/_number[j]);
				}
			}
		}
		if (offsethist->GetEntries() > 1) 
		{
			//break;
		}
		//break;
	}
	
	//c1->cd(1);
	offsethist->Draw();
	offsethist2->SetLineColor(kBlue);
	offsethist2->Draw("same");
}

