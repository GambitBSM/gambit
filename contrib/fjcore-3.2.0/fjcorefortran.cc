//STARTHEADER
// $Id: fjcorefortran.cc 4066 2016-03-04 11:16:21Z soyez $
//
// Copyright (c) 2005-2011, Matteo Cacciari, Gavin P. Salam and Gregory Soyez
//
//----------------------------------------------------------------------
// This file is part of FastJet (fjcore).
//
//  FastJet is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  The algorithms that underlie FastJet have required considerable
//  development and are described in hep-ph/0512210. If you use
//  FastJet as part of work towards a scientific publication, please
//  include a citation to the FastJet paper.
//
//  FastJet is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with FastJet. If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------
//ENDHEADER

#include <iostream>
#include "fjcore.hh"

using namespace std;
using namespace fjcore;

FJCORE_BEGIN_NAMESPACE      // defined in fjcore.hh

/// a namespace for the fortran-wrapper which contains commonly-used
/// structures and means to transfer fortran <-> C++
namespace fwrapper {
  vector<PseudoJet> input_particles, jets;
  SharedPtr<JetDefinition::Plugin> plugin;
  JetDefinition jet_def;
  SharedPtr<ClusterSequence> cs;

  /// helper routine to transfer fortran input particles into 
  void transfer_input_particles(const double * p, const int & npart) {
    input_particles.resize(0);
    input_particles.reserve(npart);
    for (int i=0; i<npart; i++) {
      valarray<double> mom(4); // mom[0..3]
      for (int j=0;j<=3; j++) {
         mom[j] = *(p++);
      }
      PseudoJet psjet(mom);
      input_particles.push_back(psjet);    
    }
  }

  /// helper routine to help transfer jets -> f77jets[4*ijet+0..3]
  void transfer_jets(double * f77jets, int & njets) {
    njets = jets.size();
    for (int i=0; i<njets; i++) {
      for (int j=0;j<=3; j++) {
        *f77jets = jets[i][j];
        f77jets++;
      } 
    }
  }
  
  /// helper routine packaging the transfers, the clustering
  /// and the extraction of the jets
  void transfer_cluster_transfer(const double * p, const int & npart, 
                                 const JetDefinition & jet_def,
				 double * f77jets, int & njets) {

    // transfer p[4*ipart+0..3] -> input_particles[i]
    transfer_input_particles(p, npart);

    // cluster without areas
    cs.reset(new ClusterSequence(input_particles,jet_def));

    // extract jets (pt-ordered)
    jets = sorted_by_pt(cs->inclusive_jets());
    
    // transfer jets -> f77jets[4*ijet+0..3]
    transfer_jets(f77jets, njets);
 
  }

}
FJCORE_END_NAMESPACE

using namespace fjcore::fwrapper;


extern "C" {   


/// f77 interface to the pp generalised-kt (sequential recombination)
/// algorithms, as defined in arXiv.org:0802.1189, which includes
/// kt, Cambridge/Aachen and anti-kt as special cases.
//
// Corresponds to the following Fortran subroutine
// interface structure:
//
//   SUBROUTINE FJCOREPPGENKT(P,NPART,R,PALG,F77JETS,NJETS)
//   DOUBLE PRECISION P(4,*), R, PALG, F, F77JETS(4,*)
//   INTEGER          NPART, NJETS
// 
// where on input
//
//   P        the input particle 4-momenta
//   NPART    the number of input momenta
//   R        the radius parameter
//   PALG     the power for the generalised kt alg 
//            (1.0=kt, 0.0=C/A,  -1.0 = anti-kt)
//
// and on output 
//
//   F77JETS  the output jet momenta (whose second dim should be >= NPART)
//            sorted in order of decreasing p_t.
//   NJETS    the number of output jets 
//
// For the values of PALG that correspond to "standard" cases (1.0=kt,
// 0.0=C/A, -1.0 = anti-kt) this routine actually calls the direct
// implementation of those algorithms, whereas for other values of
// PALG it calls the generalised kt implementation.
//
// NOTE: if you are interfacing fjcore to Pythia 6, Pythia stores its
// momenta as a matrix of the form P(4000,5), whereas this fortran
// interface to fjcore expects them as P(4,NPART), i.e. you must take
// the transpose of the Pythia array and drop the fifth component
// (particle mass).
//
void fjcoreppgenkt_(const double * p, const int & npart,                   
                    const double & R, const double & palg,
                    double * f77jets, int & njets) {
    
    // prepare jet def
    if (palg == 1.0) {
      jet_def = JetDefinition(kt_algorithm, R);
    }  else if (palg == 0.0) {
      jet_def = JetDefinition(cambridge_algorithm, R);
    }  else if (palg == -1.0) {
      jet_def = JetDefinition(antikt_algorithm, R);
    } else {
      jet_def = JetDefinition(genkt_algorithm, R, palg);
    }

    // do everything
    transfer_cluster_transfer(p,npart,jet_def,f77jets,njets);
}

/// a routine that provides similar f77 functionality to fjcoreppgenkt_, 
/// but for the e+e- algorithms instead of the pp ones; note this 
/// only gives the "inclusive" algorithms. The algorithms are as
/// defined in the FastJet manual.
void fjcoreeegenkt_(const double * p, const int & npart,                   
                    const double & R, const double & palg,
                    double * f77jets, int & njets) {
    
  // prepare jet def
  jet_def = JetDefinition(ee_genkt_algorithm, R, palg);
  
  // do everything
  transfer_cluster_transfer(p,npart,jet_def,f77jets,njets);
}





/// f77 interface to provide access to the constituents of a jet found
/// in the jet clustering with one of the above routines.
///
/// Given the index ijet of a jet (in the range 1...njets) obtained in
/// the last call to jet clustering, fill the array
/// constituent_indices, with nconstituents entries, with the indices
/// of the constituents that belong to that jet (which will be in the
/// range 1...npart)
//
// Corresponds to the following Fortran subroutine
// interface structure:
//
//   SUBROUTINE FJCORECONSTITUENTS(IJET,CONSTITUENT_INDICES,NCONSTITUENTS)
//   INTEGER    IJET
//   INTEGER    CONSTITUENT_INDICES(*)
//   INTEGER    nconstituents
//
void fjcoreconstituents_(const int & ijet, 
   	                 int * constituent_indices, int & nconstituents) {
  assert(cs.get() != 0);
  assert(ijet > 0 && ijet <= jets.size());

  vector<PseudoJet> constituents = cs->constituents(jets[ijet-1]);

  nconstituents = constituents.size();
  for (unsigned i = 0; i < nconstituents; i++) {
    constituent_indices[i] = constituents[i].cluster_hist_index()+1;
  }
}


/// return the dmin corresponding to the recombination that went from
/// n+1 to n jets (sometimes known as d_{n n+1}).
//
// Corresponds to the following Fortran interface
// 
//   FUNCTION FJCOREDMERGE(N)
//   DOUBLE PRECISION FJCOREDMERGE
//   INTEGER N
//   
double fjcoredmerge_(const int & n) {
  assert(cs.get() != 0);
  return cs->exclusive_dmerge(n);
}


/// return the maximum of the dmin encountered during all recombinations 
/// up to the one that led to an n-jet final state; identical to
/// exclusive_dmerge, except in cases where the dmin do not increase
/// monotonically.
//
// Corresponds to the following Fortran interface
// 
//   FUNCTION FJCOREDMERGEMAX(N)
//   DOUBLE PRECISION FJCOREDMERGEMAX
//   INTEGER N
//   
double fjcoredmergemax_(const int & n) {
  assert(cs.get() != 0);
  return cs->exclusive_dmerge_max(n);
}


}
