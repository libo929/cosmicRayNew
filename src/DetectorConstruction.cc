#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"
#include "G4PolarizationManager.hh"
#include "G4SubtractionSolid.hh"

#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"

#include "G4SDManager.hh"
#include "TargetSD.hh"
#include "PMTSD.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true)
{}

DetectorConstruction::~DetectorConstruction()
{}  

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Geometry parameters
  G4double targetThickness = 5.*cm;
  G4double targetSizeXY  = 25.*cm;

  G4double AlThickness = 0.3*cm;
  
  if (targetThickness == 0.) 
  {
    G4ExceptionDescription msg;
    msg << "The targetThickness should be larger than targetSpacing.";
    G4Exception("B4DetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }

  G4double envLength = targetThickness*2.;	//the length of envelop in z axis
  G4double envSizeXY = targetSizeXY+20*cm;

  auto worldSizeXY = 1.2 * envSizeXY;
  auto worldSizeZ  = 1.2 * envLength;
  
  // Get materials
  G4NistManager* nist = G4NistManager::Instance();

  G4Material* worldMaterial     = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* envMaterial       = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* targetMaterial    = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  G4Material* reflectorMaterial = nist->FindOrBuildMaterial("G4_Al");

	G4double energy[3]     = {2.034*eV, 3.*eV, 4.136*eV};
	G4double rindex[3]     = {1.3435, 1.351, 1.3608};
	G4double absorption[3] = {344.8*cm, 850.*cm, 1450.0*cm};
	
	G4MaterialPropertiesTable* MPT = new G4MaterialPropertiesTable();
	
	// property independent of energy
	MPT->AddConstProperty("SCINTILLATIONYIELD", 100./MeV);
	
	// properties that depend on energy
	MPT->AddProperty("RINDEX", energy, rindex, 3)->SetSpline(true);
	MPT->AddProperty("ABSLENGTH", energy, absorption, 3)->SetSpline(true);

	targetMaterial->SetMaterialPropertiesTable(MPT);
  
  if ( ! worldMaterial || ! envMaterial || ! targetMaterial ) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined."; 
    G4Exception("B4DetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }
   
  //     
  // World
  //
  auto worldS 
    = new G4Box("World",           // its name
                 worldSizeXY/2, worldSizeXY/2, worldSizeZ/2); // its size
                         
  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 worldMaterial,    // its material
                 "World");         // its name
                                   
  worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  //
  // Envelope
  //
  G4Box* envS
    = new G4Box("Envelope",	   // its name
		envSizeXY/2, envSizeXY/2, envLength/2); // its size

  G4LogicalVolume* envLV
    = new G4LogicalVolume(
		envS,		   // its solid
		envMaterial,	   // its material
		"Envelope");        // its name

  //envLV->SetVisAttributes(envelopeVisAtt);

  envPV = new G4PVPlacement(
		0,		   // no rotation
		G4ThreeVector(),   // at(0, 0, 0)
		envLV,		   // its logical volume
		"Envelope",	   // its name
		worldLV,	   // its mather volume
		false,		   // no boolean operations
		0, 		   // copy number
		fCheckOverlaps);   // checking overlaps

  //
  // Reflector
  //

  G4Box* ReflectorS
	= new G4Box("Reflector",
		(targetSizeXY+2*AlThickness)/2, (targetSizeXY+AlThickness)/2, (targetThickness+2*AlThickness)/2);

//	G4LogicalVolume* ReflectorLV
//		= new G4LogicalVolume(ReflectorS,
//							reflectorMaterial,
//							"Reflector");
//
//	G4VPhysicalVolume* ReflectorPV
//	= new G4PVPlacement(0,
//					G4ThreeVector(0, AlThickness/2, 0),
//					ReflectorLV,
//					"Reflector",
//					envLV,
//					false,
//					0,
//					fCheckOverlaps);

  G4Box* targetS
  = new G4Box("Target",	   // its name
 	     targetSizeXY/2, targetSizeXY/2, targetThickness/2); // its size
 
//  G4LogicalVolume* targetLv  
//      = new G4LogicalVolume(targetS,		// its solid
//                        targetMaterial,     // its material
// 		                "Target");       	// its name

 
//	G4VPhysicalVolume* TargetPV
//		= new G4PVPlacement(0,	                             // no rotation
//                    G4ThreeVector(0, -AlThickness/2, 0),                 // its position
//                    targetLv,					     // its logical volume
//                    "Target",     			         // its name
//                    ReflectorLV,				             // its mather volume
//                    false,				             // no poolean operation
//                    0,					             // copy number
//                    fCheckOverlaps);	             // checking overlaps

	G4SubtractionSolid* subtractionSolid
        = new G4SubtractionSolid("subtractionSolid", ReflectorS, targetS, 0, G4ThreeVector(0, -AlThickness/2, 0));

	G4LogicalVolume* ReflectorLV
		= new G4LogicalVolume(subtractionSolid, reflectorMaterial, "Reflector");

	G4VPhysicalVolume* ReflectorPV
		= new G4PVPlacement(0, G4ThreeVector(0, AlThickness/2, 0), ReflectorLV, "Reflector", envLV, true, 0, fCheckOverlaps);

	//
	// Target
	//

	G4LogicalVolume* targetLv  
      = new G4LogicalVolume(targetS,      // its solid
                        targetMaterial,     // its material
                      "Target");          // its name


  G4VPhysicalVolume* TargetPV
      = new G4PVPlacement(0,                               // no rotation
                    G4ThreeVector(),                 // its position
                    targetLv,                      // its logical volume
                    "Target",                          // its name
                    envLV,                           // its mather volume
                    false,                             // no poolean operation
                    0,                                 // copy number
                    fCheckOverlaps);               // checking overlaps

  //
  // PMT
  //

  G4Box* PMTS
	= new G4Box("PMT",
		targetSizeXY/2, 1.5*cm, targetThickness/2);

  G4LogicalVolume* PMTLv  
      = new G4LogicalVolume(PMTS,        // its solid
                        worldMaterial,     // its material
                        "PMT");           // its name

  G4VPhysicalVolume* PMTPV
	  = new G4PVPlacement(0,                               // no rotation
                    G4ThreeVector(0, -targetSizeXY/2.-1.5*cm, 0),                 // its position
                    PMTLv,                        // its logical volume
                    "PMT",                        // its name
                    envLV,                             // its mather volume
                    false,                           // no poolean operation
                    0,                               // copy number
                    fCheckOverlaps);                 // checking overlaps

  //std::cout << *(G4Material::GetMaterialTable()) << std::endl; // Get material table

	//
	// Surface
	//

	// Surface 1 : ReflectorPV - TargetPV
	G4OpticalSurface* opReflectorSurface = new G4OpticalSurface("ReflectorSurface");
	opReflectorSurface->SetType(dielectric_metal);
	opReflectorSurface->SetFinish(polished);
	opReflectorSurface->SetModel(glisur);

	G4LogicalBorderSurface* reflectorSurface 
				= new G4LogicalBorderSurface("ReflectorSurface", ReflectorPV, TargetPV, opReflectorSurface);

	G4OpticalSurface* opticalSurface = dynamic_cast<G4OpticalSurface*>
			(reflectorSurface->GetSurface(ReflectorPV, TargetPV)->GetSurfaceProperty());

	if(opticalSurface) opticalSurface->DumpInfo();


	G4MaterialPropertiesTable* reflectorSurfaceProperty = new G4MaterialPropertiesTable();
    
	const G4int nbins = 2;
    G4double p_mirror[] = {2.00*eV, 3.47*eV};
    G4double refl_mirror[] = {1., 1.};
    G4double effi_mirror[] = {0, 0};

    reflectorSurfaceProperty->AddProperty("REFLECTIVITY",p_mirror,refl_mirror,nbins);
    reflectorSurfaceProperty->AddProperty("EFFICIENCY",p_mirror,effi_mirror,nbins);

    opReflectorSurface->SetMaterialPropertiesTable(reflectorSurfaceProperty);

	new G4LogicalSkinSurface("ReflectorSurface", ReflectorLV, opticalSurface);

//	// Surface 2 : TargetPV - PMTPV
//    G4OpticalSurface* opPMTSurface = new G4OpticalSurface("PMTSurface");
//    opReflectorSurface->SetType(dielectric_dielectric);
//    opReflectorSurface->SetFinish(polished);
//    opReflectorSurface->SetModel(glisur);
//
//    G4LogicalBorderSurface* reflectorSurface
//                = new G4LogicalBorderSurface("ReflectorSurface", ReflectorPV, TargetPV, opReflectorSurface);
//
//    G4OpticalSurface* opticalSurface = dynamic_cast<G4OpticalSurface*>
//            (reflectorSurface->GetSurface(ReflectorPV, TargetPV)->GetSurfaceProperty());
//
//    if(opticalSurface) opticalSurface->DumpInfo();
//
//
//    G4MaterialPropertiesTable* reflectorSurfaceProperty = new G4MaterialPropertiesTable();
//
//    const G4int nbins = 2;
//    G4double p_mirror[] = {2.00*eV, 3.47*eV};
//    G4double refl_mirror[] = {1., 1.};
//    G4double effi_mirror[] = {0, 0};
//
//    reflectorSurfaceProperty->AddProperty("REFLECTIVITY",p_mirror,refl_mirror,nbins);
//    reflectorSurfaceProperty->AddProperty("EFFICIENCY",p_mirror,effi_mirror,nbins);
//
//    opReflectorSurface->SetMaterialPropertiesTable(reflectorSurfaceProperty);
//
//    new G4LogicalSkinSurface("ReflectorSurface", ReflectorLV, opticalSurface);

	//
	// Always return the physical World
	//
	return worldPV;
}

void DetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  // 
  // Sensitive detectors
  //
  TargetSD* targetSD 
    = new TargetSD("cosmicRay/TargetSD", "TargetHitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(targetSD);
  SetSensitiveDetector("Target", targetSD);
  // Setting targetSD to all logical volumes with the same name of "Target"

  PMTSD* pmtSD
    = new PMTSD("cosmicRay/PMTSD", "PMTHitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(pmtSD);
  SetSensitiveDetector("PMT", pmtSD);
}
