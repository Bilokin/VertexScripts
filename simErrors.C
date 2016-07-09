void simErrors()
{
	const int max = 200;
	int _nparticles = 0;
	int _vtxHits[max];
	float _z0[max];
	float _z0Prime[max];
	float _d0[max];
	float _d0Prime[max];
	float _costheta[max];
	float _momentum[max];
	float _covMtx0[max];
	float _covMtx6[max];
	float _covMtx9[max];
	
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,1000);
	c1->Divide(2,2);
	int nbins = 200;
	float maxp = 50;
	float maxcos = 1;
	float maxs = .20001;
	TH2F * realp = new TH2F("Pw","",nbins,0,maxp ,nbins, 0, maxs);
	TH2F * smearp = new TH2F("Sw","",nbins,0,maxp ,nbins, 0, 0.2);
	TH2F * simp = new TH2F("Pw1","",nbins,0,maxp ,nbins, 0, maxs);
	TH2F * simcos = new TH2F("Pww","",nbins,0,maxcos ,nbins, 0, maxs*0.1);
	TH2F * realcos = new TH2F("Pwq","",nbins,0,maxcos ,nbins, 0, maxs*0.1);
	TH1F * simp2 = new TH1F("P2w","",nbins, 0, 2);
	TChain* T = new TChain("Stats");
	T->Add("Modification.root");
	
	T->SetBranchAddress("nParticles", &_nparticles);
	T->SetBranchAddress("vtxHits", _vtxHits);
	T->SetBranchAddress("costheta", _costheta);
	T->SetBranchAddress("z0", _z0);
	T->SetBranchAddress("z0Prime", _z0Prime);
	T->SetBranchAddress("d0", _d0);
	T->SetBranchAddress("d0Prime", _d0Prime);
	T->SetBranchAddress("momentum", _momentum);
	T->SetBranchAddress("covMtx0", _covMtx0);
	T->SetBranchAddress("covMtx6", _covMtx6);
	T->SetBranchAddress("covMtx9", _covMtx9);

	//float a1dd = 1.0e-4; // 7.5e-5
	//float a2dd = 5.e-7; // 3.1e-6
	//float b1dd = 1.5e-5; //1.5e-7
	float a1dd = 6.4e-6; // 7.5e-5
	float a2dd = 5.47e-5; // 3.1e-6

	float b1dd = -0.5; //1.5e-7
	float b2dd = 1.8e-5; //1.8e-5
	
	float a1zz = 6.5e-5;
	float a2zz = .6e-5;

	float b1zz = 5.5e-6;
	float b2zz = 5.5e-5;

	float abdd[] = {a1dd, a2dd, b1dd, b2dd} ;
	float abzz[] = {a1zz, a2zz, b1zz, b2zz} ;

	int mTotalNumberOfEvents = T->GetEntries();
	for (int i = 0; i < mTotalNumberOfEvents; i++) 
	{
		T->GetEntry(i);
		//cout << "_nparticles: " << _nparticles << endl;

		for (int j = 0; j < _nparticles; j++) 
		{
			float costheta = TMath::Abs(_costheta[j]);
			float p = _momentum[j];
			//cout << "\t costheta: " << costheta << endl;
			//cout << "\t p: " << p << endl;
			//cout << "\t hits: " << _vtxHits[j]  << endl;
			if (_vtxHits[j] != 6 && p > 8 && p < 15) 
			{
				realcos->Fill(costheta, sqrt(_covMtx0[j]));
				float cov9 = calculateZ0(costheta, p, abzz);
				float cov0 = calculateD0(costheta, p, abdd);
				simcos->Fill(costheta, sqrt(cov0));
			}
			if (costheta > 0.8 &&costheta < 0.9 && _vtxHits[j] == 6) 
			{
				realp->Fill(_momentum[j],_covMtx0[j]);
				float cov9 = calculateZ0(costheta, p, abzz);
				if (p>2) 
				{
					simp2->Fill(cov0/_covMtx0[j]);
				}
			}
			if (std::abs(_d0[j]) == 0 && costheta < 0.9 ) 
			{
				float cov0 = calculateD0(costheta, p, abdd);
				smearp->Fill(_momentum[j],_d0Prime[j]);
				simp->Fill(_momentum[j], sqrt(cov0)*1);
			}
		}
	}
	c1->cd(1);
	//realp->Draw();
	smearp->Draw();
	simp->SetMarkerColor(kRed);
	simcos->SetMarkerColor(kRed);
	simp->Draw("same");
	c1->cd(2);
	simp2->Draw();
	c1->cd(3);
	realcos->Draw();
	simcos->Draw("same");


}

float calculateD0(float cos, float p, float * parameters)
{
	float covMtx = (parameters[0] +
		parameters[1] / (p + parameters[2]))/(1-cos*cos*cos*cos); /// sqrt(1-cos*cos) +
		//parameters[1]) / sqrt(1-cos*cos);
		//parameters[2] / (1-cos) + 
		//parameters[3] / (1-cos)/p; 
	return covMtx;
}
float calculateZ0(float cos, float p, float * parameters)
{
	float covMtx = (parameters[0] / p +
		parameters[1])/ pow(1.-cos*cos*cos*cos,2);
		//parameters[2] / sqrt(1-cos*cos) + 
		//parameters[3] / sqrt(1-cos*cos)/(p); 
	return covMtx;
}
