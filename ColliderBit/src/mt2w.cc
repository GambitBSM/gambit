#include "gambit/ColliderBit/mt2w.h"

double calculateMT2wHepUtils(vector<HEPUtils::P4>& jets, vector<bool>& btag, HEPUtils::P4& lep, float met, float metphi){

    // I am asumming that jets is sorted by Pt
    assert ( jets.size() == btag.size() );
    // require at least 2 jets
    if ( jets.size()<2 ) return 99999.; 

    // First we count the number of b-tagged jets, and separate those non b-tagged
    std::vector<int> bjets;
    std::vector<int> non_bjets;
    for( unsigned int i = 0 ; i < jets.size() ; i++ ){
        if( btag.at(i) ) {
            bjets.push_back(i);
        } else {
            non_bjets.push_back(i);
        }
    }	

    int n_btag = (int) bjets.size();
    //	cout << "n_btag = " << n_btag << endl;

    // We do different things depending on the number of b-tagged jets
    // arXiv:1203.4813 recipe

    int nMax=-1;
    if(jets.size()<=3) nMax=non_bjets.size();
    else nMax=3;

    if (n_btag == 0){                  //  0 b-tags
        // If no b-jets select the minimum of the mt2w from all combinations with 
        // the three leading jets
        float min_mt2w = 9999;

        for (int i=0; i<nMax; i++)
            for (int j=0; j<nMax; j++){
                if (i == j) continue;
                float c_mt2w = mt2wWrapperHepUtils(lep, 
                        jets[non_bjets[i]],
                        jets[non_bjets[j]], met, metphi);
                if (c_mt2w < min_mt2w)
                    min_mt2w = c_mt2w;
            }
        return min_mt2w;

    } else if (n_btag == 1 ){          //  1 b-tags
        // if only one b-jet choose the three non-b leading jets and choose the smaller
        float min_mt2w = 9999;

        for (int i=0; i<nMax; i++){
            float c_mt2w = mt2wWrapperHepUtils(lep, jets[bjets[0]], jets[non_bjets[i]], met, metphi);
            if (c_mt2w < min_mt2w)
                min_mt2w = c_mt2w;
        }
        for (int i=0; i<nMax; i++){
            float c_mt2w = mt2wWrapperHepUtils(lep, jets[non_bjets[i]], jets[bjets[0]], met, metphi);
            if (c_mt2w < min_mt2w)
                min_mt2w = c_mt2w;
        }
        return min_mt2w;

    } else if (n_btag >= 2) {          // >=2 b-tags
        // if 3 or more b-jets the paper says ignore b-tag and do like 0-bjets 
        // but we are going to make the combinations with the b-jets
        float min_mt2w = 9999;
        for (int i=0; i<n_btag; i++)
            for (int j=0; j<n_btag; j++){
                if (i == j) continue;
                float c_mt2w = mt2wWrapperHepUtils(lep, 
                        jets[bjets[i]],
                        jets[bjets[j]], met, metphi);
                if (c_mt2w < min_mt2w)
                    min_mt2w = c_mt2w;
            }
        return min_mt2w;
    }

    return -1.;
}

// This funcion is a wrapper for mt2w_bisect etc that takes HEPUtils::P4 vectors instead of doubles
// Written by Martin White (martin.white@adelaide.edu.au), October 2015
double mt2wWrapperHepUtils(HEPUtils::P4& lep, HEPUtils::P4& jet_o, HEPUtils::P4& jet_b, float met, float metphi){

    // same for all MT2x variables
    float metx = met * cos( metphi );
    float mety = met * sin( metphi );

    double pl[4];     // Visible lepton
    double pb1[4];    // bottom on the same side as the visible lepton
    double pb2[4];    // other bottom, paired with the invisible W
    double pmiss[3];  // <unused>, pmx, pmy   missing pT

    pl[0]= lep.E(); pl[1]= lep.px(); pl[2]= lep.py(); pl[3]= lep.pz();
    pb1[1] = jet_o.px();  pb1[2] = jet_o.py();   pb1[3] = jet_o.pz();
    pb2[1] = jet_b.px();  pb2[2] = jet_b.py();   pb2[3] = jet_b.pz();
    pmiss[0] = 0.; pmiss[1] = metx; pmiss[2] = mety;

    pb1[0] = jet_o.E();
    pb2[0] = jet_b.E();

    mt2w_bisect::mt2w mt2w_event;
    mt2w_event.set_momenta(pl, pb1, pb2, pmiss);

    return mt2w_event.get_mt2w();
}

