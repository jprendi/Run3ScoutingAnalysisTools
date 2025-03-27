// -*- C++ -*-
//
// Package:    Run3ScoutingAnalysisTools/ScoutingTreeMakerRun3
// Class:      ScoutingDQMMakerRun3
//
/**\class ScoutingTreeMakerRun3 ScoutingDQMMakerRun3.cc Run3ScoutingAnalysisTools/ScoutingTreeMakerRun3/plugins/ScoutingDQMMakerRun3.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David Sperka
//         Created:  Sat, 11 Feb 2023 14:15:08 GMT
//
//

// system include files
#include <memory>
#include <TLorentzVector.h>

// user include files
#include "DQMServices/Core/interface/DQMEDAnalyzer.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"


#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"

#include "DataFormats/Scouting/interface/Run3ScoutingElectron.h"
#include "DataFormats/Scouting/interface/Run3ScoutingPhoton.h"
#include "DataFormats/Scouting/interface/Run3ScoutingPFJet.h"
#include "DataFormats/Scouting/interface/Run3ScoutingVertex.h"
#include "DataFormats/Scouting/interface/Run3ScoutingTrack.h"
#include "DataFormats/Scouting/interface/Run3ScoutingMuon.h"
#include "DataFormats/Scouting/interface/Run3ScoutingParticle.h"

#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "L1Trigger/L1TGlobal/interface/L1TGlobalUtil.h"
#include "DataFormats/L1TGlobal/interface/GlobalAlgBlk.h"
#include "HLTrigger/HLTcore/interface/TriggerExpressionData.h"
#include "HLTrigger/HLTcore/interface/TriggerExpressionEvaluator.h"
#include "HLTrigger/HLTcore/interface/TriggerExpressionParser.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h" 

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.

class ScoutingDQMMakerRun3 : public DQMEDAnalyzer {
public:
  explicit ScoutingDQMMakerRun3(const edm::ParameterSet&);
  ~ScoutingDQMMakerRun3() override;

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  // void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void bookHistograms(DQMStore::IBooker&, edm::Run const&, edm::EventSetup const&) override;

  const std::string outputInternalPath_;

  const edm::InputTag triggerResultsTag;
  const edm::EDGetTokenT<edm::TriggerResults>             triggerResultsToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingMuon> >      muonsToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingElectron> >  electronsToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingVertex> >    primaryVerticesToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingVertex> >    verticesToken;
  const edm::EDGetTokenT<double>                          rhoToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingPhoton> >  photonsToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingParticle> >  pfcandsToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingPFJet> >  pfjetsToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingTrack> >  tracksToken;

  std::vector<std::string> triggerPathsVector;
  std::map<std::string, int> triggerPathsMap;

  bool doL1;
  triggerExpression::Data triggerCache_;

  edm::InputTag                algInputTag_;
  edm::InputTag                extInputTag_;
  edm::EDGetToken              algToken_;
  std::unique_ptr<l1t::L1TGlobalUtil> l1GtUtils_;
  std::vector<std::string>     l1Seeds_;
  std::vector<bool>            l1Result_;


  dqm::reco::MonitorElement* trackIso1_mu_hist;
  dqm::reco::MonitorElement* trackIso2_mu_hist;
  dqm::reco::MonitorElement* nValidPixelHits1_mu_hist;
  dqm::reco::MonitorElement* nValidPixelHits2_mu_hist;
  dqm::reco::MonitorElement* nTrackerLayersWithMeasurement1_mu_hist;
  dqm::reco::MonitorElement* nTrackerLayersWithMeasurement2_mu_hist;
  dqm::reco::MonitorElement* trk_chi21_mu_hist;
  dqm::reco::MonitorElement* trk_chi22_mu_hist;


  dqm::reco::MonitorElement* dimuon_hist;
  dqm::reco::MonitorElement* pt_dimu_hist;
  dqm::reco::MonitorElement* dr_mu_hist; 
  dqm::reco::MonitorElement* pt1_mu_hist;
  dqm::reco::MonitorElement* pt2_mu_hist;
  dqm::reco::MonitorElement* eta1_mu_hist;
  dqm::reco::MonitorElement* eta2_mu_hist;
  dqm::reco::MonitorElement* phi1_mu_hist;
  dqm::reco::MonitorElement* phi2_mu_hist;
  dqm::reco::MonitorElement* rho_hist;
  dqm::reco::MonitorElement* vtxMatch_hist;
  dqm::reco::MonitorElement* vtxChi2_hist;
  dqm::reco::MonitorElement* vtxNdof_hist;
  dqm::reco::MonitorElement* Lxy_hist;
  dqm::reco::MonitorElement* LxyErr_hist;
  dqm::reco::MonitorElement* LxySig_hist;
  dqm::reco::MonitorElement* vtxXError_hist;
  dqm::reco::MonitorElement* vtxYError_hist;
  dqm::reco::MonitorElement* vtxZError_hist;



  dqm::reco::MonitorElement* diele_hist;
  dqm::reco::MonitorElement* pt_diele_hist;
  dqm::reco::MonitorElement* dr_ele_hist;
  dqm::reco::MonitorElement* pt1_ele_hist;
  dqm::reco::MonitorElement* pt2_ele_hist;
  dqm::reco::MonitorElement* eta1_ele_hist;
  dqm::reco::MonitorElement* eta2_ele_hist;
  dqm::reco::MonitorElement* phi1_ele_hist;
  dqm::reco::MonitorElement* phi2_ele_hist;
  dqm::reco::MonitorElement* preshowerEnergy_ele_hist;
  dqm::reco::MonitorElement* corrEcalEnergyError_ele_hist;
  dqm::reco::MonitorElement* dEtaIn_ele_hist;
  dqm::reco::MonitorElement* sigmaIetaIeta_ele_hist;
  dqm::reco::MonitorElement* hOverE_ele_hist;
  dqm::reco::MonitorElement* ooEMOop_ele_hist;
  dqm::reco::MonitorElement* missingHits_ele_hist;
  dqm::reco::MonitorElement* ecalIso_ele_hist;
  dqm::reco::MonitorElement* hcalIso_ele_hist;
  dqm::reco::MonitorElement* trackIso_ele_hist;
  dqm::reco::MonitorElement* r9_ele_hist;
  dqm::reco::MonitorElement* sMin_ele_hist;
  dqm::reco::MonitorElement* sMaj_ele_hist;
  dqm::reco::MonitorElement* rawEnergy_ele_hist;


  dqm::reco::MonitorElement* pt1_pho_hist;
  dqm::reco::MonitorElement* pt2_pho_hist;
  dqm::reco::MonitorElement* eta1_pho_hist;
  dqm::reco::MonitorElement* eta2_pho_hist;
  dqm::reco::MonitorElement* phi1_pho_hist;
  dqm::reco::MonitorElement* phi2_pho_hist;
  dqm::reco::MonitorElement* rawEnergy_pho_hist;
  dqm::reco::MonitorElement* preshowerEnergy_pho_hist;
  dqm::reco::MonitorElement* corrEcalEnergyError_pho_hist;
  dqm::reco::MonitorElement* sigmaIetaIeta_pho_hist;
  dqm::reco::MonitorElement* hOverE_pho_hist;
  dqm::reco::MonitorElement* ecalIso_pho_hist;
  dqm::reco::MonitorElement* hcalIso_pho_hist;
  dqm::reco::MonitorElement* trackIso_pho_hist;
  dqm::reco::MonitorElement* r9_pho_hist;
  dqm::reco::MonitorElement* sMin_pho_hist;
  dqm::reco::MonitorElement* sMaj_pho_hist;


  dqm::reco::MonitorElement* pt1_PFJ_hist;
  dqm::reco::MonitorElement* pt2_PFJ_hist;
  dqm::reco::MonitorElement* eta1_PFJ_hist;
  dqm::reco::MonitorElement* eta2_PFJ_hist;
  dqm::reco::MonitorElement* phi1_PFJ_hist;
  dqm::reco::MonitorElement* phi2_PFJ_hist;
  dqm::reco::MonitorElement* m_PFJ_hist;
  dqm::reco::MonitorElement* jetArea_PFJ_hist;
  dqm::reco::MonitorElement* chargedHadronEnergy_PFJ_hist;
  dqm::reco::MonitorElement* neutralHadronEnergy_PFJ_hist;
  dqm::reco::MonitorElement* photonEnergy_PFJ_hist;
  dqm::reco::MonitorElement* electronEnergy_PFJ_hist;
  dqm::reco::MonitorElement* muonEnergy_PFJ_hist;
  dqm::reco::MonitorElement* HFHadronEnergy_PFJ_hist;
  dqm::reco::MonitorElement* HFEMEnergy_PFJ_hist;
  dqm::reco::MonitorElement* chargedHadronMultiplicity_PFJ_hist;
  dqm::reco::MonitorElement* neutralHadronMultiplicity_PFJ_hist;
  dqm::reco::MonitorElement* photonMultiplicity_PFJ_hist;
  dqm::reco::MonitorElement* electronMultiplicity_PFJ_hist;
  dqm::reco::MonitorElement* muonMultiplicity_PFJ_hist;
  dqm::reco::MonitorElement* HFHadronMultiplicity_PFJ_hist;
  dqm::reco::MonitorElement* HFEMMultiplicity_PFJ_hist;
  dqm::reco::MonitorElement* HOEnergy_PFJ_hist;
  dqm::reco::MonitorElement* csv_PFJ_hist;
  dqm::reco::MonitorElement* mvaDiscriminator_PFJ_hist;

  dqm::reco::MonitorElement* PF_pT_211_hist;
  dqm::reco::MonitorElement* PF_pT_n211_hist;
  dqm::reco::MonitorElement* PF_pT_130_hist;
  dqm::reco::MonitorElement* PF_pT_22_hist;
  dqm::reco::MonitorElement* PF_pT_1_hist;
  dqm::reco::MonitorElement* PF_pT_2_hist;
 



  //  muons
  float trackIso1_mu;
  float trackIso2_mu;
  int nValidPixelHits1_mu;
  int nValidPixelHits2_mu;
  int nTrackerLayersWithMeasurement1_mu;
  int nTrackerLayersWithMeasurement2_mu;
  float trk_chi21_mu;
  float trk_chi22_mu;

  bool muonID1;
  bool muonID2;
  float mass_mu;
  float pt_dimu;
  float dr_mu;
  float pt1_mu;
  float pt2_mu;
  float eta1_mu;
  float eta2_mu;
  float phi1_mu;
  float phi2_mu;

  float rho;
 // int nMuonsID;

  bool hasPvtx;

  int ndvtx;
  bool isValidVtx;
  float vtxChi2;
  int vtxNdof;
  bool vtxMatch;

  float vtxXError;
  float vtxYError;
  float vtxZError;

  float Lxy;
  float LxyErr;
  float LxySig;


// electrons

  float pt_diele;
  float pt1_ele;
  float pt2_ele;

  float eta1_ele;
  float eta2_ele;
  float phi1_ele;
  float phi2_ele;
  float mass_ele; 
  float dr_ele;

  float rawEnergy_ele;
  float preshowerEnergy_ele;
  float corrEcalEnergyError_ele;
  float dEtaIn_ele;
  float dPhiIn_ele;
  float sigmaIetaIeta_ele;
  float hOverE_ele;
  float ooEMOop_ele;
  int missingHits_ele;
  float ecalIso_ele;
  float hcalIso_ele;
  float trackIso_ele;
  float r9_ele;
  float sMin_ele;
  float sMaj_ele; 
  
// photons

  float pt1_pho;
  float pt2_pho;
  float eta1_pho;
  float eta2_pho;
  float phi1_pho;
  float phi2_pho; 
 
  float rawEnergy_pho;
  float preshowerEnergy_pho;
  float corrEcalEnergyError_pho;
  float sigmaIetaIeta_pho;
  float hOverE_pho;
  float ecalIso_pho;
  float hcalIso_pho;
  float trackIso_pho;
  float r9_pho;
  float sMin_pho;
  float sMaj_pho;

// PFjets

  float pt1_PFJ;
  float pt2_PFJ;
  float eta1_PFJ;
  float eta2_PFJ;
  float phi1_PFJ;
  float phi2_PFJ;
  float m_PFJ;
  float jetArea_PFJ;
  float chargedHadronEnergy_PFJ;
  float neutralHadronEnergy_PFJ;
  float photonEnergy_PFJ;
  float electronEnergy_PFJ;
  float muonEnergy_PFJ;
  float HFHadronEnergy_PFJ;
  float HFEMEnergy_PFJ;
  int chargedHadronMultiplicity_PFJ;
  int neutralHadronMultiplicity_PFJ;
  int photonMultiplicity_PFJ;
  int electronMultiplicity_PFJ;
  int muonMultiplicity_PFJ;
  int HFHadronMultiplicity_PFJ;
  int HFEMMultiplicity_PFJ;
  float HOEnergy_PFJ;
  float csv_PFJ;
  float mvaDiscriminator_PFJ;


// PF candidates

  int pdgId;
  std::vector<float> pT_211;
  std::vector<float> pT_n211;
  std::vector<float> pT_130;
  std::vector<float> pT_22;
  std::vector<float> pT_1;
  std::vector<float> pT_2;
 
  /*

// Calojets (this is actually not used anymore lol)

  float pt1_CLJ;
  float pt2_CLJ;
  float eta1_CLJ;
  float eta2_CLJ;
  float phi1_CLJ;
  float phi2_CLJ;
  float m_CLJ;
  float jetArea_CLJ;
  float maxEInEmTowers_CLJ;
  float maxEInHadTowers_CLJ;
  float hadEnergyInHB_CLJ;
  float hadEnergyInHE_CLJ;
  float hadEnergyInHF_CLJ;
  float emEnergyInEB_CLJ;
  float emEnergyInEE_CLJ;
  float emEnergyInHF_CLJ;
  float towersArea_CLJ;
  float mvaDiscriminator_CLJ;
  float btagDiscriminator_CLJ;
 */


};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
ScoutingDQMMakerRun3::ScoutingDQMMakerRun3(const edm::ParameterSet& iConfig):
    triggerResultsTag        (iConfig.getParameter<edm::InputTag>("triggerresults")),
    triggerResultsToken      (consumes<edm::TriggerResults>                    (triggerResultsTag)),
    muonsToken               (consumes<std::vector<Run3ScoutingMuon> >             (iConfig.getParameter<edm::InputTag>("muons"))),
    electronsToken           (consumes<std::vector<Run3ScoutingElectron> >         (iConfig.getParameter<edm::InputTag>("electrons"))),
    primaryVerticesToken     (consumes<std::vector<Run3ScoutingVertex> >           (iConfig.getParameter<edm::InputTag>("primaryVertices"))),
    verticesToken            (consumes<std::vector<Run3ScoutingVertex> >           (iConfig.getParameter<edm::InputTag>("displacedVertices"))),
    rhoToken                 (consumes<double>                                 (iConfig.getParameter<edm::InputTag>("rho"))), 
    photonsToken             (consumes<std::vector<Run3ScoutingPhoton> >         (iConfig.getParameter<edm::InputTag>("photons"))),
    pfcandsToken             (consumes<std::vector<Run3ScoutingParticle> >         (iConfig.getParameter<edm::InputTag>("pfcands"))),
    pfjetsToken              (consumes<std::vector<Run3ScoutingPFJet> >            (iConfig.getParameter<edm::InputTag>("pfjets"))),
    tracksToken              (consumes<std::vector<Run3ScoutingTrack> >            (iConfig.getParameter<edm::InputTag>("tracks"))),
    doL1                     (iConfig.existsAs<bool>("doL1")               ?    iConfig.getParameter<bool>  ("doL1")            : false)
{
    if (doL1) {
        algInputTag_ = iConfig.getParameter<edm::InputTag>("AlgInputTag");
        extInputTag_ = iConfig.getParameter<edm::InputTag>("l1tExtBlkInputTag");
        algToken_ = consumes<BXVector<GlobalAlgBlk>>(algInputTag_);
        l1Seeds_ = iConfig.getParameter<std::vector<std::string> >("l1Seeds");
        l1GtUtils_ = std::make_unique<l1t::L1TGlobalUtil>(iConfig, consumesCollector(), *this, algInputTag_, extInputTag_, l1t::UseEventSetupIn::Event);
    }
    else {
        l1Seeds_ = std::vector<std::string>();
        l1GtUtils_ = 0;
    }
}

ScoutingDQMMakerRun3::~ScoutingDQMMakerRun3() {
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  //
  // please remove this method altogether if it would be left empty
}

//
// member functions
//

// ------------ method called for each event  ------------
void ScoutingDQMMakerRun3::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  using namespace edm;
  using namespace std;
  using namespace reco;


 Handle<vector<Run3ScoutingParticle> > pfcandsH;
   iEvent.getByToken(pfcandsToken, pfcandsH);
 
  
  Handle<vector<Run3ScoutingMuon> > muonsH;
  iEvent.getByToken(muonsToken, muonsH);


  Handle<vector<Run3ScoutingPFJet> > PFjetsH;
      iEvent.getByToken(pfjetsToken, PFjetsH);



     Handle<vector<Run3ScoutingPhoton> > photonsH;
      iEvent.getByToken(photonsToken, photonsH);


      Handle<vector<Run3ScoutingElectron> > electronsH;
      iEvent.getByToken(electronsToken, electronsH);


  Handle<vector<Run3ScoutingVertex> > verticesH;
      iEvent.getByToken(verticesToken, verticesH);


      Handle<vector<Run3ScoutingVertex> > primaryVerticesH;
      iEvent.getByToken(primaryVerticesToken, primaryVerticesH);

if (pfcandsH->size() >= 2 && PFjetsH->size() >= 2 && muonsH->size() >= 2 &&
    photonsH->size() >= 2 && electronsH->size() >= 2 && verticesH->size() >= 2) {
    
    std::cout << "\n whatever ok is " << pfcandsH->size() << " \n ";
    std::cout << "pfjets  " << PFjetsH->size() << "  \n ";
    std::cout << "muons  " << muonsH->size() << "  \n ";
    std::cout << "photons  " << photonsH->size() << "  \n ";
    std::cout << "electrons  " << electronsH->size() << "  \n ";
    std::cout << "vertices  " << verticesH->size() << "  \n ";
}







/*
  std::cout << "\n whatever ok is " << pfcandsH->size() << " \n "; 

std::cout << "pfjets  " << PFjetsH->size() << "  \n "; 
std::cout << "muons  " << muonsH->size() << "  \n "; 
std::cout << "photons  " << photonsH->size() << "  \n "; 
std::cout << "electrons  " << electronsH->size() << "  \n "; 
std::cout << "vertices  " << verticesH->size() << "  \n "; 
*/


if (muonsH->size()<2) return;

 // int nMuons=0;
 // nMuonsID=0;

  vector<int> idx;

  int j=0;
  for (auto muons_iter = muonsH->begin(); muons_iter != muonsH->end(); ++muons_iter) {
      //std::cout<<"pt_mu: "<<muons_iter->pt()<<std::endl;                                             
      //std::cout<<"trkiso: "<<muons_iter->trackIso()<<" pix hits: "<< muons_iter->nValidPixelHits()<<" layers: "<<muons_iter->nTrackerLayersWithMeasurement()<<" trk chi2: "<<muons_iter->trk_chi2()<<std::endl; 

      /*
      if (muons_iter->pt()>4) {
          nMuons+=1;
          if ((muons_iter->trackIso()<0.15) &&
              (muons_iter->nValidPixelHits()>0) &&
              (muons_iter->nTrackerLayersWithMeasurement()>5)&&
              (muons_iter->trk_chi2()<10)) {
              nMuonsID+=1;
          }
      }
      */

      idx.push_back(j);
      j+=1;
  }

 // std::cout<<std::endl<<idx.size()<<std::endl;

  if (idx.size()>1) {
      //std::cout << "charge: " << (muonsH->at(idx[0]).charge()) << ", " << (muonsH->at(idx[1]).charge()) << std::endl;
      if ((muonsH->at(idx[0]).charge())*(muonsH->at(idx[1]).charge()) > 0) {
        return;
      }

      //muonID1 = (muonsH->at(idx[0]).pt()>4) && (muonsH->at(idx[0]).trackIso()<0.15) && (muonsH->at(idx[0]).nValidPixelHits()>0) && (muonsH->at(idx[0]).trk_chi2()<10);
      //muonID2 = (muonsH->at(idx[1]).pt()>4) && (muonsH->at(idx[1]).trackIso()<0.15) && (muonsH->at(idx[1]).nValidPixelHits()>0) && (muonsH->at(idx[1]).trk_chi2()<10);

      //std::cout << "ID" << muonID1 << ", " << muonID2 << std::endl;

      trackIso1_mu = muonsH->at(idx[0]).trackIso();
      trackIso2_mu = muonsH->at(idx[1]).trackIso();   
      nValidPixelHits1_mu = muonsH->at(idx[0]).nValidPixelHits();
      nValidPixelHits2_mu = muonsH->at(idx[1]).nValidPixelHits();
      nTrackerLayersWithMeasurement1_mu = muonsH->at(idx[0]).nTrackerLayersWithMeasurement();
      nTrackerLayersWithMeasurement2_mu = muonsH->at(idx[1]).nTrackerLayersWithMeasurement();
      trk_chi21_mu = muonsH->at(idx[0]).trk_chi2();
      trk_chi22_mu = muonsH->at(idx[1]).trk_chi2();

      pt1_mu=muonsH->at(idx[0]).pt();
      pt2_mu=muonsH->at(idx[1]).pt();

      eta1_mu=muonsH->at(idx[0]).eta();
      eta2_mu=muonsH->at(idx[1]).eta();      
      phi1_mu=muonsH->at(idx[0]).phi();
      phi2_mu=muonsH->at(idx[1]).phi();
      
      TLorentzVector mu1;
      mu1.SetPtEtaPhiM(pt1_mu,eta1_mu,phi1_mu,0.105658);

      TLorentzVector mu2;
      mu2.SetPtEtaPhiM(pt2_mu,eta2_mu,phi2_mu,0.105658);

      TLorentzVector dimu = mu1+mu2;
      mass_mu=dimu.M();
      pt_dimu=dimu.Pt();
      dr_mu=mu1.DeltaR(mu2);

      //std::cout<<"pt: "<<pt1_mu<<", "<<pt2_mu<<", nMuonsID: "<<nMuonsID<<std::endl;

      Handle<double> rhoH;
      iEvent.getByToken(rhoToken, rhoH);
      rho=*rhoH;

      //Handle<vector<Run3ScoutingVertex> > primaryVerticesH;
      //iEvent.getByToken(primaryVerticesToken, primaryVerticesH);

      std::vector<float> vtxX;
      std::vector<float> vtxY;

      int npvtx = 0;
      for (auto vtx_iter = primaryVerticesH->begin(); vtx_iter != primaryVerticesH->end(); ++vtx_iter) {
        //std::cout<<"primary x: "<<vtx_iter->x() <<" y: "<<  vtx_iter->y()<<" ex: "<<vtx_iter->xError()<<" ey: "<<vtx_iter->yError()<<std::endl;
        npvtx++;
        vtxX.push_back(vtx_iter->x());   
        vtxY.push_back(vtx_iter->y());                
      }

      hasPvtx = npvtx > 0;

      float avgPrimary[2];
      avgPrimary[0] = ( vtxX.empty() ) ? 0 : ( std::reduce(vtxX.begin(), vtxX.end(), 0.0) / vtxX.size() );
      avgPrimary[1] = ( vtxY.empty() ) ? 0 : ( std::reduce(vtxY.begin(), vtxY.end(), 0.0) / vtxY.size() );

      //std::cout << "npvtx: " << npvtx << " avgPrimaryX: " << avgPrimary[0] << " avgPrimaryY: " << avgPrimary[1] << std::endl;

      //Handle<vector<Run3ScoutingVertex> > verticesH;
      //iEvent.getByToken(verticesToken, verticesH);

      std::vector<int> vtxIndx1 = (muonsH->at(idx[0])).vtxIndx();
      std::vector<int> vtxIndx2 = (muonsH->at(idx[1])).vtxIndx();

      //std::cout<<"vtxIndx1 size: "<<vtxIndx1.size()<<" vtxIndx2 size: "<<vtxIndx2.size()<<" num vtx: "<<verticesH->size()<<std::endl;
      
      ndvtx = verticesH->size();
      vtxMatch = vtxIndx1.size() > 0 && vtxIndx2.size() > 0 && vtxIndx1[0] == 0 && vtxIndx2[0] == 0 && ndvtx > 0;

      Lxy=0;
      LxyErr=0;
      LxySig=0;

      if (vtxMatch) {
        auto vtx = verticesH->begin();
        double dx = (vtx->x()) - avgPrimary[0];
        double dy = (vtx->y()) - avgPrimary[1];

        //std::cout<<"x: "<<vtx->x()<<" y: "<<vtx->y()<<std::endl;

        vtxChi2 = vtx->chi2();
        vtxNdof = vtx->ndof();
        isValidVtx = vtx->isValidVtx();

        vtxXError = vtx->xError();
        vtxYError = vtx->yError();
        vtxZError = vtx->zError();

        Lxy = sqrt(dx*dx + dy*dy);
        LxyErr = sqrt(dx*dx*(vtx->xError())*(vtx->xError()) + dy*dy*(vtx->yError())*(vtx->yError())) / Lxy;
        LxySig = Lxy/LxyErr;
      }

      //std::cout<<"Lxy: "<<Lxy<<" LxyErr: "<<LxyErr<<" LxySig: "<<LxySig<<std::endl;
      
      l1Result_.clear();
      if (doL1) {
          l1GtUtils_->retrieveL1(iEvent,iSetup,algToken_);
          /*for(unsigned int r = 0; r<100; r++){
            string name ("empty");
            bool algoName_ = false;
            algoName_ = l1GtUtils_->getAlgNameFromBit(i,name);
            cout << "getAlgNameFromBit = " << algoName_  << endl;
            cout << "L1 bit number = " << i << " ; L1 bit name = " << name << endl;
            }*/
          for( unsigned int iseed = 0; iseed < l1Seeds_.size(); iseed++ ) {
              bool l1htbit = 0;
              l1GtUtils_->getFinalDecisionByName(string(l1Seeds_[iseed]), l1htbit);
              l1Result_.push_back( l1htbit );
          }
      }


      //Handle<vector<Run3ScoutingElectron> > electronsH;
      //iEvent.getByToken(electronsToken, electronsH);

      if (electronsH->size()<2) return;

      std::cout << "\n two electrons present \n ";
      

      pt1_ele=electronsH->at(idx[0]).pt();
      pt2_ele=electronsH->at(idx[1]).pt();

      eta1_ele=electronsH->at(idx[0]).eta();
      eta2_ele=electronsH->at(idx[1]).eta();      
      phi1_ele=electronsH->at(idx[0]).phi();
      phi2_ele=electronsH->at(idx[1]).phi();
      

      TLorentzVector ele1;
      ele1.SetPtEtaPhiM(pt1_ele,eta1_ele,phi1_ele,0.0005109);

      TLorentzVector ele2;
      ele2.SetPtEtaPhiM(pt2_ele,eta2_ele,phi2_ele,0.0005109);

      TLorentzVector diele = ele1+ele2;
      mass_ele=diele.M();
      pt_diele=diele.Pt();
      dr_ele=ele1.DeltaR(ele2);

      rawEnergy_ele=electronsH->at(idx[0]).rawEnergy();
      preshowerEnergy_ele=electronsH->at(idx[0]).preshowerEnergy();
      corrEcalEnergyError_ele=electronsH->at(idx[0]).corrEcalEnergyError();
      dEtaIn_ele=electronsH->at(idx[0]).dEtaIn();
      dPhiIn_ele=electronsH->at(idx[0]).dPhiIn();
      sigmaIetaIeta_ele=electronsH->at(idx[0]).sigmaIetaIeta();
      hOverE_ele=electronsH->at(idx[0]).hOverE();
      ooEMOop_ele=electronsH->at(idx[0]).ooEMOop();
      missingHits_ele=electronsH->at(idx[0]).missingHits();
      ecalIso_ele=electronsH->at(idx[0]).ecalIso();
      hcalIso_ele=electronsH->at(idx[0]).hcalIso();
      trackIso_ele=electronsH->at(idx[0]).trackIso();
      r9_ele=electronsH->at(idx[0]).r9();
      sMin_ele=electronsH->at(idx[0]).sMin();
      sMaj_ele=electronsH->at(idx[0]).sMaj();
	

      //Handle<vector<Run3ScoutingPhoton> > photonsH;
      //iEvent.getByToken(photonsToken, photonsH);

      if (photonsH->size()<2) return;
      pt1_pho=photonsH->at(idx[0]).pt();
      pt2_pho=photonsH->at(idx[1]).pt();
      eta1_pho=photonsH->at(idx[0]).eta();
      eta2_pho=photonsH->at(idx[1]).eta();
      phi1_pho=photonsH->at(idx[0]).phi();
      phi2_pho=photonsH->at(idx[1]).phi();

      rawEnergy_pho=photonsH->at(idx[0]).rawEnergy();
      preshowerEnergy_pho=photonsH->at(idx[0]).preshowerEnergy();
      corrEcalEnergyError_pho=photonsH->at(idx[0]).corrEcalEnergyError();
      sigmaIetaIeta_pho=photonsH->at(idx[0]).sigmaIetaIeta();
      hOverE_pho=photonsH->at(idx[0]).hOverE();
      ecalIso_pho=photonsH->at(idx[0]).ecalIso();
      hcalIso_pho=photonsH->at(idx[0]).hcalIso();
      trackIso_pho=photonsH->at(idx[0]).trkIso();
      r9_pho=photonsH->at(idx[0]).r9();
      sMin_pho=photonsH->at(idx[0]).sMin();
      sMaj_pho=photonsH->at(idx[0]).sMaj();


      //Handle<vector<Run3ScoutingPFJet> > PFjetsH;
      //iEvent.getByToken(pfjetsToken, PFjetsH);

      if (PFjetsH->size() < 2) return;

      pt1_PFJ = PFjetsH->at(idx[0]).pt();
      pt2_PFJ = PFjetsH->at(idx[1]).pt();
      eta1_PFJ = PFjetsH->at(idx[0]).eta();
      eta2_PFJ = PFjetsH->at(idx[1]).eta();
      phi1_PFJ = PFjetsH->at(idx[0]).phi();
      phi2_PFJ = PFjetsH->at(idx[1]).phi();

      m_PFJ = PFjetsH->at(idx[0]).m();
      jetArea_PFJ = PFjetsH->at(idx[0]).jetArea();
      chargedHadronEnergy_PFJ = PFjetsH->at(idx[0]).chargedHadronEnergy();
      neutralHadronEnergy_PFJ = PFjetsH->at(idx[0]).neutralHadronEnergy();
      photonEnergy_PFJ = PFjetsH->at(idx[0]).photonEnergy();
      electronEnergy_PFJ = PFjetsH->at(idx[0]).electronEnergy();
      muonEnergy_PFJ = PFjetsH->at(idx[0]).muonEnergy();
      HFHadronEnergy_PFJ = PFjetsH->at(idx[0]).HFHadronEnergy();
      HFEMEnergy_PFJ = PFjetsH->at(idx[0]).HFEMEnergy();
      chargedHadronMultiplicity_PFJ = PFjetsH->at(idx[0]).chargedHadronMultiplicity();
      neutralHadronMultiplicity_PFJ = PFjetsH->at(idx[0]).neutralHadronMultiplicity();
      photonMultiplicity_PFJ = PFjetsH->at(idx[0]).photonMultiplicity();
      electronMultiplicity_PFJ = PFjetsH->at(idx[0]).electronMultiplicity();
      muonMultiplicity_PFJ = PFjetsH->at(idx[0]).muonMultiplicity();
      HFHadronMultiplicity_PFJ = PFjetsH->at(idx[0]).HFHadronMultiplicity();
      HFEMMultiplicity_PFJ = PFjetsH->at(idx[0]).HFEMMultiplicity();
      HOEnergy_PFJ = PFjetsH->at(idx[0]).HOEnergy();
      csv_PFJ = PFjetsH->at(idx[0]).csv();
      mvaDiscriminator_PFJ = PFjetsH->at(idx[0]).mvaDiscriminator();



	
      std::vector<int> pdgId_all;



      for (auto iter = pfcandsH->begin(); iter != pfcandsH->end(); ++iter){
	      pdgId_all.push_back(iter->pdgId());
	      //if (pdgId_all.back() == -211){pT_211.push_back(iter->pt());}
	      switch (iter->pdgId()){ 
		      case 211: pT_211.push_back(iter->pt()); break;
		      case -211: pT_n211.push_back(iter->pt()); break;
		      case 130: pT_130.push_back(iter->pt()); break;
		      case 22: pT_22.push_back(iter->pt()); break;
		      case 1: pT_1.push_back(iter->pt()); break;
		      case 2: pT_2.push_back(iter->pt()); break;				
     		 }
      }


      dimuon_hist->Fill(mass_mu);
      pt1_mu_hist->Fill(pt1_mu);
      eta1_mu_hist->Fill(eta1_mu);

      diele_hist->Fill(mass_ele);
      pt1_ele_hist->Fill(pt1_ele);
      eta1_ele_hist->Fill(eta1_ele);

      pt1_pho_hist->Fill(pt1_pho);
      eta1_pho_hist->Fill(eta1_pho);
     
      pt1_PFJ_hist->Fill(pt1_PFJ);
      eta1_PFJ_hist->Fill(eta1_PFJ); 




trackIso1_mu_hist->Fill(trackIso1_mu);
trackIso2_mu_hist->Fill(trackIso2_mu);
nValidPixelHits1_mu_hist->Fill(nValidPixelHits1_mu);
nValidPixelHits2_mu_hist->Fill(nValidPixelHits2_mu);
nTrackerLayersWithMeasurement1_mu_hist->Fill(nTrackerLayersWithMeasurement1_mu);
nTrackerLayersWithMeasurement2_mu_hist->Fill(nTrackerLayersWithMeasurement2_mu);
trk_chi21_mu_hist->Fill(trk_chi21_mu);
trk_chi22_mu_hist->Fill(trk_chi22_mu);

pt_dimu_hist->Fill(pt_dimu);
dr_mu_hist->Fill(dr_mu);
pt1_mu_hist->Fill(pt1_mu);
pt2_mu_hist->Fill(pt2_mu);
eta1_mu_hist->Fill(eta1_mu);
eta2_mu_hist->Fill(eta2_mu);
phi1_mu_hist->Fill(phi1_mu);
phi2_mu_hist->Fill(phi2_mu);
rho_hist->Fill(rho);

vtxMatch_hist->Fill(vtxMatch);
vtxChi2_hist->Fill(vtxChi2);
vtxNdof_hist->Fill(vtxNdof);
Lxy_hist->Fill(Lxy);
LxyErr_hist->Fill(LxyErr);
LxySig_hist->Fill(LxySig);

vtxXError_hist->Fill(vtxXError);
vtxYError_hist->Fill(vtxYError);
vtxZError_hist->Fill(vtxZError);

pt_diele_hist->Fill(pt_diele);
dr_ele_hist->Fill(dr_ele);
pt1_ele_hist->Fill(pt1_ele);
pt2_ele_hist->Fill(pt2_ele);
eta1_ele_hist->Fill(eta1_ele);
eta2_ele_hist->Fill(eta2_ele);
phi1_ele_hist->Fill(phi1_ele);
phi2_ele_hist->Fill(phi2_ele);
preshowerEnergy_ele_hist->Fill(preshowerEnergy_ele);
corrEcalEnergyError_ele_hist->Fill(corrEcalEnergyError_ele);
dEtaIn_ele_hist->Fill(dEtaIn_ele);
sigmaIetaIeta_ele_hist->Fill(sigmaIetaIeta_ele);
hOverE_ele_hist->Fill(hOverE_ele);
ooEMOop_ele_hist->Fill(ooEMOop_ele);
missingHits_ele_hist->Fill(missingHits_ele);
ecalIso_ele_hist->Fill(ecalIso_ele);
hcalIso_ele_hist->Fill(hcalIso_ele);
trackIso_ele_hist->Fill(trackIso_ele);
r9_ele_hist->Fill(r9_ele);
sMin_ele_hist->Fill(sMin_ele);
sMaj_ele_hist->Fill(sMaj_ele);
rawEnergy_ele_hist->Fill(rawEnergy_ele);

pt1_pho_hist->Fill(pt1_pho);
pt2_pho_hist->Fill(pt2_pho);
eta1_pho_hist->Fill(eta1_pho);
eta2_pho_hist->Fill(eta2_pho);
phi1_pho_hist->Fill(phi1_pho);
phi2_pho_hist->Fill(phi2_pho);
rawEnergy_pho_hist->Fill(rawEnergy_pho);
preshowerEnergy_pho_hist->Fill(preshowerEnergy_pho);
corrEcalEnergyError_pho_hist->Fill(corrEcalEnergyError_pho);
sigmaIetaIeta_pho_hist->Fill(sigmaIetaIeta_pho);
hOverE_pho_hist->Fill(hOverE_pho);
ecalIso_pho_hist->Fill(ecalIso_pho);
hcalIso_pho_hist->Fill(hcalIso_pho);
trackIso_pho_hist->Fill(trackIso_pho);
r9_pho_hist->Fill(r9_pho);
sMin_pho_hist->Fill(sMin_pho);
sMaj_pho_hist->Fill(sMaj_pho);

pt1_PFJ_hist->Fill(pt1_PFJ);
pt2_PFJ_hist->Fill(pt2_PFJ);
eta1_PFJ_hist->Fill(eta1_PFJ);
eta2_PFJ_hist->Fill(eta2_PFJ);
phi1_PFJ_hist->Fill(phi1_PFJ);
phi2_PFJ_hist->Fill(phi2_PFJ);
m_PFJ_hist->Fill(m_PFJ);
jetArea_PFJ_hist->Fill(jetArea_PFJ);
chargedHadronEnergy_PFJ_hist->Fill(chargedHadronEnergy_PFJ);
neutralHadronEnergy_PFJ_hist->Fill(neutralHadronEnergy_PFJ);
photonEnergy_PFJ_hist->Fill(photonEnergy_PFJ);
electronEnergy_PFJ_hist->Fill(electronEnergy_PFJ);
muonEnergy_PFJ_hist->Fill(muonEnergy_PFJ);
HFHadronEnergy_PFJ_hist->Fill(HFHadronEnergy_PFJ);
HFEMEnergy_PFJ_hist->Fill(HFEMEnergy_PFJ);
chargedHadronMultiplicity_PFJ_hist->Fill(chargedHadronMultiplicity_PFJ);
neutralHadronMultiplicity_PFJ_hist->Fill(neutralHadronMultiplicity_PFJ);
photonMultiplicity_PFJ_hist->Fill(photonMultiplicity_PFJ);
electronMultiplicity_PFJ_hist->Fill(electronMultiplicity_PFJ);
muonMultiplicity_PFJ_hist->Fill(muonMultiplicity_PFJ);
HFHadronMultiplicity_PFJ_hist->Fill(HFHadronMultiplicity_PFJ);
HFEMMultiplicity_PFJ_hist->Fill(HFEMMultiplicity_PFJ);
HOEnergy_PFJ_hist->Fill(HOEnergy_PFJ);
csv_PFJ_hist->Fill(csv_PFJ);
mvaDiscriminator_PFJ_hist->Fill(mvaDiscriminator_PFJ);


for (float pt : pT_211) {
    PF_pT_211_hist->Fill(pt);  
}
for (float pt : pT_n211) {
    PF_pT_n211_hist->Fill(pt);  
}
for (float pt : pT_130) {
    PF_pT_130_hist->Fill(pt);  
}

for (float pt : pT_22) {
    PF_pT_22_hist->Fill(pt);  
}
for (float pt : pT_1) {
    PF_pT_1_hist->Fill(pt);  
}
for (float pt : pT_2) {
    PF_pT_2_hist->Fill(pt);  
}




}

//  }
}

// ------------ method called once each job just before starting event loop  ------------
void ScoutingDQMMakerRun3::bookHistograms(DQMStore::IBooker & ibook, edm::Run const& run, edm::EventSetup const& iSetup) {
    
	
  ibook.setCurrentFolder(outputInternalPath_);

	
	// we say thank you chatGPT for doing what I am too lazy to do by hand
    trackIso1_mu_hist = ibook.book1D("trackIso1_mu", "Track Isolation 1; Isolation; Entries", 100, 0.0, 10.0);
    trackIso2_mu_hist = ibook.book1D("trackIso2_mu", "Track Isolation 2; Isolation; Entries", 100, 0.0, 20.0);
    nValidPixelHits1_mu_hist = ibook.book1D("nValidPixelHits1_mu", "Valid Pixel Hits 1; Hits; Entries", 20, 0, 20);
    nValidPixelHits2_mu_hist = ibook.book1D("nValidPixelHits2_mu", "Valid Pixel Hits 2; Hits; Entries", 20, 0, 20);
    nTrackerLayersWithMeasurement1_mu_hist = ibook.book1D("nTrackerLayersWithMeasurement1_mu", "Tracker Layers 1; Layers; Entries", 20, 0, 20);
    nTrackerLayersWithMeasurement2_mu_hist = ibook.book1D("nTrackerLayersWithMeasurement2_mu", "Tracker Layers 2; Layers; Entries", 20, 0, 20);
    trk_chi21_mu_hist = ibook.book1D("trk_chi21_mu", "Track Chi2 1; #chi^{2}; Entries", 100, 0.0, 100.0);
    trk_chi22_mu_hist = ibook.book1D("trk_chi22_mu", "Track Chi2 2; #chi^{2}; Entries", 100, 0.0, 200.0);
    rho_hist = ibook.book1D("rho", "Event Energy Density; #rho; Entries", 100, 0.0, 80.0);
    vtxMatch_hist = ibook.book1D("vtxMatch", "Vertex Match; Matched (0/1); Entries", 2, 0, 2);
    vtxChi2_hist = ibook.book1D("vtxChi2", "Vertex #chi^{2}; #chi^{2}; Entries", 100, 0.0, 15.0);
    vtxNdof_hist = ibook.book1D("vtxNdof", "Vertex Ndof; Ndof; Entries", 50, 0, 50);
    Lxy_hist = ibook.book1D("Lxy", "Decay Length Lxy; Lxy (cm); Entries", 100, 0.0, 1.0);
    LxyErr_hist = ibook.book1D("LxyErr", "Lxy Error; Lxy Error (cm); Entries", 100, 0.0, 1.0);
    LxySig_hist = ibook.book1D("LxySig", "Lxy Significance; Lxy / #sigma_{Lxy}; Entries", 100, 0.0, 10.0);
    vtxXError_hist = ibook.book1D("vtxXError", "Vertex X Error; X Error (cm); Entries", 100, 0.0, 0.01);
    vtxYError_hist = ibook.book1D("vtxYError", "Vertex Y Error; Y Error (cm); Entries", 100, 0.0, 0.01);
    vtxZError_hist = ibook.book1D("vtxZError", "Vertex Z Error; Z Error (cm); Entries", 100, 0.0, 0.05);


    dimuon_hist = ibook.book1D("dimuonMass", "Dimuon mass; Mass (GeV); Entries", 100, 0.0, 130.0); 
    pt_dimu_hist = ibook.book1D("pt_dimu", "Dimuon pT; pT (GeV); Entries", 100, 0.0, 130.0);
    pt1_mu_hist = ibook.book1D("muon_pT","muon p_{T}; p_{T} (GeV); Entries", 100, 0.0, 150.0);
    pt2_mu_hist = ibook.book1D("pt2_mu", "Muon 2 pT; pT (GeV); Entries", 100, 0.0, 100.0);
    eta1_mu_hist = ibook.book1D("muon_eta", "muon #eta; #eta (GeV); Entries", 100, -2.7, 2.7);
    eta2_mu_hist = ibook.book1D("eta2_mu", "Muon 2 #eta; #eta; Entries", 100, -3.0, 3.0);
    dr_mu_hist = ibook.book1D("dr_mu", "Delta R between muons; #DeltaR; Entries", 100, 0.0, 5.0);
    phi1_mu_hist = ibook.book1D("phi1_mu", "Muon 1 #phi; #phi (rad); Entries", 100, -3.14, 3.14);
    phi2_mu_hist = ibook.book1D("phi2_mu", "Muon 2 #phi; #phi (rad); Entries", 100, -3.14, 3.14);


    diele_hist = ibook.book1D("dieleMass", "Dielectron mass; Mass (GeV); Entries", 100, 0.0, 120.0);pt_diele_hist = ibook.book1D("pt_diele", "Dielectron pT; pT (GeV); Entries", 100, 0.0, 100.0);
    dr_ele_hist = ibook.book1D("dr_ele", "Delta R between electrons; #DeltaR; Entries", 100, 0.0, 5.0);
    pt1_ele_hist = ibook.book1D("electron_pT","electron p_{T}; p_{T} (GeV); Entries", 100, 0.0, 150.0); 
    pt2_ele_hist = ibook.book1D("pt2_ele", "Electron 2 pT; pT (GeV); Entries", 100, 0.0, 100.0);
    eta1_ele_hist = ibook.book1D("electron_eta", "electron #eta; #eta (GeV); Entries", 100, -2.7, 2.7);
    eta2_ele_hist = ibook.book1D("eta2_ele", "Electron 2 #eta; #eta; Entries", 100, -3.0, 3.0);
    phi1_ele_hist = ibook.book1D("phi1_ele", "Electron 1 #phi; #phi (rad); Entries", 100, -3.14, 3.14);
    phi2_ele_hist = ibook.book1D("phi2_ele", "Electron 2 #phi; #phi (rad); Entries", 100, -3.14, 3.14);
    preshowerEnergy_ele_hist = ibook.book1D("preshowerEnergy_ele", "Preshower Energy; Energy (GeV); Entries", 100, 0.0, 10.0);
    corrEcalEnergyError_ele_hist = ibook.book1D("corrEcalEnergyError_ele", "Corrected ECAL Energy Error; Energy Error (GeV); Entries", 100, 0.0, 10.0);
    dEtaIn_ele_hist = ibook.book1D("dEtaIn_ele", "dEtaIn; #Delta#eta_{in}; Entries", 100, -0.1, 0.1);
    sigmaIetaIeta_ele_hist = ibook.book1D("sigmaIetaIeta_ele", "Sigma iEta iEta; #sigma_{i#eta i#eta}; Entries", 100, 0.0, 0.05);
    hOverE_ele_hist = ibook.book1D("hOverE_ele", "H/E; H/E; Entries", 100, 0.0, 0.2);
    ooEMOop_ele_hist = ibook.book1D("ooEMOop_ele", "1/E - 1/p; 1/E - 1/p; Entries", 100, -0.5, 0.5);
    missingHits_ele_hist = ibook.book1D("missingHits_ele", "Missing Hits; Hits; Entries", 10, 0, 5.0);
    ecalIso_ele_hist = ibook.book1D("ecalIso_ele", "ECAL Isolation; Isolation (GeV); Entries", 100, 0.0, 45.0);
    hcalIso_ele_hist = ibook.book1D("hcalIso_ele", "HCAL Isolation; Isolation (GeV); Entries", 100, 0.0, 15.0);
    trackIso_ele_hist = ibook.book1D("trackIso_ele", "Track Isolation; Isolation (GeV); Entries", 100, 0.0, 12.0);
    r9_ele_hist = ibook.book1D("r9_ele", "R9; R9; Entries", 100, 0.0, 1.2);
    sMin_ele_hist = ibook.book1D("sMin_ele", "sMin; sMin; Entries", 100, 0.0, 0.5);
    sMaj_ele_hist = ibook.book1D("sMaj_ele", "sMaj; sMaj; Entries", 100, 0.0, 1.0);
    rawEnergy_ele_hist = ibook.book1D("rawEnergy_ele", "Raw Energy; Energy (GeV); Entries", 100, 0.0, 100.0);



    pt1_pho_hist = ibook.book1D("photon_pT","photon p_{T}; p_{T} (GeV); Entries", 100, 0.0, 170.0);
    pt2_pho_hist = ibook.book1D("pt2_pho", "Photon 2 pT; pT (GeV); Entries", 100, 0.0, 200.0);
    eta1_pho_hist = ibook.book1D("photon_eta", "photon #eta; #eta (GeV); Entries", 100, -2.7, 2.7);
    eta2_pho_hist = ibook.book1D("eta2_pho", "Photon 2 #eta; #eta; Entries", 100, -3.0, 3.0);
    phi1_pho_hist = ibook.book1D("phi1_pho", "Photon 1 #phi; #phi (rad); Entries", 100, -3.14, 3.14);
    phi2_pho_hist = ibook.book1D("phi2_pho", "Photon 2 #phi; #phi (rad); Entries", 100, -3.14, 3.14);
    rawEnergy_pho_hist = ibook.book1D("rawEnergy_pho", "Raw Energy; Energy (GeV); Entries", 100, 0.0, 500.0);
    preshowerEnergy_pho_hist = ibook.book1D("preshowerEnergy_pho", "Preshower Energy; Energy (GeV); Entries", 100, 0.0, 10.0);
    corrEcalEnergyError_pho_hist = ibook.book1D("corrEcalEnergyError_pho", "Corrected ECAL Energy Error; Energy Error (GeV); Entries", 100, 0.0, 5.0);
    sigmaIetaIeta_pho_hist = ibook.book1D("sigmaIetaIeta_pho", "Sigma iEta iEta; #sigma_{i#eta i#eta}; Entries", 100, 0.0, 0.05);
    hOverE_pho_hist = ibook.book1D("hOverE_pho", "H/E; H/E; Entries", 100, 0.0, 0.2);
    ecalIso_pho_hist = ibook.book1D("ecalIso_pho", "ECAL Isolation; Isolation (GeV); Entries", 100, 0.0, 10.0);
    hcalIso_pho_hist = ibook.book1D("hcalIso_pho", "HCAL Isolation; Isolation (GeV); Entries", 100, 0.0, 10.0);
    trackIso_pho_hist = ibook.book1D("trackIso_pho", "Track Isolation; Isolation (GeV); Entries", 100, 0.0, 10.0);
    r9_pho_hist = ibook.book1D("r9_pho", "R9; R9; Entries", 100, 0.0, 1.2);
    sMin_pho_hist = ibook.book1D("sMin_pho", "sMin; sMin; Entries", 100, 0.0, 0.1);
    sMaj_pho_hist = ibook.book1D("sMaj_pho", "sMaj; sMaj; Entries", 100, 0.0, 0.1);


    pt1_PFJ_hist = ibook.book1D("pt1_PFJ", "Leading PFJet pT; pT (GeV); Entries", 100, 0.0, 500.0);
    pt2_PFJ_hist = ibook.book1D("pt2_PFJ", "Subleading PFJet pT; pT (GeV); Entries", 100, 0.0, 500.0);
    eta1_PFJ_hist = ibook.book1D("eta1_PFJ", "Leading PFJet #eta; #eta; Entries", 100, -5.0, 5.0);
    eta2_PFJ_hist = ibook.book1D("eta2_PFJ", "Subleading PFJet #eta; #eta; Entries", 100, -5.0, 5.0);
    phi1_PFJ_hist = ibook.book1D("phi1_PFJ", "Leading PFJet #phi; #phi (rad); Entries", 100, -3.14, 3.14);
    phi2_PFJ_hist = ibook.book1D("phi2_PFJ", "Subleading PFJet #phi; #phi (rad); Entries", 100, -3.14, 3.14);
    m_PFJ_hist = ibook.book1D("m_PFJ", "PFJet Mass; Mass (GeV); Entries", 100, 0.0, 200.0);
    jetArea_PFJ_hist = ibook.book1D("jetArea_PFJ", "PFJet Area; Area; Entries", 100, 0.0, 2.0);
    chargedHadronEnergy_PFJ_hist = ibook.book1D("chargedHadronEnergy_PFJ", "Charged Hadron Energy; Energy (GeV); Entries", 100, 0.0, 500.0);
    neutralHadronEnergy_PFJ_hist = ibook.book1D("neutralHadronEnergy_PFJ", "Neutral Hadron Energy; Energy (GeV); Entries", 100, 0.0, 5000.0);
    photonEnergy_PFJ_hist = ibook.book1D("photonEnergy_PFJ", "Photon Energy; Energy (GeV); Entries", 100, 0.0, 200.0);
    electronEnergy_PFJ_hist = ibook.book1D("electronEnergy_PFJ", "Electron Energy; Energy (GeV); Entries", 100, 0.0, 100.0);
    muonEnergy_PFJ_hist = ibook.book1D("muonEnergy_PFJ", "Muon Energy; Energy (GeV); Entries", 100, 0.0, 200.0);
    HFHadronEnergy_PFJ_hist = ibook.book1D("HFHadronEnergy_PFJ", "HF Hadron Energy; Energy (GeV); Entries", 100, 0.0, 5000.0);
    HFEMEnergy_PFJ_hist = ibook.book1D("HFEMEnergy_PFJ", "HF EM Energy; Energy (GeV); Entries", 100, 0.0, 100.0);
    chargedHadronMultiplicity_PFJ_hist = ibook.book1D("chargedHadronMultiplicity_PFJ", "Charged Hadron Multiplicity; Multiplicity; Entries", 50, 0, 50);
    neutralHadronMultiplicity_PFJ_hist = ibook.book1D("neutralHadronMultiplicity_PFJ", "Neutral Hadron Multiplicity; Multiplicity; Entries", 50, 0, 50);
    photonMultiplicity_PFJ_hist = ibook.book1D("photonMultiplicity_PFJ", "Photon Multiplicity; Multiplicity; Entries", 50, 0, 50);
    electronMultiplicity_PFJ_hist = ibook.book1D("electronMultiplicity_PFJ", "Electron Multiplicity; Multiplicity; Entries", 20, 0, 20);
    muonMultiplicity_PFJ_hist = ibook.book1D("muonMultiplicity_PFJ", "Muon Multiplicity; Multiplicity; Entries", 20, 0, 20);
    HFHadronMultiplicity_PFJ_hist = ibook.book1D("HFHadronMultiplicity_PFJ", "HF Hadron Multiplicity; Multiplicity; Entries", 50, 0, 50);
    HFEMMultiplicity_PFJ_hist = ibook.book1D("HFEMMultiplicity_PFJ", "HF EM Multiplicity; Multiplicity; Entries", 50, 0, 50);
    HOEnergy_PFJ_hist = ibook.book1D("HOEnergy_PFJ", "HO Energy; Energy (GeV); Entries", 100, 0.0, 50.0);
    csv_PFJ_hist = ibook.book1D("csv_PFJ", "CSV Discriminator; CSV; Entries", 100, 0.0, 1.0);
    mvaDiscriminator_PFJ_hist = ibook.book1D("mvaDiscriminator_PFJ", "MVA Discriminator; MVA Score; Entries", 100, -1.0, 1.0);

    pt1_PFJ_hist = ibook.book1D("PFJ_pT","PF jet p_{T}; p_{T} (GeV); Entries", 100, 0.0, 170.0);
    eta1_PFJ_hist = ibook.book1D("PFJ_eta", "PF jet #eta; #eta (GeV); Entries", 100, -2.7, 2.7);

    PF_pT_211_hist = ibook.book1D("pT_211", "PF #pi^{+} p_{T} (GeV); Entries", 100,0.0,30.0);
    PF_pT_n211_hist = ibook.book1D("pT_n211", "PF #pi^{-} p_{T} (GeV); Entries", 100,0.0,65.0);
    PF_pT_130_hist = ibook.book1D("pT_130", "PF K_{L}^{0} p_{T} (GeV); Entries", 100,0.0,25.0);
    PF_pT_22_hist = ibook.book1D("pT_22", "PF #gamma p_{T} (GeV); Entries", 100,0.0,120.0);
    PF_pT_2_hist = ibook.book1D("pT_2", "PF d-quark p_{T} (GeV); Entries", 100,0.0,6.0);
    PF_pT_1_hist = ibook.book1D("pT_1", "PF u-quark p_{T} (GeV); Entries", 100,0.0,6.0);
}
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void ScoutingDQMMakerRun3::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addWithDefaultLabel(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ScoutingDQMMakerRun3);
