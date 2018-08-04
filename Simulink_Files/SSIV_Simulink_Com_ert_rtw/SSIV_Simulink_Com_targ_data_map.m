  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 3;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (audekaprdr)
    ;%
      section.nData     = 16;
      section.data(16)  = dumData; %prealloc
      
	  ;% audekaprdr.FixPtBitwiseOperator1_BitMask
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% audekaprdr.FixPtBitwiseOperator_pdcye4hh3h
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% audekaprdr.FixPtBitwiseOperator_cmwnez4tht
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% audekaprdr.FixPtBitwiseOperator_cxnvosifes
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% audekaprdr.FixPtBitwiseOperator_ohztsiw5ag
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% audekaprdr.FixPtBitwiseOperator_fvznarljhl
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% audekaprdr.FixPtBitwiseOperator_ncdvvniusl
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% audekaprdr.FixPtBitwiseOperator_e3fhb1x4fg
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% audekaprdr.FixPtBitwiseOperator_e1pefu4111
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% audekaprdr.FixPtBitwiseOperator_bj3g1d1j5p
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% audekaprdr.FixPtBitwiseOperator_pbacdywnxg
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% audekaprdr.FixPtBitwiseOperator_ohl3pesogw
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% audekaprdr.FixPtBitwiseOperator_d15mriljoo
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% audekaprdr.FixPtBitwiseOperator_j5giwlnstb
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% audekaprdr.FixPtBitwiseOperator_pcnsquvmih
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% audekaprdr.FixPtBitwiseOperator_p00wwjvilg
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 25;
      section.data(25)  = dumData; %prealloc
      
	  ;% audekaprdr._Value
	  section.data(1).logicalSrcIdx = 16;
	  section.data(1).dtTransOffset = 0;
	
	  ;% audekaprdr._Value_bbqtwjbdzi
	  section.data(2).logicalSrcIdx = 17;
	  section.data(2).dtTransOffset = 1;
	
	  ;% audekaprdr.ConstMotTorquemNm_Value
	  section.data(3).logicalSrcIdx = 18;
	  section.data(3).dtTransOffset = 2;
	
	  ;% audekaprdr.bitsmNm_Gain
	  section.data(4).logicalSrcIdx = 19;
	  section.data(4).dtTransOffset = 3;
	
	  ;% audekaprdr.bitsmNm_Gain_iz44z4guht
	  section.data(5).logicalSrcIdx = 20;
	  section.data(5).dtTransOffset = 4;
	
	  ;% audekaprdr.bitsmNm_Gain_jjrfnm553k
	  section.data(6).logicalSrcIdx = 21;
	  section.data(6).dtTransOffset = 5;
	
	  ;% audekaprdr.bitsmNm_Gain_ljowsi2cmm
	  section.data(7).logicalSrcIdx = 22;
	  section.data(7).dtTransOffset = 6;
	
	  ;% audekaprdr.bitsmNm_Gain_iklhud12ye
	  section.data(8).logicalSrcIdx = 23;
	  section.data(8).dtTransOffset = 7;
	
	  ;% audekaprdr.AccelerationInttoDoubleScaleFac
	  section.data(9).logicalSrcIdx = 24;
	  section.data(9).dtTransOffset = 8;
	
	  ;% audekaprdr.GyroscopeInttoDoubleScaleFactor
	  section.data(10).logicalSrcIdx = 25;
	  section.data(10).dtTransOffset = 9;
	
	  ;% audekaprdr.AccelerationInttoDou_gc2d21uelw
	  section.data(11).logicalSrcIdx = 26;
	  section.data(11).dtTransOffset = 10;
	
	  ;% audekaprdr.GyroscopeInttoDouble_c3tykg3kf4
	  section.data(12).logicalSrcIdx = 27;
	  section.data(12).dtTransOffset = 11;
	
	  ;% audekaprdr.AccelerationInttoDou_gaa1ffktv1
	  section.data(13).logicalSrcIdx = 28;
	  section.data(13).dtTransOffset = 12;
	
	  ;% audekaprdr.GyroscopeInttoDouble_pwakq5xjiz
	  section.data(14).logicalSrcIdx = 29;
	  section.data(14).dtTransOffset = 13;
	
	  ;% audekaprdr.Compensatesfordirectionofspinwa
	  section.data(15).logicalSrcIdx = 30;
	  section.data(15).dtTransOffset = 14;
	
	  ;% audekaprdr.Compensatesfordirect_i4eeramtoi
	  section.data(16).logicalSrcIdx = 31;
	  section.data(16).dtTransOffset = 15;
	
	  ;% audekaprdr.EulerInttoDoubleScaleFactor_Gai
	  section.data(17).logicalSrcIdx = 32;
	  section.data(17).dtTransOffset = 16;
	
	  ;% audekaprdr.EulerInttoDoubleScal_l5pjefwhnw
	  section.data(18).logicalSrcIdx = 33;
	  section.data(18).dtTransOffset = 17;
	
	  ;% audekaprdr.EulerInttoDoubleScal_ftn3cq0u21
	  section.data(19).logicalSrcIdx = 34;
	  section.data(19).dtTransOffset = 18;
	
	  ;% audekaprdr.TriggerValueRequiredforSubsyste
	  section.data(20).logicalSrcIdx = 35;
	  section.data(20).dtTransOffset = 19;
	
	  ;% audekaprdr.TriggerSwitch_Threshold
	  section.data(21).logicalSrcIdx = 36;
	  section.data(21).dtTransOffset = 20;
	
	  ;% audekaprdr.TimeallottedforSSIVtoinitialize
	  section.data(22).logicalSrcIdx = 37;
	  section.data(22).dtTransOffset = 21;
	
	  ;% audekaprdr.Constant1_Value
	  section.data(23).logicalSrcIdx = 38;
	  section.data(23).dtTransOffset = 22;
	
	  ;% audekaprdr.SimulationTimeStep_Value
	  section.data(24).logicalSrcIdx = 39;
	  section.data(24).dtTransOffset = 23;
	
	  ;% audekaprdr.Constant2_Value
	  section.data(25).logicalSrcIdx = 40;
	  section.data(25).dtTransOffset = 24;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 72;
      section.data(72)  = dumData; %prealloc
      
	  ;% audekaprdr.DeadSwitch_Value
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
	  ;% audekaprdr.TakeData_Value
	  section.data(2).logicalSrcIdx = 42;
	  section.data(2).dtTransOffset = 1;
	
	  ;% audekaprdr.ServoandRadioOn_Value
	  section.data(3).logicalSrcIdx = 43;
	  section.data(3).dtTransOffset = 2;
	
	  ;% audekaprdr.MotorControllersOn_Value
	  section.data(4).logicalSrcIdx = 44;
	  section.data(4).dtTransOffset = 3;
	
	  ;% audekaprdr.IMUReset_Value
	  section.data(5).logicalSrcIdx = 45;
	  section.data(5).dtTransOffset = 4;
	
	  ;% audekaprdr.PrinttheregistermapontheTeensy_
	  section.data(6).logicalSrcIdx = 46;
	  section.data(6).dtTransOffset = 5;
	
	  ;% audekaprdr.PrinttheimudataontheTeensy_Valu
	  section.data(7).logicalSrcIdx = 47;
	  section.data(7).dtTransOffset = 6;
	
	  ;% audekaprdr.Printtheradiotranceiverdataonth
	  section.data(8).logicalSrcIdx = 48;
	  section.data(8).dtTransOffset = 7;
	
	  ;% audekaprdr.radio_throttleAddressNumber_Val
	  section.data(9).logicalSrcIdx = 49;
	  section.data(9).dtTransOffset = 8;
	
	  ;% audekaprdr.uint8_t1_Value
	  section.data(10).logicalSrcIdx = 50;
	  section.data(10).dtTransOffset = 9;
	
	  ;% audekaprdr.uint8_t2_Value
	  section.data(11).logicalSrcIdx = 51;
	  section.data(11).dtTransOffset = 10;
	
	  ;% audekaprdr.uint8_t3_Value
	  section.data(12).logicalSrcIdx = 52;
	  section.data(12).dtTransOffset = 11;
	
	  ;% audekaprdr.euler_headingAddressNumber_Valu
	  section.data(13).logicalSrcIdx = 53;
	  section.data(13).dtTransOffset = 12;
	
	  ;% audekaprdr.uint8_t1_Value_ph4svpkuc4
	  section.data(14).logicalSrcIdx = 54;
	  section.data(14).dtTransOffset = 13;
	
	  ;% audekaprdr.uint8_t2_Value_c1zzxyoirl
	  section.data(15).logicalSrcIdx = 55;
	  section.data(15).dtTransOffset = 14;
	
	  ;% audekaprdr.uint8_t3_Value_jlgp2rrkzi
	  section.data(16).logicalSrcIdx = 56;
	  section.data(16).dtTransOffset = 15;
	
	  ;% audekaprdr.euler_rollAddressNumber_Value
	  section.data(17).logicalSrcIdx = 57;
	  section.data(17).dtTransOffset = 16;
	
	  ;% audekaprdr.uint8_t1_Value_hq2lukzl5r
	  section.data(18).logicalSrcIdx = 58;
	  section.data(18).dtTransOffset = 17;
	
	  ;% audekaprdr.uint8_t2_Value_ngl53v5j0r
	  section.data(19).logicalSrcIdx = 59;
	  section.data(19).dtTransOffset = 18;
	
	  ;% audekaprdr.uint8_t3_Value_lnbbb2dqeb
	  section.data(20).logicalSrcIdx = 60;
	  section.data(20).dtTransOffset = 19;
	
	  ;% audekaprdr.euler_pitchAddressNumber_Value
	  section.data(21).logicalSrcIdx = 61;
	  section.data(21).dtTransOffset = 20;
	
	  ;% audekaprdr.uint8_t1_Value_n1nrgisxf2
	  section.data(22).logicalSrcIdx = 62;
	  section.data(22).dtTransOffset = 21;
	
	  ;% audekaprdr.uint8_t2_Value_jgwihwwu41
	  section.data(23).logicalSrcIdx = 63;
	  section.data(23).dtTransOffset = 22;
	
	  ;% audekaprdr.uint8_t3_Value_iav1z2typf
	  section.data(24).logicalSrcIdx = 64;
	  section.data(24).dtTransOffset = 23;
	
	  ;% audekaprdr.radio_throttleAddres_cbekgc1ix1
	  section.data(25).logicalSrcIdx = 65;
	  section.data(25).dtTransOffset = 24;
	
	  ;% audekaprdr.uint8_t1_Value_cr5hy3vrzq
	  section.data(26).logicalSrcIdx = 66;
	  section.data(26).dtTransOffset = 25;
	
	  ;% audekaprdr.uint8_t2_Value_jwpaibaxce
	  section.data(27).logicalSrcIdx = 67;
	  section.data(27).dtTransOffset = 26;
	
	  ;% audekaprdr.uint8_t3_Value_dqlq4dbfix
	  section.data(28).logicalSrcIdx = 68;
	  section.data(28).dtTransOffset = 27;
	
	  ;% audekaprdr.radio_steeringAddressNumber_Val
	  section.data(29).logicalSrcIdx = 69;
	  section.data(29).dtTransOffset = 28;
	
	  ;% audekaprdr.uint8_t1_Value_iyfuhftjuq
	  section.data(30).logicalSrcIdx = 70;
	  section.data(30).dtTransOffset = 29;
	
	  ;% audekaprdr.uint8_t2_Value_p21cu3lfhe
	  section.data(31).logicalSrcIdx = 71;
	  section.data(31).dtTransOffset = 30;
	
	  ;% audekaprdr.uint8_t3_Value_kes4jow02f
	  section.data(32).logicalSrcIdx = 72;
	  section.data(32).dtTransOffset = 31;
	
	  ;% audekaprdr.velocity_FRAddressNumber_Value
	  section.data(33).logicalSrcIdx = 73;
	  section.data(33).dtTransOffset = 32;
	
	  ;% audekaprdr.uint8_t1_Value_akmtssrtai
	  section.data(34).logicalSrcIdx = 74;
	  section.data(34).dtTransOffset = 33;
	
	  ;% audekaprdr.uint8_t2_Value_k3gkw5urld
	  section.data(35).logicalSrcIdx = 75;
	  section.data(35).dtTransOffset = 34;
	
	  ;% audekaprdr.uint8_t3_Value_oawvqyaxpy
	  section.data(36).logicalSrcIdx = 76;
	  section.data(36).dtTransOffset = 35;
	
	  ;% audekaprdr.velocity_FLAddressNumber_Value
	  section.data(37).logicalSrcIdx = 77;
	  section.data(37).dtTransOffset = 36;
	
	  ;% audekaprdr.uint8_t1_Value_n22bel2kr0
	  section.data(38).logicalSrcIdx = 78;
	  section.data(38).dtTransOffset = 37;
	
	  ;% audekaprdr.uint8_t2_Value_ggao0gz1ir
	  section.data(39).logicalSrcIdx = 79;
	  section.data(39).dtTransOffset = 38;
	
	  ;% audekaprdr.uint8_t3_Value_oxoqn0br0t
	  section.data(40).logicalSrcIdx = 80;
	  section.data(40).dtTransOffset = 39;
	
	  ;% audekaprdr.velocity_RRAddressNumber_Value
	  section.data(41).logicalSrcIdx = 81;
	  section.data(41).dtTransOffset = 40;
	
	  ;% audekaprdr.uint8_t1_Value_ekb21cf5ed
	  section.data(42).logicalSrcIdx = 82;
	  section.data(42).dtTransOffset = 41;
	
	  ;% audekaprdr.uint8_t2_Value_hazd5tqbaw
	  section.data(43).logicalSrcIdx = 83;
	  section.data(43).dtTransOffset = 42;
	
	  ;% audekaprdr.uint8_t3_Value_pnt2y4c2x2
	  section.data(44).logicalSrcIdx = 84;
	  section.data(44).dtTransOffset = 43;
	
	  ;% audekaprdr.velocity_RLAddressNumber_Value
	  section.data(45).logicalSrcIdx = 85;
	  section.data(45).dtTransOffset = 44;
	
	  ;% audekaprdr.uint8_t1_Value_i1m3o1h553
	  section.data(46).logicalSrcIdx = 86;
	  section.data(46).dtTransOffset = 45;
	
	  ;% audekaprdr.uint8_t2_Value_m54yummdfc
	  section.data(47).logicalSrcIdx = 87;
	  section.data(47).dtTransOffset = 46;
	
	  ;% audekaprdr.uint8_t3_Value_arsxpqtnpb
	  section.data(48).logicalSrcIdx = 88;
	  section.data(48).dtTransOffset = 47;
	
	  ;% audekaprdr.gyr_xAddressNumber_Value
	  section.data(49).logicalSrcIdx = 89;
	  section.data(49).dtTransOffset = 48;
	
	  ;% audekaprdr.uint8_t1_Value_j5gua0l1cu
	  section.data(50).logicalSrcIdx = 90;
	  section.data(50).dtTransOffset = 49;
	
	  ;% audekaprdr.uint8_t2_Value_ifkn0ogqah
	  section.data(51).logicalSrcIdx = 91;
	  section.data(51).dtTransOffset = 50;
	
	  ;% audekaprdr.uint8_t3_Value_h1kqrgh25u
	  section.data(52).logicalSrcIdx = 92;
	  section.data(52).dtTransOffset = 51;
	
	  ;% audekaprdr.acc_xAddressNumber_Value
	  section.data(53).logicalSrcIdx = 93;
	  section.data(53).dtTransOffset = 52;
	
	  ;% audekaprdr.uint8_t1_Value_hvfq5alqlg
	  section.data(54).logicalSrcIdx = 94;
	  section.data(54).dtTransOffset = 53;
	
	  ;% audekaprdr.uint8_t2_Value_fecgcw2rtb
	  section.data(55).logicalSrcIdx = 95;
	  section.data(55).dtTransOffset = 54;
	
	  ;% audekaprdr.uint8_t3_Value_axuapffnub
	  section.data(56).logicalSrcIdx = 96;
	  section.data(56).dtTransOffset = 55;
	
	  ;% audekaprdr.gyr_yAddressNumber_Value
	  section.data(57).logicalSrcIdx = 97;
	  section.data(57).dtTransOffset = 56;
	
	  ;% audekaprdr.uint8_t1_Value_piyajw3x43
	  section.data(58).logicalSrcIdx = 98;
	  section.data(58).dtTransOffset = 57;
	
	  ;% audekaprdr.uint8_t2_Value_dqa5qd3nqm
	  section.data(59).logicalSrcIdx = 99;
	  section.data(59).dtTransOffset = 58;
	
	  ;% audekaprdr.uint8_t3_Value_mwjdv2jlcq
	  section.data(60).logicalSrcIdx = 100;
	  section.data(60).dtTransOffset = 59;
	
	  ;% audekaprdr.acc_yAddressNumber_Value
	  section.data(61).logicalSrcIdx = 101;
	  section.data(61).dtTransOffset = 60;
	
	  ;% audekaprdr.uint8_t1_Value_cx4haj0vmu
	  section.data(62).logicalSrcIdx = 102;
	  section.data(62).dtTransOffset = 61;
	
	  ;% audekaprdr.uint8_t2_Value_kj2tsprzh4
	  section.data(63).logicalSrcIdx = 103;
	  section.data(63).dtTransOffset = 62;
	
	  ;% audekaprdr.uint8_t3_Value_mbqdfbfyg2
	  section.data(64).logicalSrcIdx = 104;
	  section.data(64).dtTransOffset = 63;
	
	  ;% audekaprdr.gyr_zAddressNumber_Value
	  section.data(65).logicalSrcIdx = 105;
	  section.data(65).dtTransOffset = 64;
	
	  ;% audekaprdr.uint8_t1_Value_k0znqgaxdh
	  section.data(66).logicalSrcIdx = 106;
	  section.data(66).dtTransOffset = 65;
	
	  ;% audekaprdr.uint8_t2_Value_lugnty1mnt
	  section.data(67).logicalSrcIdx = 107;
	  section.data(67).dtTransOffset = 66;
	
	  ;% audekaprdr.uint8_t3_Value_pnhener42w
	  section.data(68).logicalSrcIdx = 108;
	  section.data(68).dtTransOffset = 67;
	
	  ;% audekaprdr.acc_zAddressNumber_Value
	  section.data(69).logicalSrcIdx = 109;
	  section.data(69).dtTransOffset = 68;
	
	  ;% audekaprdr.uint8_t1_Value_oeciw2yhtb
	  section.data(70).logicalSrcIdx = 110;
	  section.data(70).dtTransOffset = 69;
	
	  ;% audekaprdr.uint8_t2_Value_faqrjkomp0
	  section.data(71).logicalSrcIdx = 111;
	  section.data(71).dtTransOffset = 70;
	
	  ;% audekaprdr.uint8_t3_Value_ivkyv5mnys
	  section.data(72).logicalSrcIdx = 112;
	  section.data(72).dtTransOffset = 71;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 46;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (clyvxiydarg)
    ;%
      section.nData     = 21;
      section.data(21)  = dumData; %prealloc
      
	  ;% clyvxiydarg.fdlauzuoju
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% clyvxiydarg.jgbvydvwsy
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% clyvxiydarg.bkrzd3g2wi
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% clyvxiydarg.o1fwpjq3dy
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% clyvxiydarg.nqzmchd1r4
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% clyvxiydarg.h2nnhro0e4
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% clyvxiydarg.mdze4f40rc
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% clyvxiydarg.ik0pr0vrv2
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% clyvxiydarg.punl44mluh
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% clyvxiydarg.gaij0rviey
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% clyvxiydarg.ix3hflprqv
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% clyvxiydarg.dxwjrhob5r
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% clyvxiydarg.mcnsx3wrpl
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% clyvxiydarg.cxsa4lhuyc
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% clyvxiydarg.ltxykxkvcz
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% clyvxiydarg.pj5cwigrfj
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% clyvxiydarg.fc4ucl13zb
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% clyvxiydarg.byd3vcunuk
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% clyvxiydarg.i41qlayz2l
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% clyvxiydarg.fq1qfqrphj
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% clyvxiydarg.ptrclgo5i1
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% clyvxiydarg.f0emtpydi0
	  section.data(1).logicalSrcIdx = 21;
	  section.data(1).dtTransOffset = 0;
	
	  ;% clyvxiydarg.adlewgljss
	  section.data(2).logicalSrcIdx = 22;
	  section.data(2).dtTransOffset = 1;
	
	  ;% clyvxiydarg.bvbw1uflgg
	  section.data(3).logicalSrcIdx = 23;
	  section.data(3).dtTransOffset = 2;
	
	  ;% clyvxiydarg.pllb01brx3
	  section.data(4).logicalSrcIdx = 24;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% clyvxiydarg.fisez1w02x
	  section.data(1).logicalSrcIdx = 25;
	  section.data(1).dtTransOffset = 0;
	
	  ;% clyvxiydarg.alpabwxe2w
	  section.data(2).logicalSrcIdx = 26;
	  section.data(2).dtTransOffset = 2;
	
	  ;% clyvxiydarg.nsazlii4tl
	  section.data(3).logicalSrcIdx = 27;
	  section.data(3).dtTransOffset = 3;
	
	  ;% clyvxiydarg.bwa40grhig
	  section.data(4).logicalSrcIdx = 28;
	  section.data(4).dtTransOffset = 4;
	
	  ;% clyvxiydarg.obom5x3d5k
	  section.data(5).logicalSrcIdx = 29;
	  section.data(5).dtTransOffset = 5;
	
	  ;% clyvxiydarg.blslpvafaj
	  section.data(6).logicalSrcIdx = 30;
	  section.data(6).dtTransOffset = 6;
	
	  ;% clyvxiydarg.bhdmoiwfl2
	  section.data(7).logicalSrcIdx = 31;
	  section.data(7).dtTransOffset = 7;
	
	  ;% clyvxiydarg.mzc2e1h4xa
	  section.data(8).logicalSrcIdx = 32;
	  section.data(8).dtTransOffset = 8;
	
	  ;% clyvxiydarg.n30ajead0c
	  section.data(9).logicalSrcIdx = 33;
	  section.data(9).dtTransOffset = 9;
	
	  ;% clyvxiydarg.pzzkogkfuo
	  section.data(10).logicalSrcIdx = 34;
	  section.data(10).dtTransOffset = 10;
	
	  ;% clyvxiydarg.ellnmxuy5c
	  section.data(11).logicalSrcIdx = 35;
	  section.data(11).dtTransOffset = 12;
	
	  ;% clyvxiydarg.ehp13vk0yn
	  section.data(12).logicalSrcIdx = 36;
	  section.data(12).dtTransOffset = 14;
	
	  ;% clyvxiydarg.gvjctcpowu
	  section.data(13).logicalSrcIdx = 37;
	  section.data(13).dtTransOffset = 16;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% clyvxiydarg.fkjscyvbyz
	  section.data(1).logicalSrcIdx = 38;
	  section.data(1).dtTransOffset = 0;
	
	  ;% clyvxiydarg.bpqhvv3cpv
	  section.data(2).logicalSrcIdx = 39;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.kw3hkiwkin.j5akpgvv3v
	  section.data(1).logicalSrcIdx = 40;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.eyct3yxt3z.ax0zrlqhyg
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.metswdrgzu.n4ajio1im5
	  section.data(1).logicalSrcIdx = 42;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.hyjnsswda3.n4ajio1im5
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.asiloiskms.n4ajio1im5
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.apywuh1fff.n4ajio1im5
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ir3axckkpy.n4ajio1im5
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ofmaduua5r.n4ajio1im5
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.gul1auxbrt.n4ajio1im5
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.oxosvsteyx.n4ajio1im5
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.fnox4hv2rk.n4ajio1im5
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.at01kh0lsu.n4ajio1im5
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.dgtcji23ys.n4ajio1im5
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.dmczjvykxa.n4ajio1im5
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.fh4g55wfxs.n4ajio1im5
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.mmxqbsmoal.n4ajio1im5
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.gafyqftzh5.n4ajio1im5
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.o3brjlgfg1.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.nbm22evv0g.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ebil10nhgi.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.op2jvp5kgrjz.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.kfxzmrhmet.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.b5yns515f3.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.bw3qikpzl5.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.eh2gxhlfvx.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.m5s5btvqpr.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.imtastcd1c.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.mal2e4bwfg.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.fsgkfn1wuo.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.judnob4hwn.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(34) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.nq4cmgm03a.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(35) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ix1ebopk11.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 71;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(36) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.pma3dkyose.j5akpgvv3v
	  section.data(1).logicalSrcIdx = 72;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(37) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.gpdaqcio2h.ax0zrlqhyg
	  section.data(1).logicalSrcIdx = 73;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(38) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.djjjqxtsvn.j5akpgvv3v
	  section.data(1).logicalSrcIdx = 74;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(39) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.crzjsfjgfq.ax0zrlqhyg
	  section.data(1).logicalSrcIdx = 75;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(40) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.nkc3h3u2qx.j5akpgvv3v
	  section.data(1).logicalSrcIdx = 76;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(41) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.lo2y5dsae1.ax0zrlqhyg
	  section.data(1).logicalSrcIdx = 77;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(42) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.etyd41ymc0k.j5akpgvv3v
	  section.data(1).logicalSrcIdx = 78;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(43) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.cqwydeyjjzl.ax0zrlqhyg
	  section.data(1).logicalSrcIdx = 79;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(44) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.hnc055su4jj.n4ajio1im5
	  section.data(1).logicalSrcIdx = 80;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(45) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.op2jvp5kgrj.c1kldhmsiz
	  section.data(1).logicalSrcIdx = 81;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(46) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 36;
    sectIdxOffset = 46;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (kmoqdzazlbs)
    ;%
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.iakgodzq5b
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% kmoqdzazlbs.ji3y5cqka2
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% kmoqdzazlbs.hslmt2wbm1
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% kmoqdzazlbs.iztympubk5
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% kmoqdzazlbs.pjtttqsyat
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% kmoqdzazlbs.a2u0n35vkx
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% kmoqdzazlbs.fogkdcpyxn
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% kmoqdzazlbs.nd1taqo52d
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% kmoqdzazlbs.oxyx0jt1zt
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% kmoqdzazlbs.itlqodsvjm
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% kmoqdzazlbs.du3r5tihjx
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% kmoqdzazlbs.dfyhkf1lgs
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% kmoqdzazlbs.as3iismmaz
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 18;
      section.data(18)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.h4yhtvz5ub.LoggedData
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
	  ;% kmoqdzazlbs.mvq4lwsxuy.LoggedData
	  section.data(2).logicalSrcIdx = 14;
	  section.data(2).dtTransOffset = 1;
	
	  ;% kmoqdzazlbs.lyabsq2k4s.LoggedData
	  section.data(3).logicalSrcIdx = 15;
	  section.data(3).dtTransOffset = 3;
	
	  ;% kmoqdzazlbs.iyemqsccy0.LoggedData
	  section.data(4).logicalSrcIdx = 16;
	  section.data(4).dtTransOffset = 5;
	
	  ;% kmoqdzazlbs.hi4ksfagcv.LoggedData
	  section.data(5).logicalSrcIdx = 17;
	  section.data(5).dtTransOffset = 7;
	
	  ;% kmoqdzazlbs.jjnonbv5xg.LoggedData
	  section.data(6).logicalSrcIdx = 18;
	  section.data(6).dtTransOffset = 9;
	
	  ;% kmoqdzazlbs.osxqigufb4.LoggedData
	  section.data(7).logicalSrcIdx = 19;
	  section.data(7).dtTransOffset = 13;
	
	  ;% kmoqdzazlbs.h3oogjzi32.LoggedData
	  section.data(8).logicalSrcIdx = 20;
	  section.data(8).dtTransOffset = 16;
	
	  ;% kmoqdzazlbs.de54hapdxz.LoggedData
	  section.data(9).logicalSrcIdx = 21;
	  section.data(9).dtTransOffset = 17;
	
	  ;% kmoqdzazlbs.nmdedp4f3t.LoggedData
	  section.data(10).logicalSrcIdx = 22;
	  section.data(10).dtTransOffset = 18;
	
	  ;% kmoqdzazlbs.bzefabupzc.LoggedData
	  section.data(11).logicalSrcIdx = 23;
	  section.data(11).dtTransOffset = 19;
	
	  ;% kmoqdzazlbs.lnd2o4jj1z.LoggedData
	  section.data(12).logicalSrcIdx = 24;
	  section.data(12).dtTransOffset = 20;
	
	  ;% kmoqdzazlbs.jh5cyx1ang.LoggedData
	  section.data(13).logicalSrcIdx = 25;
	  section.data(13).dtTransOffset = 21;
	
	  ;% kmoqdzazlbs.in5e0s4uxy.LoggedData
	  section.data(14).logicalSrcIdx = 26;
	  section.data(14).dtTransOffset = 22;
	
	  ;% kmoqdzazlbs.l51pt0mhbw.LoggedData
	  section.data(15).logicalSrcIdx = 27;
	  section.data(15).dtTransOffset = 23;
	
	  ;% kmoqdzazlbs.kh4sdo3mgz.LoggedData
	  section.data(16).logicalSrcIdx = 28;
	  section.data(16).dtTransOffset = 24;
	
	  ;% kmoqdzazlbs.myf2l5zu42.LoggedData
	  section.data(17).logicalSrcIdx = 29;
	  section.data(17).dtTransOffset = 25;
	
	  ;% kmoqdzazlbs.pqk21lwi5l.LoggedData
	  section.data(18).logicalSrcIdx = 30;
	  section.data(18).dtTransOffset = 26;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.js1pmoelqv
	  section.data(1).logicalSrcIdx = 31;
	  section.data(1).dtTransOffset = 0;
	
	  ;% kmoqdzazlbs.d44rbefva3
	  section.data(2).logicalSrcIdx = 32;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.mp1ginymjj
	  section.data(1).logicalSrcIdx = 33;
	  section.data(1).dtTransOffset = 0;
	
	  ;% kmoqdzazlbs.hiktqtlwmz
	  section.data(2).logicalSrcIdx = 34;
	  section.data(2).dtTransOffset = 1;
	
	  ;% kmoqdzazlbs.dv3lfxn2xh
	  section.data(3).logicalSrcIdx = 35;
	  section.data(3).dtTransOffset = 2;
	
	  ;% kmoqdzazlbs.jb4fs5m310
	  section.data(4).logicalSrcIdx = 36;
	  section.data(4).dtTransOffset = 3;
	
	  ;% kmoqdzazlbs.n14uq0f0yw
	  section.data(5).logicalSrcIdx = 37;
	  section.data(5).dtTransOffset = 4;
	
	  ;% kmoqdzazlbs.ltufaxpna0
	  section.data(6).logicalSrcIdx = 38;
	  section.data(6).dtTransOffset = 5;
	
	  ;% kmoqdzazlbs.i3af2m25ya
	  section.data(7).logicalSrcIdx = 39;
	  section.data(7).dtTransOffset = 6;
	
	  ;% kmoqdzazlbs.kl5wif40vr
	  section.data(8).logicalSrcIdx = 40;
	  section.data(8).dtTransOffset = 7;
	
	  ;% kmoqdzazlbs.lz3ugc4cwh
	  section.data(9).logicalSrcIdx = 41;
	  section.data(9).dtTransOffset = 8;
	
	  ;% kmoqdzazlbs.orrtyae4cj
	  section.data(10).logicalSrcIdx = 42;
	  section.data(10).dtTransOffset = 9;
	
	  ;% kmoqdzazlbs.mlvjnryb2f
	  section.data(11).logicalSrcIdx = 43;
	  section.data(11).dtTransOffset = 10;
	
	  ;% kmoqdzazlbs.gyhved5o0g
	  section.data(12).logicalSrcIdx = 44;
	  section.data(12).dtTransOffset = 11;
	
	  ;% kmoqdzazlbs.pthrmzewo5
	  section.data(13).logicalSrcIdx = 45;
	  section.data(13).dtTransOffset = 12;
	
	  ;% kmoqdzazlbs.pb2kg5dbwj
	  section.data(14).logicalSrcIdx = 46;
	  section.data(14).dtTransOffset = 13;
	
	  ;% kmoqdzazlbs.cyq1lvu0w5
	  section.data(15).logicalSrcIdx = 47;
	  section.data(15).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.o3brjlgfg1.cbsqjogkey
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.o3brjlgfg1.nku2fseajd
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.nbm22evv0g.cbsqjogkey
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.nbm22evv0g.nku2fseajd
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.ebil10nhgi.cbsqjogkey
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.ebil10nhgi.nku2fseajd
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.op2jvp5kgrjz.cbsqjogkey
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.op2jvp5kgrjz.nku2fseajd
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.kfxzmrhmet.cbsqjogkey
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.kfxzmrhmet.nku2fseajd
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.b5yns515f3.cbsqjogkey
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.b5yns515f3.nku2fseajd
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.bw3qikpzl5.cbsqjogkey
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.bw3qikpzl5.nku2fseajd
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.eh2gxhlfvx.cbsqjogkey
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.eh2gxhlfvx.nku2fseajd
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.m5s5btvqpr.cbsqjogkey
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.m5s5btvqpr.nku2fseajd
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.imtastcd1c.cbsqjogkey
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.imtastcd1c.nku2fseajd
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.mal2e4bwfg.cbsqjogkey
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.mal2e4bwfg.nku2fseajd
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.fsgkfn1wuo.cbsqjogkey
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.fsgkfn1wuo.nku2fseajd
	  section.data(1).logicalSrcIdx = 71;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.judnob4hwn.cbsqjogkey
	  section.data(1).logicalSrcIdx = 72;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.judnob4hwn.nku2fseajd
	  section.data(1).logicalSrcIdx = 73;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.nq4cmgm03a.cbsqjogkey
	  section.data(1).logicalSrcIdx = 74;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.nq4cmgm03a.nku2fseajd
	  section.data(1).logicalSrcIdx = 75;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.ix1ebopk11.cbsqjogkey
	  section.data(1).logicalSrcIdx = 76;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.ix1ebopk11.nku2fseajd
	  section.data(1).logicalSrcIdx = 77;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(34) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.op2jvp5kgrj.cbsqjogkey
	  section.data(1).logicalSrcIdx = 78;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(35) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.op2jvp5kgrj.nku2fseajd
	  section.data(1).logicalSrcIdx = 79;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(36) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 955352013;
  targMap.checksum1 = 994041135;
  targMap.checksum2 = 1810031466;
  targMap.checksum3 = 3036390469;

