{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  TFile f("output.root");

  TCanvas* c1 = new TCanvas();
  c1->SetGrid();

  TH2F* f1 = new TH2F("f1", "f1", 100, 0., 50., 100, 0., 35);
  f1->SetTitle("Correlation between stopping depth and energy deposition");
  f1->GetXaxis()->SetTitle("depth/mm");
  f1->GetYaxis()->SetTitle("E#mu/MeV");

  TNtuple* ntuple = (TNtuple*)f.Get("CosmicRay"); // Get the file "CosmicRay"

  // scintillator id = 2
  double MuonEdep2;       ntuple->SetBranchAddress("MuonEdep2", &MuonEdep2);
  double DecayPosition2Z; ntuple->SetBranchAddress("DecayPosition2Z", &DecayPosition2Z);
  double mutime31;        ntuple->SetBranchAddress("Time3muon", &mutime31);

  for(int i=0; i<ntuple->GetEntries(); i++)
  {
    ntuple->GetEntry(i);
 
    if(MuonEdep2!=0.&&mutime31==0.)
    f1->Fill(DecayPosition2Z*10.+325., MuonEdep2);
  }

  f1->Draw();
  c1->Draw();
}
