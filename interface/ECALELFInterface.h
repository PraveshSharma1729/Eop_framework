#ifndef ECALELFINTERFACE__
#define ECALELFINTERFACE__

#include <iostream>
#include <string>
#include <vector>

#include "CfgManager.h"
#include "CfgManagerT.h"

#include "TTree.h"
#include "TChain.h"
#include "TString.h"
#include "TTreeFormula.h"
#include "TGraphErrors.h"
#include "TH2F.h"
#include "TFile.h"
#include "TObject.h"

class ECALELFInterface
{

 public:
  //---ctors---
  ECALELFInterface(CfgManager conf);
  //ECALELFInterface(TChain* ch, string selection_str, vector<string> BranchMethod);
  //---dtor---
  ~ECALELFInterface();
  //---utils--
  Long64_t GetEntries() {return chain_->GetEntries();}
  Long64_t GetEntry(const Long64_t &i);
  Bool_t   isSelected(const Int_t &i) {return selection_->EvalInstance(i);}
  Bool_t   isEB(const Int_t &i);
  Float_t  GetEnergy(const Int_t &i);
  Float_t  GetCharge(const Int_t &i);
  Float_t  GetMee() {return Mee_; };
  Float_t  GetEnergyRaw(const Int_t &i);
  Int_t    GeteventNumber() {return eventNumber_;}
  Float_t  GetESEnergy(const Int_t &i);
  Float_t  GetP(const Int_t &i);
  Float_t  GetEtaSC(const Int_t &i);
  Float_t  GetPhi(const Int_t &i);
  void     GetSeed(Int_t &ieta, Int_t &iphi, const Int_t &i);
  int      GetietaSeed(const Int_t &i);
  int      GetiphiSeed(const Int_t &i);
  std::vector<float>* GetERecHit(const Int_t &i)        {return ERecHit_[i];}
  std::vector<float>* GetfracRecHit(const Int_t &i)     {return fracRecHit_[i];}
  std::vector<int>*   GetXRecHit(const Int_t &i)        {return XRecHit_[i];}
  std::vector<int>*   GetYRecHit(const Int_t &i)        {return YRecHit_[i];}
  std::vector<int>*   GetZRecHit(const Int_t &i)        {return ZRecHit_[i];}
  std::vector<int>*   GetrecoFlagRecHit(const Int_t &i) {return recoFlagRecHit_[i];}

 protected:
  void BranchSelected(TChain* chain);
  void BranchExtraCalib(TChain* chain);

  TTreeFormula *selection_;
  std::string selection_str_;
  std::map<std::string,TChain*> ch_;
  TChain* chain_;
  int Ncurrtree_;

  ///! Declaration of leaf types
  UInt_t          runNumber_;
  Int_t           lumiBlock_;
  Int_t           eventNumber_;
  Short_t         chargeEle_[3];
  Short_t         xSeed_[3];
  Short_t         ySeed_[3];
  Float_t         etaSCEle_[3];
  Float_t         phiSCEle_[3];
  Float_t         etaEle_[3];
  Float_t         phiEle_[3];
  Float_t         rawEnergySCEle_[3];
  Float_t         energySCEle_[3];
  Float_t         esEnergySCEle_[3];
  Float_t         pAtVtxGsfEle_[3];
  Float_t         fbremEle_[3];
  Float_t         Mee_;
  

  ///! RecHit variables
  std::vector<float>   *ERecHit_[2];
  std::vector<int>     *XRecHit_[2];  //iETA
  std::vector<int>     *YRecHit_[2];  //iPHI
  std::vector<int>     *ZRecHit_[2];
  std::vector<int>     *recoFlagRecHit_[2];
  std::vector<float>   *fracRecHit_[2];
};


#endif
