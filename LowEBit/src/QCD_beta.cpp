#include "gambit/LowEBit/QCD_beta.h"

QCD_beta::QCD_beta(unsigned int cnf, unsigned int cloop)
{
    //ctor
    nf = cnf;
    loop = cloop;
}

QCD_beta::~QCD_beta()
{
    //dtor
}

double QCD_beta::chet(){
    if(loop==1){
        return 1/4.*(11-2/3.*nf);
    }
}

double QCD_beta::trad(){
    if(loop==1){
        return (11-2/3.*nf);
    }
}
