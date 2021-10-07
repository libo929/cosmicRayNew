// ROOT macro file for plotting example B4 ntuple
// 
// Can be run from ROOT session:
// root[0] .x plotNtuple.C

{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  TFile f("output.root");

  TNtuple* ntuple = (TNtuple*)f.Get("Edep");
  //TNtuple* ntuple = (TNtuple*)f.Get("DecayTime");

  TH1F* h = new TH1F("h", "h", 100, -100, 100);

  double edep1; 
  double edep2; 
  ntuple->SetBranchAddress("edep1", &edep1);
  ntuple->SetBranchAddress("edep2", &edep2);

  for(int i = 0; i < ntuple->GetEntries(); ++i)
  {
     ntuple->GetEntry(i);
     h->Fill(edep1 - edep2);
  }

  h->Draw();
     

  //TCanvas* c1 = new TCanvas("c1", "Lifetime of cosmic ray {#mu}", 20, 20, 1000, 1000);
  //c1->SetTitle("Lifetime of cosmic ray {#mu}");

}  
