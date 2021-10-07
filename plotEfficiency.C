{
  gROOT->Reset();
  gROOT->SetStyle();

  // Get information
  // scintillator 1
  double mutime11;
  TNtuple* ntuple11 = (TNtuple*)f.Get("CosmicRay");
  ntuple11->SetBranchAddress("Time1muon", &mutime11);

  double electrontime12;
  TNtuple* ntuple12 = (TNtuple*)f.Get("CosmicRay");
  ntuple12->SetBranchAddress("Time1electron", &electrontime12);

  double position1;
  TNtuple* ntuple13 = (TNtuple*)f.Get("CosmicRay");
  ntuple13->SetBranchAddress("DecayPosition1Z", &position1);

  // scintillator 2
  double mutime21;
  TNtuple* ntuple21 = (TNtuple*)f.Get("CosmicRay");
  ntuple21->SetBranchAddress("Time2muon", &mutime21);

  double electrontime22;
  TNtuple* ntuple22 = (TNtuple*)f.Get("CosmicRay");
  ntuple22->SetBranchAddress("Time2electron", &electrontime22);

  double position2;
  TNtuple* ntuple23 = (TNtuple*)f.Get("CosmicRay");
  ntuple23->SetBranchAddress("DecayPosition2Z", &position2);

  // scintillator 3
  double mutime31;
  TNtuple* ntuple31 = (TNtuple*)f.Get("CosmicRay");
  ntuple31->SetBranchAddress("Time3muon", &mutime31);

  double electrontime32;
  TNtuple* ntuple32 = (TNtuple*)f.Get("CosmicRay");
  ntuple32->SetBranchAddress("Time3electron", &electrontime32);

  double position3;
  TNtuple* ntuple33 = (TNtuple*)f.Get("CosmicRay");
  ntuple33->SetBranchAddress("DecayPosition3Z", &position3);

  // scintillator 4
  double mutime41;
  TNtuple* ntuple41 = (TNtuple*)f.Get("CosmicRay");
  ntuple41->SetBranchAddress("Time4muon", &mutime41);

  double electrontime42;
  TNtuple* ntuple42 = (TNtuple*)f.Get("CosmicRay");
  ntuple42->SetBranchAddress("Time4electron", &electrontime42);

  double position4;
  TNtuple* ntuple43 = (TNtuple*)f.Get("CosmicRay");
  ntuple43->SetBranchAddress("DecayPosition4Z", &position4);

  // scintillator 5
  double mutime51;
  TNtuple* ntuple51 = (TNtuple*)f.Get("CosmicRay");
  ntuple51->SetBranchAddress("Time5muon", &mutime51);

  double electrontime52;
  TNtuple* ntuple52 = (TNtuple*)f.Get("CosmicRay");
  ntuple52->SetBranchAddress("Time5electron", &electrontime52);

  double position5;
  TNtuple* ntuple53 = (TNtuple*)f.Get("CosmicRay");
  ntuple53->SetBranchAddress("DecayPosition5Z", &position5);

  // scintillator 6
  double mutime61;
  TNtuple* ntuple61 = (TNtuple*)f.Get("CosmicRay");
  ntuple61->SetBranchAddress("Time6muon", &mutime61);

  double electrontime62;
  TNtuple* ntuple62 = (TNtuple*)f.Get("CosmicRay");
  ntuple62->SetBranchAddress("Time6electron", &electrontime62);

  double position6;
  TNtuple* ntuple63 = (TNtuple*)f.Get("CosmicRay");
  ntuple63->SetBranchAddress("DecayPosition6Z", &position6);

  // Fill
  // id 2
  TH2F* f2 = new TH2F("f2", "Efficiency", 50, 0., 50., 100, ); 
}
