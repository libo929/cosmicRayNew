#include "EventAction.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"

#include "TargetHit.hh"
#include "TargetSD.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include "g4root.hh"
#include <iomanip>

EventAction::EventAction()
: G4UserEventAction(),
  fTargetHCID(-1)
{} 

EventAction::~EventAction()
{}

TargetHitsCollection*
EventAction::GetTargetHitsCollection(G4int hcID, 
				const G4Event* event) const
{
  auto TargethitsCollection
    = static_cast<TargetHitsCollection*>(
	event->GetHCofThisEvent()->GetHC(hcID));

  if(!TargethitsCollection)
  {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID" << hcID;
    G4Exception("EventAction::GetHitsCollection()",
	 "MyCode0003", FatalException, msg);
  }

  return TargethitsCollection;
}

void EventAction::BeginOfEventAction(const G4Event*)
{}

void EventAction::EndOfEventAction(const G4Event* event)
{
  // Get hits collection IDs (only once)
  if(fTargetHCID == -1)
  {
     fTargetHCID = G4SDManager::GetSDMpointer()->GetCollectionID("TargetHitsCollection");
  }

  // Get hits collection
  auto targetHC = GetTargetHitsCollection(fTargetHCID, event);

  // Get analysis manager
  auto analysisManager  = G4AnalysisManager::Instance();
 
  // Fill histograms, ntuple
  //
  analysisManager->FillNtupleDColumn(0, (*targetHC)[0]->GetEdep());
  analysisManager->FillNtupleDColumn(1, (*targetHC)[0]->GetMuonEdep());
  analysisManager->FillNtupleDColumn(2, (*targetHC)[0]->GetElectronEdep());
  analysisManager->FillNtupleDColumn(3, PrimaryGeneratorAction::GetPrimaryEnergy());
  analysisManager->FillNtupleDColumn(4, (*targetHC)[0]->GetMuTime());
  analysisManager->FillNtupleDColumn(5, (*targetHC)[0]->GetElectronTime());
  analysisManager->FillNtupleDColumn(6, (*targetHC)[0]->GetDecayPosition()/10.); // unit : cm

  analysisManager->AddNtupleRow();
}
