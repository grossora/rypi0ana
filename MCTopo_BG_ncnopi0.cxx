#ifndef LARLITE_MCTOPO_BG_NCNOPI0_CXX
#define LARLITE_MCTOPO_BG_NCNOPI0_CXX

#include "MCTopo_BG_ncnopi0.h"

namespace larlite {

  bool MCTopo_BG_ncnopi0::initialize() {

    return true;
  }
  
  bool MCTopo_BG_ncnopi0::analyze(storage_manager* storage) {
	_nEvt++;
	
        // Bring in the info for the event
        auto mctruth = storage->get_data<event_mctruth>("generator");
            if(!mctruth) {
                print(larlite::msg::kERROR,__FUNCTION__,Form("Did not find specified data product, mctruth!"));
                return false;}// if no mctruth
	// Get all the particles
	// Get the Neutrino
        auto mcpart = mctruth->at(0).GetParticles();
        auto mcnu = mctruth->at(0).GetNeutrino();
//        auto ev_mcshower = storage->get_data<event_mcshower>("mcreco");// Get the mcshower info
	auto nupart = mcnu.Nu();
	bool nio = false;
            auto nux = nupart.Trajectory().at(0).X() ;
            auto nuy = nupart.Trajectory().at(0).Y() ;
            auto nuz = nupart.Trajectory().at(0).Z() ;
		if(nux<256.35-_fid && nux>0+_fid && nuy<116.5-_fid && nuy>-116.5+_fid && nuz<1036.8-_fid && nuz>-0+_fid){ 
			_nEvtinvol++;
			nio = true;
		}
	if(!nio) return false;
	if( mcnu.CCNC()==0){ return false;}

	//=&==&==&==&==&==&
	// What Type of Event 
	//=&==&==&==&==&==&
        int pi0    = 0;
	
        for(auto const& p : mcpart){
            auto x = p.Trajectory().at(0).X() ;
            auto y = p.Trajectory().at(0).Y() ;
            auto z = p.Trajectory().at(0).Z() ;
		// If the particle is contained then log 
		if(x<256.35-_fid && x>0+_fid && y<116.5-_fid && y>-116.5+_fid && z<1036.8-_fid && z>-0+_fid){ 
			if(p.PdgCode()==111 && p.StatusCode()==1) pi0++;
		}// If inside of the fiducial
	}// for loop over mcpart

	// if it is not signal....	
	 if(pi0>=1 ){ return false;} 
	_PassedEvt++;
    return true;
	// This is bad c++ but works
  }

  bool MCTopo_BG_ncnopi0::finalize() {

	std::cout<<"  \t PassedEvt  "<< _PassedEvt<<" evts in volume " <<_nEvtinvol<< " out of "<<_nEvt<<std::endl;

    return true;
  }

}
#endif
