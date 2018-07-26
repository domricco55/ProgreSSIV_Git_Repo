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
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% audekaprdr.FixPtBitwiseOperator1_BitMask
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% audekaprdr.FixPtBitwiseOperator_b2teu3fanr
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% audekaprdr.FixPtBitwiseOperator_lwwugdgd4i
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% audekaprdr.FixPtBitwiseOperator_dzmkvs5xk1
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% audekaprdr.FixPtBitwiseOperator_jvzpos55kn
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% audekaprdr.FixPtBitwiseOperator_bhnevrebin
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% audekaprdr.FixPtBitwiseOperator_ihzvxioflp
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% audekaprdr.FixPtBitwiseOperator_cm33fo1ymv
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% audekaprdr.FixPtBitwiseOperator_nhxlwfddca
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% audekaprdr.FixPtBitwiseOperator_gx4fcf0wux
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% audekaprdr.FixPtBitwiseOperator_h4ulqzgyji
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% audekaprdr.FixPtBitwiseOperator_ncfxm2jagp
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% audekaprdr.FixPtBitwiseOperator_pv02zjt0gc
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% audekaprdr.FixPtBitwiseOperator_fnveiwfrqo
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% audekaprdr.FixPtBitwiseOperator_psltjvv4ax
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 25;
      section.data(25)  = dumData; %prealloc
      
	  ;% audekaprdr._Value
	  section.data(1).logicalSrcIdx = 15;
	  section.data(1).dtTransOffset = 0;
	
	  ;% audekaprdr.ConstMotTorquemNm_Value
	  section.data(2).logicalSrcIdx = 16;
	  section.data(2).dtTransOffset = 1;
	
	  ;% audekaprdr.bitsmNm_Gain
	  section.data(3).logicalSrcIdx = 17;
	  section.data(3).dtTransOffset = 2;
	
	  ;% audekaprdr.ConstantOffsetFromRadio_Value
	  section.data(4).logicalSrcIdx = 18;
	  section.data(4).dtTransOffset = 3;
	
	  ;% audekaprdr.DeadSwitchValue_Value
	  section.data(5).logicalSrcIdx = 19;
	  section.data(5).dtTransOffset = 4;
	
	  ;% audekaprdr.DeadSwitch_Threshold
	  section.data(6).logicalSrcIdx = 20;
	  section.data(6).dtTransOffset = 5;
	
	  ;% audekaprdr.bitsmNm_Gain_n31nuftucu
	  section.data(7).logicalSrcIdx = 21;
	  section.data(7).dtTransOffset = 6;
	
	  ;% audekaprdr.bitsmNm_Gain_iz44z4guht
	  section.data(8).logicalSrcIdx = 22;
	  section.data(8).dtTransOffset = 7;
	
	  ;% audekaprdr.bitsmNm_Gain_jjrfnm553k
	  section.data(9).logicalSrcIdx = 23;
	  section.data(9).dtTransOffset = 8;
	
	  ;% audekaprdr.bitsmNm_Gain_ljowsi2cmm
	  section.data(10).logicalSrcIdx = 24;
	  section.data(10).dtTransOffset = 9;
	
	  ;% audekaprdr.AccelerationInttoDoubleScaleFac
	  section.data(11).logicalSrcIdx = 25;
	  section.data(11).dtTransOffset = 10;
	
	  ;% audekaprdr.GyroscopeInttoDoubleScaleFactor
	  section.data(12).logicalSrcIdx = 26;
	  section.data(12).dtTransOffset = 11;
	
	  ;% audekaprdr.AccelerationInttoDou_nsgzzd3dys
	  section.data(13).logicalSrcIdx = 27;
	  section.data(13).dtTransOffset = 12;
	
	  ;% audekaprdr.GyroscopeInttoDouble_leu0lmtkw5
	  section.data(14).logicalSrcIdx = 28;
	  section.data(14).dtTransOffset = 13;
	
	  ;% audekaprdr.AccelerationInttoDou_n25pvjipoq
	  section.data(15).logicalSrcIdx = 29;
	  section.data(15).dtTransOffset = 14;
	
	  ;% audekaprdr.GyroscopeInttoDouble_fnfguslit0
	  section.data(16).logicalSrcIdx = 30;
	  section.data(16).dtTransOffset = 15;
	
	  ;% audekaprdr.EulerInttoDoubleScaleFactor_Gai
	  section.data(17).logicalSrcIdx = 31;
	  section.data(17).dtTransOffset = 16;
	
	  ;% audekaprdr.EulerInttoDoubleScal_iiz5hgtpf2
	  section.data(18).logicalSrcIdx = 32;
	  section.data(18).dtTransOffset = 17;
	
	  ;% audekaprdr.EulerInttoDoubleScal_g31zf1epte
	  section.data(19).logicalSrcIdx = 33;
	  section.data(19).dtTransOffset = 18;
	
	  ;% audekaprdr.Constant1_Value
	  section.data(20).logicalSrcIdx = 34;
	  section.data(20).dtTransOffset = 19;
	
	  ;% audekaprdr.Constant_Value
	  section.data(21).logicalSrcIdx = 35;
	  section.data(21).dtTransOffset = 20;
	
	  ;% audekaprdr.Constant2_Value
	  section.data(22).logicalSrcIdx = 36;
	  section.data(22).dtTransOffset = 21;
	
	  ;% audekaprdr.Constant4_Value
	  section.data(23).logicalSrcIdx = 37;
	  section.data(23).dtTransOffset = 22;
	
	  ;% audekaprdr.Constant3_Value
	  section.data(24).logicalSrcIdx = 38;
	  section.data(24).dtTransOffset = 23;
	
	  ;% audekaprdr.Constant5_Value
	  section.data(25).logicalSrcIdx = 39;
	  section.data(25).dtTransOffset = 24;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 68;
      section.data(68)  = dumData; %prealloc
      
	  ;% audekaprdr.euler_headingAddressNumber_Valu
	  section.data(1).logicalSrcIdx = 40;
	  section.data(1).dtTransOffset = 0;
	
	  ;% audekaprdr.uint8_t1_Value
	  section.data(2).logicalSrcIdx = 41;
	  section.data(2).dtTransOffset = 1;
	
	  ;% audekaprdr.uint8_t2_Value
	  section.data(3).logicalSrcIdx = 42;
	  section.data(3).dtTransOffset = 2;
	
	  ;% audekaprdr.uint8_t3_Value
	  section.data(4).logicalSrcIdx = 43;
	  section.data(4).dtTransOffset = 3;
	
	  ;% audekaprdr.euler_rollAddressNumber_Value
	  section.data(5).logicalSrcIdx = 44;
	  section.data(5).dtTransOffset = 4;
	
	  ;% audekaprdr.uint8_t1_Value_pdh1mmrkaf
	  section.data(6).logicalSrcIdx = 45;
	  section.data(6).dtTransOffset = 5;
	
	  ;% audekaprdr.uint8_t2_Value_bjkzcm1v50
	  section.data(7).logicalSrcIdx = 46;
	  section.data(7).dtTransOffset = 6;
	
	  ;% audekaprdr.uint8_t3_Value_bzki1yseu2
	  section.data(8).logicalSrcIdx = 47;
	  section.data(8).dtTransOffset = 7;
	
	  ;% audekaprdr.euler_pitchAddressNumber_Value
	  section.data(9).logicalSrcIdx = 48;
	  section.data(9).dtTransOffset = 8;
	
	  ;% audekaprdr.uint8_t1_Value_nh5qfyju0z
	  section.data(10).logicalSrcIdx = 49;
	  section.data(10).dtTransOffset = 9;
	
	  ;% audekaprdr.uint8_t2_Value_g33fsjovlh
	  section.data(11).logicalSrcIdx = 50;
	  section.data(11).dtTransOffset = 10;
	
	  ;% audekaprdr.uint8_t3_Value_fcyoyjujtb
	  section.data(12).logicalSrcIdx = 51;
	  section.data(12).dtTransOffset = 11;
	
	  ;% audekaprdr.gyr_xAddressNumber_Value
	  section.data(13).logicalSrcIdx = 52;
	  section.data(13).dtTransOffset = 12;
	
	  ;% audekaprdr.uint8_t1_Value_j2wfmnih52
	  section.data(14).logicalSrcIdx = 53;
	  section.data(14).dtTransOffset = 13;
	
	  ;% audekaprdr.uint8_t2_Value_l24qi4amhg
	  section.data(15).logicalSrcIdx = 54;
	  section.data(15).dtTransOffset = 14;
	
	  ;% audekaprdr.uint8_t3_Value_abjhsc0f24
	  section.data(16).logicalSrcIdx = 55;
	  section.data(16).dtTransOffset = 15;
	
	  ;% audekaprdr.acc_xAddressNumber_Value
	  section.data(17).logicalSrcIdx = 56;
	  section.data(17).dtTransOffset = 16;
	
	  ;% audekaprdr.uint8_t1_Value_d1nmexi4u4
	  section.data(18).logicalSrcIdx = 57;
	  section.data(18).dtTransOffset = 17;
	
	  ;% audekaprdr.uint8_t2_Value_a4kbzdzszs
	  section.data(19).logicalSrcIdx = 58;
	  section.data(19).dtTransOffset = 18;
	
	  ;% audekaprdr.uint8_t3_Value_crbst3qg0d
	  section.data(20).logicalSrcIdx = 59;
	  section.data(20).dtTransOffset = 19;
	
	  ;% audekaprdr.gyr_yAddressNumber_Value
	  section.data(21).logicalSrcIdx = 60;
	  section.data(21).dtTransOffset = 20;
	
	  ;% audekaprdr.uint8_t1_Value_hhpzgdklhj
	  section.data(22).logicalSrcIdx = 61;
	  section.data(22).dtTransOffset = 21;
	
	  ;% audekaprdr.uint8_t2_Value_kfo5pj123x
	  section.data(23).logicalSrcIdx = 62;
	  section.data(23).dtTransOffset = 22;
	
	  ;% audekaprdr.uint8_t3_Value_llnlocx0jp
	  section.data(24).logicalSrcIdx = 63;
	  section.data(24).dtTransOffset = 23;
	
	  ;% audekaprdr.acc_yAddressNumber_Value
	  section.data(25).logicalSrcIdx = 64;
	  section.data(25).dtTransOffset = 24;
	
	  ;% audekaprdr.uint8_t1_Value_k55hriosiw
	  section.data(26).logicalSrcIdx = 65;
	  section.data(26).dtTransOffset = 25;
	
	  ;% audekaprdr.uint8_t2_Value_ewsrijoi1y
	  section.data(27).logicalSrcIdx = 66;
	  section.data(27).dtTransOffset = 26;
	
	  ;% audekaprdr.uint8_t3_Value_csq2nflakv
	  section.data(28).logicalSrcIdx = 67;
	  section.data(28).dtTransOffset = 27;
	
	  ;% audekaprdr.gyr_zAddressNumber_Value
	  section.data(29).logicalSrcIdx = 68;
	  section.data(29).dtTransOffset = 28;
	
	  ;% audekaprdr.uint8_t1_Value_iarfsgp4wp
	  section.data(30).logicalSrcIdx = 69;
	  section.data(30).dtTransOffset = 29;
	
	  ;% audekaprdr.uint8_t2_Value_h25nsb42dk
	  section.data(31).logicalSrcIdx = 70;
	  section.data(31).dtTransOffset = 30;
	
	  ;% audekaprdr.uint8_t3_Value_irei2yyusa
	  section.data(32).logicalSrcIdx = 71;
	  section.data(32).dtTransOffset = 31;
	
	  ;% audekaprdr.acc_zAddressNumber_Value
	  section.data(33).logicalSrcIdx = 72;
	  section.data(33).dtTransOffset = 32;
	
	  ;% audekaprdr.uint8_t1_Value_escjrdlkcn
	  section.data(34).logicalSrcIdx = 73;
	  section.data(34).dtTransOffset = 33;
	
	  ;% audekaprdr.uint8_t2_Value_ohr50x5o4g
	  section.data(35).logicalSrcIdx = 74;
	  section.data(35).dtTransOffset = 34;
	
	  ;% audekaprdr.uint8_t3_Value_g5ikrmq33j
	  section.data(36).logicalSrcIdx = 75;
	  section.data(36).dtTransOffset = 35;
	
	  ;% audekaprdr.radio_throttleAddressNumber_Val
	  section.data(37).logicalSrcIdx = 76;
	  section.data(37).dtTransOffset = 36;
	
	  ;% audekaprdr.uint8_t1_Value_blcwsn3mod
	  section.data(38).logicalSrcIdx = 77;
	  section.data(38).dtTransOffset = 37;
	
	  ;% audekaprdr.uint8_t2_Value_feo10nb4xc
	  section.data(39).logicalSrcIdx = 78;
	  section.data(39).dtTransOffset = 38;
	
	  ;% audekaprdr.uint8_t3_Value_p3y25qn4th
	  section.data(40).logicalSrcIdx = 79;
	  section.data(40).dtTransOffset = 39;
	
	  ;% audekaprdr.radio_steeringAddressNumber_Val
	  section.data(41).logicalSrcIdx = 80;
	  section.data(41).dtTransOffset = 40;
	
	  ;% audekaprdr.uint8_t1_Value_mwwrewolew
	  section.data(42).logicalSrcIdx = 81;
	  section.data(42).dtTransOffset = 41;
	
	  ;% audekaprdr.uint8_t2_Value_plp2fa3e20
	  section.data(43).logicalSrcIdx = 82;
	  section.data(43).dtTransOffset = 42;
	
	  ;% audekaprdr.uint8_t3_Value_feq0mqtkvh
	  section.data(44).logicalSrcIdx = 83;
	  section.data(44).dtTransOffset = 43;
	
	  ;% audekaprdr.velocity_RRAddressNumber_Value
	  section.data(45).logicalSrcIdx = 84;
	  section.data(45).dtTransOffset = 44;
	
	  ;% audekaprdr.uint8_t1_Value_iswfbqmgg0
	  section.data(46).logicalSrcIdx = 85;
	  section.data(46).dtTransOffset = 45;
	
	  ;% audekaprdr.uint8_t2_Value_og3vod555z
	  section.data(47).logicalSrcIdx = 86;
	  section.data(47).dtTransOffset = 46;
	
	  ;% audekaprdr.uint8_t3_Value_o4pefzbbdu
	  section.data(48).logicalSrcIdx = 87;
	  section.data(48).dtTransOffset = 47;
	
	  ;% audekaprdr.velocity_RLAddressNumber_Value
	  section.data(49).logicalSrcIdx = 88;
	  section.data(49).dtTransOffset = 48;
	
	  ;% audekaprdr.uint8_t1_Value_cvek4esgvd
	  section.data(50).logicalSrcIdx = 89;
	  section.data(50).dtTransOffset = 49;
	
	  ;% audekaprdr.uint8_t2_Value_lseyezibvx
	  section.data(51).logicalSrcIdx = 90;
	  section.data(51).dtTransOffset = 50;
	
	  ;% audekaprdr.uint8_t3_Value_o1yzfl3g0m
	  section.data(52).logicalSrcIdx = 91;
	  section.data(52).dtTransOffset = 51;
	
	  ;% audekaprdr.velocity_FRAddressNumber_Value
	  section.data(53).logicalSrcIdx = 92;
	  section.data(53).dtTransOffset = 52;
	
	  ;% audekaprdr.uint8_t1_Value_e4uo010ilu
	  section.data(54).logicalSrcIdx = 93;
	  section.data(54).dtTransOffset = 53;
	
	  ;% audekaprdr.uint8_t2_Value_ndppfky1ku
	  section.data(55).logicalSrcIdx = 94;
	  section.data(55).dtTransOffset = 54;
	
	  ;% audekaprdr.uint8_t3_Value_gqtbi3ry5p
	  section.data(56).logicalSrcIdx = 95;
	  section.data(56).dtTransOffset = 55;
	
	  ;% audekaprdr.velocity_FLAddressNumber_Value
	  section.data(57).logicalSrcIdx = 96;
	  section.data(57).dtTransOffset = 56;
	
	  ;% audekaprdr.uint8_t1_Value_fbwzrt0xsu
	  section.data(58).logicalSrcIdx = 97;
	  section.data(58).dtTransOffset = 57;
	
	  ;% audekaprdr.uint8_t2_Value_nlddlhtmy4
	  section.data(59).logicalSrcIdx = 98;
	  section.data(59).dtTransOffset = 58;
	
	  ;% audekaprdr.uint8_t3_Value_p5kni5nbh4
	  section.data(60).logicalSrcIdx = 99;
	  section.data(60).dtTransOffset = 59;
	
	  ;% audekaprdr.DeadSwitch_Value
	  section.data(61).logicalSrcIdx = 100;
	  section.data(61).dtTransOffset = 60;
	
	  ;% audekaprdr.TakeData_Value
	  section.data(62).logicalSrcIdx = 101;
	  section.data(62).dtTransOffset = 61;
	
	  ;% audekaprdr.ServoandRadioOn_Value
	  section.data(63).logicalSrcIdx = 102;
	  section.data(63).dtTransOffset = 62;
	
	  ;% audekaprdr.MotorControllersOn_Value
	  section.data(64).logicalSrcIdx = 103;
	  section.data(64).dtTransOffset = 63;
	
	  ;% audekaprdr.IMUReset_Value
	  section.data(65).logicalSrcIdx = 104;
	  section.data(65).dtTransOffset = 64;
	
	  ;% audekaprdr.PrinttheregistermapontheTeensy_
	  section.data(66).logicalSrcIdx = 105;
	  section.data(66).dtTransOffset = 65;
	
	  ;% audekaprdr.PrinttheimudataontheTeensy_Valu
	  section.data(67).logicalSrcIdx = 106;
	  section.data(67).dtTransOffset = 66;
	
	  ;% audekaprdr.Printtheradiotranceiverdataonth
	  section.data(68).logicalSrcIdx = 107;
	  section.data(68).dtTransOffset = 67;
	
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
    nTotSects     = 43;
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
      section.nData     = 17;
      section.data(17)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ic0gfcapnp
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% clyvxiydarg.lbyt1socd0
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% clyvxiydarg.otbtevevhj
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% clyvxiydarg.c2stu5nmv4
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% clyvxiydarg.bh2ikohbii
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% clyvxiydarg.btpkusrg1l
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% clyvxiydarg.he4lgyanuo
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% clyvxiydarg.dmoxdxwpke
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% clyvxiydarg.mmhtsaanxd
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% clyvxiydarg.epo4qe1zkt
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% clyvxiydarg.bgxxtuazwx
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% clyvxiydarg.j2olnqyzm1
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% clyvxiydarg.aft2a2enuo
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% clyvxiydarg.hrmgakyzvl
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% clyvxiydarg.bt23druc1y
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% clyvxiydarg.fuzkxqetlt
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% clyvxiydarg.cdtkwci2k5
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% clyvxiydarg.f0emtpydi0
	  section.data(1).logicalSrcIdx = 17;
	  section.data(1).dtTransOffset = 0;
	
	  ;% clyvxiydarg.iha3pgustb
	  section.data(2).logicalSrcIdx = 18;
	  section.data(2).dtTransOffset = 1;
	
	  ;% clyvxiydarg.eky3kovlym
	  section.data(3).logicalSrcIdx = 19;
	  section.data(3).dtTransOffset = 2;
	
	  ;% clyvxiydarg.bewuwo2jpj
	  section.data(4).logicalSrcIdx = 20;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% clyvxiydarg.alpabwxe2w
	  section.data(1).logicalSrcIdx = 21;
	  section.data(1).dtTransOffset = 0;
	
	  ;% clyvxiydarg.nsazlii4tl
	  section.data(2).logicalSrcIdx = 22;
	  section.data(2).dtTransOffset = 1;
	
	  ;% clyvxiydarg.bwa40grhig
	  section.data(3).logicalSrcIdx = 23;
	  section.data(3).dtTransOffset = 2;
	
	  ;% clyvxiydarg.obom5x3d5k
	  section.data(4).logicalSrcIdx = 24;
	  section.data(4).dtTransOffset = 3;
	
	  ;% clyvxiydarg.blslpvafaj
	  section.data(5).logicalSrcIdx = 25;
	  section.data(5).dtTransOffset = 4;
	
	  ;% clyvxiydarg.bhdmoiwfl2
	  section.data(6).logicalSrcIdx = 26;
	  section.data(6).dtTransOffset = 5;
	
	  ;% clyvxiydarg.mzc2e1h4xa
	  section.data(7).logicalSrcIdx = 27;
	  section.data(7).dtTransOffset = 6;
	
	  ;% clyvxiydarg.n30ajead0c
	  section.data(8).logicalSrcIdx = 28;
	  section.data(8).dtTransOffset = 7;
	
	  ;% clyvxiydarg.fisez1w02x
	  section.data(9).logicalSrcIdx = 29;
	  section.data(9).dtTransOffset = 8;
	
	  ;% clyvxiydarg.pzzkogkfuo
	  section.data(10).logicalSrcIdx = 30;
	  section.data(10).dtTransOffset = 10;
	
	  ;% clyvxiydarg.ellnmxuy5c
	  section.data(11).logicalSrcIdx = 31;
	  section.data(11).dtTransOffset = 12;
	
	  ;% clyvxiydarg.ehp13vk0yn
	  section.data(12).logicalSrcIdx = 32;
	  section.data(12).dtTransOffset = 14;
	
	  ;% clyvxiydarg.gvjctcpowu
	  section.data(13).logicalSrcIdx = 33;
	  section.data(13).dtTransOffset = 16;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ox00g0fjit.l5vcja13yp
	  section.data(1).logicalSrcIdx = 34;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.noxa1mf3ts.l5vcja13yp
	  section.data(1).logicalSrcIdx = 35;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.c22lkw3uta.l5vcja13yp
	  section.data(1).logicalSrcIdx = 36;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ngxnr31lpd.l5vcja13yp
	  section.data(1).logicalSrcIdx = 37;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.pma3dkyose.m3vx4enmn0
	  section.data(1).logicalSrcIdx = 38;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.gpdaqcio2h.pngymb2243
	  section.data(1).logicalSrcIdx = 39;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.djjjqxtsvn.m3vx4enmn0
	  section.data(1).logicalSrcIdx = 40;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.crzjsfjgfq.pngymb2243
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.nkc3h3u2qx.m3vx4enmn0
	  section.data(1).logicalSrcIdx = 42;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.lo2y5dsae1.pngymb2243
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.etyd41ymc0.m3vx4enmn0
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.cqwydeyjjz.pngymb2243
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.kw3hkiwkina.m3vx4enmn0
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.eyct3yxt3z0.pngymb2243
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.kkwkteqlx4.l5vcja13yp
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.h4on452olv.l5vcja13yp
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.bxjhchcsas.l5vcja13yp
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.aapspwvylg.l5vcja13yp
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.df2u43nrli.l5vcja13yp
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.nafrgvutkz.l5vcja13yp
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ozpzbkn2ss.l5vcja13yp
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.k1qnchht15.l5vcja13yp
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.de4ulgfcag.l5vcja13yp
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.mtjkmmufcg.l5vcja13yp
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.mmyolc4cfgd.l5vcja13yp
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.o3brjlgfg1.axmhpusnnw
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.nbm22evv0g.axmhpusnnw
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ebil10nhgi.axmhpusnnw
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.imtastcd1c.axmhpusnnw
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.mal2e4bwfg.axmhpusnnw
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.fsgkfn1wuo.axmhpusnnw
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(34) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.judnob4hwn.axmhpusnnw
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(35) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.nq4cmgm03a.axmhpusnnw
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(36) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ix1ebopk11.axmhpusnnw
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(37) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.op2jvp5kgr.axmhpusnnw
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(38) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.kfxzmrhmet.axmhpusnnw
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(39) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.eh2gxhlfvx.axmhpusnnw
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(40) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.m5s5btvqpr.axmhpusnnw
	  section.data(1).logicalSrcIdx = 71;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(41) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.b5yns515f3.axmhpusnnw
	  section.data(1).logicalSrcIdx = 72;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(42) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.bw3qikpzl52.axmhpusnnw
	  section.data(1).logicalSrcIdx = 73;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(43) = section;
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
    nTotSects     = 34;
    sectIdxOffset = 43;
    
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
      
	  ;% kmoqdzazlbs.ji3y5cqka2
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% kmoqdzazlbs.hslmt2wbm1
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% kmoqdzazlbs.iztympubk5
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% kmoqdzazlbs.pjtttqsyat
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% kmoqdzazlbs.a2u0n35vkx
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% kmoqdzazlbs.fogkdcpyxn
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% kmoqdzazlbs.nd1taqo52d
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% kmoqdzazlbs.oxyx0jt1zt
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% kmoqdzazlbs.iakgodzq5b
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
      
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.mt1ykus4yg.LoggedData
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
	  ;% kmoqdzazlbs.nqx13tjgsu.LoggedData
	  section.data(2).logicalSrcIdx = 14;
	  section.data(2).dtTransOffset = 1;
	
	  ;% kmoqdzazlbs.mie3drc5gs.LoggedData
	  section.data(3).logicalSrcIdx = 15;
	  section.data(3).dtTransOffset = 2;
	
	  ;% kmoqdzazlbs.pqk21lwi5l.LoggedData
	  section.data(4).logicalSrcIdx = 16;
	  section.data(4).dtTransOffset = 3;
	
	  ;% kmoqdzazlbs.d23of3cb0r.LoggedData
	  section.data(5).logicalSrcIdx = 17;
	  section.data(5).dtTransOffset = 4;
	
	  ;% kmoqdzazlbs.o25zpgphrs.LoggedData
	  section.data(6).logicalSrcIdx = 18;
	  section.data(6).dtTransOffset = 6;
	
	  ;% kmoqdzazlbs.f1hfbhbquj.LoggedData
	  section.data(7).logicalSrcIdx = 19;
	  section.data(7).dtTransOffset = 10;
	
	  ;% kmoqdzazlbs.mzgaxx2u5x.LoggedData
	  section.data(8).logicalSrcIdx = 20;
	  section.data(8).dtTransOffset = 12;
	
	  ;% kmoqdzazlbs.ipczob0ufs.LoggedData
	  section.data(9).logicalSrcIdx = 21;
	  section.data(9).dtTransOffset = 14;
	
	  ;% kmoqdzazlbs.cxr4a2rgrf.LoggedData
	  section.data(10).logicalSrcIdx = 22;
	  section.data(10).dtTransOffset = 16;
	
	  ;% kmoqdzazlbs.ajtuey5l4l.LoggedData
	  section.data(11).logicalSrcIdx = 23;
	  section.data(11).dtTransOffset = 19;
	
	  ;% kmoqdzazlbs.d1gcozn234.LoggedData
	  section.data(12).logicalSrcIdx = 24;
	  section.data(12).dtTransOffset = 20;
	
	  ;% kmoqdzazlbs.lqavjnmqhy.LoggedData
	  section.data(13).logicalSrcIdx = 25;
	  section.data(13).dtTransOffset = 21;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.js1pmoelqv
	  section.data(1).logicalSrcIdx = 26;
	  section.data(1).dtTransOffset = 0;
	
	  ;% kmoqdzazlbs.cyggdagd2p
	  section.data(2).logicalSrcIdx = 27;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.hiktqtlwmz
	  section.data(1).logicalSrcIdx = 28;
	  section.data(1).dtTransOffset = 0;
	
	  ;% kmoqdzazlbs.dv3lfxn2xh
	  section.data(2).logicalSrcIdx = 29;
	  section.data(2).dtTransOffset = 1;
	
	  ;% kmoqdzazlbs.jb4fs5m310
	  section.data(3).logicalSrcIdx = 30;
	  section.data(3).dtTransOffset = 2;
	
	  ;% kmoqdzazlbs.n14uq0f0yw
	  section.data(4).logicalSrcIdx = 31;
	  section.data(4).dtTransOffset = 3;
	
	  ;% kmoqdzazlbs.ltufaxpna0
	  section.data(5).logicalSrcIdx = 32;
	  section.data(5).dtTransOffset = 4;
	
	  ;% kmoqdzazlbs.i3af2m25ya
	  section.data(6).logicalSrcIdx = 33;
	  section.data(6).dtTransOffset = 5;
	
	  ;% kmoqdzazlbs.kl5wif40vr
	  section.data(7).logicalSrcIdx = 34;
	  section.data(7).dtTransOffset = 6;
	
	  ;% kmoqdzazlbs.lz3ugc4cwh
	  section.data(8).logicalSrcIdx = 35;
	  section.data(8).dtTransOffset = 7;
	
	  ;% kmoqdzazlbs.mp1ginymjj
	  section.data(9).logicalSrcIdx = 36;
	  section.data(9).dtTransOffset = 8;
	
	  ;% kmoqdzazlbs.orrtyae4cj
	  section.data(10).logicalSrcIdx = 37;
	  section.data(10).dtTransOffset = 9;
	
	  ;% kmoqdzazlbs.mlvjnryb2f
	  section.data(11).logicalSrcIdx = 38;
	  section.data(11).dtTransOffset = 10;
	
	  ;% kmoqdzazlbs.gyhved5o0g
	  section.data(12).logicalSrcIdx = 39;
	  section.data(12).dtTransOffset = 11;
	
	  ;% kmoqdzazlbs.pthrmzewo5
	  section.data(13).logicalSrcIdx = 40;
	  section.data(13).dtTransOffset = 12;
	
	  ;% kmoqdzazlbs.pb2kg5dbwj
	  section.data(14).logicalSrcIdx = 41;
	  section.data(14).dtTransOffset = 13;
	
	  ;% kmoqdzazlbs.eekfpd55za
	  section.data(15).logicalSrcIdx = 42;
	  section.data(15).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.o3brjlgfg1.ayt0qd5doj
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.o3brjlgfg1.efqrlmyyoi
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.nbm22evv0g.ayt0qd5doj
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.nbm22evv0g.efqrlmyyoi
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.ebil10nhgi.ayt0qd5doj
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.ebil10nhgi.efqrlmyyoi
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.imtastcd1c.ayt0qd5doj
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.imtastcd1c.efqrlmyyoi
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.mal2e4bwfg.ayt0qd5doj
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.mal2e4bwfg.efqrlmyyoi
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.fsgkfn1wuo.ayt0qd5doj
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.fsgkfn1wuo.efqrlmyyoi
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.judnob4hwn.ayt0qd5doj
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.judnob4hwn.efqrlmyyoi
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.nq4cmgm03a.ayt0qd5doj
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.nq4cmgm03a.efqrlmyyoi
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.ix1ebopk11.ayt0qd5doj
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.ix1ebopk11.efqrlmyyoi
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.op2jvp5kgr.ayt0qd5doj
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.op2jvp5kgr.efqrlmyyoi
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.kfxzmrhmet.ayt0qd5doj
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.kfxzmrhmet.efqrlmyyoi
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.eh2gxhlfvx.ayt0qd5doj
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.eh2gxhlfvx.efqrlmyyoi
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.m5s5btvqpr.ayt0qd5doj
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.m5s5btvqpr.efqrlmyyoi
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.b5yns515f3.ayt0qd5doj
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.b5yns515f3.efqrlmyyoi
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.bw3qikpzl52.ayt0qd5doj
	  section.data(1).logicalSrcIdx = 71;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.bw3qikpzl52.efqrlmyyoi
	  section.data(1).logicalSrcIdx = 72;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(34) = section;
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


  targMap.checksum0 = 1410388422;
  targMap.checksum1 = 2680890422;
  targMap.checksum2 = 425240738;
  targMap.checksum3 = 1883790720;

