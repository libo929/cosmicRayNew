#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class DetectorConstruction;
class PrimaryGeneratorAction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
public:

  SteppingAction(DetectorConstruction*, PrimaryGeneratorAction*, EventAction*);
  virtual ~SteppingAction();

  virtual void UserSteppingAction(const G4Step*);
    
private:
  DetectorConstruction*   fDetector;
  PrimaryGeneratorAction* fPrimary;
  EventAction*            fEvent;
};

#endif
