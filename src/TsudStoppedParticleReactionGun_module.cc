///////////////////////////////////////////////////////////////////////////////
// clone of StoppedParticleReactionGun by Andrei Gaponenko, 2013
// PM: adds: fixed particle production time - a handy tool to estimate efficiencies 
// which do not depend on time
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <cmath>
#include <memory>
#include <algorithm>

#include "cetlib_except/exception.h"

#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Random/RandomEngine.h"
#include "CLHEP/Random/RandGeneral.h"
#include "CLHEP/Units/PhysicalConstants.h"

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

#include "ConfigTools/inc/ConfigFileLookupPolicy.hh"
#include "SeedService/inc/SeedService.hh"
#include "GlobalConstantsService/inc/GlobalConstantsHandle.hh"
#include "GlobalConstantsService/inc/ParticleDataTable.hh"
#include "GlobalConstantsService/inc/PhysicsParams.hh"
#include "DataProducts/inc/PDGCode.hh"
#include "MCDataProducts/inc/GenParticle.hh"
#include "MCDataProducts/inc/GenParticleCollection.hh"
#include "Mu2eUtilities/inc/RandomUnitSphere.hh"
#include "Mu2eUtilities/inc/CzarneckiSpectrum.hh"
#include "Mu2eUtilities/inc/SimpleSpectrum.hh"
#include "Mu2eUtilities/inc/EjectedProtonSpectrum.hh"
#include "Mu2eUtilities/inc/BinnedSpectrum.hh"
#include "Mu2eUtilities/inc/Table.hh"
#include "Mu2eUtilities/inc/RootTreeSampler.hh"
#include "GeneralUtilities/inc/RSNTIO.hh"

namespace mu2e {

  //================================================================
  class TsudStoppedParticleReactionGun : public art::EDProducer {
    fhicl::ParameterSet psphys_;

    PDGCode::type pdgId_;
    double mass_;

    enum SpectrumVar { TOTAL_ENERGY, KINETIC_ENERY, MOMENTUM };
    SpectrumVar spectrumVariable_;
    static SpectrumVar parseSpectrumVar(const std::string& name);

    double elow_; // BinnedSpectrum does not store emin and emax reliably
    double ehi_;
    BinnedSpectrum spectrum_;
    static BinnedSpectrum parseSpectrumShape(const fhicl::ParameterSet& psphys,
                                             PDGCode::type pdgId,
                                             double *elow,
                                             double *ehi);

    GenId genId_;

    int verbosityLevel_;

    art::RandomNumberGenerator::base_engine_t& eng_;
    CLHEP::RandGeneral randSpectrum_;
    RandomUnitSphere randomUnitSphere_;

    RootTreeSampler<IO::StoppedParticleF> stops_;
    float productionTime_;

    double generateEnergy();

  public:
    explicit TsudStoppedParticleReactionGun(const fhicl::ParameterSet& pset);
    virtual void produce(art::Event& event);
  };

  //================================================================
  TsudStoppedParticleReactionGun::TsudStoppedParticleReactionGun(const fhicl::ParameterSet& pset)
    : psphys_(pset.get<fhicl::ParameterSet>("physics"))
    , pdgId_(PDGCode::type(psphys_.get<int>("pdgId")))
    , mass_(GlobalConstantsHandle<ParticleDataTable>()->particle(pdgId_).ref().mass().value())
    , spectrumVariable_(parseSpectrumVar(psphys_.get<std::string>("spectrumVariable")))
    , elow_()
    , ehi_()
    , spectrum_(parseSpectrumShape(psphys_, pdgId_, &elow_, &ehi_))
    , genId_(GenId::findByName(psphys_.get<std::string>("genId", "StoppedParticleReactionGun")))
    , verbosityLevel_(pset.get<int>("verbosityLevel", 0))
    , eng_(createEngine(art::ServiceHandle<SeedService>()->getSeed()))
    , randSpectrum_(eng_, spectrum_.getPDF(), spectrum_.getNbins())
    , randomUnitSphere_(eng_)
    , stops_(eng_, pset.get<fhicl::ParameterSet>("muonStops"))
    , productionTime_(pset.get<int>("productionTime", -1.))                  // remember, this is a kludge
    
  {
    produces<mu2e::GenParticleCollection>();

    if(genId_ == GenId::enum_type::unknown) {
      throw cet::exception("BADCONFIG")<<"TsudStoppedParticleReactionGun: unknown genId "
                                       <<psphys_.get<std::string>("genId", "StoppedParticleReactionGun")
                                       <<"\n";
    }

    if(verbosityLevel_ > 0) {
      std::cout<<"TsudStoppedParticleReactionGun: using = "
               <<stops_.numRecords()
               <<" stopped particles"
               <<std::endl;

      std::cout<<"TsudStoppedParticleReactionGun: using GenId = "
               <<genId_
               <<std::endl;

      std::cout<<"TsudStoppedParticleReactionGun: producing particle "
               <<pdgId_
               <<", mass = "<<mass_
               <<std::endl;

      std::cout <<"TsudStoppedParticleReactionGun: spectrum shape = "
          <<psphys_.get<std::string>("spectrumShape") << std::endl;
      if (psphys_.get<std::string>("spectrumShape")  == "tabulated")
          std::cout << " Spectrum file = "
          << psphys_.get<std::string>("spectrumFileName")
          << std::endl;
    }
    if(verbosityLevel_ > 1){
      std::cout <<"TsudStoppedParticleReactionGun: spectrum: " << std::endl;
      spectrum_.print();
    }
  }

  //================================================================
  TsudStoppedParticleReactionGun::SpectrumVar
  TsudStoppedParticleReactionGun::parseSpectrumVar(const std::string& name) {
    if(name == "totalEnergy")  return TOTAL_ENERGY;
    if(name == "kineticEnergy")  return KINETIC_ENERY;
    if(name == "momentum")  return MOMENTUM;
    throw cet::exception("BADCONFIG")<<"TsudStoppedParticleReactionGun: unknown spectrum variable "<<name<<"\n";
  }

  //================================================================
  BinnedSpectrum
  TsudStoppedParticleReactionGun::parseSpectrumShape(const fhicl::ParameterSet& psphys,
                                                 PDGCode::type pdgId,
                                                 double *elow,
                                                 double *ehi)
  {
    BinnedSpectrum res;

    const std::string spectrumShape(psphys.get<std::string>("spectrumShape"));
    if (spectrumShape == "Czarnecki") {
      const double mass(GlobalConstantsHandle<ParticleDataTable>()->particle(pdgId).ref().mass().value());
      *elow = psphys.get<double>("elow", mass);
      *ehi = GlobalConstantsHandle<PhysicsParams>()->getEndpointEnergy();
      res.initialize< CzarneckiSpectrum >(*elow, *ehi, psphys.get<double>("spectrumResolution"));
    }
    else if (spectrumShape == "flat") {
      *elow = psphys.get<double>("elow");
      *ehi = psphys.get<double>("ehi");
      res.initialize<SimpleSpectrum>(*elow, *ehi, *ehi-*elow, SimpleSpectrum::Spectrum::Flat );
    }
    else if (spectrumShape == "CeEndpoint") {
      // A simple kludge: ignore the random distribution by setting elow=ehi=eConversion
      res.initialize<SimpleSpectrum>(0., 1., 1., SimpleSpectrum::Spectrum::Flat );
      *elow = *ehi = GlobalConstantsHandle<PhysicsParams>()->getEndpointEnergy();
    }
    else if (spectrumShape == "ejectedProtons") {
      *elow = 0.;
      *ehi = 105.; // cut off at muon mass
      double spectrumRes = (*ehi - *elow)/psphys.get<unsigned>("nbins");
      res.initialize<EjectedProtonSpectrum>(*elow, *ehi, spectrumRes);
    }
    else if (spectrumShape == "tabulated") {
      // assume that tabulated are the bin centers
      res.initialize(loadTable<2>( ConfigFileLookupPolicy()( psphys.get<std::string>("spectrumFileName"))) );
      *elow = res.getAbscissa(0);
      *ehi  = res.getAbscissa(res.getNbins()-1) + res.getBinWidth();
      if(psphys.get<bool>("BinCenter", false)){
        *elow -= res.getBinWidth()/2;
        *ehi  -= res.getBinWidth()/2;
      }
      if(*elow < 0.0) throw cet::exception("BADCONFIG")
        << "TsudStoppedParticleReactionGun: negative energy endpoint "<< *elow <<"\n";
    }
    else {
      throw cet::exception("BADCONFIG")
        << "TsudStoppedParticleReactionGun: unknown spectrum shape "<<spectrumShape<<"\n";
    }

    return res;
  }

  //================================================================
  void TsudStoppedParticleReactionGun::produce(art::Event& event) {

    std::unique_ptr<GenParticleCollection> output(new GenParticleCollection);

    const auto& stop = stops_.fire();

    const CLHEP::Hep3Vector pos(stop.x, stop.y, stop.z);

    const double energy = generateEnergy();
    const double p = energy * sqrt(1 - std::pow(mass_/energy,2));

    CLHEP::Hep3Vector p3 = randomUnitSphere_.fire(p);
    CLHEP::HepLorentzVector fourmom(p3, energy);

    double time = (productionTime_ > 0) ? productionTime_ : stop.t;

    output->emplace_back(pdgId_,
                         genId_,
                         pos,
                         fourmom,
                         time);

    event.put(std::move(output));
  }

  //================================================================
  double TsudStoppedParticleReactionGun::generateEnergy() {
    double res = elow_ + (ehi_ - elow_)*randSpectrum_.fire();
    if(res < 0.0)
       throw cet::exception("BADE")<<"TsudStoppedParticleReactionGun: negative energy "<< res <<"\n";
    switch(spectrumVariable_) {
    case TOTAL_ENERGY: break;
    case KINETIC_ENERY: res += mass_; break;
    case MOMENTUM     : res = sqrt(res*res+mass_*mass_); break;
    }
    return res;
  }

  //================================================================
} // namespace mu2e

DEFINE_ART_MODULE(mu2e::TsudStoppedParticleReactionGun);
