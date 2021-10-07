{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  TFile f("output.root");

  TCanvas* c1 = new TCanvas();
  c1->SetGrid();

  const int nbins = 100;
  double xmin = 0.;  double xmax = 100.;
  double ymin = -3.; double ymax = 3.;

  TNtuple* ntuple = (TNtuple*)f.Get("CosmicRay");

  // Get Muon Primary Energy
  double PrimaryEnergy;       ntuple->SetBranchAddress("PrimaryEnergy", &PrimaryEnergy);

  //sintillator id 2, 3, 4, 5
  double DetermineUpAndDown2; ntuple->SetBranchAddress("DetermineUpAndDown2", &DetermineUpAndDown2);
  double DetermineUpAndDown3; ntuple->SetBranchAddress("DetermineUpAndDown3", &DetermineUpAndDown3);
  double DetermineUpAndDown4; ntuple->SetBranchAddress("DetermineUpAndDown4", &DetermineUpAndDown4);
  double DetermineUpAndDown5; ntuple->SetBranchAddress("DetermineUpAndDown5", &DetermineUpAndDown5);

  TH1F* upEvent   = new TH1F("upEvent", "upEvent", nbins, xmin, xmax);
  upEvent->SetLineColor(kRed);
  upEvent->SetLineWidth(3);
  TH1F* downEvent = new TH1F("downEvent", "downEvent", nbins, xmin, xmax);
  downEvent->SetLineColor(kBlue);
  downEvent->SetLineWidth(3);

  for(int i=0; i<ntuple->GetEntries(); i++)
  {
     ntuple->GetEntry(i);

     if(DetermineUpAndDown2==1) upEvent->Fill(PrimaryEnergy); if(DetermineUpAndDown2==-1) downEvent->Fill(PrimaryEnergy);
     if(DetermineUpAndDown3==1) upEvent->Fill(PrimaryEnergy); if(DetermineUpAndDown3==-1) downEvent->Fill(PrimaryEnergy);
     if(DetermineUpAndDown4==1) upEvent->Fill(PrimaryEnergy); if(DetermineUpAndDown4==-1) downEvent->Fill(PrimaryEnergy);
     if(DetermineUpAndDown5==1) upEvent->Fill(PrimaryEnergy); if(DetermineUpAndDown5==-1) downEvent->Fill(PrimaryEnergy);
  }

  int up    = 0;
  int down  = 0;
  double alpha[nbins] = {0.};
  double xposition[nbins] = {0.};

  for(int i=0; i<upEvent->GetNbinsX(); i++)
  {
    up   = upEvent->GetBinContent(i);
    down = downEvent->GetBinContent(i);

    if(up+down!=0)
    alpha[i] = (double)(up-down)/(up+down);
    xposition[i] = upEvent->GetBinCenter(i);
  }

  TGraph* g1 = new TGraph(nbins, xposition, alpha);
  g1->SetTitle("");
  g1->GetXaxis()->SetTitle("E_{#mu}(MeV)");
  g1->GetYaxis()->SetTitle("#alpha_{e}");

  g1->Draw();
  c1->Draw();
}
