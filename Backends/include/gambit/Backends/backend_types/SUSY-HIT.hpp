//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of container classes
///  for the SUSYHIT 1.4 backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Peter Athron
/// \author Csaba Balazs
/// \author Anders Kvellestad
/// \author Pat Scott
/// \date 2015 Jan-Apr
///
///  *********************************************

#ifndef __SUSYHIT_types_hpp__
#define __SUSYHIT_types_hpp__

#include "gambit/Utils/util_types.hpp"

namespace Gambit
{

    struct checkfavvio_type
    {
        Finteger icheckfav;
        Farray< Finteger,1,2 > imodfav;
    };

    struct susyhitin_type
    {
        Fdouble flagshsin;
        Fdouble amsin;
        Fdouble amcin;
        Fdouble ammuonin;
        Fdouble alphin;
        Fdouble gamwin;
        Fdouble gamzin;
        Fdouble vusin;
        Fdouble vcbin;
        Fdouble rvubin;
    };

    struct sd_leshouches1_type
    {
        Fstring<100> spinfo1;
        Fstring<100> spinfo2;
        Fstring<100> modselval;
        Fstring<20> mincom;
        Fstring<20> extcom;
        Fstring<20> softcom;
        Fstring<20> hmixcom;
    };

    struct sd_leshouches2_type
    {
        Farray< Fdouble,1,20 > minval;
        Farray< Fdouble,0,100 > extval;
        Farray< Fdouble,1,20 > smval;
        Farray< Fdouble,1,50 > massval;
        Farray< Fdouble,1,4,1,4 > nmixval;
        Farray< Fdouble,1,2,1,2 > umixval;
        Farray< Fdouble,1,2,1,2 > vmixval;
        Farray< Fdouble,1,2,1,2 > stopmixval;
        Farray< Fdouble,1,2,1,2 > sbotmixval;
        Farray< Fdouble,1,2,1,2 > staumixval;
        Farray< Fdouble,1,10 > hmixval;
        Farray< Fdouble,1,3 > gaugeval;
        Farray< Fdouble,1,100 > msoftval;
        Farray< Fdouble,1,3,1,3 > auval;
        Farray< Fdouble,1,3,1,3 > adval;
        Farray< Fdouble,1,3,1,3 > aeval;
        Farray< Fdouble,1,3,1,3 > yuval;
        Farray< Fdouble,1,3,1,3 > ydval;
        Farray< Fdouble,1,3,1,3 > yeval;
        Fdouble alphaval;
        Farray< Fdouble,1,22 > qvalue;
        Farray< Finteger,1,2 > imod;
    };

    struct slha_leshouches2_hdec_type
    {
        Farray< Fdouble,1,20 > minval;
        Farray< Fdouble,0,100 > extval;
        Farray< Fdouble,1,20 > smval;
        Farray< Fdouble,1,50 > massval;
        Farray< Fdouble,1,4,1,4 > nmixval;
        Farray< Fdouble,1,2,1,2 > umixval;
        Farray< Fdouble,1,2,1,2 > vmixval;
        Farray< Fdouble,1,2,1,2 > stopmixval;
        Farray< Fdouble,1,2,1,2 > sbotmixval;
        Farray< Fdouble,1,2,1,2 > staumixval;
        Farray< Fdouble,1,10 > hmixval;
        Farray< Fdouble,1,3 > gaugeval;
        Farray< Fdouble,1,100 > msoftval;
        Farray< Fdouble,1,3,1,3 > auval;
        Farray< Fdouble,1,3,1,3 > adval;
        Farray< Fdouble,1,3,1,3 > aeval;
        Farray< Fdouble,1,3,1,3 > yuval;
        Farray< Fdouble,1,3,1,3 > ydval;
        Farray< Fdouble,1,3,1,3 > yeval;
        Fdouble alphaval;
        Farray< Fdouble,1,20 > qvalue;
        Farray< Finteger,1,2 > imod;
    };

    struct widtha_hdec_type
    {
        Fdouble abrb;
        Fdouble abrl;
        Fdouble abrm;
        Fdouble abrs;
        Fdouble abrc;
        Fdouble abrt;
        Fdouble abrg;
        Fdouble abrga;
        Fdouble abrzga;
        Fdouble abrz;
        Fdouble awdth;
    };

    struct widthhl_hdec_type
    {
        Fdouble hlbrb;
        Fdouble hlbrl;
        Fdouble hlbrm;
        Fdouble hlbrs;
        Fdouble hlbrc;
        Fdouble hlbrt;
        Fdouble hlbrg;
        Fdouble hlbrga;
        Fdouble hlbrzga;
        Fdouble hlbrw;
        Fdouble hlbrz;
        Fdouble hlbra;
        Fdouble hlbraz;
        Fdouble hlbrhw;
        Fdouble hlwdth;
    };

    struct widthhh_hdec_type
    {
        Fdouble hhbrb;
        Fdouble hhbrl;
        Fdouble hhbrm;
        Fdouble hhbrs;
        Fdouble hhbrc;
        Fdouble hhbrt;
        Fdouble hhbrg;
        Fdouble hhbrga;
        Fdouble hhbrzga;
        Fdouble hhbrw;
        Fdouble hhbrz;
        Fdouble hhbrh;
        Fdouble hhbra;
        Fdouble hhbraz;
        Fdouble hhbrhw;
        Fdouble hhwdth;
    };

    struct widthhc_hdec_type
    {
        Fdouble hcbrb;
        Fdouble hcbrl;
        Fdouble hcbrm;
        Fdouble hcbrbu;
        Fdouble hcbrs;
        Fdouble hcbrc;
        Fdouble hcbrt;
        Fdouble hcbrw;
        Fdouble hcbra;
        Fdouble hcwdth;
    };

    struct wisusy_hdec_type
    {
        Farray< Fdouble,1,2,1,2 > hlbrsc;
        Farray< Fdouble,1,4,1,4 > hlbrsn;
        Farray< Fdouble,1,2,1,2 > hhbrsc;
        Farray< Fdouble,1,4,1,4 > hhbrsn;
        Farray< Fdouble,1,2,1,2 > habrsc;
        Farray< Fdouble,1,4,1,4 > habrsn;
        Farray< Fdouble,1,2,1,4 > hcbrsu;
        Fdouble hlbrcht;
        Fdouble hhbrcht;
        Fdouble habrcht;
        Fdouble hlbrnet;
        Fdouble hhbrnet;
        Fdouble habrnet;
        Fdouble hcbrcnt;
        Fdouble hlbrsl;
        Fdouble hhbrsl;
        Fdouble hcbrsl;
        Fdouble habrsl;
        Fdouble habrst;
        Fdouble habrsb;
        Fdouble hhbrsq;
        Farray< Fdouble,1,2,1,2 > hhbrst;
        Farray< Fdouble,1,2,1,2 > hhbrsb;
        Fdouble hhbrsqt;
        Fdouble hcbrsq;
        Farray< Fdouble,1,2,1,2 > hcbrstb;
        Fdouble hcbrsqt;
        Fdouble hlbrsq;
        Fdouble hlbrsqt;
    };

    struct wisfer_hdec_type
    {
        Fdouble bhlslnl;
        Fdouble bhlslel;
        Fdouble bhlsler;
        Fdouble bhlsqul;
        Fdouble bhlsqur;
        Fdouble bhlsqdl;
        Fdouble bhlsqdr;
        Farray< Fdouble,1,2,1,2 > bhlst;
        Farray< Fdouble,1,2,1,2 > bhlsb;
        Farray< Fdouble,1,2,1,2 > bhlstau;
        Fdouble bhhslnl;
        Fdouble bhhslel;
        Fdouble bhhsler;
        Fdouble bhhsqul;
        Fdouble bhhsqur;
        Fdouble bhhsqdl;
        Fdouble bhhsqdr;
        Farray< Fdouble,1,2,1,2 > bhhst;
        Farray< Fdouble,1,2,1,2 > bhhsb;
        Farray< Fdouble,1,2,1,2 > bhhstau;
        Fdouble bhastau;
        Fdouble bhasb;
        Fdouble bhast;
        Fdouble bhcsl00;
        Fdouble bhcsl11;
        Fdouble bhcsl21;
        Fdouble bhcsq;
        Farray< Fdouble,1,2,1,2 > bhcstb;
    };

    struct hd_golddec_type
    {
        Farray< Fdouble,1,4 > whlgd;
        Farray< Fdouble,1,4 > whhgd;
        Farray< Fdouble,1,4 > whagd;
        Farray< Fdouble,1,2 > whcgd;
    };

    struct sd_char2body_type
    {
        Farray< Fdouble,1,2 > brcharst1;
        Farray< Fdouble,1,2 > brcharst2;
        Farray< Fdouble,1,2 > brcharsb1;
        Farray< Fdouble,1,2 > brcharsb2;
        Farray< Fdouble,1,2 > brcharsupl;
        Farray< Fdouble,1,2 > brcharsupr;
        Farray< Fdouble,1,2 > brcharsdownl;
        Farray< Fdouble,1,2 > brcharsdownr;
        Farray< Fdouble,1,2 > brcharsnel;
        Farray< Fdouble,1,2 > brcharsn1;
        Farray< Fdouble,1,2 > brcharsn2;
        Farray< Fdouble,1,2 > brcharsell;
        Farray< Fdouble,1,2 > brcharselr;
        Farray< Fdouble,1,2 > brcharstau1;
        Farray< Fdouble,1,2 > brcharstau2;
        Farray< Fdouble,1,2,1,4 > brcharhcneut;
        Farray< Fdouble,1,2,1,4 > brcharwneut;
        Fdouble brcharzchic;
        Fdouble brcharhlchic;
        Fdouble brcharhhchic;
        Fdouble brcharhachic;
    };

    struct sd_char2bodygrav_type
    {
        Farray< Fdouble,1,2 > brcharwgravitino;
        Farray< Fdouble,1,2 > brcharhcgravitino;
    };

    struct sd_char3body_type
    {
        Farray< Fdouble,1,2,1,4 > brntaunut;
        Farray< Fdouble,1,2,1,4 > brnelnue;
        Farray< Fdouble,1,2,1,4 > brnmunumu;
        Farray< Fdouble,1,2,1,4 > brnupdb;
        Farray< Fdouble,1,2,1,4 > brnchsb;
        Farray< Fdouble,1,2,1,4 > brntopbb;
        Farray< Fdouble,1,2 > brglupdb;
        Farray< Fdouble,1,2 > brglchsb;
        Farray< Fdouble,1,2 > brgltopbb;
        Fdouble brchee;
        Fdouble brchmumu;
        Fdouble brchtautau;
        Fdouble brchnene;
        Fdouble brchnmunmu;
        Fdouble brchntauntau;
        Fdouble brchupup;
        Fdouble brchdodo;
        Fdouble brchchch;
        Fdouble brchstst;
        Fdouble brchtoptop;
        Fdouble brchbotbot;
    };

    struct sd_charwidth_type
    {
        Farray< Fdouble,1,2 > chartot;
    };

    struct sd_neut2body_type
    {
        Farray< Fdouble,1,4 > brneutst1;
        Farray< Fdouble,1,4 > brneutst2;
        Farray< Fdouble,1,4 > brneutsb1;
        Farray< Fdouble,1,4 > brneutsb2;
        Farray< Fdouble,1,4 > brneutsupl;
        Farray< Fdouble,1,4 > brneutsupr;
        Farray< Fdouble,1,4 > brneutsdownl;
        Farray< Fdouble,1,4 > brneutsdownr;
        Farray< Fdouble,1,4 > brneutsnel;
        Farray< Fdouble,1,4 > brneutsn1;
        Farray< Fdouble,1,4 > brneutsn2;
        Farray< Fdouble,1,4 > brneutsell;
        Farray< Fdouble,1,4 > brneutselr;
        Farray< Fdouble,1,4 > brneutstau1;
        Farray< Fdouble,1,4 > brneutstau2;
        Farray< Fdouble,1,4,1,2 > brneutwchar;
        Farray< Fdouble,1,4,1,2 > brneuthcchar;
        Farray< Fdouble,1,4,1,4 > brneutzneut;
        Farray< Fdouble,1,4,1,4 > brneuthlneut;
        Farray< Fdouble,1,4,1,4 > brneuthhneut;
        Farray< Fdouble,1,4,1,4 > brneuthaneut;
    };

    struct sd_neut2bodygrav_type
    {
        Farray< Fdouble,1,4 > brneutgamgrav;
        Farray< Fdouble,1,4 > brneutzgrav;
        Farray< Fdouble,1,4 > brneuthlgrav;
        Farray< Fdouble,1,4 > brneuthhgrav;
        Farray< Fdouble,1,4 > brneuthagrav;
    };

    struct sd_neut3body_type
    {
        Farray< Fdouble,1,4,1,4 > brneutup;
        Farray< Fdouble,1,4,1,4 > brneutdow;
        Farray< Fdouble,1,4,1,4 > brneutch;
        Farray< Fdouble,1,4,1,4 > brneutst;
        Farray< Fdouble,1,4,1,4 > brneutbot;
        Farray< Fdouble,1,4,1,4 > brneuttop;
        Farray< Fdouble,1,4,1,4 > brneutel;
        Farray< Fdouble,1,4,1,4 > brneutmu;
        Farray< Fdouble,1,4,1,4 > brneuttau;
        Farray< Fdouble,1,4,1,4 > brneutnue;
        Farray< Fdouble,1,4,1,4 > brneutnumu;
        Farray< Fdouble,1,4,1,4 > brneutnutau;
        Farray< Fdouble,1,4,1,2 > brchubd;
        Farray< Fdouble,1,4,1,2 > brchcbs;
        Farray< Fdouble,1,4,1,2 > brchtbb;
        Farray< Fdouble,1,4,1,2 > brchelne;
        Farray< Fdouble,1,4,1,2 > brchmunmu;
        Farray< Fdouble,1,4,1,2 > brchtauntau;
        Farray< Fdouble,1,4 > brglup;
        Farray< Fdouble,1,4 > brgldo;
        Farray< Fdouble,1,4 > brglch;
        Farray< Fdouble,1,4 > brglst;
        Farray< Fdouble,1,4 > brgltop;
        Farray< Fdouble,1,4 > brglbot;
    };

    struct sd_neutloop_type
    {
        Farray< Fdouble,1,4,1,4 > brnraddec;
    };

    struct sd_neutwidth_type
    {
        Farray< Fdouble,1,4 > neuttot;
    };

    struct sd_glui2body_type
    {
        Fdouble brgst1;
        Fdouble brgst2;
        Fdouble brgsb1;
        Fdouble brgsb2;
        Fdouble brgsupl;
        Fdouble brgsupr;
        Fdouble brgsdownl;
        Fdouble brgsdownr;
    };

    struct sd_glui3body_type
    {
        Farray< Fdouble,1,4 > brgoup;
        Farray< Fdouble,1,4 > brgoch;
        Farray< Fdouble,1,4 > brgodn;
        Farray< Fdouble,1,4 > brgost;
        Farray< Fdouble,1,4 > brgotp;
        Farray< Fdouble,1,4 > brgobt;
        Farray< Fdouble,1,2 > brgoud;
        Farray< Fdouble,1,2 > brgocs;
        Farray< Fdouble,1,2 > brgotb;
        Fdouble brhcst1b;
        Fdouble brwst1b;
    };

    struct sd_gluiloop_type
    {
        Farray< Fdouble,1,4 > brglnjgluon;
    };

    struct sd_gluiwidth_type
    {
        Fdouble gluitot;
    };

    struct sd_sup2body_type
    {
        Farray< Fdouble,1,4 > brsuplnup;
        Farray< Fdouble,1,2 > brsuplcdow;
        Fdouble brsuplglui;
        Farray< Fdouble,1,4 > brsuprnup;
        Farray< Fdouble,1,2 > brsuprcdow;
        Fdouble brsuprglui;
    };

    struct sd_supwidth_type
    {
        Fdouble supltot2;
        Fdouble suprtot2;
    };

    struct sd_sdown2body_type
    {
        Farray< Fdouble,1,4 > brsdowlndow;
        Farray< Fdouble,1,2 > brsdowlchup;
        Fdouble brsdowlglui;
        Farray< Fdouble,1,4 > brsdowrndow;
        Farray< Fdouble,1,2 > brsdowrchup;
        Fdouble brsdowrglui;
    };

    struct sd_sdownwidth_type
    {
        Fdouble sdowltot2;
        Fdouble sdowrtot2;
    };

    struct sd_stop2body_type
    {
        Farray< Fdouble,1,4 > brst1neutt;
        Farray< Fdouble,1,4 > brst2neutt;
        Farray< Fdouble,1,2 > brst1charb;
        Farray< Fdouble,1,2 > brst1hcsb;
        Farray< Fdouble,1,2 > brst1wsb;
        Farray< Fdouble,1,2 > brst2charb;
        Farray< Fdouble,1,2 > brst2hcsb;
        Farray< Fdouble,1,2 > brst2wsb;
        Fdouble brst1glui;
        Fdouble brst2glui;
        Fdouble brst2hl;
        Fdouble brst2hh;
        Fdouble brst2ha;
        Fdouble brst2ztop;
    };

    struct sd_stop3body_type
    {
        Farray< Fdouble,1,2,1,4 > brstopw;
        Farray< Fdouble,1,2,1,4 > brstoph;
        Farray< Fdouble,1,2,1,2 > brststau;
        Farray< Fdouble,1,2,1,2 > brstsntau;
        Farray< Fdouble,1,2,1,2 > brstsel;
        Farray< Fdouble,1,2,1,2 > brstbsbst;
        Farray< Fdouble,1,2,1,2 > brstbbsbt;
        Farray< Fdouble,1,2,1,2 > brsttausbnu;
        Farray< Fdouble,1,2,1,2 > brstelsbnu;
        Farray< Fdouble,1,2,1,2 > brstupsbdow;
        Farray< Fdouble,1,2 > brstsnel;
        Fdouble brst2st1tt;
        Fdouble brst2st1startt;
        Fdouble brst2st1bb;
        Fdouble brst2st1uu;
        Fdouble brst2st1dd;
        Fdouble brst2st1ee;
        Fdouble brst2st1nunu;
        Fdouble brst2st1tautau;
    };

    struct sd_stoploop_type
    {
        Fdouble brgamma;
        Fdouble brgammaup;
        Fdouble brgammagluino;
    };

    struct sd_stop4body_type
    {
        Fdouble brgamma4bod;
        Fdouble brgammaup4bod;
        Fdouble brgammagluino4bod;
        Fdouble br4bodoffshelltau;
    };

    struct sd_stopwidth_type
    {
        Fdouble stoptot4;
        Farray< Fdouble,1,2 > stoptot;
    };

    struct sd_sbot2body_type
    {
        Farray< Fdouble,1,4 > brsb1neutt;
        Farray< Fdouble,1,4 > brsb2neutt;
        Farray< Fdouble,1,2 > brsb1chart;
        Farray< Fdouble,1,2 > brsb2chart;
        Farray< Fdouble,1,2 > brsb1hcst;
        Farray< Fdouble,1,2 > brsb2hcst;
        Farray< Fdouble,1,2 > brsb1wst;
        Farray< Fdouble,1,2 > brsb2wst;
        Fdouble brsb1glui;
        Fdouble brsb2glui;
        Fdouble brsb2hl;
        Fdouble brsb2hh;
        Fdouble brsb2ha;
        Fdouble brsb2zbot;
    };

    struct sd_sbot3body_type
    {
        Farray< Fdouble,1,2,1,2 > brsbstau;
        Farray< Fdouble,1,2,1,2 > brsbsntau;
        Farray< Fdouble,1,2,1,2 > brsbsel;
        Farray< Fdouble,1,2,1,2 > brsbtstsb;
        Farray< Fdouble,1,2,1,2 > brsbtbstb;
        Farray< Fdouble,1,2,1,2 > brsbtaustnu;
        Farray< Fdouble,1,2,1,2 > brsbelstnu;
        Farray< Fdouble,1,2,1,2 > brsbupstdow;
        Farray< Fdouble,1,2 > brsbsnel;
        Fdouble brsb2sb1bb;
        Fdouble brsb2sb1starbb;
        Fdouble brsb2sb1tt;
        Fdouble brsb2sb1uu;
        Fdouble brsb2sb1dd;
        Fdouble brsb2sb1ee;
        Fdouble brsb2sb1nunu;
        Fdouble brsb2sb1tautau;
    };

    struct sd_sbotwidth_type
    {
        Farray< Fdouble,1,2 > sbottot;
    };

    struct sd_sel2body_type
    {
        Farray< Fdouble,1,4 > brsellneute;
        Farray< Fdouble,1,2 > brsellcharnue;
        Farray< Fdouble,1,4 > brselrneute;
        Farray< Fdouble,1,2 > brselrcharnue;
    };

    struct sd_selwidth_type
    {
        Fdouble selltot2;
        Fdouble selrtot2;
    };

    struct sd_snel2body_type
    {
        Farray< Fdouble,1,4 > brsnellneut;
        Farray< Fdouble,1,4 > brsnellchar;
    };

    struct sd_snelwidth_type
    {
        Fdouble sneltot2;
    };

    struct sd_stau2body_type
    {
        Farray< Fdouble,1,4 > brstau1neut;
        Farray< Fdouble,1,4 > brstau2neut;
        Farray< Fdouble,1,2 > brstau1char;
        Farray< Fdouble,1,2 > brstau1hcsn;
        Farray< Fdouble,1,2 > brstau1wsn;
        Farray< Fdouble,1,2 > brstau2char;
        Farray< Fdouble,1,2 > brstau2hcsn;
        Farray< Fdouble,1,2 > brstau2wsn;
        Fdouble brstau2hl;
        Fdouble brstau2hh;
        Fdouble brstau2ha;
        Fdouble brstau2ztau;
    };

    struct sd_stau2bodygrav_type
    {
        Fdouble brstautaugrav;
    };

    struct sd_stauwidth_type
    {
        Fdouble stau1tot2;
        Fdouble stau2tot2;
    };

    struct sd_sntau2body_type
    {
        Farray< Fdouble,1,4 > brsntauneut;
        Farray< Fdouble,1,2 > brsntauchar;
        Farray< Fdouble,1,2 > brsntau1wstau;
        Farray< Fdouble,1,2 > brsntau1hcstau;
    };

    struct sd_sntauwidth_type
    {
        Fdouble sntautot2;
    };

    struct sd_top2body_type
    {
        Fdouble brtopbw;
        Fdouble brtopbh;
        Farray< Fdouble,1,4,1,2 > brtopneutrstop;
    };

    struct sd_topwidth_type
    {
        Fdouble toptot2;
    };

    struct flavviolation_type
    {
        Farray< Fdouble,1,3,1,3 > vckm;
        Farray< Fdouble,1,3,1,3 > msq2;
        Farray< Fdouble,1,3,1,3 > msd2;
        Farray< Fdouble,1,3,1,3 > msu2;
        Farray< Fdouble,1,3,1,3 > td;
        Farray< Fdouble,1,3,1,3 > tu;
        Farray< Fdouble,1,6,1,6 > usqmix;
        Finteger ifavvio;
        Farray< Fdouble,1,6,1,6 > dsqmix;
    };

    struct sd_mbmb_type
    {
        Fdouble sd_mbmb;
        Finteger i_sd_mbmb;
    };

    struct sd_selectron_type
    {
        Farray< Fdouble,1,6,1,6 > selmix;
    };

}

#endif // defined __SUSYHIT_types_hpp__
