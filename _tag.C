#define MAXN  1000
void _tag()
{
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,500);
	c1->Divide(2,1);
	TChain* T2 = new TChain("Stats");
	T2->Add("TrashMCTest.root");

	TChain* T = new TChain("Primaries");
	T->Add("VertexRestorer.root");
	
	float _primeCostheta[MAXN];
	int _tag = 0;
	int _primariesTotal = 0;

	T2->SetBranchAddress("tag", &_tag);
	T->SetBranchAddress("primariesTotal", &_primariesTotal);
	T->SetBranchAddress("primeCostheta", &_primeCostheta);

	int mTotalNumberOfEvents = T2->GetEntries();
	int nbins = 30;
	int maxd = 1;
	TH1F * probhist = new TH1F("Pw","# of tracks comparison",nbins,-1,maxd);
	TH1F * taghist = new TH1F("Pw","# of tracks comparison",nbins,-1,maxd);
	for (int i = 0; i < mTotalNumberOfEvents; i++) 
	{
		T2->GetEntry(i);
		T->GetEntry(i);
		if (_tag == 0) 
		{
			for (int j = 0; j < _primariesTotal; j++) 
			{
				probhist->Fill(_primeCostheta[j]);
			}
		}
		else 
		{
			for (int j = 0; j < _primariesTotal; j++) 
			{
				taghist->Fill(_primeCostheta[j]);
			}
		}
	
	}
	c1->cd(1);
	THStack * stack = new THStack("d",";cos");
	stack->Add(probhist);
	stack->Add(taghist);
	probhist->SetLineWidth(3);
	//probhist->SetFillColor(kBlue);
	taghist->SetLineWidth(3);
	taghist->SetLineColor(kYellow+1);
	//taghist->SetFillColor(kYellow);
	probhist->Draw();
	taghist->Draw("same");
	stack->Draw();
	c1->cd(2);
	TFile * file = TFile::Open("TrashRecoTest.root");
	file->cd();
	TTree * tree = Jets;
	TH1F * bhist = new TH1F("bhist","# of tracks comparison",nbins,-1,maxd);
	TH1F * bbarhist = new TH1F("bbarhist","# of tracks comparison",nbins,-1,maxd);
	TH1F * whist = new TH1F("whist",";cos#theta",nbins,-1,maxd);
	tree->Project("bhist", "costhetaJetParticles", "costhetaJetParticles > -1 && mcpdg < 0");
	tree->Project("bbarhist", "costhetaJetParticles", "costhetaJetParticles > -1 && mcpdg > 0");
	tree->Project("whist", "costhetaJetParticles", "costhetaJetParticles > -1 && mcpdg == 0");
	whist->SetLineWidth(3);
	whist->SetLineColor(kBlue);
	whist->SetMinimum(0);
	whist->Draw("same");
	bhist->SetLineWidth(3);
	bhist->SetLineColor(kGreen);
	bhist->Draw("same");
	bbarhist->SetLineWidth(3);
	bbarhist->SetLineColor(kRed);
	bbarhist->Draw("same");
	TLegend *legendMean = new TLegend(0.17,0.7,0.5,0.92,NULL,"brNDC");
	legendMean->SetFillColor(kWhite);
	legendMean->SetBorderSize(0);
	legendMean->AddEntry(bhist,"b-jet","fp");
	legendMean->AddEntry(bbarhist,"#bar{b}-jet","fp");
	legendMean->AddEntry(whist,"w-jets","fp");
	legendMean->Draw();
	gPad->Modified();

}
