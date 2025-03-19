#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "run.hh"
#include "G4Timer.hh"






using namespace std;

int main(int argc , char** argv){

    G4RunManager *runManager = new G4RunManager();

    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());

    runManager->SetUserInitialization(new MyActionInitialization());

    runManager->Initialize();
    // Create and initialize the timer
    G4Timer timer;
    
    // Start the timer before running the simulation
    timer.Start();



    G4UIExecutive *ui = 0;
    
    if (argc == 1)
    {
        ui = new G4UIExecutive(argc,argv); 
    }
    

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    G4UImanager *UImanager =  G4UImanager::GetUIpointer();



    if(ui)
    {
        
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
    }

    else
    {
        
        G4String command = "/control/execute ";
        G4String filename = argv[1];
        UImanager->ApplyCommand(command+filename);
    }


    // Stop the timer after the simulation ends
    timer.Stop();
    
    // Output the total runtime
    G4cout << "Total runtime: " << timer.GetRealElapsed() << " seconds." << G4endl;

    return 0 ;

}


