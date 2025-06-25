#ifndef __loaded_types_Pythia_8_312_hpp__
#define __loaded_types_Pythia_8_312_hpp__ 1

#ifndef EXCLUDE_HEPMC

#include "wrapper_GAMBIT_hepmc_writer.h"
#include "wrapper_Pythia.h"
#include "wrapper_UserHooks.h"
#include "wrapper_PartonLevel.h"
#include "wrapper_ResonanceDecays.h"
#include "wrapper_ParticleDecays.h"
#include "wrapper_SigmaProcess.h"
#include "wrapper_SLHAinterface.h"
#include "wrapper_ParticleData.h"
#include "wrapper_CoupSUSY.h"
#include "wrapper_LHdecayChannel.h"
#include "wrapper_LHdecayTable.h"
#include "wrapper_SusyLesHouches.h"
#include "wrapper_DecayChannel.h"
#include "wrapper_ParticleDataEntry.h"
#include "wrapper_CoupSM.h"
#include "wrapper_ResonanceWidths.h"
#include "wrapper_ResonanceGmZ.h"
#include "wrapper_SigmaTotal.h"
#include "wrapper_BeamParticle.h"
#include "wrapper_SlowJet.h"
#include "wrapper_Event.h"
#include "wrapper_Particle.h"
#include "wrapper_AlphaStrong.h"
#include "wrapper_AlphaEM.h"
#include "wrapper_Parm.h"
#include "wrapper_Settings.h"
#include "wrapper_Rndm.h"
#include "wrapper_Info.h"
#include "wrapper_Logger.h"
#include "wrapper_Vec4.h"
#include "wrapper_Hist.h"
#include "identification.hpp"

// Indicate which types are provided by this backend, and what the symbols of their factories are.
#define Pythia_8_312_all_data \
  (( /*class*/(Pythia8)(GAMBIT_hepmc_writer),    /*constructors*/((("Factory_GAMBIT_hepmc_writer_0__BOSS_1","_Factory_GAMBIT_hepmc_writer_0__BOSS_1"),())) )) \
  (( /*class*/(Pythia8)(Pythia),    /*constructors*/((("Factory_Pythia_0__BOSS_2","_Factory_Pythia_0__BOSS_2"),(std::string, bool))) ((("Factory_Pythia_1__BOSS_3","_Factory_Pythia_1__BOSS_3"),(std::string))) ((("Factory_Pythia_2__BOSS_4","_Factory_Pythia_2__BOSS_4"),())) ((("Factory_Pythia_3__BOSS_5","_Factory_Pythia_3__BOSS_5"),(my_ns::Pythia8::Settings&, my_ns::Pythia8::ParticleData&, bool))) ((("Factory_Pythia_4__BOSS_6","_Factory_Pythia_4__BOSS_6"),(my_ns::Pythia8::Settings&, my_ns::Pythia8::ParticleData&))) ((("Factory_Pythia_5__BOSS_7","_Factory_Pythia_5__BOSS_7"),(std::istream&, std::istream&, bool))) ((("Factory_Pythia_6__BOSS_8","_Factory_Pythia_6__BOSS_8"),(std::istream&, std::istream&))) )) \
  (( /*class*/(Pythia8)(UserHooks),    /*constructors*/((("Factory_UserHooks_0__BOSS_9","_Factory_UserHooks_0__BOSS_9"),(const my_ns::Pythia8::UserHooks&))) )) \
  (( /*class*/(Pythia8)(PartonLevel),    /*constructors*/((("Factory_PartonLevel_0__BOSS_10","_Factory_PartonLevel_0__BOSS_10"),())) )) \
  (( /*class*/(Pythia8)(ResonanceDecays),    /*constructors*/((("Factory_ResonanceDecays_0__BOSS_11","_Factory_ResonanceDecays_0__BOSS_11"),())) )) \
  (( /*class*/(Pythia8)(ParticleDecays),    /*constructors*/((("Factory_ParticleDecays_0__BOSS_12","_Factory_ParticleDecays_0__BOSS_12"),())) )) \
  (( /*class*/(Pythia8)(SigmaProcess),    /*constructors*/((("Factory_SigmaProcess_0__BOSS_13","_Factory_SigmaProcess_0__BOSS_13"),(const my_ns::Pythia8::SigmaProcess&))) )) \
  (( /*class*/(Pythia8)(SLHAinterface),    /*constructors*/((("Factory_SLHAinterface_0__BOSS_14","_Factory_SLHAinterface_0__BOSS_14"),())) )) \
  (( /*class*/(Pythia8)(ParticleData),    /*constructors*/((("Factory_ParticleData_0__BOSS_15","_Factory_ParticleData_0__BOSS_15"),())) )) \
  (( /*class*/(Pythia8)(CoupSUSY),    /*constructors*/((("Factory_CoupSUSY_0__BOSS_16","_Factory_CoupSUSY_0__BOSS_16"),())) )) \
  (( /*class*/(Pythia8)(LHdecayChannel),    /*constructors*/((("Factory_LHdecayChannel_0__BOSS_17","_Factory_LHdecayChannel_0__BOSS_17"),())) ((("Factory_LHdecayChannel_1__BOSS_18","_Factory_LHdecayChannel_1__BOSS_18"),(double, int, std::vector<int>, std::string))) ((("Factory_LHdecayChannel_2__BOSS_19","_Factory_LHdecayChannel_2__BOSS_19"),(double, int, std::vector<int>))) )) \
  (( /*class*/(Pythia8)(LHdecayTable),    /*constructors*/((("Factory_LHdecayTable_0__BOSS_20","_Factory_LHdecayTable_0__BOSS_20"),())) ((("Factory_LHdecayTable_1__BOSS_21","_Factory_LHdecayTable_1__BOSS_21"),(int))) ((("Factory_LHdecayTable_2__BOSS_22","_Factory_LHdecayTable_2__BOSS_22"),(int, double))) )) \
  (( /*class*/(Pythia8)(SusyLesHouches),    /*constructors*/((("Factory_SusyLesHouches_0__BOSS_23","_Factory_SusyLesHouches_0__BOSS_23"),(int))) ((("Factory_SusyLesHouches_1__BOSS_24","_Factory_SusyLesHouches_1__BOSS_24"),())) ((("Factory_SusyLesHouches_2__BOSS_25","_Factory_SusyLesHouches_2__BOSS_25"),(std::string, int))) ((("Factory_SusyLesHouches_3__BOSS_26","_Factory_SusyLesHouches_3__BOSS_26"),(std::string))) )) \
  (( /*class*/(Pythia8)(DecayChannel),    /*constructors*/((("Factory_DecayChannel_0__BOSS_27","_Factory_DecayChannel_0__BOSS_27"),(int, double, int, int, int, int, int, int, int, int, int))) ((("Factory_DecayChannel_1__BOSS_28","_Factory_DecayChannel_1__BOSS_28"),(int, double, int, int, int, int, int, int, int, int))) ((("Factory_DecayChannel_2__BOSS_29","_Factory_DecayChannel_2__BOSS_29"),(int, double, int, int, int, int, int, int, int))) ((("Factory_DecayChannel_3__BOSS_30","_Factory_DecayChannel_3__BOSS_30"),(int, double, int, int, int, int, int, int))) ((("Factory_DecayChannel_4__BOSS_31","_Factory_DecayChannel_4__BOSS_31"),(int, double, int, int, int, int, int))) ((("Factory_DecayChannel_5__BOSS_32","_Factory_DecayChannel_5__BOSS_32"),(int, double, int, int, int, int))) ((("Factory_DecayChannel_6__BOSS_33","_Factory_DecayChannel_6__BOSS_33"),(int, double, int, int, int))) ((("Factory_DecayChannel_7__BOSS_34","_Factory_DecayChannel_7__BOSS_34"),(int, double, int, int))) ((("Factory_DecayChannel_8__BOSS_35","_Factory_DecayChannel_8__BOSS_35"),(int, double, int))) ((("Factory_DecayChannel_9__BOSS_36","_Factory_DecayChannel_9__BOSS_36"),(int, double))) ((("Factory_DecayChannel_10__BOSS_37","_Factory_DecayChannel_10__BOSS_37"),(int))) ((("Factory_DecayChannel_11__BOSS_38","_Factory_DecayChannel_11__BOSS_38"),())) )) \
  (( /*class*/(Pythia8)(ParticleDataEntry),    /*constructors*/((("Factory_ParticleDataEntry_0__BOSS_39","_Factory_ParticleDataEntry_0__BOSS_39"),(int, std::string, int, int, int, double, double, double, double, double, bool))) ((("Factory_ParticleDataEntry_1__BOSS_40","_Factory_ParticleDataEntry_1__BOSS_40"),(int, std::string, int, int, int, double, double, double, double, double))) ((("Factory_ParticleDataEntry_2__BOSS_41","_Factory_ParticleDataEntry_2__BOSS_41"),(int, std::string, int, int, int, double, double, double, double))) ((("Factory_ParticleDataEntry_3__BOSS_42","_Factory_ParticleDataEntry_3__BOSS_42"),(int, std::string, int, int, int, double, double, double))) ((("Factory_ParticleDataEntry_4__BOSS_43","_Factory_ParticleDataEntry_4__BOSS_43"),(int, std::string, int, int, int, double, double))) ((("Factory_ParticleDataEntry_5__BOSS_44","_Factory_ParticleDataEntry_5__BOSS_44"),(int, std::string, int, int, int, double))) ((("Factory_ParticleDataEntry_6__BOSS_45","_Factory_ParticleDataEntry_6__BOSS_45"),(int, std::string, int, int, int))) ((("Factory_ParticleDataEntry_7__BOSS_46","_Factory_ParticleDataEntry_7__BOSS_46"),(int, std::string, int, int))) ((("Factory_ParticleDataEntry_8__BOSS_47","_Factory_ParticleDataEntry_8__BOSS_47"),(int, std::string, int))) ((("Factory_ParticleDataEntry_9__BOSS_48","_Factory_ParticleDataEntry_9__BOSS_48"),(int, std::string))) ((("Factory_ParticleDataEntry_10__BOSS_49","_Factory_ParticleDataEntry_10__BOSS_49"),(int))) ((("Factory_ParticleDataEntry_11__BOSS_50","_Factory_ParticleDataEntry_11__BOSS_50"),())) ((("Factory_ParticleDataEntry_12__BOSS_51","_Factory_ParticleDataEntry_12__BOSS_51"),(int, std::string, std::string, int, int, int, double, double, double, double, double, bool))) ((("Factory_ParticleDataEntry_13__BOSS_52","_Factory_ParticleDataEntry_13__BOSS_52"),(int, std::string, std::string, int, int, int, double, double, double, double, double))) ((("Factory_ParticleDataEntry_14__BOSS_53","_Factory_ParticleDataEntry_14__BOSS_53"),(int, std::string, std::string, int, int, int, double, double, double, double))) ((("Factory_ParticleDataEntry_15__BOSS_54","_Factory_ParticleDataEntry_15__BOSS_54"),(int, std::string, std::string, int, int, int, double, double, double))) ((("Factory_ParticleDataEntry_16__BOSS_55","_Factory_ParticleDataEntry_16__BOSS_55"),(int, std::string, std::string, int, int, int, double, double))) ((("Factory_ParticleDataEntry_17__BOSS_56","_Factory_ParticleDataEntry_17__BOSS_56"),(int, std::string, std::string, int, int, int, double))) ((("Factory_ParticleDataEntry_18__BOSS_57","_Factory_ParticleDataEntry_18__BOSS_57"),(int, std::string, std::string, int, int, int))) ((("Factory_ParticleDataEntry_19__BOSS_58","_Factory_ParticleDataEntry_19__BOSS_58"),(int, std::string, std::string, int, int))) ((("Factory_ParticleDataEntry_20__BOSS_59","_Factory_ParticleDataEntry_20__BOSS_59"),(int, std::string, std::string, int))) ((("Factory_ParticleDataEntry_21__BOSS_60","_Factory_ParticleDataEntry_21__BOSS_60"),(int, std::string, std::string))) )) \
  (( /*class*/(Pythia8)(CoupSM),    /*constructors*/((("Factory_CoupSM_0__BOSS_61","_Factory_CoupSM_0__BOSS_61"),())) )) \
  (( /*class*/(Pythia8)(ResonanceWidths),    /*constructors*/((("Factory_ResonanceWidths_0__BOSS_62","_Factory_ResonanceWidths_0__BOSS_62"),(const my_ns::Pythia8::ResonanceWidths&))) )) \
  (( /*class*/(Pythia8)(ResonanceGmZ),    /*constructors*/((("Factory_ResonanceGmZ_0__BOSS_63","_Factory_ResonanceGmZ_0__BOSS_63"),(int))) )) \
  (( /*class*/(Pythia8)(SigmaTotal),    /*constructors*/((("Factory_SigmaTotal_0__BOSS_64","_Factory_SigmaTotal_0__BOSS_64"),())) )) \
  (( /*class*/(Pythia8)(BeamParticle),    /*constructors*/((("Factory_BeamParticle_0__BOSS_65","_Factory_BeamParticle_0__BOSS_65"),())) )) \
  (( /*class*/(Pythia8)(SlowJet),    /*constructors*/((("Factory_SlowJet_0__BOSS_66","_Factory_SlowJet_0__BOSS_66"),(int, double, double, double, int, int))) ((("Factory_SlowJet_1__BOSS_67","_Factory_SlowJet_1__BOSS_67"),(int, double, double, double, int))) ((("Factory_SlowJet_2__BOSS_68","_Factory_SlowJet_2__BOSS_68"),(int, double, double, double))) ((("Factory_SlowJet_3__BOSS_69","_Factory_SlowJet_3__BOSS_69"),(int, double, double))) ((("Factory_SlowJet_4__BOSS_70","_Factory_SlowJet_4__BOSS_70"),(int, double))) )) \
  (( /*class*/(Pythia8)(Event),    /*constructors*/((("Factory_Event_0__BOSS_71","_Factory_Event_0__BOSS_71"),(int))) ((("Factory_Event_1__BOSS_72","_Factory_Event_1__BOSS_72"),())) )) \
  (( /*class*/(Pythia8)(Particle),    /*constructors*/((("Factory_Particle_0__BOSS_73","_Factory_Particle_0__BOSS_73"),())) ((("Factory_Particle_1__BOSS_74","_Factory_Particle_1__BOSS_74"),(int, int, int, int, int, int, int, int, double, double, double, double, double, double, double))) ((("Factory_Particle_2__BOSS_75","_Factory_Particle_2__BOSS_75"),(int, int, int, int, int, int, int, int, double, double, double, double, double, double))) ((("Factory_Particle_3__BOSS_76","_Factory_Particle_3__BOSS_76"),(int, int, int, int, int, int, int, int, double, double, double, double, double))) ((("Factory_Particle_4__BOSS_77","_Factory_Particle_4__BOSS_77"),(int, int, int, int, int, int, int, int, double, double, double, double))) ((("Factory_Particle_5__BOSS_78","_Factory_Particle_5__BOSS_78"),(int, int, int, int, int, int, int, int, double, double, double))) ((("Factory_Particle_6__BOSS_79","_Factory_Particle_6__BOSS_79"),(int, int, int, int, int, int, int, int, double, double))) ((("Factory_Particle_7__BOSS_80","_Factory_Particle_7__BOSS_80"),(int, int, int, int, int, int, int, int, double))) ((("Factory_Particle_8__BOSS_81","_Factory_Particle_8__BOSS_81"),(int, int, int, int, int, int, int, int))) ((("Factory_Particle_9__BOSS_82","_Factory_Particle_9__BOSS_82"),(int, int, int, int, int, int, int))) ((("Factory_Particle_10__BOSS_83","_Factory_Particle_10__BOSS_83"),(int, int, int, int, int, int))) ((("Factory_Particle_11__BOSS_84","_Factory_Particle_11__BOSS_84"),(int, int, int, int, int))) ((("Factory_Particle_12__BOSS_85","_Factory_Particle_12__BOSS_85"),(int, int, int, int))) ((("Factory_Particle_13__BOSS_86","_Factory_Particle_13__BOSS_86"),(int, int, int))) ((("Factory_Particle_14__BOSS_87","_Factory_Particle_14__BOSS_87"),(int, int))) ((("Factory_Particle_15__BOSS_88","_Factory_Particle_15__BOSS_88"),(int))) ((("Factory_Particle_16__BOSS_89","_Factory_Particle_16__BOSS_89"),(int, int, int, int, int, int, int, int, my_ns::Pythia8::Vec4, double, double, double))) ((("Factory_Particle_17__BOSS_90","_Factory_Particle_17__BOSS_90"),(int, int, int, int, int, int, int, int, my_ns::Pythia8::Vec4, double, double))) ((("Factory_Particle_18__BOSS_91","_Factory_Particle_18__BOSS_91"),(int, int, int, int, int, int, int, int, my_ns::Pythia8::Vec4, double))) ((("Factory_Particle_19__BOSS_92","_Factory_Particle_19__BOSS_92"),(int, int, int, int, int, int, int, int, my_ns::Pythia8::Vec4))) )) \
  (( /*class*/(Pythia8)(AlphaStrong),    /*constructors*/((("Factory_AlphaStrong_0__BOSS_93","_Factory_AlphaStrong_0__BOSS_93"),())) )) \
  (( /*class*/(Pythia8)(AlphaEM),    /*constructors*/((("Factory_AlphaEM_0__BOSS_94","_Factory_AlphaEM_0__BOSS_94"),())) )) \
  (( /*class*/(Pythia8)(Parm),    /*constructors*/((("Factory_Parm_0__BOSS_95","_Factory_Parm_0__BOSS_95"),(std::string, double, bool, bool, double, double))) ((("Factory_Parm_1__BOSS_96","_Factory_Parm_1__BOSS_96"),(std::string, double, bool, bool, double))) ((("Factory_Parm_2__BOSS_97","_Factory_Parm_2__BOSS_97"),(std::string, double, bool, bool))) ((("Factory_Parm_3__BOSS_98","_Factory_Parm_3__BOSS_98"),(std::string, double, bool))) ((("Factory_Parm_4__BOSS_99","_Factory_Parm_4__BOSS_99"),(std::string, double))) ((("Factory_Parm_5__BOSS_100","_Factory_Parm_5__BOSS_100"),(std::string))) ((("Factory_Parm_6__BOSS_101","_Factory_Parm_6__BOSS_101"),())) )) \
  (( /*class*/(Pythia8)(Settings),    /*constructors*/((("Factory_Settings_0__BOSS_102","_Factory_Settings_0__BOSS_102"),())) )) \
  (( /*class*/(Pythia8)(Rndm),    /*constructors*/((("Factory_Rndm_0__BOSS_103","_Factory_Rndm_0__BOSS_103"),())) ((("Factory_Rndm_1__BOSS_104","_Factory_Rndm_1__BOSS_104"),(int))) )) \
  (( /*class*/(Pythia8)(Info),    /*constructors*/((("Factory_Info_0__BOSS_105","_Factory_Info_0__BOSS_105"),())) ((("Factory_Info_1__BOSS_106","_Factory_Info_1__BOSS_106"),(bool))) )) \
  (( /*class*/(Pythia8)(Logger),    /*constructors*/((("Factory_Logger_0__BOSS_107","_Factory_Logger_0__BOSS_107"),())) )) \
  (( /*class*/(Pythia8)(Vec4),    /*constructors*/((("Factory_Vec4_0__BOSS_108","_Factory_Vec4_0__BOSS_108"),(double, double, double, double))) ((("Factory_Vec4_1__BOSS_109","_Factory_Vec4_1__BOSS_109"),(double, double, double))) ((("Factory_Vec4_2__BOSS_110","_Factory_Vec4_2__BOSS_110"),(double, double))) ((("Factory_Vec4_3__BOSS_111","_Factory_Vec4_3__BOSS_111"),(double))) ((("Factory_Vec4_4__BOSS_112","_Factory_Vec4_4__BOSS_112"),())) )) \
  (( /*class*/(Pythia8)(Hist),    /*constructors*/((("Factory_Hist_0__BOSS_113","_Factory_Hist_0__BOSS_113"),())) ((("Factory_Hist_1__BOSS_114","_Factory_Hist_1__BOSS_114"),(std::string, int, double, double, bool, bool))) ((("Factory_Hist_2__BOSS_115","_Factory_Hist_2__BOSS_115"),(std::string, int, double, double, bool))) ((("Factory_Hist_3__BOSS_116","_Factory_Hist_3__BOSS_116"),(std::string, int, double, double))) ((("Factory_Hist_4__BOSS_117","_Factory_Hist_4__BOSS_117"),(std::string, int, double))) ((("Factory_Hist_5__BOSS_118","_Factory_Hist_5__BOSS_118"),(std::string, int))) ((("Factory_Hist_6__BOSS_119","_Factory_Hist_6__BOSS_119"),(std::string))) ((("Factory_Hist_7__BOSS_120","_Factory_Hist_7__BOSS_120"),(std::string, const my_ns::Pythia8::Hist&))) )) \

// If the default version has been loaded, set it as default.
#if ALREADY_LOADED(CAT_3(BACKENDNAME,_,CAT(Default_,BACKENDNAME)))
  SET_DEFAULT_VERSION_FOR_LOADING_TYPES(BACKENDNAME,SAFE_VERSION,CAT(Default_,BACKENDNAME))
#endif

// Undefine macros to avoid conflict with other backends.
#include "gambit/Backends/backend_undefs.hpp"
 
#endif

#endif /* __loaded_types_Pythia_8_312_hpp__ */
