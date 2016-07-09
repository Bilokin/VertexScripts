void checkImpactParameters()
{
	TFile *_file0 = TFile::Open("RecoTest.root");
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1200,400);
	c1->Divide(3,1);
	c1->cd(1);
	TaggedVertices->Draw("z0PrimeOfParticles : z0OfParticles","abs(z0PrimeOfParticles ) < 2 && abs(z0OfParticles ) < 2 &&abs(z0PrimeOfParticles ) > 0.001");
	c1->cd(2);
	TaggedVertices->Draw("d0PrimeOfParticles : d0OfParticles","abs(d0PrimeOfParticles ) < 2 && abs(d0OfParticles ) < 2 ");

	c1->cd(3);
	//Stats->Draw("phi0PrimeOfParticles : phi0","abs(phi0PrimeOfParticles ) < 3.14 && abs(phi0 ) < 3.14");

}
