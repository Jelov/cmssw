###############################################################################################
#
# Basic PAT configuration
#
###############################################################################################
##
## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *
##
##
process.source.fileNames = ['file:/afs/cern.ch/sw/lcg/tmp/PAT_Tutorial_Summer14/exercise_08_04DF20AC-28B5-E311-814A-003048679296.root']
process.maxEvents.input = 1000
process.out.fileName = "myTuple.root"
process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string('histo.root'),
    closeFileFast = cms.untracked.bool(True)
)

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkSummary = cms.untracked.PSet(
    reportEvery = cms.untracked.int32(100),
    limit = cms.untracked.int32(10000000)
)
process.MessageLogger.cerr.FwkReport = cms.untracked.PSet(
    reportEvery = cms.untracked.int32(100),
    limit = cms.untracked.int32(10000000)
)
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool( False )
)

###############################################################################################
#
# Task1: MC Matching
#
###############################################################################################
##
## prepare several clones of match associations for status 1 and 3
process.load("PhysicsTools.PatAlgos.patSequences_cff")
process.muMatch1 = process.muonMatch.clone(mcStatus = [1]) # stable
process.muMatch3 = process.muonMatch.clone(mcStatus = [3]) # hard scattering

##
## add the new matches to the default sequence
process.patDefaultSequence.replace(
    process.muonMatch,
    process.muMatch1 +
    process.muMatch3
)
##
## add input(s) with MC match information
process.patMuons.genParticleMatch = cms.VInputTag(
    cms.InputTag("muMatch1"),
    cms.InputTag("muMatch3")
)

##
##
process.analyzePatMCMatching = cms.EDAnalyzer(
    "MyPatMatchingTask1",
    muonSrc  = cms.untracked.InputTag("selectedPatMuons")
)

## let it run
process.p = cms.Path(
    process.patDefaultSequence * 
process.analyzePatMCMatching
)

