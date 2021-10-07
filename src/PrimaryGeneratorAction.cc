#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

/*
double funFlux(double *x, double *par)
{
    double muonEnergy = x[0];
    double theta = par[0]/180. * TMath::Pi();

    const double P1 = 0.102573;
    const double P2 = -0.068287;
    const double P3 = 0.958633;
    const double P4 = 0.0407253;
    const double P5 = 0.817285;

    double cosTheta = cos(theta); 
    double cosThetaStar2 = ( cosTheta * cosTheta + P1 * P1 + P2 * pow(cosTheta, P3) + P4 * pow(cosTheta, P5) ) / 
        (1. + P1*P1 + P2 + P4);
    double cosThetaStar = sqrt(cosThetaStar2);

    double Emu = muonEnergy;       // GeV

    double term1 = 1./(1 + 1.1 * Emu * cosThetaStar/115);
    double term2 = 0.054/(1 + 1.1 * Emu * cosThetaStar/850);

    double flux = 0.14 * pow(Emu * (1. + 3.64/(Emu * pow(cosThetaStar, 1.29))), -2.7) * (term1 +  term2);

    return flux * 10000; // 1/cm^2 -> 1/m^2
}
*/

double PrimaryGeneratorAction::fPrimaryEnergy;

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),
  fEnvelopeBox(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
  //fMuonGen = new TF1("f0", funFlux, 0.1, 2000, 1); 

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="mu+");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  //G4double Energy = G4UniformRand() * 100.;
  //fParticleGun->SetParticleEnergy(Energy * MeV);
  fParticleGun->SetParticleEnergy(100. * keV);
  //std::cout << Energy << std::endl;
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
  //delete fMuonGen;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event
  //

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get Envelope volume
  // from G4LogicalVolumeStore.
  
  G4double envSizeZ = 0.;
  G4double envSizeXY = 0.;

  if (!fEnvelopeBox)
  {
    G4LogicalVolume* envLV
      = G4LogicalVolumeStore::GetInstance()->GetVolume("Envelope");
    if(envLV)
    { 
      fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
    }
  }

  if(fEnvelopeBox) 
  {
    envSizeZ = fEnvelopeBox->GetZHalfLength()*2.;
    envSizeXY = fEnvelopeBox->GetXHalfLength()-10*cm;
  }

  G4double z0 = -0.5 * envSizeZ;
  G4double x0 = envSizeXY*(G4UniformRand()-0.5);
  G4double y0 = envSizeXY*(G4UniformRand()-0.5);

  
  fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, z0));

  //double muonEn = fMuonGen->GetRandom();
  //fParticleGun->SetParticleEnergy(muonEn * GeV);
  //fParticleGun->SetParticleEnergy(G4Random->Uniform(0, 100) * MeV);

  G4double fEnergy = G4UniformRand() * 100.;
  fPrimaryEnergy = fEnergy;
  fParticleGun->SetParticleEnergy(fEnergy * MeV);

  fParticleGun->GeneratePrimaryVertex(anEvent);//significant
}

double PrimaryGeneratorAction::GetPrimaryEnergy()
{
   return fPrimaryEnergy;
}
