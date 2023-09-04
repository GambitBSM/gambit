//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of container classes
///  for the DarkSUSY backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///          (christoph.weniger@gmail.com)
///  \date 2012 Mar
///
///  \author Torsten Bringmann
///          (torsten.bringmann@fys.uio.no)
///  \date 2013 Jun, 2014 Mar, 2015 Apr, 2018 Sep, 2019 May
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2013 Oct
///
///  \author Jonathan Cornell
///          (jcornell@ucsc.edu)
///  \date 2014 Oct
///
///  \author Joakim Edsjo
///          (edsjo@fysik.su.se)
///  \date 2015 May, 2018 Sep
///
///  *********************************************

#ifndef __DarkSUSY_types_hpp__
#define __DarkSUSY_types_hpp__

#include "gambit/Utils/util_types.hpp"

namespace Gambit
{
 
  struct DS_IBINTVARS
  {
      Fdouble ibcom_x, ibcom_z, ibcom_mx, ibcom_mp1, ibcom_mp2;
      Finteger intch, intyield;
  };

  // this one only exists in DS 5
  struct DS5_MSPCTM
  {
      Farray<Fdouble,0,50> mass, runnmann;
      Fdouble mu2gev,md2gev,ms2gev,mcmc,mbmb,mtmt;
  };

  // this one only exists in DS 6
  struct DS_SMQUARKMASSES
  {
      Fdouble mu2gev,md2gev,ms2gev,mcmc,mbmb,mtmt;
      Fstring<5> roption;
  };
	
  // this one only exists in DS 6
  struct DS_PMASSES
  {
      Farray<Fdouble,0,255> mass;
  };

  // this one only exists in DS 5
  struct DS5_WIDTHS
  {
      Farray<Fdouble,0,50> width;
  };

  // this one only exists in DS 6
  struct DS_PWIDTHS
  {
      Farray<Fdouble,0,255> width;
  };

  // this one only exists in DS 6 (returned by dsddgpgn)
  struct DS_gg
  {
      Farray< Fdouble_complex,1,27,1,2 > gg;
  };

  struct DS_INTDOF
  {
      Farray<Finteger,0,50> kdof;
  };

  // this one only exists in DS 5
  struct DS5_PACODES
  {
      Farray<Finteger,1,2> kse,ksmu,kstau,ksu,ksd,ksc,kss,kst,ksb;
      Farray<Finteger,1,4> kn;
      Farray<Finteger,1,2> kcha;
      Farray<Finteger,1,3> knu,kl,kqu,kqd;
      Farray<Finteger,1,6> ksnu,ksl,ksqu,ksqd;
      // character*8 pname(0:numpartspecies)
  };

  // this one only exists in DS 6+
  struct DS_PACODES_MSSM
  {
      Farray<Finteger,1,3> knu,kl,kqu,kqd;
      Farray<Finteger,1,6> ksnu,ksl,ksqu,ksqd;
      Farray<Finteger,1,4> kn;
      Farray<Finteger,1,2> kcha;
      Farray<Finteger,1,3,1,1> ksnu_flav;
      Farray<Finteger,1,3,1,2> ksl_flav,ksqu_flav,ksqd_flav;
  };

  // this one only exists in DS 6.1
  struct DS_PACODES_MSSM61
  {
      Farray<Finteger,1,3> knu,kl,kqu,kqd;
      Farray<Finteger,1,2> kse,ksmu,kstau,ksu,ksd,ksc,kss,kst,ksb;
      Farray<Finteger,1,4> kn;
      Farray<Finteger,1,2> kcha;
      Farray<Finteger,1,6> ksnu,ksl,ksqu,ksqd;
  };


  struct DS_MSSMIUSEFUL
  {
      Finteger lsp;
      Finteger kln;
  };

  struct DS_VRTXS
  {
      Farray< Fdouble_complex,1,50,1,50,1,50 > gl;
      Farray< Fdouble_complex,1,50,1,50,1,50 > gr;
  };

  // this one only exists in DS 5
  struct DS5_SMRUSEFUL
  {
      Fdouble s2thw;
      Fdouble sinthw;
      Fdouble costhw;
      Fdouble delrho;
      Fdouble alph3mz;
      Fdouble gfermi;
      Fdouble s2wmz;
      Fdouble swmz;
      Fdouble cwmz;
  };

  // this one only exists in DS 6
  struct DS_SMCOUPLING
  {
      Fdouble alph3mz;
      Fdouble gfermi;
      Fdouble alphem;
      Fdouble s2thw;
      Fdouble sinthw;
      Fdouble costhw;
      Fdouble s2wmz;
      Fdouble swmz;
      Fdouble cwmz;
      Fdouble g2weak;
      Fdouble g2wmz;
      Fdouble g3stro;
      Fdouble gyweak;
      Fdouble gywmz;
  };

  //this one existet only in DS 6.1
  struct DS_SMCOUPLING61
  {
      Fdouble alph3mz;
      Fdouble gfermi;
      Fdouble alphem;
      Fdouble s2thw;
      Fdouble sinthw;
      Fdouble costhw;
      Fdouble s2wmz;
      Fdouble swmz;
      Fdouble cwmz;
  };

  // this one only exists in DS 5
  struct DS5_SMCUSEFUL
  {
      Fstring<5> roption;
  };
  
  // this one only exists in DS 5
  struct DS5_COUPLINGCONSTANTS
  {
      Fdouble g2weak;
      Fdouble gyweak;
      Fdouble g3stro;
      Fdouble alphem;
      Fdouble alph3;
      Farray< Fdouble,1,12 > yukawa;
      Fdouble g2wmz;
      Fdouble gywmz;
  };

  // this one only exists in DS 6.1
  struct DS_COUPLINGCONSTANTS
  {
      Fdouble alph3;
      Farray< Fdouble,1,12 > yukawa;
  };
	
  // this one only exists in DS 6
  struct DS_COUPLINGCONSTANTS61
  {
      Fdouble g2weak;
      Fdouble gyweak;
      Fdouble g3stro;
      Fdouble alph3;
      Farray< Fdouble,1,12 > yukawa;
      Fdouble g2wmz;
      Fdouble gywmz;
  };
  
  struct DS5_SCKM
  {
      Fdouble ckms12;
      Fdouble ckms23;
      Fdouble ckms13;
      Fdouble ckmdelta;
  };

  struct DS_SCKM
  {
      Farray< Fdouble_complex,1,3,1,3 > ckm;
      Fdouble ckms12;
      Fdouble ckms23;
      Fdouble ckms13;
      Fdouble ckmdelta;
  };

  struct DS_MIXING
  {
      Farray< Fdouble_complex,1,3,1,3 > ckm;
  };

  struct DS_MSSMTYPE
  {
      Finteger modeltype;
  };

  struct DS_MSSMPAR
  {
      Fdouble tanbe;
      Fdouble mu;
      Fdouble m2;
      Fdouble m1;
      Fdouble m3;
      Fdouble ma;
      Farray< Fdouble,1,3 > mass2u;
      Farray< Fdouble,1,3 > mass2q;
      Farray< Fdouble,1,3 > mass2d;
      Farray< Fdouble,1,3 > mass2l;
      Farray< Fdouble,1,3 > mass2e;
      Farray< Fdouble,1,3 > asoftu;
      Farray< Fdouble,1,3 > asoftd;
      Farray< Fdouble,1,3 > asofte;
  };
  
  struct DS_MSSMSWITCH
  {
      Fdouble msquarks;
      Fdouble msleptons;
      Finteger higloop;
      Finteger neuloop;
      Finteger bsgqcd;
      Finteger higwid;
  };
	
  struct DS_SFERMIONMASS
  {
      Farray< Fdouble,1,3 > massup1;
      Farray< Fdouble,1,3 > massup2;
      Farray< Fdouble,1,3 > thetamixu;
      Farray< Fdouble,1,3 > massdn1;
      Farray< Fdouble,1,3 > massdn2;
      Farray< Fdouble,1,3 > thetamixd;
      Farray< Fdouble,1,3 > masssn;
      Farray< Fdouble,1,3 > masssl1;
      Farray< Fdouble,1,3 > masssl2;
      Farray< Fdouble,1,3 > thetamixsl;
  };

  struct DS_MSSMWIDTHS
  {
      Farray< Fdouble,1,32,1,4 > hdwidth;
  };

  struct DS_MSSMMIXING
  {
      Farray< Fdouble_complex,1,4,1,4 > neunmx;
      Farray< Fdouble_complex,1,2,1,2 > chaumx;
      Farray< Fdouble_complex,1,2,1,2 > chavmx;
      Farray< Fdouble_complex,1,3,1,3 > slulmx;
      Farray< Fdouble_complex,1,6,1,3 > sldlmx;
      Farray< Fdouble_complex,1,6,1,3 > sldrmx;
      Farray< Fdouble_complex,1,6,1,3 > squlmx;
      Farray< Fdouble_complex,1,6,1,3 > squrmx;
      Farray< Fdouble_complex,1,6,1,3 > sqdlmx;
      Farray< Fdouble_complex,1,6,1,3 > sqdrmx;
      Fdouble alpha;
      Fdouble mix_stop;
      Fdouble mix_sbot;
      Fdouble mix_stau;
  };

  // only in DarkSUSY 5
  struct DS5_RDMGEV
  {
      Farray<Fdouble,1,1000> mco, mdof, rgev, rwid;
      Finteger nco, nres;
      Farray<Finteger,1,1000> kcoann;
  };

  // only in DarkSUSY_MSSM 6
  struct DS_DSANCOANN
  {
      Farray<Fdouble,1,50> mco, mdof;
      Farray<Finteger,1,50> kco;
      Finteger nco;
  };

  struct DS_RDPTH
  {
      Farray<Fdouble,0,1001> pth;
      Farray<Finteger,0,1001> incth;
      Finteger nth;
  };

  struct DS_RDSWITCH
  {
      Finteger thavint,rdprt;
  };

  struct DS_RDLUN
  {
      Finteger rdlulog,rdluerr;
  };

  struct DS_RDPADD
  {
      Fdouble pdivr,dpres;
      Finteger nlow,nhigh,npres,nthup,cthtest,spltest;
  };

  struct DS_RDDOF
  {
      Farray<Fdouble,1,300> tgev,fh,fg,fe,fp;
      Finteger nf,khi,klo,dofcode;
  };

  struct DS_RDERRORS
  {
      Finteger rderr,rdwar,rdinit;
  };

  struct DS_RDPARS_OLD
  {
      Fdouble cosmin,waccd,dpminr,dpthr,wdiffr,wdifft;
      Fdouble hstep,hmin,compeps,xinit,xfinal,umax,cfr,pmax;
  };

  struct DS_RDPARS
  {
      Fdouble cosmin,waccd,dpminr,dpmaxr,dpthr,wdiffr,wdifft;
      Fdouble hstep,hmin,compeps,xinit,xfinal,umax,cfr,pmax,ptopr;
      Fdouble theps,thepshi;
  };

  struct DS_RDTIME
  {
      Fdouble rdt_max,rdt_start,rdt_end;
  };

  // this one only exists in DS5
  struct DS5_DDCOM
  {
      Farray<Fdouble, 7, 12> ftp;
      Farray<Fdouble, 7, 12> ftn;
      Fdouble delu;
      Fdouble deld;
      Fdouble dels;
      Finteger ddpole;
      Finteger dddn;
      Fstring<10> ddfsi;
      Fstring<10> ddfsd;
  };

  // this one only exists in DS5
  struct DS5_NUCOM
  {
      Farray<Fdouble, 1, 29> wabr;
      Farray<Fdouble, 1, 29, 1, 3> was0br;
      Farray<Fdouble, 1, 15> wascbr;
      Farray<Fdouble, 1, 3> was0m;
      Fdouble wascm;
      Fdouble wamwimp;
      Fdouble wasv;
      Fdouble wasigsip;
      Fdouble wasigsdp;
      Flogical dswasetupcalled;
  };

  struct DS_NUCOM
  {
      Farray<Fdouble, 1, 29, 1, 3> ans0br;
      Farray<Fdouble, 1, 15> anscbr;
      Farray<Fdouble, 1, 3> ans0m;
      Fdouble anscm;
      Farray<Finteger, 1, 29,1, 6> anch_2body;
      Farray<Finteger, 1, 29, 1, 2> yieldchannels_line;
  };

  // this one only exists in DS 5
  struct DS5_HMCOM
  {
      Fdouble rho0;      // non-rescaled local density
      Fdouble rhox;      // rescaled local density
      Fdouble v_sun;     // circular speed at the Sun
      Fdouble r_0;       // galactocentric distance
      Fdouble v_earth;   // Keplerian velocity of the Earth around the Sun
      Finteger hclumpy;  // 1=smooth 2=clumpy
  };

  // this one only exists in DS 6
  struct DS_HMCOM
  {
      Fdouble rho0;      // non-rescaled local density
      Fdouble v_sun;     // circular speed at the Sun
      Fdouble r_0;       // galactocentric distance
      Fdouble v_earth;   // Keplerian velocity of the Earth around the Sun
      Finteger hclumpy;  // 1=smooth 2=clumpy
  };

  // this one only exists in DS 6
  struct DS_DDCOMLEGACY
  {
      Farray<Fdouble, 7, 12> ftp;
      Farray<Fdouble, 7, 12> ftn;
      Fdouble delu;
      Fdouble deld;
      Fdouble dels;
  };

  // this one only exists in DS 6
  struct DS_DDMSSMCOM
  {
      Finteger ddpole;
      Finteger dddn;
  };

  struct DS_HMISODF
  {
      Fdouble vd_3d;     // velocity dispersion in 3 dimensions
      Fdouble vgalesc;   // galactic escape velocity
  };

  struct DS_HMFRAMEVELCOM
  {
      Fdouble veX;
      Fdouble veY;
      Fdouble veZ;
      Fdouble vspX;
      Fdouble vspY;
      Fdouble vspZ;
      Fdouble v_obs;
  };

  struct DS_HMNOCLUE
  {
      Fdouble vobs;        // speed of earth observer with respect to halo
                           // yearly averaged ????
  };


}

#endif /* defined __DarkSUSY_types_hpp__ */
