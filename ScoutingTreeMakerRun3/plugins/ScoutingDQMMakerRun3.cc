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
 
   std::cout << "\n"; 
   for (auto iter = pfcandsH->begin(); iter != pfcandsH->end(); ++iter){
	   std::cout << " " << iter->pdgId() << " ";
     switch (iter->pdgId()){ 
       case 211: PF_pT_211_hist->Fill(iter->pt()); PF_eta_211_hist->Fill(iter->eta()); PF_phi_211_hist->Fill(iter->phi());    break;
       case -211: PF_pT_n211_hist->Fill(iter->pt()); PF_eta_n211_hist->Fill(iter->eta()); PF_phi_n211_hist->Fill(iter->phi());    break;
       case 130: PF_pT_130_hist->Fill(iter->pt()); PF_eta_130_hist->Fill(iter->eta()); PF_phi_130_hist->Fill(iter->phi());    break;
       case 22: PF_pT_22_hist->Fill(iter->pt()); PF_eta_22_hist->Fill(iter->eta()); PF_phi_22_hist->Fill(iter->phi());    break;
       case 13: PF_pT_13_hist->Fill(iter->pt()); PF_eta_13_hist->Fill(iter->eta()); PF_phi_13_hist->Fill(iter->phi());    break;
       case -13: PF_pT_n13_hist->Fill(iter->pt()); PF_eta_n13_hist->Fill(iter->eta()); PF_phi_n13_hist->Fill(iter->phi());    break;
       case 1: PF_pT_1_hist->Fill(iter->pt()); PF_eta_1_hist->Fill(iter->eta()); PF_phi_1_hist->Fill(iter->phi());    break;
       case 2: PF_pT_2_hist->Fill(iter->pt()); PF_eta_2_hist->Fill(iter->eta()); PF_phi_1_hist->Fill(iter->phi());    break; 
       }
   }
  

}

// ------------ method called once each job just before starting event loop  ------------
void ScoutingDQMMakerRun3::bookHistograms(DQMStore::IBooker & ibook, edm::Run const& run, edm::EventSetup const& iSetup) {
    
	
  ibook.setCurrentFolder(outputInternalPath_);

    PF_pT_211_hist = ibook.book1DD("pT_211", "PF h^{+}  p_{T} (GeV); Entries", 100,0.0,13.0);
    PF_pT_n211_hist = ibook.book1DD("pT_n211", "PF h^{-} p_{T} (GeV); Entries", 100,0.0,14.0);
    PF_pT_130_hist = ibook.book1DD("pT_130", "PF h^{0} p_{T} (GeV); Entries", 100,0.0,20.0);
    PF_pT_22_hist = ibook.book1DD("pT_22", "PF #gamma p_{T} (GeV); Entries", 100,0.0,18.0);
    PF_pT_13_hist = ibook.book1DD("pT_13", "PF #mu^{+} p_{T} (GeV); Entries", 100,0.0,200.0);
    PF_pT_n13_hist = ibook.book1DD("pT_n13", "PF #mu^{-} p_{T} (GeV); Entries", 100,0.0,200.0);
    PF_pT_2_hist = ibook.book1DD("pT_2", "PF HF h (GeV); Entries", 100,0.0,4.5);
    PF_pT_1_hist = ibook.book1DD("pT_1", "PF HF e/#gamma p_{T} (GeV); Entries", 100,0.0,6.0);


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
