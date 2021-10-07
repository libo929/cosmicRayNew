{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  TFile f("output.root");

  TCanvas* c1 = new TCanvas();
  c1->SetGrid();

  int nbins = 100;
  double xmin = 0.;
  double xmax = 50.;
  double ymin = 0.;
  double ymax = 40.;

  TNtuple* ntuple = (TNtuple*)f.Get("CosmicRay");
 
  double ElectronEdep2;       ntuple->SetBranchAddress("ElectronEdep2", &ElectronEdep2);
  double DecayPosition2Z;     ntuple->SetBranchAddress("DecayPosition2Z", &DecayPosition2Z);
  double ElectronEdep1;       ntuple->SetBranchAddress("ElectronEdep1", &ElectronEdep1);
  double ElectronEdep3;       ntuple->SetBranchAddress("ElectronEdep3", &ElectronEdep3);
  double DetermineUpAndDown2; ntuple->SetBranchAddress("DetermineUpAndDown2", &DetermineUpAndDown2);

  TH2F* upEvent = new TH2F("upEvent", "upEvent", nbins, xmin, xmax, nbins, ymin, ymax); // scintillator id : 2
  upEvent->SetTitle("Correlation between stopping depth and deposition");
  upEvent->GetXaxis()->SetTitle("depth/mm");
  upEvent->GetYaxis()->SetTitle("E_{e}/MeV");

  TH2F* downEvent = new TH2F("downEvent", "downEvent", nbins, xmin, xmax, nbins, ymin, ymax);

  upEvent->SetMarkerColor(kRed);
  upEvent->SetMarkerStyle(8);

  downEvent->SetMarkerColor(kBlue);
  downEvent->SetMarkerStyle(8);

  for(int i=0; i<ntuple->GetEntries(); i++)
  {
    ntuple->GetEntry(i);
    
    if(DetermineUpAndDown2!=0 && ElectronEdep2!=0. && DecayPosition2Z!=0.)
    {
        if(DetermineUpAndDown2==1)   upEvent->Fill(DecayPosition2Z*10.+325., ElectronEdep2);
        if(DetermineUpAndDown2==-1)  downEvent->Fill(DecayPosition2Z*10.+325., ElectronEdep2);
    }
  }

  TLegend* leg = new TLegend(.1, .7, .3, .9, "");
  leg->SetFillColor(0);
  leg->AddEntry(upEvent, "up event");
  leg->AddEntry(downEvent, "down event");

  upEvent->Draw();
  downEvent->Draw("Same");
  leg->DrawClone("Same");

  

  // Draw PDF
  //upEvent->Print("Correlation between stopping depth and deposition.pdf");
  c1->Draw();
}
