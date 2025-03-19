#include <iostream>
#include<TFile.h>
#include<TH1F.h>
#include<TF1.h>
#include<TRandom.h>

using namespace std;

void Analysis()
{

    TFile *file = new TFile("Spectrum.root","READ");

    TH1F *h1 = (TH1F*)file->Get("hist");

    TH1F *h2 = new TH1F("hist1","",100,0,1.0);

    TF1* stDev = new TF1("Standard Deviation","(2.5+55.05*TMath::Sqrt(x[0]+0.52365*x[0]*x[0]))/2350", 0, 100);

    int maxFilledBin = h1->FindLastBinAbove();

    cout << maxFilledBin << endl;


    for(int i = 2; i<=maxFilledBin; i++)
    {

        int counts = h1->GetBinContent(i);

        if(counts != 0)
        {
            for (int j = 0; j < counts; j++ )
            {

                double Currentbin = h1->GetBinCenter(i);

                double bin = Currentbin+gRandom->Gaus(0,stDev->Eval(Currentbin));


                h2->Fill(bin);


            }
        }

    }

    h2->Draw("C");
    h2->SetStats(0);
    h2->GetXaxis()->SetTitle("Energy [MeV]");
    h2->GetYaxis()->SetTitle("Number of Counts");

}