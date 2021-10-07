#ifndef PMTHit_h
#define PMTHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4VProcess.hh"
#include "tls.hh"

class PMTHit : public G4VHit
{
  public:
    PMTHit();
    PMTHit(const PMTHit&);
    virtual ~PMTHit();

    // operators
    const PMTHit& operator=(const PMTHit&);
    G4bool operator==(const PMTHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // Add values
    void AddEdep(G4double de);
    void AddMuTime(G4double mutime);
    void AddElectronTime(G4double electrontime);
    void AddDecayPosition(G4double decayPosition);
    void AddMuonEdep(G4double de);
    void AddElectronEdep(G4double de);
    //void AddWhetherUpEventAndDownEvent

    // Get methods
    G4double GetEdep() const {return fEdep;};
    G4double GetMuTime() const {return fmutime;};
    G4double GetElectronTime() const {return felectiontime;};
    G4double GetDecayPosition() const {return fDecayPosition;};
    G4double GetMuonEdep() const {return fMuonEdep;};
    G4double GetElectronEdep() const {return fElectronEdep;};

  private:
    G4double fEdep;
    G4double fmutime;
    G4double felectiontime;
    G4double fDecayPosition;
    G4double fMuonEdep;
    G4double fElectronEdep;
};

typedef G4THitsCollection<PMTHit> PMTHitsCollection;

extern G4ThreadLocal G4Allocator<PMTHit>* PMTHitAllocator;

inline void* PMTHit::operator new(size_t)
{
  if(!PMTHitAllocator)
      PMTHitAllocator = new G4Allocator<PMTHit>;
  return (void *) PMTHitAllocator->MallocSingle();
}

inline void PMTHit::operator delete(void *hit)
{
  PMTHitAllocator->FreeSingle((PMTHit*) hit);
}

#endif
