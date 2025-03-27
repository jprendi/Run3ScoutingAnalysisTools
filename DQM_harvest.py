import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
# Enable LogInfo
process.MessageLogger.cerr = cms.untracked.PSet(
    # threshold = cms.untracked.string('ERROR'),
    WARNING = cms.untracked.PSet(
        limit = cms.untracked.int32(0)
    ),
 )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("DQMRootSource",
                            fileNames = cms.untracked.vstring("file:DQM_test.root")) # Files from step 1



process.DQMStore = cms.Service("DQMStore")

process.load("DQMServices.Components.DQMEnvironment_cfi")
process.dqmSaver.workflow = '/Scouting/myTest/DQM'

process.load("DQMServices.Components.MEtoEDMConverter_cff")
process.load("DQMServices.Components.DQMStoreStats_cfi")

process.p1 = cms.Path(process.dqmSaver)
process.schedule = cms.Schedule(process.p1)


