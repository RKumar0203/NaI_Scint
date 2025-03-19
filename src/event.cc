#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
    fEdep = 0;
}

MyEventAction::~MyEventAction(){}

void MyEventAction::BeginOfEventAction( const G4Event* )
{
    fEdep = 0;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
    //G4cout << "Energy Deposition " << fEdep << G4endl;

     G4AnalysisManager *man = G4AnalysisManager::Instance();

    if(fEdep>0)
    {

        man->FillNtupleDColumn(0, 0 ,fEdep);
        man->AddNtupleRow(0);
        man->FillH1(0, fEdep);
    }

} 
