#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIcommand.hh"

#include "FTFP_BERT.hh"
#include "G4OpticalPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"
#include "g4root.hh"

int main(int argc,char **argv)		//Detect interactive mode (if no arguments ) and define UI session
{
  G4UIExecutive *ui = 0;
  if (argc == 1)
  {
  ui = new G4UIExecutive(argc, argv);
  }

  //Potionally:choose a different Randow engine
  //
#ifdef G4MULTITHREADED
  G4MTRunManger* runManager = new G4MTRRunManager;
#else
  G4RunManager* runManager = new G4RunManager;
#endif
  
  //Set mandatory initialization classes
  //
  //Detector construction
  runManager->SetUserInitialization(new DetectorConstruction());

  //Physics list
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  physicsList->SetVerboseLevel(1);
  physicsList->RegisterPhysics(opticalPhysics);
  runManager->SetUserInitialization(physicsList);

  //User action initialization
  runManager->SetUserInitialization(new ActionInitialization());

  //Initialization visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  G4UImanager* UImanager = G4UImanager::GetUIpointer();		//Get the pointer to the User Interface manager

  //Process macro or start UI session
  //
  if(!ui)		//batch mode
  {
  G4String command = "/control/execute ";
  G4String fileName = argv[1];
  UImanager->ApplyCommand(command+fileName);
  }
  else			//interactive mode
  {
  UImanager->ApplyCommand("/control/execute init_vis.mac");
  ui->SessionStart();
  delete ui;
  }
delete visManager;
delete runManager;
}
