
ParticleDefinitions[GaugeES] = {

      {VB,   { Description -> "B-Boson"}},                                                   
      {VG,   { Description -> "Gluon"}},          
      {VWB,  { Description -> "W-Bosons"}},          
      {gB,   { Description -> "B-Boson Ghost"}},                                                   
      {gG,   { Description -> "Gluon Ghost" }},          
      {gWB,  { Description -> "W-Boson Ghost"}}
      };
      
      
      
      
   ParticleDefinitions[EWSB] = {

     {hh   ,  {  Description -> "Higgs",
                 ElectricCharge->0,     
                 PDG -> {25},
                 FeynArtsNr -> 1,
                 PDG.IX -> {101000001} }}, 
                 
     {G0   ,  {  Description -> "Pseudo-Scalar Higgs",
                 PDG -> {0},
                 PDG.IX ->{0},
                 Mass -> {0},
                 FeynArtsNr -> 4,
                 ElectricCharge->0,                 
                 Width -> {0} }},  

     {H0   ,  {  Description -> "H0", 
                 OutputName ->"H0",
                 PDG -> {35},
                 PDG.IX -> {101000001},
                 FeynArtsNr -> 2,
                 ElectricCharge->0,                 
                 LaTeX -> "H" }}, 
                 
     {A0   ,  {  Description -> "A0",
                 OutputName ->"A0",
                 PDG -> {36},
                 ElectricCharge->0,
                 FeynArtsNr -> 3,
                 LaTeX -> "A^0" }},             
            
      

      
      {Hp,  { Description -> "Charged Higgs",
                 ElectricCharge -> 1,
                 FeynArtsNr -> 5}},                                                   
      {VP,   { Description -> "Photon"}}, 
      {VZ,   { Description -> "Z-Boson",
      			 Goldstone -> G0 }}, 
      {VG,   { Description -> "Gluon" }},          
      {VWp,  { Description -> "W+ - Boson",
      			Goldstone -> Hp[{1}] }},         
      {gP,   { Description -> "Photon Ghost"}},                                                   
      {gWp,  { Description -> "Positive W+ - Boson Ghost"}}, 
      {gWpC, { Description -> "Negative W+ - Boson Ghost" }}, 
      {gZ,   { Description -> "Z-Boson Ghost" }},
      {gG,   { Description -> "Gluon Ghost" }}, 
                               
                 
      {Fd,   { Description -> "Down-Quarks"}},   
      {Fu,   { Description -> "Up-Quarks"}},   
      {Fe,   { Description -> "Leptons" }},
      {Fv,   { Description -> "Neutrinos" }}                                                              
     
        };    
        
        
        
 WeylFermionAndIndermediate = {
                 
       {phid,   {  PDG -> 0,
                 Width -> 0, 
                 Mass -> Automatic,
                 LaTeX -> "\\phi_{d}",
                 OutputName -> "" }},                                                                       
   
   
       {phiu,   {  PDG -> 0,
                 Width -> 0, 
                 Mass -> Automatic,
                 LaTeX -> "\\phi_{u}",
                 OutputName -> "" }}, 
                                                                                       
    {sigmad,   {  PDG -> 0,
                 Width -> 0, 
                 Mass -> Automatic,
                 LaTeX -> "\\sigma_{d}",
                 OutputName -> "" }},
                                                                                        
    {sigmau,   {  PDG -> 0,
                 Width -> 0, 
                 Mass -> Automatic,
                 LaTeX -> "\\sigma_{u}",
                 OutputName -> "" }}


        };       

