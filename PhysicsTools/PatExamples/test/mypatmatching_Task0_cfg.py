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
process.maxEvents.input = 10


###############################################################################################
#
# Task0:
#
###############################################################################################
##
process.analyzePatMCMatching = cms.EDAnalyzer(
    "MyPatMatchingTask0",
    genSrc   = cms.untracked.InputTag("genParticles"),
    genDebug = cms.untracked.bool(True)
    )

## let it run
process.p = cms.Path(
#    process.patDefaultSequence + 
	process.analyzePatMCMatching
    )

process.out.fileName = "myTuple_task0.root"

process.out.outputCommands += [
    'keep *_genParticles_*_*'
    ]
