void precision(string observable = "precisionT", string filename = "RecoTest.root")
{
	TCanvas * c = new TCanvas("canvas", "Data-MC",0,0,500,500);
	int bin = 50;
	float high = 1;
	float middle = 0.9;
	float low = 0.;
	TFile * file = TFile::Open(filename.c_str());
	TH1F * forward = new TH1F("forward",";gen difference [mm]",bin,low,high);
	TH1F * barrel = new TH1F("barrel",";precision [mm]",bin,low,high);
	TaggedVertices->Project("barrel",observable.c_str(), "precision < 10. && precision > 0 && abs(costhetaVtx) < 0.9");
	//MissedTracks->Project("barrel", observable.c_str(), "deltapMissed < 10. && deltapMissed > 0 && abs(costhetaMissed) < 0.9");
	//MissedTracks->Project("barrel", observable.c_str(), "momentumMissed < 100. && momentumMissed > 0 && abs(costhetaMissed) < 0.9");
	//TaggedVertices->Project("barrel", observable.c_str(), "deltapOfParticles < 10. && deltapOfParticles > 0 && abs(costhetaOfParticles) < 0.9");
	makePretty(barrel,kGreen, "precision [mm]");
	makePretty(barrel,kGreen, "#Delta p/p^{2}");
	TaggedVertices->Project("forward", observable.c_str(), "precision < 10. && precision > 0 && abs(costhetaVtx) > 0.9 && abs(costhetaVtx) < 0.98");
	//MissedTracks->Project("forward", observable.c_str(), "deltapMissed < 10. && deltapMissed > 0 && abs(costhetaMissed) > 0.9 && abs(costhetaMissed) < 0.99");
	//MissedTracks->Project("forward", observable.c_str(), "momentumMissed < 10. && momentumMissed > 0 && abs(costhetaMissed) > 0.9 && abs(costhetaMissed) < 0.99");
	//TaggedVertices->Project("forward", observable.c_str(), "deltapOfParticles < 10. && deltapOfParticles > 0 && abs(costhetaOfParticles) > 0.9 && abs(costhetaOfParticles) < 0.99");
	makePretty(forward,kRed);
	cout << "Mean: " << barrel->GetMean() << " vs " << forward->GetMean() << "\n";
	barrel->DrawNormalized("h");
	forward->DrawNormalized("hsame");
	TLegend *legendMean = new TLegend(0.44,0.7,0.87,0.82,NULL,"brNDC");
	//legendMean->SetHeader(header.c_str());
	legendMean->SetFillColor(kWhite);
	legendMean->SetBorderSize(0);
	legendMean->AddEntry(barrel,"|cos#theta| < 0.9","l");
	legendMean->AddEntry(forward,"|cos#theta| > 0.9","l");
	legendMean->Draw();

}
void makePretty(TH1 * htemp, int color, string title = "")
{
	htemp->SetMinimum(0);
	htemp->SetLineWidth(3);
	htemp->SetTitle("");
	htemp->GetXaxis()->SetTitle(title.c_str());
	htemp->SetLineColor(color);
	htemp->SetStats(0);
}
