/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice */
/* $Id: $ */

/////////////////////////////////////////////////
// AliAnalysisTaskCMEV0PID:
// analysis task for ZDC gain Equalization
// and CME analysis for identified particles 
// using VZERO (and ZDC) Detector
// Author: Rihan Haque (mhaque@cern.ch)
// and R Sultana
/////////////////////////////////////////////////

#ifndef AliAnalysisTaskCMEV0PID_H
#define AliAnalysisTaskCMEV0PID_H

#include "AliAnalysisTaskSE.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TList.h"
#include "TFile.h"
#include "TString.h"
#include "TProfile.h"
#include "TProfile2D.h"

class    AliVEvent;      
class    AliVVertex;    
class    AliESDEvent;       
class    AliAODEvent;      
class    AliPIDResponse;    
class    AliMultSelection;    
class    AliAnalysisUtils;




class AliAnalysisTaskCMEV0PID : public AliAnalysisTaskSE {

 public:

  AliAnalysisTaskCMEV0PID();
  AliAnalysisTaskCMEV0PID(const char *name);
  virtual ~AliAnalysisTaskCMEV0PID();
  virtual void UserCreateOutputObjects();
  virtual void UserExec(Option_t * /*option*/);
    
  //User Defined Functions:
  void SetFilterBit(Int_t b)                 {this->fFilterBit = b;}
  void SetEventPlaneHarmonic(Int_t pn)       {this->gPsiN     = pn;}

  void SetNSigmaCutTPC(Float_t b)            {this->fNSigmaCut = b;}
  void SetPtRangeMin(Float_t b)              {this->fMinPtCut  = b;}
  void SetPtRangeMax(Float_t b)              {this->fMaxPtCut  = b;}
  void SetEtaRangeMin(Float_t b)             {this->fMinEtaCut = b;}
  void SetEtaRangeMax(Float_t b)             {this->fMaxEtaCut = b;}
  void SetCollisionSystem(TString s)         {this->sNucleiTP  = s;}

  void SetCentralityPercentileMin(Float_t b) {this->fCentralityPercentMin = b;}
  void SetCentralityPercentileMax(Float_t b) {this->fCentralityPercentMax = b;}
  void SetFBEfficiencyList(TList *flist)     {this->fListFBHijing  =  flist;}
  
  void SetFlagForMCcorrection(Bool_t b)      {this->bApplyMCcorr   = b;}
  void SetFlagV0MGainCorr(Bool_t b)          {this->bV0MGainCorr   = b;}
  void SetFlagSkipPileUpCuts(Bool_t b)       {this->bSkipPileUpCut = b;}
  void SetFlagFillNUAforPID(Bool_t b)        {this->bFillNUAHistPID = b;}



  void SetFBEfficiencyFilePath(TString path) {this->sPathOfMCFile  =   path;}
  void SetPileUpCutParam(Float_t m,Float_t c) {this->fPileUpSlopeParm = m;  this->fPileUpConstParm = c;}
  void SetListForNUACorr(TList *fln)         {this->fListNUACorr   = fln;}
  void SetListForV0MCorr(TList *flv)         {this->fListV0MCorr   = flv;}

  

   

 protected:


 private:

  AliVEvent             *fVevent;             //! event
  AliESDEvent           *fESD;                //! esd
  AliAODEvent           *fAOD;                //! aod
  AliPIDResponse        *fPIDResponse;        //! PID response Handler
  AliMultSelection      *fMultSelection;      //!
  AliAnalysisUtils      *fAnalysisUtil;       //! Event selection
  TList                 *fListHist;           //!
  TFile                 *mfileFBHijing;       //!
  TList                 *fListFBHijing;       //!
  TList                 *fListNUACorr;        //
  TList                 *fListV0MCorr;        //
  //histograms:
  TH1F         *fHistTaskConfigParameters;   //! Task input parameters FB / cut values etc.
  TH1F                  *fHistPileUpCount;   //!
  TH1F               *fHistMultSelPUCount;   //!
  TH2F                  *fHistEtaPtBefore;   //! Eta-Pt acceptance
  TH2F                   *fHistEtaPtAfter;   //! Eta-Pt acceptance
  TH2F        *fHistTPCvsGlobalMultBefore;   //!
  TH2F         *fHistTPCvsGlobalMultAfter;   //!

  TH2F             *fHistTPCdEdxvsPBefore;   //!
  TH2F              *fHistTPCdEdxvsPAfter;   //!
  TH2F             *fHistTOFBetavsPBefore;   //!
  TH2F              *fHistTOFBetavsPAfter;   //!
  TH2F            *fHistTOFMassvsPtBefore;   //!

  TH2F                *fHistTOFMatchCount;   //!    

  TH2F            *fHistTPCVsESDTrkBefore;   //!  
  TH2F             *fHistTPCVsESDTrkAfter;   //!    

  TH2F           *fHistTPConlyVsCL1Before;   //!  
  TH2F           *fHistTPConlyVsV0MBefore;   //!    
  TH2F            *fHistTPConlyVsCL1After;   //!    
  TH2F            *fHistTPConlyVsV0MAfter;   //!   
  TH2F            *fHistGlobalVsV0MBefore;   //!   
  TH2F             *fHistGlobalVsV0MAfter;   //!   

  TH2F              *fHistRawVsCorrMultFB;   //!  
  TH2F                *hCentvsTPCmultCuts;   //! 

  TH2F             *fHV0AEventPlaneVsCent;   //!
  TH2F             *fHV0CEventPlaneVsCent;   //!
  TH2F            *fHTPCAEventPlaneVsCent;   //!
  TH2F            *fHTPCCEventPlaneVsCent;   //!
  TH2F                    *fV0MultChVsRun;   //!   To fill VOM multiplicity 
  
  TH1F                   *fCentDistBefore;   //!   without PileUp cut
  TH1F                    *fCentDistAfter;   //!   with PileUp cut
  TH1D                      *fHCorrectV0M;   //!   To read Gain Correction file.
  TH2D                   *fHAvgerageQnV0A;   //!   V0A Average <Qn>, n=2,3
  TH2D                   *fHAvgerageQnV0C;   //!   V0C Average <Qn>, n=2,3

  TProfile              *fV0AQ2xVsCentRun; //!
  TProfile              *fV0AQ2yVsCentRun; //!
  TProfile              *fV0CQ2xVsCentRun; //!
  TProfile              *fV0CQ2yVsCentRun; //!
  TProfile              *fV0AQ3xVsCentRun; //!
  TProfile              *fV0AQ3yVsCentRun; //!
  TProfile              *fV0CQ3xVsCentRun; //!
  TProfile              *fV0CQ3yVsCentRun; //!


  TProfile              *fTPCAQ2xVsCentRun; //!
  TProfile              *fTPCAQ2yVsCentRun; //!
  TProfile              *fTPCCQ2xVsCentRun; //!
  TProfile              *fTPCCQ2yVsCentRun; //!
  TProfile              *fTPCAQ3xVsCentRun; //!
  TProfile              *fTPCAQ3yVsCentRun; //!
  TProfile              *fTPCCQ3xVsCentRun; //!
  TProfile              *fTPCCQ3yVsCentRun; //!
  TProfile              *fTPCAQ4xVsCentRun; //!
  TProfile              *fTPCAQ4yVsCentRun; //!
  TProfile              *fTPCCQ4xVsCentRun; //!
  TProfile              *fTPCCQ4yVsCentRun; //!











  Int_t                 fFilterBit;  //
  Int_t                      gPsiN;  //
  Int_t                 fOldRunNum;  //
  Int_t                fEventCount;  //!
  Float_t               fNSigmaCut;  //
  Float_t                fMinPtCut;  //
  Float_t                fMaxPtCut;  //
  Float_t               fMinEtaCut;  //
  Float_t               fMaxEtaCut;  //
  Float_t    fCentralityPercentMin;  //
  Float_t    fCentralityPercentMax;  //
  Float_t         fPileUpSlopeParm;  //
  Float_t         fPileUpConstParm;  //

  Bool_t              bApplyMCcorr;  //
  Bool_t              bV0MGainCorr;  //
  Bool_t            bSkipPileUpCut;  //
  Bool_t           bFillNUAHistPID;  //

  TString            sPathOfMCFile;  //
  TString                sNucleiTP;  //
 






  TH1F            *fHistEventCount;   //!    last in the list












  //-------- Arrays ----------
  TH1F           *fHistPtwithTPCNsigma[3];   //!
  TH1F          *fHistPtwithTOFmasscut[3];   //!
  TH1F           *fHistPtwithTOFSignal[3];   //!
  TH2F        *fHistTOFnSigmavsPtAfter[3];   //!
  TH2F        *fHistTPCnSigmavsPtAfter[3];   //!
  TH3F     *fHistTPCTOFnSigmavsPtAfter[3];   //!
  TH2F       *fHistTPCdEdxvsPtPIDAfter[3];   //!


  
  TH3D                *fHCorrectNUApos[5];   //! 5 centrality bin, read NUA from file
  TH3D                *fHCorrectNUAneg[5];   //! 5 centrality bin, read NUA from file

  TH3D                *fHCorrectNUAposPion[5];   //! 5 centrality bin, read NUA from file
  TH3D                *fHCorrectNUAnegPion[5];   //! 5 centrality bin, read NUA from file

  TH3D                *fHCorrectNUAposKaon[5];   //! 5 centrality bin, read NUA from file
  TH3D                *fHCorrectNUAnegKaon[5];   //! 5 centrality bin, read NUA from file

  TH3D                *fHCorrectNUAposProton[5];   //! 5 centrality bin, read NUA from file
  TH3D                *fHCorrectNUAnegProton[5];   //! 5 centrality bin, read NUA from file



  //CME Using Event plane method: Charge
  TProfile     *fHist_Corr3p_EP_Norm_PN[2][4];  //! 
  TProfile     *fHist_Corr3p_EP_Norm_PP[2][4];  //!
  TProfile     *fHist_Corr3p_EP_Norm_NN[2][4];  //!
  TProfile     *fHist_Reso2n_EP_Norm_Det[2][4]; //! 

  //CME Using Event plane method: Pion
  TProfile     *fHist_Corr3p_Pion_EP_Norm_PN[2][4];  //! 
  TProfile     *fHist_Corr3p_Pion_EP_Norm_PP[2][4];  //!
  TProfile     *fHist_Corr3p_Pion_EP_Norm_NN[2][4];  //!

  //CME Using Event plane method: Kaon
  TProfile     *fHist_Corr3p_Kaon_EP_Norm_PN[2][4];  //! 
  TProfile     *fHist_Corr3p_Kaon_EP_Norm_PP[2][4];  //!
  TProfile     *fHist_Corr3p_Kaon_EP_Norm_NN[2][4];  //!

  //CME Using Event plane method: Proton
  TProfile     *fHist_Corr3p_Proton_EP_Norm_PN[2][4];  //! 
  TProfile     *fHist_Corr3p_Proton_EP_Norm_PP[2][4];  //!
  TProfile     *fHist_Corr3p_Proton_EP_Norm_NN[2][4];  //!





  // NUA histograms:
  TH3F        *fHist3DEtaPhiVz_Pos_Run[4][5];  //! 4 particle 5 centrality bin 
  TH3F        *fHist3DEtaPhiVz_Neg_Run[4][5];  //! 4 particle 5 centrality bin 



  TH1D           *fFB_Efficiency_Cent[10];   //!

  //--------- PileUp Functions -----------
  Bool_t CheckEventIsPileUp(AliAODEvent* faod);
  Bool_t PileUpMultiVertex(const AliAODEvent* faod);
  double GetWDist(const AliVVertex* v0, const AliVVertex* v1);

  //for NUA and gain corrections:
  void  GetNUACorrectionHist(Int_t run);
  void  GetV0MCorrectionHist(Int_t run);


  
  //----------- other functions ----------
  void  SetUpCentralityOutlierCut();
  void  SetupEventAndTaskConfigInfo();
  void  SetupMCcorrectionMap(TString sMCfilePath);
  Int_t GetCentralityScaled0to10(Float_t fCent);




  
  AliAnalysisTaskCMEV0PID(const AliAnalysisTaskCMEV0PID &other);
  AliAnalysisTaskCMEV0PID &operator=(const AliAnalysisTaskCMEV0PID &other);    
  ClassDef(AliAnalysisTaskCMEV0PID, 1) 

};

#endif