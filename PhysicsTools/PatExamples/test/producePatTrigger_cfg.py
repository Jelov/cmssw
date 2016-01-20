
### ========
### Skeleton
### ========

## ---
## Start with pre-defined skeleton process
## ---
from PhysicsTools.PatAlgos.patTemplate_cfg import *

## switch to uncheduled mode
process.options.allowUnscheduled = cms.untracked.bool(True)
#process.Tracer = cms.Service("Tracer")

process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
process.load("PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff")

## ---
## Modifications
## ---
# input files. Let's use Z to mumu sample for this exercise instead of ttbar. 
#from PhysicsTools.PatAlgos.patInputFiles_cff import filesRelValProdTTbarAODSIM
#process.source.fileNames = filesRelValProdTTbarAODSIM
process.source.fileNames = ["/store/relval/CMSSW_7_1_0/RelValZMM_13/GEN-SIM-RECO/POSTLS171_V15-v1/00000/6650F961-99FB-E311-BA90-0025905A48BC.root"]

process.maxEvents.input     = 1000 # reduce number of events for testing.
process.options.wantSummary = True # to suppress the long output at the end of the job
# specific
#process.patJetCorrFactors.useRho = False
process.patJets.addTagInfos      = False # to save space
process.selectedPatMuons.cut     = 'isTrackerMuon=1 & isGlobalMuon=1 & innerTrack.numberOfValidHits>=11 & globalTrack.normalizedChi2<10.0  & globalTrack.hitPattern.numberOfValidMuonHits>0 & abs(dB)<0.02 & (trackIso+caloIso)/pt<0.05'

## ---
## Define the path ---> no need to define the path in the unscheduled mode (TJ)
## ---
#process.p = cms.Path(
#  process.patDefaultSequence
#)

### ========
### Plug-ins
### ========

## ---
## PAT trigger matching
## --
process.muonTriggerMatchHLTMuons = cms.EDProducer(
  # matching in DeltaR, sorting by best DeltaR
  "PATTriggerMatcherDRLessByR"
  # matcher input collections
, src     = cms.InputTag( 'selectedPatMuons' )
, matched = cms.InputTag( 'patTrigger' )
  # selections of trigger objects
, matchedCuts = cms.string( 'type( "TriggerMuon" ) && path( "HLT_Mu24_v*", 1, 0 )' ) # input does not yet have the 'saveTags' parameter in HLT
  # selection of matches
, maxDPtRel   = cms.double( 0.5 ) # no effect here
, maxDeltaR   = cms.double( 0.5 )
, maxDeltaEta = cms.double( 0.2 ) # no effect here
  # definition of matcher output
, resolveAmbiguities    = cms.bool( True )
, resolveByMatchQuality = cms.bool( True )
)

### ============
### Python tools
### ============

## --
## Switch to selected PAT objects in the main work flow
## --
##from PhysicsTools.PatAlgos.tools.coreTools import removeCleaning
##removeCleaning( process ) ## this function is not available anymore in 70X (TJ)
# to save a bit of disk space
process.out.outputCommands += [ 'drop *_*_*_*'
                               ,'keep *_patTrigger*_*_*'
                               ,'keep *_selectedPatMuons*_*_*'
                              ]
process.out.fileName = 'edmPatTrigger.root'
## --
## Switch on PAT trigger
## --
from PhysicsTools.PatAlgos.tools.trigTools import *
switchOnTrigger( process ) # This is optional and can be omitted.
switchOnTriggerMatching( process, triggerMatchers = [ 'muonTriggerMatchHLTMuons' ] )
# Switch to selected PAT objects in the trigger matching
#removeCleaningFromTriggerMatching( process ) ## this function is not available anymore in 70X (TJ)
