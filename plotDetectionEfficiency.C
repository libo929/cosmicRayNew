{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  TFile f("output.root");

  TCanvas* c1 = new TCanvas();
  c1->SetGrid();
  c1->SetLogx();

  TNtuple* ntuple = (TNtuple*)f.Get("CosmicRay");
  double count; ntuple->SetBranchAddress("DetectionEfficiency", &count);

  int x = ntuple->GetEntries();

  TH2F* f1 = new TH2F("f1", "f1", 100, 0., x, 100, 0., 1.);
  f1->SetTitle("Detection Efficiency");
  f1->GetXaxis()->SetTitle("Event Number");
  f1->GetYaxis()->SetTitle("Efficiency");

  for(int i=0; i<ntuple->GetEntries(); i++)
  {
    ntuple->GetEntry(i);
      f1->Fill(i+1, count/(i+1));
  }

  f1->Draw();
  c1->Draw();
}
