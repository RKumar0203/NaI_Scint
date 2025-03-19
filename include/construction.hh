#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH


#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4UnionSolid.hh"
#include "G4Sphere.hh"
#include "G4GenericMessenger.hh"


class MyDetectorConstruction : public G4VUserDetectorConstruction{
    public:
        MyDetectorConstruction();
        ~MyDetectorConstruction();

        virtual G4VPhysicalVolume *Construct();
        G4LogicalVolume *GetScoringVolume() const {return fScoringVolume;}

        private:
        G4LogicalVolume *NaI_Logical;
        G4LogicalVolume *fScoringVolume;
        G4GenericMessenger *fMessengar;
        G4int SDD;
        void DefineMaterial();

};


#endif
