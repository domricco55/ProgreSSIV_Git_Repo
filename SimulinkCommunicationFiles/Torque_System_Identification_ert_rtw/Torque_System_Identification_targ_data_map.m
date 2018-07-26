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
    ;% Auto data (hfsubh0wqd)
    ;%
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% hfsubh0wqd.FixPtBitwiseOperator1_BitMask
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% hfsubh0wqd.FixPtBitwiseOperator_b2teu3fanr
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% hfsubh0wqd.FixPtBitwiseOperator_lwwugdgd4i
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% hfsubh0wqd.FixPtBitwiseOperator_dzmkvs5xk1
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% hfsubh0wqd.FixPtBitwiseOperator_jvzpos55kn
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% hfsubh0wqd.FixPtBitwiseOperator_bhnevrebin
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% hfsubh0wqd.FixPtBitwiseOperator_ihzvxioflp
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% hfsubh0wqd.FixPtBitwiseOperator_cm33fo1ymv
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% hfsubh0wqd.FixPtBitwiseOperator_nhxlwfddca
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% hfsubh0wqd.FixPtBitwiseOperator_gx4fcf0wux
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% hfsubh0wqd.FixPtBitwiseOperator_h4ulqzgyji
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% hfsubh0wqd.FixPtBitwiseOperator_ncfxm2jagp
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% hfsubh0wqd.FixPtBitwiseOperator_pv02zjt0gc
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% hfsubh0wqd.FixPtBitwiseOperator_fnveiwfrqo
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% hfsubh0wqd.FixPtBitwiseOperator_psltjvv4ax
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 39;
      section.data(39)  = dumData; %prealloc
      
	  ;% hfsubh0wqd.ConstantSteeringOffsetFromRadio
	  section.data(1).logicalSrcIdx = 15;
	  section.data(1).dtTransOffset = 0;
	
	  ;% hfsubh0wqd.bitsmNm_Gain
	  section.data(2).logicalSrcIdx = 16;
	  section.data(2).dtTransOffset = 1;
	
	  ;% hfsubh0wqd.Step1_Time
	  section.data(3).logicalSrcIdx = 17;
	  section.data(3).dtTransOffset = 2;
	
	  ;% hfsubh0wqd.Step1_Y0
	  section.data(4).logicalSrcIdx = 18;
	  section.data(4).dtTransOffset = 3;
	
	  ;% hfsubh0wqd.Step1_YFinal
	  section.data(5).logicalSrcIdx = 19;
	  section.data(5).dtTransOffset = 4;
	
	  ;% hfsubh0wqd.Step2_Time
	  section.data(6).logicalSrcIdx = 20;
	  section.data(6).dtTransOffset = 5;
	
	  ;% hfsubh0wqd.Step2_Y0
	  section.data(7).logicalSrcIdx = 21;
	  section.data(7).dtTransOffset = 6;
	
	  ;% hfsubh0wqd.Step2_YFinal
	  section.data(8).logicalSrcIdx = 22;
	  section.data(8).dtTransOffset = 7;
	
	  ;% hfsubh0wqd.Step3_Time
	  section.data(9).logicalSrcIdx = 23;
	  section.data(9).dtTransOffset = 8;
	
	  ;% hfsubh0wqd.Step3_Y0
	  section.data(10).logicalSrcIdx = 24;
	  section.data(10).dtTransOffset = 9;
	
	  ;% hfsubh0wqd.Step3_YFinal
	  section.data(11).logicalSrcIdx = 25;
	  section.data(11).dtTransOffset = 10;
	
	  ;% hfsubh0wqd.Step4_Time
	  section.data(12).logicalSrcIdx = 26;
	  section.data(12).dtTransOffset = 11;
	
	  ;% hfsubh0wqd.Step4_Y0
	  section.data(13).logicalSrcIdx = 27;
	  section.data(13).dtTransOffset = 12;
	
	  ;% hfsubh0wqd.Step4_YFinal
	  section.data(14).logicalSrcIdx = 28;
	  section.data(14).dtTransOffset = 13;
	
	  ;% hfsubh0wqd.ConstantThrottleOffsetFromRadio
	  section.data(15).logicalSrcIdx = 29;
	  section.data(15).dtTransOffset = 14;
	
	  ;% hfsubh0wqd.DeadSwitchValue_Value
	  section.data(16).logicalSrcIdx = 30;
	  section.data(16).dtTransOffset = 15;
	
	  ;% hfsubh0wqd._Value
	  section.data(17).logicalSrcIdx = 31;
	  section.data(17).dtTransOffset = 16;
	
	  ;% hfsubh0wqd.DeadSwitch_Threshold
	  section.data(18).logicalSrcIdx = 32;
	  section.data(18).dtTransOffset = 17;
	
	  ;% hfsubh0wqd.bitsmNm_Gain_n31nuftucu
	  section.data(19).logicalSrcIdx = 33;
	  section.data(19).dtTransOffset = 18;
	
	  ;% hfsubh0wqd.bitsmNm_Gain_iz44z4guht
	  section.data(20).logicalSrcIdx = 34;
	  section.data(20).dtTransOffset = 19;
	
	  ;% hfsubh0wqd.bitsmNm_Gain_jjrfnm553k
	  section.data(21).logicalSrcIdx = 35;
	  section.data(21).dtTransOffset = 20;
	
	  ;% hfsubh0wqd.bitsmNm_Gain_ljowsi2cmm
	  section.data(22).logicalSrcIdx = 36;
	  section.data(22).dtTransOffset = 21;
	
	  ;% hfsubh0wqd.Compensatesfordirectionofspinwa
	  section.data(23).logicalSrcIdx = 37;
	  section.data(23).dtTransOffset = 22;
	
	  ;% hfsubh0wqd.Compensatesfordirect_jvqcwcozr3
	  section.data(24).logicalSrcIdx = 38;
	  section.data(24).dtTransOffset = 23;
	
	  ;% hfsubh0wqd.AccelerationInttoDoubleScaleFac
	  section.data(25).logicalSrcIdx = 39;
	  section.data(25).dtTransOffset = 24;
	
	  ;% hfsubh0wqd.GyroscopeInttoDoubleScaleFactor
	  section.data(26).logicalSrcIdx = 40;
	  section.data(26).dtTransOffset = 25;
	
	  ;% hfsubh0wqd.AccelerationInttoDou_nsgzzd3dys
	  section.data(27).logicalSrcIdx = 41;
	  section.data(27).dtTransOffset = 26;
	
	  ;% hfsubh0wqd.GyroscopeInttoDouble_leu0lmtkw5
	  section.data(28).logicalSrcIdx = 42;
	  section.data(28).dtTransOffset = 27;
	
	  ;% hfsubh0wqd.AccelerationInttoDou_n25pvjipoq
	  section.data(29).logicalSrcIdx = 43;
	  section.data(29).dtTransOffset = 28;
	
	  ;% hfsubh0wqd.GyroscopeInttoDouble_fnfguslit0
	  section.data(30).logicalSrcIdx = 44;
	  section.data(30).dtTransOffset = 29;
	
	  ;% hfsubh0wqd.EulerInttoDoubleScaleFactor_Gai
	  section.data(31).logicalSrcIdx = 45;
	  section.data(31).dtTransOffset = 30;
	
	  ;% hfsubh0wqd.EulerInttoDoubleScal_iiz5hgtpf2
	  section.data(32).logicalSrcIdx = 46;
	  section.data(32).dtTransOffset = 31;
	
	  ;% hfsubh0wqd.EulerInttoDoubleScal_g31zf1epte
	  section.data(33).logicalSrcIdx = 47;
	  section.data(33).dtTransOffset = 32;
	
	  ;% hfsubh0wqd.Constant1_Value
	  section.data(34).logicalSrcIdx = 48;
	  section.data(34).dtTransOffset = 33;
	
	  ;% hfsubh0wqd.Constant_Value
	  section.data(35).logicalSrcIdx = 49;
	  section.data(35).dtTransOffset = 34;
	
	  ;% hfsubh0wqd.Constant2_Value
	  section.data(36).logicalSrcIdx = 50;
	  section.data(36).dtTransOffset = 35;
	
	  ;% hfsubh0wqd.Constant4_Value
	  section.data(37).logicalSrcIdx = 51;
	  section.data(37).dtTransOffset = 36;
	
	  ;% hfsubh0wqd.Constant3_Value
	  section.data(38).logicalSrcIdx = 52;
	  section.data(38).dtTransOffset = 37;
	
	  ;% hfsubh0wqd.Constant5_Value
	  section.data(39).logicalSrcIdx = 53;
	  section.data(39).dtTransOffset = 38;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 68;
      section.data(68)  = dumData; %prealloc
      
	  ;% hfsubh0wqd.euler_headingAddressNumber_Valu
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
	  ;% hfsubh0wqd.uint8_t1_Value
	  section.data(2).logicalSrcIdx = 55;
	  section.data(2).dtTransOffset = 1;
	
	  ;% hfsubh0wqd.uint8_t2_Value
	  section.data(3).logicalSrcIdx = 56;
	  section.data(3).dtTransOffset = 2;
	
	  ;% hfsubh0wqd.uint8_t3_Value
	  section.data(4).logicalSrcIdx = 57;
	  section.data(4).dtTransOffset = 3;
	
	  ;% hfsubh0wqd.euler_rollAddressNumber_Value
	  section.data(5).logicalSrcIdx = 58;
	  section.data(5).dtTransOffset = 4;
	
	  ;% hfsubh0wqd.uint8_t1_Value_pdh1mmrkaf
	  section.data(6).logicalSrcIdx = 59;
	  section.data(6).dtTransOffset = 5;
	
	  ;% hfsubh0wqd.uint8_t2_Value_bjkzcm1v50
	  section.data(7).logicalSrcIdx = 60;
	  section.data(7).dtTransOffset = 6;
	
	  ;% hfsubh0wqd.uint8_t3_Value_bzki1yseu2
	  section.data(8).logicalSrcIdx = 61;
	  section.data(8).dtTransOffset = 7;
	
	  ;% hfsubh0wqd.euler_pitchAddressNumber_Value
	  section.data(9).logicalSrcIdx = 62;
	  section.data(9).dtTransOffset = 8;
	
	  ;% hfsubh0wqd.uint8_t1_Value_nh5qfyju0z
	  section.data(10).logicalSrcIdx = 63;
	  section.data(10).dtTransOffset = 9;
	
	  ;% hfsubh0wqd.uint8_t2_Value_g33fsjovlh
	  section.data(11).logicalSrcIdx = 64;
	  section.data(11).dtTransOffset = 10;
	
	  ;% hfsubh0wqd.uint8_t3_Value_fcyoyjujtb
	  section.data(12).logicalSrcIdx = 65;
	  section.data(12).dtTransOffset = 11;
	
	  ;% hfsubh0wqd.gyr_xAddressNumber_Value
	  section.data(13).logicalSrcIdx = 66;
	  section.data(13).dtTransOffset = 12;
	
	  ;% hfsubh0wqd.uint8_t1_Value_j2wfmnih52
	  section.data(14).logicalSrcIdx = 67;
	  section.data(14).dtTransOffset = 13;
	
	  ;% hfsubh0wqd.uint8_t2_Value_l24qi4amhg
	  section.data(15).logicalSrcIdx = 68;
	  section.data(15).dtTransOffset = 14;
	
	  ;% hfsubh0wqd.uint8_t3_Value_abjhsc0f24
	  section.data(16).logicalSrcIdx = 69;
	  section.data(16).dtTransOffset = 15;
	
	  ;% hfsubh0wqd.acc_xAddressNumber_Value
	  section.data(17).logicalSrcIdx = 70;
	  section.data(17).dtTransOffset = 16;
	
	  ;% hfsubh0wqd.uint8_t1_Value_d1nmexi4u4
	  section.data(18).logicalSrcIdx = 71;
	  section.data(18).dtTransOffset = 17;
	
	  ;% hfsubh0wqd.uint8_t2_Value_a4kbzdzszs
	  section.data(19).logicalSrcIdx = 72;
	  section.data(19).dtTransOffset = 18;
	
	  ;% hfsubh0wqd.uint8_t3_Value_crbst3qg0d
	  section.data(20).logicalSrcIdx = 73;
	  section.data(20).dtTransOffset = 19;
	
	  ;% hfsubh0wqd.gyr_yAddressNumber_Value
	  section.data(21).logicalSrcIdx = 74;
	  section.data(21).dtTransOffset = 20;
	
	  ;% hfsubh0wqd.uint8_t1_Value_hhpzgdklhj
	  section.data(22).logicalSrcIdx = 75;
	  section.data(22).dtTransOffset = 21;
	
	  ;% hfsubh0wqd.uint8_t2_Value_kfo5pj123x
	  section.data(23).logicalSrcIdx = 76;
	  section.data(23).dtTransOffset = 22;
	
	  ;% hfsubh0wqd.uint8_t3_Value_llnlocx0jp
	  section.data(24).logicalSrcIdx = 77;
	  section.data(24).dtTransOffset = 23;
	
	  ;% hfsubh0wqd.acc_yAddressNumber_Value
	  section.data(25).logicalSrcIdx = 78;
	  section.data(25).dtTransOffset = 24;
	
	  ;% hfsubh0wqd.uint8_t1_Value_k55hriosiw
	  section.data(26).logicalSrcIdx = 79;
	  section.data(26).dtTransOffset = 25;
	
	  ;% hfsubh0wqd.uint8_t2_Value_ewsrijoi1y
	  section.data(27).logicalSrcIdx = 80;
	  section.data(27).dtTransOffset = 26;
	
	  ;% hfsubh0wqd.uint8_t3_Value_csq2nflakv
	  section.data(28).logicalSrcIdx = 81;
	  section.data(28).dtTransOffset = 27;
	
	  ;% hfsubh0wqd.gyr_zAddressNumber_Value
	  section.data(29).logicalSrcIdx = 82;
	  section.data(29).dtTransOffset = 28;
	
	  ;% hfsubh0wqd.uint8_t1_Value_iarfsgp4wp
	  section.data(30).logicalSrcIdx = 83;
	  section.data(30).dtTransOffset = 29;
	
	  ;% hfsubh0wqd.uint8_t2_Value_h25nsb42dk
	  section.data(31).logicalSrcIdx = 84;
	  section.data(31).dtTransOffset = 30;
	
	  ;% hfsubh0wqd.uint8_t3_Value_irei2yyusa
	  section.data(32).logicalSrcIdx = 85;
	  section.data(32).dtTransOffset = 31;
	
	  ;% hfsubh0wqd.acc_zAddressNumber_Value
	  section.data(33).logicalSrcIdx = 86;
	  section.data(33).dtTransOffset = 32;
	
	  ;% hfsubh0wqd.uint8_t1_Value_escjrdlkcn
	  section.data(34).logicalSrcIdx = 87;
	  section.data(34).dtTransOffset = 33;
	
	  ;% hfsubh0wqd.uint8_t2_Value_ohr50x5o4g
	  section.data(35).logicalSrcIdx = 88;
	  section.data(35).dtTransOffset = 34;
	
	  ;% hfsubh0wqd.uint8_t3_Value_g5ikrmq33j
	  section.data(36).logicalSrcIdx = 89;
	  section.data(36).dtTransOffset = 35;
	
	  ;% hfsubh0wqd.radio_throttleAddressNumber_Val
	  section.data(37).logicalSrcIdx = 90;
	  section.data(37).dtTransOffset = 36;
	
	  ;% hfsubh0wqd.uint8_t1_Value_blcwsn3mod
	  section.data(38).logicalSrcIdx = 91;
	  section.data(38).dtTransOffset = 37;
	
	  ;% hfsubh0wqd.uint8_t2_Value_feo10nb4xc
	  section.data(39).logicalSrcIdx = 92;
	  section.data(39).dtTransOffset = 38;
	
	  ;% hfsubh0wqd.uint8_t3_Value_p3y25qn4th
	  section.data(40).logicalSrcIdx = 93;
	  section.data(40).dtTransOffset = 39;
	
	  ;% hfsubh0wqd.radio_steeringAddressNumber_Val
	  section.data(41).logicalSrcIdx = 94;
	  section.data(41).dtTransOffset = 40;
	
	  ;% hfsubh0wqd.uint8_t1_Value_mwwrewolew
	  section.data(42).logicalSrcIdx = 95;
	  section.data(42).dtTransOffset = 41;
	
	  ;% hfsubh0wqd.uint8_t2_Value_plp2fa3e20
	  section.data(43).logicalSrcIdx = 96;
	  section.data(43).dtTransOffset = 42;
	
	  ;% hfsubh0wqd.uint8_t3_Value_feq0mqtkvh
	  section.data(44).logicalSrcIdx = 97;
	  section.data(44).dtTransOffset = 43;
	
	  ;% hfsubh0wqd.velocity_RRAddressNumber_Value
	  section.data(45).logicalSrcIdx = 98;
	  section.data(45).dtTransOffset = 44;
	
	  ;% hfsubh0wqd.uint8_t1_Value_iswfbqmgg0
	  section.data(46).logicalSrcIdx = 99;
	  section.data(46).dtTransOffset = 45;
	
	  ;% hfsubh0wqd.uint8_t2_Value_og3vod555z
	  section.data(47).logicalSrcIdx = 100;
	  section.data(47).dtTransOffset = 46;
	
	  ;% hfsubh0wqd.uint8_t3_Value_o4pefzbbdu
	  section.data(48).logicalSrcIdx = 101;
	  section.data(48).dtTransOffset = 47;
	
	  ;% hfsubh0wqd.velocity_RLAddressNumber_Value
	  section.data(49).logicalSrcIdx = 102;
	  section.data(49).dtTransOffset = 48;
	
	  ;% hfsubh0wqd.uint8_t1_Value_cvek4esgvd
	  section.data(50).logicalSrcIdx = 103;
	  section.data(50).dtTransOffset = 49;
	
	  ;% hfsubh0wqd.uint8_t2_Value_lseyezibvx
	  section.data(51).logicalSrcIdx = 104;
	  section.data(51).dtTransOffset = 50;
	
	  ;% hfsubh0wqd.uint8_t3_Value_o1yzfl3g0m
	  section.data(52).logicalSrcIdx = 105;
	  section.data(52).dtTransOffset = 51;
	
	  ;% hfsubh0wqd.velocity_FRAddressNumber_Value
	  section.data(53).logicalSrcIdx = 106;
	  section.data(53).dtTransOffset = 52;
	
	  ;% hfsubh0wqd.uint8_t1_Value_e4uo010ilu
	  section.data(54).logicalSrcIdx = 107;
	  section.data(54).dtTransOffset = 53;
	
	  ;% hfsubh0wqd.uint8_t2_Value_ndppfky1ku
	  section.data(55).logicalSrcIdx = 108;
	  section.data(55).dtTransOffset = 54;
	
	  ;% hfsubh0wqd.uint8_t3_Value_gqtbi3ry5p
	  section.data(56).logicalSrcIdx = 109;
	  section.data(56).dtTransOffset = 55;
	
	  ;% hfsubh0wqd.velocity_FLAddressNumber_Value
	  section.data(57).logicalSrcIdx = 110;
	  section.data(57).dtTransOffset = 56;
	
	  ;% hfsubh0wqd.uint8_t1_Value_fbwzrt0xsu
	  section.data(58).logicalSrcIdx = 111;
	  section.data(58).dtTransOffset = 57;
	
	  ;% hfsubh0wqd.uint8_t2_Value_nlddlhtmy4
	  section.data(59).logicalSrcIdx = 112;
	  section.data(59).dtTransOffset = 58;
	
	  ;% hfsubh0wqd.uint8_t3_Value_p5kni5nbh4
	  section.data(60).logicalSrcIdx = 113;
	  section.data(60).dtTransOffset = 59;
	
	  ;% hfsubh0wqd.DeadSwitch_Value
	  section.data(61).logicalSrcIdx = 114;
	  section.data(61).dtTransOffset = 60;
	
	  ;% hfsubh0wqd.TakeData_Value
	  section.data(62).logicalSrcIdx = 115;
	  section.data(62).dtTransOffset = 61;
	
	  ;% hfsubh0wqd.ServoandRadioOn_Value
	  section.data(63).logicalSrcIdx = 116;
	  section.data(63).dtTransOffset = 62;
	
	  ;% hfsubh0wqd.MotorControllersOn_Value
	  section.data(64).logicalSrcIdx = 117;
	  section.data(64).dtTransOffset = 63;
	
	  ;% hfsubh0wqd.IMUReset_Value
	  section.data(65).logicalSrcIdx = 118;
	  section.data(65).dtTransOffset = 64;
	
	  ;% hfsubh0wqd.PrinttheregistermapontheTeensy_
	  section.data(66).logicalSrcIdx = 119;
	  section.data(66).dtTransOffset = 65;
	
	  ;% hfsubh0wqd.PrinttheimudataontheTeensy_Valu
	  section.data(67).logicalSrcIdx = 120;
	  section.data(67).dtTransOffset = 66;
	
	  ;% hfsubh0wqd.Printtheradiotranceiverdataonth
	  section.data(68).logicalSrcIdx = 121;
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
    ;% Auto data (bcbnz3pviq3)
    ;%
      section.nData     = 22;
      section.data(22)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.entylulmd5
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% bcbnz3pviq3.hoftz5ist3
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% bcbnz3pviq3.g1ymh3n4o2
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% bcbnz3pviq3.oxx2uzgtga
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% bcbnz3pviq3.jzn5f0csdz
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% bcbnz3pviq3.lmf2b3vgl1
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% bcbnz3pviq3.ffppn00ujx
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% bcbnz3pviq3.os3hh3ptsn
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% bcbnz3pviq3.j2f3blujwc
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% bcbnz3pviq3.nexjqxxcjb
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% bcbnz3pviq3.bob2qs0m2o
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% bcbnz3pviq3.lyph5br3yp
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% bcbnz3pviq3.f5oufzjurl
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% bcbnz3pviq3.eddjjje21f
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% bcbnz3pviq3.jlwckkxiei
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% bcbnz3pviq3.j3lqwe4tw1
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% bcbnz3pviq3.nxpg2jsbyq
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% bcbnz3pviq3.dr5drw3fbh
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% bcbnz3pviq3.mmjec4i05n
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% bcbnz3pviq3.nzzylt4pfp
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% bcbnz3pviq3.flm2pggnbu
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
	  ;% bcbnz3pviq3.ewusjnsqza
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 21;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.kiqlcrbhpd
	  section.data(1).logicalSrcIdx = 22;
	  section.data(1).dtTransOffset = 0;
	
	  ;% bcbnz3pviq3.mu1tda4pvu
	  section.data(2).logicalSrcIdx = 23;
	  section.data(2).dtTransOffset = 1;
	
	  ;% bcbnz3pviq3.mz1bnlqwjq
	  section.data(3).logicalSrcIdx = 24;
	  section.data(3).dtTransOffset = 2;
	
	  ;% bcbnz3pviq3.onewuzpual
	  section.data(4).logicalSrcIdx = 25;
	  section.data(4).dtTransOffset = 3;
	
	  ;% bcbnz3pviq3.ghwskbbhdi
	  section.data(5).logicalSrcIdx = 26;
	  section.data(5).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 9;
      section.data(9)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.fo0pm3uwlj
	  section.data(1).logicalSrcIdx = 27;
	  section.data(1).dtTransOffset = 0;
	
	  ;% bcbnz3pviq3.lnxekykaij
	  section.data(2).logicalSrcIdx = 28;
	  section.data(2).dtTransOffset = 1;
	
	  ;% bcbnz3pviq3.fjamwntira
	  section.data(3).logicalSrcIdx = 29;
	  section.data(3).dtTransOffset = 2;
	
	  ;% bcbnz3pviq3.ecjnrxz4zu
	  section.data(4).logicalSrcIdx = 30;
	  section.data(4).dtTransOffset = 3;
	
	  ;% bcbnz3pviq3.onhfoswdat
	  section.data(5).logicalSrcIdx = 31;
	  section.data(5).dtTransOffset = 4;
	
	  ;% bcbnz3pviq3.eagfij1pkr
	  section.data(6).logicalSrcIdx = 32;
	  section.data(6).dtTransOffset = 5;
	
	  ;% bcbnz3pviq3.bjwvdathsg
	  section.data(7).logicalSrcIdx = 33;
	  section.data(7).dtTransOffset = 6;
	
	  ;% bcbnz3pviq3.dhwmsgy1vn
	  section.data(8).logicalSrcIdx = 34;
	  section.data(8).dtTransOffset = 7;
	
	  ;% bcbnz3pviq3.ieuqbkocix
	  section.data(9).logicalSrcIdx = 35;
	  section.data(9).dtTransOffset = 8;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.b0mz21uh1d.nq1r3xuc2f
	  section.data(1).logicalSrcIdx = 36;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.pa2bl0ovap.nq1r3xuc2f
	  section.data(1).logicalSrcIdx = 37;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.hsog1gm5cf.nq1r3xuc2f
	  section.data(1).logicalSrcIdx = 38;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.fug4zee3lg.nq1r3xuc2f
	  section.data(1).logicalSrcIdx = 39;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.et41d54xaa.g5bezzodno
	  section.data(1).logicalSrcIdx = 40;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.akrpzvrymx.eby3lmyfkq
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.k0bypo2i44.g5bezzodno
	  section.data(1).logicalSrcIdx = 42;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.mwoivz5m3d.eby3lmyfkq
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.ns3ir5puko.g5bezzodno
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.bx1r2ppyrf.eby3lmyfkq
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.erscwsexjd.g5bezzodno
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.nqervnvkau.eby3lmyfkq
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.mfqext4ds3v.g5bezzodno
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.pz2brhyl1ja.eby3lmyfkq
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.bjnlk3ig1k.nq1r3xuc2f
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.fcmva1ljw4.nq1r3xuc2f
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.g2oz1nx5o5.nq1r3xuc2f
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.l0ftidyaau.nq1r3xuc2f
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.g33oxuuwvv.nq1r3xuc2f
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.gwhnv2z3du.nq1r3xuc2f
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.fno2gqm1kq.nq1r3xuc2f
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.ispi3o2kzu.nq1r3xuc2f
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.l54i1azqz0.nq1r3xuc2f
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.ctj4hrrxsm.nq1r3xuc2f
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.kf5lrubpxzk.nq1r3xuc2f
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.ofcbwygs4y.lhmuybsd40
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.lw402j4sww.lhmuybsd40
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.bvnpvtn3w2.lhmuybsd40
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.a5cawnqdxh.lhmuybsd40
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.ptn0zzsasl.lhmuybsd40
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.mfzul4xb0c.lhmuybsd40
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(34) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.lor4in3kgh.lhmuybsd40
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(35) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.drvj3iyv0v.lhmuybsd40
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(36) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.a1i1joqiwo.lhmuybsd40
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(37) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.kwayhm3myh.lhmuybsd40
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(38) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.lne55bwcle.lhmuybsd40
	  section.data(1).logicalSrcIdx = 71;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(39) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.kq0x5ztojb.lhmuybsd40
	  section.data(1).logicalSrcIdx = 72;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(40) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.bgnhpbvcji.lhmuybsd40
	  section.data(1).logicalSrcIdx = 73;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(41) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.kxd4n1z1x5.lhmuybsd40
	  section.data(1).logicalSrcIdx = 74;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(42) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bcbnz3pviq3.njwbwsnfxkq.lhmuybsd40
	  section.data(1).logicalSrcIdx = 75;
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
    ;% Auto data (ncrheapzqjr)
    ;%
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.gpy3tgdcfh
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ncrheapzqjr.fwzd0r5tnv
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ncrheapzqjr.a42pnyunic
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% ncrheapzqjr.kfizrl3opc
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% ncrheapzqjr.dzhdxmtenc
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% ncrheapzqjr.jl0yhoxgot
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% ncrheapzqjr.l05qjdpzuf
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% ncrheapzqjr.ln1yrxjkvg
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% ncrheapzqjr.puxssjp2qc
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% ncrheapzqjr.nmpzbjxsau
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% ncrheapzqjr.f0wrzpmmno
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% ncrheapzqjr.kfarebjxqb
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% ncrheapzqjr.lqinklytjt
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 14;
      section.data(14)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.kw2tzeok2l.LoggedData
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ncrheapzqjr.lzj1xkabkw.LoggedData
	  section.data(2).logicalSrcIdx = 14;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ncrheapzqjr.ig4lgoyz3b.LoggedData
	  section.data(3).logicalSrcIdx = 15;
	  section.data(3).dtTransOffset = 2;
	
	  ;% ncrheapzqjr.bgy2k5rsb5.LoggedData
	  section.data(4).logicalSrcIdx = 16;
	  section.data(4).dtTransOffset = 3;
	
	  ;% ncrheapzqjr.imz1le2d10.LoggedData
	  section.data(5).logicalSrcIdx = 17;
	  section.data(5).dtTransOffset = 4;
	
	  ;% ncrheapzqjr.kkk1v21s1n.LoggedData
	  section.data(6).logicalSrcIdx = 18;
	  section.data(6).dtTransOffset = 6;
	
	  ;% ncrheapzqjr.nja1kzgr1s.LoggedData
	  section.data(7).logicalSrcIdx = 19;
	  section.data(7).dtTransOffset = 7;
	
	  ;% ncrheapzqjr.aflbxsnnfp.LoggedData
	  section.data(8).logicalSrcIdx = 20;
	  section.data(8).dtTransOffset = 11;
	
	  ;% ncrheapzqjr.bzuwccxjpy.LoggedData
	  section.data(9).logicalSrcIdx = 21;
	  section.data(9).dtTransOffset = 13;
	
	  ;% ncrheapzqjr.fpn1jbhrx2.LoggedData
	  section.data(10).logicalSrcIdx = 22;
	  section.data(10).dtTransOffset = 15;
	
	  ;% ncrheapzqjr.bsdagjg02n.LoggedData
	  section.data(11).logicalSrcIdx = 23;
	  section.data(11).dtTransOffset = 17;
	
	  ;% ncrheapzqjr.oj2bgni3op.LoggedData
	  section.data(12).logicalSrcIdx = 24;
	  section.data(12).dtTransOffset = 20;
	
	  ;% ncrheapzqjr.a0wp1wg45h.LoggedData
	  section.data(13).logicalSrcIdx = 25;
	  section.data(13).dtTransOffset = 21;
	
	  ;% ncrheapzqjr.b5any2pkvn.LoggedData
	  section.data(14).logicalSrcIdx = 26;
	  section.data(14).dtTransOffset = 22;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.hc02i2dogj
	  section.data(1).logicalSrcIdx = 27;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ncrheapzqjr.g15n22rf3n
	  section.data(2).logicalSrcIdx = 28;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.mhgurwpbrc
	  section.data(1).logicalSrcIdx = 29;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ncrheapzqjr.esxqtezkw3
	  section.data(2).logicalSrcIdx = 30;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ncrheapzqjr.mnrv3eqtb3
	  section.data(3).logicalSrcIdx = 31;
	  section.data(3).dtTransOffset = 2;
	
	  ;% ncrheapzqjr.d50qunws5l
	  section.data(4).logicalSrcIdx = 32;
	  section.data(4).dtTransOffset = 3;
	
	  ;% ncrheapzqjr.auz41dwhus
	  section.data(5).logicalSrcIdx = 33;
	  section.data(5).dtTransOffset = 4;
	
	  ;% ncrheapzqjr.owqcz3sulf
	  section.data(6).logicalSrcIdx = 34;
	  section.data(6).dtTransOffset = 5;
	
	  ;% ncrheapzqjr.bqrgujk3hd
	  section.data(7).logicalSrcIdx = 35;
	  section.data(7).dtTransOffset = 6;
	
	  ;% ncrheapzqjr.jtj3jgwqsk
	  section.data(8).logicalSrcIdx = 36;
	  section.data(8).dtTransOffset = 7;
	
	  ;% ncrheapzqjr.owf1reatuq
	  section.data(9).logicalSrcIdx = 37;
	  section.data(9).dtTransOffset = 8;
	
	  ;% ncrheapzqjr.hyy0qqv0s1
	  section.data(10).logicalSrcIdx = 38;
	  section.data(10).dtTransOffset = 9;
	
	  ;% ncrheapzqjr.mr5ehce5rp
	  section.data(11).logicalSrcIdx = 39;
	  section.data(11).dtTransOffset = 10;
	
	  ;% ncrheapzqjr.em13oopoli
	  section.data(12).logicalSrcIdx = 40;
	  section.data(12).dtTransOffset = 11;
	
	  ;% ncrheapzqjr.e35gwnahbt
	  section.data(13).logicalSrcIdx = 41;
	  section.data(13).dtTransOffset = 12;
	
	  ;% ncrheapzqjr.n0gqhim2re
	  section.data(14).logicalSrcIdx = 42;
	  section.data(14).dtTransOffset = 13;
	
	  ;% ncrheapzqjr.f04c2gxlwc
	  section.data(15).logicalSrcIdx = 43;
	  section.data(15).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.ofcbwygs4y.hoxxp4dx1q
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.ofcbwygs4y.neoeyve35c
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.lw402j4sww.hoxxp4dx1q
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.lw402j4sww.neoeyve35c
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.bvnpvtn3w2.hoxxp4dx1q
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.bvnpvtn3w2.neoeyve35c
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.a5cawnqdxh.hoxxp4dx1q
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.a5cawnqdxh.neoeyve35c
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.ptn0zzsasl.hoxxp4dx1q
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.ptn0zzsasl.neoeyve35c
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.mfzul4xb0c.hoxxp4dx1q
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.mfzul4xb0c.neoeyve35c
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.lor4in3kgh.hoxxp4dx1q
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.lor4in3kgh.neoeyve35c
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.drvj3iyv0v.hoxxp4dx1q
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.drvj3iyv0v.neoeyve35c
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.a1i1joqiwo.hoxxp4dx1q
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.a1i1joqiwo.neoeyve35c
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.kwayhm3myh.hoxxp4dx1q
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.kwayhm3myh.neoeyve35c
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.lne55bwcle.hoxxp4dx1q
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.lne55bwcle.neoeyve35c
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.kq0x5ztojb.hoxxp4dx1q
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.kq0x5ztojb.neoeyve35c
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.bgnhpbvcji.hoxxp4dx1q
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.bgnhpbvcji.neoeyve35c
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.kxd4n1z1x5.hoxxp4dx1q
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.kxd4n1z1x5.neoeyve35c
	  section.data(1).logicalSrcIdx = 71;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.njwbwsnfxkq.hoxxp4dx1q
	  section.data(1).logicalSrcIdx = 72;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ncrheapzqjr.njwbwsnfxkq.neoeyve35c
	  section.data(1).logicalSrcIdx = 73;
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


  targMap.checksum0 = 2449984981;
  targMap.checksum1 = 271937281;
  targMap.checksum2 = 248947612;
  targMap.checksum3 = 236966218;

