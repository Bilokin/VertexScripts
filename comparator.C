void comparator(string filename1, string filename2, string observable, string cuts = "")
{
	TCanvas * c = new TCanvas("canvas", "Data-MC",0,0,500,600);
	//c->Divide(1,2, 0.01, 0.01);
	TPad *pad1 = new TPad("pad1", "The pad 80% of the height",0.0,0.2,1.0,1.0,21);
	TPad *pad2 = new TPad("pad2", "The pad 20% of the height",0.0,0.0,1.0,0.2,22);
	pad1->SetFillColor(kWhite);
	pad2->SetFillColor(kWhite);
	pad1->Draw();
	pad2->Draw();
	TFile * file1 = TFile::Open(filename1.c_str(), "read");
	TTree * missedTracks1 = MissedTracks;
//	missedTracks1->Print("toponly");
	TTree * taggedVertices1 = TaggedVertices;
	TTree * missedVertex1 = MissedVertex;
	TTree * stats1 = Stats;
	TFile * file2 = TFile::Open(filename2.c_str(), "read");
	TTree * missedTracks2 = MissedTracks;
	TTree * missedVertex2 = MissedVertex;
	TTree * stats2 = Stats;
	TTree * taggedVertices2 = TaggedVertices;

	int c1 = missedTracks1->Project("tmp",observable.c_str());
	cout << c1 <<endl;
	if (c1 > 0) 
	{
		drawHists(missedTracks1, missedTracks2, observable, cuts);
	}
	int c2 = stats1->Project("tmp",observable.c_str());
	cout << c2 <<endl;
	if (c2 > 0) 
	{
		drawHists(stats1, stats2, observable, cuts);
	}
	int c3 = taggedVertices1->Project("tmp",observable.c_str());
	cout << c3 <<endl;
	if (c3 > 0 && c2 < 1) 
	{
		drawHists(taggedVertices1, taggedVertices2, observable, cuts);
	}
	int c4 = missedVertex1->Project("tmp",observable.c_str());
	cout << c4 <<endl;
	if (c4 > 0 && c3 < 1) 
	{
		drawHists(missedVertex1, missedVertex2, observable, cuts);
	}
	pad1->cd();
	TLegend *legendMean = new TLegend(0.44,0.6,0.87,0.82,NULL,"brNDC");
	//legendMean->SetHeader(header.c_str());
	legendMean->SetFillColor(kWhite);
	legendMean->SetBorderSize(0);
	legendMean->AddEntry(htemp1,filename1.c_str(),"l");
	legendMean->AddEntry(htemp2,filename2.c_str(),"l");
	legendMean->Draw();
}
void drawHists(TTree * tree1, TTree * tree2, string observable, string cuts = "")
{
	string cut = observable + " > -1";
	if (cuts != "") 
	{
		cut += " && ";
		cut += cuts;
	}
	pad1->cd();
	int number1 = tree1->Project("htemp1",observable.c_str(), cut.c_str());
	htemp1->Sumw2();
	makePretty(htemp1, kBlue, observable);
	int number2 = tree2->Project("htemp2",observable.c_str(), cut.c_str());
	htemp2->Sumw2();
	makePretty(htemp2, kGreen, observable);
	if (abs(tree1->GetEntries() - tree2->GetEntries()) < 100) 
	{
		htemp1->Draw("he");
		htemp2->Draw("hesame");
		cout << "Selection: " << number1 << " vs " << number2 << endl;
	}
	else 
	{
		htemp1->Scale(1./htemp1->GetEntries());
		htemp2->Scale(1./htemp2->GetEntries());
		htemp1->DrawNormalized("h");
		htemp2->DrawNormalized("hsame");
	}
	pad2->cd();
	TH1 * htemp2 = htemp2;
	TH1 * htemp1 = htemp1;
	TH1 * htemp3 = htemp1->Clone();
	htemp3->Divide(htemp1, htemp2);
	makePretty(htemp3, kBlack);
	htemp3->SetMinimum(0);
	htemp3->SetMaximum(2);
	pad2->SetGridy();
	htemp3->GetYaxis()->SetNdivisions(107);
	htemp3->GetYaxis()->SetLabelSize(0.1);
	htemp3->Draw();
	cout << "Mean: " << htemp1->GetMean() << " vs " <<htemp2->GetMean() << endl;
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
