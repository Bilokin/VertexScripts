void _charge()
{
	if (!gSystem->AccessPathName("MCTest_original.root")) 
	{
		cout << "EXIST!\n";
		gROOT->ProcessLine(".x /users/flc/bilokin/Processors/Macros/vertex/chargeEfficiency.C (\"RecoTest_original.root\",kBlack, NULL, \"MCTest_original.root\")");
	}
	else 
	{
		cout << "NOT EXIST!\n";
		gROOT->ProcessLine(".x /users/flc/bilokin/Processors/Macros/vertex/chargeEfficiency.C (\"RecoTest_original.root\",kBlack)");
	}
	gROOT->ProcessLine(".x /users/flc/bilokin/Processors/Macros/vertex/chargeEfficiency.C (\"RecoTest.root\",kBlue,c1)");
}
