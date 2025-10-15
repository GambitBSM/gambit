/// ATLAS 3 b jets + MET, 139invfb
///
/// Based on ATLAS EXOT 2018 58 (2210.15413)
///
/// \author Tomasz Procter
/// \date 2025 October
///
/// Note 1: This analysis requires ONNXRunTime for the MCBOT NN tagger
///
///
/// ***************************************


#include "gambit/cmake/cmake_variables.hpp"
#ifndef EXCLUDE_ONNXRUNTIME


#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/onnx_rt_wrapper.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"

// Let's be flexible about fjcore/fastjet
// (define structure copied from heputils/FastJet.h)
#ifndef FJCORE
#ifndef FJNS
#define FJNS fastjet
#endif
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#else 
#include "fjcore.hh"
#ifndef FJNS
#define FJNS fjcore
#endif
#endif

using namespace std;

namespace Gambit {
namespace ColliderBit {

    // First: define a helper class & types for dealing with MCBOT 
    // Largely copied from (my) rivet implementation
    namespace MCBOT {

        enum class MCBOTtag {
            BKG = 0,
            TOP = 1,
            HIGGS = 2,
            VECTOR = 3,
        };

        struct MCBOT {
            MCBOT(const std::string& nnfile="ATLAS_2022_I2172216.onnx") : _nnfile{nnfile} {
            // n.b. ONNX file converted from lwtnn with petrifyML (cite?)
            _nn = make_unique<onnx_rt_wrapper>(nnfile);
            }


            // Tag a RC jet (and its vector of consitutents). Note that the cuts required to
            // tag a jet are DIFFERENT in 2l/3l channels (control channel with twoLep=True/False)
            MCBOTtag tagJet(const Jet & j, const vector<const Jet*> & constitJets,
                            const vector<bool> & constitBtags, const bool twoLep=true ){
            vector<double> onnxout;
            _nn->compute<double, double>(getMCBOTinput(j, constitJets, constitBtags), onnxout);
            // Seperate scores to improve legibility:
            const double dnnOutput_V = onnxout[2];
            const double dnnOutput_H = onnxout[1];
            const double dnnOutput_top = onnxout[3];
            
            // The business of going from scores to tags is unfortunately long winded.
            const bool tagV = dnnOutput_V > (twoLep ? 0.30 : 0.26);
            const bool tagH = dnnOutput_H > (twoLep ? 0.35 : 0.31);
            const bool tagtop = dnnOutput_top > (twoLep ? 0.30 : 0.21);

            if (!tagV && !tagH && !tagtop) return MCBOTtag::BKG;
            if (tagV && !tagH && !tagtop) return MCBOTtag::VECTOR;
            if (!tagV && !tagH && tagtop) return MCBOTtag::TOP;
            // Note that triple tag = H tag
            // N.B.: this is disputed by the int note, but I take Olaf's word for it.
            if ((!tagV && tagH && !tagtop) || (tagV && tagH && tagtop)) return MCBOTtag::HIGGS;

            // Oh dear, we're now in the ugly case of tiebreaks.
            // It's not clear to me what happened if e.g. V=0.34, H=0.31,t=0.31, light=0.04 --
            // Because V is the highest scoring but hasn't crossed the tag threshold.
            // Not discussed in paper/int note. Hopefully a minor effect.
            if ( (dnnOutput_V > dnnOutput_H ) &&
                    (dnnOutput_V > dnnOutput_top ) ) return MCBOTtag::VECTOR;

            if ( (dnnOutput_H > dnnOutput_V ) &&
                    (dnnOutput_H > dnnOutput_top ) ) return MCBOTtag::HIGGS;

            if ( (dnnOutput_top > dnnOutput_H ) &&
                    (dnnOutput_top > dnnOutput_V ) ) return MCBOTtag::TOP;

            // Shouldn't ever be triggered (even in cases of triple ==), just in case:
            std::cerr << "MCBOT tagger unable to assign a tag (debugging suggested)" << std::endl;
            // TODO: errors in colliderbit?
            //throw Error("MCBOT tagger unable to assign a tag (debugging suggested)");
            }

            inline static vector<double> getMCBOTinput(const Jet & j,
                                                        const vector<const Jet*> & constitJets,
                                                    const vector<bool> & constitBtags) {
            // n.b. This ordering is a bit counter-intuitive, but it matches the order in
            // the original lwtnn json 
            return vector<double>{
                    // subjet 3 variables
                    constitJets.size() > 2 ? constitJets[2]->pT()/MeV : 0.,
                    constitJets.size() > 2 ? constitJets[2]->eta() : j.eta(),
                    // TODO (IMPORTANT): check gambit phi convention
                    constitJets.size() > 2 ? constitJets[2]->phi() : j.phi(),
                    constitJets.size() > 2 ? constitJets[2]->E()/MeV : 0.,
                    constitJets.size() > 2 ? (double)constitBtags[2] : -1.,
                    // subjet 2 variables
                    constitJets.size() > 1 ? constitJets[1]->pT()/MeV : 0.,
                    constitJets.size() > 1 ? constitJets[1]->eta() : j.eta(),
                    constitJets.size() > 1 ? constitJets[1]->phi() : j.phi(),
                    constitJets.size() > 1 ? constitJets[1]->E()/MeV : 0.,
                    constitJets.size() > 1 ? (double)constitBtags[1] : -1.,
                    // lead subjet variables
                    constitJets[0]->pT()/MeV,
                    constitJets[0]->eta(),
                    constitJets[0]->phi(),
                    constitJets[0]->E()/MeV,
                    (double)constitBtags[0],
                    // Whole-jet variables
                    j.mass()/MeV,
                    min((double)constitJets.size(), 3.),
                    j.pT()/MeV,
                    };      
            }

            vector<MCBOTtag> tagJets(const vector<Jet> & js, const vector<vector<const Jet*>> constitJetss,
                                    const vector<vector<bool>> constitBtags, const bool twoLep=true){
            // Assume js and constitJetss are same length, if not its someone elses fault.
            const size_t nTags = js.size();
            vector<MCBOTtag> rtn;
            rtn.reserve(nTags);
            for (size_t i{0}; i < nTags; ++i){
                rtn.push_back(tagJet(js[i], constitJetss[i], constitBtags[i], twoLep));
            }
            return rtn;
            }

        private:
            std::string _nnfile;
            unique_ptr<onnx_rt_wrapper> _nn;
        };
    }

    // We have a lot of distributions/bar-charts in this analysis, which are all independent signal regions.
    // I don't want to have to write DEFINE_SIGNAL_REGION a million times, so here's a class that uses the existing machinery
    // Maybe we should consider something like this more centrally? Expecially if we are including more and more EXOT analyses,
    // where this is more common.
    // As far as I can see, whether the counters are stores in _counters vs in a different counter makes no difference?
    // No YODA style template cleverness here.
    class SIGNAL_DISTRIBUTION{
        vector<double> _edges;
        std::map<string, EventCounter> _counters;
        std::string _name;

    public:
        SIGNAL_DISTRIBUTION(const string & name, vector<double> binedges) : _name(name), _edges(binedges) {
            for (size_t i = 0; i < binedges.size()-1; ++i){
                _counters[_name+"_"s+to_string(i)] = EventCounter(_name+to_string(i));
            }
        }

        void fill(const double fillval, Event* event, bool includeOverFlow=true, bool includeUnderFlow=false) {
            if (fillval < xmin()){
                if (includeUnderFlow) {_counters[_name+"_0"].add_event(event); return;} else return;
            }
            if (fillval > xmax()){
                if (includeOverFlow) {_counters[_name+"_"s+to_string(_edges.size())].add_event(event); return;} else return;
            }
             
            _counters[_name+"_"+to_string(binIndex(fillval, _edges, false))].add_event(event);
        }

        double xmax() const {
            return _edges[_edges.size()-1];
        }
        
        double xmin() const {
            return _edges[0];
        }

        void reset() {
            for (auto & c : _counters){
                c.second.reset();
            }
        }
    };

    class Analysis_ATLAS_13TeV_EXOT_2018_58 : public Analysis {

        protected:
        // TODO SR MAP

        private:
        unique_ptr<MCBOT::MCBOT> _mcbot;

        public:
        // Required detector sim
        static constexpr const char* detector = "ATLAS";


        // Analysis helper functions
        // @{
        static double JVT_eff(const Jet &j){
            if (j.abseta() > 2.4) return 1.;
            if (j.pT() <= 20 || j.pT() >= 60) return 1.;

            const static vector<double> binedges_pt = {20,25,30,35,40,45,50,55,60};
            const static vector<double> binvals = {0.86, 0.9, 0.92, 0.93, 0.94, 0.95, 0.95, 0.96};

            const size_t bini = binIndex(j.pT(), binedges_pt);
            return binvals[bini];
        }

        static double JVT_eff(const Jet* j){
            return JVT_eff(*j);
        }

        static void apply_JVT(const vector<const Jet*> &jsIn, vector<const Jet*> &jsOut){
            for (const Jet* j : jsIn){
                if (random_bool(JVT_eff(j))){
                    jsOut.push_back(j);
                }
            }
        }
        // @}


        Analysis_ATLAS_13TeV_EXOT_2018_58() {
            set_analysis_name("ATLAS_13TeV_EXOT_2018_58");
            set_luminosity(139.);

            // Load the NN
            //TODO: We really want to be as sure as possible this is called the minimal number of times.
            _mcbot = make_unique<MCBOT::MCBOT>(GAMBIT_DIR"/ColliderBit/data/analyses_ML/Analysis_ATLAS_13TeV_EXOT_2018_58.onnx");
        }

        void run(const HEPUtils::Event* event) {

            // Get objects, do overlaps, etc:
            // TODO: EDIT!!!!!!!!!!!!!!!!!!!!!

            // Get the missing energy in the event
            double met = event->met();
            HEPUtils::P4 metVec = event->missingmom();

            BASELINE_PARTICLES(event->electrons(), baselineEl1, 25, 0, DBL_MAX, 1.37);
            BASELINE_PARTICLES(event->electrons(), baselineEl2, 25, 1.52, DBL_MAX, 2.47);
            BASELINE_PARTICLES(event->muons(), muons, 25, 0, DBL_MAX, 2.5);
            
            BASELINE_PARTICLE_COMBINATION(electrons, baselineEl1, baselineEl2)
            applyEfficiency(electrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Tight")); 
            applyEfficiency(muons, ATLAS::eff1DMu.at("MUON_2018_03_ID_Medium")); 
            
            BASELINE_JETS(event->jets("antikt_R04"), basectrJets, 25, 0, DBL_MAX, 2.5);
            BASELINE_JETS(event->jets("antikt_R04"), basefwdJets, 35., 2.5, DBL_MAX, 4.5);

            BASELINE_JET_COMBINATION(candJets, basectrJets, basefwdJets);
            // TODO -- apply JVT if we want to see if that makes any difference.

            JetPtrs bJets, nonbJets;
        
            // Find b-jets
            const double cmisstag = 1/6.; const double misstag = 1./134.;
            // pt-dependent b-tagging -> turns out to be kind of important due to
            // large number of high-pt jets.
            const static vector<double>binedges_pt = {0.00, 30.0, 40.00, 50.00, 60.0, 75.00, 90.0, 105., 150., 200., 500 };
            const static vector<double> eff_pt =     {0.63, 0.705, 0.74, 0.76, 0.775, 0.785, 0.795, 0.80, 0.79, 0.75, 0.675};
            // N.b!!! The overflow value is extrapolated (from ATL-PHYS-PUB-2016-012)
            // You could quite reasonably pick a very wide range of values, and the
            // difference on the final result is order 5-10%.
            for (const HEPUtils::Jet* jet : candJets) {
                if (jet->abseta() >= 2.5) continue;
                // Tag
                if( jet->btag() && random_bool(eff_pt[binIndex(jet->pT(), binedges_pt, true)]) ) bJets.push_back(jet);
                // Misstag c-jet
                else if( jet->ctag() && random_bool(cmisstag) ) bJets.push_back(jet);
                // Misstag light jet
                else if( random_bool(misstag) ) bJets.push_back(jet);
                // Non b-jet
                else nonbJets.push_back(jet);
            }
            // Overlap removal
            // 1. Any muons leaving energy in calo and sharing track with electron
            // Not really possible in MC but lets use dR < 0.01
            removeOverlap(muons, electrons, 0.01);
            // 2. Electrons within 0.2 of muons
            removeOverlap(electrons, muons, 0.2);
            // 3. Jets within 0.2 of an electron
            removeOverlap(candJets, electrons, 0.2);
            removeOverlap(bJets, electrons, 0.2);
            removeOverlap(nonbJets, electrons, 0.2);
            // 4. Electeons within 0.4 of remaining jets
            removeOverlap(electrons, candJets, 0.4);
            // 5. TODO: Non b-jets, track req. within 0.2 of a mu
            // TODO
            // 6. Muons within deltaR < min(0,4m 0.04/10mu.pt) iof remaining jets
            auto mudRmax = [](const double mupt){return std::min(0.4, 0.04 + 10./mupt);};
            removeOverlap(muons, candJets, mudRmax);


            // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

            // Start analysing the event:
            // We need an OSSF pair -- veto quickly if nothing
            if (electrons.size() < 2 && muons.size() < 2) return;

            /// PRESELECTION:
            // Presel # 1: >=1 OSSF pair
            // Get OSSF pairs
            vector<pair<Particle, Particle>> OSSF_PAIRS;
            for (size_t i = 0; i < electrons.size(); ++i){
                for (size_t j = 0; j < i; ++j){
                    if (electrons[i]->pid() * electrons[j]->pid() < 0){
                        OSSF_PAIRS.push_back({electrons[i], electrons[j]});
                    }
                }
            }
            for (size_t i = 0; i < muons.size(); ++i){
                for (size_t j = 0; j < i; ++j){
                if (muons[i]->pid() * muons[j]->pid() < 0){
                    OSSF_PAIRS.push_back({muons[i], muons[j]});
                }
                }
            }
            if (OSSF_PAIRS.size() < 1) return;

            //PRESEL #2: two small jets in central region:
            if (count_if(candJets.begin(), candJets.end(),
                [](const Jet* j){return (j->abseta() < 2.5 );}) < 2){ return; }
            
            // PRESEL #3: Z-boson candidate |M(ll)-MZ| < 10*GeV
            // Get the Z bsoson candidate - i.e. the OSSF pair with lowest dM
            double best_deltaM = DBL_MAX;
            P4 ZCandidate;
            for (const pair<Particle, Particle>& ossf_pair : OSSF_PAIRS){
                const P4 this_candidate(ossf_pair.first.mom() + ossf_pair.second.mom());
                if (abs(this_candidate.m()-91.2*GeV) < best_deltaM){
                    best_deltaM = abs(this_candidate.m()-91.2*GeV);
                    ZCandidate = this_candidate;
                }
            }
            if (best_deltaM >= 10*GeV) return;

            /// PRESEL DONE
            ///////////////////////////////////

            // Time for reclustering.
            vector<shared_ptr<Jet>> RCjets = get_jets(candJets, 1.0, 150*GeV);

            // Trimming, and matching Jets to constituents
            // This is a bit ugly, but no way around it
            vector<Jet> TrimmedRCjets;
            vector<vector<const Jet*>> TrimmedRCjetConstituents;
            vector<vector<bool>> TrimmedRCjetConstituentBtags;
            trim_and_match(RCjets, candJets, bJets,
                            TrimmedRCjets, TrimmedRCjetConstituents, TrimmedRCjetConstituentBtags);


            // Channel decision
            // 2 LEPTON CHANNEL:
            if (electrons.size() + muons.size() == 2){
                const double HT = scalarSumPt(candJets);

                // Additional 2L presel.
                // Z Candidate pT > 300*Gev:
                if (ZCandidate.pT() <= 300*GeV ) return;
                // HTjet + ETMiss > 920*GeV
                if (HT + met <= 920*GeV ) return;
                // At least one b jet
                if (bJets.size() == 0) return;

                // Control regions
                if (HT + met <= 1380*GeV ){
                    if (bJets.size() == 1){
                        // 2l_1b_CR
                    }
                    else {
                        // 2l_2b_CR
                    }
                    // And we're all done
                    return;
                }
                // If we're in the SR, need to use MCBOT.
                const vector<MCBOT::MCBOTtag> tags = _mcbot->tagJets(TrimmedRCjets, TrimmedRCjetConstituents, TrimmedRCjetConstituentBtags, true);
                const string category = get_2l_MCBOT_category(tags, bJets.size());
                // TODO FILLING
            }
            // 3 LEPTON CHANNEL:
            else {
                const double HTjetlep = scalarSumPt(candJets) + scalarSumPt(electrons) + scalarSumPt(muons);

                if (ZCandidate.pT() < 200*GeV) return;

                if (HTjetlep < 300*GeV) return;

                if (bJets.size() == 0){
                    // We're in the VV CR
                    // TODO FILLING
                    return;
                }
                // Signal region
                // Need to run MCBOT
                const vector<MCBOT::MCBOTtag> tags = _mcbot->tagJets(TrimmedRCjets, TrimmedRCjetConstituents, TrimmedRCjetConstituentBtags, true);
                const string category = get_3l_MCBOT_category(tags);
                // TODO FILLING

            }

        }


        //Get the MCBot category (defined in Table 2) for 2l channel
        static string get_2l_MCBOT_category(const vector<MCBOT::MCBOTtag>& tags, const size_t nbtags) {
            size_t nVtags = 0, nHtags = 0, ntoptags = 0;
            for(const MCBOT::MCBOTtag t : tags){
                if (t == MCBOT::MCBOTtag::VECTOR)
                ++nVtags;
                else if (t == MCBOT::MCBOTtag::HIGGS){
                ++nHtags;
                }
                else if (t == MCBOT::MCBOTtag::TOP){
                ++ntoptags;
                }
            }
            if (nVtags == 0 && nHtags == 0 && ntoptags == 0){
                return "No_tag";
            }
            else if (nVtags == 1 && nHtags == 0 && ntoptags == 0){
                return "V_tag";
            }
            else if (nVtags == 0 && nHtags == 1 && ntoptags == 0){
                return "H_tag";
            }
            else if (nVtags == 0 && nHtags == 0 && ntoptags == 1){
                return "top_tag";
            }
            else if ((nVtags == 2 && nHtags == 0 && ntoptags == 0) ||
                (nVtags == 0 && nHtags == 2 && ntoptags == 0)
                || (nVtags == 1 && nHtags == 0 && ntoptags == 1 && nbtags == 1)
                || (nVtags == 1 && nHtags == 1 && ntoptags == 0 && nbtags >= 2)
                || (nVtags == 0 && nHtags == 0 && ntoptags == 2 && nbtags >= 2)){
                return "Double_tag_1";
            }
            else if ((nVtags == 0 && nHtags == 1 && ntoptags == 1)
                || (nVtags == 0 && nHtags == 0 && ntoptags == 2 && nbtags == 1)){
                return "Double_tag_2";
            }
            else if ((nVtags == 1 && nHtags == 1 && ntoptags == 0 && nbtags == 1)
                || (nVtags == 1 && nHtags == 0 && ntoptags == 1 && nbtags >= 2)
                || (nVtags + nHtags + ntoptags > 2)){
                return "OF";
            }
            else {
                // TODO: Does gambit have its own exception classes?
                //throw Error("FAILED TO CATEGORISE JET - DEBUGGING REQUIRED");
                return "";
            }
        }

         //Get the MCBot category (defined in Table 2) for 3l channel
        static string get_3l_MCBOT_category(vector<MCBOT::MCBOTtag> tags) {
            size_t nVtags = 0, nHtags = 0, ntoptags = 0;
            for(const MCBOT::MCBOTtag t : tags){
                if (t == MCBOT::MCBOTtag::VECTOR)
                ++nVtags;
                else if (t == MCBOT::MCBOTtag::HIGGS){
                ++nHtags;
                }
                else if (t == MCBOT::MCBOTtag::TOP){
                ++ntoptags;
                }
            }
            if (nVtags == 0 && nHtags == 0 && ntoptags == 0){
                return "No_tag";
            }
            else if (nVtags >= 1 && nHtags == 0 && ntoptags == 0){
                return "V_tag";
            }
            else if (nVtags == 0 && nHtags >= 1 && ntoptags == 0){
                return "H_tag";
            }
            else if (nVtags == 0 && nHtags == 0 && ntoptags >= 1){
                return "top_tag";
            }
            else 
                return "OF";
        }

        static inline bool isCloseToBJet(const Jet* jtest, const vector<const Jet*> & bJets, double dR=0.01){
            for (const Jet* j : bJets){
                if (j->mom().deltaR_eta(jtest->mom()) < dR){
                    return true;
                }
            }
            return false;
        }

        // Given reclustered jets, remove subjets < 5% of total pT, and match the remaining subjets to existing btagged
        // objects
        // This is ugly, I fdon't see a way around.
        static void trim_and_match(const vector<shared_ptr<Jet>> & RCJetsIn, const vector<const Jet*> & smallJetsIn, vector<const Jet*> bJetsIn,
                            vector<Jet> & RCJetsOut, vector<vector<const Jet*>> & constituentsOut, vector<vector<bool>> & consitituentBtagsOut,
                            const double ptfrac = 0.05, const double ptmin = 150*GeV, const double etamax = 4.5){
            vector<Jet> RCJetsOutTemp; vector<vector<const Jet*>> constituentsOutTemp; vector<vector<bool>> bJetsOutTemp;
            for (const shared_ptr<Jet> j : RCJetsIn){
                const double pTmin = ptfrac*j->pT();
                bool jetfound; //technically, need a guard in case the RC jet is made of loads on tiny tiny jets and disappears
                FJNS::PseudoJet trimmed;
                vector<const Jet*> constituentList;
                vector<bool> tagList;
                for (const FJNS::PseudoJet & jin : j->pseudojet().constituents() ){
                    jetfound=true;
                    if (jin.pt() < pTmin) continue;
                    trimmed += jin;
                    auto counterpart = std::find_if(smallJetsIn.begin(), smallJetsIn.end(),
                                                [&jin](const Jet* sj){return HEPUtils::deltaR_eta(*sj, HEPUtils::Jet(jin)) < 0.04;});
                                                // TODO: it really should be possible to call DeltaR(jet, pseudojet)
                    // There WILL be a counterpart for every jet.
                    constituentList.push_back(*counterpart);
                    if (isCloseToBJet(*counterpart, bJetsIn)){
                        tagList.push_back(true);
                    }
                    else tagList.push_back(false);
                }
                if (jetfound){
                    if (trimmed.pt() > ptmin && abs(trimmed.eta()) < etamax) {
                        RCJetsOutTemp.push_back(Jet(trimmed));
                        // n.b. this sorting is essential!
                        sortByPt(constituentList);
                        constituentsOutTemp.push_back(constituentList);
                        bJetsOutTemp.push_back(tagList);
                    }
                }
            }
            // If there's a cleaner way to re-organise...
            // Build a permutation vector to get the order we want.

            // It is very annoying that there is no empty Jet constructor
            RCJetsOut = vector<Jet>{};
            for (size_t i = 0; i < RCJetsOutTemp.size(); ++i) {RCJetsOut.push_back(Jet(0,0,0,0));};
            constituentsOut = vector<vector<const Jet*>>(constituentsOutTemp.size());
            consitituentBtagsOut = vector<vector<bool>>(constituentsOutTemp.size());
            vector<size_t> permutation(RCJetsOutTemp.size());
            std::iota(permutation.begin(), permutation.end(), 0);
            sort(permutation.begin(), permutation.end(),
                [&RCJetsOutTemp](size_t i, size_t j){
                return RCJetsOutTemp[i].pT() > RCJetsOutTemp[j].pT();
            });
            std::transform(permutation.begin(), permutation.end(), 
                RCJetsOut.begin(), 
                [&RCJetsOutTemp](size_t i){return RCJetsOutTemp[i];
                });
            std::transform(permutation.begin(), permutation.end(), 
                constituentsOut.begin(), [&constituentsOutTemp](size_t i){return constituentsOutTemp[i];});
            std::transform(permutation.begin(), permutation.end(), consitituentBtagsOut.begin(),
                [&bJetsOutTemp](size_t i){return bJetsOutTemp[i];});
        }

        

    };
}
}




#endif