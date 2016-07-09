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
	TaggedVertices->Draw("errorOfParticles:momentumOfParticles >> vtx6","errorOfParticles >0 && errorOfParticles < 0.5 && momentumOfParticles < 10 && abs(costhetaOfParticles) < 0.9 && vtxHitsOfParticles == 6");
	TaggedVertices->Draw("errorOfParticles.:momentumOfParticles >> vtx4","errorOfParticles >0 && errorOfParticles < 0.5 && momentumOfParticles < 10 && abs(costhetaOfParticles) < 0.9 && vtxHitsOfParticles == 4","same");
	c1->cd(2);
	//TaggedVertices->Draw("errorOfParticles:momentumOfParticles >> ftdvtx","errorOfParticles > 0 && errorOfParticles < 0.5 && momentumOfParticles < 10 && abs(costhetaOfParticles) > 0.9 && vtxHitsOfParticles == 4","");
	//TaggedVertices->Draw("errorOfParticles:momentumOfParticles >> ftd","errorOfParticles > 0 && errorOfParticles < 0.5 && momentumOfParticles < 10 && abs(costhetaOfParticles) > 0.9 && ftdHitsOfParticles > 0","same");
	TaggedVertices->Draw("errorOfParticles:abs(costhetaOfParticles)>>ftdvtxcos","errorOfParticles > 0 && errorOfParticles < 0.5 && momentumOfParticles > 10 && momentumOfParticles < 110.5 && abs(costhetaOfParticles) > 0. && vtxHitsOfParticles >3","");
	//TaggedVertices->Draw("errorOfParticles:abs(costhetaOfParticles)>>ftdcos","errorOfParticles > 0 && errorOfParticles < 0.5 && momentumOfParticles > 10 && momentumOfParticles < 11.5 && abs(costhetaOfParticles) > 0. && vtxHitsOfParticles == 0 && ftdHitsOfParticles > 1 && abs(rHitOfParticles*costhetaOfParticles/sqrt(1-costhetaOfParticles * costhetaOfParticles)) < 230","same");
	TaggedVertices->Draw("errorOfParticles:abs(costhetaOfParticles)>>ftdcos","errorOfParticles > 0 && errorOfParticles < 0.5 && momentumOfParticles > 10 && momentumOfParticles < 110.5 && abs(costhetaOfParticles) > 0. && vtxHitsOfParticles == 0 && ftdHitsOfParticles > 5","same");
	//vtx6->Draw("");
}

