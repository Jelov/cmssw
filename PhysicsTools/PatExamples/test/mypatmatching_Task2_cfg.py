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
# Task2: MC Matching
#
###############################################################################################
##
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.inFlightMuons = cms.EDProducer("PATGenCandsFromSimTracksProducer",
        src           = cms.InputTag("famosSimHits"),   ## use "famosSimHits" for FAMOS, "g4SimHits" for FULLSIM
        setStatus     = cms.int32(-1),
        particleTypes = cms.vstring("mu+"),          ## picks also mu-, of course
        filter        = cms.vstring("pt > 0.5"),     ## just for testing
        makeMotherLink = cms.bool(True),
        writeAncestors = cms.bool(True),             ## save also the intermediate GEANT ancestors of the muons
        genParticles   = cms.InputTag("genParticles"),
)
process.load("PhysicsTools.PatAlgos.patSequences_cff")
## prepare several clones of match associations for status 1 and 3
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
    "MyPatMatchingTask2",
    muonSrc  = cms.untracked.InputTag("cleanPatMuons")
)

## let it run
process.p = cms.Path(
    process.patDefaultSequence + process.analyzePatMCMatching
)

