#include "gambit/LowEBit/QCD_gamma.h"

QCD_gamma::QCD_gamma(unsigned int cnf, unsigned int cloop)
{
    //ctor
    nf = cnf;
    loop = cloop;
}

QCD_gamma::~QCD_gamma()
{
    //dtor
}

double QCD_gamma::chet(){
    if(loop == 1){
        return 1.0;
    }
}
