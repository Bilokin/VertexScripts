void _charge()
{
	gROOT->ProcessLine(".x /users/flc/bilokin/Processors/Macros/vertex/chargeEfficiency.C (\"TrashRecoTest_original.root\",kBlack)");
	gROOT->ProcessLine(".x /users/flc/bilokin/Processors/Macros/vertex/chargeEfficiency.C (\"TrashRecoTest.root\",kBlue,c1)");
}
