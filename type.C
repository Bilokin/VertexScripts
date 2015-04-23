void type()
{
	
	int bin_e = 50;
	int max_e = 1;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * all = new TH1F("all2", "E(Ntracks)", bin_e,0.0,max_e);
	TH1F * missed = new TH1F("missed2", "E(Ntracks)", bin_e,0.0,max_e);
	missed->SetFillColor(kRed);
	TFile * fileMC = TFile::Open("TrashMCTest.root");
	TTree * vertex = Vertices;
	vertex->Draw("massOfParticles >> all2", "massOfParticles > 0.0" ,"same");// ,"massOfParticles > 0.0");//, "same");
	all2->Draw();
	TFile * fileR = TFile::Open("TrashRecoTest.root");
	TTree * normaltree = MissedTracks;
	normaltree->Draw("massMissed >> missed2" ,"massMissed > 0.0", "hsame");
	missed2->Draw("same");
	TEfficiency * eff = NULL;
	if (TEfficiency::CheckConsistency(*missed2, *all2)) 
	{
		std::cout <<"here";
		eff = new TEfficiency(*missed2, *all2);
	}//*/
	eff->SetTitle("Fraction of lost particles;m,GeV;\%");
	//eff->Draw("AP");
}
