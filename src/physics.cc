#include "physics.hh"
#include "G4Gamma.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4RayleighScattering.hh"
#include "G4HadronicParameters.hh"
#include "CLHEP/Units/SystemOfUnits.h"



MyPhysicsList :: MyPhysicsList(){

    // Set the time threshold for radioactive decays to a very high value (e.g., 1.0e+60 years)
    G4HadronicParameters::Instance()->SetTimeThresholdForRadioactiveDecay(1.0e+60 * CLHEP::year);
    
    RegisterPhysics(new G4EmStandardPhysics());

    RegisterPhysics(new G4DecayPhysics());

    RegisterPhysics(new G4RadioactiveDecayPhysics());

}



void MyPhysicsList::ConstructEM()
{
// Get pointer to G4PhysicsListHelper
G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

// Get pointer to gamma
G4ParticleDefinition* particle = G4Gamma::GammaDefinition();

// Construct and register processes for gamma
ph->RegisterProcess(new G4PhotoElectricEffect(), particle);
ph->RegisterProcess(new G4ComptonScattering(), particle);
ph->RegisterProcess(new G4GammaConversion(), particle);
ph->RegisterProcess(new G4RayleighScattering(), particle);

}


void MyPhysicsList::SetCuts()
{
    G4VUserPhysicsList::SetCuts();
}

MyPhysicsList::~MyPhysicsList(){}