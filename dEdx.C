void dEdx(string recofilename = "RecoTest.root")
{
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,500);
	c1->Divide(2,1);
	TFile *_file0 = TFile::Open(recofilename.c_str());
	int nbins = 1000;
	float maxp = 80;
	float maxcos = 1;
	float maxs = 3e-7;
	float maxes = 3e-9;
	float mins = 1e-7;
	c1->cd(1);
	TH2F * pip = new TH2F("pip",";p [GeV];dE/dx, [GeV/mm]",nbins,0,maxp ,nbins, mins, maxs);
	TH2F * prp = new TH2F("prp",";p [GeV];#frac{dE}{dx}, [GeV/mm]",nbins,0,maxp ,nbins, mins, maxs);
	TH2F * ep = new TH2F("ep",";p [GeV];#frac{dE}{dx}, [GeV/mm]",nbins,0,maxp ,nbins, mins, maxs);
	TH2F * ep = new TH2F("mup",";p [GeV];#frac{dE}{dx}, [GeV/mm]",nbins,0,maxp ,nbins, mins, maxs);
	TH2F * kp = new TH2F("kp","",nbins,0,maxp ,nbins, mins, maxs);
	TH2F * picos = new TH2F("picos",";|cos#theta|;dE/dx, [GeV/mm]",nbins,0,maxcos ,nbins, mins, maxs);
	TH2F * kcos = new TH2F("kcos","",nbins,0,maxcos ,nbins, mins, maxs);
	TH2F * pcos = new TH2F("pcos","",nbins,0,maxcos ,nbins, mins, maxs);
	TH1F * ko = new TH1F("ko",";offset [mm]",nbins, 0, 6);
	TH1F * po = new TH1F("po",";offset [mm]",nbins, 0, 6);
	makePretty(pip,kRed);
	makePretty(prp,kRed+1);
	makePretty(ep,kBlack);
	makePretty(mup,kBlack);
	makePretty(kp,kBlue);
	makePretty(picos,kRed);
	makePretty(kcos,kBlue);
	makePretty(pcos,kRed+1);
	pip->GetYaxis()->SetTitleOffset(1.7);
	if (recofilename == "RecoTest.root") 
	{
		int npions = TaggedVertices->Draw("dEdxOfParticles*pow(acos(abs(costhetaOfParticles)),0.15):momentumOfParticles >> pip","dEdxOfParticles > 0 && abs(trueTypeOfParticles) == 211  && generation ","");
		int nprotons = TaggedVertices->Draw("dEdxOfParticles*pow(acos(abs(costhetaOfParticles)),0.15):momentumOfParticles >> prp","dEdxOfParticles > 0 && abs(trueTypeOfParticles) == 2212&& generation","");
		int nkaons = TaggedVertices->Draw("dEdxOfParticles*pow(acos(abs(costhetaOfParticles)),0.15):momentumOfParticles >> kp","dEdxOfParticles > 0 && abs(trueTypeOfParticles) == 321 && generation ","");
	}
	if (recofilename == "pid.root") 
	{
		int npions = Stats->Draw("dEdx:momentum >> pip","dEdx > 0 && abs(trueType) == 211","");
		int nprotons = Stats->Draw("dEdx:momentum >> prp","dEdx > 0 && abs(trueType) == 2212","");
		int nkaons = Stats->Draw("dEdx:momentum >> kp","dEdx > 0 && abs(trueType) == 321","");
	}
	cout << "Nkaons: " << nkaons << " nprotons: "<< nprotons << " npions: " << npions << endl;
	gPad->SetLogx();
	TF1 * f1 = new TF1("f1","1.9e-08*log(x)+1.25e-07",0, maxp);
	TF1 * f2 = new TF1("f2","1.9e-08*log(x)+1.07e-07",0, maxp);
	f1->SetLineColor(kGray);
	f2->SetLineColor(kGray);
	pip->Draw();
	prp->Draw("same");
	kp->Draw("same");
	f1->Draw("same");
	f2->Draw("same");
	TLegend *legendMean = new TLegend(0.2,0.85,0.25,0.7,NULL,"brNDC");
        legendMean->SetFillColor(kWhite);
        legendMean->SetBorderSize(1);
        legendMean->AddEntry(pip,"#pi","p");
        legendMean->AddEntry(kp,"K","p");
        legendMean->AddEntry(prp,"p","p");
	legendMean->Draw();
	if (recofilename == "pid.root") 
	{
		return;
	}
	c1->cd(2);
	picos->GetYaxis()->SetTitleOffset(1.4);

	TaggedVertices->Draw("dEdxOfParticles*pow(acos(abs(costhetaOfParticles)),0.15):costhetaOfParticles >> picos","errordEdxOfParticles > 0 && abs(trueTypeOfParticles) == 211","");
	TaggedVertices->Draw("dEdxOfParticles*pow(acos(abs(costhetaOfParticles)),0.15):costhetaOfParticles >> kcos","errordEdxOfParticles > 0 && abs(trueTypeOfParticles) == 321","");
	TaggedVertices->Draw("dEdxOfParticles*pow(acos(abs(costhetaOfParticles)),0.15):costhetaOfParticles >> pcos","errordEdxOfParticles > 0 && abs(trueTypeOfParticles) == 2212","");
	gPad->Modified();
	TaggedVertices->Draw("offsetOfParticles >> ko" , "momentumOfParticles > 0 &&  abs(trueTypeOfParticles) == 321 && generation == 3 && isProngOfParticles == 1");
	TaggedVertices->Draw("offsetOfParticles >> po" , "momentumOfParticles > 0 &&  abs(trueTypeOfParticles) == 211 && generation == 3 && isProngOfParticles == 1");
	picos->Draw();
	pcos->Draw("same");
	kcos->Draw("same");
	makePretty(ko, kBlue);
	makePretty(po,kRed);
	//ko->DrawNormalized();
	//po->DrawNormalized("same");
	TLegend *legendMean1 = new TLegend(0.57,0.7,0.85,0.85,NULL,"brNDC");
        legendMean1->SetFillColor(kWhite);
        legendMean1->SetBorderSize(0);
        legendMean1->AddEntry(po,"#pi","l");
        legendMean1->AddEntry(ko,"K","l");
	legendMean1->Draw();
}
void makePretty(TH2F * p, int color)
{
	p->SetStats(0);
	p->SetMarkerColor(color);	
	p->SetMarkerStyle(20);
	p->SetMarkerSize(0.2);
}
void makePretty(TH1F * missed,  int color)
{
	missed->SetMinimum(0);
	missed->SetStats(0);
	missed->SetLineColor(color);
	missed->SetLineWidth(2);
}
