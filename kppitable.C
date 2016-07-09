void kppitable(string recofilename = "RecoTest.root")
{
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,500,500);
	TFile *_file0 = TFile::Open(recofilename.c_str());
	TH2F * table = new TH2F("table",";Reconstructed;Generated", 3, 0, 3,3,0,3);
	//if (recofilename == "RecoTest.root") 
	{
		int pipi = TaggedVertices->Draw("momentumOfParticles","momentumOfParticles >0 && abs(trueTypeOfParticles == 211) && abs(pidTypeOfParticles) == 211 ");
		int pik = TaggedVertices->Draw("momentumOfParticles","momentumOfParticles >0 && abs(trueTypeOfParticles == 211) && abs(pidTypeOfParticles) == 321 ");
		int pip = TaggedVertices->Draw("momentumOfParticles","momentumOfParticles >0 && abs(trueTypeOfParticles == 211) && abs(pidTypeOfParticles) == 2212");

		int kk = TaggedVertices->Draw("momentumOfParticles","momentumOfParticles >0 && abs(trueTypeOfParticles == 321) && abs(pidTypeOfParticles) == 321 ");
		int kpi = TaggedVertices->Draw("momentumOfParticles","momentumOfParticles >0 && abs(trueTypeOfParticles == 321) && abs(pidTypeOfParticles) == 211");
		int kp = TaggedVertices->Draw("momentumOfParticles","momentumOfParticles >0 && abs(trueTypeOfParticles == 321) && abs(pidTypeOfParticles) == 2212");

		int pp = TaggedVertices->Draw("momentumOfParticles","momentumOfParticles >0 && abs(trueTypeOfParticles == 2212) && abs(pidTypeOfParticles) == 2212");
		int ppi = TaggedVertices->Draw("momentumOfParticles","momentumOfParticles >0 && abs(trueTypeOfParticles == 2212) && abs(pidTypeOfParticles) == 211");
		int pk = TaggedVertices->Draw("momentumOfParticles","momentumOfParticles >0 && abs(trueTypeOfParticles == 2212) && abs(pidTypeOfParticles) == 321 ");
		
	}
	if (recofilename == "pid.root") 
	{
		int pipi = Stats->Draw("momentum","momentum>0 && abs(trueType == 211) && abs(tagType) == 211 ");
		int pik = Stats->Draw("momentum","momentum>0 && abs(trueType == 211) && abs(tagType) == 321 ");
		int pip = Stats->Draw("momentum","momentum>0 && abs(trueType == 211) && abs(tagType) == 2212 ");
		cout << pipi << endl;
		int kk = Stats->Draw("momentum","momentum>0 && abs(trueType == 321) && abs(tagType) == 321 ");
		int kpi = Stats->Draw("momentum","momentum>0 && abs(trueType == 321) && abs(tagType) == 211 ");
		int kp = Stats->Draw("momentum","momentum>0 && abs(trueType == 321) && abs(tagType) == 2212 ");
		
		int pp = Stats->Draw("momentum","momentum>0 && abs(trueType == 2212) && abs(tagType) == 2212 ");
		int pk = Stats->Draw("momentum","momentum>0 && abs(trueType == 2212) && abs(tagType) == 321 ");
		int ppi = Stats->Draw("momentum","momentum>0 && abs(trueType == 2212) && abs(tagType) == 211 ");
	}
	table->SetBinContent(1,1, pipi);
	table->SetBinContent(2,1, pik);
	table->SetBinContent(3,1, pip);

	table->SetBinContent(1,2, kpi);
	table->SetBinContent(2,2, kk);
	table->SetBinContent(3,2, kp);

	table->SetBinContent(1,3, ppi);
	table->SetBinContent(2,3, pk);
	table->SetBinContent(3,3, pp);
	format(table);
	cout << "Kaon purity: " << (float)kk/(pik+kk+pk)*100 << "% efficiency: " << (float)kk/(kk+kpi+kp)*100 << "%\n";
	table->Draw("text");
}
void format(TH2 * table)
{
	table->SetStats(0);
	gPad->SetGridx();
	gPad->SetGridy();
	table->SetMarkerSize(1.5);
	table->GetXaxis()->CenterLabels();
	table->GetYaxis()->CenterLabels();
	table->GetYaxis()->SetNdivisions(110);
	table->GetXaxis()->SetNdivisions(110);
	table->GetXaxis()->SetLabelSize(0.05);
	table->GetYaxis()->SetLabelSize(0.05);
	table->GetXaxis()->SetBinLabel(1,"#pi");
	table->GetXaxis()->SetBinLabel(2,"K");
	table->GetXaxis()->SetBinLabel(3,"p");
	table->GetYaxis()->SetBinLabel(1,"#pi");
	table->GetYaxis()->SetBinLabel(2,"K");
	table->GetYaxis()->SetBinLabel(3,"p");
}
