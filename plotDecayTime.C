{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  TFile f("output.root");

  TCanvas* c1 = new TCanvas();
  c1->Divide(2, 3);

  int nbins = 100;
  double xmin = 0.;
  double xmax = 30000.;

  TNtuple* ntuple = (TNtuple*)f.Get("CosmicRay"); // Get the file "CosmicRay"

  // id 1
  double mutime11;       ntuple->SetBranchAddress("Time1muon", &mutime11);
  double electrontime12; ntuple->SetBranchAddress("Time1electron", &electrontime12);

  // id 2
  double mutime21;       ntuple->SetBranchAddress("Time2muon", &mutime21);
  double electrontime22; ntuple->SetBranchAddress("Time2electron", &electrontime22);

  // id 3
  double mutime31;       ntuple->SetBranchAddress("Time3muon", &mutime31);
  double electrontime32; ntuple->SetBranchAddress("Time3electron", &electrontime32);

  // id 4
  double mutime41;       ntuple->SetBranchAddress("Time4muon", &mutime41);
  double electrontime42; ntuple->SetBranchAddress("Time4electron", &electrontime42);

  // id 5
  double mutime51;       ntuple->SetBranchAddress("Time5muon", &mutime51);
  double electrontime52; ntuple->SetBranchAddress("Time5electron", &electrontime52);

  // id 6
  double mutime61;       ntuple->SetBranchAddress("Time6muon", &mutime61);
  double electrontime62; ntuple->SetBranchAddress("Time6electron", &electrontime62);


  // id 1
  TH1F* f1 = new TH1F("f1", "f1", nbins, xmin, xmax);
  f1->SetTitle("Muon lifetime");
  f1->GetXaxis()->SetTitle("Time/ns");
  f1->GetYaxis()->SetTitle("count");

  // id 2
  TH1F* f2 = new TH1F("f2", "f2", nbins, xmin, xmax);
  f2->SetTitle("Muon lifetime");
  f2->GetXaxis()->SetTitle("Time/ns");
  f2->GetYaxis()->SetTitle("count");

  // id 3
  TH1F* f3 = new TH1F("f3", "f3", nbins, xmin, xmax);
  f3->SetTitle("Muon lifetime");
  f3->GetXaxis()->SetTitle("Time/ns");
  f3->GetYaxis()->SetTitle("count");

  // id 4
  TH1F* f4 = new TH1F("f4", "f4", nbins, xmin, xmax);
  f4->SetTitle("Muon lifetime");
  f4->GetXaxis()->SetTitle("Time/ns");
  f4->GetYaxis()->SetTitle("count");

  // id 5
  TH1F* f5 = new TH1F("f5", "f5", nbins, xmin, xmax);
  f5->SetTitle("Muon lifetime");
  f5->GetXaxis()->SetTitle("Time/ns");
  f5->GetYaxis()->SetTitle("count");

  // id 6
  TH1F* f6 = new TH1F("f6", "f6", nbins, xmin, xmax);
  f6->SetTitle("Muon lifetime");
  f6->GetXaxis()->SetTitle("Time/ns");
  f6->GetYaxis()->SetTitle("count");


  // Fill information
  for(int i=0; i<ntuple->GetEntries(); i++)
  {
    ntuple->GetEntry(i);

    if(electrontime12!=0) f1->Fill(electrontime12-mutime11);
    if(electrontime22!=0) f2->Fill(electrontime22-mutime21);
    if(electrontime32!=0) f3->Fill(electrontime32-mutime31);
    if(electrontime42!=0) f4->Fill(electrontime42-mutime41);
    if(electrontime52!=0) f5->Fill(electrontime52-mutime51);
    if(electrontime62!=0) f6->Fill(electrontime62-mutime61);
  }

  c1->cd(1);
  f1->Draw();

  c1->cd(2);
  f2->Draw("same");

  c1->cd(3);
  f3->Draw("same");

  c1->cd(4);
  f4->Draw("same");

  c1->cd(5);
  f5->Draw("same");

  c1->cd(6);
  f6->Draw("same");

  c1->Draw();
}
