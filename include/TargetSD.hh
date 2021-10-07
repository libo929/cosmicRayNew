#ifndef TargetSD_h
#define TargetSD_h 1

#include "G4VSensitiveDetector.hh"
#include "TargetHit.hh"
#include <vector>

class G4Step;
class G4HCofThisEvent;

class TargetSD : public G4VSensitiveDetector
{
  public:
    TargetSD(const G4String& name, 
             const G4String& hitsCollectionName);
    virtual ~TargetSD();
  
    // methods from base class
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

  private:

    TargetHitsCollection* fHitsCollection;
};

#endif
