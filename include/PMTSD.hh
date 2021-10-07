#ifndef PMTSD_h
#define PMTSD_h 1

#include "G4VSensitiveDetector.hh"
#include "PMTHit.hh"
#include <vector>

class G4Step;
class G4HCofThisEvent;

class PMTSD : public G4VSensitiveDetector
{
  public:
    PMTSD(const G4String& name, 
             const G4String& hitsCollectionName);
    virtual ~PMTSD();
  
    // methods from base class
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

  private:

    PMTHitsCollection* fHitsCollection;
};

#endif
