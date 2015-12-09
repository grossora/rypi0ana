/**
 * \file ERAnaMassInspect.h
 *
 * \ingroup rypi0ana
 * 
 * \brief Class def header for a class ERAnaMassInspect
 *
 * @author ryan
 */

/** \addtogroup rypi0ana

    @{*/

#ifndef ERTOOL_ERANAMASSINSPECT_H
#define ERTOOL_ERANAMASSINSPECT_H

#include "ERTool/Base/AnaBase.h"
#include "ERTool/Base/ParticleGraph.h"
#include "ERTool/Base/Particle.h"
#include "ERTool/Base/EventData.h"
#include "GeoAlgo/GeoAlgo.h"


#include "TH1.h"
#include "TTree.h"


namespace ertool {

  /**
     \class ERAnaMassInspect
     User custom Analysis class made by kazuhiro
   */
  class ERAnaMassInspect : public AnaBase {
  
  public:

    /// Default constructor
    ERAnaMassInspect(const std::string& name="ERAnaMassInspect");

    /// Default destructor
    virtual ~ERAnaMassInspect(){}

    /// Reset function
    virtual void Reset();

    /// Function to accept fclite::PSet
    void AcceptPSet(const ::fcllite::PSet& cfg);

    /// Called @ before processing the first event sample
    void ProcessBegin();

    /// Function to evaluate input showers and determine a score
    bool Analyze(const EventData &data, const ParticleGraph &graph);

    /// Called after processing the last event sample
    void ProcessEnd(TFile* fout=nullptr);

   protected:
	geoalgo::GeoAlgo _geoAlgo;
   private: 
//        TH1D* _pi0MassReco;
  //      TH1D* _fancypi0MassReco;

/*
       TTree *FullTree;
	double _massRR;
	double _massMC;
	double _massRMC;
	double _massMCR;
	double _angleR;
	double _angleMC;
	double _EER;
	double _EEMC;
	double _EEPMC;
	double _dot;
	double _mcdot;
	double _newangle;
*/
       TTree *BestMatchTree;
	double _EBestR;
	double _EBestMC;
        double _PxBestR;
        double _PyBestR;
        double _PzBestR;
        double _PxBestMC;
        double _PyBestMC;
        double _PzBestMC;
        double _DirDifBest;
       TTree *SecondMatchTree;
        double _ESecondR;
        double _ESecondMC;
        double _PxSecondR;
        double _PySecondR;
        double _PzSecondR;
        double _PxSecondMC;
        double _PySecondMC;
        double _PzSecondMC;
        double _DirDifSecond;

       TTree *MatchTree;
	double _E1E2R;
	double _E1E2MC;
	double _OpeningAngleR;
	double _OpeningAngleMC;
	double _vtxXR;
	double _vtxYR;
	double _vtxZR;
//	double _vtxfshowersXR;
//	double _vtxfshowersYR;
//	double _vtxfshowersZR;
	double _vtxXMC;
	double _vtxYMC;
	double _vtxZMC;
	double _SPVTXOpeiningangleMC;
	double _SPVTXOpeiningangleRvtx;

  };
}
#endif

/** @} */ // end of doxygen group 
