void covMtx(string cuts = "")
{
	TFile *_file0 = TFile::Open("Modification.root");
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1200,800);
	c1->Divide(3,2);
	c1->cd(1);
	string z0cuts = "abs(z0Prime) < 10  && ftdHits > 1" + cuts;
	Stats->Draw("(z0Prime ) ",z0cuts.c_str());
	c1->cd(2);
	//string z0cutsF = "momentum > 10 && abs(z0 - z0Prime)/sqrt(covMtx9) < 20 && ftdHits > 1";
	string z0cutsF = "abs(z0Prime) < 10  && ftdHits > 1 && abs(z0Prime)/sqrt(covMtx9) < 20" + cuts;
	Stats->Draw("abs(z0Prime)/sqrt(covMtx9) ",z0cutsF.c_str());
	c1->cd(3);
	string z0cutsC = "sqrt(covMtx9 )< 1 && ftdHits > 1"+ cuts;
	Stats->Draw("sqrt(covMtx9)",z0cutsC.c_str());

	c1->cd(4);
	//string d0cuts = "momentum > 10 && abs(d0 - d0Prime)/sqrt(covMtx0) < 20 &&vtxHits > 5";
	//Stats->Draw("(dPrime - d0)/sqrt(covMtx0) : abs(costheta)",d0cuts.c_str());
	//Stats->Draw("(d0Prime - d0) : abs(costheta)",d0cuts.c_str());
	string d0cuts = "abs(d0Prime) < 1 && ftdHits > 1 && abs(costheta) < 0.985"+ cuts;
	Stats->Draw("(d0Prime ) ",d0cuts.c_str());
	c1->cd(5);
	string d0cutsF = " abs(d0 - d0Prime)/sqrt(covMtx0) < 20 &&ftdHits > 1";
	string d0cuts = "ftdHits > 1 && abs(costheta) < 0.985 && abs(d0Prime)/sqrt(covMtx0) < 20" + cuts;
	//Stats->Draw("(d0Prime - d0)/sqrt(covMtx0) : abs(costheta)",d0cutsF.c_str());
	Stats->Draw("abs(d0Prime)/sqrt(covMtx0)",d0cuts.c_str());
	c1->cd(6);
	string d0cutsC = "sqrt(covMtx0) < 1 &&ftdHits > 1 && abs(costheta) < 0.985" + cuts;
	Stats->Draw("sqrt(covMtx0)",d0cutsC.c_str());
}

