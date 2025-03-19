#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4OpticalPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"

class MyPhysicsList: public G4VModularPhysicsList{
    public:

    MyPhysicsList();
    ~MyPhysicsList();

   // virtual void ConstructParticle();
    //void AddPhysicsList(const G4String& name);
   // virtual void ConstructProcess(); 
    virtual void ConstructEM();
    void SetCuts() override; 


};

#endif // PHYSICS_HH
