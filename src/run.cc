#include "run.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{ 
    G4AnalysisManager *man = G4AnalysisManager::Instance();


    man->OpenFile("output.root");
    man->CreateNtuple("Energy","Energy");
    man->CreateNtupleDColumn("fEdep");
    man->FinishNtuple(0);
    man->CreateH1("Detector1","Edep in Scintillator", 100, 0., 3);
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}
