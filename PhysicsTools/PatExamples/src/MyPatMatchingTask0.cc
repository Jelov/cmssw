// -*- C++ -*-
//
// Package:    MyPatMatchingTask0
// Class:      MyPatMatchingTask0
// 
/**\class MyPatMatchingTask0 MyPatMatchingTask0.cc UserCode/PatMCMatching/src/MyPatMatchingTask0.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Phat Srimanobhas,40 1-A11,+41227671646,
//         Created:  Thu Nov 24 21:39:38 CET 2011
// $Id$
//
//


// system include files
#include <memory>
#include <map>
#include <string>


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "Math/VectorUtil.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TLorentzVector.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Math/interface/deltaPhi.h"

//
// class declaration
//

class MyPatMatchingTask0 : public edm::EDAnalyzer {
public:
  explicit MyPatMatchingTask0(const edm::ParameterSet&);
  ~MyPatMatchingTask0();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  
  // input tags  
  edm::InputTag genSrc_;
  bool genDebug_;
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
MyPatMatchingTask0::MyPatMatchingTask0(const edm::ParameterSet& iConfig)
{
  //
  genSrc_   = iConfig.getUntrackedParameter<edm::InputTag>("genSrc");
  genDebug_ = iConfig.getUntrackedParameter<bool>("genDebug");
}


MyPatMatchingTask0::~MyPatMatchingTask0(){}

//
// member functions
//

// ------------ method called for each event  ------------
void
MyPatMatchingTask0::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace reco;
   using namespace pat;
   using namespace std;
   
   //-------------------------------------------------------------------------
   // Task 0:
   //
   // get genParticle collection
   edm::Handle<GenParticleCollection> genParticles;
   iEvent.getByLabel("genParticles", genParticles);
   //
   if(genDebug_==true){
     for(size_t i = 0; i < genParticles->size(); ++ i) {
       if(i>200) break;
       const GenParticle & ParticleCand = (*genParticles)[i];
       cout<<i<<") Particle = "<<ParticleCand.pdgId()<<", Status = "<<ParticleCand.status()<<endl;
       // Daughter
       const GenParticleRefVector& daughterRefs = ParticleCand.daughterRefVector();
       for(reco::GenParticleRefVector::const_iterator idr = daughterRefs.begin(); idr!= daughterRefs.end(); ++idr) {
	 cout<<"    - Daughter "<<(*idr).key()<<" "<<(*idr)->pdgId()<<endl;
       }
       // Mother
       const GenParticleRefVector& motherRefs = ParticleCand.motherRefVector();
       for(reco::GenParticleRefVector::const_iterator imr = motherRefs.begin(); imr!= motherRefs.end(); ++imr) {
	 cout<<"   - Mother "<<(*imr).key()<<" "<<(*imr)->pdgId()<<endl;
       }
     }
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
MyPatMatchingTask0::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MyPatMatchingTask0::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
MyPatMatchingTask0::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
MyPatMatchingTask0::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
MyPatMatchingTask0::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
MyPatMatchingTask0::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MyPatMatchingTask0::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MyPatMatchingTask0);
