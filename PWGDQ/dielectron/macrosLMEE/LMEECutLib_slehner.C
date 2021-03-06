#ifndef LMEECutLib_slehner
#define LMEECutLib_slehner

class LMEECutLib {
    
  
private:
      
    
public:
  
  LMEECutLib() {  
  ::Info("LMEECutLib","CREATE NEW LMEECUTLIB slehner");
    pidFilterCuts = new AliDielectronPID("PIDCuts1","PIDCuts1");
    fUsedVars= new TBits(AliDielectronVarManager::kNMaxValues);
    
  }
  static AliDielectronPID* GetPIDCutsAna();

  AliDielectronCutGroup* GetTrackCuts(int trsel=0, int pidsel=0);
  AliDielectronEventCuts* GetEventCuts(int sel);
  static TH3D SetEtaCorrectionTPC( Int_t corrXdim, Int_t corrYdim, Int_t corrZdim, Bool_t runwise);
  static AliDielectronPID* pidFilterCuts;
  static TBits *fUsedVars;               // used variables
  TH1 *fPostPIDCntrdCorr;   // post pid correction object for electron sigma centroids in TPC
};

static TH3D LMEECutLib::SetEtaCorrectionTPC( Int_t corrXdim, Int_t corrYdim, Int_t corrZdim, Bool_t runwise, int sel) {

    
  ::Info("LMEECutLib::SetEtaCorrectionTPC","starting LMEECutLib::SetEtaCorrectionTPC()\n");
  TString path="alien:///alice/cern.ch/user/s/selehner/recal/recalib_data_tpc_nsigmaele.root";
  gSystem->Exec(TString::Format("alien_cp %s .",path.Data()));
  ::Info("LMEECutLib::SetEtaCorrectionTPC","Copy TPC correction from Alien: %s",path.Data());
  _file = TFile::Open("recalib_data_tpc_nsigmaele.root");
  
  TH3D* mean = dynamic_cast<TH3D*>(_file->Get("sum_mean_correction"));
  TH3D* width= dynamic_cast<TH3D*>(_file->Get("sum_width_correction"));
  
  // AliDielectron::SetCentroidCorrFunction
  UInt_t valType[20] = {0};
  valType[0]=corrXdim;     valType[1]=corrYdim;     valType[2]=corrZdim;
  AliDielectronHistos::StoreVariables(mean, valType);
  // clone temporare histogram, otherwise it will not be streamed to file!
  TString key = Form("cntrd%d%d%d",corrXdim,corrYdim,corrZdim);
  fPostPIDCntrdCorr = (TH1*)mean->Clone(key.Data());
  // check for corrections and add their variables to the fill map
  if(fPostPIDCntrdCorr)  {
    printf("POST TPC PID CORRECTION added for centroids:  ");
    switch(fPostPIDCntrdCorr->GetDimension()) {
    case 3: printf(" %s, ",fPostPIDCntrdCorr->GetZaxis()->GetName());
    case 2: printf(" %s, ",fPostPIDCntrdCorr->GetYaxis()->GetName());
    case 1: printf(" %s ",fPostPIDCntrdCorr->GetXaxis()->GetName());
    }
    printf("\n");
    fUsedVars->SetBitNumber(corrXdim, kTRUE);
    fUsedVars->SetBitNumber(corrYdim, kTRUE);
    fUsedVars->SetBitNumber(corrZdim, kTRUE);
  }
  
  if(fPostPIDCntrdCorr)     AliDielectronPID::SetCentroidCorrFunction(fPostPIDCntrdCorr);
  
  
  
  // AliDielectron::SetWidthCorrFunction
  {
  UInt_t valType[20] = {0};
  valType[0]=corrXdim;     valType[1]=corrYdim;     valType[2]=corrZdim;
  AliDielectronHistos::StoreVariables(width, valType);
  // clone temporare histogram, otherwise it will not be streamed to file!
  TString key = Form("wdth%d%d%d",corrXdim,corrYdim,corrZdim);
  fPostPIDWdthCorr = (TH1*)width->Clone(key.Data());
  // check for corrections and add their variables to the fill map
  if(fPostPIDWdthCorr)  {
    printf("POST TPC PID CORRECTION added for widths:  ");
    switch(fPostPIDWdthCorr->GetDimension()) {
    case 3: printf(" %s, ",fPostPIDWdthCorr->GetZaxis()->GetName());
    case 2: printf(" %s, ",fPostPIDWdthCorr->GetYaxis()->GetName());
    case 1: printf(" %s ",fPostPIDWdthCorr->GetXaxis()->GetName());
    }
    printf("\n");
    fUsedVars->SetBitNumber(corrXdim, kTRUE);
    fUsedVars->SetBitNumber(corrYdim, kTRUE);
    fUsedVars->SetBitNumber(corrZdim, kTRUE);
        }
    }
  
  if(fPostPIDWdthCorr)      AliDielectronPID::SetWidthCorrFunction(fPostPIDWdthCorr);

  if(sel==1){
        if(mean)   ::Info("LMEECutLib::SetEtaCorrectionTPC","Mean Correction Histo loaded, entries: %f",mean->GetEntries());
        else {
        ::Info("LMEECutLib::SetEtaCorrectionTPC","Mean Correction Histo not loaded! entries: %f",mean->GetEntries());
        return 0;
        }
      return *mean;
  }
  else{
        if(width)   ::Info("LMEECutLib::SetEtaCorrectionTPC","Width Correction Histo loaded, entries: %f",width->GetEntries());
        else {
        ::Info("LMEECutLib::SetEtaCorrectionTPC","Width Correction Histo not loaded! entries: %f",width->GetEntries());
        return 0;
        }
      return *width;
  }
}  

// Note: event cuts are identical for all analysis 'cutDefinition's that run together!
AliDielectronEventCuts* LMEECutLib::GetEventCuts(int sel) {
  ::Info("AddTask_slehner_TreeMakeWCutLib","setting event cuts");
  
  AliDielectronEventCuts* eventCuts = new AliDielectronEventCuts("eventCuts","evcuts");
  
  eventCuts->SetVertexType(AliDielectronEventCuts::kVtxAny);
  eventCuts->SetRequireVertex();
  eventCuts->SetMinVtxContributors(1);
  eventCuts->SetVertexZ(-10.,+10.);
    
  return eventCuts;
}


AliDielectronPID* LMEECutLib::GetPIDCutsAna(int sel) {
    

//  pidFilterCuts = new AliDielectronPID("PIDCuts1","PIDCuts1");
  ::Info("AddTask_slehner_TreeMakeWCutLib"," >>>>>>>>>>>>>>>>>>>>>> GetPIDCutsAna() >>>>>>>>>>>>>>>>>>>>>> ");
  //nanoAOD Prefilter cuts - should always be applied  if working on nanoAODs in real data, otherwise MC and real data might not use same cuts
//  pidFilterCuts->AddCut(AliDielectronPID::<kTPC,AliPID::kElectron,-4.,4.);
//  pidFilterCuts->AddCut(AliDielectronPID::kTPC,AliPID::kPion,-100.,3.5,0.,0.,kTRUE);
//  pidFilterCuts->AddCut(AliDielectronPID::kITS,AliPID::kElectron,-4.,4.);

//  switch (sel) {
      ::Info("AddTask_slehner_TreeMakeWCutLib","chose PID cut %d",sel); 
//      case 0:
      // additional PID cuts: carsten analysis PID cut (Physics Forum 12.04.18)
      pidFilterCuts->AddCut(AliDielectronPID::kTPC,AliPID::kElectron, -2, 3.0 , 0. ,100., kFALSE);
      pidFilterCuts->AddCut(AliDielectronPID::kTPC,AliPID::kPion, -100, 4.5 , 0. ,100., kTRUE);
      pidFilterCuts->AddCut(AliDielectronPID::kITS,AliPID::kElectron, -3.5, 0.5 , 0. ,100., kFALSE);
      pidFilterCuts->AddCut(AliDielectronPID::kTOF,AliPID::kElectron, -3.0 , 3.0 , 0. ,100., kFALSE, AliDielectronPID::kIfAvailable);
//      break;
//  }
  
  return(pidFilterCuts);       //Add nanoAODfilter PID cuts

}

AliDielectronCutGroup* LMEECutLib::GetTrackCuts(int selTr, int selPID) {
  ::Info("AddTask_slehner_TreeMakeWCutLib"," >>>>>>>>>>>>>>>>>>>>>> GetTrackSelectionAna() >>>>>>>>>>>>>>>>>>>>>> ");
  AliDielectronCutGroup* trackCuts = new AliDielectronCutGroup("CutsAna","CutsAna",AliDielectronCutGroup::kCompAND);
    
  ////Add nanoAOD filter cuts
  AliDielectronVarCuts *varCutsFilter   = new AliDielectronVarCuts("VarCuts","VarCuts");
  AliDielectronTrackCuts *trkCutsFilter = new AliDielectronTrackCuts("TrkCuts","TrkCuts");

  trkCutsFilter->SetITSclusterCut(AliDielectronTrackCuts::kOneOf, 3); // SPD any
  trkCutsFilter->SetRequireITSRefit(kTRUE);
  trkCutsFilter->SetRequireTPCRefit(kTRUE); // not useful when using prefilter

  varCutsFilter->AddCut(AliDielectronVarManager::kPt,           0.2, 8.0);
  varCutsFilter->AddCut(AliDielectronVarManager::kEta,         -0.8,   0.8);
  varCutsFilter->AddCut(AliDielectronVarManager::kNclsTPC,      80.0, 160.0);
  varCutsFilter->AddCut(AliDielectronVarManager::kNclsITS,      3.0, 100.0);
  varCutsFilter->AddCut(AliDielectronVarManager::kITSchi2Cl,    0.0,   15.0);
//  //varCutsFilter->AddCut(AliDielectronVarManager::kNclsSITS,     0.0,   3.1); // means 0 and 1 shared Cluster    // did not work on ESD when filtering nanoAODs
  varCutsFilter->AddCut(AliDielectronVarManager::kTPCchi2Cl,    0.0,   8.0);
  varCutsFilter->AddCut(AliDielectronVarManager::kNFclsTPCr,    80.0, 160.0);
  varCutsFilter->AddCut(AliDielectronVarManager::kImpactParXY, -1.0,   1.0);
  varCutsFilter->AddCut(AliDielectronVarManager::kImpactParZ,  -3.0,   3.0);
  varCutsFilter->AddCut(AliDielectronVarManager::kKinkIndex0,   0.);
  
////  switch (selTr) {

    ::Info("AddTask_slehner_TreeMakeWCutLib","chose track cut %d");      
      
// //     case 0:

            AliDielectronVarCuts* trackCutsAOD =new AliDielectronVarCuts("trackCutsAOD","trackCutsAOD");     
            trackCutsAOD->AddCut(AliDielectronVarManager::kImpactParXY, -1.0,   1.0);
            trackCutsAOD->AddCut(AliDielectronVarManager::kImpactParZ,  -3.0,   3.0);
////            trackCutsAOD->AddCut(AliDielectronVarManager::kNclsITS,      4.0, 100.0);
            trackCutsAOD->AddCut(AliDielectronVarManager::kNclsTPC,      100.0, 160.0);
// //           trackCutsAOD->AddCut(AliDielectronVarManager::kITSchi2Cl,    0.0,   4.0);
//  //          trackCutsAOD->AddCut(AliDielectronVarManager::kTPCchi2Cl,    0.0,   4.0);
            trackCutsAOD->AddCut(AliDielectronVarManager::kNFclsTPCr,    100.0, 160.0);
            trackCutsAOD->AddCut(AliDielectronVarManager::kNFclsTPCfCross,     0.95, 1.05);

            AliDielectronCutGroup* SharedClusterCut = new AliDielectronCutGroup("SharedClusterCut","SharedClusterCut",AliDielectronCutGroup::kCompOR);
            double delta = 0.00001;
            AliDielectronVarCuts* trackCutsSharedCluster0 = new AliDielectronVarCuts("trackCutsSharedCluster0", "trackCutsSharedCluster0");
            trackCutsSharedCluster0->AddCut(AliDielectronVarManager::kNclsSMapITS, 0-delta, 0+delta);
            AliDielectronVarCuts* trackCutsSharedCluster2 = new AliDielectronVarCuts("trackCutsSharedCluster2", "trackCutsSharedCluster2");
            trackCutsSharedCluster2->AddCut(AliDielectronVarManager::kNclsSMapITS, 2-delta, 2+delta);
            AliDielectronVarCuts* trackCutsSharedCluster4 = new AliDielectronVarCuts("trackCutsSharedCluster4", "trackCutsSharedCluster4");
            trackCutsSharedCluster4->AddCut(AliDielectronVarManager::kNclsSMapITS, 4-delta, 4+delta);
            AliDielectronVarCuts* trackCutsSharedCluster8 = new AliDielectronVarCuts("trackCutsSharedCluster8", "trackCutsSharedCluster8");
            trackCutsSharedCluster8->AddCut(AliDielectronVarManager::kNclsSMapITS, 8-delta, 8+delta);
            AliDielectronVarCuts* trackCutsSharedCluster16 = new AliDielectronVarCuts("trackCutsSharedCluster16", "trackCutsSharedCluster16");
            trackCutsSharedCluster16->AddCut(AliDielectronVarManager::kNclsSMapITS, 16-delta, 16+delta);
            AliDielectronVarCuts* trackCutsSharedCluster32 = new AliDielectronVarCuts("trackCutsSharedCluster32", "trackCutsSharedCluster32");
            trackCutsSharedCluster32->AddCut(AliDielectronVarManager::kNclsSMapITS, 32-delta, 32+delta);
            SharedClusterCut->AddCut(trackCutsSharedCluster0);
            SharedClusterCut->AddCut(trackCutsSharedCluster2);
            SharedClusterCut->AddCut(trackCutsSharedCluster4);
            SharedClusterCut->AddCut(trackCutsSharedCluster8);
            SharedClusterCut->AddCut(trackCutsSharedCluster16);
            SharedClusterCut->AddCut(trackCutsSharedCluster32);
            
            AliDielectronTrackCuts *trackCutsDiel = new AliDielectronTrackCuts("trackCutsDiel","trackCutsDiel");
            trackCutsDiel->SetAODFilterBit(AliDielectronTrackCuts::kGlobalNoDCA);   //(1<<4) -> error
            trackCutsDiel->SetClusterRequirementITS(AliESDtrackCuts::kSPD, AliESDtrackCuts::kFirst);

            trackCuts->AddCut(varCutsFilter);
            trackCuts->AddCut(trkCutsFilter);
            
            trackCuts->AddCut(trackCutsDiel);
            trackCuts->AddCut(trackCutsAOD);
            
            trackCuts->AddCut(GetPIDCutsAna(selPID));

  
  return trackCuts;
}






