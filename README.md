# Run3ScoutingAnalysisTools

## NGT HLT Scouting DQM Module -- work in progress
This repository is fully based and then expanded on the work [here](https://github.com/CMS-Run3ScoutingTools/Run3ScoutingAnalysisTools). Instead of trees, we produce DQM histograms with all the available scouting objects. The use case is for the NGT demonstrator, as a DQM instance to compare the regular HLT scouting path to our path (presentation on the demonstrator can be found [here](https://indico.cern.ch/event/1504131/contributions/6341017/attachments/3028520/5345755/NGT-HLT_OptimalCalibrations_AlCaDBWorkshop_10.03.2025_Zarucki.pdf)). 

### Getting started
```
cmsrel CMSSW_15_1_0_pre1
cd CMSSW_15_1_0_pre1/src
cmsenv
git cms-init
git clone git@github.com:jprendi/Run3ScoutingAnalysisTools.git 
scram b -j 96
```

### Getting the dataset from the scouting path the demonstrator will be using

```
hltGetConfiguration /dev/CMSSW_15_0_0/HLT \
   --globaltag 150X_dataRun3_HLT_v1 \
   --data \
   --unprescale \
   --output minimal \
   --max-events 100 \
   --eras Run3_2024 --l1-emulator uGT --l1 L1Menu_Collisions2025_v1_0_0_xml \
   --paths HLT_TestData_v*,DST_PFScouting_*,Dataset_TestDataRaw,LocalTestDataRawOutput,Dataset_TestDataScouting,LocalTestDataScoutingOutput \
   --input /store/data/Run2024I/EphemeralHLTPhysics0/RAW/v1/000/386/593/00000/91a08676-199e-404c-9957-f72772ef1354.root \
   > hltData.py

cmsRun hltData.py >& hltData.log
```

This gives as an output several .root files but the one we are interested in is `outputLocalTestDataScouting.root` .

### get the DQM plots!

```
cd Run3ScoutingAnalysisTools
cmsRun DQM.py
cmsRun DQM_harvest.py
```

This will yield in the final file called like `DQM_V0001_R000386593__Scouting__myTest__DQM.root`.

