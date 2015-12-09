#ifndef ERTOOL_ERANAMASSINSPECT_CXX
#define ERTOOL_ERANAMASSINSPECT_CXX

#include "ERAnaMassInspect.h"

namespace ertool {

  ERAnaMassInspect::ERAnaMassInspect(const std::string& name) : AnaBase(name)
  {
        BestMatchTree = new TTree("BestMatchTree","BestMatchTree");
                BestMatchTree->Branch("_EBestR",&_EBestR,"_EBestR/D");
                BestMatchTree->Branch("_EBestMC",&_EBestMC,"_EBestMC/D");
                BestMatchTree->Branch("_PxBestR",&_PxBestR,"_PxBestR/D");
                BestMatchTree->Branch("_PyBestR",&_PyBestR,"_PyBestR/D");
                BestMatchTree->Branch("_PzBestR",&_PzBestR,"_PzBestR/D");
                BestMatchTree->Branch("_PxBestMC",&_PxBestMC,"_PxBestMC/D");
                BestMatchTree->Branch("_PyBestMC",&_PyBestMC,"_PyBestMC/D");
                BestMatchTree->Branch("_PzBestMC",&_PzBestMC,"_PzBestMC/D");
                BestMatchTree->Branch("_DirDifBest",&_DirDifBest,"_DirDifBest/D");

        SecondMatchTree = new TTree("SecondMatchTree","SecondMatchTree");
                SecondMatchTree->Branch("_ESecondR",&_ESecondR,"_ESecondR/D");
                SecondMatchTree->Branch("_ESecondMC",&_ESecondMC,"_ESecondMC/D");
                SecondMatchTree->Branch("_PxSecondR",&_PxSecondR,"_PxSecondR/D");
                SecondMatchTree->Branch("_PySecondR",&_PySecondR,"_PySecondR/D");
                SecondMatchTree->Branch("_PzSecondR",&_PzSecondR,"_PzSecondR/D");
                SecondMatchTree->Branch("_PxSecondMC",&_PxSecondMC,"_PxSecondMC/D");
                SecondMatchTree->Branch("_PySecondMC",&_PySecondMC,"_PySecondMC/D");
                SecondMatchTree->Branch("_PzSecondMC",&_PzSecondMC,"_PzSecondMC/D");
                SecondMatchTree->Branch("_DirDifSecond",&_DirDifSecond,"_DirDifSecond/D");
	
        MatchTree = new TTree("MatchTree","MatchTree");
		MatchTree->Branch("_EBestR",&_EBestR,"_EBestR/D");
                MatchTree->Branch("_EBestMC",&_EBestMC,"_EBestMC/D");
                MatchTree->Branch("_PxBestR",&_PxBestR,"_PxBestR/D");
                MatchTree->Branch("_PyBestR",&_PyBestR,"_PyBestR/D");
                MatchTree->Branch("_PzBestR",&_PzBestR,"_PzBestR/D");
                MatchTree->Branch("_PxBestMC",&_PxBestMC,"_PxBestMC/D");
                MatchTree->Branch("_PyBestMC",&_PyBestMC,"_PyBestMC/D");
                MatchTree->Branch("_PzBestMC",&_PzBestMC,"_PzBestMC/D");
                MatchTree->Branch("_DirDifBest",&_DirDifBest,"_DirDifBest/D");
                MatchTree->Branch("_ESecondR",&_ESecondR,"_ESecondR/D");
                MatchTree->Branch("_ESecondMC",&_ESecondMC,"_ESecondMC/D");
                MatchTree->Branch("_PxSecondR",&_PxSecondR,"_PxSecondR/D");
                MatchTree->Branch("_PySecondR",&_PySecondR,"_PySecondR/D");
                MatchTree->Branch("_PzSecondR",&_PzSecondR,"_PzSecondR/D");
                MatchTree->Branch("_PxSecondMC",&_PxSecondMC,"_PxSecondMC/D");
                MatchTree->Branch("_PySecondMC",&_PySecondMC,"_PySecondMC/D");
                MatchTree->Branch("_PzSecondMC",&_PzSecondMC,"_PzSecondMC/D");
                MatchTree->Branch("_DirDifSecond",&_DirDifSecond,"_DirDifSecond/D");
                MatchTree->Branch("_E1E2R",&_E1E2R,"_E1E2R/D");
                MatchTree->Branch("_E1E2MC",&_E1E2MC,"_E1E2MC/D");
                MatchTree->Branch("_OpeningAngleR",&_OpeningAngleR,"_OpeningAngleR/D");
                MatchTree->Branch("_OpeningAngleMC",&_OpeningAngleMC,"_OpeningAngleMC/D");
                MatchTree->Branch("_vtxXR",&_vtxXR,"_vtxXR/D");
                MatchTree->Branch("_vtxYR",&_vtxYR,"_vtxYR/D");
                MatchTree->Branch("_vtxZR",&_vtxZR,"_vtxZR/D");
                MatchTree->Branch("_vtxXMC",&_vtxXMC,"_vtxXMC/D");
                MatchTree->Branch("_vtxYMC",&_vtxYMC,"_vtxYMC/D");
                MatchTree->Branch("_vtxZMC",&_vtxZMC,"_vtxZMC/D");
                MatchTree->Branch("_SPVTXOpeiningangleMC",&_SPVTXOpeiningangleMC,"_SPVTXOpeiningangleMC/D");
                MatchTree->Branch("_SPVTXOpeiningangleRvtx",&_SPVTXOpeiningangleRvtx,"_SPVTXOpeiningangleRvtx/D");
	
 

}

  void ERAnaMassInspect::Reset()
  {}

  void ERAnaMassInspect::AcceptPSet(const ::fcllite::PSet& cfg)
  {}

  void ERAnaMassInspect::ProcessBegin()
  {}

  bool ERAnaMassInspect::Analyze(const EventData &data, const ParticleGraph &graph )
  {
	// This ana will look at events that produce just one pi0. 
	// To start this makes it easy to understand what is happening with matching 
	// So what when we look at raw numbers from here for a an effieency our definition should be 
	// The events that produce only one pi0 in reco. 
	// That means there still more events that produce multipi0 but we are not looking at them yet
std::cout<<" Start Of event"<<std::endl;
        auto mcgraph = MCParticleGraph();
        auto mceventdata = MCEventData();
        auto particles = graph.GetParticleArray();
//        unsigned int pi0id =-999;
        int  pi0counter = 0;
        // check to see if we have reco a pi0 that is primary 
	Shower showerA;	
	Shower showerB;	
	Shower mcshowerA;	
	Shower mcshowerB;	
	bool bshrA = false;
	bool mcbshrA = false;
        for(auto const & p : particles){
                if(p.PdgCode()==111 ){
		// Fill out the pi0vtx
		_vtxXR = p.Vertex()[0];
		_vtxYR = p.Vertex()[1];
		_vtxZR = p.Vertex()[2];
                                auto kids = p.Children();
                                for( auto const  kid: kids){
                                        auto kidpart = graph.GetParticle(kid);
					if(bshrA) showerB= data.Shower(kidpart.RecoID());
					if(!bshrA){showerA= data.Shower(kidpart.RecoID());
					bshrA= true;}
                                        }
                                pi0counter++;}}
                                //pi0id = p.ID(); pi0counter++;}}
	if(pi0counter!=1) return false;
// MC	
double showerAEnergyMC;
double showerBEnergyMC;
::geoalgo::Vector showerADirMC;
::geoalgo::Vector showerBDirMC;
	auto mcp =  mcgraph.GetParticleArray();
//        unsigned int mcid =-999;
        int  mcpi0counter = 0;
        for(auto const & m : mcp){if(m.PdgCode()==111){ 
		// Fill out the pi0vtxMC
		_vtxXMC = m.Vertex()[0];
		_vtxYMC = m.Vertex()[1];
		_vtxZMC = m.Vertex()[2];
			auto kids = m.Children();
				if(kids.size()!=2) return false;// This is a dalitz Decay
                                for( auto const  kid: kids){
                                        auto kidpart = mcgraph.GetParticle(kid);
				if(!kidpart.HasRecoObject()) return false;
					if(mcbshrA){
						showerBEnergyMC = kidpart.Energy();
						showerBDirMC = kidpart.Momentum();
						 mcshowerB= mceventdata.Shower(kidpart.RecoID());}
					if(!mcbshrA){
						showerAEnergyMC = kidpart.Energy();
						showerADirMC = kidpart.Momentum();
						mcshowerA= mceventdata.Shower(kidpart.RecoID());
						mcbshrA= true;}
                                        }
			//mcid = m.ID();}}// not sure if this will work for bnb
			 mcpi0counter;}} // for single particle
///////////////EVENTDATA TEST////////////////////////////////////
///////////////////////////////////////
///========================///////////
///////////////////////////////////////
///========================///////////
///////////////////////////////////////
// I have both showers mc and reco 
// Find which to match up to
	// use direction to match them instead of start point. 
std::cout<<"\nWORKING AREA FOR MATCHING STARTS"<<std::endl;

	double _angleAMAR = showerADirMC.Angle(showerA.Dir());
	double _angleAMBR = showerADirMC.Angle(showerB.Dir());
	double _angleBMAR = showerBDirMC.Angle(showerA.Dir());
	double _angleBMBR = showerBDirMC.Angle(showerB.Dir());
	
	std::vector<double> matchangle;
	matchangle.push_back(_angleAMAR);
	matchangle.push_back(_angleAMBR);
	matchangle.push_back(_angleBMAR);
	matchangle.push_back(_angleBMBR);
	
	double maxangle = 10;
	int matchcode = -999;
	for(unsigned int a=0; a<matchangle.size(); a++){
		if(matchangle[a]==matchangle[a]) {
		if(matchangle[a]<maxangle){ 
		maxangle = matchangle[a]; 
		matchcode = a;}
			}// if matchangle.... looking for nan's 
		}
	if(matchcode == -999) std::cout<<"We did not find a match "<<std::endl;
	
	bool AABB = false;
	bool ABBA = false;
	if(matchcode == 0 || matchcode == 3 ) AABB=true;
	if(matchcode == 1 || matchcode == 2 ) ABBA=true;
	
	if(!AABB && !ABBA) std::cout<<" We don't have a match AGAIN"<<std::endl;

	// Compare First best matched shower 
	double bestshowerEnergy ; 
	double bestshowerEnergyMC ;
	::geoalgo::Vector bestshowerDir;
	::geoalgo::Vector bestshowerDirMC;
	double secondshowerEnergy ; 
	double secondshowerEnergyMC ;
	::geoalgo::Vector secondshowerDir;
	::geoalgo::Vector secondshowerDirMC;
	if(AABB){ 
		if(matchcode==0){	
			bestshowerEnergy = showerA._energy;
			bestshowerEnergyMC = showerAEnergyMC;
			bestshowerDir = showerA.Dir();
			bestshowerDirMC = showerADirMC;
			secondshowerEnergy = showerB._energy;
			secondshowerEnergyMC = showerBEnergyMC;
			secondshowerDir = showerB.Dir();
			secondshowerDirMC = showerBDirMC;
			}

		if(matchcode==3){	
			secondshowerEnergy = showerA._energy;
			secondshowerEnergyMC = showerAEnergyMC;
			secondshowerDir = showerA.Dir();
			secondshowerDirMC = showerADirMC;
			bestshowerEnergy = showerB._energy;
			bestshowerEnergyMC = showerBEnergyMC;
			bestshowerDir = showerB.Dir();
			bestshowerDirMC = showerBDirMC;
			}
		
		}
	if(ABBA){ 
		if(matchcode==1){
			bestshowerEnergy = showerA._energy;
			bestshowerEnergyMC = showerBEnergyMC;
			bestshowerDir = showerA.Dir();
			bestshowerDirMC = showerBDirMC;
			secondshowerEnergy = showerB._energy;
			secondshowerEnergyMC = showerAEnergyMC;
			secondshowerDir = showerB.Dir();
			secondshowerDirMC = showerADirMC;
			}
		if(matchcode==2){
			secondshowerEnergy = showerA._energy;
			secondshowerEnergyMC = showerBEnergyMC;
			secondshowerDir = showerA.Dir();
			secondshowerDirMC = showerBDirMC;
			bestshowerEnergy = showerB._energy;
			bestshowerEnergyMC = showerAEnergyMC;
			bestshowerDir = showerB.Dir();
			bestshowerDirMC = showerADirMC;
			}
		}

// Define tree stuff
	_EBestR = bestshowerEnergy;
	_EBestMC = bestshowerEnergyMC;
	_PxBestR = bestshowerDir[0]/bestshowerDir.Length();
	_PyBestR = bestshowerDir[1]/bestshowerDir.Length();
	_PzBestR = bestshowerDir[2]/bestshowerDir.Length();
	_PxBestMC = bestshowerDirMC[0]/bestshowerDirMC.Length();
	_PyBestMC = bestshowerDirMC[1]/bestshowerDirMC.Length();
	_PzBestMC = bestshowerDirMC[2]/bestshowerDirMC.Length();
	_ESecondR = secondshowerEnergy;
	_ESecondMC = secondshowerEnergyMC;
	_PxSecondR = secondshowerDir[0]/secondshowerDir.Length();
	_PySecondR = secondshowerDir[1]/secondshowerDir.Length();
	_PzSecondR = secondshowerDir[2]/secondshowerDir.Length();
	_PxSecondMC = secondshowerDirMC[0]/secondshowerDirMC.Length();
	_PySecondMC = secondshowerDirMC[1]/secondshowerDirMC.Length();
	_PzSecondMC = secondshowerDirMC[2]/secondshowerDirMC.Length();
	_DirDifBest =  bestshowerDir.Angle(bestshowerDirMC);
	_DirDifSecond =  secondshowerDir.Angle(secondshowerDirMC);

	BestMatchTree->Fill();
	SecondMatchTree->Fill();

	_E1E2R = bestshowerEnergy*secondshowerEnergy;
	_E1E2MC = bestshowerEnergyMC*secondshowerEnergyMC;
	_OpeningAngleR =  bestshowerDir.Angle(secondshowerDir);
	_OpeningAngleMC =  bestshowerDirMC.Angle(secondshowerDirMC);

	// calculate opening angle using truth pi0 vtx and showers start points
geoalgo::Vector_t SAv(3);
        SAv[0] = (showerA.Start()[0] - _vtxXMC);
        SAv[1] = (showerA.Start()[1] - _vtxYMC);
        SAv[2] = (showerA.Start()[2] - _vtxZMC);
geoalgo::Vector_t SBv(3);
        SBv[0] = (showerB.Start()[0] - _vtxXMC);
        SBv[1] = (showerB.Start()[1] - _vtxYMC);
        SBv[2] = (showerB.Start()[2] - _vtxZMC);
	_SPVTXOpeiningangleMC = SAv.Angle(SBv);	
	// calculate opening angle using reco pi0 vtx and showers start points: basically using point from common origin
geoalgo::Vector_t Sav(3);
        Sav[0] = (showerA.Start()[0] - _vtxXR);
        Sav[1] = (showerA.Start()[1] - _vtxYR);
        Sav[2] = (showerA.Start()[2] - _vtxZR);
geoalgo::Vector_t Sbv(3);
        Sbv[0] = (showerB.Start()[0] - _vtxXR);
        Sbv[1] = (showerB.Start()[1] - _vtxYR);
        Sbv[2] = (showerB.Start()[2] - _vtxZR);
	_SPVTXOpeiningangleRvtx = Sav.Angle(Sbv);	

	MatchTree->Fill();
//std::cout<<"WORKING AREA FOR MATCHING ENDS\n"<<std::endl;
///////////////////////////////////////
///========================///////////
///////////////////////////////////////
///========================///////////
///////////////////////////////////////

 return true; }

  void ERAnaMassInspect::ProcessEnd(TFile* fout)
  {
	BestMatchTree->Write();
	SecondMatchTree->Write();
	MatchTree->Write();
}

}

#endif
