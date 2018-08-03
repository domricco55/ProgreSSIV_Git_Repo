  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 4;
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
    ;% Auto data (lpyvnxj1h0)
    ;%
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% lpyvnxj1h0.SpeedController_I
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% lpyvnxj1h0.SpeedController_P
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% lpyvnxj1h0.FixPtBitwiseOperator1_BitMask
	  section.data(1).logicalSrcIdx = 2;
	  section.data(1).dtTransOffset = 0;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_psltjvv4ax
	  section.data(2).logicalSrcIdx = 3;
	  section.data(2).dtTransOffset = 1;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_ncfxm2jagp
	  section.data(3).logicalSrcIdx = 4;
	  section.data(3).dtTransOffset = 2;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_pv02zjt0gc
	  section.data(4).logicalSrcIdx = 5;
	  section.data(4).dtTransOffset = 3;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_kifbw1j4su
	  section.data(5).logicalSrcIdx = 6;
	  section.data(5).dtTransOffset = 4;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_b2teu3fanr
	  section.data(6).logicalSrcIdx = 7;
	  section.data(6).dtTransOffset = 5;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_lwwugdgd4i
	  section.data(7).logicalSrcIdx = 8;
	  section.data(7).dtTransOffset = 6;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_dzmkvs5xk1
	  section.data(8).logicalSrcIdx = 9;
	  section.data(8).dtTransOffset = 7;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_jvzpos55kn
	  section.data(9).logicalSrcIdx = 10;
	  section.data(9).dtTransOffset = 8;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_bhnevrebin
	  section.data(10).logicalSrcIdx = 11;
	  section.data(10).dtTransOffset = 9;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_ihzvxioflp
	  section.data(11).logicalSrcIdx = 12;
	  section.data(11).dtTransOffset = 10;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_cm33fo1ymv
	  section.data(12).logicalSrcIdx = 13;
	  section.data(12).dtTransOffset = 11;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_nhxlwfddca
	  section.data(13).logicalSrcIdx = 14;
	  section.data(13).dtTransOffset = 12;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_gx4fcf0wux
	  section.data(14).logicalSrcIdx = 15;
	  section.data(14).dtTransOffset = 13;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_h4ulqzgyji
	  section.data(15).logicalSrcIdx = 16;
	  section.data(15).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 34;
      section.data(34)  = dumData; %prealloc
      
	  ;% lpyvnxj1h0.Compensatesfordirectionofspinwa
	  section.data(1).logicalSrcIdx = 17;
	  section.data(1).dtTransOffset = 0;
	
	  ;% lpyvnxj1h0.Compensatesfordirect_jvqcwcozr3
	  section.data(2).logicalSrcIdx = 18;
	  section.data(2).dtTransOffset = 1;
	
	  ;% lpyvnxj1h0.RPMtoms_Gain
	  section.data(3).logicalSrcIdx = 19;
	  section.data(3).dtTransOffset = 2;
	
	  ;% lpyvnxj1h0.ConstantSteeringOffsetFromRadio
	  section.data(4).logicalSrcIdx = 20;
	  section.data(4).dtTransOffset = 3;
	
	  ;% lpyvnxj1h0.bitsmNm_Gain
	  section.data(5).logicalSrcIdx = 21;
	  section.data(5).dtTransOffset = 4;
	
	  ;% lpyvnxj1h0.DesiredVelocityms_Time
	  section.data(6).logicalSrcIdx = 22;
	  section.data(6).dtTransOffset = 5;
	
	  ;% lpyvnxj1h0.DesiredVelocityms_Y0
	  section.data(7).logicalSrcIdx = 23;
	  section.data(7).dtTransOffset = 6;
	
	  ;% lpyvnxj1h0.DesiredVelocityms_YFinal
	  section.data(8).logicalSrcIdx = 24;
	  section.data(8).dtTransOffset = 7;
	
	  ;% lpyvnxj1h0.Integrator_IC
	  section.data(9).logicalSrcIdx = 25;
	  section.data(9).dtTransOffset = 8;
	
	  ;% lpyvnxj1h0.Saturation_UpperSat
	  section.data(10).logicalSrcIdx = 26;
	  section.data(10).dtTransOffset = 9;
	
	  ;% lpyvnxj1h0.Saturation_LowerSat
	  section.data(11).logicalSrcIdx = 27;
	  section.data(11).dtTransOffset = 10;
	
	  ;% lpyvnxj1h0.ConstantThrottleOffsetFromRadio
	  section.data(12).logicalSrcIdx = 28;
	  section.data(12).dtTransOffset = 11;
	
	  ;% lpyvnxj1h0.DeadSwitchValue_Value
	  section.data(13).logicalSrcIdx = 29;
	  section.data(13).dtTransOffset = 12;
	
	  ;% lpyvnxj1h0._Value
	  section.data(14).logicalSrcIdx = 30;
	  section.data(14).dtTransOffset = 13;
	
	  ;% lpyvnxj1h0.DeadSwitch_Threshold
	  section.data(15).logicalSrcIdx = 31;
	  section.data(15).dtTransOffset = 14;
	
	  ;% lpyvnxj1h0.bitsmNm_Gain_n31nuftucu
	  section.data(16).logicalSrcIdx = 32;
	  section.data(16).dtTransOffset = 15;
	
	  ;% lpyvnxj1h0.bitsmNm_Gain_iz44z4guht
	  section.data(17).logicalSrcIdx = 33;
	  section.data(17).dtTransOffset = 16;
	
	  ;% lpyvnxj1h0.bitsmNm_Gain_jjrfnm553k
	  section.data(18).logicalSrcIdx = 34;
	  section.data(18).dtTransOffset = 17;
	
	  ;% lpyvnxj1h0.bitsmNm_Gain_ljowsi2cmm
	  section.data(19).logicalSrcIdx = 35;
	  section.data(19).dtTransOffset = 18;
	
	  ;% lpyvnxj1h0.AccelerationInttoDoubleScaleFac
	  section.data(20).logicalSrcIdx = 36;
	  section.data(20).dtTransOffset = 19;
	
	  ;% lpyvnxj1h0.GyroscopeInttoDoubleScaleFactor
	  section.data(21).logicalSrcIdx = 37;
	  section.data(21).dtTransOffset = 20;
	
	  ;% lpyvnxj1h0.AccelerationInttoDou_nsgzzd3dys
	  section.data(22).logicalSrcIdx = 38;
	  section.data(22).dtTransOffset = 21;
	
	  ;% lpyvnxj1h0.GyroscopeInttoDouble_leu0lmtkw5
	  section.data(23).logicalSrcIdx = 39;
	  section.data(23).dtTransOffset = 22;
	
	  ;% lpyvnxj1h0.AccelerationInttoDou_n25pvjipoq
	  section.data(24).logicalSrcIdx = 40;
	  section.data(24).dtTransOffset = 23;
	
	  ;% lpyvnxj1h0.GyroscopeInttoDouble_fnfguslit0
	  section.data(25).logicalSrcIdx = 41;
	  section.data(25).dtTransOffset = 24;
	
	  ;% lpyvnxj1h0.EulerInttoDoubleScaleFactor_Gai
	  section.data(26).logicalSrcIdx = 42;
	  section.data(26).dtTransOffset = 25;
	
	  ;% lpyvnxj1h0.EulerInttoDoubleScal_iiz5hgtpf2
	  section.data(27).logicalSrcIdx = 43;
	  section.data(27).dtTransOffset = 26;
	
	  ;% lpyvnxj1h0.EulerInttoDoubleScal_g31zf1epte
	  section.data(28).logicalSrcIdx = 44;
	  section.data(28).dtTransOffset = 27;
	
	  ;% lpyvnxj1h0.Constant1_Value
	  section.data(29).logicalSrcIdx = 45;
	  section.data(29).dtTransOffset = 28;
	
	  ;% lpyvnxj1h0.Constant_Value
	  section.data(30).logicalSrcIdx = 46;
	  section.data(30).dtTransOffset = 29;
	
	  ;% lpyvnxj1h0.Constant2_Value
	  section.data(31).logicalSrcIdx = 47;
	  section.data(31).dtTransOffset = 30;
	
	  ;% lpyvnxj1h0.Constant4_Value
	  section.data(32).logicalSrcIdx = 48;
	  section.data(32).dtTransOffset = 31;
	
	  ;% lpyvnxj1h0.Constant3_Value
	  section.data(33).logicalSrcIdx = 49;
	  section.data(33).dtTransOffset = 32;
	
	  ;% lpyvnxj1h0.Constant5_Value
	  section.data(34).logicalSrcIdx = 50;
	  section.data(34).dtTransOffset = 33;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 68;
      section.data(68)  = dumData; %prealloc
      
	  ;% lpyvnxj1h0.velocity_FRAddressNumber_Value
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
	  ;% lpyvnxj1h0.uint8_t1_Value
	  section.data(2).logicalSrcIdx = 52;
	  section.data(2).dtTransOffset = 1;
	
	  ;% lpyvnxj1h0.uint8_t2_Value
	  section.data(3).logicalSrcIdx = 53;
	  section.data(3).dtTransOffset = 2;
	
	  ;% lpyvnxj1h0.uint8_t3_Value
	  section.data(4).logicalSrcIdx = 54;
	  section.data(4).dtTransOffset = 3;
	
	  ;% lpyvnxj1h0.velocity_FLAddressNumber_Value
	  section.data(5).logicalSrcIdx = 55;
	  section.data(5).dtTransOffset = 4;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_fbwzrt0xsu
	  section.data(6).logicalSrcIdx = 56;
	  section.data(6).dtTransOffset = 5;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_nlddlhtmy4
	  section.data(7).logicalSrcIdx = 57;
	  section.data(7).dtTransOffset = 6;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_p5kni5nbh4
	  section.data(8).logicalSrcIdx = 58;
	  section.data(8).dtTransOffset = 7;
	
	  ;% lpyvnxj1h0.velocity_RRAddressNumber_Value
	  section.data(9).logicalSrcIdx = 59;
	  section.data(9).dtTransOffset = 8;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_iswfbqmgg0
	  section.data(10).logicalSrcIdx = 60;
	  section.data(10).dtTransOffset = 9;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_og3vod555z
	  section.data(11).logicalSrcIdx = 61;
	  section.data(11).dtTransOffset = 10;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_o4pefzbbdu
	  section.data(12).logicalSrcIdx = 62;
	  section.data(12).dtTransOffset = 11;
	
	  ;% lpyvnxj1h0.velocity_RLAddressNumber_Value
	  section.data(13).logicalSrcIdx = 63;
	  section.data(13).dtTransOffset = 12;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_cvek4esgvd
	  section.data(14).logicalSrcIdx = 64;
	  section.data(14).dtTransOffset = 13;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_lseyezibvx
	  section.data(15).logicalSrcIdx = 65;
	  section.data(15).dtTransOffset = 14;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_o1yzfl3g0m
	  section.data(16).logicalSrcIdx = 66;
	  section.data(16).dtTransOffset = 15;
	
	  ;% lpyvnxj1h0.euler_headingAddressNumber_Valu
	  section.data(17).logicalSrcIdx = 67;
	  section.data(17).dtTransOffset = 16;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_lkntw2gjcg
	  section.data(18).logicalSrcIdx = 68;
	  section.data(18).dtTransOffset = 17;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_mgwg4dupzs
	  section.data(19).logicalSrcIdx = 69;
	  section.data(19).dtTransOffset = 18;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_fw55euegux
	  section.data(20).logicalSrcIdx = 70;
	  section.data(20).dtTransOffset = 19;
	
	  ;% lpyvnxj1h0.euler_rollAddressNumber_Value
	  section.data(21).logicalSrcIdx = 71;
	  section.data(21).dtTransOffset = 20;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_pdh1mmrkaf
	  section.data(22).logicalSrcIdx = 72;
	  section.data(22).dtTransOffset = 21;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_bjkzcm1v50
	  section.data(23).logicalSrcIdx = 73;
	  section.data(23).dtTransOffset = 22;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_bzki1yseu2
	  section.data(24).logicalSrcIdx = 74;
	  section.data(24).dtTransOffset = 23;
	
	  ;% lpyvnxj1h0.euler_pitchAddressNumber_Value
	  section.data(25).logicalSrcIdx = 75;
	  section.data(25).dtTransOffset = 24;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_nh5qfyju0z
	  section.data(26).logicalSrcIdx = 76;
	  section.data(26).dtTransOffset = 25;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_g33fsjovlh
	  section.data(27).logicalSrcIdx = 77;
	  section.data(27).dtTransOffset = 26;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_fcyoyjujtb
	  section.data(28).logicalSrcIdx = 78;
	  section.data(28).dtTransOffset = 27;
	
	  ;% lpyvnxj1h0.gyr_xAddressNumber_Value
	  section.data(29).logicalSrcIdx = 79;
	  section.data(29).dtTransOffset = 28;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_j2wfmnih52
	  section.data(30).logicalSrcIdx = 80;
	  section.data(30).dtTransOffset = 29;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_l24qi4amhg
	  section.data(31).logicalSrcIdx = 81;
	  section.data(31).dtTransOffset = 30;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_abjhsc0f24
	  section.data(32).logicalSrcIdx = 82;
	  section.data(32).dtTransOffset = 31;
	
	  ;% lpyvnxj1h0.acc_xAddressNumber_Value
	  section.data(33).logicalSrcIdx = 83;
	  section.data(33).dtTransOffset = 32;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_d1nmexi4u4
	  section.data(34).logicalSrcIdx = 84;
	  section.data(34).dtTransOffset = 33;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_a4kbzdzszs
	  section.data(35).logicalSrcIdx = 85;
	  section.data(35).dtTransOffset = 34;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_crbst3qg0d
	  section.data(36).logicalSrcIdx = 86;
	  section.data(36).dtTransOffset = 35;
	
	  ;% lpyvnxj1h0.gyr_yAddressNumber_Value
	  section.data(37).logicalSrcIdx = 87;
	  section.data(37).dtTransOffset = 36;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_hhpzgdklhj
	  section.data(38).logicalSrcIdx = 88;
	  section.data(38).dtTransOffset = 37;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_kfo5pj123x
	  section.data(39).logicalSrcIdx = 89;
	  section.data(39).dtTransOffset = 38;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_llnlocx0jp
	  section.data(40).logicalSrcIdx = 90;
	  section.data(40).dtTransOffset = 39;
	
	  ;% lpyvnxj1h0.acc_yAddressNumber_Value
	  section.data(41).logicalSrcIdx = 91;
	  section.data(41).dtTransOffset = 40;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_k55hriosiw
	  section.data(42).logicalSrcIdx = 92;
	  section.data(42).dtTransOffset = 41;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_ewsrijoi1y
	  section.data(43).logicalSrcIdx = 93;
	  section.data(43).dtTransOffset = 42;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_csq2nflakv
	  section.data(44).logicalSrcIdx = 94;
	  section.data(44).dtTransOffset = 43;
	
	  ;% lpyvnxj1h0.gyr_zAddressNumber_Value
	  section.data(45).logicalSrcIdx = 95;
	  section.data(45).dtTransOffset = 44;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_iarfsgp4wp
	  section.data(46).logicalSrcIdx = 96;
	  section.data(46).dtTransOffset = 45;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_h25nsb42dk
	  section.data(47).logicalSrcIdx = 97;
	  section.data(47).dtTransOffset = 46;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_irei2yyusa
	  section.data(48).logicalSrcIdx = 98;
	  section.data(48).dtTransOffset = 47;
	
	  ;% lpyvnxj1h0.acc_zAddressNumber_Value
	  section.data(49).logicalSrcIdx = 99;
	  section.data(49).dtTransOffset = 48;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_escjrdlkcn
	  section.data(50).logicalSrcIdx = 100;
	  section.data(50).dtTransOffset = 49;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_ohr50x5o4g
	  section.data(51).logicalSrcIdx = 101;
	  section.data(51).dtTransOffset = 50;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_g5ikrmq33j
	  section.data(52).logicalSrcIdx = 102;
	  section.data(52).dtTransOffset = 51;
	
	  ;% lpyvnxj1h0.radio_throttleAddressNumber_Val
	  section.data(53).logicalSrcIdx = 103;
	  section.data(53).dtTransOffset = 52;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_blcwsn3mod
	  section.data(54).logicalSrcIdx = 104;
	  section.data(54).dtTransOffset = 53;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_feo10nb4xc
	  section.data(55).logicalSrcIdx = 105;
	  section.data(55).dtTransOffset = 54;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_p3y25qn4th
	  section.data(56).logicalSrcIdx = 106;
	  section.data(56).dtTransOffset = 55;
	
	  ;% lpyvnxj1h0.radio_steeringAddressNumber_Val
	  section.data(57).logicalSrcIdx = 107;
	  section.data(57).dtTransOffset = 56;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_mwwrewolew
	  section.data(58).logicalSrcIdx = 108;
	  section.data(58).dtTransOffset = 57;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_plp2fa3e20
	  section.data(59).logicalSrcIdx = 109;
	  section.data(59).dtTransOffset = 58;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_feq0mqtkvh
	  section.data(60).logicalSrcIdx = 110;
	  section.data(60).dtTransOffset = 59;
	
	  ;% lpyvnxj1h0.DeadSwitch_Value
	  section.data(61).logicalSrcIdx = 111;
	  section.data(61).dtTransOffset = 60;
	
	  ;% lpyvnxj1h0.TakeData_Value
	  section.data(62).logicalSrcIdx = 112;
	  section.data(62).dtTransOffset = 61;
	
	  ;% lpyvnxj1h0.ServoandRadioOn_Value
	  section.data(63).logicalSrcIdx = 113;
	  section.data(63).dtTransOffset = 62;
	
	  ;% lpyvnxj1h0.MotorControllersOn_Value
	  section.data(64).logicalSrcIdx = 114;
	  section.data(64).dtTransOffset = 63;
	
	  ;% lpyvnxj1h0.IMUReset_Value
	  section.data(65).logicalSrcIdx = 115;
	  section.data(65).dtTransOffset = 64;
	
	  ;% lpyvnxj1h0.PrinttheregistermapontheTeensy_
	  section.data(66).logicalSrcIdx = 116;
	  section.data(66).dtTransOffset = 65;
	
	  ;% lpyvnxj1h0.PrinttheimudataontheTeensy_Valu
	  section.data(67).logicalSrcIdx = 117;
	  section.data(67).dtTransOffset = 66;
	
	  ;% lpyvnxj1h0.Printtheradiotranceiverdataonth
	  section.data(68).logicalSrcIdx = 118;
	  section.data(68).dtTransOffset = 67;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
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
    ;% Auto data (ngwkuxrl30h)
    ;%
      section.nData     = 25;
      section.data(25)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.goicmyl1b2
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ngwkuxrl30h.aurkuh54cu
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ngwkuxrl30h.ocmqfypqv1
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% ngwkuxrl30h.gmzmqyembu
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% ngwkuxrl30h.pp5difj1ae
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% ngwkuxrl30h.gg4ejhjbyt
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% ngwkuxrl30h.nf3pttmeh0
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% ngwkuxrl30h.o44uqodtll
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% ngwkuxrl30h.n4k0hxwf5l
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% ngwkuxrl30h.i4n44eh5n1
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% ngwkuxrl30h.j532g4ur2g
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 13;
	
	  ;% ngwkuxrl30h.avq0vo1ltj
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 14;
	
	  ;% ngwkuxrl30h.aekojq4djl
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 15;
	
	  ;% ngwkuxrl30h.otfirjhqhp
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 16;
	
	  ;% ngwkuxrl30h.hogkymthgv
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 17;
	
	  ;% ngwkuxrl30h.brslgvoazc
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 18;
	
	  ;% ngwkuxrl30h.hp50qmle4i
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 19;
	
	  ;% ngwkuxrl30h.pnhcr0iazy
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 20;
	
	  ;% ngwkuxrl30h.dq1ktk43wx
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 21;
	
	  ;% ngwkuxrl30h.fzgu01utxu
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 22;
	
	  ;% ngwkuxrl30h.hlbe5rh0cv
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 23;
	
	  ;% ngwkuxrl30h.k5c2zqyceq
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 24;
	
	  ;% ngwkuxrl30h.fia5rxhr3l
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 25;
	
	  ;% ngwkuxrl30h.aiadjttii0
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 26;
	
	  ;% ngwkuxrl30h.f2vkc5n0n2
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 27;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.hmbqn33kqw
	  section.data(1).logicalSrcIdx = 25;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ngwkuxrl30h.dygekuq1ll
	  section.data(2).logicalSrcIdx = 26;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ngwkuxrl30h.n4o1gr0x35
	  section.data(3).logicalSrcIdx = 27;
	  section.data(3).dtTransOffset = 2;
	
	  ;% ngwkuxrl30h.mwib43op1y
	  section.data(4).logicalSrcIdx = 28;
	  section.data(4).dtTransOffset = 3;
	
	  ;% ngwkuxrl30h.pjxcr14fkm
	  section.data(5).logicalSrcIdx = 29;
	  section.data(5).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 9;
      section.data(9)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.ekzdpyqdge
	  section.data(1).logicalSrcIdx = 30;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ngwkuxrl30h.muq5zmbn3r
	  section.data(2).logicalSrcIdx = 31;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ngwkuxrl30h.pwebukhun0
	  section.data(3).logicalSrcIdx = 32;
	  section.data(3).dtTransOffset = 2;
	
	  ;% ngwkuxrl30h.ir10twv5tb
	  section.data(4).logicalSrcIdx = 33;
	  section.data(4).dtTransOffset = 3;
	
	  ;% ngwkuxrl30h.pnpudeaf4t
	  section.data(5).logicalSrcIdx = 34;
	  section.data(5).dtTransOffset = 4;
	
	  ;% ngwkuxrl30h.bvbhxpbrth
	  section.data(6).logicalSrcIdx = 35;
	  section.data(6).dtTransOffset = 5;
	
	  ;% ngwkuxrl30h.ml5lnjsl1s
	  section.data(7).logicalSrcIdx = 36;
	  section.data(7).dtTransOffset = 6;
	
	  ;% ngwkuxrl30h.cjy2ntjat0
	  section.data(8).logicalSrcIdx = 37;
	  section.data(8).dtTransOffset = 7;
	
	  ;% ngwkuxrl30h.cuc3vlyflu
	  section.data(9).logicalSrcIdx = 38;
	  section.data(9).dtTransOffset = 8;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.igzxso45vj.peekzayaza
	  section.data(1).logicalSrcIdx = 39;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.m4g15z44rg.peekzayaza
	  section.data(1).logicalSrcIdx = 40;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.jl31gk0dp0.peekzayaza
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.blhmqzejza.peekzayaza
	  section.data(1).logicalSrcIdx = 42;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.hduf11nqm5.ca0vhailpa
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.eojam00dlx.lwegmsa4zp
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.b0ijxufkkr.ca0vhailpa
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.neiyt2bqud.lwegmsa4zp
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.bxw45fu3fk.ca0vhailpa
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.dlplqysdxo.lwegmsa4zp
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.oimhny2hoz.ca0vhailpa
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.bguuk1u1pv.lwegmsa4zp
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.edcnapftbow.ca0vhailpa
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.ejlnqjcfsiy.lwegmsa4zp
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.gizd4idou5.peekzayaza
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.frtamjx4ve.peekzayaza
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.f3zdpfpl3u.peekzayaza
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.cm1e4dikvc.peekzayaza
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.ehvsyetglw.peekzayaza
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.jittrgdbfq.peekzayaza
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.mfdug0vezs.peekzayaza
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.f3ttkpb3q5.peekzayaza
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.pliq0ckivk.peekzayaza
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.axt0phmdkj.peekzayaza
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.nu4fyjdnsdd.peekzayaza
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.dvpqmjqb1n.axphthfcvr
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.jtyclzua3t.axphthfcvr
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.baivdu1wt0.axphthfcvr
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.hlybsl2cgn.axphthfcvr
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.jnpdmcahon.axphthfcvr
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.fum3atfoqu.axphthfcvr
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(34) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.e5v5bx013w.axphthfcvr
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(35) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.psfrn3qsk0.axphthfcvr
	  section.data(1).logicalSrcIdx = 71;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(36) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.fxsfzp40io.axphthfcvr
	  section.data(1).logicalSrcIdx = 72;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(37) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.fzjme0r5v4.axphthfcvr
	  section.data(1).logicalSrcIdx = 73;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(38) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.bqtw5k3h1l.axphthfcvr
	  section.data(1).logicalSrcIdx = 74;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(39) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.epdw1uru12.axphthfcvr
	  section.data(1).logicalSrcIdx = 75;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(40) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.c4szrdzfjz.axphthfcvr
	  section.data(1).logicalSrcIdx = 76;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(41) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.k54btlvaqy.axphthfcvr
	  section.data(1).logicalSrcIdx = 77;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(42) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.dqhh5t5yq5z.axphthfcvr
	  section.data(1).logicalSrcIdx = 78;
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
    ;% Auto data (cg3ibeewf53)
    ;%
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.nnfizqiv0l
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% cg3ibeewf53.kfxzkjvpsk
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% cg3ibeewf53.ltxrui4g3i
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% cg3ibeewf53.ebyonliuwf
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% cg3ibeewf53.bnpmfqmomz
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% cg3ibeewf53.c0vsjscsqh
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% cg3ibeewf53.azi1wcpfid
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% cg3ibeewf53.oqgboxs2pp
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% cg3ibeewf53.dsknplatsh
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% cg3ibeewf53.fqkx4ayo2q
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% cg3ibeewf53.b2jykk5ji0
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% cg3ibeewf53.kzztpyxhfm
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% cg3ibeewf53.bmdyk3hp5p
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 16;
      section.data(16)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.ntxq3scv05.LoggedData
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
	  ;% cg3ibeewf53.aojoykzsdi.LoggedData
	  section.data(2).logicalSrcIdx = 14;
	  section.data(2).dtTransOffset = 1;
	
	  ;% cg3ibeewf53.l2mcblmxhu.LoggedData
	  section.data(3).logicalSrcIdx = 15;
	  section.data(3).dtTransOffset = 2;
	
	  ;% cg3ibeewf53.nnjq5qwmqi.LoggedData
	  section.data(4).logicalSrcIdx = 16;
	  section.data(4).dtTransOffset = 3;
	
	  ;% cg3ibeewf53.kdfb5pdgzn.LoggedData
	  section.data(5).logicalSrcIdx = 17;
	  section.data(5).dtTransOffset = 4;
	
	  ;% cg3ibeewf53.oe3ubbhoy2.LoggedData
	  section.data(6).logicalSrcIdx = 18;
	  section.data(6).dtTransOffset = 5;
	
	  ;% cg3ibeewf53.h2lwvxpcqj.LoggedData
	  section.data(7).logicalSrcIdx = 19;
	  section.data(7).dtTransOffset = 7;
	
	  ;% cg3ibeewf53.njvlimmeyn.LoggedData
	  section.data(8).logicalSrcIdx = 20;
	  section.data(8).dtTransOffset = 8;
	
	  ;% cg3ibeewf53.kmqgabetn4.LoggedData
	  section.data(9).logicalSrcIdx = 21;
	  section.data(9).dtTransOffset = 10;
	
	  ;% cg3ibeewf53.nyqh5dphei.LoggedData
	  section.data(10).logicalSrcIdx = 22;
	  section.data(10).dtTransOffset = 12;
	
	  ;% cg3ibeewf53.cg3rkvyeni.LoggedData
	  section.data(11).logicalSrcIdx = 23;
	  section.data(11).dtTransOffset = 14;
	
	  ;% cg3ibeewf53.h2dsgwkndy.LoggedData
	  section.data(12).logicalSrcIdx = 24;
	  section.data(12).dtTransOffset = 16;
	
	  ;% cg3ibeewf53.iolqh5umvb.LoggedData
	  section.data(13).logicalSrcIdx = 25;
	  section.data(13).dtTransOffset = 20;
	
	  ;% cg3ibeewf53.beeu1et30m.LoggedData
	  section.data(14).logicalSrcIdx = 26;
	  section.data(14).dtTransOffset = 23;
	
	  ;% cg3ibeewf53.jgsdqb1s4w.LoggedData
	  section.data(15).logicalSrcIdx = 27;
	  section.data(15).dtTransOffset = 24;
	
	  ;% cg3ibeewf53.h2qpnaxgfz.LoggedData
	  section.data(16).logicalSrcIdx = 28;
	  section.data(16).dtTransOffset = 25;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.mwubnqbpre
	  section.data(1).logicalSrcIdx = 29;
	  section.data(1).dtTransOffset = 0;
	
	  ;% cg3ibeewf53.ef0g4a1zza
	  section.data(2).logicalSrcIdx = 30;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.ktk41lwjeb
	  section.data(1).logicalSrcIdx = 31;
	  section.data(1).dtTransOffset = 0;
	
	  ;% cg3ibeewf53.oan42s30ka
	  section.data(2).logicalSrcIdx = 32;
	  section.data(2).dtTransOffset = 1;
	
	  ;% cg3ibeewf53.d5fycav3jh
	  section.data(3).logicalSrcIdx = 33;
	  section.data(3).dtTransOffset = 2;
	
	  ;% cg3ibeewf53.d3qal1dlso
	  section.data(4).logicalSrcIdx = 34;
	  section.data(4).dtTransOffset = 3;
	
	  ;% cg3ibeewf53.ml3zhyhxpj
	  section.data(5).logicalSrcIdx = 35;
	  section.data(5).dtTransOffset = 4;
	
	  ;% cg3ibeewf53.mic2ccttzi
	  section.data(6).logicalSrcIdx = 36;
	  section.data(6).dtTransOffset = 5;
	
	  ;% cg3ibeewf53.fnm5jw4ury
	  section.data(7).logicalSrcIdx = 37;
	  section.data(7).dtTransOffset = 6;
	
	  ;% cg3ibeewf53.b5kkbdqz3o
	  section.data(8).logicalSrcIdx = 38;
	  section.data(8).dtTransOffset = 7;
	
	  ;% cg3ibeewf53.amz1ygk2qo
	  section.data(9).logicalSrcIdx = 39;
	  section.data(9).dtTransOffset = 8;
	
	  ;% cg3ibeewf53.nuy0cnjia2
	  section.data(10).logicalSrcIdx = 40;
	  section.data(10).dtTransOffset = 9;
	
	  ;% cg3ibeewf53.bjzr3wi4k2
	  section.data(11).logicalSrcIdx = 41;
	  section.data(11).dtTransOffset = 10;
	
	  ;% cg3ibeewf53.lq2xk5n2gd
	  section.data(12).logicalSrcIdx = 42;
	  section.data(12).dtTransOffset = 11;
	
	  ;% cg3ibeewf53.amy52haimr
	  section.data(13).logicalSrcIdx = 43;
	  section.data(13).dtTransOffset = 12;
	
	  ;% cg3ibeewf53.hyt40luu1m
	  section.data(14).logicalSrcIdx = 44;
	  section.data(14).dtTransOffset = 13;
	
	  ;% cg3ibeewf53.mdv01wq3vx
	  section.data(15).logicalSrcIdx = 45;
	  section.data(15).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.dvpqmjqb1n.lta3n0n5b4
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.dvpqmjqb1n.hzhllxmofq
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.jtyclzua3t.lta3n0n5b4
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.jtyclzua3t.hzhllxmofq
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.baivdu1wt0.lta3n0n5b4
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.baivdu1wt0.hzhllxmofq
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.hlybsl2cgn.lta3n0n5b4
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.hlybsl2cgn.hzhllxmofq
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.jnpdmcahon.lta3n0n5b4
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.jnpdmcahon.hzhllxmofq
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.fum3atfoqu.lta3n0n5b4
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.fum3atfoqu.hzhllxmofq
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.e5v5bx013w.lta3n0n5b4
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.e5v5bx013w.hzhllxmofq
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.psfrn3qsk0.lta3n0n5b4
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.psfrn3qsk0.hzhllxmofq
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.fxsfzp40io.lta3n0n5b4
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.fxsfzp40io.hzhllxmofq
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.fzjme0r5v4.lta3n0n5b4
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.fzjme0r5v4.hzhllxmofq
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.bqtw5k3h1l.lta3n0n5b4
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.bqtw5k3h1l.hzhllxmofq
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.epdw1uru12.lta3n0n5b4
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.epdw1uru12.hzhllxmofq
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.c4szrdzfjz.lta3n0n5b4
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.c4szrdzfjz.hzhllxmofq
	  section.data(1).logicalSrcIdx = 71;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.k54btlvaqy.lta3n0n5b4
	  section.data(1).logicalSrcIdx = 72;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.k54btlvaqy.hzhllxmofq
	  section.data(1).logicalSrcIdx = 73;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.dqhh5t5yq5z.lta3n0n5b4
	  section.data(1).logicalSrcIdx = 74;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.dqhh5t5yq5z.hzhllxmofq
	  section.data(1).logicalSrcIdx = 75;
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


  targMap.checksum0 = 264987653;
  targMap.checksum1 = 1530834613;
  targMap.checksum2 = 1362620218;
  targMap.checksum3 = 310297753;

