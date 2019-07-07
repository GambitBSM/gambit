//==========================================================================
// This file has been automatically generated for Pythia 8
// MadGraph5_aMC@NLO v. 2.3.2.2, 2015-09-06
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#ifndef Pythia8_Sigma_GambitDemo_UFO_gg_uvuvx_H
#define Pythia8_Sigma_GambitDemo_UFO_gg_uvuvx_H

#include <complex> 

#include "Pythia8/SigmaProcess.h"
#include "Parameters_GambitDemo_UFO.h"

using namespace std; 

namespace Pythia8 
{
//==========================================================================
// A class for calculating the matrix elements for
// Process: g g > uv uv~ WEIGHTED=2
//--------------------------------------------------------------------------

class Sigma_GambitDemo_UFO_gg_uvuvx : public Sigma2Process 
{
  public:

    // Constructor.
    Sigma_GambitDemo_UFO_gg_uvuvx() {}

    // Initialize process.
    virtual void initProc(); 

    // Calculate flavour-independent parts of cross section.
    virtual void sigmaKin(); 

    // Evaluate sigmaHat(sHat).
    virtual double sigmaHat(); 

    // Select flavour, colour and anticolour.
    virtual void setIdColAcol(); 

    // Evaluate weight for decay angles.
    virtual double weightDecay(Event& process, int iResBeg, int iResEnd); 

    // Info on the subprocess.
    virtual string name() const {return "gg_uvuvx (GambitDemo_UFO)";}

    virtual int code() const {return 10000;}

    virtual string inFlux() const {return "gg";}
    int id3Mass() const {return 9000005;}
    int id4Mass() const {return 9000005;}

    // Tell Pythia that sigmaHat returns the ME^2
    virtual bool convertM2() const {return true;}

  private:

    // Private functions to calculate the matrix element for all subprocesses
    // Calculate wavefunctions
    void calculate_wavefunctions(const int perm[], const int hel[]); 
    static const int nwavefuncs = 7; 
    std::complex<double> w[nwavefuncs][18]; 
    static const int namplitudes = 3; 
    std::complex<double> amp[namplitudes]; 
    double matrix_gg_uvuvx(); 

    // Constants for array limits
    static const int nexternal = 4; 
    static const int nprocesses = 1; 

    // Store the matrix element value from sigmaKin
    double matrix_element[nprocesses]; 

    // Color flows, used when selecting color
    double * jamp2[nprocesses]; 

    // Pointer to the model parameters
    Parameters_GambitDemo_UFO * pars; 

}; 

}  // end namespace Pythia8

#endif  // Pythia8_Sigma_GambitDemo_UFO_gg_uvuvx_H

