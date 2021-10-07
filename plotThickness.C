#include "TCanvas.h"
#include "TH2F.h"
#include "TGraphErrors.h"

{
	gROOT->Reset();
	gROOT->SetStyle("Plain");

	TFile f("output.root");

	TNtuple* ntuple = (TNtuple*)f.Get("CosmicRay");

	// Get information
	double PrimaryEnergy;		ntuple->SetBranchAddress("PrimaryEnergy", &PrimaryEnergy);
	double TimeMuon;			ntuple->SetBranchAddress("Timemuon", &TimeMuon);
	double TimeElectron;		ntuple->SetBranchAddress("Timeelectron", &TimeElectron);
	double DecayPositionZ;		ntuple->SetBranchAddress("DecayPositionZ", &DecayPositionZ);

	// Draw
	//

    // Canvas
	TCanvas* c1 = new TCanvas();
    c1->SetGrid();

	// TH2F
	const int nbins = 100;
	double xmin = 0., xmax = 5;
	double ymin = 0., ymax = 3000;

	int num;
	double val, position;

	TH1F* f1a = new TH1F("", "", nbins, xmin, xmax);
	TH1F* f1b = new TH1F("", "", nbins, xmin, xmax);

    TH2F* f2 = new TH2F("", "", nbins, xmin, xmax, nbins, ymin, ymax);
	f2->GetXaxis()->SetTitle("Position/cm");
	f2->GetYaxis()->SetTitle("lifetime/ns"); f2->GetYaxis()->SetTitleOffset(1.2);

	f2->SetMarkerStyle(8);
	f2->SetMarkerColor(kRed);

	TH2F* f2Theory = new TH2F("", "", nbins, xmin, xmax, nbins, ymin, ymax);
	f2Theory->SetMarkerStyle(8);
	f2Theory->SetMarkerColor(kBlack);


	for(int i=0; i<ntuple->GetEntries(); i++)
	{
		ntuple->GetEntry(i);

		if(TimeElectron != 0.)
		{
			f1a->Fill(DecayPositionZ+25., TimeElectron-TimeMuon);
			f1b->Fill(DecayPositionZ+25.);
		}
	}

	for(int i=0; i<f1a->GetNbinsX(); i++)
	{
		position = f1a->GetBinCenter(i);

		val = f1a->GetBinContent(i);
		num = f1b->GetBinContent(i);

		if(num != 0)
		{
			f2->Fill(position, val/(double)num);
			f2Theory->Fill(position, 2197.3);
		}
	}

	TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
	legend->AddEntry(f2, "measurements");
	legend->AddEntry(f2Theory, "Theoretical value");

	f2->Draw();
	f2Theory->Draw("Same");
	legend->Draw("Same");

	c1->Draw();
}
