void impactParameters(string cuts = "")
{
	//string cuts = " && abs(costheta) > 0.9 && vtxHits == 0";
	//string cuts = " && abs(costheta) < 0.9 && vtxHits == 6";
	TFile *_file0 = TFile::Open("Modification.root");
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1200,800);
	c1->Divide(3,2);
	c1->cd(1);
	string z0cuts = "abs(z0Prime/z0-1) < 2. ";
	Stats->Draw("z0Prime :z0",(z0cuts + cuts).c_str());
	Stats->Draw("z0Prime /z0 : abs(costheta)",(z0cuts + cuts).c_str());
	c1->cd(2);
	string d0cuts = "abs(d0Prime/d0-1) < 2. ";
	int ntracks = Stats->Draw("d0Prime /d0 : abs(costheta)",(d0cuts + cuts).c_str());
	c1->cd(3);
	string sigmaOffsetcuts = "abs(sigmaOffsetPrime) < 0.3 ";
	Stats->Draw("sigmaOffsetPrime : abs(costheta)",(sigmaOffsetcuts + cuts).c_str());

	c1->cd(4);
	string covMtx0cuts = "sqrt(covMtx0 ) < 0.1 && abs(covMtx0 ) > 0";
	Stats->Draw("sqrt(covMtx0) : abs(costheta)",(covMtx0cuts + cuts).c_str(),"");
	TH2F   *htemp4 = (TH2F*)gPad->GetPrimitive("htemp");
	htemp4->GetYaxis()->SetTitleOffset(1.4);
	htemp4->SetTitleSize(20.4,"t");
	htemp4->SetTitle(";|cos#theta|;#sigma_{D_{0}}, [mm]");
	//Stats->Draw("covMtx0 : momentum",(covMtx0cuts + cuts).c_str(),"");
	c1->cd(5);
	string covMtx6cuts = "sqrt(covMtx6 ) < 0.1 && abs(covMtx6 ) > 0";
	Stats->Draw("sqrt(covMtx6) : abs(costheta)",(covMtx6cuts + cuts).c_str());
	//Stats->Draw("covMtx6 : momentum",(covMtx6cuts + cuts).c_str());
	c1->cd(6);
	string covMtx9cuts = "sqrt(covMtx9) < 0.1 && abs(covMtx9 ) > 0";
	Stats->Draw("sqrt(covMtx9) : abs(costheta)",(covMtx9cuts + cuts).c_str());
	TH2F   *htemp6 = (TH2F*)gPad->GetPrimitive("htemp");
	htemp6->GetYaxis()->SetTitleOffset(1.4);
	htemp6->SetTitle(";|cos#theta|;#sigma_{Z_{0}}, [mm]");
	cout << "Ntracks: " << ntracks << "\n";
	//Stats->Draw("covMtx9 : momentum",(covMtx9cuts + cuts).c_str());
	/*TCanvas * c2 = new TCanvas("c2", "The 3d view",0,0,500,500);
	c2->cd();
	TF1 *f1 = new TF1("f1","0.01+TMath::Gaus(x,0,0.1/[0])",0,1);
	TH2F * hist = new TH2F("hist","",100,0,1,100,0,0.1);
	//f1->Draw("lego2");
	f1->SetParameter(0,0.5);
	for (int i = 0; i < 10000; i++) 
	{
		double parameter = f1->GetRandom();
		f1->SetParameter(0,parameter);	
		double r = f1->GetRandom();
		hist->Fill(parameter,r);
	}
	//hist->Draw();
	double r = f1->GetRandom();
	cout << "Random: " << r <<endl;
*/
}
