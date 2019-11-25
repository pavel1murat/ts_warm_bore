//
// select events which have SimParticle's with given PDG code in a collection with a given name
//
//

#include "art/Framework/Principal/Provenance.h"
#include "MCDataProducts/inc/SimParticleCollection.hh"

#include "art/Framework/Core/EDFilter.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Services/Optional/TFileService.h"
#include "art/Framework/Principal/Handle.h"
#include "canvas/Persistency/Common/Ptr.h"
#include "canvas/Persistency/Common/Ptr.h"
#include "cetlib_except/exception.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include <cmath>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

namespace mu2e {

  class SimParticleFilter : public art::EDFilter {
  public:

    typedef SimParticleCollection::key_type key_type;

    explicit SimParticleFilter(fhicl::ParameterSet const& PSet) :
      art::EDFilter(PSet)
      , _simpCollTag  (PSet.get<string>     ("simpCollTag"))
      , _pdgCodes     (PSet.get<vector<int>>("pdgCodes"   ))
    {
    }

    virtual ~SimParticleFilter() { }

    virtual void beginJob();
    virtual void beginRun(art::Run const& Rn);
    virtual bool filter  (art::Event& Evt);

  private:

    string        _simpCollTag;
    vector<int>   _pdgCodes;
  };

//-----------------------------------------------------------------------------
  void SimParticleFilter::beginJob() {
  }

//-----------------------------------------------------------------------------
  void SimParticleFilter::beginRun(art::Run const& run) {
  }

  //-----------------------------------------------------------------------------
  void SimParticleFilter::filter(art::Event& Event) {

    bool found (false);

    art::Handle<SimParticleCollection> simpcH
    event.getByLabel(_simpCollTag,simpch);

    const SimParticleCollection* simpc = simpch->product();

    for (const auto& iter : simpc) {
      const mu2e::SimParticle* simp = &iter.second;

      int pdg_code = simp->pdgId();

      for (int i=0; i< _pdgCodes.size(); i++) {
	if (pdg_code == _pdgCodes[i]) {
	  found = true;
	}
      }
    }

    return found;
  }

}  // end namespace mu2e

using mu2e::SimParticleFilter;
DEFINE_ART_MODULE(SimParticleFilter);
