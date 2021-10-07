// ROOT macro file for plotting example B4 ntuple
// 
// Can be run from ROOT session:
// root[0] .x plotNtuple.C

{
  gROOT->Reset();
  gROOT->SetStyle("Plain");


  TFile f("output.root");

  TCanvas* c1 = new TCanvas("c1", "Lifetime of cosmic ray {#mu}", 20, 20, 1000, 1000);
  c1->SetTitle("Lifetime of cosmic ray {#mu}");

  TNtuple* ntuple = (TNtuple*)f.Get("DecayTime");
  c1->Divide(2, 3);

  c1->cd(1);
  ntuple->Draw("Time1electron-Time1muon", "Time1electron>0&&Time1muon>0");

  c1->cd(2);
  ntuple->Draw("Time2electron-Time2muon", "Time2electron>0&&Time2muon>0");

  c1->cd(3);
  ntuple->Draw("Time3electron-Time3muon", "Time3electron>0&&Time3muon>0");

  c1->cd(4);
  ntuple->Draw("Time4electron-Time4muon", "Time4electron>0&&Time4muon>0");

  c1->cd(5);
  ntuple->Draw("Time5electron-Time5muon", "Time5electron>0&&Time5muon>0");

  c1->cd(6);
  ntuple->Draw("Time6electron-Time6muon", "Time6electron>0&&Time6muon>0");

  c1->Print("Time.jpg");
/*
  gROOT->Reset();
  gROOT->SetStyle("Plain");


  TFile f("output.root");

  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);

  TNtuple* ntuple = (TNtuple*)f.Get("cosmicRay");
  c1->Divide(6, 2);

  c1->cd(1);
  ntuple->Draw("Time11");

  c1->cd(2);
  ntuple->Draw("Time12");

  c1->cd(3);
  ntuple->Draw("Time21");

  c1->cd(4);
  ntuple->Draw("Time22");

  c1->cd(5);
  ntuple->Draw("Time31");

  c1->cd(6);
  ntuple->Draw("Time32");

  c1->cd(7);
  ntuple->Draw("Time41");

  c1->cd(8);
  ntuple->Draw("Time42");

  c1->cd(9);
  ntuple->Draw("Time51");

  c1->cd(10);
  ntuple->Draw("Time52");

  c1->cd(11);
  ntuple->Draw("Time61");  

  c1->cd(12);
  ntuple->Draw("Time62");

  
//  // Draw histos filled by Geant4 simulation 
//  //   
//
//  // Open file filled by Geant4 simulation 
//  TFile f("B4.root");
//
//  // Create a canvas and divide it into 2x2 pads
//  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
//  c1->Divide(2,2);
//  
//  // Get ntuple
//  TNtuple* ntuple = (TNtuple*)f.Get("B4");
//
//  // Draw Eabs histogram in the pad 1
//  c1->cd(1);
//  ntuple->Draw("Eabs");
//  
//  // Draw Labs histogram in the pad 2
//  c1->cd(2);
//  ntuple->Draw("Labs");
//  
//  // Draw Egap histogram in the pad 3
//  // with logaritmic scale for y  ?? how to do this?
//  c1->cd(3);
//  gPad->SetLogy(1);
//  ntuple->Draw("Egap");
//  
//  // Draw Lgap histogram in the pad 4
//  // with logaritmic scale for y  ?? how to do this?
//  c1->cd(4);
//  gPad->SetLogy(1);
//  ntuple->Draw("Egap");
*/
}  
