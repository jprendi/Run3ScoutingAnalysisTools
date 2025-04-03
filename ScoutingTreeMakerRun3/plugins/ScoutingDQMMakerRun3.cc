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

  const std::string outputInternalPath_ = "HLT/ScoutingOffline/Misc";

  const edm::InputTag triggerResultsTag;
  const edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingMuon>> muonsToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingElectron>> electronsToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingVertex>> primaryVerticesToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingVertex>> verticesToken;
  const edm::EDGetTokenT<double> rhoToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingPhoton>> photonsToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingParticle>> pfcandsToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingPFJet>> pfjetsToken;
  const edm::EDGetTokenT<std::vector<Run3ScoutingTrack>> tracksToken;

  std::vector<std::string> triggerPathsVector;
  std::map<std::string, int> triggerPathsMap;

  bool doL1;
  triggerExpression::Data triggerCache_;

  edm::InputTag algInputTag_;
  edm::InputTag extInputTag_;
  edm::EDGetToken algToken_;
  std::unique_ptr<l1t::L1TGlobalUtil> l1GtUtils_;
  std::vector<std::string> l1Seeds_;
  std::vector<bool> l1Result_;

  // PF candidates histograms
  dqm::reco::MonitorElement* PF_pT_211_hist;
  dqm::reco::MonitorElement* PF_pT_n211_hist;
  dqm::reco::MonitorElement* PF_pT_130_hist;
  dqm::reco::MonitorElement* PF_pT_22_hist;
  dqm::reco::MonitorElement* PF_pT_13_hist;
  dqm::reco::MonitorElement* PF_pT_n13_hist;
  dqm::reco::MonitorElement* PF_pT_1_hist;
  dqm::reco::MonitorElement* PF_pT_2_hist;

  dqm::reco::MonitorElement* PF_eta_211_hist;
  dqm::reco::MonitorElement* PF_eta_n211_hist;
  dqm::reco::MonitorElement* PF_eta_130_hist;
  dqm::reco::MonitorElement* PF_eta_22_hist;
  dqm::reco::MonitorElement* PF_eta_13_hist;
  dqm::reco::MonitorElement* PF_eta_n13_hist;
  dqm::reco::MonitorElement* PF_eta_1_hist;
  dqm::reco::MonitorElement* PF_eta_2_hist;

  dqm::reco::MonitorElement* PF_phi_211_hist;
  dqm::reco::MonitorElement* PF_phi_n211_hist;
  dqm::reco::MonitorElement* PF_phi_130_hist;
  dqm::reco::MonitorElement* PF_phi_22_hist;
  dqm::reco::MonitorElement* PF_phi_13_hist;
  dqm::reco::MonitorElement* PF_phi_n13_hist;
  dqm::reco::MonitorElement* PF_phi_1_hist;
  dqm::reco::MonitorElement* PF_phi_2_hist;



  dqm::reco::MonitorElement* PF_vertex_211_hist;
  dqm::reco::MonitorElement* PF_vertex_n211_hist;
  dqm::reco::MonitorElement* PF_vertex_130_hist;
  dqm::reco::MonitorElement* PF_vertex_22_hist;
  dqm::reco::MonitorElement* PF_vertex_13_hist;
  dqm::reco::MonitorElement* PF_vertex_n13_hist;
  dqm::reco::MonitorElement* PF_vertex_1_hist;
  dqm::reco::MonitorElement* PF_vertex_2_hist;
  
  dqm::reco::MonitorElement* PF_normchi2_211_hist;
  dqm::reco::MonitorElement* PF_normchi2_n211_hist;
  dqm::reco::MonitorElement* PF_normchi2_130_hist;
  dqm::reco::MonitorElement* PF_normchi2_22_hist;
  dqm::reco::MonitorElement* PF_normchi2_13_hist;
  dqm::reco::MonitorElement* PF_normchi2_n13_hist;
  dqm::reco::MonitorElement* PF_normchi2_1_hist;
  dqm::reco::MonitorElement* PF_normchi2_2_hist;
  
  dqm::reco::MonitorElement* PF_dz_211_hist;
  dqm::reco::MonitorElement* PF_dz_n211_hist;
  dqm::reco::MonitorElement* PF_dz_130_hist;
  dqm::reco::MonitorElement* PF_dz_22_hist;
  dqm::reco::MonitorElement* PF_dz_13_hist;
  dqm::reco::MonitorElement* PF_dz_n13_hist;
  dqm::reco::MonitorElement* PF_dz_1_hist;
  dqm::reco::MonitorElement* PF_dz_2_hist;
  
  dqm::reco::MonitorElement* PF_dxy_211_hist;
  dqm::reco::MonitorElement* PF_dxy_n211_hist;
  dqm::reco::MonitorElement* PF_dxy_130_hist;
  dqm::reco::MonitorElement* PF_dxy_22_hist;
  dqm::reco::MonitorElement* PF_dxy_13_hist;
  dqm::reco::MonitorElement* PF_dxy_n13_hist;
  dqm::reco::MonitorElement* PF_dxy_1_hist;
  dqm::reco::MonitorElement* PF_dxy_2_hist;
  
  dqm::reco::MonitorElement* PF_dzsig_211_hist;
  dqm::reco::MonitorElement* PF_dzsig_n211_hist;
  dqm::reco::MonitorElement* PF_dzsig_130_hist;
  dqm::reco::MonitorElement* PF_dzsig_22_hist;
  dqm::reco::MonitorElement* PF_dzsig_13_hist;
  dqm::reco::MonitorElement* PF_dzsig_n13_hist;
  dqm::reco::MonitorElement* PF_dzsig_1_hist;
  dqm::reco::MonitorElement* PF_dzsig_2_hist;
  
  dqm::reco::MonitorElement* PF_dxysig_211_hist;
  dqm::reco::MonitorElement* PF_dxysig_n211_hist;
  dqm::reco::MonitorElement* PF_dxysig_130_hist;
  dqm::reco::MonitorElement* PF_dxysig_22_hist;
  dqm::reco::MonitorElement* PF_dxysig_13_hist;
  dqm::reco::MonitorElement* PF_dxysig_n13_hist;
  dqm::reco::MonitorElement* PF_dxysig_1_hist;
  dqm::reco::MonitorElement* PF_dxysig_2_hist;
  
  dqm::reco::MonitorElement* PF_trk_pt_211_hist;
  dqm::reco::MonitorElement* PF_trk_pt_n211_hist;
  dqm::reco::MonitorElement* PF_trk_pt_130_hist;
  dqm::reco::MonitorElement* PF_trk_pt_22_hist;
  dqm::reco::MonitorElement* PF_trk_pt_13_hist;
  dqm::reco::MonitorElement* PF_trk_pt_n13_hist;
  dqm::reco::MonitorElement* PF_trk_pt_1_hist;
  dqm::reco::MonitorElement* PF_trk_pt_2_hist;
  
  dqm::reco::MonitorElement* PF_trk_eta_211_hist;
  dqm::reco::MonitorElement* PF_trk_eta_n211_hist;
  dqm::reco::MonitorElement* PF_trk_eta_130_hist;
  dqm::reco::MonitorElement* PF_trk_eta_22_hist;
  dqm::reco::MonitorElement* PF_trk_eta_13_hist;
  dqm::reco::MonitorElement* PF_trk_eta_n13_hist;
  dqm::reco::MonitorElement* PF_trk_eta_1_hist;
  dqm::reco::MonitorElement* PF_trk_eta_2_hist;
  
  dqm::reco::MonitorElement* PF_trk_phi_211_hist;
  dqm::reco::MonitorElement* PF_trk_phi_n211_hist;
  dqm::reco::MonitorElement* PF_trk_phi_130_hist;
  dqm::reco::MonitorElement* PF_trk_phi_22_hist;
  dqm::reco::MonitorElement* PF_trk_phi_13_hist;
  dqm::reco::MonitorElement* PF_trk_phi_n13_hist;
  dqm::reco::MonitorElement* PF_trk_phi_1_hist;
  dqm::reco::MonitorElement* PF_trk_phi_2_hist;
  



  // photon histograms
  dqm::reco::MonitorElement* pt_pho_hist;
  dqm::reco::MonitorElement* eta_pho_hist;
  dqm::reco::MonitorElement* phi_pho_hist;
  dqm::reco::MonitorElement* m_pho_hist;
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

  // electron histograms
  dqm::reco::MonitorElement* pt_ele_hist;
  dqm::reco::MonitorElement* eta_ele_hist;
  dqm::reco::MonitorElement* phi_ele_hist;
  dqm::reco::MonitorElement* m_ele_hist;
  dqm::reco::MonitorElement* rawEnergy_ele_hist;
  dqm::reco::MonitorElement* preshowerEnergy_ele_hist;
  dqm::reco::MonitorElement* corrEcalEnergyError_ele_hist;
  dqm::reco::MonitorElement* dEtaIn_ele_hist;
  dqm::reco::MonitorElement* dPhiIn_ele_hist;
  dqm::reco::MonitorElement* sigmaIetaIeta_ele_hist;
  dqm::reco::MonitorElement* hOverE_ele_hist;
  dqm::reco::MonitorElement* ooEMOop_ele_hist;
  dqm::reco::MonitorElement* missingHits_ele_hist;
  dqm::reco::MonitorElement* trackfbrem_ele_hist;
  dqm::reco::MonitorElement* ecalIso_ele_hist;
  dqm::reco::MonitorElement* hcalIso_ele_hist;
  dqm::reco::MonitorElement* trackIso_ele_hist;
  dqm::reco::MonitorElement* r9_ele_hist;
  dqm::reco::MonitorElement* sMin_ele_hist;
  dqm::reco::MonitorElement* sMaj_ele_hist;

  // muon histograms

  dqm::reco::MonitorElement* pt_mu_hist;
  dqm::reco::MonitorElement* eta_mu_hist;
  dqm::reco::MonitorElement* phi_mu_hist;
  dqm::reco::MonitorElement* m_mu_hist;
  dqm::reco::MonitorElement* type_mu_hist;
  dqm::reco::MonitorElement* charge_mu_hist;
  dqm::reco::MonitorElement* normalizedChi2_mu_hist;
  dqm::reco::MonitorElement* ecalIso_mu_hist;
  dqm::reco::MonitorElement* hcalIso_mu_hist;
  dqm::reco::MonitorElement* trackIso_mu_hist;
  dqm::reco::MonitorElement* nValidStandAloneMuonHits_mu_hist;
  dqm::reco::MonitorElement* nStandAloneMuonMatchedStations_mu_hist;
  dqm::reco::MonitorElement* nValidRecoMuonHits_mu_hist;
  dqm::reco::MonitorElement* nRecoMuonChambers_mu_hist;
  dqm::reco::MonitorElement* nRecoMuonChambersCSCorDT_mu_hist;
  dqm::reco::MonitorElement* nRecoMuonMatches_mu_hist;
  dqm::reco::MonitorElement* nRecoMuonMatchedStations_mu_hist;
  dqm::reco::MonitorElement* nRecoMuonExpectedMatchedStations_mu_hist;
  dqm::reco::MonitorElement* recoMuonStationMask_mu_hist;
  dqm::reco::MonitorElement* nRecoMuonMatchedRPCLayers_mu_hist;
  dqm::reco::MonitorElement* recoMuonRPClayerMask_mu_hist;
  dqm::reco::MonitorElement* nValidPixelHits_mu_hist;
  dqm::reco::MonitorElement* nValidStripHits_mu_hist;
  dqm::reco::MonitorElement* nPixelLayersWithMeasurement_mu_hist;
  dqm::reco::MonitorElement* nTrackerLayersWithMeasurement_mu_hist;

  // PF Jet histograms

  dqm::reco::MonitorElement* pt_pfj_hist;
  dqm::reco::MonitorElement* eta_pfj_hist;
  dqm::reco::MonitorElement* phi_pfj_hist;
  dqm::reco::MonitorElement* m_pfj_hist;
  dqm::reco::MonitorElement* jetArea_pfj_hist;
  dqm::reco::MonitorElement* chargedHadronEnergy_pfj_hist;
  dqm::reco::MonitorElement* neutralHadronEnergy_pfj_hist;
  dqm::reco::MonitorElement* photonEnergy_pfj_hist;
  dqm::reco::MonitorElement* electronEnergy_pfj_hist;
  dqm::reco::MonitorElement* muonEnergy_pfj_hist;
  dqm::reco::MonitorElement* HFHadronEnergy_pfj_hist;
  dqm::reco::MonitorElement* HFEMEnergy_pfj_hist;
  dqm::reco::MonitorElement* chargedHadronMultiplicity_pfj_hist;
  dqm::reco::MonitorElement* neutralHadronMultiplicity_pfj_hist;
  dqm::reco::MonitorElement* photonMultiplicity_pfj_hist;
  dqm::reco::MonitorElement* electronMultiplicity_pfj_hist;
  dqm::reco::MonitorElement* muonMultiplicity_pfj_hist;
  dqm::reco::MonitorElement* HFHadronMultiplicity_pfj_hist;
  dqm::reco::MonitorElement* HFEMMultiplicity_pfj_hist;
  dqm::reco::MonitorElement* HOEnergy_pfj_hist;
  dqm::reco::MonitorElement* csv_pfj_hist;
  dqm::reco::MonitorElement* mvaDiscriminator_pfj_hist;


  dqm::reco::MonitorElement* x_vtx_hist;
dqm::reco::MonitorElement* y_vtx_hist;
dqm::reco::MonitorElement* z_vtx_hist;
dqm::reco::MonitorElement* zError_vtx_hist;
dqm::reco::MonitorElement* xError_vtx_hist;
dqm::reco::MonitorElement* yError_vtx_hist;
dqm::reco::MonitorElement* tracksSize_vtx_hist;
dqm::reco::MonitorElement* chi2_vtx_hist;
dqm::reco::MonitorElement* ndof_vtx_hist;
dqm::reco::MonitorElement* isValidVtx_vtx_hist;
dqm::reco::MonitorElement* xyCov_vtx_hist;
dqm::reco::MonitorElement* xzCov_vtx_hist;
dqm::reco::MonitorElement* yzCov_vtx_hist;


dqm::reco::MonitorElement* tk_pt_tk_hist;
dqm::reco::MonitorElement* tk_eta_tk_hist;
dqm::reco::MonitorElement* tk_phi_tk_hist;
dqm::reco::MonitorElement* tk_chi2_tk_hist;
dqm::reco::MonitorElement* tk_ndof_tk_hist;
dqm::reco::MonitorElement* tk_charge_tk_hist;
dqm::reco::MonitorElement* tk_dxy_tk_hist;
dqm::reco::MonitorElement* tk_dz_tk_hist;
dqm::reco::MonitorElement* tk_nValidPixelHits_tk_hist;
dqm::reco::MonitorElement* tk_nTrackerLayersWithMeasurement_tk_hist;
dqm::reco::MonitorElement* tk_nValidStripHits_tk_hist;
dqm::reco::MonitorElement* tk_qoverp_tk_hist;
dqm::reco::MonitorElement* tk_lambda_tk_hist;
dqm::reco::MonitorElement* tk_dxy_Error_tk_hist;
dqm::reco::MonitorElement* tk_dz_Error_tk_hist;
dqm::reco::MonitorElement* tk_qoverp_Error_tk_hist;
dqm::reco::MonitorElement* tk_lambda_Error_tk_hist;
dqm::reco::MonitorElement* tk_phi_Error_tk_hist;
dqm::reco::MonitorElement* tk_dsz_tk_hist;
dqm::reco::MonitorElement* tk_dsz_Error_tk_hist;
dqm::reco::MonitorElement* tk_qoverp_lambda_cov_tk_hist;
dqm::reco::MonitorElement* tk_qoverp_phi_cov_tk_hist;
dqm::reco::MonitorElement* tk_qoverp_dxy_cov_tk_hist;
dqm::reco::MonitorElement* tk_qoverp_dsz_cov_tk_hist;
dqm::reco::MonitorElement* tk_lambda_phi_cov_tk_hist;
dqm::reco::MonitorElement* tk_lambda_dxy_cov_tk_hist;
dqm::reco::MonitorElement* tk_lambda_dsz_cov_tk_hist;
dqm::reco::MonitorElement* tk_phi_dxy_cov_tk_hist;
dqm::reco::MonitorElement* tk_phi_dsz_cov_tk_hist;
dqm::reco::MonitorElement* tk_dxy_dsz_cov_tk_hist;
dqm::reco::MonitorElement* tk_vtxInd_tk_hist;
dqm::reco::MonitorElement* tk_vx_tk_hist;
dqm::reco::MonitorElement* tk_vy_tk_hist;
dqm::reco::MonitorElement* tk_vz_tk_hist;


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
ScoutingDQMMakerRun3::ScoutingDQMMakerRun3(const edm::ParameterSet& iConfig)
    : triggerResultsTag(iConfig.getParameter<edm::InputTag>("triggerresults")),
      triggerResultsToken(consumes<edm::TriggerResults>(triggerResultsTag)),
      muonsToken(consumes<std::vector<Run3ScoutingMuon>>(iConfig.getParameter<edm::InputTag>("muons"))),
      electronsToken(consumes<std::vector<Run3ScoutingElectron>>(iConfig.getParameter<edm::InputTag>("electrons"))),
      primaryVerticesToken(
          consumes<std::vector<Run3ScoutingVertex>>(iConfig.getParameter<edm::InputTag>("primaryVertices"))),
      verticesToken(
          consumes<std::vector<Run3ScoutingVertex>>(iConfig.getParameter<edm::InputTag>("displacedVertices"))),
      rhoToken(consumes<double>(iConfig.getParameter<edm::InputTag>("rho"))),
      photonsToken(consumes<std::vector<Run3ScoutingPhoton>>(iConfig.getParameter<edm::InputTag>("photons"))),
      pfcandsToken(consumes<std::vector<Run3ScoutingParticle>>(iConfig.getParameter<edm::InputTag>("pfcands"))),
      pfjetsToken(consumes<std::vector<Run3ScoutingPFJet>>(iConfig.getParameter<edm::InputTag>("pfjets"))),
      tracksToken(consumes<std::vector<Run3ScoutingTrack>>(iConfig.getParameter<edm::InputTag>("tracks"))),
      doL1(iConfig.existsAs<bool>("doL1") ? iConfig.getParameter<bool>("doL1") : false) {
  if (doL1) {
    algInputTag_ = iConfig.getParameter<edm::InputTag>("AlgInputTag");
    extInputTag_ = iConfig.getParameter<edm::InputTag>("l1tExtBlkInputTag");
    algToken_ = consumes<BXVector<GlobalAlgBlk>>(algInputTag_);
    l1Seeds_ = iConfig.getParameter<std::vector<std::string>>("l1Seeds");
    l1GtUtils_ = std::make_unique<l1t::L1TGlobalUtil>(
        iConfig, consumesCollector(), *this, algInputTag_, extInputTag_, l1t::UseEventSetupIn::Event);
  } else {
    l1Seeds_ = std::vector<std::string>();
    l1GtUtils_ = nullptr;
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

  // all the handles needed
  Handle<vector<Run3ScoutingParticle>> pfcandsH;
  iEvent.getByToken(pfcandsToken, pfcandsH);
  Handle<vector<Run3ScoutingPhoton>> photonsH;
  iEvent.getByToken(photonsToken, photonsH);
  Handle<vector<Run3ScoutingElectron>> electronsH;
  iEvent.getByToken(electronsToken, electronsH);
  Handle<vector<Run3ScoutingMuon>> muonsH;
  iEvent.getByToken(muonsToken, muonsH);
  Handle<vector<Run3ScoutingPFJet>> PFjetsH;
  iEvent.getByToken(pfjetsToken, PFjetsH);
  Handle<vector<Run3ScoutingVertex> > verticesH;
  iEvent.getByToken(verticesToken, verticesH);
  Handle<vector<Run3ScoutingTrack> > tracksH;
  iEvent.getByToken(tracksToken, tracksH);
  
  

  

  // fill the PF candidate histograms (no electrons!)

  /*for (auto iter = pfcandsH->begin(); iter != pfcandsH->end(); ++iter) {
    switch (iter->pdgId()) {
      case 211:
        PF_pT_211_hist->Fill(iter->pt());
        PF_eta_211_hist->Fill(iter->eta());
        PF_phi_211_hist->Fill(iter->phi());
        break;
      case -211:
        PF_pT_n211_hist->Fill(iter->pt());
        PF_eta_n211_hist->Fill(iter->eta());
        PF_phi_n211_hist->Fill(iter->phi());
        break;
      case 130:
        PF_pT_130_hist->Fill(iter->pt());
        PF_eta_130_hist->Fill(iter->eta());
        PF_phi_130_hist->Fill(iter->phi());
        break;
      case 22:
        PF_pT_22_hist->Fill(iter->pt());
        PF_eta_22_hist->Fill(iter->eta());
        PF_phi_22_hist->Fill(iter->phi());
        break;
      case 13:
        PF_pT_13_hist->Fill(iter->pt());
        PF_eta_13_hist->Fill(iter->eta());
        PF_phi_13_hist->Fill(iter->phi());
        break;
      case -13:
        PF_pT_n13_hist->Fill(iter->pt());
        PF_eta_n13_hist->Fill(iter->eta());
        PF_phi_n13_hist->Fill(iter->phi());
        break;
      case 1:
        PF_pT_1_hist->Fill(iter->pt());
        PF_eta_1_hist->Fill(iter->eta());
        PF_phi_1_hist->Fill(iter->phi());
        break;
      case 2:
        PF_pT_2_hist->Fill(iter->pt());
        PF_eta_2_hist->Fill(iter->eta());
        PF_phi_1_hist->Fill(iter->phi());
        break;
    }
  }*/

  for (auto iter = pfcandsH->begin(); iter != pfcandsH->end(); ++iter) {
    switch (iter->pdgId()) {
      case 211:
        PF_pT_211_hist->Fill(iter->pt());
        PF_eta_211_hist->Fill(iter->eta());
        PF_phi_211_hist->Fill(iter->phi());
        PF_vertex_211_hist->Fill(iter->vertex());
        PF_normchi2_211_hist->Fill(iter->normchi2());
        PF_dz_211_hist->Fill(iter->dz());
        PF_dxy_211_hist->Fill(iter->dxy());
        PF_dzsig_211_hist->Fill(iter->dzsig());
        PF_dxysig_211_hist->Fill(iter->dxysig());
        PF_trk_pt_211_hist->Fill(iter->trk_pt());
        PF_trk_eta_211_hist->Fill(iter->trk_eta());
        PF_trk_phi_211_hist->Fill(iter->trk_phi());
        break;
      case -211:
        PF_pT_n211_hist->Fill(iter->pt());
        PF_eta_n211_hist->Fill(iter->eta());
        PF_phi_n211_hist->Fill(iter->phi());
        PF_vertex_n211_hist->Fill(iter->vertex());
        PF_normchi2_n211_hist->Fill(iter->normchi2());
        PF_dz_n211_hist->Fill(iter->dz());
        PF_dxy_n211_hist->Fill(iter->dxy());
        PF_dzsig_n211_hist->Fill(iter->dzsig());
        PF_dxysig_n211_hist->Fill(iter->dxysig());
        PF_trk_pt_n211_hist->Fill(iter->trk_pt());
        PF_trk_eta_n211_hist->Fill(iter->trk_eta());
        PF_trk_phi_n211_hist->Fill(iter->trk_phi());
        break;
      case 130:
        PF_pT_130_hist->Fill(iter->pt());
        PF_eta_130_hist->Fill(iter->eta());
        PF_phi_130_hist->Fill(iter->phi());
        PF_vertex_130_hist->Fill(iter->vertex());
        PF_normchi2_130_hist->Fill(iter->normchi2());
        PF_dz_130_hist->Fill(iter->dz());
        PF_dxy_130_hist->Fill(iter->dxy());
        PF_dzsig_130_hist->Fill(iter->dzsig());
        PF_dxysig_130_hist->Fill(iter->dxysig());
        PF_trk_pt_130_hist->Fill(iter->trk_pt());
        PF_trk_eta_130_hist->Fill(iter->trk_eta());
        PF_trk_phi_130_hist->Fill(iter->trk_phi());
        break;
      case 22:
        PF_pT_22_hist->Fill(iter->pt());
        PF_eta_22_hist->Fill(iter->eta());
        PF_phi_22_hist->Fill(iter->phi());
        PF_vertex_22_hist->Fill(iter->vertex());
        PF_normchi2_22_hist->Fill(iter->normchi2());
        PF_dz_22_hist->Fill(iter->dz());
        PF_dxy_22_hist->Fill(iter->dxy());
        PF_dzsig_22_hist->Fill(iter->dzsig());
        PF_dxysig_22_hist->Fill(iter->dxysig());
        PF_trk_pt_22_hist->Fill(iter->trk_pt());
        PF_trk_eta_22_hist->Fill(iter->trk_eta());
        PF_trk_phi_22_hist->Fill(iter->trk_phi());
        break;
      case 13:
        PF_pT_13_hist->Fill(iter->pt());
        PF_eta_13_hist->Fill(iter->eta());
        PF_phi_13_hist->Fill(iter->phi());
        PF_vertex_13_hist->Fill(iter->vertex());
        PF_normchi2_13_hist->Fill(iter->normchi2());
        PF_dz_13_hist->Fill(iter->dz());
        PF_dxy_13_hist->Fill(iter->dxy());
        PF_dzsig_13_hist->Fill(iter->dzsig());
        PF_dxysig_13_hist->Fill(iter->dxysig());
        PF_trk_pt_13_hist->Fill(iter->trk_pt());
        PF_trk_eta_13_hist->Fill(iter->trk_eta());
        PF_trk_phi_13_hist->Fill(iter->trk_phi());
        break;
      case -13:
        PF_pT_n13_hist->Fill(iter->pt());
        PF_eta_n13_hist->Fill(iter->eta());
        PF_phi_n13_hist->Fill(iter->phi());
        PF_vertex_n13_hist->Fill(iter->vertex());
        PF_normchi2_n13_hist->Fill(iter->normchi2());
        PF_dz_n13_hist->Fill(iter->dz());
        PF_dxy_n13_hist->Fill(iter->dxy());
        PF_dzsig_n13_hist->Fill(iter->dzsig());
        PF_dxysig_n13_hist->Fill(iter->dxysig());
        PF_trk_pt_n13_hist->Fill(iter->trk_pt());
        PF_trk_eta_n13_hist->Fill(iter->trk_eta());
        PF_trk_phi_n13_hist->Fill(iter->trk_phi());
        break;
      case 1:
        PF_pT_1_hist->Fill(iter->pt());
        PF_eta_1_hist->Fill(iter->eta());
        PF_phi_1_hist->Fill(iter->phi());
        PF_vertex_1_hist->Fill(iter->vertex());
        PF_normchi2_1_hist->Fill(iter->normchi2());
        PF_dz_1_hist->Fill(iter->dz());
        PF_dxy_1_hist->Fill(iter->dxy());
        PF_dzsig_1_hist->Fill(iter->dzsig());
        PF_dxysig_1_hist->Fill(iter->dxysig());
        PF_trk_pt_1_hist->Fill(iter->trk_pt());
        PF_trk_eta_1_hist->Fill(iter->trk_eta());
        PF_trk_phi_1_hist->Fill(iter->trk_phi());
        break;
      case 2:
        PF_pT_2_hist->Fill(iter->pt());
        PF_eta_2_hist->Fill(iter->eta());
        PF_phi_2_hist->Fill(iter->phi());
        PF_vertex_2_hist->Fill(iter->vertex());
        PF_normchi2_2_hist->Fill(iter->normchi2());
        PF_dz_2_hist->Fill(iter->dz());
        PF_dxy_2_hist->Fill(iter->dxy());
        PF_dzsig_2_hist->Fill(iter->dzsig());
        PF_dxysig_2_hist->Fill(iter->dxysig());
        PF_trk_pt_2_hist->Fill(iter->trk_pt());
        PF_trk_eta_2_hist->Fill(iter->trk_eta());
        PF_trk_phi_2_hist->Fill(iter->trk_phi());
        break;
    }
  }


  // fill all the photon histograms

  for (auto iter = photonsH->begin(); iter != photonsH->end(); ++iter) {
    pt_pho_hist->Fill(iter->pt());
    eta_pho_hist->Fill(iter->eta());
    phi_pho_hist->Fill(iter->phi());
    m_pho_hist->Fill(iter->m());
    rawEnergy_pho_hist->Fill(iter->rawEnergy());
    preshowerEnergy_pho_hist->Fill(iter->preshowerEnergy());
    corrEcalEnergyError_pho_hist->Fill(iter->corrEcalEnergyError());
    sigmaIetaIeta_pho_hist->Fill(iter->sigmaIetaIeta());
    hOverE_pho_hist->Fill(iter->hOverE());
    ecalIso_pho_hist->Fill(iter->ecalIso());
    hcalIso_pho_hist->Fill(iter->hcalIso());
    trackIso_pho_hist->Fill(iter->trkIso());
    r9_pho_hist->Fill(iter->r9());
    sMin_pho_hist->Fill(iter->sMin());
    sMaj_pho_hist->Fill(iter->sMaj());
  }

  // fill all the electron histograms

  for (auto iter = electronsH->begin(); iter != electronsH->end(); ++iter) {
    pt_ele_hist->Fill(iter->pt());
    eta_ele_hist->Fill(iter->eta());
    phi_ele_hist->Fill(iter->phi());
    m_ele_hist->Fill(iter->m());
    rawEnergy_ele_hist->Fill(iter->rawEnergy());
    preshowerEnergy_ele_hist->Fill(iter->preshowerEnergy());
    corrEcalEnergyError_ele_hist->Fill(iter->corrEcalEnergyError());
    dEtaIn_ele_hist->Fill(iter->dEtaIn());
    dPhiIn_ele_hist->Fill(iter->dPhiIn());
    sigmaIetaIeta_ele_hist->Fill(iter->sigmaIetaIeta());
    hOverE_ele_hist->Fill(iter->hOverE());
    ooEMOop_ele_hist->Fill(iter->ooEMOop());
    missingHits_ele_hist->Fill(iter->missingHits());
    trackfbrem_ele_hist->Fill(iter->trackfbrem());
    ecalIso_ele_hist->Fill(iter->ecalIso());
    hcalIso_ele_hist->Fill(iter->hcalIso());
    trackIso_ele_hist->Fill(iter->trackIso());
    r9_ele_hist->Fill(iter->r9());
    sMin_ele_hist->Fill(iter->sMin());
    sMaj_ele_hist->Fill(iter->sMaj());
  }

    // fill all the muon histograms
    for (auto iter = muonsH->begin(); iter != muonsH->end(); ++iter) {
      pt_mu_hist->Fill(iter->pt());
      eta_mu_hist->Fill(iter->eta());
      phi_mu_hist->Fill(iter->phi());
      m_mu_hist->Fill(iter->m());
      type_mu_hist->Fill(iter->type());
      charge_mu_hist->Fill(iter->charge());
      normalizedChi2_mu_hist->Fill(iter->normalizedChi2());
      ecalIso_mu_hist->Fill(iter->ecalIso());
      hcalIso_mu_hist->Fill(iter->hcalIso());
      trackIso_mu_hist->Fill(iter->trackIso());
      nValidStandAloneMuonHits_mu_hist->Fill(iter->nValidStandAloneMuonHits());
      nStandAloneMuonMatchedStations_mu_hist->Fill(iter->nStandAloneMuonMatchedStations());
      nValidRecoMuonHits_mu_hist->Fill(iter->nValidRecoMuonHits());
      nRecoMuonChambers_mu_hist->Fill(iter->nRecoMuonChambers());
      nRecoMuonChambersCSCorDT_mu_hist->Fill(iter->nRecoMuonChambersCSCorDT());
      nRecoMuonMatches_mu_hist->Fill(iter->nRecoMuonMatches());
      nRecoMuonMatchedStations_mu_hist->Fill(iter->nRecoMuonMatchedStations());
      nRecoMuonExpectedMatchedStations_mu_hist->Fill(iter->nRecoMuonExpectedMatchedStations());
      recoMuonStationMask_mu_hist->Fill(iter->recoMuonStationMask());
      nRecoMuonMatchedRPCLayers_mu_hist->Fill(iter->nRecoMuonMatchedRPCLayers());
      recoMuonRPClayerMask_mu_hist->Fill(iter->recoMuonRPClayerMask());
      nValidPixelHits_mu_hist->Fill(iter->nValidPixelHits());
      nValidStripHits_mu_hist->Fill(iter->nValidStripHits());
      nPixelLayersWithMeasurement_mu_hist->Fill(iter->nPixelLayersWithMeasurement());
      nTrackerLayersWithMeasurement_mu_hist->Fill(iter->nTrackerLayersWithMeasurement());
    }

    // fill all the PF Jet histograms
    for (auto iter = PFjetsH->begin(); iter != PFjetsH->end(); ++iter) {
      pt_pfj_hist->Fill(iter->pt());
      eta_pfj_hist->Fill(iter->eta());
      phi_pfj_hist->Fill(iter->phi());
      m_pfj_hist->Fill(iter->m());
      jetArea_pfj_hist->Fill(iter->jetArea());
      chargedHadronEnergy_pfj_hist->Fill(iter->chargedHadronEnergy());
      neutralHadronEnergy_pfj_hist->Fill(iter->neutralHadronEnergy());
      photonEnergy_pfj_hist->Fill(iter->photonEnergy());
      electronEnergy_pfj_hist->Fill(iter->electronEnergy());
      muonEnergy_pfj_hist->Fill(iter->muonEnergy());
      HFHadronEnergy_pfj_hist->Fill(iter->HFHadronEnergy());
      HFEMEnergy_pfj_hist->Fill(iter->HFEMEnergy());
      chargedHadronMultiplicity_pfj_hist->Fill(iter->chargedHadronMultiplicity());
      neutralHadronMultiplicity_pfj_hist->Fill(iter->neutralHadronMultiplicity());
      photonMultiplicity_pfj_hist->Fill(iter->photonMultiplicity());
      electronMultiplicity_pfj_hist->Fill(iter->electronMultiplicity());
      muonMultiplicity_pfj_hist->Fill(iter->muonMultiplicity());
      HFHadronMultiplicity_pfj_hist->Fill(iter->HFHadronMultiplicity());
      HFEMMultiplicity_pfj_hist->Fill(iter->HFEMMultiplicity());
      HOEnergy_pfj_hist->Fill(iter->HOEnergy());
      csv_pfj_hist->Fill(iter->csv());
      mvaDiscriminator_pfj_hist->Fill(iter->mvaDiscriminator());
    }
  

    for (auto iter = verticesH->begin(); iter != verticesH->end(); ++iter) {
      x_vtx_hist->Fill(iter->x());
      y_vtx_hist->Fill(iter->y());
      z_vtx_hist->Fill(iter->z());
      zError_vtx_hist->Fill(iter->zError());
      xError_vtx_hist->Fill(iter->xError());
      yError_vtx_hist->Fill(iter->yError());
      tracksSize_vtx_hist->Fill(iter->tracksSize());
      chi2_vtx_hist->Fill(iter->chi2());
      ndof_vtx_hist->Fill(iter->ndof());
      isValidVtx_vtx_hist->Fill(iter->isValidVtx());
      xyCov_vtx_hist->Fill(iter->xyCov());
      xzCov_vtx_hist->Fill(iter->xzCov());
      yzCov_vtx_hist->Fill(iter->yzCov());
    }

    for (auto iter = tracksH->begin(); iter != tracksH->end(); ++iter) {
      tk_pt_tk_hist->Fill(iter->tk_pt());
      tk_eta_tk_hist->Fill(iter->tk_eta());
      tk_phi_tk_hist->Fill(iter->tk_phi());
      tk_chi2_tk_hist->Fill(iter->tk_chi2());
      tk_ndof_tk_hist->Fill(iter->tk_ndof());
      tk_charge_tk_hist->Fill(iter->tk_charge());
      tk_dxy_tk_hist->Fill(iter->tk_dxy());
      tk_dz_tk_hist->Fill(iter->tk_dz());
      tk_nValidPixelHits_tk_hist->Fill(iter->tk_nValidPixelHits());
      tk_nTrackerLayersWithMeasurement_tk_hist->Fill(iter->tk_nTrackerLayersWithMeasurement());
      tk_nValidStripHits_tk_hist->Fill(iter->tk_nValidStripHits());
      tk_qoverp_tk_hist->Fill(iter->tk_qoverp());
      tk_lambda_tk_hist->Fill(iter->tk_lambda());
      tk_dxy_Error_tk_hist->Fill(iter->tk_dxy_Error());
      tk_dz_Error_tk_hist->Fill(iter->tk_dz_Error());
      tk_qoverp_Error_tk_hist->Fill(iter->tk_qoverp_Error());
      tk_lambda_Error_tk_hist->Fill(iter->tk_lambda_Error());
      tk_phi_Error_tk_hist->Fill(iter->tk_phi_Error());
      tk_vtxInd_tk_hist->Fill(iter->tk_vtxInd());
      tk_vx_tk_hist->Fill(iter->tk_vx());
      tk_vy_tk_hist->Fill(iter->tk_vy());
      tk_vz_tk_hist->Fill(iter->tk_vz());
    }
    
    
}

// ------------ method called once each job just before starting event loop  ------------
void ScoutingDQMMakerRun3::bookHistograms(DQMStore::IBooker& ibook,
                                          edm::Run const& run,
                                          edm::EventSetup const& iSetup) {
  ibook.setCurrentFolder(outputInternalPath_);

  PF_pT_211_hist = ibook.book1DD("pT_211", "PF h^{+}  p_{T} (GeV); Entries", 100, 0.0, 13.0);
  PF_pT_n211_hist = ibook.book1DD("pT_n211", "PF h^{-} p_{T} (GeV); Entries", 100, 0.0, 14.0);
  PF_pT_130_hist = ibook.book1DD("pT_130", "PF h^{0} p_{T} (GeV); Entries", 100, 0.0, 20.0);
  PF_pT_22_hist = ibook.book1DD("pT_22", "PF #gamma p_{T} (GeV); Entries", 100, 0.0, 18.0);
  PF_pT_13_hist = ibook.book1DD("pT_13", "PF #mu^{+} p_{T} (GeV); Entries", 100, 0.0, 200.0);
  PF_pT_n13_hist = ibook.book1DD("pT_n13", "PF #mu^{-} p_{T} (GeV); Entries", 100, 0.0, 200.0);
  PF_pT_2_hist = ibook.book1DD("pT_2", "PF HF h (GeV); Entries", 100, 0.0, 4.5);
  PF_pT_1_hist = ibook.book1DD("pT_1", "PF HF e/#gamma p_{T} (GeV); Entries", 100, 0.0, 6.0);

  PF_eta_211_hist = ibook.book1DD("eta_211", "PF h^{+} #eta; Entries", 100, -5.0, 5.0);
  PF_eta_n211_hist = ibook.book1DD("eta_n211", "PF h^{-} #eta; Entries", 100, -5.0, 5.0);
  PF_eta_130_hist = ibook.book1DD("eta_130", "PF h^{0} #eta; Entries", 100, -5.0, 5.0);
  PF_eta_22_hist = ibook.book1DD("eta_22", "PF #gamma #eta; Entries", 100, -5.0, 5.0);
  PF_eta_13_hist = ibook.book1DD("eta_13", "PF #mu^{+} #eta; Entries", 100, -5.0, 5.0);
  PF_eta_n13_hist = ibook.book1DD("eta_n13", "PF #mu^{-} #eta; Entries", 100, -5.0, 5.0);
  PF_eta_1_hist = ibook.book1DD("eta_2", "PF HF h #eta; Entries", 100, -5.0, 5.0);
  PF_eta_2_hist = ibook.book1DD("eta_1", "PF HF e/#gamma #eta; Entries", 100, -5.0, 5.0);

  PF_phi_211_hist = ibook.book1DD("phi_211", "PF h^{+} #phi (rad); Entries", 100, -3.14, 3.14);
  PF_phi_n211_hist = ibook.book1DD("phi_n211", "PF h^{-} #phi (rad); Entries", 100, -3.14, 3.14);
  PF_phi_130_hist = ibook.book1DD("phi_130", "PF h^{0} #phi (rad); Entries", 100, -3.14, 3.14);
  PF_phi_22_hist = ibook.book1DD("phi_22", "PF #gamma #phi (rad); Entries", 100, -3.14, 3.14);
  PF_phi_13_hist = ibook.book1DD("phi_13", "PF #mu^{+} #phi (rad); Entries", 100, -3.14, 3.14);
  PF_phi_n13_hist = ibook.book1DD("phi_n13", "PF #mu^{-} #phi (rad); Entries", 100, -3.14, 3.14);
  PF_phi_1_hist = ibook.book1DD("phi_2", "PF HF h #phi (rad); Entries", 100, -3.14, 3.14);
  PF_phi_2_hist = ibook.book1DD("phi_1", "PF HF e/#gamma #phi (rad); Entries", 100, -3.14, 3.14);


  PF_vertex_211_hist = ibook.book1DD("vertex_211", "PF h^{+} Vertex; Entries", 100, -10.0, 10.0);
  PF_vertex_n211_hist = ibook.book1DD("vertex_n211", "PF h^{-} Vertex; Entries", 100, -10.0, 10.0);
  PF_vertex_130_hist = ibook.book1DD("vertex_130", "PF h^{0} Vertex; Entries", 100, -10.0, 10.0);
  PF_vertex_22_hist = ibook.book1DD("vertex_22", "PF #gamma Vertex; Entries", 100, -10.0, 10.0);
  PF_vertex_13_hist = ibook.book1DD("vertex_13", "PF #mu^{+} Vertex; Entries", 100, -10.0, 10.0);
  PF_vertex_n13_hist = ibook.book1DD("vertex_n13", "PF #mu^{-} Vertex; Entries", 100, -10.0, 10.0);
  PF_vertex_1_hist = ibook.book1DD("vertex_1", "PF HF h Vertex; Entries", 100, -10.0, 10.0);
  PF_vertex_2_hist = ibook.book1DD("vertex_2", "PF HF e/#gamma Vertex; Entries", 100, -10.0, 10.0);
  
  PF_normchi2_211_hist = ibook.book1DD("normchi2_211", "PF h^{+} Norm Chi^2; Entries", 100, 0.0, 10.0);
  PF_normchi2_n211_hist = ibook.book1DD("normchi2_n211", "PF h^{-} Norm Chi^2; Entries", 100, 0.0, 10.0);
  PF_normchi2_130_hist = ibook.book1DD("normchi2_130", "PF h^{0} Norm Chi^2; Entries", 100, 0.0, 10.0);
  PF_normchi2_22_hist = ibook.book1DD("normchi2_22", "PF #gamma Norm Chi^2; Entries", 100, 0.0, 10.0);
  PF_normchi2_13_hist = ibook.book1DD("normchi2_13", "PF #mu^{+} Norm Chi^2; Entries", 100, 0.0, 10.0);
  PF_normchi2_n13_hist = ibook.book1DD("normchi2_n13", "PF #mu^{-} Norm Chi^2; Entries", 100, 0.0, 10.0);
  PF_normchi2_1_hist = ibook.book1DD("normchi2_1", "PF HF h Norm Chi^2; Entries", 100, 0.0, 10.0);
  PF_normchi2_2_hist = ibook.book1DD("normchi2_2", "PF HF e/#gamma Norm Chi^2; Entries", 100, 0.0, 10.0);
  
  PF_dz_211_hist = ibook.book1DD("dz_211", "PF h^{+} dz (cm); Entries", 100, -1.0, 1.0);
  PF_dz_n211_hist = ibook.book1DD("dz_n211", "PF h^{-} dz (cm); Entries", 100, -1.0, 1.0);
  PF_dz_130_hist = ibook.book1DD("dz_130", "PF h^{0} dz (cm); Entries", 100, -1.0, 1.0);
  PF_dz_22_hist = ibook.book1DD("dz_22", "PF #gamma dz (cm); Entries", 100, -1.0, 1.0);
  PF_dz_13_hist = ibook.book1DD("dz_13", "PF #mu^{+} dz (cm); Entries", 100, -1.0, 1.0);
  PF_dz_n13_hist = ibook.book1DD("dz_n13", "PF #mu^{-} dz (cm); Entries", 100, -1.0, 1.0);
  PF_dz_1_hist = ibook.book1DD("dz_1", "PF HF h dz (cm); Entries", 100, -1.0, 1.0);
  PF_dz_2_hist = ibook.book1DD("dz_2", "PF HF e/#gamma dz (cm); Entries", 100, -1.0, 1.0);
  
  PF_dxy_211_hist = ibook.book1DD("dxy_211", "PF h^{+} dxy (cm); Entries", 100, -0.5, 0.5);
  PF_dxy_n211_hist = ibook.book1DD("dxy_n211", "PF h^{-} dxy (cm); Entries", 100, -0.5, 0.5);
  PF_dxy_130_hist = ibook.book1DD("dxy_130", "PF h^{0} dxy (cm); Entries", 100, -0.5, 0.5);
  PF_dxy_22_hist = ibook.book1DD("dxy_22", "PF #gamma dxy (cm); Entries", 100, -0.5, 0.5);
  PF_dxy_13_hist = ibook.book1DD("dxy_13", "PF #mu^{+} dxy (cm); Entries", 100, -0.5, 0.5);
  PF_dxy_n13_hist = ibook.book1DD("dxy_n13", "PF #mu^{-} dxy (cm); Entries", 100, -0.5, 0.5);
  PF_dxy_1_hist = ibook.book1DD("dxy_1", "PF HF h dxy (cm); Entries", 100, -0.5, 0.5);
  PF_dxy_2_hist = ibook.book1DD("dxy_2", "PF HF e/#gamma dxy (cm); Entries", 100, -0.5, 0.5);
  
  PF_dzsig_211_hist = ibook.book1DD("dzsig_211", "PF h^{+} dzsig; Entries", 100, 0.0, 10.0);
  PF_dzsig_n211_hist = ibook.book1DD("dzsig_n211", "PF h^{-} dzsig; Entries", 100, 0.0, 10.0);
  PF_dzsig_130_hist = ibook.book1DD("dzsig_130", "PF h^{0} dzsig; Entries", 100, 0.0, 10.0);
  PF_dzsig_22_hist = ibook.book1DD("dzsig_22", "PF #gamma dzsig; Entries", 100, 0.0, 10.0);
  PF_dzsig_13_hist = ibook.book1DD("dzsig_13", "PF #mu^{+} dzsig; Entries", 100, 0.0, 10.0);
  PF_dzsig_n13_hist = ibook.book1DD("dzsig_n13", "PF #mu^{-} dzsig; Entries", 100, 0.0, 10.0);
  PF_dzsig_1_hist = ibook.book1DD("dzsig_1", "PF HF h dzsig; Entries", 100, 0.0, 10.0);
  PF_dzsig_2_hist = ibook.book1DD("dzsig_2", "PF HF e/#gamma dzsig; Entries", 100, 0.0, 10.0);
  
  PF_dxysig_211_hist = ibook.book1DD("dxysig_211", "PF h^{+} dxysig; Entries", 100, 0.0, 10.0);
  PF_dxysig_n211_hist = ibook.book1DD("dxysig_n211", "PF h^{-} dxysig; Entries", 100, 0.0, 10.0);
  PF_dxysig_130_hist = ibook.book1DD("dxysig_130", "PF h^{0} dxysig; Entries", 100, 0.0, 10.0);
  PF_dxysig_22_hist = ibook.book1DD("dxysig_22", "PF #gamma dxysig; Entries", 100, 0.0, 10.0);
  PF_dxysig_13_hist = ibook.book1DD("dxysig_13", "PF #mu^{+} dxysig; Entries", 100, 0.0, 10.0);
  PF_dxysig_n13_hist = ibook.book1DD("dxysig_n13", "PF #mu^{-} dxysig; Entries", 100, 0.0, 10.0);
  PF_dxysig_1_hist = ibook.book1DD("dxysig_1", "PF HF h dxysig; Entries", 100, 0.0, 10.0);
  PF_dxysig_2_hist = ibook.book1DD("dxysig_2", "PF HF e/#gamma dxysig; Entries", 100, 0.0, 10.0);
  
  PF_trk_pt_211_hist = ibook.book1DD("trk_pt_211", "PF h^{+} Track p_{T} (GeV); Entries", 100, 0.0, 10.0);
  PF_trk_pt_n211_hist = ibook.book1DD("trk_pt_n211", "PF h^{-} Track p_{T} (GeV); Entries", 100, 0.0, 10.0);
  PF_trk_pt_130_hist = ibook.book1DD("trk_pt_130", "PF h^{0} Track p_{T} (GeV); Entries", 100, 0.0, 10.0);
  PF_trk_pt_22_hist = ibook.book1DD("trk_pt_22", "PF #gamma Track p_{T} (GeV); Entries", 100, 0.0, 10.0);
  PF_trk_pt_13_hist = ibook.book1DD("trk_pt_13", "PF #mu^{+} Track p_{T} (GeV); Entries", 100, 0.0, 10.0);
  PF_trk_pt_n13_hist = ibook.book1DD("trk_pt_n13", "PF #mu^{-} Track p_{T} (GeV); Entries", 100, 0.0, 10.0);
  PF_trk_pt_1_hist = ibook.book1DD("trk_pt_1", "PF HF h Track p_{T} (GeV); Entries", 100, 0.0, 10.0);
  PF_trk_pt_2_hist = ibook.book1DD("trk_pt_2", "PF HF e/#gamma Track p_{T} (GeV); Entries", 100, 0.0, 10.0);

  
  PF_trk_eta_211_hist = ibook.book1DD("trk_eta_211", "PF h^{+} Track #eta; Entries", 100, -3.0, 3.0);
PF_trk_eta_n211_hist = ibook.book1DD("trk_eta_n211", "PF h^{-} Track #eta; Entries", 100, -3.0, 3.0);
PF_trk_eta_130_hist = ibook.book1DD("trk_eta_130", "PF h^{0} Track #eta; Entries", 100, -3.0, 3.0);
PF_trk_eta_22_hist = ibook.book1DD("trk_eta_22", "PF #gamma Track #eta; Entries", 100, -3.0, 3.0);
PF_trk_eta_13_hist = ibook.book1DD("trk_eta_13", "PF #mu^{+} Track #eta; Entries", 100, -3.0, 3.0);
PF_trk_eta_n13_hist = ibook.book1DD("trk_eta_n13", "PF #mu^{-} Track #eta; Entries", 100, -3.0, 3.0);
PF_trk_eta_1_hist = ibook.book1DD("trk_eta_1", "PF HF h Track #eta; Entries", 100, -3.0, 3.0);
PF_trk_eta_2_hist = ibook.book1DD("trk_eta_2", "PF HF e/#gamma Track #eta; Entries", 100, -3.0, 3.0);

PF_trk_phi_211_hist = ibook.book1DD("trk_phi_211", "PF h^{+} Track #phi; Entries", 100, -3.2, 3.2);
PF_trk_phi_n211_hist = ibook.book1DD("trk_phi_n211", "PF h^{-} Track #phi; Entries", 100, -3.2, 3.2);
PF_trk_phi_130_hist = ibook.book1DD("trk_phi_130", "PF h^{0} Track #phi; Entries", 100, -3.2, 3.2);
PF_trk_phi_22_hist = ibook.book1DD("trk_phi_22", "PF #gamma Track #phi; Entries", 100, -3.2, 3.2);
PF_trk_phi_13_hist = ibook.book1DD("trk_phi_13", "PF #mu^{+} Track #phi; Entries", 100, -3.2, 3.2);
PF_trk_phi_n13_hist = ibook.book1DD("trk_phi_n13", "PF #mu^{-} Track #phi; Entries", 100, -3.2, 3.2);
PF_trk_phi_1_hist = ibook.book1DD("trk_phi_1", "PF HF h Track #phi; Entries", 100, -3.2, 3.2);
PF_trk_phi_2_hist = ibook.book1DD("trk_phi_2", "PF HF e/#gamma Track #phi; Entries", 100, -3.2, 3.2);





  pt_pho_hist = ibook.book1D("pt_pho", "Photon pT; pT (GeV); Entries", 100, 0.0, 200.0);
  eta_pho_hist = ibook.book1D("eta_pho", "photon #eta; #eta (GeV); Entries", 100, -2.7, 2.7);
  phi_pho_hist = ibook.book1D("phi_pho", "Photon #phi; #phi (rad); Entries", 100, -3.14, 3.14);
  m_pho_hist = ibook.book1D("m_pho", "Photon #m; m; Entries", 100, -0.01, 0.01);
  rawEnergy_pho_hist = ibook.book1D("rawEnergy_pho", "Raw Energy Photon; Energy (GeV); Entries", 100, 0.0, 250.0);
  preshowerEnergy_pho_hist =
      ibook.book1D("preshowerEnergy_pho", "Preshower Energy Photon; Energy (GeV); Entries", 100, 0.0, 10.0);
  corrEcalEnergyError_pho_hist = ibook.book1D(
      "corrEcalEnergyError_pho", "Corrected ECAL Energy Error Photon; Energy Error (GeV); Entries", 100, 0.0, 20.0);
  sigmaIetaIeta_pho_hist =
      ibook.book1D("sigmaIetaIeta_pho", "Sigma iEta iEta Photon; #sigma_{i#eta i#eta}; Entries", 100, 0.0, 0.5);
  hOverE_pho_hist = ibook.book1D("hOverE_pho", "H/E Photon; H/E; Entries", 100, 0.0, 1.5);
  ecalIso_pho_hist = ibook.book1D("ecalIso_pho", "ECAL Isolation Photon; Isolation (GeV); Entries", 100, 0.0, 100.0);
  hcalIso_pho_hist = ibook.book1D("hcalIso_pho", "HCAL Isolation Photon; Isolation (GeV); Entries", 100, 0.0, 100.0);
  trackIso_pho_hist = ibook.book1D("trackIso_pho", "Track Isolation Photon; Isolation (GeV); Entries", 100, 0.0, 0.5);
  r9_pho_hist = ibook.book1D("r9_pho", "R9; R9; Entries", 100, 0.0, 5);
  sMin_pho_hist = ibook.book1D("sMin_pho", "sMin Photon; sMin; Entries", 100, 0.0, 3);
  sMaj_pho_hist = ibook.book1D("sMaj_pho", "sMaj Photon ; sMaj; Entries", 100, 0.0, 3);

  pt_ele_hist = ibook.book1D("pt_ele", "Electron pT; pT (GeV); Entries", 100, 0.0, 200.0);
  eta_ele_hist = ibook.book1D("eta_ele", "Electron #eta; #eta; Entries", 100, -2.7, 2.7);
  phi_ele_hist = ibook.book1D("phi_ele", "Electron #phi; #phi (rad); Entries", 100, -3.14, 3.14);
  m_ele_hist = ibook.book1D("m_ele", "Electron #m; m; Entries", 100, -0.01, 0.01);
  rawEnergy_ele_hist = ibook.book1D("rawEnergy_ele", "Raw Energy Electron; Energy (GeV); Entries", 100, 0.0, 250.0);
  preshowerEnergy_ele_hist =
      ibook.book1D("preshowerEnergy_ele", "Preshower Energy Electron; Energy (GeV); Entries", 100, 0.0, 10.0);
  corrEcalEnergyError_ele_hist = ibook.book1D(
      "corrEcalEnergyError_ele", "Corrected ECAL Energy Error Electron; Energy Error (GeV); Entries", 100, 0.0, 20.0);
  dEtaIn_ele_hist = ibook.book1D("dEtaIn_ele", "dEtaIn Electron; dEtaIn; Entries", 100, -0.05, 0.05);
  dPhiIn_ele_hist = ibook.book1D("dPhiIn_ele", "dPhiIn Electron; dPhiIn; Entries", 100, -0.2, 0.2);
  sigmaIetaIeta_ele_hist =
      ibook.book1D("sigmaIetaIeta_ele", "Sigma iEta iEta Electron; #sigma_{i#eta i#eta}; Entries", 100, 0.0, 0.05);
  hOverE_ele_hist = ibook.book1D("hOverE_ele", "H/E Electron; H/E; Entries", 100, 0.0, 1.5);
  ooEMOop_ele_hist = ibook.book1D("ooEMOop_ele", "1/E - 1/p Electron; 1/E - 1/p; Entries", 100, -0.05, 0.05);
  missingHits_ele_hist = ibook.book1D("missingHits_ele", "Missing Hits Electron; Count; Entries", 10, 0, 10);
  trackfbrem_ele_hist = ibook.book1D("trackfbrem_ele", "Track fbrem Electron; fbrem; Entries", 100, -1.0, 1.0);
  ecalIso_ele_hist = ibook.book1D("ecalIso_ele", "ECAL Isolation Electron; Isolation (GeV); Entries", 100, 0.0, 100.0);
  hcalIso_ele_hist = ibook.book1D("hcalIso_ele", "HCAL Isolation Electron; Isolation (GeV); Entries", 100, 0.0, 100.0);
  trackIso_ele_hist = ibook.book1D("trackIso_ele", "Track Isolation Electron; Isolation (GeV); Entries", 100, 0.0, 0.5);
  r9_ele_hist = ibook.book1D("r9_ele", "R9 Electron; R9; Entries", 100, 0.0, 5);
  sMin_ele_hist = ibook.book1D("sMin_ele", "sMin Electron; sMin; Entries", 100, 0.0, 3);
  sMaj_ele_hist = ibook.book1D("sMaj_ele", "sMaj Electron; sMaj; Entries", 100, 0.0, 3);

  pt_mu_hist = ibook.book1D("pt_mu", "Muon pT; pT (GeV); Entries", 100, 0.0, 200.0);
  eta_mu_hist = ibook.book1D("eta_mu", "Muon #eta; #eta; Entries", 100, -2.7, 2.7);
  phi_mu_hist = ibook.book1D("phi_mu", "Muon #phi; #phi (rad); Entries", 100, -3.14, 3.14);
  m_mu_hist = ibook.book1D("m_mu", "Muon Mass; m (GeV); Entries", 100, 0.0, 0.2);
  type_mu_hist = ibook.book1D("type_mu", "Muon Type; Type; Entries", 10, 0, 10);
  charge_mu_hist = ibook.book1D("charge_mu", "Muon Charge; Charge; Entries", 3, -1, 2);
  normalizedChi2_mu_hist = ibook.book1D("normalizedChi2_mu", "Normalized Chi2; Chi2; Entries", 100, 0.0, 10.0);
  ecalIso_mu_hist = ibook.book1D("ecalIso_mu", "ECAL Isolation Muon; Isolation (GeV); Entries", 100, 0.0, 100.0);
  hcalIso_mu_hist = ibook.book1D("hcalIso_mu", "HCAL Isolation Muon; Isolation (GeV); Entries", 100, 0.0, 100.0);
  trackIso_mu_hist = ibook.book1D("trackIso_mu", "Track Isolation Muon; Isolation (GeV); Entries", 100, 0.0, 50.0);
  nValidStandAloneMuonHits_mu_hist =
      ibook.book1D("nValidStandAloneMuonHits_mu", "Valid Standalone Muon Hits; Hits; Entries", 50, 0, 50);
  nStandAloneMuonMatchedStations_mu_hist = ibook.book1D(
      "nStandAloneMuonMatchedStations_mu", "Standalone Muon Matched Stations; Stations; Entries", 10, 0, 10);
  nValidRecoMuonHits_mu_hist = ibook.book1D("nValidRecoMuonHits_mu", "Valid Reco Muon Hits; Hits; Entries", 50, 0, 50);
  nRecoMuonChambers_mu_hist = ibook.book1D("nRecoMuonChambers_mu", "Reco Muon Chambers; Chambers; Entries", 10, 0, 10);
  nRecoMuonChambersCSCorDT_mu_hist =
      ibook.book1D("nRecoMuonChambersCSCorDT_mu", "Reco Muon Chambers (CSC or DT); Chambers; Entries", 10, 0, 10);
  nRecoMuonMatches_mu_hist = ibook.book1D("nRecoMuonMatches_mu", "Reco Muon Matches; Matches; Entries", 10, 0, 10);
  nRecoMuonMatchedStations_mu_hist =
      ibook.book1D("nRecoMuonMatchedStations_mu", "Reco Muon Matched Stations; Stations; Entries", 10, 0, 10);
  nRecoMuonExpectedMatchedStations_mu_hist = ibook.book1D(
      "nRecoMuonExpectedMatchedStations_mu", "Reco Muon Expected Matched Stations; Stations; Entries", 10, 0, 10);
  recoMuonStationMask_mu_hist =
      ibook.book1D("recoMuonStationMask_mu", "Reco Muon Station Mask; Mask; Entries", 20, 0, 20);
  nRecoMuonMatchedRPCLayers_mu_hist =
      ibook.book1D("nRecoMuonMatchedRPCLayers_mu", "Reco Muon Matched RPC Layers; Layers; Entries", 10, 0, 10);
  recoMuonRPClayerMask_mu_hist =
      ibook.book1D("recoMuonRPClayerMask_mu", "Reco Muon RPC Layer Mask; Mask; Entries", 20, 0, 20);
  nValidPixelHits_mu_hist = ibook.book1D("nValidPixelHits_mu", "Valid Pixel Hits; Hits; Entries", 20, 0, 20);
  nValidStripHits_mu_hist = ibook.book1D("nValidStripHits_mu", "Valid Strip Hits; Hits; Entries", 50, 0, 50);
  nPixelLayersWithMeasurement_mu_hist =
      ibook.book1D("nPixelLayersWithMeasurement_mu", "Pixel Layers with Measurement; Layers; Entries", 10, 0, 10);
  nTrackerLayersWithMeasurement_mu_hist =
      ibook.book1D("nTrackerLayersWithMeasurement_mu", "Tracker Layers with Measurement; Layers; Entries", 20, 0, 20);

  pt_pfj_hist = ibook.book1D("pt_pfj", "PF Jet pT; pT (GeV); Entries", 100, 0.0, 500.0);
  eta_pfj_hist = ibook.book1D("eta_pfj", "PF Jet #eta; #eta; Entries", 100, -5.0, 5.0);
  phi_pfj_hist = ibook.book1D("phi_pfj", "PF Jet #phi; #phi (rad); Entries", 100, -3.14, 3.14);
  m_pfj_hist = ibook.book1D("m_pfj", "PF Jet Mass; Mass (GeV); Entries", 100, 0.0, 200.0);
  jetArea_pfj_hist = ibook.book1D("jetArea_pfj", "PF Jet Area; Area; Entries", 100, 0.0, 2.0);
  chargedHadronEnergy_pfj_hist =
      ibook.book1D("chargedHadronEnergy_pfj", "Charged Hadron Energy; Energy (GeV); Entries", 100, 0.0, 500.0);
  neutralHadronEnergy_pfj_hist =
      ibook.book1D("neutralHadronEnergy_pfj", "Neutral Hadron Energy; Energy (GeV); Entries", 100, 0.0, 500.0);
  photonEnergy_pfj_hist = ibook.book1D("photonEnergy_pfj", "Photon Energy; Energy (GeV); Entries", 100, 0.0, 300.0);
  electronEnergy_pfj_hist =
      ibook.book1D("electronEnergy_pfj", "Electron Energy; Energy (GeV); Entries", 100, 0.0, 100.0);
  muonEnergy_pfj_hist = ibook.book1D("muonEnergy_pfj", "Muon Energy; Energy (GeV); Entries", 100, 0.0, 100.0);
  HFHadronEnergy_pfj_hist =
      ibook.book1D("HFHadronEnergy_pfj", "HF Hadron Energy; Energy (GeV); Entries", 100, 0.0, 300.0);
  HFEMEnergy_pfj_hist = ibook.book1D("HFEMEnergy_pfj", "HF EM Energy; Energy (GeV); Entries", 100, 0.0, 300.0);
  chargedHadronMultiplicity_pfj_hist =
      ibook.book1D("chargedHadronMultiplicity_pfj", "Charged Hadron Multiplicity; Multiplicity; Entries", 50, 0, 50);
  neutralHadronMultiplicity_pfj_hist =
      ibook.book1D("neutralHadronMultiplicity_pfj", "Neutral Hadron Multiplicity; Multiplicity; Entries", 50, 0, 50);
  photonMultiplicity_pfj_hist =
      ibook.book1D("photonMultiplicity_pfj", "Photon Multiplicity; Multiplicity; Entries", 50, 0, 50);
  electronMultiplicity_pfj_hist =
      ibook.book1D("electronMultiplicity_pfj", "Electron Multiplicity; Multiplicity; Entries", 20, 0, 20);
  muonMultiplicity_pfj_hist =
      ibook.book1D("muonMultiplicity_pfj", "Muon Multiplicity; Multiplicity; Entries", 20, 0, 20);
  HFHadronMultiplicity_pfj_hist =
      ibook.book1D("HFHadronMultiplicity_pfj", "HF Hadron Multiplicity; Multiplicity; Entries", 20, 0, 20);
  HFEMMultiplicity_pfj_hist =
      ibook.book1D("HFEMMultiplicity_pfj", "HF EM Multiplicity; Multiplicity; Entries", 20, 0, 20);
  HOEnergy_pfj_hist = ibook.book1D("HOEnergy_pfj", "HO Energy; Energy (GeV); Entries", 100, 0.0, 50.0);
  csv_pfj_hist = ibook.book1D("csv_pfj", "Combined Secondary Vertex (CSV); CSV Score; Entries", 100, 0.0, 1.0);
  mvaDiscriminator_pfj_hist = ibook.book1D("mvaDiscriminator_pfj", "MVA Discriminator; Score; Entries", 100, -1.0, 1.0);

  x_vtx_hist = ibook.book1D("x_vtx", "Vertex X Position; x (cm); Entries", 100, -0.5, 0.5);
  y_vtx_hist = ibook.book1D("y_vtx", "Vertex Y Position; y (cm); Entries", 100, -0.5, 0.5);
  z_vtx_hist = ibook.book1D("z_vtx", "Vertex Z Position; z (cm); Entries", 100, -20.0, 20.0);
  zError_vtx_hist = ibook.book1D("zError_vtx", "Vertex Z Error; z Error (cm); Entries", 100, 0.0, 0.05);
  xError_vtx_hist = ibook.book1D("xError_vtx", "Vertex X Error; x Error (cm); Entries", 100, 0.0, 0.05);
  yError_vtx_hist = ibook.book1D("yError_vtx", "Vertex Y Error; y Error (cm); Entries", 100, 0.0, 0.05);
  tracksSize_vtx_hist = ibook.book1D("tracksSize_vtx", "Number of Tracks at Vertex; Tracks; Entries", 100, 0, 100);
  chi2_vtx_hist = ibook.book1D("chi2_vtx", "Vertex Chi2; #chi^{2}; Entries", 100, 0.0, 50.0);
  ndof_vtx_hist = ibook.book1D("ndof_vtx", "Vertex Ndof; Ndof; Entries", 100, 0, 100);
  isValidVtx_vtx_hist = ibook.book1D("isValidVtx_vtx", "Is Valid Vertex?; 0 = False, 1 = True; Entries", 2, 0, 2);
  xyCov_vtx_hist = ibook.book1D("xyCov_vtx", "Vertex XY Covariance; Cov(x,y); Entries", 100, -0.01, 0.01);
  xzCov_vtx_hist = ibook.book1D("xzCov_vtx", "Vertex XZ Covariance; Cov(x,z); Entries", 100, -0.01, 0.01);
  yzCov_vtx_hist = ibook.book1D("yzCov_vtx", "Vertex YZ Covariance; Cov(y,z); Entries", 100, -0.01, 0.01);
  
  tk_pt_tk_hist = ibook.book1D("tk_pt_tk", "Tracker pT; pT (GeV); Entries", 100, 0.0, 200.0);
tk_eta_tk_hist = ibook.book1D("tk_eta_tk", "Tracker #eta; #eta; Entries", 100, -2.7, 2.7);
tk_phi_tk_hist = ibook.book1D("tk_phi_tk", "Tracker #phi; #phi (rad); Entries", 100, -3.14, 3.14);
tk_chi2_tk_hist = ibook.book1D("tk_chi2_tk", "Tracker Chi2; #chi^{2}; Entries", 100, 0.0, 50.0);
tk_ndof_tk_hist = ibook.book1D("tk_ndof_tk", "Tracker Ndof; Ndof; Entries", 100, 0, 100);
tk_charge_tk_hist = ibook.book1D("tk_charge_tk", "Tracker Charge; Charge; Entries", 3, -1, 2);
tk_dxy_tk_hist = ibook.book1D("tk_dxy_tk", "Tracker dxy; dxy (cm); Entries", 100, -0.5, 0.5);
tk_dz_tk_hist = ibook.book1D("tk_dz_tk", "Tracker dz; dz (cm); Entries", 100, -20.0, 20.0);
tk_nValidPixelHits_tk_hist = ibook.book1D("tk_nValidPixelHits_tk", "Valid Pixel Hits; Hits; Entries", 20, 0, 20);
tk_nTrackerLayersWithMeasurement_tk_hist =
    ibook.book1D("tk_nTrackerLayersWithMeasurement_tk", "Tracker Layers with Measurement; Layers; Entries", 20, 0, 20);
tk_nValidStripHits_tk_hist = ibook.book1D("tk_nValidStripHits_tk", "Valid Strip Hits; Hits; Entries", 50, 0, 50);
tk_qoverp_tk_hist = ibook.book1D("tk_qoverp_tk", "q/p; q/p; Entries", 100, -0.1, 0.1);
tk_lambda_tk_hist = ibook.book1D("tk_lambda_tk", "Lambda; #lambda; Entries", 100, -2, 2);
tk_dxy_Error_tk_hist = ibook.book1D("tk_dxy_Error_tk", "dxy Error; dxy Error (cm); Entries", 100, 0.0, 0.05);
tk_dz_Error_tk_hist = ibook.book1D("tk_dz_Error_tk", "dz Error; dz Error (cm); Entries", 100, 0.0, 0.05);
tk_qoverp_Error_tk_hist = ibook.book1D("tk_qoverp_Error_tk", "q/p Error; q/p Error; Entries", 100, 0.0, 0.01);
tk_lambda_Error_tk_hist = ibook.book1D("tk_lambda_Error_tk", "Lambda Error; #lambda Error; Entries", 100, 0.0, 0.1);
tk_phi_Error_tk_hist = ibook.book1D("tk_phi_Error_tk", "Phi Error; #phi Error (rad); Entries", 100, 0.0, 0.01);
tk_dsz_tk_hist = ibook.book1D("tk_dsz_tk", "dsz; dsz (cm); Entries", 100, -2, 2);
tk_dsz_Error_tk_hist = ibook.book1D("tk_dsz_Error_tk", "dsz Error; dsz Error (cm); Entries", 100, 0.0, 0.05);
tk_vtxInd_tk_hist = ibook.book1D("tk_vtxInd_tk", "Vertex Index; Index; Entries", 50, 0, 50);
tk_vx_tk_hist = ibook.book1D("tk_vx_tk", "Tracker Vertex X; x (cm); Entries", 100, -0.5, 0.5);
tk_vy_tk_hist = ibook.book1D("tk_vy_tk", "Tracker Vertex Y; y (cm); Entries", 100, -0.5, 0.5);
tk_vz_tk_hist = ibook.book1D("tk_vz_tk", "Tracker Vertex Z; z (cm); Entries", 100, -20.0, 20.0);


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
