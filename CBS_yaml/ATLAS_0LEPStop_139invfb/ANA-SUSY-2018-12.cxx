#include "SimpleAnalysisFramework/AnalysisClass.h"

DefineAnalysis(ttbarMET0L2018)

void ttbarMET0L2018::Init() {
  //Define Signal Regions
  addRegions( { "SRA", "SRATT", "SRATW", "SRAT0" });
  addRegions( { "SRB", "SRBTT", "SRBTW", "SRBT0" });
  addRegions( { "SRC", "SRC1", "SRC2", "SRC3", "SRC4", "SRC5" });
  addRegions( { "SRD", "SRD0", "SRD1", "SRD2" });
  
  //Define Cutflow steps as regions
  addRegions( { "Cutflow_SRATT_0_LeptonVeto",
		"Cutflow_SRATT_1_BadJetVeto",
		"Cutflow_SRATT_2_Met",
		"Cutflow_SRATT_3_NJets",
		"Cutflow_SRATT_4_JetPt1",
		"Cutflow_SRATT_5_JetPt3",
		"Cutflow_SRATT_6_NBJets1",
		"Cutflow_SRATT_7_NBJets2",
		"Cutflow_SRATT_8_MetSig14",
		"Cutflow_SRATT_9_MetSig25",
		"Cutflow_SRATT_10_MtBMin",
		"Cutflow_SRATT_11_NAntiKt12",
		"Cutflow_SRATT_12_AntiKt12M0",
		"Cutflow_SRATT_13_AntiKt12M1",
		"Cutflow_SRATT_14_AntiKt8M0",
		"Cutflow_SRATT_15_MT2Chi2",
		"Cutflow_SRATT_16_DRBB",
		"Cutflow_SRATT_17_NBClose0",
		"Cutflow_SRATT_18_NBClose1",
		"Cutflow_SRATT_19_dPhiJetMetMin4"
    });
  
  addRegions( { "Cutflow_SRBTW_0_LeptonVeto",
		"Cutflow_SRBTW_1_BadJetVeto",
		"Cutflow_SRBTW_2_Met",
		"Cutflow_SRBTW_3_NJets",
		"Cutflow_SRBTW_4_JetPt1",
		"Cutflow_SRBTW_5_JetPt3",
		"Cutflow_SRBTW_6_NBJets1",
		"Cutflow_SRBTW_7_NBJets2",
		"Cutflow_SRBTW_8_MetSig14",
		"Cutflow_SRBTW_9_MtBMin",
		"Cutflow_SRBTW_10_MtBMax",
		"Cutflow_SRBTW_11_NAntiKt12",
		"Cutflow_SRBTW_12_AntiKt12M0",
		"Cutflow_SRBTW_13_AntiKt12M1",
		"Cutflow_SRBTW_14_MT2Chi2",
		"Cutflow_SRBTW_15_DRBB",
		"Cutflow_SRBTW_16_dPhiJetMetMin4"
    });
  
  addRegions( { "Cutflow_SRC_0_LeptonVeto",
		"Cutflow_SRC_1_BadJetVeto",
		"Cutflow_SRC_2_Met",
		"Cutflow_SRC_3_NJets",
		"Cutflow_SRC_4_JetPt1",
		"Cutflow_SRC_5_JetPt3_40",
		"Cutflow_SRC_6_NBJets1",
		"Cutflow_SRC_7_NBJets2",
		"Cutflow_SRC_8_MetSig5",
		"Cutflow_SRC_9_BJetPt0",
		"Cutflow_SRC_10_JetPt3_50",
		"Cutflow_SRC_11_ISRPt",
		"Cutflow_SRC_12_DPhiISRMet",
		"Cutflow_SRC_13_MS",
		"Cutflow_SRC_14_dPhiJetMetMin2",
		"Cutflow_SRC_15_RISR",
    });
  
  addRegions( { "Cutflow_SRD_0_LeptonVeto",
		"Cutflow_SRD_1_BadJetVeto",
		"Cutflow_SRD_2_Met",
		"Cutflow_SRD_3_LeadNonBJetPt",
		"Cutflow_SRD_4_LeadNonBJetDPhiMet",
		"Cutflow_SRD_5_MetSigHt8",
		"Cutflow_SRD_6_MetSigHt22",
		"Cutflow_SRD0_7_NBJets",
		"Cutflow_SRD1_7_NBJets",
		"Cutflow_SRD2_7_NBJets",
		"Cutflow_SRD0_8_MetDPhiJets",
		"Cutflow_SRD0_9_MetSigHt26",
		"Cutflow_SRD1_8_BJet1Eta",
		"Cutflow_SRD1_9_BJet1DPhiNonBJet",
		"Cutflow_SRD2_8_BJet1Pt",
		"Cutflow_SRD2_9_BJet2Eta",
		"Cutflow_SRD2_10_BJet1DPhiNonBJet",
		"Cutflow_SRD2_11_BJet2DPhiNonBJet"
    });

  //Define N-1 Histograms
  addHistogram("NAntiKt12_SRA",10,0,10);
  addHistogram("NAntiKt12_SRB",10,0,10);
  addHistogram("AntiKt12M0_SRA",20,0,400);
  addHistogram("AntiKt12M0_SRB",20,0,400);
  addHistogram("AntiKt12M1_SRA",20,0,400);
  addHistogram("AntiKt12M1_SRB",20,0,400);
  addHistogram("AntiKt8M0_SRA",20,0,400);
  addHistogram("NJets_SRA",20,0,20);
  addHistogram("NJets_SRB",20,0,20);
  addHistogram("NJets_SRC",20,0,20);
  addHistogram("NJets_SRD",20,0,20);
  addHistogram("NJets_SRD0",20,0,20);
  addHistogram("NJets_SRD1",20,0,20);
  addHistogram("NJets_SRD2",20,0,20);
  addHistogram("NJetsCA_SRC",20,0,20);
  addHistogram("NBJets_SRA",10,0,10);
  addHistogram("NBJets_SRB",10,0,10);
  addHistogram("NBJets_SRC",10,0,10);
  addHistogram("NBJets_SRD",10,0,10);
  addHistogram("NBJets_SRD0",10,0,10);
  addHistogram("NBJets_SRD1",10,0,10);
  addHistogram("NBJets_SRD2",10,0,10);
  addHistogram("NBJetsCA_SRC",10,0,10);
  addHistogram("Met_SRA",20,200,1200);
  addHistogram("Met_SRB",20,200,1200);
  addHistogram("Met_SRC",10,200,1200);
  addHistogram("Met_SRD",20,0.,1000);
  addHistogram("Met_SRD0",10,200,1200);
  addHistogram("Met_SRD1",10,200,1200);
  addHistogram("Met_SRD2",10,200,1200);
  addHistogram("MetSig_SRA",20,0,40);
  addHistogram("MetSig_SRB",20,0,40);
  addHistogram("MetSig_SRC",10,0,40);
  addHistogram("MetSigHt_SRD",20,0,40);
  addHistogram("MetSigHt_SRD0",10,20,40);
  addHistogram("MetSigHt_SRD1",10,20,40);
  addHistogram("MetSigHt_SRD2",10,20,40);
  addHistogram("JetPt0_SRA",10,0,800);
  addHistogram("JetPt1_SRA",10,0,800);
  addHistogram("JetPt2_SRA",10,0,400);
  addHistogram("JetPt3_SRA",10,0,400);
  addHistogram("JetPt0_SRB",10,0,800);
  addHistogram("JetPt1_SRB",10,0,800);
  addHistogram("JetPt2_SRB",10,0,400);
  addHistogram("JetPt3_SRB",10,0,400);
  addHistogram("JetPt0_SRC",10,0,1600);
  addHistogram("JetPt1_SRC",10,0,800);
  addHistogram("JetPt2_SRC",10,0,400);
  addHistogram("JetPt3_40_SRC",10,0,400);
  addHistogram("JetPt3_50_SRC",10,0,400);
  addHistogram("MtBMin_SRA",10,0,1000);
  addHistogram("MtBMin_SRB",10,0,1000);
  addHistogram("MtBMax_SRB",10,0,1000);
  addHistogram("MT2Chi2_SRA",24,0,1200);
  addHistogram("MT2Chi2_SRB",24,0,1200);
  addHistogram("DRBB_SRA",10,0,4);
  addHistogram("DRBB_SRB",10,0,4);
  addHistogram("NCloseByBJets12Leading_SRA",5,0,5);
  addHistogram("NCloseByBJets12Subleading_SRA",5,0,5);
  addHistogram("DPhiJetMetMin4_SRA",20,0,4);
  addHistogram("DPhiJetMetMin4_SRB",20,0,4);
  addHistogram("DPhiJetMetMin4_SRD",20,0,4);
  addHistogram("DPhiJetMetMin4_SRD0",20,0,4);
  addHistogram("DPhiJetMetMin4_SRD1",20,0,4);
  addHistogram("DPhiJetMetMin4_SRD2",5,0,4);
  addHistogram("DPhiJetMetMin2_SRC",10,0,4);
  addHistogram("DPhiMetISR_SRC",25,0,5);
  addHistogram("RISR_SRC",24,0,1.2);
  addHistogram("MS_SRC",20,0,1000);
  addHistogram("PTISR_SRC",20,0,2000);
  addHistogram("PtB1_SRC",20,0,400);
  addHistogram("LeadBJetPt_SRD1",20,0,1000);
  addHistogram("LeadBJetPt_SRD2",5,0,1000);
  addHistogram("LeadNonBJetPt_SRD",20,0,1000);
  addHistogram("LeadNonBJetPt_SRD0",20,0,1000);
  addHistogram("LeadNonBJetDPhiMet_SRD",10,2.0,4.0);
  addHistogram("LeadNonBJetDPhiMet_SRD0",10,2.0,4.0);
  addHistogram("LeadNonBJetDPhiMet_SRD1",10,2.0,4.0);
  addHistogram("LeadNonBJetDPhiMet_SRD2",10,2.0,4.0);
  addHistogram("LeadNonBJetPt_SRD1",20,0,1000);
  addHistogram("LeadNonBJetPt_SRD2",5,0,1000);
  addHistogram("LeadBJetDPhiNonBJet_SRD1",20,0,4.0);
  addHistogram("LeadBJetDPhiNonBJet_SRD2",5,0,4.0);
  addHistogram("SubleadBJetDPhiNonBJet_SRD2",5,0,4.0);
  addHistogram("SubleadBJetEta_SRD2",6,-3.0,3.0);
  
  LabRecoFrame* LAB = m_RF_helper.addLabFrame("LAB");
  DecayRecoFrame* CM = m_RF_helper.addDecayFrame("CM");
  DecayRecoFrame* S = m_RF_helper.addDecayFrame("S");
  VisibleRecoFrame* ISR = m_RF_helper.addVisibleFrame("ISR");
  VisibleRecoFrame* V = m_RF_helper.addVisibleFrame("V");
  InvisibleRecoFrame* I = m_RF_helper.addInvisibleFrame("I");

  LAB->SetChildFrame(*CM);
  CM->AddChildFrame(*ISR);
  CM->AddChildFrame(*S);
  S->AddChildFrame(*V);
  S->AddChildFrame(*I);

  LAB->InitializeTree();

  InvisibleGroup* INV = m_RF_helper.addInvisibleGroup("INV");
  INV->AddFrame(*I);
  CombinatoricGroup* VIS = m_RF_helper.addCombinatoricGroup("VIS");
  VIS->AddFrame(*ISR);
  VIS->SetNElementsForFrame(*ISR,1,false);
  VIS->AddFrame(*V);
  VIS->SetNElementsForFrame(*V,0,false);

  // set the invisible system mass to zero
  InvisibleJigsaw* InvMass = m_RF_helper.addInvisibleJigsaw("InvMass",kSetMass);
  INV->AddJigsaw(*InvMass);

  // define the rule for partitioning objects between "ISR" and "V"
  MinMassesCombJigsaw* SplitVis = m_RF_helper.addCombinatoricJigsaw("CombPPJigsaw", kMinMasses);
  VIS->AddJigsaw(*SplitVis);
  // "0" group (ISR)
  SplitVis->AddFrame(*ISR, 0);
  // "1" group (V + I)
  SplitVis->AddFrame(*V,1);
  SplitVis->AddFrame(*I,1);

  LAB->InitializeAnalysis();
}

void ttbarMET0L2018::ProcessEvent(AnalysisEvent *event) {
  // Assume PrimVtx for Truth
  // No Trigger for Truth
  
  // Get Baseline Objects
  auto baseJets = event->getJets(20., 2.8, JVT59Jet);
  auto baseElectrons = event->getElectrons(4.5, 2.47, ELooseBLLH | EZ05mm);
  auto baseMuons = event->getMuons(4.0, 2.7, MuMedium | MuZ05mm);
  
  // Get Truth Met + Object-Based MetSig
  auto metVec = event->getMET();
  float Met = metVec.Pt();
  double MetSig = event->getMETSignificance();

  // Overlap Removal
  auto radiusCalcLepton = [] (const AnalysisObject& lepton, const AnalysisObject& ) {return std::min(0.4, 0.04 + 10/lepton.Pt());};
  auto muJetSpecial = [] (const AnalysisObject& jet, const AnalysisObject& muon) {
    if (jet.pass(NOT(BTag77MV2c10)) && (jet.pass(LessThan3Tracks) || muon.Pt()/jet.Pt()>0.5)) return 0.2;
    else return 0.;
  };
  baseMuons = overlapRemoval(baseMuons, baseElectrons, 0.01, NOT(MuCaloTaggedOnly));
  baseElectrons = overlapRemoval(baseElectrons, baseMuons, 0.01);
  
  baseJets = overlapRemoval(baseJets, baseElectrons, 0.2, NOT(BTag77MV2c10));
  baseElectrons = overlapRemoval(baseElectrons, baseJets, 0.2);
  
  baseJets = overlapRemoval(baseJets, baseMuons, muJetSpecial, NOT(BTag77MV2c10));
  baseMuons = overlapRemoval(baseMuons, baseJets, 0.2);
  
  baseMuons = overlapRemoval(baseMuons, baseJets, radiusCalcLepton);
  baseElectrons = overlapRemoval(baseElectrons, baseJets, radiusCalcLepton);

  // After OR Baseline Leptons
  int nBaseElectrons = countObjects(baseElectrons, 4.5, 2.47);
  int nBaseMuons = countObjects(baseMuons, 4.0, 2.7);
  int nLep = nBaseElectrons + nBaseMuons;
  auto baseLeptons = baseElectrons + baseMuons;

  // Get signal jets
  auto signalJets = filterObjects(baseJets, 20, 2.8, JVT59Jet);
  int nSignalJets = countObjects(signalJets, 20, 2.8);
  auto nonBJets = filterObjects(signalJets, 20, 2.8, NOT(BTag77MV2c10));
  int nNonBJets = countObjects(nonBJets, 20, 2.8);
  auto signalBJets = filterObjects(signalJets, 20, 2.5, BTag77MV2c10);
  int nBJets = countObjects(signalBJets, 20, 2.5);

  // Check for bad jets after Overlap Removal
  int nBadJets = countObjects(signalJets, 20, 4.5, NOT(LooseBadJet));
  
  // DRBB
  float DRBB = 0;
  if (nBJets > 1) DRBB = signalBJets[1].DeltaR(signalBJets[0]);

  // dPhiJetMet
  double dPhiJetMetMin2 = 0;
  double dPhiJetMetMin3 = 0;
  double dPhiJetMetMin4 = 0;
  if (nSignalJets >= 2) {
    dPhiJetMetMin2 = std::min(fabs(metVec.DeltaPhi(signalJets[0])), fabs(metVec.DeltaPhi(signalJets[1])));
    if (nSignalJets>=3) {
      dPhiJetMetMin3 = std::min(dPhiJetMetMin2, fabs(metVec.DeltaPhi(signalJets[2])));
      if (nSignalJets>=4) {
	dPhiJetMetMin4 = std::min(dPhiJetMetMin3, fabs(metVec.DeltaPhi(signalJets[3])));
      }
    }
  }
  
  // Reclustering
  float AntiKt8M_0 = 0;
  //  float AntiKt8M_1 = 0;
  float AntiKt12M_0 = 0;
  float AntiKt12M_1 = 0;
  auto fatJetsR8 = reclusterJets(signalJets, 0.8, 20., 0.2, 0.00);
  int nFatJetsR8 = countObjects(fatJetsR8, 20, 2.8);
  auto fatJetsR12 = reclusterJets(signalJets, 1.2, 20., 0.2, 0.00);
  int nFatJetsR12 = countObjects(fatJetsR12, 20, 2.8);
  if (nFatJetsR8 > 0) AntiKt8M_0 = fatJetsR8[0].M();
  //if (nFatJetsR8 > 1) AntiKt8M_1 = fatJetsR8[1].M();
  if (nFatJetsR12 > 0) AntiKt12M_0 = fatJetsR12[0].M();
  if (nFatJetsR12 > 1) AntiKt12M_1 = fatJetsR12[1].M();
  

  // Tau veto (Here for bookeeping. The LessOrEq4Tracks flag doesn't actually reject anything)
  float MtTauCand = -1;
  auto tauCands = filterObjects(signalJets, 20, 2.5, LessOrEq4Tracks);
  for (const auto& jet : tauCands) {
    if (jet.DeltaPhi(metVec) < M_PI/5.) {
      MtTauCand = calcMT(jet, metVec);
    }
    if (MtTauCand > 0) break;
  }
  
    
  // Close-by b-jets and MtBMets
  int NCloseByBJets12Leading = 0;
  int NCloseByBJets12Subleading = 0;
  float MtBMin = 0;
  float MtBMax = 0;
  double dPhi_min = 1000.;
  double dPhi_max = 0.;
  if (nBJets >= 2) {
    for (const auto& jet : signalBJets) {
      double dphi = fabs(metVec.DeltaPhi(jet));
      if (dphi < dPhi_min) {
	dPhi_min = dphi;
	MtBMin = calcMT(jet, metVec);
      }
      if (dphi > dPhi_max) {
	dPhi_max = dphi;
	MtBMax = calcMT(jet, metVec);
      }
      if (nFatJetsR12 > 0 && jet.DeltaR(fatJetsR12[0]) <= 1.2)
	NCloseByBJets12Leading++;
      if (nFatJetsR12 > 1 && jet.DeltaR(fatJetsR12[1]) <= 1.2)
	NCloseByBJets12Subleading++;
    }
  }
  
  //Chi2 method (Same as stop0L2015.cxx)
  float realWMass = 80.385;
  float realTopMass = 173.210;
  double Chi2min = DBL_MAX;
  int W1j1_low = -1, W1j2_low = -1, W2j1_low = -1, W2j2_low = -1, b1_low = -1, b2_low = -1;
  double MT2Chi2 = 0;
  if (nSignalJets >= 4 && nBJets >= 2 && nNonBJets >= 2) {
    for (int W1j1 = 0; W1j1 < (int) nNonBJets; W1j1++) { 
      for (int W2j1 = 0; W2j1 < (int) nNonBJets; W2j1++) {
	if (W2j1 == W1j1) continue; 
	for (int b1 = 0; b1 < (int) nBJets; b1++) {
	  for (int b2 = 0; b2 < (int) nBJets; b2++) {
	    if (b2 == b1) continue;
	    double chi21, chi22, mW1, mW2, mt1, mt2;	    
	    if (W2j1 > W1j1) {
	      mW1 = nonBJets[W1j1].M();
	      mW2 = nonBJets[W2j1].M();
	      mt1 = (nonBJets[W1j1] + signalBJets[b1]).M();
	      mt2 = (nonBJets[W2j1] + signalBJets[b2]).M();
	      chi21 = (mW1 - realWMass) * (mW1 - realWMass) / realWMass + (mt1 - realTopMass) * (mt1 - realTopMass) / realTopMass;
	      chi22 = (mW2 - realWMass) * (mW2 - realWMass) / realWMass + (mt2 - realTopMass) * (mt2 - realTopMass) / realTopMass;
	      if (Chi2min > (chi21 + chi22)) {
		Chi2min = chi21 + chi22;
		if (chi21 < chi22) {
		  W1j1_low = W1j1;
		  W1j2_low = -1;
		  W2j1_low = W2j1;
		  W2j2_low = -1;
		  b1_low = b1;
		  b2_low = b2;
		}
		else {
		  W2j1_low = W1j1;
		  W2j2_low = -1;
		  W1j1_low = W2j1;
		  W1j2_low = -1;
		  b2_low = b1;
		  b1_low = b2;
		}
	      }
	    }
	    if (nNonBJets < 3)
	      continue;
	    for (int W1j2 = W1j1 + 1; W1j2 < nNonBJets; W1j2++) {
	      if (W1j2 == W2j1) continue;
	      //try bll,bl top candidates
	      mW1 = (nonBJets[W1j1] + nonBJets[W1j2]).M();
	      mW2 = (nonBJets[W2j1]).M();
	      mt1 = (nonBJets[W1j1] + nonBJets[W1j2] + signalBJets[b1]).M();
	      mt2 = (nonBJets[W2j1] + signalBJets[b2]).M();
	      chi21 = (mW1 - realWMass) * (mW1 - realWMass) / realWMass + (mt1 - realTopMass) * (mt1 - realTopMass) / realTopMass;
	      chi22 = (mW2 - realWMass) * (mW2 - realWMass) / realWMass + (mt2 - realTopMass) * (mt2 - realTopMass) / realTopMass;
	      if (Chi2min > (chi21 + chi22)) {
		Chi2min = chi21 + chi22;
		if (chi21 < chi22) {
		  W1j1_low = W1j1;
		  W1j2_low = W1j2;
		  W2j1_low = W2j1;
		  W2j2_low = -1;
		  b1_low = b1;
		  b2_low = b2;
		}
		else {
		  W2j1_low = W1j1;
		  W2j2_low = W1j2;
		  W1j1_low = W2j1;
		  W1j2_low = -1;
		  b2_low = b1;
		  b1_low = b2;
		}
	      }
	      if (nNonBJets < 4) continue;
	      //try bll, bll top candidates
	      for (int W2j2 = W2j1 + 1; W2j2 < (int) nNonBJets; W2j2++) {
		if ((W2j2 == W1j1) || (W2j2 == W1j2)) continue;
		if (W2j1 < W1j1) continue; //runtime reasons, we don't want combinations checked twice <--------------------This line should be added
		mW1 = (nonBJets[W1j1] + nonBJets[W1j2]).M();
		mW2 = (nonBJets[W2j1] + nonBJets[W2j2]).M();
		mt1 = (nonBJets[W1j1] + nonBJets[W1j2] + signalBJets[b1]).M();
		mt2 = (nonBJets[W2j1] + nonBJets[W2j2] + signalBJets[b2]).M();
		chi21 = (mW1 - realWMass) * (mW1 - realWMass) / realWMass + (mt1 - realTopMass) * (mt1 - realTopMass) / realTopMass;
		chi22 = (mW2 - realWMass) * (mW2 - realWMass) / realWMass + (mt2 - realTopMass) * (mt2 - realTopMass) / realTopMass;
		if (Chi2min > (chi21 + chi22)) {
		  Chi2min = chi21 + chi22;
		  if (chi21 < chi22) {
		    W1j1_low = W1j1;
		    W1j2_low = W1j2;
		    W2j1_low = W2j1;
		    W2j2_low = W2j2;
		    b1_low = b1;
		    b2_low = b2;
		  }
		  else {
		    W2j1_low = W1j1;
		    W2j2_low = W1j2;
		    W1j1_low = W2j1;
		    W1j2_low = W2j2;
		    b2_low = b1;
		    b1_low = b2;
		  }
		}
	      }
	    }
	  }
	}
      }
    }
    
    AnalysisObject WCand0 = nonBJets[W1j1_low];
    if (W1j2_low != -1) WCand0 += nonBJets[W1j2_low];
    AnalysisObject topCand0 = WCand0 + signalBJets[b1_low];
    
    AnalysisObject WCand1 = nonBJets[W2j1_low];
    if (W2j2_low != -1) WCand1 += nonBJets[W2j2_low];
    AnalysisObject topCand1 = WCand1 + signalBJets[b2_low];
    
    AnalysisObject top0Chi2 = topCand0;
    AnalysisObject top1Chi2 = topCand1;

    double Energy0 = sqrt(173.210 * 173.210 + top0Chi2.Pt() * top0Chi2.Pt());
    double Energy1 = sqrt(173.210 * 173.210 + top1Chi2.Pt() * top1Chi2.Pt());
    AnalysisObject top0(top0Chi2.Px(), top0Chi2.Py(), 0, Energy0, 0, 0, COMBINED, 0, 0);
    AnalysisObject top1(top1Chi2.Px(), top1Chi2.Py(), 0, Energy1, 0, 0, COMBINED, 0, 0);
    MT2Chi2 = calcMT2(top0, top1, metVec);
  }
     
  // RestFrames stuff
  double CA_PTISR=0;
  double CA_MS=0;
  double CA_NbV=0;
  double CA_NjV=0;
  double CA_RISR=0;
  double CA_dphiISRI=0;
  double CA_pTjV4=0;
  double CA_pTbV1=0;
  
  LabRecoFrame* LAB = m_RF_helper.getLabFrame("LAB");
  InvisibleGroup* INV = m_RF_helper.getInvisibleGroup("INV");
  CombinatoricGroup* VIS = m_RF_helper.getCombinatoricGroup("VIS");
  
  LAB->ClearEvent();
  std::vector<RFKey> jetID;
  
  // use transverse view of jet 4-vectors
  for(const auto & jet : signalJets)
    jetID.push_back(VIS->AddLabFrameFourVector(jet.transFourVect()));
  
  INV->SetLabFrameThreeVector(metVec.Vect());
  // std::cout<<"Something happens below that spits out a warning."<<std::endl;

  int m_NjV(0);
  int m_NbV(0);
  int m_NbISR(0);
  double m_pTjV4(0.);
  double m_pTbV1(0);
  double m_PTISR(0.);
  double m_MS(0.);
  double m_RISR(0.);
  double m_dphiISRI(0.);
  

  if (nSignalJets>0) {
    if(!LAB->AnalyzeEvent()) std::cout << "Something went wrong... " << nSignalJets<< std::endl;
  
    DecayRecoFrame* CM = m_RF_helper.getDecayFrame("CM");
    DecayRecoFrame* S = m_RF_helper.getDecayFrame("S");
    VisibleRecoFrame* ISR = m_RF_helper.getVisibleFrame("ISR");
    VisibleRecoFrame* V = m_RF_helper.getVisibleFrame("V");
    InvisibleRecoFrame* I = m_RF_helper.getInvisibleFrame("I");
  
    for(int i = 0; i < nSignalJets; i++) {
      if (VIS->GetFrame(jetID[i]) == *V) { // sparticle group
	m_NjV++;
	if (m_NjV == 4) m_pTjV4 = signalJets[i].Pt();
	if (signalJets[i].pass(BTag77MV2c10) && fabs(signalJets[i].Eta())<2.5) {
	  m_NbV++;
	  if (m_NbV == 1) m_pTbV1 = signalJets[i].Pt();
	}
      } else {
	if (signalJets[i].pass(BTag77MV2c10) && fabs(signalJets[i].Eta())<2.5)
	  m_NbISR++;
      }
    }
  
    // need at least one jet associated with MET-side of event
    if(m_NjV >= 1)
      {
	TVector3 vP_ISR = ISR->GetFourVector(*CM).Vect();
	TVector3 vP_I = I->GetFourVector(*CM).Vect();
      
	m_PTISR = vP_ISR.Mag();
	m_RISR = fabs(vP_I.Dot(vP_ISR.Unit())) / m_PTISR;
      
	m_MS = S->GetMass();
      
	m_dphiISRI = fabs(vP_ISR.DeltaPhi(vP_I));
      
	CA_PTISR=m_PTISR;
	CA_MS=m_MS;
	CA_NbV=m_NbV;
	CA_NjV=m_NjV;
	CA_RISR=m_RISR;
	CA_dphiISRI=m_dphiISRI;
	CA_pTjV4=m_pTjV4;
	CA_pTbV1=m_pTbV1;
      }
  }

  // Sum Pt Vars
  double Ht = sumObjectsPt(signalJets);
  double HtSig = Met / TMath::Sqrt(Ht);
  //  double sumTagJetPt = sumObjectsPt(signalBJets, 2);

  /////////////////////////////////////
  // End Variable calculations

  //////////////////////////////////////
  // Region Cuts
  bool pre1B4J0L = Met > 250 && nLep == 0 && nSignalJets >= 4 && nBJets >= 1 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && dPhiJetMetMin2>0.4;
  bool pre2B4J0L = pre1B4J0L && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MetSig > 5 && MtBMin > 50 && MtTauCand < 0;
  bool pre2B4J0Ltight = pre2B4J0L && MtBMin > 200;
  bool pre2B4J0LtightTT = pre2B4J0Ltight && nFatJetsR12>=2 && AntiKt12M_0>120. && AntiKt12M_1>120;
  bool pre2B4J0LtightTW = pre2B4J0Ltight && nFatJetsR12>=2 && AntiKt12M_0>120. && AntiKt12M_1>60 && AntiKt12M_1<120;
  bool pre2B4J0LtightT0 = pre2B4J0Ltight && nFatJetsR12>=2 && AntiKt12M_0>120. && AntiKt12M_1>0 && AntiKt12M_1<60;
  
  bool SRA = pre2B4J0Ltight && MT2Chi2 > 450 && nFatJetsR12>=2 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && MetSig > 25.00 && NCloseByBJets12Leading >= 1;
  bool SRATT = pre2B4J0LtightTT && MT2Chi2 > 450 && AntiKt8M_0 > 60.00 && MetSig > 25.00 && NCloseByBJets12Leading >= 1 && NCloseByBJets12Subleading >= 1 && DRBB > 1.00;
  bool SRATW = pre2B4J0LtightTW && MT2Chi2 > 450 && AntiKt8M_0 > 60.00 && MetSig > 25.00 && NCloseByBJets12Leading >= 1;
  bool SRAT0 = pre2B4J0LtightT0 && MT2Chi2 > 450 && AntiKt8M_0 > 60.00 && MetSig > 25.00 && NCloseByBJets12Leading >= 1;
  
  bool SRB = pre2B4J0Ltight && MtBMax>200 && DRBB>1.4 && nFatJetsR12>=2 && AntiKt12M_0>120 && MT2Chi2<450 && MetSig>14;
  bool SRBTT = SRB && nFatJetsR12>=2 && AntiKt12M_0>120. && AntiKt12M_1>120;
  bool SRBTW = SRB && nFatJetsR12>=2 && AntiKt12M_0>120. && AntiKt12M_1>60 && AntiKt12M_1<120;
  bool SRBT0 = SRB && nFatJetsR12>=2 && AntiKt12M_0>120. && AntiKt12M_1>0 && AntiKt12M_1<60;

  if (SRA) accept("SRA");
  if (SRATT) accept("SRATT");
  if (SRATW) accept("SRATW");
  if (SRAT0) accept("SRAT0");
  if (SRB) accept("SRB");
  if (SRBTT) accept("SRBTT");
  if (SRBTW) accept("SRBTW");
  if (SRBT0) accept("SRBT0");
  
  bool SRC = pre1B4J0L && CA_NbV >= 2 && MetSig > 5 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50;
  if ( SRC ) accept("SRC");
  if ( SRC && CA_RISR >= 0.30 && CA_RISR <= 0.4) accept("SRC1");
  if ( SRC && CA_RISR >= 0.4 && CA_RISR <= 0.5) accept("SRC2");
  if ( SRC && CA_RISR >= 0.5 && CA_RISR <= 0.6) accept("SRC3");
  if ( SRC && CA_RISR >= 0.6 && CA_RISR <= 0.7) accept("SRC4");
  if ( SRC && CA_RISR >= 0.7) accept("SRC5");

  bool SRDLoose = nLep == 0 && nBadJets == 0 && Met > 250 && nonBJets.size() > 0 && nonBJets.size() > 0 && nonBJets[0].Pt()>250 && nonBJets[0].DeltaR(metVec) > 2.4 && HtSig > 22;
  bool SRD0 = SRDLoose && nBJets == 0 && dPhiJetMetMin4>0.4 && HtSig > 26;
  bool SRD1 = SRDLoose && nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.0 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2;
  bool SRD2 = SRDLoose && nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6;
  bool SRD = SRD0 || SRD1 || SRD2;

  if ( SRD ) accept("SRD");
  if ( SRD0 ) accept("SRD0");
  if ( SRD1 ) accept("SRD1");
  if ( SRD2 ) accept("SRD2");

  /////////////////////////////////////////
  /////////////////////////////////////////
  // N-1 Plots

  //////////////////////////////////
  // SRA (Note the Leading top mass cut. Really, this is a SRATX region.)
  // Cut String: Met > 250 && nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MT2Chi2 > 450 && nFatJetsR12>=2 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && MetSig > 25.00 && NCloseByBJets12Leading >= 1
  
  // First fill any hists that don't get explicitly cut in SRA (full cut string)
  if (Met > 250 && nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MT2Chi2 > 450 && nFatJetsR12>=2 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && MetSig > 25.00 && NCloseByBJets12Leading >= 1) {
    fill("AntiKt12M1_SRA",AntiKt12M_1);
    fill("DRBB_SRA",DRBB);
    fill("NCloseByBJets12Subleading_SRA",NCloseByBJets12Subleading);
  }
  // Remove Leading AntiKt12 Fat Jet Mass cut, but still ask for 2 fat jets (SRATX->SRA)
  if (Met > 250 && nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MT2Chi2 > 450 && nFatJetsR12>=2 && MetSig > 25.00 && NCloseByBJets12Leading >= 1 && AntiKt8M_0 > 60.00) {
    fill("AntiKt12M0_SRA",AntiKt12M_0);
  }
  // Remove AntiKt8 Fat Jet cut
  if (Met > 250 && nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MT2Chi2 > 450 && nFatJetsR12>=2 && MetSig > 25.00 && NCloseByBJets12Leading >= 1 && AntiKt12M_0>120) {
    fill("AntiKt8M0_SRA",AntiKt8M_0);
  }
  // Remove NBJets cut
  if (Met > 250 && nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MT2Chi2 > 450 && nFatJetsR12>=2 && MetSig > 25.00 && NCloseByBJets12Leading >= 1 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00) {
    fill("NBJets_SRA",nBJets);
  }
  // Remove Met cut
  if (nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MT2Chi2 > 450 && nFatJetsR12>=2 && MetSig > 25.00 && NCloseByBJets12Leading >= 1 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && nBJets >= 2) { 
    fill("Met_SRA",Met);
  }
  // Remove MetSig cut
  if (nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MT2Chi2 > 450 && nFatJetsR12>=2 && NCloseByBJets12Leading >= 1 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && nBJets >= 2 && Met > 250 ) {
    fill("MetSig_SRA",MetSig);
  }
  // Remove NJets cut (Need to relax JetPt[3] and dphijetmetmin4 cuts since those are essentially a NJets>=4 cut)
  if (nLep == 0 && nSignalJets >= 3 && signalJets[1].Pt() > 80 && signalJets[2].Pt() > 40 && dPhiJetMetMin3 > 0.4 && MtBMin > 200 && MT2Chi2 > 450 && nFatJetsR12>=2 && NCloseByBJets12Leading >= 1 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && nBJets >= 2 && Met > 250 && MetSig > 25.00 ) {
    fill("NJets_SRA",nSignalJets);
  }
  // Remove JetPt3 cut. Note only pt req removed.
  if (nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[2].Pt() > 40 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MT2Chi2 > 450 && nFatJetsR12>=2 && NCloseByBJets12Leading >= 1 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && nBJets >= 2 && Met > 250 && MetSig > 25.00  ) {
    fill("JetPt3_SRA",signalJets[3].Pt());
  }
  // Remove JetPt2 cut. Since JetPt3>JetPt2 and the cut is the same on both, only JetPt0-1 pt cuts applied
  if (nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MT2Chi2 > 450 && nFatJetsR12>=2 && NCloseByBJets12Leading >= 1 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && nBJets >= 2 && Met > 250 && MetSig > 25.00 ) {
    fill("JetPt2_SRA",signalJets[2].Pt());
  }
  // Remove JetPt1. Note only pt req removed
  if (nLep == 0 && nSignalJets >= 4 && signalJets[0].Pt() > 80 && signalJets[3].Pt() > 40 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MT2Chi2 > 450 && nFatJetsR12>=2 && NCloseByBJets12Leading >= 1 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && nBJets >= 2 && Met > 250 && MetSig > 25.00) {
    fill("JetPt1_SRA",signalJets[1].Pt());
  }
  // Remove JetPt0 cut. Since JetPt0>JetPt1 and the cut is the same on both, only JetPt 2-3 applied
  if (nLep == 0 && nSignalJets >= 4 && signalJets[3].Pt() > 40 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MT2Chi2 > 450 && nFatJetsR12>=2 && NCloseByBJets12Leading >= 1 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && nBJets >= 2 && Met > 250 && MetSig > 25.00 ) {
    fill("JetPt0_SRA",signalJets[0].Pt());
  }
  // Remove Mt2Chi2 cut
  if (nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && nFatJetsR12>=2 && NCloseByBJets12Leading >= 1 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && nBJets >= 2 && Met > 250 && MetSig > 25.00) {
    fill("MT2Chi2_SRA",MT2Chi2);
  }
  // Remove DPhiJetMetMin4 cut
  if (nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && MtBMin > 200 && nFatJetsR12>=2 && NCloseByBJets12Leading >= 1 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && nBJets >= 2 && Met > 250 && MetSig > 25.00 && MT2Chi2 > 450 ) {
    fill("DPhiJetMetMin4_SRA",dPhiJetMetMin4);
  }
  // Remove MtBMin cut
  if (nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nFatJetsR12>=2 && NCloseByBJets12Leading >= 1 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && nBJets >= 2 && Met > 250 && MetSig > 25.00 && MT2Chi2 > 450 && dPhiJetMetMin4 > 0.4) {
    fill("MtBMin_SRA",MtBMin);
  }
  // Remove NAntiKt12 req
  if (nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && NCloseByBJets12Leading >= 1 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && nBJets >= 2 && Met > 250 && MetSig > 25.00 && MT2Chi2 > 450 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 ) {
    fill("NAntiKt12_SRA",nFatJetsR12);
  }
  // Remove NCloseByBJets12Leading cut
  if (nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && nBJets >= 2 && Met > 250 && MetSig > 25.00 && MT2Chi2 > 450 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && nFatJetsR12>=2) {
    fill("NCloseByBJets12Leading_SRA",NCloseByBJets12Leading);
  }

  //////////////////////
  // SRB
  // Cut String:  nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MtBMax>200 && DRBB>1.4 && nFatJetsR12>=2 && AntiKt12M_0>120 && MT2Chi2<450 && MetSig>14
  
  // First fill variables not explicitly cut in SRB (Just as SRA, this is really an SRBTX region)
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MtBMax>200 && DRBB>1.4 && nFatJetsR12>=2 && AntiKt12M_0>120 && MT2Chi2<450 && MetSig>14) {
    fill("AntiKt12M1_SRB",AntiKt12M_1);
  }
  // Remove Leading Antikt12 mass cut. While I'm at it, fill the 
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && nBJets >= 1 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MtBMax>200 && DRBB>1.4 && nFatJetsR12>=2 && MT2Chi2<450 && MetSig>14) {
    fill("AntiKt12M0_SRB",AntiKt12M_0);
  }
  // Remove NBJets cut (also remove DRBB since that is an implicit cut on NBJets)
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MtBMax>200 && nFatJetsR12>=2 && AntiKt12M_0>120 && MT2Chi2<450 && MetSig>14) {
    fill("NBJets_SRB",nBJets);
    // Take advantage and fill DRBB N-1 plot
    if (nBJets >= 2) {
      fill("DRBB_SRB",DRBB);
    }
  }
  // Remove Met cut
  if (nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MtBMax>200 && DRBB>1.4 && nFatJetsR12>=2 && AntiKt12M_0>120 && MT2Chi2<450 && MetSig>14) { 
    fill("Met_SRB",Met);
  }
  // Remove MetSig cut
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MtBMax>200 && DRBB>1.4 && nFatJetsR12>=2 && AntiKt12M_0>120 && MT2Chi2<450) {
    fill("MetSig_SRB",MetSig);
  }
  // Remove NJets cut (Need to relax JetPt[3] and dphijetmetmin4 cuts since those are essentially a NJets>=4 cut)
  if (nLep == 0 && Met > 250 && nSignalJets >= 3 && signalJets[1].Pt() > 80 && signalJets[2].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin3 > 0.4 && MtBMin > 200 && MtBMax>200 && DRBB>1.4 && nFatJetsR12>=2 && AntiKt12M_0>120 && MT2Chi2<450 && MetSig>14) {
    fill("NJets_SRB",nSignalJets);
  }
  // Remove JetPt3 cut. Note only pt req removed
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[2].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MtBMax>200 && DRBB>1.4 && nFatJetsR12>=2 && AntiKt12M_0>120 && MT2Chi2<450 && MetSig>14) {
    fill("JetPt3_SRB",signalJets[3].Pt());
  }
  // Remove JetPt2 cut. Since JetPt3>JetPt2 and the cut is the same on both, only JetPt0-1 pt cuts applied
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MtBMax>200 && DRBB>1.4 && nFatJetsR12>=2 && AntiKt12M_0>120 && MT2Chi2<450 && MetSig>14) {
    fill("JetPt2_SRB",signalJets[2].Pt());
  }
  // Remove JetPt1. Note only pt req removed
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[0].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MtBMax>200 && DRBB>1.4 && nFatJetsR12>=2 && AntiKt12M_0>120 && MT2Chi2<450 && MetSig>14) {
    fill("JetPt1_SRB",signalJets[1].Pt());
  }
  // Remove JetPt0 cut. Since JetPt0>JetPt1 and the cut is the same on both, only JetPt 2-3 applied
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[3].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MtBMax>200 && DRBB>1.4 && nFatJetsR12>=2 && AntiKt12M_0>120 && MT2Chi2<450 && MetSig>14) {
    fill("JetPt0_SRB",signalJets[0].Pt());
  }
  // Remove Mt2Chi2 cuts
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MtBMax>200 && DRBB>1.4 && nFatJetsR12>=2 && AntiKt12M_0>120 && MetSig>14) {
    fill("MT2Chi2_SRB",MT2Chi2);
  }
  // Remove DPhiJetMetMin4 cut
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 2 && MtBMin > 200 && MtBMax>200 && DRBB>1.4 && nFatJetsR12>=2 && AntiKt12M_0>120 && MT2Chi2<450 && MetSig>14) {
    fill("DPhiJetMetMin4_SRB",dPhiJetMetMin4);
  }
  // Remove MtBMin cut
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMax>200 && DRBB>1.4 && nFatJetsR12>=2 && AntiKt12M_0>120 && MT2Chi2<450 && MetSig>14) {
    fill("MtBMin_SRB",MtBMin);
  }
  // Remove MtBMax cut
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && DRBB>1.4 && nFatJetsR12>=2 && AntiKt12M_0>120 && MT2Chi2<450 && MetSig>14) {
    fill("MtBMax_SRB",MtBMin);
  }
  // Remove NAntiKt12 cut
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MtBMin > 200 && MtBMax>200 && DRBB>1.4 && AntiKt12M_0>120 && MT2Chi2<450 && MetSig>14) {
    fill("NAntiKt12_SRB",nFatJetsR12);
  }

  /////////////////////////////////////
  // SRC
  // SRC = nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 1 && dPhiJetMetMin2>0.4 && MetSig > 5 && CA_NbV >= 2 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50
  // Fill RISR (Since this is what catergorizes SRC1-5, the SRC hists below do not have a cut applied of this.)
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 1 && dPhiJetMetMin2>0.4 && MetSig > 5 && CA_NbV >= 2 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50) {
    fill("RISR_SRC",CA_RISR);
  }
  // Remove Met cut
  if (nLep == 0 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 1 && dPhiJetMetMin2>0.4 && MetSig > 5 && CA_NbV >= 2 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50) {
    fill("Met_SRC", Met);
  }
  // Remove (both) NBJets cut
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && dPhiJetMetMin2>0.4 && MetSig > 5 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50) {
    fill("NBJetsCA_SRC",CA_NbV);
    fill("NBJets_SRC",nBJets);
  }
  // Remove MetSig cut
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 1 && dPhiJetMetMin2>0.4 && CA_NbV >= 2 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50) {
    fill("MetSig_SRC",MetSig);
  }
  // Remove MS cut
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 1 && dPhiJetMetMin2>0.4 && MetSig > 5 && CA_NbV >= 2 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50) {
    fill("MS_SRC",CA_MS);
  }
  // Remove NJets (both) cuts. (Need to relax JetPt[3] and CA_pTjV4 cuts since those are essentially a NJets>=4 cut)
  if (nLep == 0 && Met > 250 && nSignalJets >= 3 && signalJets[1].Pt() > 80 && signalJets[2].Pt() > 40 && nBJets >= 1 && dPhiJetMetMin2>0.4 && MetSig > 5 && CA_NbV >= 2 && CA_NjV >= 3 && CA_pTbV1 > 40 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_PTISR > 400) {
    fill("NJets_SRC",nSignalJets);
    fill("NJetsCA_SRC",CA_NjV);
  }
  // Remove JetPt3 cut.
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[2].Pt() > 40 && nBJets >= 1 && dPhiJetMetMin2>0.4 && MetSig > 5 && CA_NbV >= 2 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50) {
    fill("JetPt3_40_SRC",signalJets[3].Pt());
  }
  // Remove CA JetPt3 cut.
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 1 && dPhiJetMetMin2>0.4 && MetSig > 5 && CA_NbV >= 2 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_PTISR > 400) {
    fill("JetPt3_50_SRC",CA_pTjV4);
  }
  // Remove JetPt2 cut. Since JetPt3>JetPt2 and the cut is the same on both, only JetPt0-1 pt cuts applied
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && nBJets >= 1 && dPhiJetMetMin2>0.4 && MetSig > 5 && CA_NbV >= 2 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50) {
    fill("JetPt2_SRC",signalJets[2].Pt());
  }
  // Remove JetPt1. Note only pt req removed
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[0].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 1 && dPhiJetMetMin2>0.4 && MetSig > 5 && CA_NbV >= 2 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50) {
    fill("JetPt1_SRC",signalJets[1].Pt());
  }
  // Remove JetPt0 cut. Since JetPt0>JetPt1 and the cut is the same on both, only JetPt 2-3 applied
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[3].Pt() > 40 && nBJets >= 1 && dPhiJetMetMin2>0.4 && MetSig > 5 && CA_NbV >= 2 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50) {
    fill("JetPt0_SRC",signalJets[0].Pt());
  }
  // Remove PTISR
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 1 && dPhiJetMetMin2>0.4 && MetSig > 5 && CA_NbV >= 2 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_pTjV4 > 50) {
    fill("PTISR_SRC",CA_PTISR);
  }
  // Remove PtB1
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 1 && dPhiJetMetMin2>0.4 && MetSig > 5 && CA_NbV >= 2 && CA_NjV >= 4 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50) {
    fill("PtB1_SRC",CA_pTbV1);
  }
  // Remove DPhiMetISR
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 1 && dPhiJetMetMin2>0.4 && MetSig > 5 && CA_NbV >= 2 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_MS > 400 && CA_PTISR > 400 && CA_pTjV4 > 50) {
    fill("DPhiMetISR_SRC",CA_dphiISRI);
  }
  // Remove DPhiMetMin2
  if (nLep == 0 && Met > 250 && nSignalJets >= 4 && signalJets[1].Pt() > 80 && signalJets[3].Pt() > 40 && nBJets >= 1 && MetSig > 5 && CA_NbV >= 2 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50) {
    fill("DPhiJetMetMin2_SRC",dPhiJetMetMin2);
  }


  /////////////////////////////////////
  // SRD
  // Cut String: nLep == 0 && nBadJets == 0 && Met > 250 && nonBJets.size() > 0 && nonBJets.size() > 0 && nonBJets[0].Pt()>250 && nonBJets[0].DeltaR(metVec) > 2.4 && HtSig > 22 && ((nBJets == 0 && dPhiJetMetMin4>0.4 && HtSig > 26) || (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) || (nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6))

  // SRD0
  // First fill histograms that aren't explicitly cut on. NBJets goes here too.
  if (nLep == 0 && nBadJets == 0 && Met > 250 && nonBJets.size() > 0 && nonBJets.size() > 0 && nonBJets[0].Pt()>250 && nonBJets[0].DeltaR(metVec) > 2.4 && HtSig > 22 && ((nBJets == 0 && dPhiJetMetMin4>0.4 && HtSig > 26) || (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) || (nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6))) {
    fill("NJets_SRD",nSignalJets);
    fill("NBJets_SRD",nBJets);
    if (nBJets == 0 && dPhiJetMetMin4>0.4 && HtSig > 26) fill("NBJets_SRD0",nBJets);
    if (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) fill("NBJets_SRD1",nBJets);
    if (nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6) fill("NBJets_SRD2",nBJets);
  }
  // Remove Met
  if (nLep == 0 && nBadJets == 0 && nonBJets.size() > 0 && nonBJets.size() > 0 && nonBJets[0].Pt()>250 && nonBJets[0].DeltaR(metVec) > 2.4 && HtSig > 22 && ((nBJets == 0 && dPhiJetMetMin4>0.4 && HtSig > 26) || (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) || (nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6))) {
    fill("Met_SRD",nBJets);
    if (nBJets == 0 && dPhiJetMetMin4>0.4 && HtSig > 26) fill("Met_SRD0",nBJets);
    if (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) fill("Met_SRD1",nBJets);
    if (nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6) fill("Met_SRD2",nBJets);
  }
  // Remove MetSigHt
  if (nLep == 0 && nBadJets == 0 && Met > 250 && nonBJets.size() > 0 && nonBJets.size() > 0 && nonBJets[0].Pt()>250 && nonBJets[0].DeltaR(metVec) > 2.4 && ((nBJets == 0 && dPhiJetMetMin4>0.4) || (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) || (nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6))) {
    fill("MetSigHt_SRD",HtSig);
    if (nBJets == 0 && dPhiJetMetMin4>0.4) fill("MetSigHt_SRD0",HtSig);
    if (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) fill("MetSigHt_SRD1",HtSig);
    if (nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6) fill("MetSigHt_SRD2",HtSig);
  }
  // Remove DPhiJetMetMin4
  if (nLep == 0 && nBadJets == 0 && Met > 250 && nonBJets.size() > 0 && nonBJets.size() > 0 && nonBJets[0].Pt()>250 && nonBJets[0].DeltaR(metVec) > 2.4 && HtSig > 22 && ((nBJets == 0 && dPhiJetMetMin4>0.4 && HtSig > 26) || (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) || (nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6))) {
    fill("DPhiJetMetMin4_SRD",dPhiJetMetMin4);
    if (nBJets == 0 && HtSig > 26) fill("DPhiJetMetMin4_SRD0",dPhiJetMetMin4);
    if (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) fill("DPhiJetMetMin4_SRD1",dPhiJetMetMin4);
    if (nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6) fill("DPhiJetMetMin4_SRD2",dPhiJetMetMin4);
  }
  // Remove LeadBJetPt
  if (nLep == 0 && nBadJets == 0 && Met > 250 && nonBJets.size() > 0 && nonBJets.size() > 0 && nonBJets[0].Pt()>250 && nonBJets[0].DeltaR(metVec) > 2.4 && HtSig > 22 && ((nBJets == 0 && dPhiJetMetMin4>0.4 && HtSig > 26) || (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) || (nBJets >= 2 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6))) {
    if (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) fill("LeadBJetPt_SRD1",signalBJets[0].Pt());
    if (nBJets >= 2 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6) fill("LeadBJetPt_SRD2",signalBJets[0].Pt());
  }
  // Remove Lead Non-BJet Pt
  if (nLep == 0 && nBadJets == 0 && Met > 250 && nonBJets.size() > 0 && nonBJets.size() > 0 && nonBJets[0].DeltaR(metVec) > 2.4 && HtSig > 22 && ((nBJets == 0 && dPhiJetMetMin4>0.4 && HtSig > 26) || (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) || (nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6))) {
    fill("LeadNonBJetPt_SRD",nonBJets[0].Pt());
    if (nBJets == 0 && dPhiJetMetMin4>0.4 && HtSig > 26) fill("LeadNonBJetPt_SRD0",nonBJets[0].Pt());
    if (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) fill("LeadNonBJetPt_SRD1",nonBJets[0].Pt());
    if (nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6) fill("LeadNonBJetPt_SRD2",nonBJets[0].Pt());
  }
  //Remove LeadNonBJetDPhiMet
  if (nLep == 0 && nBadJets == 0 && Met > 250 && nonBJets.size() > 0 && nonBJets.size() > 0 && nonBJets[0].Pt()>250 && HtSig > 22 && ((nBJets == 0 && dPhiJetMetMin4>0.4 && HtSig > 26) || (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) || (nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6))) {
    fill("LeadNonBJetDPhiMet_SRD",nonBJets[0].DeltaR(metVec));
    if (nBJets == 0 && dPhiJetMetMin4>0.4 && HtSig > 26) fill("LeadNonBJetDPhiMet_SRD0",nonBJets[0].DeltaR(metVec));
    if (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) fill("LeadNonBJetDPhiMet_SRD1",nonBJets[0].DeltaR(metVec));
    if (nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6) fill("LeadNonBJetDPhiMet_SRD2",nonBJets[0].DeltaR(metVec));
  }
  // Remove LeadBJetDPhiNonBJet (also remove sublead in SRD2)
  if (nLep == 0 && nBadJets == 0 && Met > 250 && nonBJets.size() > 0 && nonBJets.size() > 0 && nonBJets[0].Pt()>250 && nonBJets[0].DeltaR(metVec) > 2.4 && HtSig > 22 && ((nBJets == 0 && dPhiJetMetMin4>0.4 && HtSig > 26) || (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6) || (nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2))) {
    if (nBJets == 1 && fabs(signalBJets[0].Eta())<1.6) fill("LeadBJetDPhiNonBJet_SRD1",signalBJets[0].DeltaPhi(nonBJets[0]));
    if (nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2) fill("LeadBJetDPhiNonBJet_SRD2",signalBJets[0].DeltaPhi(nonBJets[0]));
  }
  // Remove SubleadBJetDPhiNonBJet
  if (nLep == 0 && nBadJets == 0 && Met > 250 && nonBJets.size() > 0 && nonBJets.size() > 0 && nonBJets[0].Pt()>250 && nonBJets[0].DeltaR(metVec) > 2.4 && HtSig > 22 && nBJets >= 2 && signalBJets[0].Pt()<175 && fabs(signalBJets[1].Eta())<1.2 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2) fill("SubleadBJetDPhiNonBJet_SRD2",signalBJets[1].DeltaPhi(nonBJets[0]));
  // Remove SubleadBJetEta
  if (nLep == 0 && nBadJets == 0 && Met > 250 && nonBJets.size() > 0 && nonBJets.size() > 0 && nonBJets[0].Pt()>250 && nonBJets[0].DeltaR(metVec) > 2.4 && HtSig > 22 && nBJets >= 2 && signalBJets[0].Pt()<175 && signalBJets[0].DeltaPhi(nonBJets[0])>2.2 && signalBJets[1].DeltaPhi(nonBJets[0])>1.6) fill("SubleadBJetEta_SRD2",nBJets);

  /////////////////////////////////////
  // Cutflow
  
  // SRA
  if (nLep == 0) {
    accept("Cutflow_SRATT_0_LeptonVeto");
    if (nBadJets == 0 ) {
      accept("Cutflow_SRATT_1_BadJetVeto");
      if (Met > 250) {
	accept("Cutflow_SRATT_2_Met");
	if (nSignalJets >= 4) {
	  accept("Cutflow_SRATT_3_NJets");
	  if (signalJets[1].Pt() > 80){
	    accept("Cutflow_SRATT_4_JetPt1");
	    if (signalJets[3].Pt() > 40) {
	      accept("Cutflow_SRATT_5_JetPt3");
	      if (nBJets >= 1) {
		accept("Cutflow_SRATT_6_NBJets1");
		if (nBJets >= 2) {
		  accept("Cutflow_SRATT_7_NBJets2");
		  if (MetSig >= 14) {
		    accept("Cutflow_SRATT_8_MetSig14");
		    if (MetSig >= 25) {
		      accept("Cutflow_SRATT_9_MetSig25");
		      if (MtBMin >= 200) {
			accept("Cutflow_SRATT_10_MtBMin");
			if (nFatJetsR12>=2 ){
			  accept("Cutflow_SRATT_11_NAntiKt12");
			  if (AntiKt12M_0 >= 120) {
			    accept("Cutflow_SRATT_12_AntiKt12M0");
			    if (AntiKt12M_1 >= 120) {
			      accept("Cutflow_SRATT_13_AntiKt12M1");
			      if (AntiKt8M_0 >= 60) {
				accept("Cutflow_SRATT_14_AntiKt8M0");
				if (MT2Chi2 > 450) {
				  accept("Cutflow_SRATT_15_MT2Chi2");
				  if (DRBB >= 1.0) {
				    accept("Cutflow_SRATT_16_DRBB");
				    if ( NCloseByBJets12Leading >= 1) {
				      accept("Cutflow_SRATT_17_NBClose0");
				      if ( NCloseByBJets12Subleading >= 1) {
					accept("Cutflow_SRATT_18_NBClose1");
					if ( dPhiJetMetMin4 > 0.4 ) {
					  accept("Cutflow_SRATT_19_dPhiJetMetMin4");
					}
				      }
				    }
				  }
				}
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}	    
	      }
	    }
	  }
	}
      }
    }
  }
  
  //SRB
  if (nLep == 0) {
    accept("Cutflow_SRBTW_0_LeptonVeto");
    if (nBadJets == 0 ) {
      accept("Cutflow_SRBTW_1_BadJetVeto");
      if (Met > 250) {
	accept("Cutflow_SRBTW_2_Met");
	if (nSignalJets >= 4) {
	  accept("Cutflow_SRBTW_3_NJets");
	  if (signalJets[1].Pt() > 80){
	    accept("Cutflow_SRBTW_4_JetPt1");
	    if (signalJets[3].Pt() > 40) {
	      accept("Cutflow_SRBTW_5_JetPt3");
	      if (nBJets >= 1) {
		accept("Cutflow_SRBTW_6_NBJets1");
		if (nBJets >= 2) {
		  accept("Cutflow_SRBTW_7_NBJets2");
		  if (MetSig >= 14) {
		    accept("Cutflow_SRBTW_8_MetSig14");
		    if (MtBMin >= 200) {
		      accept("Cutflow_SRBTW_9_MtBMin");
		      if (MtBMax >= 200) {
			accept("Cutflow_SRBTW_10_MtBMax");
			if (nFatJetsR12>=2 ){
			  accept("Cutflow_SRBTW_11_NAntiKt12");
			  if (AntiKt12M_0 >= 120) {
			    accept("Cutflow_SRBTW_12_AntiKt12M0");
			    if (AntiKt12M_1 > 60 && AntiKt12M_1 < 120) {
			      accept("Cutflow_SRBTW_13_AntiKt12M1");
			      if (MT2Chi2 < 450) {
				accept("Cutflow_SRBTW_14_MT2Chi2");
				if (DRBB > 1.4) {
				  accept("Cutflow_SRBTW_15_DRBB");
				  if ( dPhiJetMetMin4 > 0.4 ) {
				    accept("Cutflow_SRBTW_16_dPhiJetMetMin4");
				  }
				}
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}	    
	      }
	    }
	  }
	}
      }
    }
  }

  //SRC
  if (nLep == 0) {
    accept("Cutflow_SRC_0_LeptonVeto");
    if (nBadJets == 0) {
      accept("Cutflow_SRC_1_BadJetVeto");
      if (Met > 250) {
	accept("Cutflow_SRC_2_Met");
	if (CA_NjV >= 4) {
	  accept("Cutflow_SRC_3_NJets");
	  if (signalJets[1].Pt() > 80) {
	    accept("Cutflow_SRC_4_JetPt1");
	    if (signalJets[3].Pt() > 40) {
	      accept("Cutflow_SRC_5_JetPt3_40");
	      if (nBJets >= 1) {
		accept("Cutflow_SRC_6_NBJets1");
		if (CA_NbV >= 2) {
		  accept("Cutflow_SRC_7_NBJets2");
		  if (MetSig >= 5) {
		    accept("Cutflow_SRC_8_MetSig5");
		    if (CA_pTbV1 > 40) {
		      accept("Cutflow_SRC_9_BJetPt0");
		      if (CA_pTjV4 > 50) {
			accept("Cutflow_SRC_10_JetPt3_50");
			if (CA_PTISR > 400) {
			  accept("Cutflow_SRC_11_ISRPt");
			  if (CA_dphiISRI > 3.0) {
			    accept("Cutflow_SRC_12_DPhiISRMet");
			    if (CA_MS > 400) {
			      accept("Cutflow_SRC_13_MS");
			      if ( dPhiJetMetMin2 > 0.4 ) {
				accept("Cutflow_SRC_14_dPhiJetMetMin2");
				if ( 0.3 < CA_RISR) {
				  accept("Cutflow_SRC_15_RISR");
				}
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
  //SRD
  if (nLep == 0 ) {
    accept("Cutflow_SRD_0_LeptonVeto");
    if (nBadJets == 0 ) {
      accept("Cutflow_SRD_1_BadJetVeto");
      if (Met > 250) {
	accept("Cutflow_SRD_2_Met");
	if (nonBJets.size() > 0 && nonBJets[0].Pt()>250) {
	  accept("Cutflow_SRD_3_LeadNonBJetPt");
	  if (nonBJets[0].DeltaR(metVec) > 2.4) {
	    accept("Cutflow_SRD_4_LeadNonBJetDPhiMet");
	    if (HtSig > 8) {
	      accept("Cutflow_SRD_5_MetSigHt8");
	      if (HtSig > 22) {
		accept("Cutflow_SRD_6_MetSigHt22");
		if (nBJets == 0) {//SRD0
		  accept("Cutflow_SRD0_7_NBJets");
		  if (dPhiJetMetMin4>0.4) {
		    accept("Cutflow_SRD0_8_MetDPhiJets");
		    if (HtSig > 26) {
		      accept("Cutflow_SRD0_9_MetSigHt26");
		    }
		  }
		} else if (nBJets == 1) {//SRD1
		  accept("Cutflow_SRD1_7_NBJets");
		  if (fabs(signalBJets[0].Eta())<1.6) {
		    accept("Cutflow_SRD1_8_BJet1Eta");
		    if (signalBJets[0].DeltaPhi(nonBJets[0])>2.2) {
		      accept("Cutflow_SRD1_9_BJet1DPhiNonBJet");
		    }
		  }
		} else {//SRD2
		  accept("Cutflow_SRD2_7_NBJets");
		  if (signalBJets[0].Pt()<175) {
		    accept("Cutflow_SRD2_8_BJet1Pt");
		    if (fabs(signalBJets[1].Eta())<1.2) {
		      accept("Cutflow_SRD2_9_BJet2Eta");
		      if (signalBJets[0].DeltaPhi(nonBJets[0])>2.2) {
			accept("Cutflow_SRD2_10_BJet1DPhiNonBJet");
			if (signalBJets[1].DeltaPhi(nonBJets[0])>1.6) {
			  accept("Cutflow_SRD2_11_BJet2DPhiNonBJet");
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }

  //////////////////////////////
  // Finished with event
  return;
}
