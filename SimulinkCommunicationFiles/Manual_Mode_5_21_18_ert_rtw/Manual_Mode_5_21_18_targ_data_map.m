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
    ;% Auto data (of4bvhuzsv)
    ;%
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% of4bvhuzsv.FixPtBitwiseOperator1_BitMask
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_allykckzh4
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_nohtoqfgpu
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_p5jtkki0ka
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_biy0ofdraq
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_jz4ils4mdl
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_b2q5a3dmet
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_cwn0e2kvrc
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_prlgl5frdt
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_hxkxzaxnmm
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_eywjf2cgmz
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_ndvnypechq
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_mooxnprtk3
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_cfmyhdyzs4
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_b2ufezlyo5
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 25;
      section.data(25)  = dumData; %prealloc
      
	  ;% of4bvhuzsv.bitsmNm_Gain
	  section.data(1).logicalSrcIdx = 15;
	  section.data(1).dtTransOffset = 0;
	
	  ;% of4bvhuzsv.ConstantOffsetFromRadio_Value
	  section.data(2).logicalSrcIdx = 16;
	  section.data(2).dtTransOffset = 1;
	
	  ;% of4bvhuzsv.SmallDeadZoneForSafety_Start
	  section.data(3).logicalSrcIdx = 17;
	  section.data(3).dtTransOffset = 2;
	
	  ;% of4bvhuzsv.SmallDeadZoneForSafety_End
	  section.data(4).logicalSrcIdx = 18;
	  section.data(4).dtTransOffset = 3;
	
	  ;% of4bvhuzsv.bitsmNm_Gain_a0guxcsc1n
	  section.data(5).logicalSrcIdx = 19;
	  section.data(5).dtTransOffset = 4;
	
	  ;% of4bvhuzsv.bitsmNm_Gain_gvhph3akut
	  section.data(6).logicalSrcIdx = 20;
	  section.data(6).dtTransOffset = 5;
	
	  ;% of4bvhuzsv.bitsmNm_Gain_j3ysscodce
	  section.data(7).logicalSrcIdx = 21;
	  section.data(7).dtTransOffset = 6;
	
	  ;% of4bvhuzsv.bitsmNm_Gain_cjk4fymxdf
	  section.data(8).logicalSrcIdx = 22;
	  section.data(8).dtTransOffset = 7;
	
	  ;% of4bvhuzsv.Compensatesfordirectionofspinwa
	  section.data(9).logicalSrcIdx = 23;
	  section.data(9).dtTransOffset = 8;
	
	  ;% of4bvhuzsv.Compensatesfordirect_cf4nxnhxs5
	  section.data(10).logicalSrcIdx = 24;
	  section.data(10).dtTransOffset = 9;
	
	  ;% of4bvhuzsv.AccelerationInttoDoubleScaleFac
	  section.data(11).logicalSrcIdx = 25;
	  section.data(11).dtTransOffset = 10;
	
	  ;% of4bvhuzsv.GyroscopeInttoDoubleScaleFactor
	  section.data(12).logicalSrcIdx = 26;
	  section.data(12).dtTransOffset = 11;
	
	  ;% of4bvhuzsv.AccelerationInttoDou_e1y3s5ygre
	  section.data(13).logicalSrcIdx = 27;
	  section.data(13).dtTransOffset = 12;
	
	  ;% of4bvhuzsv.GyroscopeInttoDouble_hxh3ovbjsw
	  section.data(14).logicalSrcIdx = 28;
	  section.data(14).dtTransOffset = 13;
	
	  ;% of4bvhuzsv.AccelerationInttoDou_agzu2jmipw
	  section.data(15).logicalSrcIdx = 29;
	  section.data(15).dtTransOffset = 14;
	
	  ;% of4bvhuzsv.GyroscopeInttoDouble_cgdkqmhmkx
	  section.data(16).logicalSrcIdx = 30;
	  section.data(16).dtTransOffset = 15;
	
	  ;% of4bvhuzsv.EulerInttoDoubleScaleFactor_Gai
	  section.data(17).logicalSrcIdx = 31;
	  section.data(17).dtTransOffset = 16;
	
	  ;% of4bvhuzsv.EulerInttoDoubleScal_lghdi0rztz
	  section.data(18).logicalSrcIdx = 32;
	  section.data(18).dtTransOffset = 17;
	
	  ;% of4bvhuzsv.EulerInttoDoubleScal_kbgtqhxbzr
	  section.data(19).logicalSrcIdx = 33;
	  section.data(19).dtTransOffset = 18;
	
	  ;% of4bvhuzsv.Constant1_Value
	  section.data(20).logicalSrcIdx = 34;
	  section.data(20).dtTransOffset = 19;
	
	  ;% of4bvhuzsv.Constant_Value
	  section.data(21).logicalSrcIdx = 35;
	  section.data(21).dtTransOffset = 20;
	
	  ;% of4bvhuzsv.Constant2_Value
	  section.data(22).logicalSrcIdx = 36;
	  section.data(22).dtTransOffset = 21;
	
	  ;% of4bvhuzsv.Constant4_Value
	  section.data(23).logicalSrcIdx = 37;
	  section.data(23).dtTransOffset = 22;
	
	  ;% of4bvhuzsv.Constant3_Value
	  section.data(24).logicalSrcIdx = 38;
	  section.data(24).dtTransOffset = 23;
	
	  ;% of4bvhuzsv.Constant5_Value
	  section.data(25).logicalSrcIdx = 39;
	  section.data(25).dtTransOffset = 24;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 68;
      section.data(68)  = dumData; %prealloc
      
	  ;% of4bvhuzsv.euler_headingAddressNumber_Valu
	  section.data(1).logicalSrcIdx = 40;
	  section.data(1).dtTransOffset = 0;
	
	  ;% of4bvhuzsv.uint8_t1_Value
	  section.data(2).logicalSrcIdx = 41;
	  section.data(2).dtTransOffset = 1;
	
	  ;% of4bvhuzsv.uint8_t2_Value
	  section.data(3).logicalSrcIdx = 42;
	  section.data(3).dtTransOffset = 2;
	
	  ;% of4bvhuzsv.uint8_t3_Value
	  section.data(4).logicalSrcIdx = 43;
	  section.data(4).dtTransOffset = 3;
	
	  ;% of4bvhuzsv.euler_rollAddressNumber_Value
	  section.data(5).logicalSrcIdx = 44;
	  section.data(5).dtTransOffset = 4;
	
	  ;% of4bvhuzsv.uint8_t1_Value_fajil5otqc
	  section.data(6).logicalSrcIdx = 45;
	  section.data(6).dtTransOffset = 5;
	
	  ;% of4bvhuzsv.uint8_t2_Value_cmbfgpgjkm
	  section.data(7).logicalSrcIdx = 46;
	  section.data(7).dtTransOffset = 6;
	
	  ;% of4bvhuzsv.uint8_t3_Value_auyg3hmfwl
	  section.data(8).logicalSrcIdx = 47;
	  section.data(8).dtTransOffset = 7;
	
	  ;% of4bvhuzsv.euler_pitchAddressNumber_Value
	  section.data(9).logicalSrcIdx = 48;
	  section.data(9).dtTransOffset = 8;
	
	  ;% of4bvhuzsv.uint8_t1_Value_h32gtcaucs
	  section.data(10).logicalSrcIdx = 49;
	  section.data(10).dtTransOffset = 9;
	
	  ;% of4bvhuzsv.uint8_t2_Value_debteyg1yt
	  section.data(11).logicalSrcIdx = 50;
	  section.data(11).dtTransOffset = 10;
	
	  ;% of4bvhuzsv.uint8_t3_Value_ps1cg0o1ke
	  section.data(12).logicalSrcIdx = 51;
	  section.data(12).dtTransOffset = 11;
	
	  ;% of4bvhuzsv.gyr_xAddressNumber_Value
	  section.data(13).logicalSrcIdx = 52;
	  section.data(13).dtTransOffset = 12;
	
	  ;% of4bvhuzsv.uint8_t1_Value_ekv5t2hox1
	  section.data(14).logicalSrcIdx = 53;
	  section.data(14).dtTransOffset = 13;
	
	  ;% of4bvhuzsv.uint8_t2_Value_onrochiyev
	  section.data(15).logicalSrcIdx = 54;
	  section.data(15).dtTransOffset = 14;
	
	  ;% of4bvhuzsv.uint8_t3_Value_nswylz10in
	  section.data(16).logicalSrcIdx = 55;
	  section.data(16).dtTransOffset = 15;
	
	  ;% of4bvhuzsv.acc_xAddressNumber_Value
	  section.data(17).logicalSrcIdx = 56;
	  section.data(17).dtTransOffset = 16;
	
	  ;% of4bvhuzsv.uint8_t1_Value_enchdjtvcn
	  section.data(18).logicalSrcIdx = 57;
	  section.data(18).dtTransOffset = 17;
	
	  ;% of4bvhuzsv.uint8_t2_Value_mfpa3gircm
	  section.data(19).logicalSrcIdx = 58;
	  section.data(19).dtTransOffset = 18;
	
	  ;% of4bvhuzsv.uint8_t3_Value_n1mqsrpxk5
	  section.data(20).logicalSrcIdx = 59;
	  section.data(20).dtTransOffset = 19;
	
	  ;% of4bvhuzsv.gyr_yAddressNumber_Value
	  section.data(21).logicalSrcIdx = 60;
	  section.data(21).dtTransOffset = 20;
	
	  ;% of4bvhuzsv.uint8_t1_Value_iyqpxgl2kj
	  section.data(22).logicalSrcIdx = 61;
	  section.data(22).dtTransOffset = 21;
	
	  ;% of4bvhuzsv.uint8_t2_Value_c5rq0ubefu
	  section.data(23).logicalSrcIdx = 62;
	  section.data(23).dtTransOffset = 22;
	
	  ;% of4bvhuzsv.uint8_t3_Value_ptisq55ei5
	  section.data(24).logicalSrcIdx = 63;
	  section.data(24).dtTransOffset = 23;
	
	  ;% of4bvhuzsv.acc_yAddressNumber_Value
	  section.data(25).logicalSrcIdx = 64;
	  section.data(25).dtTransOffset = 24;
	
	  ;% of4bvhuzsv.uint8_t1_Value_dca1g4fbhc
	  section.data(26).logicalSrcIdx = 65;
	  section.data(26).dtTransOffset = 25;
	
	  ;% of4bvhuzsv.uint8_t2_Value_bkbxylz1b1
	  section.data(27).logicalSrcIdx = 66;
	  section.data(27).dtTransOffset = 26;
	
	  ;% of4bvhuzsv.uint8_t3_Value_eeh12bmm2g
	  section.data(28).logicalSrcIdx = 67;
	  section.data(28).dtTransOffset = 27;
	
	  ;% of4bvhuzsv.gyr_zAddressNumber_Value
	  section.data(29).logicalSrcIdx = 68;
	  section.data(29).dtTransOffset = 28;
	
	  ;% of4bvhuzsv.uint8_t1_Value_h43fbsnkpg
	  section.data(30).logicalSrcIdx = 69;
	  section.data(30).dtTransOffset = 29;
	
	  ;% of4bvhuzsv.uint8_t2_Value_eafiiqbkgq
	  section.data(31).logicalSrcIdx = 70;
	  section.data(31).dtTransOffset = 30;
	
	  ;% of4bvhuzsv.uint8_t3_Value_oj5my2hqlu
	  section.data(32).logicalSrcIdx = 71;
	  section.data(32).dtTransOffset = 31;
	
	  ;% of4bvhuzsv.acc_zAddressNumber_Value
	  section.data(33).logicalSrcIdx = 72;
	  section.data(33).dtTransOffset = 32;
	
	  ;% of4bvhuzsv.uint8_t1_Value_p511kx5um5
	  section.data(34).logicalSrcIdx = 73;
	  section.data(34).dtTransOffset = 33;
	
	  ;% of4bvhuzsv.uint8_t2_Value_jivobjlhfb
	  section.data(35).logicalSrcIdx = 74;
	  section.data(35).dtTransOffset = 34;
	
	  ;% of4bvhuzsv.uint8_t3_Value_k1p4iqo3cv
	  section.data(36).logicalSrcIdx = 75;
	  section.data(36).dtTransOffset = 35;
	
	  ;% of4bvhuzsv.radio_throttleAddressNumber_Val
	  section.data(37).logicalSrcIdx = 76;
	  section.data(37).dtTransOffset = 36;
	
	  ;% of4bvhuzsv.uint8_t1_Value_pik4yifivl
	  section.data(38).logicalSrcIdx = 77;
	  section.data(38).dtTransOffset = 37;
	
	  ;% of4bvhuzsv.uint8_t2_Value_dagdlneepy
	  section.data(39).logicalSrcIdx = 78;
	  section.data(39).dtTransOffset = 38;
	
	  ;% of4bvhuzsv.uint8_t3_Value_iug04v4dnj
	  section.data(40).logicalSrcIdx = 79;
	  section.data(40).dtTransOffset = 39;
	
	  ;% of4bvhuzsv.radio_steeringAddressNumber_Val
	  section.data(41).logicalSrcIdx = 80;
	  section.data(41).dtTransOffset = 40;
	
	  ;% of4bvhuzsv.uint8_t1_Value_bdjao5j5m2
	  section.data(42).logicalSrcIdx = 81;
	  section.data(42).dtTransOffset = 41;
	
	  ;% of4bvhuzsv.uint8_t2_Value_nifxbdjnx1
	  section.data(43).logicalSrcIdx = 82;
	  section.data(43).dtTransOffset = 42;
	
	  ;% of4bvhuzsv.uint8_t3_Value_abz5y50h5c
	  section.data(44).logicalSrcIdx = 83;
	  section.data(44).dtTransOffset = 43;
	
	  ;% of4bvhuzsv.velocity_RRAddressNumber_Value
	  section.data(45).logicalSrcIdx = 84;
	  section.data(45).dtTransOffset = 44;
	
	  ;% of4bvhuzsv.uint8_t1_Value_fuqp2r2lsf
	  section.data(46).logicalSrcIdx = 85;
	  section.data(46).dtTransOffset = 45;
	
	  ;% of4bvhuzsv.uint8_t2_Value_mwf1trdjuc
	  section.data(47).logicalSrcIdx = 86;
	  section.data(47).dtTransOffset = 46;
	
	  ;% of4bvhuzsv.uint8_t3_Value_jgmgjfzdnx
	  section.data(48).logicalSrcIdx = 87;
	  section.data(48).dtTransOffset = 47;
	
	  ;% of4bvhuzsv.velocity_RLAddressNumber_Value
	  section.data(49).logicalSrcIdx = 88;
	  section.data(49).dtTransOffset = 48;
	
	  ;% of4bvhuzsv.uint8_t1_Value_gv23hz2t0a
	  section.data(50).logicalSrcIdx = 89;
	  section.data(50).dtTransOffset = 49;
	
	  ;% of4bvhuzsv.uint8_t2_Value_mx0w5a4tar
	  section.data(51).logicalSrcIdx = 90;
	  section.data(51).dtTransOffset = 50;
	
	  ;% of4bvhuzsv.uint8_t3_Value_pnjf4z32eo
	  section.data(52).logicalSrcIdx = 91;
	  section.data(52).dtTransOffset = 51;
	
	  ;% of4bvhuzsv.velocity_FRAddressNumber_Value
	  section.data(53).logicalSrcIdx = 92;
	  section.data(53).dtTransOffset = 52;
	
	  ;% of4bvhuzsv.uint8_t1_Value_gmoo3bwrgq
	  section.data(54).logicalSrcIdx = 93;
	  section.data(54).dtTransOffset = 53;
	
	  ;% of4bvhuzsv.uint8_t2_Value_eyohhuy2kp
	  section.data(55).logicalSrcIdx = 94;
	  section.data(55).dtTransOffset = 54;
	
	  ;% of4bvhuzsv.uint8_t3_Value_at31p5wsy3
	  section.data(56).logicalSrcIdx = 95;
	  section.data(56).dtTransOffset = 55;
	
	  ;% of4bvhuzsv.velocity_FLAddressNumber_Value
	  section.data(57).logicalSrcIdx = 96;
	  section.data(57).dtTransOffset = 56;
	
	  ;% of4bvhuzsv.uint8_t1_Value_lie2wyxwfp
	  section.data(58).logicalSrcIdx = 97;
	  section.data(58).dtTransOffset = 57;
	
	  ;% of4bvhuzsv.uint8_t2_Value_o0ude4bnkc
	  section.data(59).logicalSrcIdx = 98;
	  section.data(59).dtTransOffset = 58;
	
	  ;% of4bvhuzsv.uint8_t3_Value_j4q5aemuzl
	  section.data(60).logicalSrcIdx = 99;
	  section.data(60).dtTransOffset = 59;
	
	  ;% of4bvhuzsv.DeadSwitch_Value
	  section.data(61).logicalSrcIdx = 100;
	  section.data(61).dtTransOffset = 60;
	
	  ;% of4bvhuzsv.TakeData_Value
	  section.data(62).logicalSrcIdx = 101;
	  section.data(62).dtTransOffset = 61;
	
	  ;% of4bvhuzsv.ServoandRadioOn_Value
	  section.data(63).logicalSrcIdx = 102;
	  section.data(63).dtTransOffset = 62;
	
	  ;% of4bvhuzsv.MotorControllersOn_Value
	  section.data(64).logicalSrcIdx = 103;
	  section.data(64).dtTransOffset = 63;
	
	  ;% of4bvhuzsv.IMUReset_Value
	  section.data(65).logicalSrcIdx = 104;
	  section.data(65).dtTransOffset = 64;
	
	  ;% of4bvhuzsv.PrinttheregistermapontheTeensy_
	  section.data(66).logicalSrcIdx = 105;
	  section.data(66).dtTransOffset = 65;
	
	  ;% of4bvhuzsv.PrinttheimudataontheTeensy_Valu
	  section.data(67).logicalSrcIdx = 106;
	  section.data(67).dtTransOffset = 66;
	
	  ;% of4bvhuzsv.Printtheradiotranceiverdataonth
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
    ;% Auto data (egmb1woemnz)
    ;%
      section.nData     = 19;
      section.data(19)  = dumData; %prealloc
      
	  ;% egmb1woemnz.dizmaqw4wv
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% egmb1woemnz.ah1wccj0hb
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% egmb1woemnz.dtnqhcfefn
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% egmb1woemnz.h5dh40yo3n
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% egmb1woemnz.k4hkvupn1k
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% egmb1woemnz.lztf45yioo
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% egmb1woemnz.pg4zzzsbqz
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% egmb1woemnz.m4byydifw2
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% egmb1woemnz.ey0bfaq1yo
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% egmb1woemnz.l5tk2pl30a
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% egmb1woemnz.hiyccvgnmo
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% egmb1woemnz.iussxojxsb
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% egmb1woemnz.f11r3ojunv
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% egmb1woemnz.oer3bdzhcy
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% egmb1woemnz.mi01rugklb
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% egmb1woemnz.pagovnxicx
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% egmb1woemnz.dr5p33i3mz
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% egmb1woemnz.bhmqafjm1h
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% egmb1woemnz.hatil2gcfb
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% egmb1woemnz.ovbkjj5wlx
	  section.data(1).logicalSrcIdx = 19;
	  section.data(1).dtTransOffset = 0;
	
	  ;% egmb1woemnz.gq5x3msvik
	  section.data(2).logicalSrcIdx = 20;
	  section.data(2).dtTransOffset = 1;
	
	  ;% egmb1woemnz.oeyxzekjqt
	  section.data(3).logicalSrcIdx = 21;
	  section.data(3).dtTransOffset = 2;
	
	  ;% egmb1woemnz.dfyxyn0u3v
	  section.data(4).logicalSrcIdx = 22;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% egmb1woemnz.dasom0iuc4
	  section.data(1).logicalSrcIdx = 23;
	  section.data(1).dtTransOffset = 0;
	
	  ;% egmb1woemnz.orbydnpnuc
	  section.data(2).logicalSrcIdx = 24;
	  section.data(2).dtTransOffset = 1;
	
	  ;% egmb1woemnz.b0gf0kpizg
	  section.data(3).logicalSrcIdx = 25;
	  section.data(3).dtTransOffset = 2;
	
	  ;% egmb1woemnz.ald455nrar
	  section.data(4).logicalSrcIdx = 26;
	  section.data(4).dtTransOffset = 3;
	
	  ;% egmb1woemnz.minzuf0qnk
	  section.data(5).logicalSrcIdx = 27;
	  section.data(5).dtTransOffset = 4;
	
	  ;% egmb1woemnz.m10uyypppj
	  section.data(6).logicalSrcIdx = 28;
	  section.data(6).dtTransOffset = 5;
	
	  ;% egmb1woemnz.ao5unspa12
	  section.data(7).logicalSrcIdx = 29;
	  section.data(7).dtTransOffset = 6;
	
	  ;% egmb1woemnz.olxdp2jbgt
	  section.data(8).logicalSrcIdx = 30;
	  section.data(8).dtTransOffset = 7;
	
	  ;% egmb1woemnz.mzrcel25aj
	  section.data(9).logicalSrcIdx = 31;
	  section.data(9).dtTransOffset = 8;
	
	  ;% egmb1woemnz.efbsdn54ab
	  section.data(10).logicalSrcIdx = 32;
	  section.data(10).dtTransOffset = 10;
	
	  ;% egmb1woemnz.fzdpsrqgns
	  section.data(11).logicalSrcIdx = 33;
	  section.data(11).dtTransOffset = 12;
	
	  ;% egmb1woemnz.jghajepyfr
	  section.data(12).logicalSrcIdx = 34;
	  section.data(12).dtTransOffset = 14;
	
	  ;% egmb1woemnz.cinlx0zlh0
	  section.data(13).logicalSrcIdx = 35;
	  section.data(13).dtTransOffset = 16;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.hjusqb5zfc.nnkxqw3vsj
	  section.data(1).logicalSrcIdx = 36;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.oi1mzppqxr.nnkxqw3vsj
	  section.data(1).logicalSrcIdx = 37;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.gv4rvzzoqw.nnkxqw3vsj
	  section.data(1).logicalSrcIdx = 38;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.e5ydgeoc1o.nnkxqw3vsj
	  section.data(1).logicalSrcIdx = 39;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.kds31ao13x.il54yk5vh3
	  section.data(1).logicalSrcIdx = 40;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.lfjd5omifu.aejrhql1to
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.pw4fqo1enu.il54yk5vh3
	  section.data(1).logicalSrcIdx = 42;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.bewanmvt2d.aejrhql1to
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.lgpqjgcdpf.il54yk5vh3
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.lzpastgvn4.aejrhql1to
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.hsznc4jqpx.il54yk5vh3
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.l1j3qezpxj.aejrhql1to
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.fduyubsxisk.il54yk5vh3
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.lcxkjccy3rs.aejrhql1to
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.gmzvfkjh02.nnkxqw3vsj
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.ct4m5n0ngd.nnkxqw3vsj
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.bf4m1g0p2g.nnkxqw3vsj
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.o35g5y1zt2.nnkxqw3vsj
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.pzctjtbusa.nnkxqw3vsj
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.hih1dqze0f.nnkxqw3vsj
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.cdke4qxg4w.nnkxqw3vsj
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.bdopsdcvhn.nnkxqw3vsj
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.abuavkhwpo.nnkxqw3vsj
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.hyi0oor530.nnkxqw3vsj
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.grlqnuabpud.nnkxqw3vsj
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.jjwbdm32dt.eidj4voigx
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.ap5o1ljg5p.eidj4voigx
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.ntpnjgaxbk.eidj4voigx
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.ltp5v1qb5p.eidj4voigx
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.dhd2bo1xvw.eidj4voigx
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.jvot4d0aks.eidj4voigx
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(34) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.addnvjrs50.eidj4voigx
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(35) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.bmuonaufob.eidj4voigx
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(36) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.dy5xffgu1e.eidj4voigx
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(37) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.jei05f3f2n.eidj4voigx
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(38) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.c4w4mthusc.eidj4voigx
	  section.data(1).logicalSrcIdx = 71;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(39) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.c4ks1ni02r.eidj4voigx
	  section.data(1).logicalSrcIdx = 72;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(40) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.fzox2unuby.eidj4voigx
	  section.data(1).logicalSrcIdx = 73;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(41) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.dm5drkuaxy.eidj4voigx
	  section.data(1).logicalSrcIdx = 74;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(42) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.c3zx4oz2izh.eidj4voigx
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
    ;% Auto data (khgsjmcu2zh)
    ;%
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.kst1bghm0u
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% khgsjmcu2zh.m5gpu04pbi
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% khgsjmcu2zh.eurzswxv10
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% khgsjmcu2zh.oblucujwrj
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% khgsjmcu2zh.iy2ycucml2
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% khgsjmcu2zh.kpxptlgulj
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% khgsjmcu2zh.kpi0me4fid
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% khgsjmcu2zh.ezupqoky5o
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% khgsjmcu2zh.fadgrf3krt
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% khgsjmcu2zh.h0igzngwjk
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% khgsjmcu2zh.o5aop53kjy
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% khgsjmcu2zh.edionmzsrl
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% khgsjmcu2zh.mncixck0dm
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ekz5ohvfzj.LoggedData
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
	  ;% khgsjmcu2zh.jd343gxwrq.LoggedData
	  section.data(2).logicalSrcIdx = 14;
	  section.data(2).dtTransOffset = 1;
	
	  ;% khgsjmcu2zh.jazheukumr.LoggedData
	  section.data(3).logicalSrcIdx = 15;
	  section.data(3).dtTransOffset = 2;
	
	  ;% khgsjmcu2zh.pat0uqaepq.LoggedData
	  section.data(4).logicalSrcIdx = 16;
	  section.data(4).dtTransOffset = 3;
	
	  ;% khgsjmcu2zh.pvjcjiv2zv.LoggedData
	  section.data(5).logicalSrcIdx = 17;
	  section.data(5).dtTransOffset = 4;
	
	  ;% khgsjmcu2zh.brdv3wfywn.LoggedData
	  section.data(6).logicalSrcIdx = 18;
	  section.data(6).dtTransOffset = 6;
	
	  ;% khgsjmcu2zh.euyjfovthx.LoggedData
	  section.data(7).logicalSrcIdx = 19;
	  section.data(7).dtTransOffset = 10;
	
	  ;% khgsjmcu2zh.j4vqnawqis.LoggedData
	  section.data(8).logicalSrcIdx = 20;
	  section.data(8).dtTransOffset = 12;
	
	  ;% khgsjmcu2zh.npgddqz44t.LoggedData
	  section.data(9).logicalSrcIdx = 21;
	  section.data(9).dtTransOffset = 14;
	
	  ;% khgsjmcu2zh.fcu5h2vywn.LoggedData
	  section.data(10).logicalSrcIdx = 22;
	  section.data(10).dtTransOffset = 16;
	
	  ;% khgsjmcu2zh.o3n0tlffr1.LoggedData
	  section.data(11).logicalSrcIdx = 23;
	  section.data(11).dtTransOffset = 19;
	
	  ;% khgsjmcu2zh.fze3tfcfs1.LoggedData
	  section.data(12).logicalSrcIdx = 24;
	  section.data(12).dtTransOffset = 20;
	
	  ;% khgsjmcu2zh.cuvfj5oyyh.LoggedData
	  section.data(13).logicalSrcIdx = 25;
	  section.data(13).dtTransOffset = 21;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.a5vniid1mf
	  section.data(1).logicalSrcIdx = 26;
	  section.data(1).dtTransOffset = 0;
	
	  ;% khgsjmcu2zh.gwm13mwotc
	  section.data(2).logicalSrcIdx = 27;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ghn2nojvif
	  section.data(1).logicalSrcIdx = 28;
	  section.data(1).dtTransOffset = 0;
	
	  ;% khgsjmcu2zh.ihdwydbhnm
	  section.data(2).logicalSrcIdx = 29;
	  section.data(2).dtTransOffset = 1;
	
	  ;% khgsjmcu2zh.irk2ylhvxt
	  section.data(3).logicalSrcIdx = 30;
	  section.data(3).dtTransOffset = 2;
	
	  ;% khgsjmcu2zh.jtqm1njr1g
	  section.data(4).logicalSrcIdx = 31;
	  section.data(4).dtTransOffset = 3;
	
	  ;% khgsjmcu2zh.f1zj5fzhjo
	  section.data(5).logicalSrcIdx = 32;
	  section.data(5).dtTransOffset = 4;
	
	  ;% khgsjmcu2zh.ljodvfojqz
	  section.data(6).logicalSrcIdx = 33;
	  section.data(6).dtTransOffset = 5;
	
	  ;% khgsjmcu2zh.g514tpjtzd
	  section.data(7).logicalSrcIdx = 34;
	  section.data(7).dtTransOffset = 6;
	
	  ;% khgsjmcu2zh.mginnteowg
	  section.data(8).logicalSrcIdx = 35;
	  section.data(8).dtTransOffset = 7;
	
	  ;% khgsjmcu2zh.o5dhktr2xg
	  section.data(9).logicalSrcIdx = 36;
	  section.data(9).dtTransOffset = 8;
	
	  ;% khgsjmcu2zh.fvguhkipj3
	  section.data(10).logicalSrcIdx = 37;
	  section.data(10).dtTransOffset = 9;
	
	  ;% khgsjmcu2zh.ml5cuilmwp
	  section.data(11).logicalSrcIdx = 38;
	  section.data(11).dtTransOffset = 10;
	
	  ;% khgsjmcu2zh.panzj542po
	  section.data(12).logicalSrcIdx = 39;
	  section.data(12).dtTransOffset = 11;
	
	  ;% khgsjmcu2zh.b2zbxp5dyr
	  section.data(13).logicalSrcIdx = 40;
	  section.data(13).dtTransOffset = 12;
	
	  ;% khgsjmcu2zh.azxeehreyh
	  section.data(14).logicalSrcIdx = 41;
	  section.data(14).dtTransOffset = 13;
	
	  ;% khgsjmcu2zh.g313j543ib
	  section.data(15).logicalSrcIdx = 42;
	  section.data(15).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.jjwbdm32dt.dxnvlicpck
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.jjwbdm32dt.ls3zcvq2zm
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ap5o1ljg5p.dxnvlicpck
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ap5o1ljg5p.ls3zcvq2zm
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ntpnjgaxbk.dxnvlicpck
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ntpnjgaxbk.ls3zcvq2zm
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ltp5v1qb5p.dxnvlicpck
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ltp5v1qb5p.ls3zcvq2zm
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.dhd2bo1xvw.dxnvlicpck
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.dhd2bo1xvw.ls3zcvq2zm
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.jvot4d0aks.dxnvlicpck
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.jvot4d0aks.ls3zcvq2zm
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.addnvjrs50.dxnvlicpck
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.addnvjrs50.ls3zcvq2zm
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.bmuonaufob.dxnvlicpck
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.bmuonaufob.ls3zcvq2zm
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.dy5xffgu1e.dxnvlicpck
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.dy5xffgu1e.ls3zcvq2zm
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.jei05f3f2n.dxnvlicpck
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.jei05f3f2n.ls3zcvq2zm
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.c4w4mthusc.dxnvlicpck
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.c4w4mthusc.ls3zcvq2zm
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.c4ks1ni02r.dxnvlicpck
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.c4ks1ni02r.ls3zcvq2zm
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.fzox2unuby.dxnvlicpck
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.fzox2unuby.ls3zcvq2zm
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.dm5drkuaxy.dxnvlicpck
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.dm5drkuaxy.ls3zcvq2zm
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.c3zx4oz2izh.dxnvlicpck
	  section.data(1).logicalSrcIdx = 71;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.c3zx4oz2izh.ls3zcvq2zm
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


  targMap.checksum0 = 3010181780;
  targMap.checksum1 = 2641481573;
  targMap.checksum2 = 3302378944;
  targMap.checksum3 = 663301287;

