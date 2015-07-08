void jetanalysis()
{
	TFile * file = TFile::Open("TrashRecoTest.root");
	int bin_e = 30;
	float max_a = 1.5;
	int max_p = 15;
	TCanvas * c1 = new TCanvas("c1", "Jets",0,0,1000,500);
	c1->Divide(2,1);
	c1->cd(1);
	TH2F* h2 = new TH2F("h2","Phase space of missed;#alpha_{jet};|p_{prong}|",bin_e,0.,max_a,bin_e,0.,max_p);
	Jets->Project("h2","pJetParticles:alphaJetParticles","btags > 0.3 && alphaJetParticles > 0.0 && abs(mcpdg) > -1 && numberOfVertices > -1 && typeJetParticles > 0 && prongJetParticles > 0");
	h2->Draw("COLZ");
	c1->cd(2);
	TH2F* h3 = new TH2F("h3","Phase space of primary;#alpha_{jet};|p_{bkg}|",bin_e,0.,max_a,bin_e,0.,max_p);
	Jets->Project("h3","pJetParticles:alphaJetParticles","btags > 0.3 &&alphaJetParticles > 0.0 && abs(mcpdg) > 1 && numberOfVertices > -1 && typeJetParticles > 0 && prongJetParticles == 0");
	h3->Draw("COLZ");
}
