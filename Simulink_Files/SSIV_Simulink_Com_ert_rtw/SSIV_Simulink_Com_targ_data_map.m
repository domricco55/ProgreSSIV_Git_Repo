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
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% audekaprdr.FixPtBitwiseOperator1_BitMask
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% audekaprdr.FixPtBitwiseOperator_mhhzho00zb
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% audekaprdr.FixPtBitwiseOperator_iuw2zv1xh4
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% audekaprdr.FixPtBitwiseOperator_evsezmta4a
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% audekaprdr.FixPtBitwiseOperator_ikm2prctc4
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 25;
      section.data(25)  = dumData; %prealloc
      
	  ;% audekaprdr._Value
	  section.data(1).logicalSrcIdx = 5;
	  section.data(1).dtTransOffset = 0;
	
	  ;% audekaprdr._Value_bbqtwjbdzi
	  section.data(2).logicalSrcIdx = 6;
	  section.data(2).dtTransOffset = 1;
	
	  ;% audekaprdr.ConstMotTorquemNm_Value
	  section.data(3).logicalSrcIdx = 7;
	  section.data(3).dtTransOffset = 2;
	
	  ;% audekaprdr.bitsmNm_Gain
	  section.data(4).logicalSrcIdx = 8;
	  section.data(4).dtTransOffset = 3;
	
	  ;% audekaprdr.bitsmNm_Gain_iz44z4guht
	  section.data(5).logicalSrcIdx = 9;
	  section.data(5).dtTransOffset = 4;
	
	  ;% audekaprdr.bitsmNm_Gain_jjrfnm553k
	  section.data(6).logicalSrcIdx = 10;
	  section.data(6).dtTransOffset = 5;
	
	  ;% audekaprdr.bitsmNm_Gain_ljowsi2cmm
	  section.data(7).logicalSrcIdx = 11;
	  section.data(7).dtTransOffset = 6;
	
	  ;% audekaprdr.bitsmNm_Gain_iklhud12ye
	  section.data(8).logicalSrcIdx = 12;
	  section.data(8).dtTransOffset = 7;
	
	  ;% audekaprdr.TriggerValueRequiredforSubsyste
	  section.data(9).logicalSrcIdx = 13;
	  section.data(9).dtTransOffset = 8;
	
	  ;% audekaprdr.TriggerSwitch_Threshold
	  section.data(10).logicalSrcIdx = 14;
	  section.data(10).dtTransOffset = 9;
	
	  ;% audekaprdr.TimeallottedforSSIVtoinitialize
	  section.data(11).logicalSrcIdx = 15;
	  section.data(11).dtTransOffset = 10;
	
	  ;% audekaprdr.Compensatesfordirectionofspinwa
	  section.data(12).logicalSrcIdx = 16;
	  section.data(12).dtTransOffset = 11;
	
	  ;% audekaprdr.Compensatesfordirect_cyqa4lxb0n
	  section.data(13).logicalSrcIdx = 17;
	  section.data(13).dtTransOffset = 12;
	
	  ;% audekaprdr.EulerInttoDoubleScaleFactor_Gai
	  section.data(14).logicalSrcIdx = 18;
	  section.data(14).dtTransOffset = 13;
	
	  ;% audekaprdr.EulerInttoDoubleScaleFactor1_Ga
	  section.data(15).logicalSrcIdx = 19;
	  section.data(15).dtTransOffset = 14;
	
	  ;% audekaprdr.EulerInttoDoubleScaleFactor2_Ga
	  section.data(16).logicalSrcIdx = 20;
	  section.data(16).dtTransOffset = 15;
	
	  ;% audekaprdr.AccelerationInttoDoubleScaleFac
	  section.data(17).logicalSrcIdx = 21;
	  section.data(17).dtTransOffset = 16;
	
	  ;% audekaprdr.GyroscopeInttoDoubleScaleFactor
	  section.data(18).logicalSrcIdx = 22;
	  section.data(18).dtTransOffset = 17;
	
	  ;% audekaprdr.AccelerationInttoDou_gxoyxbctvl
	  section.data(19).logicalSrcIdx = 23;
	  section.data(19).dtTransOffset = 18;
	
	  ;% audekaprdr.GyroscopeInttoDouble_b3uzo31i4w
	  section.data(20).logicalSrcIdx = 24;
	  section.data(20).dtTransOffset = 19;
	
	  ;% audekaprdr.AccelerationInttoDou_felr2o3vjy
	  section.data(21).logicalSrcIdx = 25;
	  section.data(21).dtTransOffset = 20;
	
	  ;% audekaprdr.GyroscopeInttoDouble_msa2vzmmf0
	  section.data(22).logicalSrcIdx = 26;
	  section.data(22).dtTransOffset = 21;
	
	  ;% audekaprdr.Constant1_Value
	  section.data(23).logicalSrcIdx = 27;
	  section.data(23).dtTransOffset = 22;
	
	  ;% audekaprdr.TimeZero_Value
	  section.data(24).logicalSrcIdx = 28;
	  section.data(24).dtTransOffset = 23;
	
	  ;% audekaprdr.Constant2_Value
	  section.data(25).logicalSrcIdx = 29;
	  section.data(25).dtTransOffset = 24;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 58;
      section.data(58)  = dumData; %prealloc
      
	  ;% audekaprdr.DeadSwitch_Value
	  section.data(1).logicalSrcIdx = 30;
	  section.data(1).dtTransOffset = 0;
	
	  ;% audekaprdr.TakeData_Value
	  section.data(2).logicalSrcIdx = 31;
	  section.data(2).dtTransOffset = 1;
	
	  ;% audekaprdr.ServoandRadioOn_Value
	  section.data(3).logicalSrcIdx = 32;
	  section.data(3).dtTransOffset = 2;
	
	  ;% audekaprdr.MotorControllersOn_Value
	  section.data(4).logicalSrcIdx = 33;
	  section.data(4).dtTransOffset = 3;
	
	  ;% audekaprdr.IMUReset_Value
	  section.data(5).logicalSrcIdx = 34;
	  section.data(5).dtTransOffset = 4;
	
	  ;% audekaprdr.PrinttheregistermapontheTeensy_
	  section.data(6).logicalSrcIdx = 35;
	  section.data(6).dtTransOffset = 5;
	
	  ;% audekaprdr.PrinttheimudataontheTeensy_Valu
	  section.data(7).logicalSrcIdx = 36;
	  section.data(7).dtTransOffset = 6;
	
	  ;% audekaprdr.Printtheradiotranceiverdataonth
	  section.data(8).logicalSrcIdx = 37;
	  section.data(8).dtTransOffset = 7;
	
	  ;% audekaprdr.radio_throttleAddressNumber_Val
	  section.data(9).logicalSrcIdx = 38;
	  section.data(9).dtTransOffset = 8;
	
	  ;% audekaprdr.radio_throttleAddres_exvfxpj3wb
	  section.data(10).logicalSrcIdx = 39;
	  section.data(10).dtTransOffset = 9;
	
	  ;% audekaprdr.euler_headingAddressNumber_Valu
	  section.data(11).logicalSrcIdx = 40;
	  section.data(11).dtTransOffset = 10;
	
	  ;% audekaprdr.uint8_t1_Value
	  section.data(12).logicalSrcIdx = 41;
	  section.data(12).dtTransOffset = 11;
	
	  ;% audekaprdr.uint8_t2_Value
	  section.data(13).logicalSrcIdx = 42;
	  section.data(13).dtTransOffset = 12;
	
	  ;% audekaprdr.uint8_t3_Value
	  section.data(14).logicalSrcIdx = 43;
	  section.data(14).dtTransOffset = 13;
	
	  ;% audekaprdr.uint8_t4_Value
	  section.data(15).logicalSrcIdx = 44;
	  section.data(15).dtTransOffset = 14;
	
	  ;% audekaprdr.uint8_t5_Value
	  section.data(16).logicalSrcIdx = 45;
	  section.data(16).dtTransOffset = 15;
	
	  ;% audekaprdr.uint8_t6_Value
	  section.data(17).logicalSrcIdx = 46;
	  section.data(17).dtTransOffset = 16;
	
	  ;% audekaprdr.uint8_t7_Value
	  section.data(18).logicalSrcIdx = 47;
	  section.data(18).dtTransOffset = 17;
	
	  ;% audekaprdr.uint8_t8_Value
	  section.data(19).logicalSrcIdx = 48;
	  section.data(19).dtTransOffset = 18;
	
	  ;% audekaprdr.uint8_t9_Value
	  section.data(20).logicalSrcIdx = 49;
	  section.data(20).dtTransOffset = 19;
	
	  ;% audekaprdr.uint8_t10_Value
	  section.data(21).logicalSrcIdx = 50;
	  section.data(21).dtTransOffset = 20;
	
	  ;% audekaprdr.uint8_t11_Value
	  section.data(22).logicalSrcIdx = 51;
	  section.data(22).dtTransOffset = 21;
	
	  ;% audekaprdr.uint8_t12_Value
	  section.data(23).logicalSrcIdx = 52;
	  section.data(23).dtTransOffset = 22;
	
	  ;% audekaprdr.uint8_t13_Value
	  section.data(24).logicalSrcIdx = 53;
	  section.data(24).dtTransOffset = 23;
	
	  ;% audekaprdr.uint8_t14_Value
	  section.data(25).logicalSrcIdx = 54;
	  section.data(25).dtTransOffset = 24;
	
	  ;% audekaprdr.uint8_t15_Value
	  section.data(26).logicalSrcIdx = 55;
	  section.data(26).dtTransOffset = 25;
	
	  ;% audekaprdr.uint8_t16_Value
	  section.data(27).logicalSrcIdx = 56;
	  section.data(27).dtTransOffset = 26;
	
	  ;% audekaprdr.uint8_t17_Value
	  section.data(28).logicalSrcIdx = 57;
	  section.data(28).dtTransOffset = 27;
	
	  ;% audekaprdr.uint8_t18_Value
	  section.data(29).logicalSrcIdx = 58;
	  section.data(29).dtTransOffset = 28;
	
	  ;% audekaprdr.uint8_t19_Value
	  section.data(30).logicalSrcIdx = 59;
	  section.data(30).dtTransOffset = 29;
	
	  ;% audekaprdr.velocity_FRAddressNumber_Value
	  section.data(31).logicalSrcIdx = 60;
	  section.data(31).dtTransOffset = 30;
	
	  ;% audekaprdr.uint8_t1_Value_lno1pqpgau
	  section.data(32).logicalSrcIdx = 61;
	  section.data(32).dtTransOffset = 31;
	
	  ;% audekaprdr.uint8_t2_Value_h01j0dtng3
	  section.data(33).logicalSrcIdx = 62;
	  section.data(33).dtTransOffset = 32;
	
	  ;% audekaprdr.uint8_t3_Value_ojbhmh4dql
	  section.data(34).logicalSrcIdx = 63;
	  section.data(34).dtTransOffset = 33;
	
	  ;% audekaprdr.uint8_t4_Value_g3zwx4rgr4
	  section.data(35).logicalSrcIdx = 64;
	  section.data(35).dtTransOffset = 34;
	
	  ;% audekaprdr.uint8_t5_Value_c1y4l1anxp
	  section.data(36).logicalSrcIdx = 65;
	  section.data(36).dtTransOffset = 35;
	
	  ;% audekaprdr.uint8_t6_Value_crnrnd3vt1
	  section.data(37).logicalSrcIdx = 66;
	  section.data(37).dtTransOffset = 36;
	
	  ;% audekaprdr.uint8_t7_Value_euqjumixhk
	  section.data(38).logicalSrcIdx = 67;
	  section.data(38).dtTransOffset = 37;
	
	  ;% audekaprdr.uint8_t8_Value_kf0ktppryn
	  section.data(39).logicalSrcIdx = 68;
	  section.data(39).dtTransOffset = 38;
	
	  ;% audekaprdr.uint8_t9_Value_mjpcb5wgfy
	  section.data(40).logicalSrcIdx = 69;
	  section.data(40).dtTransOffset = 39;
	
	  ;% audekaprdr.node_errors0AddressNumber_Value
	  section.data(41).logicalSrcIdx = 70;
	  section.data(41).dtTransOffset = 40;
	
	  ;% audekaprdr.uint8_t1_Value_osffxyz322
	  section.data(42).logicalSrcIdx = 71;
	  section.data(42).dtTransOffset = 41;
	
	  ;% audekaprdr.uint8_t2_Value_be1gslf0db
	  section.data(43).logicalSrcIdx = 72;
	  section.data(43).dtTransOffset = 42;
	
	  ;% audekaprdr.uint8_t3_Value_ij0jf4g5dq
	  section.data(44).logicalSrcIdx = 73;
	  section.data(44).dtTransOffset = 43;
	
	  ;% audekaprdr.uint8_t4_Value_lcbb3njbqj
	  section.data(45).logicalSrcIdx = 74;
	  section.data(45).dtTransOffset = 44;
	
	  ;% audekaprdr.uint8_t5_Value_crdeyu0jn1
	  section.data(46).logicalSrcIdx = 75;
	  section.data(46).dtTransOffset = 45;
	
	  ;% audekaprdr.uint8_t6_Value_ctvwon1ehz
	  section.data(47).logicalSrcIdx = 76;
	  section.data(47).dtTransOffset = 46;
	
	  ;% audekaprdr.uint8_t7_Value_bqwaa044go
	  section.data(48).logicalSrcIdx = 77;
	  section.data(48).dtTransOffset = 47;
	
	  ;% audekaprdr.uint8_t8_Value_oldziuby0p
	  section.data(49).logicalSrcIdx = 78;
	  section.data(49).dtTransOffset = 48;
	
	  ;% audekaprdr.uint8_t9_Value_bwzvycrqy5
	  section.data(50).logicalSrcIdx = 79;
	  section.data(50).dtTransOffset = 49;
	
	  ;% audekaprdr.uint8_t1_Value_ia4e5oaw1u
	  section.data(51).logicalSrcIdx = 80;
	  section.data(51).dtTransOffset = 50;
	
	  ;% audekaprdr.uint8_t2_Value_naxjt0rvcp
	  section.data(52).logicalSrcIdx = 81;
	  section.data(52).dtTransOffset = 51;
	
	  ;% audekaprdr.uint8_t3_Value_fyilwaxi5e
	  section.data(53).logicalSrcIdx = 82;
	  section.data(53).dtTransOffset = 52;
	
	  ;% audekaprdr.uint8_t4_Value_duovhn5e5i
	  section.data(54).logicalSrcIdx = 83;
	  section.data(54).dtTransOffset = 53;
	
	  ;% audekaprdr.uint8_t5_Value_dzou0vne3f
	  section.data(55).logicalSrcIdx = 84;
	  section.data(55).dtTransOffset = 54;
	
	  ;% audekaprdr.uint8_t1_Value_m2yjzgvvms
	  section.data(56).logicalSrcIdx = 85;
	  section.data(56).dtTransOffset = 55;
	
	  ;% audekaprdr.uint8_t2_Value_fnasbuyxyr
	  section.data(57).logicalSrcIdx = 86;
	  section.data(57).dtTransOffset = 56;
	
	  ;% audekaprdr.uint8_t3_Value_lyjhgytxlw
	  section.data(58).logicalSrcIdx = 87;
	  section.data(58).dtTransOffset = 57;
	
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
    nTotSects     = 33;
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
      section.nData     = 27;
      section.data(27)  = dumData; %prealloc
      
	  ;% clyvxiydarg.jpsqjt4aqc
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% clyvxiydarg.gmju5vdzaw
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% clyvxiydarg.byd3vcunuk
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% clyvxiydarg.i41qlayz2l
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% clyvxiydarg.fq1qfqrphj
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% clyvxiydarg.p03v3l5dtg
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% clyvxiydarg.fklgmao3vf
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% clyvxiydarg.izfkoa3k2f
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% clyvxiydarg.dfksjrift1
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% clyvxiydarg.etf1h03rv2
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% clyvxiydarg.lfyr3el3kb
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% clyvxiydarg.naeaims21s
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% clyvxiydarg.avjg3r3biy
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% clyvxiydarg.jncb5cj1bo
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% clyvxiydarg.ggpb1i0ltl
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% clyvxiydarg.olboryt0kl
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% clyvxiydarg.jygvsqkpvf
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% clyvxiydarg.nrurb5ugeo
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% clyvxiydarg.iaryzarr32
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% clyvxiydarg.gqctnzw5tp
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% clyvxiydarg.fd4bkz2z3l
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
	  ;% clyvxiydarg.ob3td3wwfj
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 21;
	
	  ;% clyvxiydarg.fo20rz1yku
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 22;
	
	  ;% clyvxiydarg.nzcb34e1i2
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 23;
	
	  ;% clyvxiydarg.eq2lz15ikg
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 24;
	
	  ;% clyvxiydarg.lgjatwqg0h
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 25;
	
	  ;% clyvxiydarg.ptrclgo5i1
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 26;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.cwtpop0rmr
	  section.data(1).logicalSrcIdx = 30;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.f0emtpydi0
	  section.data(1).logicalSrcIdx = 27;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% clyvxiydarg.fisez1w02x
	  section.data(1).logicalSrcIdx = 28;
	  section.data(1).dtTransOffset = 0;
	
	  ;% clyvxiydarg.eyael1tplk
	  section.data(2).logicalSrcIdx = 29;
	  section.data(2).dtTransOffset = 2;
	
	  ;% clyvxiydarg.alpabwxe2w
	  section.data(3).logicalSrcIdx = 31;
	  section.data(3).dtTransOffset = 22;
	
	  ;% clyvxiydarg.nsazlii4tl
	  section.data(4).logicalSrcIdx = 32;
	  section.data(4).dtTransOffset = 23;
	
	  ;% clyvxiydarg.bwa40grhig
	  section.data(5).logicalSrcIdx = 33;
	  section.data(5).dtTransOffset = 24;
	
	  ;% clyvxiydarg.obom5x3d5k
	  section.data(6).logicalSrcIdx = 34;
	  section.data(6).dtTransOffset = 25;
	
	  ;% clyvxiydarg.blslpvafaj
	  section.data(7).logicalSrcIdx = 35;
	  section.data(7).dtTransOffset = 26;
	
	  ;% clyvxiydarg.bhdmoiwfl2
	  section.data(8).logicalSrcIdx = 36;
	  section.data(8).dtTransOffset = 27;
	
	  ;% clyvxiydarg.mzc2e1h4xa
	  section.data(9).logicalSrcIdx = 37;
	  section.data(9).dtTransOffset = 28;
	
	  ;% clyvxiydarg.n30ajead0c
	  section.data(10).logicalSrcIdx = 38;
	  section.data(10).dtTransOffset = 29;
	
	  ;% clyvxiydarg.pzzkogkfuo
	  section.data(11).logicalSrcIdx = 39;
	  section.data(11).dtTransOffset = 30;
	
	  ;% clyvxiydarg.ellnmxuy5c
	  section.data(12).logicalSrcIdx = 40;
	  section.data(12).dtTransOffset = 32;
	
	  ;% clyvxiydarg.ehp13vk0yn
	  section.data(13).logicalSrcIdx = 41;
	  section.data(13).dtTransOffset = 34;
	
	  ;% clyvxiydarg.gvjctcpowu
	  section.data(14).logicalSrcIdx = 42;
	  section.data(14).dtTransOffset = 36;
	
	  ;% clyvxiydarg.c1kldhmsiz
	  section.data(15).logicalSrcIdx = 43;
	  section.data(15).dtTransOffset = 38;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% clyvxiydarg.fkjscyvbyz
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
	  ;% clyvxiydarg.bpqhvv3cpv
	  section.data(2).logicalSrcIdx = 45;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.kw3hkiwkin.j5akpgvv3v
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.eyct3yxt3z.ax0zrlqhyg
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.aihwuaexvw.n4ajio1im5
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.cyc3zucud0.n4ajio1im5
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.bmfn1yplfs.n4ajio1im5
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.fyrgkvgkk3.n4ajio1im5
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.fwedfp34hs.n4ajio1im5
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ncoqhkv5ys.n4ajio1im5
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.mu5jwskqri.n4ajio1im5
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.lclrlp1izs.n4ajio1im5
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.fivyg2jeoh.n4ajio1im5
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.nuqu3wjywt.n4ajio1im5
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.pqp2qdkolc.n4ajio1im5
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ja3iuojduj.n4ajio1im5
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ooht12f5wu.n4ajio1im5
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ircfuffmvs.n4ajio1im5
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.dqtr2ragwc.n4ajio1im5
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ad5br1tctb.o0or2f1sl5
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.p5q4i2llvju.o0or2f1sl5
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.pma3dkyose.j5akpgvv3v
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.gpdaqcio2h.ax0zrlqhyg
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.djjjqxtsvn.j5akpgvv3v
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.crzjsfjgfq.ax0zrlqhyg
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.nkc3h3u2qx.j5akpgvv3v
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.lo2y5dsae1.ax0zrlqhyg
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.etyd41ymc0k.j5akpgvv3v
	  section.data(1).logicalSrcIdx = 71;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.cqwydeyjjzl.ax0zrlqhyg
	  section.data(1).logicalSrcIdx = 72;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.hnc055su4jj.n4ajio1im5
	  section.data(1).logicalSrcIdx = 73;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(33) = section;
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
    nTotSects     = 9;
    sectIdxOffset = 33;
    
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
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.p0itik4eqh
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% kmoqdzazlbs.pkxkl24b2g
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% kmoqdzazlbs.cbsqjogkey
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.iakgodzq5b
	  section.data(1).logicalSrcIdx = 3;
	  section.data(1).dtTransOffset = 0;
	
	  ;% kmoqdzazlbs.ji3y5cqka2
	  section.data(2).logicalSrcIdx = 4;
	  section.data(2).dtTransOffset = 1;
	
	  ;% kmoqdzazlbs.hslmt2wbm1
	  section.data(3).logicalSrcIdx = 5;
	  section.data(3).dtTransOffset = 2;
	
	  ;% kmoqdzazlbs.iztympubk5
	  section.data(4).logicalSrcIdx = 6;
	  section.data(4).dtTransOffset = 3;
	
	  ;% kmoqdzazlbs.pjtttqsyat
	  section.data(5).logicalSrcIdx = 7;
	  section.data(5).dtTransOffset = 4;
	
	  ;% kmoqdzazlbs.a2u0n35vkx
	  section.data(6).logicalSrcIdx = 8;
	  section.data(6).dtTransOffset = 5;
	
	  ;% kmoqdzazlbs.fogkdcpyxn
	  section.data(7).logicalSrcIdx = 9;
	  section.data(7).dtTransOffset = 6;
	
	  ;% kmoqdzazlbs.nd1taqo52d
	  section.data(8).logicalSrcIdx = 10;
	  section.data(8).dtTransOffset = 7;
	
	  ;% kmoqdzazlbs.oxyx0jt1zt
	  section.data(9).logicalSrcIdx = 11;
	  section.data(9).dtTransOffset = 8;
	
	  ;% kmoqdzazlbs.itlqodsvjm
	  section.data(10).logicalSrcIdx = 12;
	  section.data(10).dtTransOffset = 9;
	
	  ;% kmoqdzazlbs.du3r5tihjx
	  section.data(11).logicalSrcIdx = 13;
	  section.data(11).dtTransOffset = 10;
	
	  ;% kmoqdzazlbs.dfyhkf1lgs
	  section.data(12).logicalSrcIdx = 14;
	  section.data(12).dtTransOffset = 11;
	
	  ;% kmoqdzazlbs.as3iismmaz
	  section.data(13).logicalSrcIdx = 15;
	  section.data(13).dtTransOffset = 12;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 16;
      section.data(16)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.h544vmxpx5.LoggedData
	  section.data(1).logicalSrcIdx = 16;
	  section.data(1).dtTransOffset = 0;
	
	  ;% kmoqdzazlbs.j5q5dwdzen.LoggedData
	  section.data(2).logicalSrcIdx = 17;
	  section.data(2).dtTransOffset = 1;
	
	  ;% kmoqdzazlbs.bzefabupzc.LoggedData
	  section.data(3).logicalSrcIdx = 18;
	  section.data(3).dtTransOffset = 3;
	
	  ;% kmoqdzazlbs.lnd2o4jj1z.LoggedData
	  section.data(4).logicalSrcIdx = 19;
	  section.data(4).dtTransOffset = 4;
	
	  ;% kmoqdzazlbs.jh5cyx1ang.LoggedData
	  section.data(5).logicalSrcIdx = 20;
	  section.data(5).dtTransOffset = 5;
	
	  ;% kmoqdzazlbs.in5e0s4uxy.LoggedData
	  section.data(6).logicalSrcIdx = 21;
	  section.data(6).dtTransOffset = 6;
	
	  ;% kmoqdzazlbs.l51pt0mhbw.LoggedData
	  section.data(7).logicalSrcIdx = 22;
	  section.data(7).dtTransOffset = 7;
	
	  ;% kmoqdzazlbs.kh4sdo3mgz.LoggedData
	  section.data(8).logicalSrcIdx = 23;
	  section.data(8).dtTransOffset = 8;
	
	  ;% kmoqdzazlbs.a2zl4cae3t.LoggedData
	  section.data(9).logicalSrcIdx = 24;
	  section.data(9).dtTransOffset = 9;
	
	  ;% kmoqdzazlbs.l10ncjinas.LoggedData
	  section.data(10).logicalSrcIdx = 25;
	  section.data(10).dtTransOffset = 17;
	
	  ;% kmoqdzazlbs.cccf0t0za1.LoggedData
	  section.data(11).logicalSrcIdx = 26;
	  section.data(11).dtTransOffset = 21;
	
	  ;% kmoqdzazlbs.ns0tvfazpg.LoggedData
	  section.data(12).logicalSrcIdx = 27;
	  section.data(12).dtTransOffset = 24;
	
	  ;% kmoqdzazlbs.mpw52uizsr.LoggedData
	  section.data(13).logicalSrcIdx = 28;
	  section.data(13).dtTransOffset = 26;
	
	  ;% kmoqdzazlbs.fxvn4qyb0h.LoggedData
	  section.data(14).logicalSrcIdx = 29;
	  section.data(14).dtTransOffset = 28;
	
	  ;% kmoqdzazlbs.myf2l5zu42.LoggedData
	  section.data(15).logicalSrcIdx = 30;
	  section.data(15).dtTransOffset = 30;
	
	  ;% kmoqdzazlbs.pqk21lwi5l.LoggedData
	  section.data(16).logicalSrcIdx = 31;
	  section.data(16).dtTransOffset = 31;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.js1pmoelqv
	  section.data(1).logicalSrcIdx = 32;
	  section.data(1).dtTransOffset = 0;
	
	  ;% kmoqdzazlbs.phgvbjym0p
	  section.data(2).logicalSrcIdx = 33;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 18;
      section.data(18)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.mp1ginymjj
	  section.data(1).logicalSrcIdx = 34;
	  section.data(1).dtTransOffset = 0;
	
	  ;% kmoqdzazlbs.hbtmjfnvip
	  section.data(2).logicalSrcIdx = 35;
	  section.data(2).dtTransOffset = 1;
	
	  ;% kmoqdzazlbs.exk53tdlg3
	  section.data(3).logicalSrcIdx = 36;
	  section.data(3).dtTransOffset = 2;
	
	  ;% kmoqdzazlbs.hiktqtlwmz
	  section.data(4).logicalSrcIdx = 37;
	  section.data(4).dtTransOffset = 3;
	
	  ;% kmoqdzazlbs.dv3lfxn2xh
	  section.data(5).logicalSrcIdx = 38;
	  section.data(5).dtTransOffset = 4;
	
	  ;% kmoqdzazlbs.jb4fs5m310
	  section.data(6).logicalSrcIdx = 39;
	  section.data(6).dtTransOffset = 5;
	
	  ;% kmoqdzazlbs.n14uq0f0yw
	  section.data(7).logicalSrcIdx = 40;
	  section.data(7).dtTransOffset = 6;
	
	  ;% kmoqdzazlbs.ltufaxpna0
	  section.data(8).logicalSrcIdx = 41;
	  section.data(8).dtTransOffset = 7;
	
	  ;% kmoqdzazlbs.i3af2m25ya
	  section.data(9).logicalSrcIdx = 42;
	  section.data(9).dtTransOffset = 8;
	
	  ;% kmoqdzazlbs.kl5wif40vr
	  section.data(10).logicalSrcIdx = 43;
	  section.data(10).dtTransOffset = 9;
	
	  ;% kmoqdzazlbs.lz3ugc4cwh
	  section.data(11).logicalSrcIdx = 44;
	  section.data(11).dtTransOffset = 10;
	
	  ;% kmoqdzazlbs.orrtyae4cj
	  section.data(12).logicalSrcIdx = 45;
	  section.data(12).dtTransOffset = 11;
	
	  ;% kmoqdzazlbs.mlvjnryb2f
	  section.data(13).logicalSrcIdx = 46;
	  section.data(13).dtTransOffset = 12;
	
	  ;% kmoqdzazlbs.gyhved5o0g
	  section.data(14).logicalSrcIdx = 47;
	  section.data(14).dtTransOffset = 13;
	
	  ;% kmoqdzazlbs.pthrmzewo5
	  section.data(15).logicalSrcIdx = 48;
	  section.data(15).dtTransOffset = 14;
	
	  ;% kmoqdzazlbs.nku2fseajd
	  section.data(16).logicalSrcIdx = 49;
	  section.data(16).dtTransOffset = 15;
	
	  ;% kmoqdzazlbs.pb2kg5dbwj
	  section.data(17).logicalSrcIdx = 50;
	  section.data(17).dtTransOffset = 16;
	
	  ;% kmoqdzazlbs.dstyzu0rlu
	  section.data(18).logicalSrcIdx = 51;
	  section.data(18).dtTransOffset = 17;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.ad5br1tctb.msyjj10o5w
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.ad5br1tctb.b1wj05bnq3
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.p5q4i2llvju.msyjj10o5w
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.p5q4i2llvju.b1wj05bnq3
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
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


  targMap.checksum0 = 3110750142;
  targMap.checksum1 = 2197541632;
  targMap.checksum2 = 3890691610;
  targMap.checksum3 = 56769280;

