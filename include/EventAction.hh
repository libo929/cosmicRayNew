#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "DetectorConstruction.hh"
#include "TargetHit.hh"

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
    void AddPhi(G4double phi);

  private:
  TargetHitsCollection* GetTargetHitsCollection(G4int hcID, const G4Event* event) const;

  G4int fTargetHCID;
};

#endif
