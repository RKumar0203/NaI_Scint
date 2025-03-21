#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "globals.hh"

class MyRunAction : public G4UserRunAction{
    public:
        MyRunAction();
        ~MyRunAction();

        virtual void BeginOfRunAction(const G4Run*);
        virtual void EndOfRunAction(const G4Run*);
};


#endif
