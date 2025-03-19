#include <iostream>
#include <fstream>
#include<TCanvas.h>
#include<TFile.h>
#include<TTree.h>
#include<TH1F.h>
using namespace std;


void spectrum()
{

    TCanvas *c1 = new TCanvas("c1","Cs137 spectrum");

    TFile *f = new TFile("Co_60_spectrum.root","READ");

    TFile *f1 = new TFile("Europium.root","RECREATE");

    TTree *t = (TTree*)f->Get("Energy");
    
    TH1F *hist = new TH1F("hist","hist",100,0,1.7);

    fstream fp;

    fp.open("data.txt",ios::out);


    Int_t events;
    Double_t Energy;
    events = t->GetEntries();
    cout << "Total No. of events are: " << events << endl;

    t->SetBranchAddress("fEdep",&Energy);


    for(Int_t i = 1; i<=events; i++)
    {
        t->GetEntry(i);
        hist->Fill(Energy);
        fp << Energy << endl;
    }
    c1->cd();
    hist->Draw();
    hist->Write();
    f1->Close();
    fp.close();

}
