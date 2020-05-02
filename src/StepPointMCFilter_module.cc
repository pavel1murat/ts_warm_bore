//
// 2019-10-20 P.Murat: select events which have StepPointMC's with given PDG code in a collection with a given name
//
//

#include "art/Framework/Principal/Provenance.h"
#include "MCDataProducts/inc/StepPointMCCollection.hh"

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
#include <string>

using namespace std;

namespace mu2e {

  class StepPointMCFilter : public art::EDFilter {
  public:

    explicit StepPointMCFilter(fhicl::ParameterSet const& PSet) :
      _spmcCollTag  (PSet.get<string>     ("spmcCollTag"))
      , _pdgCodes   (PSet.get<vector<int>>("pdgCodes"   ))
      , _debugLevel (PSet.get<int>        ("debugLevel" ))
    {
    }

    virtual ~StepPointMCFilter() { }

    virtual void beginJob();
    virtual bool beginRun(art::Run&   aRun );
    virtual bool filter  (art::Event& Event);

  private:

    string        _spmcCollTag;
    vector<int>   _pdgCodes;
    int           _debugLevel;
  };

//-----------------------------------------------------------------------------
  void StepPointMCFilter::beginJob() {
  }

//-----------------------------------------------------------------------------
  bool StepPointMCFilter::beginRun(art::Run& aRun) {
    return true;
  }

  //-----------------------------------------------------------------------------
  bool StepPointMCFilter::filter(art::Event& Event) {

    bool found_pdg_code (0);

    art::Handle<StepPointMCCollection> spmcch;
    Event.getByLabel(_spmcCollTag,spmcch);

    if (spmcch.isValid()) {
      const StepPointMCCollection* spmcc = spmcch.product();

      for (const auto& iter : *spmcc) {
	const mu2e::StepPointMC* spmc = &iter;

	art::Ptr<mu2e::SimParticle> const& simptr = spmc->simParticle();
	const mu2e::SimParticle* simp  = simptr.get();

	int pdg_code = simp->pdgId();

	if (_debugLevel > 0) printf("[StepPointMCFilter::filter] : pdg_code: %10i\n",pdg_code);
	
	int n = _pdgCodes.size();
	for (int i=0; i<n ; i++) {
	  if (pdg_code == _pdgCodes[i]) {
	    found_pdg_code = _pdgCodes[i];
	    break;
	  }
	}
	if (found_pdg_code != 0) break;
      }
    }
    else {
      printf("[StepPointMCFilter::filter] : ERROR: StepPointMCCOllection %s not found\n",_spmcCollTag.data());
    }
    
    if (_debugLevel > 0) {
      printf("[StepPointMCFilter::filter] : run,subrun,event: %10i,%10i,%10i:  found_pdg_code: %10i\n", 
	     Event.run(),Event.subRun(), Event.event(),found_pdg_code);
    }

    return (found_pdg_code != 0);
  }

}  // end namespace mu2e

using mu2e::StepPointMCFilter;
DEFINE_ART_MODULE(StepPointMCFilter);
