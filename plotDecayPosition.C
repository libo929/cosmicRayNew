{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  TFile f("output.root");

  TCanvas* c1 = new TCanvas();
  c1->SetGrid();


  TNtuple* ntuple = (TNtuple*)f.Get("CosmicRay");

  double decayPosition1; ntuple->SetBranchAddress("DecayPosition1Z", &decayPosition1);
  double decayPosition2; ntuple->SetBranchAddress("DecayPosition2Z", &decayPosition2);
  double decayPosition3; ntuple->SetBranchAddress("DecayPosition3Z", &decayPosition3);
  double decayPosition4; ntuple->SetBranchAddress("DecayPosition4Z", &decayPosition4);
  double decayPosition5; ntuple->SetBranchAddress("DecayPosition5Z", &decayPosition5);
  double decayPosition6; ntuple->SetBranchAddress("DecayPosition6Z", &decayPosition6);

  TH1F* f1 = new TH1F("f1", "f1", 100, -110., 110.);
  f1->SetTitle("Muon decay position in the Z coordinate");
  f1->GetXaxis()->SetTitle("Position/cm");
  f1->GetYaxis()->SetTitle("The event number");

  for(int i=0; i<ntuple->GetEntries(); i++)
  {
    ntuple->GetEntry(i);

    if(decayPosition1!=0) f1->Fill(decayPosition1);
    if(decayPosition2!=0) f1->Fill(decayPosition2);
    if(decayPosition3!=0) f1->Fill(decayPosition3);
    if(decayPosition4!=0) f1->Fill(decayPosition4);
    if(decayPosition5!=0) f1->Fill(decayPosition5);
    if(decayPosition6!=0) f1->Fill(decayPosition6);
  }

  f1->Draw();
  c1->Draw();
}
