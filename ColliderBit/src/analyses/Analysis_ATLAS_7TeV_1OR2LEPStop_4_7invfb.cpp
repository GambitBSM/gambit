//
// Created by dsteiner on 31/07/18.
// Amended by Martin White on 08/03/19.
//
// Based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2012-10/ (arXiv:1209.2102)

//#include <gambit/ColliderBit/colliders/SpecializablePythia.hpp>
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include <gambit/ColliderBit/ATLASEfficiencies.hpp>
#include "gambit/ColliderBit/analyses/AnalysisUtil.hpp"

namespace Gambit {
  namespace ColliderBit {

    using namespace std;
    using namespace HEPUtils;

    class Analysis_ATLAS_7TeV_1OR2LEPStop_4_7invfb : public Analysis {
public:

// Required detector sim
static constexpr const char* detector = "ATLAS";


#define CUTFLOWMAP(X)				\
      X(Total_events)				\
      X(electron_eq_4_jets)			\
      X(electron_met_gt_40)			\
      X(electron_eq_2_bjets)			\
      X(electron_sr)				\
      X(muon_eq_4_jets)				\
      X(muon_met_gt_40)				\
      X(muon_eq_2_bjets)			\
      X(muon_sr)				\
      X(twoLep_met_gt_40)			\
      X(twoLep_gt_1_bjet)			\
      X(mll_lt_81)				\
      X(mll_gt_30_lt_81)			\
      X(num_2lsr1)				\
      X(num_2lsr2)
#define f(x) x,
#define g(x) #x,
      const std::vector<std::string> cutflowNames = {CUTFLOWMAP(g)};
      enum cutflowEnum {CUTFLOWMAP(f)};
#undef g
#undef f
#undef CUTFLOWMAP

#define VARMAP(X)				\
      X(mTopHad)				\
      X(oneLepSqrtS)				\
      X(mllKey)					\
      X(twoLepSqrtS)
#define f(x) x,
#define g(x) #x,
      const std::vector<std::string> varNames = {VARMAP(g)};
      enum varEnum {VARMAP(f)};
#undef g
#undef f
#undef VARMAP

      std::map<std::string, std::vector<double>> varResults;

      std::map<std::string, int> cutflows;

      double num1LSR=0;
      double num2LSR1=0;
      double num2LSR2=0;

      std::vector<double> calcNuPz(double Mw, P4 metMom, P4 lepMom)
      {
	double mu = sqr(Mw) / 2.0 + metMom.px() * lepMom.px() + metMom.py() * lepMom.py();
	double denom = lepMom.E2() - lepMom.pz2();
	double a = mu * lepMom.pz() / denom;
	double a2 = sqr(a);
	double b = (lepMom.E2() * metMom.E2() - sqr(mu)) / denom;
	double delta = a2 - b;
	if (delta < 0)
	  {
	    return {a};
	  }
	else
	  {
	    return {a + std::sqrt(delta), a - std::sqrt(delta)};
	  }
      }

      P4 getBestHadronicTop(
			    std::vector<const Jet *> bJets,
			    std::vector<const Jet *> lightJets,
			    const P4& leptonMom,
			    const P4& metMom,
			    double width,
			    double mean
			    )
      {
	// gaussian probability density function
	auto prob = [&width, &mean](P4 particle) {
	  return 1 - std::erf(1.0 * std::abs(particle.m() - mean) / (std::sqrt(2.0) * width));
	};

	double pTotal = 0.0;
	P4 bestHadronicTop;
	std::vector<double> nuPzChoices = calcNuPz(80.0, metMom, leptonMom);
	P4 nu;
	for (double nuPz : nuPzChoices)
	  {
	    double nuE = std::sqrt(sqr(metMom.px()) + sqr(metMom.py()) + sqr(nuPz));
	    nu.setPE(metMom.px(), metMom.py(), nuPz, nuE);
	    P4 WLep = leptonMom + nu;
	    // go through every bJet
	    for (const Jet* firstBJet : bJets)
	      {
		for (const Jet* secondBJet : bJets)
		  {
		    if (firstBJet == secondBJet)
		      {
			continue;
		      }
		    P4 topLep = *firstBJet + WLep;
		    // go through every combination of two light jets
		    for (const Jet* firstLightJet : lightJets)
		      {
			for (const Jet* secondLightJet : lightJets)
			  {
			    // don't want to use a light jet with itself
			    if (firstLightJet == secondLightJet)
			      {
				continue;
			      }
			    P4 WHad = *firstLightJet + *secondLightJet;
			    P4 topHad = *secondBJet + WHad;
			    // calculate a new probability
			    double newPTotal = prob(topHad) * prob(WHad) * prob(topLep) * prob(WLep);
			    if (newPTotal > pTotal)
			      {
				// update the best values
				pTotal = newPTotal;
				bestHadronicTop = topHad;
			      }
			  }
		      }
		  }
	      }
	  }
	return bestHadronicTop;
      }

      double calcMt(P4 metVec, P4 lepVec)
      {
	double Met = metVec.pT();
	double pTLep = lepVec.pT();
	return std::sqrt(2 * pTLep * Met - 2 * AnalysisUtil::dot2D(lepVec, metVec));
      }


      double calcSqrtSSubMin(P4 visibleSubsystem, P4 invisbleSubsystem)
      {
	double visiblePart = std::sqrt(sqr(visibleSubsystem.m()) + sqr(visibleSubsystem.pT()));
	double invisiblePart = invisbleSubsystem.pT();
	double twoDimensionalVecSum =
	  sqr(visibleSubsystem.px() + invisbleSubsystem.px())
	  + sqr(visibleSubsystem.py() + invisbleSubsystem.py());
	return std::sqrt(sqr(visiblePart + invisiblePart) - twoDimensionalVecSum);
      }

      void getBJets(
		    std::vector<const Jet*>& jets,
		    std::vector<const Jet*>* bJets,
		    std::vector<const Jet*>* lightJets)
      {
	/// @note We assume that b jets have previously been 100% tagged
	const std::vector<double> a = {0, 10.};
	const std::vector<double> b = {0, 10000.};
	const std::vector<double> c = {0.60};
	BinnedFn2D<double> _eff2d(a,b,c);
	for (const Jet* jet : jets)
	  {
	    bool hasTag = has_tag(_eff2d, jet->eta(), jet->pT());
	    if(jet->btag() && hasTag && jet->abseta() < 2.5)
	      {
		bJets->push_back(jet);
	      }
	    else
	      {
		lightJets->push_back(jet);
	      }
	  }
      }


      /**
       * The constructor that should initialize some variables
       */
Analysis_ATLAS_7TeV_1OR2LEPStop_4_7invfb()
      {
	set_analysis_name("ATLAS_7TeV_1OR2LEPStop_4_7invfb");
	set_luminosity(4.7);
      }

      /**
       * Performs the main part of the analysis
       * @param event an event contain particle and jet information
       */
      void run(const HEPUtils::Event* event)
      {
	// TODO: take log of plots and constrain the plot range
	//HEPUtilsAnalysis::analyze(event);
	//cout << "Event number: " << num_events() << endl;
	incrementCut(Total_events);
	std::vector<const Particle*> electrons = event->electrons();
	std::vector<const Particle*> muons = event->muons();
	std::vector<const Jet*> jets = event->jets();

	electrons = AnalysisUtil::filterPtEta(electrons, 20, 2.47);
	muons = AnalysisUtil::filterPtEta(muons, 10, 2.4);
	jets = AnalysisUtil::filterPtEta(jets, 20, 4.5);

	std::vector<const Jet*> bJets, lightJets;
	getBJets(jets, &bJets, &lightJets);

	jets = AnalysisUtil::jetLeptonOverlapRemoval(jets, electrons, 0.2);
	electrons = AnalysisUtil::leptonJetOverlapRemoval(electrons, jets, 0.4);
	muons = AnalysisUtil::leptonJetOverlapRemoval(muons, jets, 0.4);

	jets = AnalysisUtil::filterMaxEta(jets, 2.5);

	ATLAS::applyTightIDElectronSelection(electrons);

	std::vector<const Particle*> leptons = AnalysisUtil::getSortedLeptons({electrons, muons});
	std::sort(electrons.begin(), electrons.end(), AnalysisUtil::sortParticlesByPt);
	std::sort(muons.begin(), muons.end(), AnalysisUtil::sortParticlesByPt);
	std::sort(jets.begin(), jets.end(), AnalysisUtil::sortJetsByPt);
	std::sort(bJets.begin(), bJets.end(), AnalysisUtil::sortJetsByPt);
	std::sort(lightJets.begin(), lightJets.end(), AnalysisUtil::sortJetsByPt);

	size_t
	  nLeptons = leptons.size(),
	  nJets = jets.size(),
	  nBJets = bJets.size(),
	  nLightJets = lightJets.size();

	double Met = event->met();
	const P4& metVec = event->missingmom();

	if (nLeptons == 1)
	  {
	    if (!AnalysisUtil::muonFilter7TeV(muons) && muons.size() == 1)
	      {
		return;
	      }
	    cutflowEnum a, b, c;
	    if (electrons.size() == 1) a = electron_eq_4_jets, b = electron_met_gt_40, c = electron_eq_2_bjets;
	    if (muons.size() == 1) a = muon_eq_4_jets, b = muon_met_gt_40, c = muon_eq_2_bjets;
	    if (nJets == 4)
	      {
		incrementCut(a);
		{
		  if (Met > 40)
		    {
		      incrementCut(b);
		      if (nBJets == 2)
			{
			  incrementCut(c);
			}
		    }
		}
	      }
	  }




	// minimal selection requirements for single lepton
	if (nLeptons == 1 && nBJets >= 2 && nLightJets >= 2 && Met > 40)
	  {
	    double mT = calcMt(metVec, leptons[0]->mom());

	    auto isValidTop = [](double mean, double width, double mass) {return mass < mean - 0.5 * width;};

	    if (mT > 30)
	      {
		double mean = 0.0, width = 0.0;
		P4 hadronicTop;

		P4 visibleSubsystem = *leptons[0] + *lightJets[0] + *lightJets[1] + *bJets[0] + *bJets[1];
		double sqrtSsubMin = calcSqrtSSubMin(visibleSubsystem, metVec);
		bool isOneLep = false;
		// e-channel
		if (electrons.size() == 1 && electrons[0]->pT() > 25)
		  {
		    mean = 168.4, width = 18.0;
		    hadronicTop = getBestHadronicTop(bJets, lightJets, *electrons[0], metVec, width, mean);
		    isOneLep = true;
		  }

		// mu-channel
		if (muons.size() == 1 && muons[0]->pT() > 20)
		  {
		    mean = 168.2, width = 18.6;
		    hadronicTop = getBestHadronicTop(bJets, lightJets, *muons[0], metVec, width, mean);
		    isOneLep = true;
		  }


		bool validTop = isValidTop(mean, width, hadronicTop.m());

		if (isOneLep)
		  {
		    varResults[varNames[mTopHad]].push_back(hadronicTop.m());
		    varResults[varNames[oneLepSqrtS]].push_back(sqrtSsubMin);
		  }

		// check if we are in the 1LSR signal region
		if (isOneLep && validTop && sqrtSsubMin < 250)
		  {
		    num1LSR += event->weight();
		    if (electrons.size() == 1) incrementCut(electron_sr);
		    if (muons.size() == 1) incrementCut(muon_sr);
		  }
	      }
	  }

	if (nLeptons == 2 && Met > 40 && AnalysisUtil::oppositeSign(leptons[0], leptons[1]) && nJets >= 2)
	  {
	    P4 ll = *leptons[0] + *leptons[1];
	    double mll = ll.m();
	    incrementCut(twoLep_met_gt_40);
	    {
	      if (nBJets >= 1)
		{
		  incrementCut(twoLep_gt_1_bjet);
		  if (mll < 81)
		    {
		      incrementCut(mll_lt_81);
		    }
		  if (mll < 81 && mll > 30)
		    {
		      incrementCut(mll_gt_30_lt_81);
		    }
		}
	    }
	  }

	if (nLeptons == 2 && AnalysisUtil::oppositeSign(leptons[0], leptons[1]) && Met > 40 && nJets >= 2 && nBJets >= 1)
	  {
	    P4 ll = *leptons[0] + *leptons[1];
	    double mll = ll.m();

	    P4 visibleSubsystem = *leptons[0] + *leptons[1] + *jets[0] + *jets[1];

	    double sqrtSsubMin = calcSqrtSSubMin(visibleSubsystem, metVec);

	    double mlljj = visibleSubsystem.m();
	    varResults[varNames[mllKey]].push_back(mll);
	    if (mll > 30 && mll < 81)
	      {
		bool isTwoLeptonEvent = false;

		// ee channel
		if (electrons.size() == 2 && electrons[0]->pT() > 25)
		  {
		    isTwoLeptonEvent = true;
		  }

		// mu-mu channel
		if (muons.size() == 2 && muons[0]->pT() > 20)
		  {
		    isTwoLeptonEvent = true;
		  }

		// e-mu channel
		if (electrons.size() == 1 && muons.size() == 1 && (electrons[0]->pT() > 25 || muons[0]->pT() > 20))
		  {
		    isTwoLeptonEvent = true;
		  }

		if (isTwoLeptonEvent)
		  {
		    varResults[varNames[twoLepSqrtS]].push_back(sqrtSsubMin);

		    if (sqrtSsubMin < 225)
		      {
			num2LSR1 += event->weight();
			incrementCut(num_2lsr1);
		      }
		    if (sqrtSsubMin < 235 && mlljj < 140)
		      {
			num2LSR2 += event->weight();
			incrementCut(num_2lsr2);
		      }
		  }
	      }
	  }
      }

/**
       * Adds results from other threads if OMP_NUM_THREAD != 1
       * @param other results from another thread
       */

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
void combine(const Analysis* other)
{
  const Analysis_ATLAS_7TeV_1OR2LEPStop_4_7invfb* specificOther = dynamic_cast<const Analysis_ATLAS_7TeV_1OR2LEPStop_4_7invfb*>(other);
  num1LSR += specificOther->num1LSR;
  num2LSR1 += specificOther->num2LSR1;
  num2LSR2 += specificOther->num2LSR2;
}


      void collect_results()
      {
	//saveCutFlow();

	add_result(SignalRegionData("1LSR", 50, {num1LSR, 0.}, {38., 7.}));
	add_result(SignalRegionData("2LSR1", 123, {num2LSR1, 0.}, {115., 15.}));
	add_result(SignalRegionData("2LSR2", 47, {num2LSR2, 0.}, {46., 7.}));

	//cout << "1LSR: " << num1LSR << ", 2LSR1: " << num2LSR1 << ", 2LSR2: " << num2LSR2 << endl;

	/*for (std::pair<std::string, std::vector<double>> entry : varResults)
	  {
	    cout << "SAVE_START:" << entry.first << endl;
	    for (double value : entry.second)
	      {
		cout << value << endl;
	      }
	    cout << "SAVE_END" << endl;
	    }*/
      }

protected:

void analysis_specific_reset()
{
  num1LSR = 0;
  num2LSR1 = 0;
  num2LSR2 = 0;
  for (std::string varName : varNames)
    {
      varResults[varName] = {};
    }
}

/*void scale(double factor)
  {
  HEPUtilsAnalysis::scale(factor);
  cout << "SAVE_XSEC:" << xsec() << endl;
  auto save = [](double value, std::string name)
  {
  cout << "SAVE_START:" << name << endl;
  cout << value << endl;
  cout << "SAVE_END" << endl;
  };
  save(num1LSR, "num1LSR");
  save(num2LSR1, "num2LSR1");
  save(num2LSR2, "num2LSR2");
  }*/


void incrementCut(int cutIndex)
{
  cutflows[cutflowNames[cutIndex]]++;
}

void saveCutFlow()
{
  double scale_by = 1.0;
  cout << "SAVE_START:cuts" << endl;
  cout << "CUT;RAW;SCALED;%" << endl;
  double initialCut = cutflows[cutflowNames[Total_events]];
  double thisCut;
  for (std::string name : cutflowNames) {
    thisCut = cutflows[name];
    cout << name.c_str() << ";"
	 << thisCut << ";"
	 << thisCut * scale_by << ";"
	 << 100. * thisCut / initialCut
	 << endl;
  }
  cout << "SAVE_END" << endl;
}
};

DEFINE_ANALYSIS_FACTORY(ATLAS_7TeV_1OR2LEPStop_4_7invfb)
}
}

