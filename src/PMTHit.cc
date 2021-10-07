#include "PMTHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<PMTHit>* PMTHitAllocator=0;

PMTHit::PMTHit()
 : G4VHit(),
   fEdep(0.),
   fmutime(0.),
   felectiontime(0.),
   fDecayPosition(0.),
   fMuonEdep(0.),
   fElectronEdep(0.)
{}

PMTHit::~PMTHit() 
{}

PMTHit::PMTHit(const PMTHit& right)
  : G4VHit()
{
  fEdep          = right.fEdep;
  fmutime        = right.fmutime;
  felectiontime  = right.felectiontime;
  fDecayPosition = right.fDecayPosition;
  fMuonEdep      = right.fMuonEdep;
  fElectronEdep  = right.fElectronEdep;
}

const PMTHit& PMTHit::operator=(const PMTHit& right)
{
  fEdep          = right.fEdep;
  fmutime        = right.fmutime;
  felectiontime  = right.felectiontime;
  fDecayPosition = right.fDecayPosition;
  fMuonEdep      = right.fMuonEdep;
  fElectronEdep  = right.fElectronEdep;

  return *this;
}

G4bool PMTHit::operator==(const PMTHit& right) const
{
  return ( this == &right ) ? true : false;
}

void PMTHit::AddEdep(G4double de)
{
  fEdep+=de;
}

void PMTHit::AddMuTime(G4double mutime)
{
  fmutime = mutime;
}

void PMTHit::AddElectronTime(G4double electrontime)
{
  felectiontime = electrontime;
}

void PMTHit::AddDecayPosition(G4double decayPosition)
{
  fDecayPosition = decayPosition;
}

void PMTHit::AddMuonEdep(G4double muonEdep)
{
  fMuonEdep+=muonEdep;
}

void PMTHit::AddElectronEdep(G4double electronEdep)
{
  fElectronEdep+=electronEdep;
}
