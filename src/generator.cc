#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "proton";
    G4ParticleDefinition *particle = particleTable->FindParticle("geantino");
    G4ThreeVector pos1(0.0*cm, 0.0*cm, -0.0* cm);
    fParticleGun->SetParticlePosition(pos1);
    fParticleGun->SetParticleMomentum(0.*GeV);
    fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();

    if(particle = G4Geantino::Geantino())
    {
        G4int Z = 27;
        G4int A = 60;
        G4double charge = 0.*eplus;
        G4double energy = 0.*keV;
        G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z,A,energy);
        fParticleGun->SetParticleDefinition(ion);
        fParticleGun->SetParticleCharge(charge);
    }
    fParticleGun->GeneratePrimaryVertex(anEvent);

}