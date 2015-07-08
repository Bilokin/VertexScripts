void purity()
{
	TFile * file2 = TFile::Open("VertexRestorer.root");
	int nbin = 25;
	float maxangle = .10;
	float maxdev = 10;
	TH2F * rec = new TH2F("rec", "missed;#alpha;#epsilon/#sigma", nbin,0,maxangle,nbin,0,maxdev );
	TH2F * fake = new TH2F("fake", "fake;#alpha;#epsilon/#sigma", nbin,0,maxangle,nbin,0,maxdev );
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,1200,500);
	c1->Divide(3,1);
	c1->cd(1);
	Stats->Project("rec","missedDeviation:missedAngle","");
	rec->Draw("colz");
	c1->cd(2);
	TF1 * f = new TF1("func", "8.0*sqrt(x-0.001)",0,maxangle);
	//TF1 * f = new TF1("func", "1.2*log(50.0*(x+0.02))",0,maxangle);
	Stats->Project("fake","fakeDeviation:fakeAngle","");
	fake->Draw("colz");
	TH2F * purity = new TH2F("purity", "purity map;#alpha;#epsilon/#sigma", nbin,0,maxangle,nbin,0,maxdev );
	TH2F * efficiency = new TH2F("efficiency", "efficiency map;#alpha;#epsilon/#sigma", nbin,0,maxangle,nbin,0,maxdev );
	int fakesum = 0;
	int recsum = 0;
/*
	for (int i = 0; i < nbin; i++) 
	{
		for (int j = nbin-1; j > -1; j--) 
		{
			int nfake = fake->GetBinContent(i+1,j+1);
			int nrec = rec->GetBinContent(i+1,j+1);
			fakesum += nfake;
			recsum += nrec;
			std::cout << "fake: " << nfake 
				  << " fakesum: " << fakesum 
				  << " rec: " << nrec
				  << " recsum: " << recsum 
				  <<  '\n';
			float content = (nfake+nrec > 0)? (float)recsum/(float)(fakesum+recsum)*100.0 : 0;
			purity->SetBinContent(i+1,j+1, (int)content);
		}
	}*/
	int recsume = 0;
	for (int i = 0; i < nbin; i++) 
	{
		for (int j = nbin-1; j > -1; j--) 
		{
			int nrec = rec->GetBinContent(i+1,j+1);
			recsume += nrec; 
			float content = (recsum > 0)? (float)recsume/(float)(recsum)*100.0 : 0;
			efficiency->SetBinContent(i+1,j+1, (int)content);
		}
	}
	string option = "colz";
	c1->cd(3);
	//efficiency->Draw(option.c_str());
	TF1 * f1 = new TF1("f","15*sqrt(x)+0.5",0,0.1);
	//c1->cd(4);
	purity->Divide(rec,fake);
	purity->Draw(option.c_str());
	f1->Draw("same");
	//f->Draw("same");

}
