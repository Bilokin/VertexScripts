void stat(string recofilename = "RecoTest.root", string mcfilename = "MCTest.root")
{
	TFile * mcfile = TFile::Open(mcfilename.c_str());//, "read");
	TTree * mcvertices = Vertices;
	TTree * mcstat = Stats;
	TFile * recofile = TFile::Open(recofilename.c_str());//, "read");
	TTree * recostat = Stats;
	TTree * recovertices = TaggedVertices;
	TTree * recoLVTX = MissedVertex;
	TTree * recoLTr = MissedTracks;
	int bin_e = 50;
	float min_e = 0;
	float max_e = 1000;
	TH1F * missedhist = new TH1F("missedhist", ";#epsilon [mm]", bin_e,min_e,max_e);
	int mctotaltracks = mcvertices->Project("missedhist", "momentumOfParticles", "momentumOfParticles > 0");
	int mcdecayedtracks = mcvertices->Project("missedhist", "momentumOfParticles", "momentumOfParticles > 0 && interactionOfParticles == 0");
	int mconetrackvtx = mcvertices->Project("missedhist", "momentumOfParticles", "momentumOfParticles > 0 && numberOfParticles == 1");

	int recoVtxTracksTotal = recovertices->Project("missedhist", "momentumOfParticles", "momentumOfParticles > 0" ); 
	int recoVtxTracksNoVXD = recovertices->Project("missedhist", "momentumOfParticles", "momentumOfParticles > 0 && vtxHitsOfParticles < 3" ); 
	int recoVtxTracksFTDNoVXD = recovertices->Project("missedhist", "momentumOfParticles", "momentumOfParticles > 0 && vtxHitsOfParticles == 0 && ftdHitsOfParticles > 0" ); 
	int recoVtxOneTracks = recovertices->Project("missedhist", "momentumOfParticles", "momentumOfParticles > 0 && numberOfParticles == 1" ); 
	
	int recoMissedVtxTracks = recoLVTX->Project("missedhist", "momentumOfParticlesVtx", "momentumOfParticlesVtx > 0");
	int recoMissedVtxOneTracks = recoLVTX->Project("missedhist", "momentumOfParticlesVtx", "momentumOfParticlesVtx > 0 && numberOfTracksMissedVtx == 1");

	int recoMissedTracksTotal = recoLTr->Project("missedhist", "momentumMissed", "momentumMissed > 0");
	int recoMissedTracksNonReco = recoLTr->Project("missedhist", "momentumMissed", "momentumMissed > 0 && isrecoMissed == 0");
	int recoMissedTracksNoVXD = recoLTr->Project("missedhist", "momentumMissed", "momentumMissed > 0 && vtxHitsMissed == 0 && ftdHitsMissed == 0");
	int recoMissedTracksFTDNoVXD = recoLTr->Project("missedhist", "momentumMissed", "momentumMissed > 0 && vtxHitsMissed < 3 && ftdHitsMissed > 0");
	int recoMissedTracksNoTrack = recoLTr->Project("missedhist", "momentumMissed", "momentumMissed > 0 && hastrackMissed == 0");
	int recoMissedTracksForward = recoLTr->Project("missedhist", "momentumMissed", "momentumMissed > 0 && abs(costhetaMissed) > 0.9");
	int fake = recoVtxTracksTotal+recoMissedTracksTotal+recoMissedVtxTracks - mctotaltracks;
	cout << "---------------------\n";
	cout << "---------------------\n";
	printStat("Gen Total", mctotaltracks, mctotaltracks);
	//printStat("Gen Decayed", mcdecayedtracks, mctotaltracks);
	printStat("Gen 1tr VTX", mconetrackvtx, mctotaltracks);
	cout << "---------------------\n";
	printStat("Reco Total", recoVtxTracksTotal, mctotaltracks);
	printStat("Reco NoVXD", recoVtxTracksNoVXD, mctotaltracks);
	printStat("Reco FTD", recoVtxTracksFTDNoVXD, mctotaltracks);
	printStat("Reco 1tr VTX", recoVtxOneTracks, mctotaltracks);
	cout << "---------------------\n";
	cout << "---------------------\n";
	printStat("Lost VTX", recoMissedVtxTracks, mctotaltracks);
	printStat("Lost 1tr VTX", recoMissedVtxOneTracks, mctotaltracks);
	cout << "---------------------\n";
	printStat("Lost Tracks", recoMissedTracksTotal, mctotaltracks);
	printStat("Lost Forward", recoMissedTracksForward, mctotaltracks);
	printStat("Lost NonReco", recoMissedTracksNonReco, mctotaltracks);
	printStat("Lost NoVXD", recoMissedTracksNoVXD, mctotaltracks);
	printStat("Lost FTD", recoMissedTracksFTDNoVXD, mctotaltracks);
	printStat("Lost NoTrack", recoMissedTracksNoTrack, mctotaltracks);
	cout << "---------------------\n";
	cout << "---------------------\n";
	printStat("Total Lost", recoMissedTracksTotal + recoMissedVtxTracks, mctotaltracks);
	printStat("False Added", fake, mctotaltracks);
	cout << "Total damage:\t\t\t" << fake + recoMissedTracksTotal<< "\t" << (float)(fake + recoMissedTracksTotal) / (recoVtxTracksTotal - fake) * 100 << "%\n";
	cout << "---------------------\n";
	cout << "---------------------\n";
	mcfile->Close();
	recofile->Close();
	
}
void printStat(string name, int number, int totalnumber)
{
	cout << name << " particles:\t\t" << number << "\t" << (float)number / totalnumber  * 100 << "%\n";
}
