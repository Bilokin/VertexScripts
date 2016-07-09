#include <sstream>
void eventCharge()
{
	int bin_e = 5;
	int qlow = -2;
	int qhigh = 3;
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,500);
	c1->Divide(2,1);
	TFile * file = TFile::Open("RecoTest.root");	
	TH2F * thcharge = new TH2F("thcharge", ";bbarcharge;bcharge", bin_e,qlow,qhigh, bin_e,qlow,qhigh);
	TH2F * thchargegood = new TH2F("thchargegood", ";bbarcharge;bcharge", bin_e,qlow,qhigh, bin_e,qlow,qhigh);
	TH2F * thchargebad = new TH2F("thchargebad", ";bbarcharge;bcharge", bin_e,qlow,qhigh, bin_e,qlow,qhigh);
	TH2F * thevent = new TH2F("thevent", ";Reconstructed;Generated", 6,0,6, 6,0,6);
	int __bbargencharge = 0;
	int __bgencharge = 0;
	int bcharge = 0;
	int bbarcharge = 0;
	float btag = 0;
	float bbartag = 0;
	Stats->SetBranchAddress("btag",&btag);
	Stats->SetBranchAddress("bbartag",&bbartag);
	Stats->SetBranchAddress("bcharge",&bcharge);
	Stats->SetBranchAddress("bbarcharge",&bbarcharge);
	Stats->SetBranchAddress("__bbargencharge",&__bbargencharge);
	Stats->SetBranchAddress("__bgencharge",&__bgencharge);
	int mTotalNumberOfEvents = Stats->GetEntries();
	int totalcounter = 0;
	int diagonal = 0;
	for (int i = 0; i < mTotalNumberOfEvents; i++) 
	{
		Stats->GetEntry(i);
		if (abs(bcharge) < 2 && abs(bbarcharge) < 2) 
		{
			totalcounter++;
			//cout << "i: " << getIndex(bcharge,bbarcharge) << endl;
			thevent->Fill(getIndex(bcharge,bbarcharge), getIndex(__bgencharge,__bbargencharge));
			if (getIndex(bcharge,bbarcharge) == getIndex(__bgencharge,__bbargencharge)) 
			{
				diagonal++;
			}
		}

	}
	Stats->Project("thcharge",
		"bcharge:bbarcharge",
		" bcharge > -4 && bbarcharge > -4 && (bbartag > .8 && btag > 0.3 || bbartag > .3 && btag > 0.8)");
	//	" bcharge > -4 && bbarcharge > -4");
	Stats->Project("thchargegood",
		"bcharge:bbarcharge",
		" bcharge > -4 && bbarcharge > -4 && (bbartag > .8 && bbartag > 0.3 || bbartag > .3 && bbartag > 0.8) && (bnumber == __bgennumber && bbarnumber == __bbargennumber)");
	Stats->Project("thchargebad",
		"bcharge:bbarcharge",
		" bcharge > -4 && bbarcharge > -4 && (bbartag > .8 && bbartag > 0.3 || bbartag > .3 && bbartag > 0.8) && (bnumber < __bgennumber && bbarnumber < __bbargennumber)");
	
	//Stats->Project("thevent",
	//	"((__bbargencharge) -2 *(__bgencharge)):((bbarcharge) - 2*(bcharge)) ",
		//"(0):(bbarcharge - 2*bcharge) ",
	//	" abs(bcharge) < 2 && abs(bbarcharge) < 2 && (bbartag > .8 && btag > 0.3 || bbartag > .3 && btag > 0.8) && __bbargencharge > -2 && __bbargencharge > -2");
	//thcharge->Scale(100./thcharge->GetEntries());
	thchargegood->Divide(thcharge);
	thchargebad->Divide(thcharge);
	makePretty(thevent, 9);
	makePretty(thcharge);
	makePretty(thchargegood);
	makePretty(thchargebad);
	cout << "-------------------------\n";
	cout << "q1 = q2 = 0 (Not used): " << getF(0, 0, thcharge) << "%\n";
	cout << "-------------------------\n";
	cout << "q1 + q2 = 1: " << getF(0, -1, thcharge) + getF(1, 0, thcharge) +getF(-1, 0, thcharge) + getF(0, 1, thcharge) << "%, purity: " << (getF(0, -1, thcharge) + getF(1, 0, thcharge) )/ (getF(0, -1, thcharge) + getF(1, 0, thcharge) + getF(-1, 0, thcharge) + getF(0, 1, thcharge)) << endl;
	cout << "q1 + q2 = 0: " << getF(1, -1, thcharge) + getF(-1, 1, thcharge) << "%, purity: " << (getF(1, -1, thcharge) )/ (getF(1, -1, thcharge) + getF(-1, 1, thcharge)) << endl;
	cout << "q1 + q2 = 2: " << getF(1, 1, thcharge) + getF(-1, -1, thcharge) << "%\n";
	cout << "-------------------------\n";
	cout << "-------------------------\n";
	cout << "Diagonal: " << diagonal << "(" << (float)diagonal/totalcounter * 100 << "%)\n" ;
	//thevent->GetXaxis()->SetBinLabel(1,"label");
	setLabels(thevent);
	c1->cd(1);
	gPad->SetGrid();
	thchargegood->Draw("text");
	thcharge->Draw("text");
	c1->cd(2);
	gPad->SetGrid();
	thevent->Draw("text");
	//thchargebad->Draw("text");
}
void setLabels(TH2F * thevent, int bin_e = 6)
{
	for (int i = 0; i < 3; i++) 
	{
		int q = i-1;
		stringstream s;
		s << q << -1;
		cout << s.str() << endl;
		thevent->GetXaxis()->SetBinLabel(i+1,s.str().c_str());
		thevent->GetYaxis()->SetBinLabel(i+1,s.str().c_str());
	}
	thevent->GetXaxis()->SetBinLabel(4,"10");
	thevent->GetYaxis()->SetBinLabel(4,"10");
	thevent->GetXaxis()->SetBinLabel(5,"00");
	thevent->GetYaxis()->SetBinLabel(5,"00");
	thevent->GetXaxis()->SetBinLabel(6,"11");
	thevent->GetYaxis()->SetBinLabel(6,"11");

}
void makePretty(TH2F * thcharge, int bin_e = 5)
{
	//thcharge->Scale(100.);
	thcharge->SetMarkerSize(1.5);
	thcharge->SetStats(0);
	thcharge->GetXaxis()->CenterLabels();
	thcharge->GetYaxis()->CenterLabels();
	thcharge->GetYaxis()->SetNdivisions(100 + bin_e);
	thcharge->GetXaxis()->SetNdivisions(100 + bin_e);
	for (int i = 1; i < bin_e+1; i++) 
	{
		for (int j = 1; j < bin_e+1; j++) 
		{
			thcharge->SetBinContent(i,j, TMath::Nint(thcharge->GetBinContent(i,j)*10.) / 10. );
		}
	}
}
int getIndex(int bcharge, int bbarcharge)
{
	//int i = ((float)bcharge)/abs(bcharge) + 1;
	//int j = ((float)bbarcharge)/abs(bbarcharge) + 1;
	int i = bcharge + 1;
	int j = bbarcharge + 1;

	int index = (i == 1 && j == 1)? 4 : i + j;
	index = (i == 2 && j == 2)? 5 : index;
	return index;
}
float getF(int bbarcharge, int bcharge, TH2F * thcharge)
{
	return thcharge->GetBinContent(q(bbarcharge),q(bcharge));
}
int q(int i) { return i + 3;}
