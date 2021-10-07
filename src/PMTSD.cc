#include "PMTSD.hh"
#include "DetectorConstruction.hh"
#include "G4VProcess.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "g4root.hh"

PMTSD::PMTSD(const G4String& name,
                   const G4String& hitsCollectionName)
 : G4VSensitiveDetector(name),
   fHitsCollection(NULL)
{
  collectionName.insert(hitsCollectionName);
}

PMTSD::~PMTSD() 
{}

void PMTSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  fHitsCollection 
    = new PMTHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce
  G4int hcID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection );

  // Create hits
  fHitsCollection->insert(new PMTHit());
}

G4bool PMTSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
	G4int pid = step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();

	auto analysisManager  = G4AnalysisManager::Instance();

	if(pid == 22 && step->IsFirstStepInVolume())
	{
		analysisManager->FillNtupleDColumn(1, 0, step->GetTrack()->GetKineticEnergy());
		analysisManager->FillNtupleDColumn(1, 1, step->GetTrack()->GetGlobalTime());
		analysisManager->AddNtupleRow(1);
	}


	return true;
}

void PMTSD::EndOfEvent(G4HCofThisEvent*)
{}
