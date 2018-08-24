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
      
      section.nData     = 16;
      section.data(16)  = dumData; %prealloc
      
	  ;% lpyvnxj1h0.FixPtBitwiseOperator1_BitMask
	  section.data(1).logicalSrcIdx = 2;
	  section.data(1).dtTransOffset = 0;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_j51sx5qhjl
	  section.data(2).logicalSrcIdx = 3;
	  section.data(2).dtTransOffset = 1;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_ll25hv2pst
	  section.data(3).logicalSrcIdx = 4;
	  section.data(3).dtTransOffset = 2;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_fg3lbkzwhk
	  section.data(4).logicalSrcIdx = 5;
	  section.data(4).dtTransOffset = 3;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_pxonffanhl
	  section.data(5).logicalSrcIdx = 6;
	  section.data(5).dtTransOffset = 4;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_hl5ghk4iee
	  section.data(6).logicalSrcIdx = 7;
	  section.data(6).dtTransOffset = 5;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_mcgdnlxhj3
	  section.data(7).logicalSrcIdx = 8;
	  section.data(7).dtTransOffset = 6;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_pwjuaz1cmf
	  section.data(8).logicalSrcIdx = 9;
	  section.data(8).dtTransOffset = 7;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_e0elo5d0jz
	  section.data(9).logicalSrcIdx = 10;
	  section.data(9).dtTransOffset = 8;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_ad0govex5e
	  section.data(10).logicalSrcIdx = 11;
	  section.data(10).dtTransOffset = 9;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_kfenjhmvco
	  section.data(11).logicalSrcIdx = 12;
	  section.data(11).dtTransOffset = 10;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_dv0hmz0dcl
	  section.data(12).logicalSrcIdx = 13;
	  section.data(12).dtTransOffset = 11;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_ib30bchkku
	  section.data(13).logicalSrcIdx = 14;
	  section.data(13).dtTransOffset = 12;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_hmvz0ity5j
	  section.data(14).logicalSrcIdx = 15;
	  section.data(14).dtTransOffset = 13;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_f2btdw51to
	  section.data(15).logicalSrcIdx = 16;
	  section.data(15).dtTransOffset = 14;
	
	  ;% lpyvnxj1h0.FixPtBitwiseOperator_a3nz0k5lnj
	  section.data(16).logicalSrcIdx = 17;
	  section.data(16).dtTransOffset = 15;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 35;
      section.data(35)  = dumData; %prealloc
      
	  ;% lpyvnxj1h0._Value
	  section.data(1).logicalSrcIdx = 18;
	  section.data(1).dtTransOffset = 0;
	
	  ;% lpyvnxj1h0._Value_ptyw2e1opn
	  section.data(2).logicalSrcIdx = 19;
	  section.data(2).dtTransOffset = 1;
	
	  ;% lpyvnxj1h0.Outport_Y0
	  section.data(3).logicalSrcIdx = 20;
	  section.data(3).dtTransOffset = 2;
	
	  ;% lpyvnxj1h0.Outport1_Y0
	  section.data(4).logicalSrcIdx = 21;
	  section.data(4).dtTransOffset = 3;
	
	  ;% lpyvnxj1h0.Outport2_Y0
	  section.data(5).logicalSrcIdx = 22;
	  section.data(5).dtTransOffset = 4;
	
	  ;% lpyvnxj1h0.Outport3_Y0
	  section.data(6).logicalSrcIdx = 23;
	  section.data(6).dtTransOffset = 5;
	
	  ;% lpyvnxj1h0.DesiredVelocityms_Time
	  section.data(7).logicalSrcIdx = 24;
	  section.data(7).dtTransOffset = 6;
	
	  ;% lpyvnxj1h0.DesiredVelocityms_Y0
	  section.data(8).logicalSrcIdx = 25;
	  section.data(8).dtTransOffset = 7;
	
	  ;% lpyvnxj1h0.DesiredVelocityms_YFinal
	  section.data(9).logicalSrcIdx = 26;
	  section.data(9).dtTransOffset = 8;
	
	  ;% lpyvnxj1h0.Integrator_IC
	  section.data(10).logicalSrcIdx = 27;
	  section.data(10).dtTransOffset = 9;
	
	  ;% lpyvnxj1h0.Saturation_UpperSat
	  section.data(11).logicalSrcIdx = 28;
	  section.data(11).dtTransOffset = 10;
	
	  ;% lpyvnxj1h0.Saturation_LowerSat
	  section.data(12).logicalSrcIdx = 29;
	  section.data(12).dtTransOffset = 11;
	
	  ;% lpyvnxj1h0.bitsmNm_Gain
	  section.data(13).logicalSrcIdx = 30;
	  section.data(13).dtTransOffset = 12;
	
	  ;% lpyvnxj1h0.bitsmNm_Gain_hdnf15wrbt
	  section.data(14).logicalSrcIdx = 31;
	  section.data(14).dtTransOffset = 13;
	
	  ;% lpyvnxj1h0.bitsmNm_Gain_gfnjdunlwe
	  section.data(15).logicalSrcIdx = 32;
	  section.data(15).dtTransOffset = 14;
	
	  ;% lpyvnxj1h0.bitsmNm_Gain_bx24kctye3
	  section.data(16).logicalSrcIdx = 33;
	  section.data(16).dtTransOffset = 15;
	
	  ;% lpyvnxj1h0.Compensatesfordirectionofspinwa
	  section.data(17).logicalSrcIdx = 34;
	  section.data(17).dtTransOffset = 16;
	
	  ;% lpyvnxj1h0.Compensatesfordirect_ishdnk5xr2
	  section.data(18).logicalSrcIdx = 35;
	  section.data(18).dtTransOffset = 17;
	
	  ;% lpyvnxj1h0.RPMtoms_Gain
	  section.data(19).logicalSrcIdx = 36;
	  section.data(19).dtTransOffset = 18;
	
	  ;% lpyvnxj1h0.bitsmNm_Gain_fcdokc5uar
	  section.data(20).logicalSrcIdx = 37;
	  section.data(20).dtTransOffset = 19;
	
	  ;% lpyvnxj1h0.AccelerationInttoDoubleScaleFac
	  section.data(21).logicalSrcIdx = 38;
	  section.data(21).dtTransOffset = 20;
	
	  ;% lpyvnxj1h0.GyroscopeInttoDoubleScaleFactor
	  section.data(22).logicalSrcIdx = 39;
	  section.data(22).dtTransOffset = 21;
	
	  ;% lpyvnxj1h0.AccelerationInttoDou_gfeqh2hxee
	  section.data(23).logicalSrcIdx = 40;
	  section.data(23).dtTransOffset = 22;
	
	  ;% lpyvnxj1h0.GyroscopeInttoDouble_fnugxjs4f5
	  section.data(24).logicalSrcIdx = 41;
	  section.data(24).dtTransOffset = 23;
	
	  ;% lpyvnxj1h0.AccelerationInttoDou_bx3sfeju3y
	  section.data(25).logicalSrcIdx = 42;
	  section.data(25).dtTransOffset = 24;
	
	  ;% lpyvnxj1h0.GyroscopeInttoDouble_d5uuy2ctqj
	  section.data(26).logicalSrcIdx = 43;
	  section.data(26).dtTransOffset = 25;
	
	  ;% lpyvnxj1h0.TriggerValueRequiredforSubsyste
	  section.data(27).logicalSrcIdx = 44;
	  section.data(27).dtTransOffset = 26;
	
	  ;% lpyvnxj1h0.TriggerSwitch_Threshold
	  section.data(28).logicalSrcIdx = 45;
	  section.data(28).dtTransOffset = 27;
	
	  ;% lpyvnxj1h0.TimeallottedforSSIVtoinitialize
	  section.data(29).logicalSrcIdx = 46;
	  section.data(29).dtTransOffset = 28;
	
	  ;% lpyvnxj1h0.EulerInttoDoubleScaleFactor_Gai
	  section.data(30).logicalSrcIdx = 47;
	  section.data(30).dtTransOffset = 29;
	
	  ;% lpyvnxj1h0.EulerInttoDoubleScal_k5rkmzovmy
	  section.data(31).logicalSrcIdx = 48;
	  section.data(31).dtTransOffset = 30;
	
	  ;% lpyvnxj1h0.EulerInttoDoubleScal_mvzrvwh5kl
	  section.data(32).logicalSrcIdx = 49;
	  section.data(32).dtTransOffset = 31;
	
	  ;% lpyvnxj1h0.Constant6_Value
	  section.data(33).logicalSrcIdx = 50;
	  section.data(33).dtTransOffset = 32;
	
	  ;% lpyvnxj1h0.SimulationTimeStep_Value
	  section.data(34).logicalSrcIdx = 51;
	  section.data(34).dtTransOffset = 33;
	
	  ;% lpyvnxj1h0.Constant7_Value
	  section.data(35).logicalSrcIdx = 52;
	  section.data(35).dtTransOffset = 34;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 72;
      section.data(72)  = dumData; %prealloc
      
	  ;% lpyvnxj1h0.DeadSwitch_Value
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
	  ;% lpyvnxj1h0.TakeData_Value
	  section.data(2).logicalSrcIdx = 54;
	  section.data(2).dtTransOffset = 1;
	
	  ;% lpyvnxj1h0.ServoandRadioOn_Value
	  section.data(3).logicalSrcIdx = 55;
	  section.data(3).dtTransOffset = 2;
	
	  ;% lpyvnxj1h0.MotorControllersOn_Value
	  section.data(4).logicalSrcIdx = 56;
	  section.data(4).dtTransOffset = 3;
	
	  ;% lpyvnxj1h0.IMUReset_Value
	  section.data(5).logicalSrcIdx = 57;
	  section.data(5).dtTransOffset = 4;
	
	  ;% lpyvnxj1h0.PrinttheregistermapontheTeensy_
	  section.data(6).logicalSrcIdx = 58;
	  section.data(6).dtTransOffset = 5;
	
	  ;% lpyvnxj1h0.PrinttheimudataontheTeensy_Valu
	  section.data(7).logicalSrcIdx = 59;
	  section.data(7).dtTransOffset = 6;
	
	  ;% lpyvnxj1h0.Printtheradiotranceiverdataonth
	  section.data(8).logicalSrcIdx = 60;
	  section.data(8).dtTransOffset = 7;
	
	  ;% lpyvnxj1h0.radio_steeringAddressNumber_Val
	  section.data(9).logicalSrcIdx = 61;
	  section.data(9).dtTransOffset = 8;
	
	  ;% lpyvnxj1h0.uint8_t1_Value
	  section.data(10).logicalSrcIdx = 62;
	  section.data(10).dtTransOffset = 9;
	
	  ;% lpyvnxj1h0.uint8_t2_Value
	  section.data(11).logicalSrcIdx = 63;
	  section.data(11).dtTransOffset = 10;
	
	  ;% lpyvnxj1h0.uint8_t3_Value
	  section.data(12).logicalSrcIdx = 64;
	  section.data(12).dtTransOffset = 11;
	
	  ;% lpyvnxj1h0.velocity_FRAddressNumber_Value
	  section.data(13).logicalSrcIdx = 65;
	  section.data(13).dtTransOffset = 12;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_cwc1djd3yz
	  section.data(14).logicalSrcIdx = 66;
	  section.data(14).dtTransOffset = 13;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_gxe1aomgo2
	  section.data(15).logicalSrcIdx = 67;
	  section.data(15).dtTransOffset = 14;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_ihh2h0aa4q
	  section.data(16).logicalSrcIdx = 68;
	  section.data(16).dtTransOffset = 15;
	
	  ;% lpyvnxj1h0.velocity_FLAddressNumber_Value
	  section.data(17).logicalSrcIdx = 69;
	  section.data(17).dtTransOffset = 16;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_h2gcfcaqyd
	  section.data(18).logicalSrcIdx = 70;
	  section.data(18).dtTransOffset = 17;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_guv1s5zpct
	  section.data(19).logicalSrcIdx = 71;
	  section.data(19).dtTransOffset = 18;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_lqt5w51gff
	  section.data(20).logicalSrcIdx = 72;
	  section.data(20).dtTransOffset = 19;
	
	  ;% lpyvnxj1h0.velocity_RRAddressNumber_Value
	  section.data(21).logicalSrcIdx = 73;
	  section.data(21).dtTransOffset = 20;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_pebk0w3dxv
	  section.data(22).logicalSrcIdx = 74;
	  section.data(22).dtTransOffset = 21;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_b50z1rnpdb
	  section.data(23).logicalSrcIdx = 75;
	  section.data(23).dtTransOffset = 22;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_fkdsna2sdf
	  section.data(24).logicalSrcIdx = 76;
	  section.data(24).dtTransOffset = 23;
	
	  ;% lpyvnxj1h0.velocity_RLAddressNumber_Value
	  section.data(25).logicalSrcIdx = 77;
	  section.data(25).dtTransOffset = 24;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_mwigsjn0on
	  section.data(26).logicalSrcIdx = 78;
	  section.data(26).dtTransOffset = 25;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_fgokpme3bd
	  section.data(27).logicalSrcIdx = 79;
	  section.data(27).dtTransOffset = 26;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_p0wty1kh3e
	  section.data(28).logicalSrcIdx = 80;
	  section.data(28).dtTransOffset = 27;
	
	  ;% lpyvnxj1h0.radio_throttleAddressNumber_Val
	  section.data(29).logicalSrcIdx = 81;
	  section.data(29).dtTransOffset = 28;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_moq2jb2dbk
	  section.data(30).logicalSrcIdx = 82;
	  section.data(30).dtTransOffset = 29;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_j45n0wdi4j
	  section.data(31).logicalSrcIdx = 83;
	  section.data(31).dtTransOffset = 30;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_fncxogyzya
	  section.data(32).logicalSrcIdx = 84;
	  section.data(32).dtTransOffset = 31;
	
	  ;% lpyvnxj1h0.euler_headingAddressNumber_Valu
	  section.data(33).logicalSrcIdx = 85;
	  section.data(33).dtTransOffset = 32;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_ezgc3bkrr3
	  section.data(34).logicalSrcIdx = 86;
	  section.data(34).dtTransOffset = 33;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_nyb31epfxn
	  section.data(35).logicalSrcIdx = 87;
	  section.data(35).dtTransOffset = 34;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_btle0cpm4x
	  section.data(36).logicalSrcIdx = 88;
	  section.data(36).dtTransOffset = 35;
	
	  ;% lpyvnxj1h0.euler_rollAddressNumber_Value
	  section.data(37).logicalSrcIdx = 89;
	  section.data(37).dtTransOffset = 36;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_drd3xh54pp
	  section.data(38).logicalSrcIdx = 90;
	  section.data(38).dtTransOffset = 37;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_fzocaavlvm
	  section.data(39).logicalSrcIdx = 91;
	  section.data(39).dtTransOffset = 38;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_e2affnwmie
	  section.data(40).logicalSrcIdx = 92;
	  section.data(40).dtTransOffset = 39;
	
	  ;% lpyvnxj1h0.euler_pitchAddressNumber_Value
	  section.data(41).logicalSrcIdx = 93;
	  section.data(41).dtTransOffset = 40;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_plesh25z30
	  section.data(42).logicalSrcIdx = 94;
	  section.data(42).dtTransOffset = 41;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_h33j5qc3ne
	  section.data(43).logicalSrcIdx = 95;
	  section.data(43).dtTransOffset = 42;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_kdxbfhfw0b
	  section.data(44).logicalSrcIdx = 96;
	  section.data(44).dtTransOffset = 43;
	
	  ;% lpyvnxj1h0.gyr_xAddressNumber_Value
	  section.data(45).logicalSrcIdx = 97;
	  section.data(45).dtTransOffset = 44;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_kl0tghuisc
	  section.data(46).logicalSrcIdx = 98;
	  section.data(46).dtTransOffset = 45;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_iwvlwkpu45
	  section.data(47).logicalSrcIdx = 99;
	  section.data(47).dtTransOffset = 46;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_fhgabvhymz
	  section.data(48).logicalSrcIdx = 100;
	  section.data(48).dtTransOffset = 47;
	
	  ;% lpyvnxj1h0.acc_xAddressNumber_Value
	  section.data(49).logicalSrcIdx = 101;
	  section.data(49).dtTransOffset = 48;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_kbpezf5ohk
	  section.data(50).logicalSrcIdx = 102;
	  section.data(50).dtTransOffset = 49;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_evgu2dclcq
	  section.data(51).logicalSrcIdx = 103;
	  section.data(51).dtTransOffset = 50;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_ddfuos2pe2
	  section.data(52).logicalSrcIdx = 104;
	  section.data(52).dtTransOffset = 51;
	
	  ;% lpyvnxj1h0.gyr_yAddressNumber_Value
	  section.data(53).logicalSrcIdx = 105;
	  section.data(53).dtTransOffset = 52;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_fifsrtpkgo
	  section.data(54).logicalSrcIdx = 106;
	  section.data(54).dtTransOffset = 53;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_mfuu3zdpmt
	  section.data(55).logicalSrcIdx = 107;
	  section.data(55).dtTransOffset = 54;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_cehxtfqlkd
	  section.data(56).logicalSrcIdx = 108;
	  section.data(56).dtTransOffset = 55;
	
	  ;% lpyvnxj1h0.acc_yAddressNumber_Value
	  section.data(57).logicalSrcIdx = 109;
	  section.data(57).dtTransOffset = 56;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_kl4y2if24c
	  section.data(58).logicalSrcIdx = 110;
	  section.data(58).dtTransOffset = 57;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_gq42v2v5qb
	  section.data(59).logicalSrcIdx = 111;
	  section.data(59).dtTransOffset = 58;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_epzvrriq3n
	  section.data(60).logicalSrcIdx = 112;
	  section.data(60).dtTransOffset = 59;
	
	  ;% lpyvnxj1h0.gyr_zAddressNumber_Value
	  section.data(61).logicalSrcIdx = 113;
	  section.data(61).dtTransOffset = 60;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_f1cbafc0ik
	  section.data(62).logicalSrcIdx = 114;
	  section.data(62).dtTransOffset = 61;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_htj1cmvga1
	  section.data(63).logicalSrcIdx = 115;
	  section.data(63).dtTransOffset = 62;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_mh2nfvsd3a
	  section.data(64).logicalSrcIdx = 116;
	  section.data(64).dtTransOffset = 63;
	
	  ;% lpyvnxj1h0.acc_zAddressNumber_Value
	  section.data(65).logicalSrcIdx = 117;
	  section.data(65).dtTransOffset = 64;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_f1zwvnvjia
	  section.data(66).logicalSrcIdx = 118;
	  section.data(66).dtTransOffset = 65;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_evkzk2rntu
	  section.data(67).logicalSrcIdx = 119;
	  section.data(67).dtTransOffset = 66;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_ibtcgpyr5u
	  section.data(68).logicalSrcIdx = 120;
	  section.data(68).dtTransOffset = 67;
	
	  ;% lpyvnxj1h0.radio_throttleAddres_p4zq4o0hs0
	  section.data(69).logicalSrcIdx = 121;
	  section.data(69).dtTransOffset = 68;
	
	  ;% lpyvnxj1h0.uint8_t1_Value_arnxnrh2dy
	  section.data(70).logicalSrcIdx = 122;
	  section.data(70).dtTransOffset = 69;
	
	  ;% lpyvnxj1h0.uint8_t2_Value_khle0v1wh1
	  section.data(71).logicalSrcIdx = 123;
	  section.data(71).dtTransOffset = 70;
	
	  ;% lpyvnxj1h0.uint8_t3_Value_dcn3mnclgo
	  section.data(72).logicalSrcIdx = 124;
	  section.data(72).dtTransOffset = 71;
	
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
    nTotSects     = 47;
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
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.i4n44eh5n1
	  section.data(1).logicalSrcIdx = 6;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 27;
      section.data(27)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.mlropoudai
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ngwkuxrl30h.kfxvly0eje
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ngwkuxrl30h.g43odph4ra
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% ngwkuxrl30h.ljzhvtf4ss
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% ngwkuxrl30h.nqkhzh0kna
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% ngwkuxrl30h.fsdssvakmh
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% ngwkuxrl30h.fq15qqczpj
	  section.data(7).logicalSrcIdx = 7;
	  section.data(7).dtTransOffset = 6;
	
	  ;% ngwkuxrl30h.kohcr3xatr
	  section.data(8).logicalSrcIdx = 8;
	  section.data(8).dtTransOffset = 7;
	
	  ;% ngwkuxrl30h.im3abezydx
	  section.data(9).logicalSrcIdx = 9;
	  section.data(9).dtTransOffset = 8;
	
	  ;% ngwkuxrl30h.mzbtbliauf
	  section.data(10).logicalSrcIdx = 10;
	  section.data(10).dtTransOffset = 9;
	
	  ;% ngwkuxrl30h.gdwa1fq2nn
	  section.data(11).logicalSrcIdx = 11;
	  section.data(11).dtTransOffset = 10;
	
	  ;% ngwkuxrl30h.pkbnespg5v
	  section.data(12).logicalSrcIdx = 12;
	  section.data(12).dtTransOffset = 11;
	
	  ;% ngwkuxrl30h.mgsnj3fpho
	  section.data(13).logicalSrcIdx = 13;
	  section.data(13).dtTransOffset = 12;
	
	  ;% ngwkuxrl30h.okhvmzamkd
	  section.data(14).logicalSrcIdx = 14;
	  section.data(14).dtTransOffset = 13;
	
	  ;% ngwkuxrl30h.mfppywas52
	  section.data(15).logicalSrcIdx = 15;
	  section.data(15).dtTransOffset = 14;
	
	  ;% ngwkuxrl30h.ivrg2lbm4e
	  section.data(16).logicalSrcIdx = 16;
	  section.data(16).dtTransOffset = 15;
	
	  ;% ngwkuxrl30h.h515zhgsym
	  section.data(17).logicalSrcIdx = 17;
	  section.data(17).dtTransOffset = 16;
	
	  ;% ngwkuxrl30h.j4udxgysdk
	  section.data(18).logicalSrcIdx = 18;
	  section.data(18).dtTransOffset = 17;
	
	  ;% ngwkuxrl30h.ketb32uv1l
	  section.data(19).logicalSrcIdx = 19;
	  section.data(19).dtTransOffset = 18;
	
	  ;% ngwkuxrl30h.bzkkj2huh1
	  section.data(20).logicalSrcIdx = 20;
	  section.data(20).dtTransOffset = 19;
	
	  ;% ngwkuxrl30h.j4dnhufclr
	  section.data(21).logicalSrcIdx = 21;
	  section.data(21).dtTransOffset = 20;
	
	  ;% ngwkuxrl30h.hg32kasdl0
	  section.data(22).logicalSrcIdx = 22;
	  section.data(22).dtTransOffset = 21;
	
	  ;% ngwkuxrl30h.psvc2eqbhj
	  section.data(23).logicalSrcIdx = 23;
	  section.data(23).dtTransOffset = 22;
	
	  ;% ngwkuxrl30h.gbeq1twthq
	  section.data(24).logicalSrcIdx = 24;
	  section.data(24).dtTransOffset = 23;
	
	  ;% ngwkuxrl30h.igfogpicfk
	  section.data(25).logicalSrcIdx = 25;
	  section.data(25).dtTransOffset = 24;
	
	  ;% ngwkuxrl30h.hogkymthgv
	  section.data(26).logicalSrcIdx = 26;
	  section.data(26).dtTransOffset = 25;
	
	  ;% ngwkuxrl30h.f2vkc5n0n2
	  section.data(27).logicalSrcIdx = 27;
	  section.data(27).dtTransOffset = 26;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.messmrodiv
	  section.data(1).logicalSrcIdx = 28;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ngwkuxrl30h.ivawlyhryp
	  section.data(2).logicalSrcIdx = 29;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ngwkuxrl30h.dcagfssoah
	  section.data(3).logicalSrcIdx = 30;
	  section.data(3).dtTransOffset = 2;
	
	  ;% ngwkuxrl30h.koslpbokub
	  section.data(4).logicalSrcIdx = 31;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 9;
      section.data(9)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.cuc3vlyflu
	  section.data(1).logicalSrcIdx = 32;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ngwkuxrl30h.nw2hrss5h3
	  section.data(2).logicalSrcIdx = 33;
	  section.data(2).dtTransOffset = 2;
	
	  ;% ngwkuxrl30h.pgly4qmgn3
	  section.data(3).logicalSrcIdx = 34;
	  section.data(3).dtTransOffset = 3;
	
	  ;% ngwkuxrl30h.fybbvb01f2
	  section.data(4).logicalSrcIdx = 35;
	  section.data(4).dtTransOffset = 4;
	
	  ;% ngwkuxrl30h.g4w3rr541p
	  section.data(5).logicalSrcIdx = 36;
	  section.data(5).dtTransOffset = 5;
	
	  ;% ngwkuxrl30h.dpfdvwcuis
	  section.data(6).logicalSrcIdx = 37;
	  section.data(6).dtTransOffset = 6;
	
	  ;% ngwkuxrl30h.ppwny0hklo
	  section.data(7).logicalSrcIdx = 38;
	  section.data(7).dtTransOffset = 7;
	
	  ;% ngwkuxrl30h.oikbc2tzwm
	  section.data(8).logicalSrcIdx = 39;
	  section.data(8).dtTransOffset = 8;
	
	  ;% ngwkuxrl30h.k45tdhcnex
	  section.data(9).logicalSrcIdx = 40;
	  section.data(9).dtTransOffset = 9;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.ktvi2ikeov
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ngwkuxrl30h.e2wxhptxhn
	  section.data(2).logicalSrcIdx = 42;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ngwkuxrl30h.lmr5rqw5oz
	  section.data(3).logicalSrcIdx = 43;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.flvni5slx2.odscltsmn5
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.azxipu5sgk.gp42lp0gag
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.hpqqzjscri.gx3mwplptf
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.hehgbywmbk.gx3mwplptf
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.jeud2kypfr.gx3mwplptf
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.mczq41vdx2.gx3mwplptf
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.huu2jah4h0.gx3mwplptf
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.nn33v5amct.gx3mwplptf
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.ea3ykdbsao.gx3mwplptf
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.kpqphaekhl.gx3mwplptf
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.ejxpdk0tuu.gx3mwplptf
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.a3v44rntro.gx3mwplptf
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.ezwg33fmes.gx3mwplptf
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.j2bl4h4opr.gx3mwplptf
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.jpqk2g5ami.gx3mwplptf
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.n25qs0tn4t.gx3mwplptf
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.jglicahs4f.gx3mwplptf
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.dqhh5t5yq5.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.dvpqmjqb1n.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.jtyclzua3t.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.baivdu1wt0.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.hlybsl2cgn.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.jnpdmcahon.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.fum3atfoqu.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.e5v5bx013w.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.psfrn3qsk0.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.fxsfzp40io.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.fzjme0r5v4.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 71;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.bqtw5k3h1l.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 72;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(34) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.epdw1uru12.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 73;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(35) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.c4szrdzfjz.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 74;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(36) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.k54btlvaqyow.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 75;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(37) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.ar5cbxx2hl.odscltsmn5
	  section.data(1).logicalSrcIdx = 76;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(38) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.bal55qvwsc.gp42lp0gag
	  section.data(1).logicalSrcIdx = 77;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(39) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.elsky2r1vj.odscltsmn5
	  section.data(1).logicalSrcIdx = 78;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(40) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.a2f5qubcpl.gp42lp0gag
	  section.data(1).logicalSrcIdx = 79;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(41) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.pqxcvbr5ry.odscltsmn5
	  section.data(1).logicalSrcIdx = 80;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(42) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.deptgugkwo.gp42lp0gag
	  section.data(1).logicalSrcIdx = 81;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(43) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.agyfdwk13er.odscltsmn5
	  section.data(1).logicalSrcIdx = 82;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(44) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.lc1x3ygm3by.gp42lp0gag
	  section.data(1).logicalSrcIdx = 83;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(45) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.c22dvgq4m2l.gx3mwplptf
	  section.data(1).logicalSrcIdx = 84;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(46) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ngwkuxrl30h.k54btlvaqyo.j2fnq4vpty
	  section.data(1).logicalSrcIdx = 85;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(47) = section;
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
    sectIdxOffset = 47;
    
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
      
	  ;% cg3ibeewf53.d3faz5e3ri
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% cg3ibeewf53.bhslxkomyj
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% cg3ibeewf53.jmugpuxqkz
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% cg3ibeewf53.atykzpwf1x
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% cg3ibeewf53.obnhmjubqg
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% cg3ibeewf53.nen0ajecpn
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% cg3ibeewf53.aflisttmw0
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% cg3ibeewf53.cdsj0q2nn0
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% cg3ibeewf53.h3ol2nkrhq
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% cg3ibeewf53.mdp4avueqw
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% cg3ibeewf53.ciwdrlnimd
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% cg3ibeewf53.hjzur5wtw2
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% cg3ibeewf53.pceo33fhce
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 21;
      section.data(21)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.lw0sxgglzt.LoggedData
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
	  ;% cg3ibeewf53.nnjq5qwmqi.LoggedData
	  section.data(2).logicalSrcIdx = 14;
	  section.data(2).dtTransOffset = 1;
	
	  ;% cg3ibeewf53.bx54yobmmu.LoggedData
	  section.data(3).logicalSrcIdx = 15;
	  section.data(3).dtTransOffset = 2;
	
	  ;% cg3ibeewf53.dx2emldhn1.LoggedData
	  section.data(4).logicalSrcIdx = 16;
	  section.data(4).dtTransOffset = 4;
	
	  ;% cg3ibeewf53.hsd4bamyzm.LoggedData
	  section.data(5).logicalSrcIdx = 17;
	  section.data(5).dtTransOffset = 6;
	
	  ;% cg3ibeewf53.crjqh1hgpk.LoggedData
	  section.data(6).logicalSrcIdx = 18;
	  section.data(6).dtTransOffset = 8;
	
	  ;% cg3ibeewf53.lqvmebfok5.LoggedData
	  section.data(7).logicalSrcIdx = 19;
	  section.data(7).dtTransOffset = 10;
	
	  ;% cg3ibeewf53.b20pkyqe3c.LoggedData
	  section.data(8).logicalSrcIdx = 20;
	  section.data(8).dtTransOffset = 12;
	
	  ;% cg3ibeewf53.kxdhzxidjt.LoggedData
	  section.data(9).logicalSrcIdx = 21;
	  section.data(9).dtTransOffset = 13;
	
	  ;% cg3ibeewf53.hicw2geed0.LoggedData
	  section.data(10).logicalSrcIdx = 22;
	  section.data(10).dtTransOffset = 14;
	
	  ;% cg3ibeewf53.fmlrmbmpal.LoggedData
	  section.data(11).logicalSrcIdx = 23;
	  section.data(11).dtTransOffset = 15;
	
	  ;% cg3ibeewf53.cgym5ktizm.LoggedData
	  section.data(12).logicalSrcIdx = 24;
	  section.data(12).dtTransOffset = 16;
	
	  ;% cg3ibeewf53.l4au003mwf.LoggedData
	  section.data(13).logicalSrcIdx = 25;
	  section.data(13).dtTransOffset = 17;
	
	  ;% cg3ibeewf53.l5ohllsrgc.LoggedData
	  section.data(14).logicalSrcIdx = 26;
	  section.data(14).dtTransOffset = 21;
	
	  ;% cg3ibeewf53.pmvvnbwnc1.LoggedData
	  section.data(15).logicalSrcIdx = 27;
	  section.data(15).dtTransOffset = 24;
	
	  ;% cg3ibeewf53.m0na5x4e3o.LoggedData
	  section.data(16).logicalSrcIdx = 28;
	  section.data(16).dtTransOffset = 25;
	
	  ;% cg3ibeewf53.allshcup52.LoggedData
	  section.data(17).logicalSrcIdx = 29;
	  section.data(17).dtTransOffset = 26;
	
	  ;% cg3ibeewf53.h1dhvwbqik.LoggedData
	  section.data(18).logicalSrcIdx = 30;
	  section.data(18).dtTransOffset = 27;
	
	  ;% cg3ibeewf53.c5lnaptkos.LoggedData
	  section.data(19).logicalSrcIdx = 31;
	  section.data(19).dtTransOffset = 29;
	
	  ;% cg3ibeewf53.cb50swcerk.LoggedData
	  section.data(20).logicalSrcIdx = 32;
	  section.data(20).dtTransOffset = 31;
	
	  ;% cg3ibeewf53.oc3zrdh0rh.LoggedData
	  section.data(21).logicalSrcIdx = 33;
	  section.data(21).dtTransOffset = 32;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.oryxrnwgxb
	  section.data(1).logicalSrcIdx = 34;
	  section.data(1).dtTransOffset = 0;
	
	  ;% cg3ibeewf53.p12jjk5f2x
	  section.data(2).logicalSrcIdx = 35;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.bz3uzbijgi
	  section.data(1).logicalSrcIdx = 36;
	  section.data(1).dtTransOffset = 0;
	
	  ;% cg3ibeewf53.j3yn12fugu
	  section.data(2).logicalSrcIdx = 37;
	  section.data(2).dtTransOffset = 1;
	
	  ;% cg3ibeewf53.lf04negfii
	  section.data(3).logicalSrcIdx = 38;
	  section.data(3).dtTransOffset = 2;
	
	  ;% cg3ibeewf53.clyd31xxxy
	  section.data(4).logicalSrcIdx = 39;
	  section.data(4).dtTransOffset = 3;
	
	  ;% cg3ibeewf53.oagyvyu5pe
	  section.data(5).logicalSrcIdx = 40;
	  section.data(5).dtTransOffset = 4;
	
	  ;% cg3ibeewf53.h5t42qiqms
	  section.data(6).logicalSrcIdx = 41;
	  section.data(6).dtTransOffset = 5;
	
	  ;% cg3ibeewf53.p1vf31jtz3
	  section.data(7).logicalSrcIdx = 42;
	  section.data(7).dtTransOffset = 6;
	
	  ;% cg3ibeewf53.cq42nbs2ig
	  section.data(8).logicalSrcIdx = 43;
	  section.data(8).dtTransOffset = 7;
	
	  ;% cg3ibeewf53.m1fcxth45i
	  section.data(9).logicalSrcIdx = 44;
	  section.data(9).dtTransOffset = 8;
	
	  ;% cg3ibeewf53.ow3qkcnmhz
	  section.data(10).logicalSrcIdx = 45;
	  section.data(10).dtTransOffset = 9;
	
	  ;% cg3ibeewf53.egx1trrxvu
	  section.data(11).logicalSrcIdx = 46;
	  section.data(11).dtTransOffset = 10;
	
	  ;% cg3ibeewf53.lnhxtl3k4f
	  section.data(12).logicalSrcIdx = 47;
	  section.data(12).dtTransOffset = 11;
	
	  ;% cg3ibeewf53.jno341jjgf
	  section.data(13).logicalSrcIdx = 48;
	  section.data(13).dtTransOffset = 12;
	
	  ;% cg3ibeewf53.i1rjduyhcx
	  section.data(14).logicalSrcIdx = 49;
	  section.data(14).dtTransOffset = 13;
	
	  ;% cg3ibeewf53.dogxnk2xyh
	  section.data(15).logicalSrcIdx = 50;
	  section.data(15).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.dqhh5t5yq5.jkphomqarc
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.dqhh5t5yq5.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.dvpqmjqb1n.jkphomqarc
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.dvpqmjqb1n.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.jtyclzua3t.jkphomqarc
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.jtyclzua3t.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.baivdu1wt0.jkphomqarc
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.baivdu1wt0.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.hlybsl2cgn.jkphomqarc
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.hlybsl2cgn.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.jnpdmcahon.jkphomqarc
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.jnpdmcahon.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.fum3atfoqu.jkphomqarc
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.fum3atfoqu.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.e5v5bx013w.jkphomqarc
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.e5v5bx013w.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.psfrn3qsk0.jkphomqarc
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.psfrn3qsk0.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.fxsfzp40io.jkphomqarc
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.fxsfzp40io.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.fzjme0r5v4.jkphomqarc
	  section.data(1).logicalSrcIdx = 71;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.fzjme0r5v4.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 72;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.bqtw5k3h1l.jkphomqarc
	  section.data(1).logicalSrcIdx = 73;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.bqtw5k3h1l.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 74;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.epdw1uru12.jkphomqarc
	  section.data(1).logicalSrcIdx = 75;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.epdw1uru12.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 76;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.c4szrdzfjz.jkphomqarc
	  section.data(1).logicalSrcIdx = 77;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.c4szrdzfjz.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 78;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.k54btlvaqyow.jkphomqarc
	  section.data(1).logicalSrcIdx = 79;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.k54btlvaqyow.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 80;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(34) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.k54btlvaqyo.jkphomqarc
	  section.data(1).logicalSrcIdx = 81;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(35) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% cg3ibeewf53.k54btlvaqyo.dfbzqr4cle
	  section.data(1).logicalSrcIdx = 82;
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


  targMap.checksum0 = 3079871989;
  targMap.checksum1 = 2657729139;
  targMap.checksum2 = 2665504348;
  targMap.checksum3 = 1243080108;

