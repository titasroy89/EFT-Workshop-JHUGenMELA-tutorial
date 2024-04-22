#include <iostream>
#include <fstream>
#include "string.h"
#include "Mela.h"
#include "TVar.hh"
#include "TCouplingsBase.hh"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

using namespace std;

TLorentzVector ptEtaPhiVector(double pt, double eta, double phi, double m){ //constructs pt, eta, phi TLorentzVector
    TLorentzVector vec = TLorentzVector();
    vec.SetPtEtaPhiM(pt, eta, phi, m);
    return vec;
}

int main(int argc, char const *argv[])
{
    Mela m = Mela(13, 125, TVar::SILENT);

    string data_path = "../SAMPLE_DATA/EWSample_4l.root";
    string data_path = "../SAMPLE_DATA/ggHSample_4l.root";
    TFile* dataFile = TFile::Open(data_path);

    TTreeReader myReader("eventTree", dataFile);

    TTreeReaderValue<vector<short>> LHEDaughterId(myReader,   "LHEDaughterId");
    TTreeReaderValue<vector<float>> LHEDaughterPt(myReader,   "LHEDaughterPt");
    TTreeReaderValue<vector<float>> LHEDaughterEta(myReader,  "LHEDaughterEta");
    TTreeReaderValue<vector<float>> LHEDaughterPhi(myReader,  "LHEDaughterPhi");
    TTreeReaderValue<vector<float>> LHEDaughterMass(myReader, "LHEDaughterMass");
    
    TTreeReaderValue<vector<short>> LHEAssociatedParticleId(myReader,   "LHEAssociatedParticleId");
    TTreeReaderValue<vector<float>> LHEAssociatedParticlePt(myReader,   "LHEAssociatedParticlePt");
    TTreeReaderValue<vector<float>> LHEAssociatedParticleEta(myReader,  "LHEAssociatedParticleEta");
    TTreeReaderValue<vector<float>> LHEAssociatedParticlePhi(myReader,  "LHEAssociatedParticlePhi");
    TTreeReaderValue<vector<float>> LHEAssociatedParticleMass(myReader, "LHEAssociatedParticleMass");
    
    TTreeReaderValue<vector<short>> LHEMotherId(myReader, "LHEMotherId");
    TTreeReaderValue<vector<float>> LHEMotherPz(myReader, "LHEMotherPz");
    TTreeReaderValue<vector<float>> LHEMotherE(myReader,  "LHEMotherE");

    vector<float> probs;
    ofstream outputFile;
    outputFile.open("probs_output.txt");
    outputFile << data_path << "\n";

    while (myReader.Next()){

        SimpleParticleCollection_t* mother_collection = new SimpleParticleCollection_t();
        SimpleParticleCollection_t* daughter_collection = new SimpleParticleCollection_t();
        SimpleParticleCollection_t* associated_collection = new SimpleParticleCollection_t();

        vector<TLorentzVector> motherVecs;
        vector<TLorentzVector> daughterVecs;
        vector<TLorentzVector> associatedVecs;

        int i = 0;
        for(i = 0; i < (*LHEMotherId).size(); i++){
            mother_collection->push_back(
                SimpleParticle_t((int)(*LHEMotherId)[i], ptEtaPhiVector(0, 0, (*LHEMotherPz)[i], (*LHEMotherE)[i]))
            );
        }

        for(i = 0; i < (*LHEDaughterId).size(); i++){
            daughter_collection->push_back(
                SimpleParticle_t((int)(*LHEDaughterId)[i],ptEtaPhiVector((*LHEDaughterPt)[i], (*LHEDaughterEta)[i], (*LHEDaughterPhi)[i], (*LHEDaughterMass)[i]))
            );
        }

        for(i = 0; i < (*LHEAssociatedParticleId).size(); i++){
            associated_collection->push_back(
                SimpleParticle_t((int)(*LHEAssociatedParticleId)[i],ptEtaPhiVector((*LHEAssociatedParticlePt)[i], (*LHEAssociatedParticleEta)[i], (*LHEAssociatedParticlePhi)[i], (*LHEAssociatedParticleMass)[i]))
            );
        }
        if(associated_collection->empty()){
            associated_collection = nullptr;
        }

        /*SET UP MELA ATTRIBUTES HERE!*/
        

        m.setInputEvent(daughter_collection, associated_collection, mother_collection, true);

        float prob = 0;
        //computeFunction
        probs.push_back(prob);

        outputFile << prob << "\n";
        delete mother_collection;
        mother_collection = nullptr;
    }

    outputFile.close();
    dataFile->Close();

    return 0;
}
