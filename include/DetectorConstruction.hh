#ifndef B4cDetectorConstruction_h
#define B4cDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    const G4VPhysicalVolume* GetEnvelope()      {return envPV;};
    const G4VPhysicalVolume* GetWorld()      {return worldPV;};
     
  private:
    // data members
    //
    G4VPhysicalVolume* envPV;
    G4VPhysicalVolume* worldPV;

    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

#endif
