{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  TFile f("output.root");

  TCanvas* c1 = new TCanvas();
  c1->SetGrid();

  const int nbins = 100;
  double xmin = 0.;  double xmax = 50.;
  double ymin = -3.; double ymax = 3.;

  TNtuple* ntuple = (TNtuple*)f.Get("CosmicRay");

  //sintillator id 2
  double DetermineUpAndDown2; ntuple->SetBranchAddress("DetermineUpAndDown2", &DetermineUpAndDown2);
  double DecayPosition2Z;     ntuple->SetBranchAddress("DecayPosition2Z", &DecayPosition2Z);
  

  TH1F* upEvent   = new TH1F("upEvent", "upEvent", nbins, xmin, xmax);
  upEvent->SetLineColor(kRed);
  upEvent->SetLineWidth(3);
  TH1F* downEvent = new TH1F("downEvent", "downEvent", nbins, xmin, xmax);
  downEvent->SetLineColor(kBlue);
  downEvent->SetLineWidth(3);

  for(int i=0; i<ntuple->GetEntries(); i++)
  {
     ntuple->GetEntry(i);

     if(DetermineUpAndDown2==1)  upEvent->Fill(DecayPosition2Z*10+325.);
     if(DetermineUpAndDown2==-1) downEvent->Fill(DecayPosition2Z*10+325.);
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
  g1->GetXaxis()->SetTitle("d/mm");
  g1->GetYaxis()->SetTitle("#alpha_{e}");

  g1->Draw();
  c1->Draw();
}
