#ifndef AliSigma0ParticleBase_H
#define AliSigma0ParticleBase_H

#include "AliESDtrack.h"
#include "AliMCEvent.h"
#include "AliMCParticle.h"
#include "Riostream.h"
#include "TObject.h"

class AliSigma0ParticleBase {
 public:
  AliSigma0ParticleBase();
  virtual ~AliSigma0ParticleBase() {}
  AliSigma0ParticleBase &operator=(const AliSigma0ParticleBase &obj);
  AliSigma0ParticleBase(const AliESDtrack *track, int pdg,
                        const float magneticField, int filterbit = 0);

  double ComputeRelK(const AliSigma0ParticleBase &part2,
                     bool debug = false) const;
  double ComputeRelKMC(const AliSigma0ParticleBase &part2) const;
  double ComputePhiStar(const AliVTrack &track, const float magneticField,
                        const float radius) const;
  void ProcessMCInfo(AliMCParticle *mcParticle, AliMCEvent *mcEvent);

  void SetMass(double mass) { fMass = mass; }
  void SetUse(bool use) { fUse = use; }
  void SetMCP(double px, double py, double pz) {
    fPMC[0] = px;
    fPMC[1] = py;
    fPMC[2] = pz;
  }
  void SetPDGCode(int pdg) { fPDGCode = pdg; }
  void SetDCA(double r, double z) {
    fDCAr = r;
    fDCAz = z;
  }

  double GetPx() const { return fP[0]; }
  double GetPy() const { return fP[1]; }
  double GetPz() const { return fP[2]; }

  double GetPxMC() const { return fPMC[0]; }
  double GetPyMC() const { return fPMC[1]; }
  double GetPzMC() const { return fPMC[2]; }
  double GetPtMC() const {
    return std::sqrt(fPMC[0] * fPMC[0] + fPMC[1] * fPMC[1]);
  }

  int GetCharge() const { return fCharge; }
  int GetPDGcode() const { return fPDGCode; }
  int GetPDGcodeMother() const { return fPDGCodeMother; }
  double GetMass() const { return fMass; }
  int GetQ() const { return fQ; }
  double GetPt() const { return fPt; }
  int GetTrackLabel() const { return fTrackLabel; }
  double GetPhi() const { return fPhi; }
  double GetEta() const { return fEta; }
  bool GetIsUse() const { return fUse; }
  double GetDCAr() { return fDCAr; }
  double GetDCAz() { return fDCAz; }
  double GetPhiStar(int iRadius) const { return fPhistar[iRadius]; }
  int GetMCLabel() const { return fMClabel; }

 protected:
  double fP[3];
  double fPMC[3];

  int fPDGCode;
  int fPDGCodeMother;
  double fMass;
  int fQ;
  double fPt;
  int fTrackLabel;
  int fMClabel;
  double fPhi;
  double fEta;

  int fCharge;
  double fDCAz;
  double fDCAr;
  bool fUse;

  double fPhistar[9];

 private:
  ClassDef(AliSigma0ParticleBase, 2)
};

#endif
