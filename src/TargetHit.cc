#include "TargetHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<TargetHit>* TargetHitAllocator=0;

TargetHit::TargetHit()
 : G4VHit(),
   fEdep(0.),
   fmutime(0.),
   felectiontime(0.),
   fDecayPosition(0.),
   fMuonEdep(0.),
   fElectronEdep(0.)
{}

TargetHit::~TargetHit() 
{}

TargetHit::TargetHit(const TargetHit& right)
  : G4VHit()
{
  fEdep          = right.fEdep;
  fmutime        = right.fmutime;
  felectiontime  = right.felectiontime;
  fDecayPosition = right.fDecayPosition;
  fMuonEdep      = right.fMuonEdep;
  fElectronEdep  = right.fElectronEdep;
}

const TargetHit& TargetHit::operator=(const TargetHit& right)
{
  fEdep          = right.fEdep;
  fmutime        = right.fmutime;
  felectiontime  = right.felectiontime;
  fDecayPosition = right.fDecayPosition;
  fMuonEdep      = right.fMuonEdep;
  fElectronEdep  = right.fElectronEdep;

  return *this;
}

G4bool TargetHit::operator==(const TargetHit& right) const
{
  return ( this == &right ) ? true : false;
}

void TargetHit::AddEdep(G4double de)
{
  fEdep+=de;
}

void TargetHit::AddMuTime(G4double mutime)
{
  fmutime = mutime;
}

void TargetHit::AddElectronTime(G4double electrontime)
{
  felectiontime = electrontime;
}

void TargetHit::AddDecayPosition(G4double decayPosition)
{
  fDecayPosition = decayPosition;
}

void TargetHit::AddMuonEdep(G4double muonEdep)
{
  fMuonEdep+=muonEdep;
}

void TargetHit::AddElectronEdep(G4double electronEdep)
{
  fElectronEdep+=electronEdep;
}
