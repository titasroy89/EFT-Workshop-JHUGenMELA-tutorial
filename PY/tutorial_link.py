import Mela
import uproot
import numpy as np


if __name__ == "__main__":
    m = Mela.Mela(13, 125, Mela.VerbosityLevel.SILENT)
    data_path = "../SAMPLE_DATA/ggHSample_4l.root"
    # data_path = "../SAMPLE_DATA/EWSample_4l.root"

    dataFile = uproot.open(data_path)

    tree = dataFile["eventTree"]
    data = tree.arrays(
        [
            "LHEDaughterId", "LHEDaughterPt", "LHEDaughterEta", "LHEDaughterPhi", "LHEDaughterMass",
            "LHEAssociatedParticleId", "LHEAssociatedParticlePt", "LHEAssociatedParticleEta", "LHEAssociatedParticlePhi", "LHEAssociatedParticleMass",
            "LHEMotherId", "LHEMotherPz", "LHEMotherE"
        ],
        library='np'
    )
    f = open("probs_output.txt", "w+")
    probs = []
    for i in range(tree.num_entries):
        mothers = Mela.SimpleParticleCollection_t(
            data["LHEMotherId"][i],
            [0]*len(data["LHEMotherId"][i]),
            [0]*len(data["LHEMotherId"][i]),
            data["LHEMotherPz"][i],
            data["LHEMotherE"][i],
            False
        )

        daughters = Mela.SimpleParticleCollection_t(
            data["LHEDaughterId"][i],
            data["LHEDaughterPt"][i],
            data["LHEDaughterEta"][i],
            data["LHEDaughterPhi"][i],
            data["LHEDaughterMass"][i],
            True
        )

        associated = Mela.SimpleParticleCollection_t(
            data["LHEAssociatedParticleId"][i],
            data["LHEAssociatedParticlePt"][i],
            data["LHEAssociatedParticleEta"][i],
            data["LHEAssociatedParticlePhi"][i],
            data["LHEAssociatedParticleMass"][i],
            True
        )

        #SET UP MELA ATTRIBUTES HERE!
        m.setInputEvent(daughters, associated, mothers, True)
        prob = None #replace with compute function
        probs.append(prob)

        f.write(f"{prob:.3e}\n")

    f.close()
    dataFile.close()