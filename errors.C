void errors()
{
	TFile *_file0 = TFile::Open("Modification.root");
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,500);
	c1->Divide(2,1);
	float highe = 0.5;
	float highp = 10;
	int nbin = 2000;
	TH2F * vtx4 = new TH2F("vtx4", ";p;#sigma_{offset}",nbin,0.,highp,nbin,0.0,highe);
	TH2F * vtx6 = new TH2F("vtx6", "|cos#theta| < 0.9;p;#sigma_{offset}",nbin,0,highp,nbin,0.0,highe);
	TH2F * ftdvtx = new TH2F("ftdvtx", "|cos#theta| > 0.9;p;#sigma_{offset}",nbin,0,highp,nbin,0.0,highe);
	TH2F * ftd = new TH2F("ftd", ";p;#sigma_{offset}",nbin,0,highp,nbin,0.002,highe);
	TH2F * ftdcos =new  TH2F("ftdcos", ";|cos#theta|;#sigma_{offset}",nbin,0,1,nbin,0.0,highe); 
	TH2F * ftdvtxcos =new  TH2F("ftdvtxcos", ";|cos#theta|;#sigma_{offset}",nbin,0,1,nbin,0.0,highe); 
	c1->cd(1);
	vtx4->SetMarkerColor(kRed);
	ftdvtx->SetMarkerColor(kRed);
	ftdcos->SetMarkerColor(kRed);
	Stats->Draw("sigmaOffset:momentum >> vtx6","sigmaOffset >0 && sigmaOffset < 0.5 && momentum < 10 && abs(costheta) < 0.9 && vtxHits == 6");
	Stats->Draw("sigmaOffset:momentum >> vtx4","sigmaOffset >0 && sigmaOffset < 0.5 && momentum < 10 && abs(costheta) < 0.9 && vtxHits == 4","same");
	c1->cd(2);
	//Stats->Draw("sigmaOffset:momentum >> ftdvtx","sigmaOffset > 0 && sigmaOffset < 0.5 && momentum < 10 && abs(costheta) > 0.9 && vtxHits == 4","");
	//Stats->Draw("sigmaOffset:momentum >> ftd","sigmaOffset > 0 && sigmaOffset < 0.5 && momentum < 10 && abs(costheta) > 0.9 && ftdHits > 0","same");
	Stats->Draw("sigmaOffset:abs(costheta)>>ftdvtxcos","sigmaOffset > 0 && sigmaOffset < 0.5 && momentum > 10 && momentum < 110.5 && abs(costheta) > 0. && vtxHits >3","");
	Stats->Draw("sigmaOffset:abs(costheta)>>ftdcos","sigmaOffset > 0 && sigmaOffset < 0.5 && momentum > 10 && momentum < 110.5 && abs(costheta) > 0. && vtxHits == 0 && ftdHits > 2 && abs(radius*costheta/sqrt(1-costheta * costheta)) < 230","same");
	//Stats->Draw("sigmaOffset:abs(costheta)>>ftdcos","sigmaOffset > 0 && sigmaOffset < 0.5 && momentum > 10 && momentum < 110.5 && abs(costheta) > 0. && vtxHits == 0 && ftdHits > 1","same");
	//vtx6->Draw("");
}

