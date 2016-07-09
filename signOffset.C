void signOffset(string filename = "VertexRestorer.root")
{
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,500,500);
	TFile * file2 = TFile::Open(filename.c_str());
	int bins = 50;
	float high = 1;
	float low = -1.;
	TH1F * missedcos = new TH1F("missedcos", "; z_{0}", bins, low, high);
	TH1F * fakecos = new TH1F("fakecos", "Angle", bins, low, high);
	makePretty(missedcos, false);
	makePretty(fakecos, true);
	Stats->Draw("missedZ0 >> missedcos","missedCosthetaVtx < 0");
	Stats->Draw("fakeZ0 >> fakecos","fakeCosthetaVtx < 0", "same");
	//Stats->Draw("missedZ0 >> missedcos","missedCosthetaVtx > 0 && missedCosthetaVtx - missedCostheta > 0 && missedOffset > 0");
	//Stats->Draw("fakeZ0 >> fakecos","fakeCosthetaVtx > 0 && fakeCosthetaVtx - fakeCostheta > 0 && fakeOffset > 0", "same");
	missedcos->Draw();
	fakecos->Draw("samee");
}

void makePretty(TH1F * missed, bool fake)
{
	missed->SetMinimum(0);
	missed->SetStats(0);
	if (fake) 
	{
		missed->SetMarkerStyle(21);
		missed->SetMarkerColor(kRed);
		missed->SetMarkerSize(1.0);
	}
	else 
	{
		missed->SetLineColor(kBlue);
		missed->SetLineWidth(2);
	}
}
