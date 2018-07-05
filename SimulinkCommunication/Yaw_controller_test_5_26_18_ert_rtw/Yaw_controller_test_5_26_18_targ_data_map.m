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
    ;% Auto data (lyfmacnrqu)
    ;%
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% lyfmacnrqu.Klqr
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% lyfmacnrqu.FixPtBitwiseOperator1_BitMask
	  section.data(1).logicalSrcIdx = 1;
	  section.data(1).dtTransOffset = 0;
	
	  ;% lyfmacnrqu.FixPtBitwiseOperator_por4gyvigl
	  section.data(2).logicalSrcIdx = 2;
	  section.data(2).dtTransOffset = 1;
	
	  ;% lyfmacnrqu.FixPtBitwiseOperator_dbwoemf5x1
	  section.data(3).logicalSrcIdx = 3;
	  section.data(3).dtTransOffset = 2;
	
	  ;% lyfmacnrqu.FixPtBitwiseOperator_atugmhsjgu
	  section.data(4).logicalSrcIdx = 4;
	  section.data(4).dtTransOffset = 3;
	
	  ;% lyfmacnrqu.FixPtBitwiseOperator_jsxtcvks5h
	  section.data(5).logicalSrcIdx = 5;
	  section.data(5).dtTransOffset = 4;
	
	  ;% lyfmacnrqu.FixPtBitwiseOperator_kdshhjihni
	  section.data(6).logicalSrcIdx = 6;
	  section.data(6).dtTransOffset = 5;
	
	  ;% lyfmacnrqu.FixPtBitwiseOperator_o52d0510h2
	  section.data(7).logicalSrcIdx = 7;
	  section.data(7).dtTransOffset = 6;
	
	  ;% lyfmacnrqu.FixPtBitwiseOperator_otzx5fht4b
	  section.data(8).logicalSrcIdx = 8;
	  section.data(8).dtTransOffset = 7;
	
	  ;% lyfmacnrqu.FixPtBitwiseOperator_ddrm2k3tv5
	  section.data(9).logicalSrcIdx = 9;
	  section.data(9).dtTransOffset = 8;
	
	  ;% lyfmacnrqu.FixPtBitwiseOperator_lldzw4n4id
	  section.data(10).logicalSrcIdx = 10;
	  section.data(10).dtTransOffset = 9;
	
	  ;% lyfmacnrqu.FixPtBitwiseOperator_angyx3o0qv
	  section.data(11).logicalSrcIdx = 11;
	  section.data(11).dtTransOffset = 10;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 36;
      section.data(36)  = dumData; %prealloc
      
	  ;% lyfmacnrqu._Value
	  section.data(1).logicalSrcIdx = 12;
	  section.data(1).dtTransOffset = 0;
	
	  ;% lyfmacnrqu.ConstMotVel_Value
	  section.data(2).logicalSrcIdx = 13;
	  section.data(2).dtTransOffset = 1;
	
	  ;% lyfmacnrqu.EulerInttoDoubleScaleFactor_Gai
	  section.data(3).logicalSrcIdx = 14;
	  section.data(3).dtTransOffset = 2;
	
	  ;% lyfmacnrqu.CorrectingForSignConvention1_Ga
	  section.data(4).logicalSrcIdx = 15;
	  section.data(4).dtTransOffset = 3;
	
	  ;% lyfmacnrqu.Gain_Gain
	  section.data(5).logicalSrcIdx = 16;
	  section.data(5).dtTransOffset = 4;
	
	  ;% lyfmacnrqu.Integrator_IC
	  section.data(6).logicalSrcIdx = 17;
	  section.data(6).dtTransOffset = 5;
	
	  ;% lyfmacnrqu.Gain1_Gain
	  section.data(7).logicalSrcIdx = 18;
	  section.data(7).dtTransOffset = 6;
	
	  ;% lyfmacnrqu.GyroscopeInttoDoubleScaleFactor
	  section.data(8).logicalSrcIdx = 19;
	  section.data(8).dtTransOffset = 7;
	
	  ;% lyfmacnrqu.CorrectingForSignConvention_Gai
	  section.data(9).logicalSrcIdx = 20;
	  section.data(9).dtTransOffset = 8;
	
	  ;% lyfmacnrqu.Gain1_Gain_jmhajh5utx
	  section.data(10).logicalSrcIdx = 21;
	  section.data(10).dtTransOffset = 9;
	
	  ;% lyfmacnrqu.DesiredYawRate_Value
	  section.data(11).logicalSrcIdx = 22;
	  section.data(11).dtTransOffset = 10;
	
	  ;% lyfmacnrqu.Gain2_Gain
	  section.data(12).logicalSrcIdx = 23;
	  section.data(12).dtTransOffset = 11;
	
	  ;% lyfmacnrqu.RadianstoSteeringInput_Gain
	  section.data(13).logicalSrcIdx = 24;
	  section.data(13).dtTransOffset = 12;
	
	  ;% lyfmacnrqu.Saturation_UpperSat
	  section.data(14).logicalSrcIdx = 25;
	  section.data(14).dtTransOffset = 13;
	
	  ;% lyfmacnrqu.Saturation_LowerSat
	  section.data(15).logicalSrcIdx = 26;
	  section.data(15).dtTransOffset = 14;
	
	  ;% lyfmacnrqu.DeadSwitchValue_Value
	  section.data(16).logicalSrcIdx = 27;
	  section.data(16).dtTransOffset = 15;
	
	  ;% lyfmacnrqu.TransferFcn1_A
	  section.data(17).logicalSrcIdx = 28;
	  section.data(17).dtTransOffset = 16;
	
	  ;% lyfmacnrqu.TransferFcn1_C
	  section.data(18).logicalSrcIdx = 29;
	  section.data(18).dtTransOffset = 17;
	
	  ;% lyfmacnrqu.TransferFcn_A
	  section.data(19).logicalSrcIdx = 30;
	  section.data(19).dtTransOffset = 18;
	
	  ;% lyfmacnrqu.TransferFcn_C
	  section.data(20).logicalSrcIdx = 31;
	  section.data(20).dtTransOffset = 19;
	
	  ;% lyfmacnrqu.AccelerationInttoDoubleScaleFac
	  section.data(21).logicalSrcIdx = 32;
	  section.data(21).dtTransOffset = 20;
	
	  ;% lyfmacnrqu.EulerInttoDoubleScal_klqdo4gs5x
	  section.data(22).logicalSrcIdx = 33;
	  section.data(22).dtTransOffset = 21;
	
	  ;% lyfmacnrqu.FlippingSignConvention1_Gain
	  section.data(23).logicalSrcIdx = 34;
	  section.data(23).dtTransOffset = 22;
	
	  ;% lyfmacnrqu.EulerInttoDoubleScal_plft3vecxp
	  section.data(24).logicalSrcIdx = 35;
	  section.data(24).dtTransOffset = 23;
	
	  ;% lyfmacnrqu.FlippingSignConvention2_Gain
	  section.data(25).logicalSrcIdx = 36;
	  section.data(25).dtTransOffset = 24;
	
	  ;% lyfmacnrqu.AccelerationInttoDou_aujvyfutvl
	  section.data(26).logicalSrcIdx = 37;
	  section.data(26).dtTransOffset = 25;
	
	  ;% lyfmacnrqu.GyroscopeInttoDouble_b421t1gbm1
	  section.data(27).logicalSrcIdx = 38;
	  section.data(27).dtTransOffset = 26;
	
	  ;% lyfmacnrqu.AccelerationInttoDou_lh2vjcl0wj
	  section.data(28).logicalSrcIdx = 39;
	  section.data(28).dtTransOffset = 27;
	
	  ;% lyfmacnrqu.GyroscopeInttoDouble_e5xd4ckhrv
	  section.data(29).logicalSrcIdx = 40;
	  section.data(29).dtTransOffset = 28;
	
	  ;% lyfmacnrqu.Integrator1_IC
	  section.data(30).logicalSrcIdx = 41;
	  section.data(30).dtTransOffset = 29;
	
	  ;% lyfmacnrqu.Constant4_Value
	  section.data(31).logicalSrcIdx = 42;
	  section.data(31).dtTransOffset = 30;
	
	  ;% lyfmacnrqu.Constant3_Value
	  section.data(32).logicalSrcIdx = 43;
	  section.data(32).dtTransOffset = 31;
	
	  ;% lyfmacnrqu.Constant5_Value
	  section.data(33).logicalSrcIdx = 44;
	  section.data(33).dtTransOffset = 32;
	
	  ;% lyfmacnrqu.Constant7_Value
	  section.data(34).logicalSrcIdx = 45;
	  section.data(34).dtTransOffset = 33;
	
	  ;% lyfmacnrqu.Constant6_Value
	  section.data(35).logicalSrcIdx = 46;
	  section.data(35).dtTransOffset = 34;
	
	  ;% lyfmacnrqu.Constant8_Value
	  section.data(36).logicalSrcIdx = 47;
	  section.data(36).dtTransOffset = 35;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 52;
      section.data(52)  = dumData; %prealloc
      
	  ;% lyfmacnrqu.euler_headingAddressNumber_Valu
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
	  ;% lyfmacnrqu.uint8_t1_Value
	  section.data(2).logicalSrcIdx = 49;
	  section.data(2).dtTransOffset = 1;
	
	  ;% lyfmacnrqu.uint8_t2_Value
	  section.data(3).logicalSrcIdx = 50;
	  section.data(3).dtTransOffset = 2;
	
	  ;% lyfmacnrqu.uint8_t3_Value
	  section.data(4).logicalSrcIdx = 51;
	  section.data(4).dtTransOffset = 3;
	
	  ;% lyfmacnrqu.gyr_zAddressNumber_Value
	  section.data(5).logicalSrcIdx = 52;
	  section.data(5).dtTransOffset = 4;
	
	  ;% lyfmacnrqu.uint8_t1_Value_l4s4vz5xkx
	  section.data(6).logicalSrcIdx = 53;
	  section.data(6).dtTransOffset = 5;
	
	  ;% lyfmacnrqu.uint8_t2_Value_hhrg0id5fg
	  section.data(7).logicalSrcIdx = 54;
	  section.data(7).dtTransOffset = 6;
	
	  ;% lyfmacnrqu.uint8_t3_Value_hmivthjikv
	  section.data(8).logicalSrcIdx = 55;
	  section.data(8).dtTransOffset = 7;
	
	  ;% lyfmacnrqu.euler_rollAddressNumber_Value
	  section.data(9).logicalSrcIdx = 56;
	  section.data(9).dtTransOffset = 8;
	
	  ;% lyfmacnrqu.uint8_t1_Value_jp52tw5trt
	  section.data(10).logicalSrcIdx = 57;
	  section.data(10).dtTransOffset = 9;
	
	  ;% lyfmacnrqu.uint8_t2_Value_cbekgc1ix1
	  section.data(11).logicalSrcIdx = 58;
	  section.data(11).dtTransOffset = 10;
	
	  ;% lyfmacnrqu.uint8_t3_Value_ogsbdg3hgh
	  section.data(12).logicalSrcIdx = 59;
	  section.data(12).dtTransOffset = 11;
	
	  ;% lyfmacnrqu.euler_pitchAddressNumber_Value
	  section.data(13).logicalSrcIdx = 60;
	  section.data(13).dtTransOffset = 12;
	
	  ;% lyfmacnrqu.uint8_t1_Value_pvva4akqka
	  section.data(14).logicalSrcIdx = 61;
	  section.data(14).dtTransOffset = 13;
	
	  ;% lyfmacnrqu.uint8_t2_Value_h4tdc4qduu
	  section.data(15).logicalSrcIdx = 62;
	  section.data(15).dtTransOffset = 14;
	
	  ;% lyfmacnrqu.uint8_t3_Value_a3ug1bpdkn
	  section.data(16).logicalSrcIdx = 63;
	  section.data(16).dtTransOffset = 15;
	
	  ;% lyfmacnrqu.gyr_xAddressNumber_Value
	  section.data(17).logicalSrcIdx = 64;
	  section.data(17).dtTransOffset = 16;
	
	  ;% lyfmacnrqu.uint8_t1_Value_pmn1jm1kfo
	  section.data(18).logicalSrcIdx = 65;
	  section.data(18).dtTransOffset = 17;
	
	  ;% lyfmacnrqu.uint8_t2_Value_i0vxnflql2
	  section.data(19).logicalSrcIdx = 66;
	  section.data(19).dtTransOffset = 18;
	
	  ;% lyfmacnrqu.uint8_t3_Value_nrurpwmqav
	  section.data(20).logicalSrcIdx = 67;
	  section.data(20).dtTransOffset = 19;
	
	  ;% lyfmacnrqu.acc_xAddressNumber_Value
	  section.data(21).logicalSrcIdx = 68;
	  section.data(21).dtTransOffset = 20;
	
	  ;% lyfmacnrqu.uint8_t1_Value_ouskjask11
	  section.data(22).logicalSrcIdx = 69;
	  section.data(22).dtTransOffset = 21;
	
	  ;% lyfmacnrqu.uint8_t2_Value_jfwwqdd2no
	  section.data(23).logicalSrcIdx = 70;
	  section.data(23).dtTransOffset = 22;
	
	  ;% lyfmacnrqu.uint8_t3_Value_dw24f2x23u
	  section.data(24).logicalSrcIdx = 71;
	  section.data(24).dtTransOffset = 23;
	
	  ;% lyfmacnrqu.gyr_yAddressNumber_Value
	  section.data(25).logicalSrcIdx = 72;
	  section.data(25).dtTransOffset = 24;
	
	  ;% lyfmacnrqu.uint8_t1_Value_bcobfnndsx
	  section.data(26).logicalSrcIdx = 73;
	  section.data(26).dtTransOffset = 25;
	
	  ;% lyfmacnrqu.uint8_t2_Value_hqwvrd4twi
	  section.data(27).logicalSrcIdx = 74;
	  section.data(27).dtTransOffset = 26;
	
	  ;% lyfmacnrqu.uint8_t3_Value_c21o0i3auf
	  section.data(28).logicalSrcIdx = 75;
	  section.data(28).dtTransOffset = 27;
	
	  ;% lyfmacnrqu.acc_yAddressNumber_Value
	  section.data(29).logicalSrcIdx = 76;
	  section.data(29).dtTransOffset = 28;
	
	  ;% lyfmacnrqu.uint8_t1_Value_b0zppk31r4
	  section.data(30).logicalSrcIdx = 77;
	  section.data(30).dtTransOffset = 29;
	
	  ;% lyfmacnrqu.uint8_t2_Value_pyjvbvlbem
	  section.data(31).logicalSrcIdx = 78;
	  section.data(31).dtTransOffset = 30;
	
	  ;% lyfmacnrqu.uint8_t3_Value_b0b4j2vbaf
	  section.data(32).logicalSrcIdx = 79;
	  section.data(32).dtTransOffset = 31;
	
	  ;% lyfmacnrqu.acc_zAddressNumber_Value
	  section.data(33).logicalSrcIdx = 80;
	  section.data(33).dtTransOffset = 32;
	
	  ;% lyfmacnrqu.uint8_t1_Value_ndwjvcq4pj
	  section.data(34).logicalSrcIdx = 81;
	  section.data(34).dtTransOffset = 33;
	
	  ;% lyfmacnrqu.uint8_t2_Value_a3uff1f45z
	  section.data(35).logicalSrcIdx = 82;
	  section.data(35).dtTransOffset = 34;
	
	  ;% lyfmacnrqu.uint8_t3_Value_pg3iqy2mhk
	  section.data(36).logicalSrcIdx = 83;
	  section.data(36).dtTransOffset = 35;
	
	  ;% lyfmacnrqu.radio_throttleAddressNumber_Val
	  section.data(37).logicalSrcIdx = 84;
	  section.data(37).dtTransOffset = 36;
	
	  ;% lyfmacnrqu.uint8_t1_Value_mqqv3z2urc
	  section.data(38).logicalSrcIdx = 85;
	  section.data(38).dtTransOffset = 37;
	
	  ;% lyfmacnrqu.uint8_t2_Value_k1eeeatxki
	  section.data(39).logicalSrcIdx = 86;
	  section.data(39).dtTransOffset = 38;
	
	  ;% lyfmacnrqu.uint8_t3_Value_e43ty2im1x
	  section.data(40).logicalSrcIdx = 87;
	  section.data(40).dtTransOffset = 39;
	
	  ;% lyfmacnrqu.radio_steeringAddressNumber_Val
	  section.data(41).logicalSrcIdx = 88;
	  section.data(41).dtTransOffset = 40;
	
	  ;% lyfmacnrqu.uint8_t1_Value_cw1zfby0wz
	  section.data(42).logicalSrcIdx = 89;
	  section.data(42).dtTransOffset = 41;
	
	  ;% lyfmacnrqu.uint8_t2_Value_ek5gh5om5j
	  section.data(43).logicalSrcIdx = 90;
	  section.data(43).dtTransOffset = 42;
	
	  ;% lyfmacnrqu.uint8_t3_Value_fpzgv3t1fy
	  section.data(44).logicalSrcIdx = 91;
	  section.data(44).dtTransOffset = 43;
	
	  ;% lyfmacnrqu.DeadSwitch_Value
	  section.data(45).logicalSrcIdx = 92;
	  section.data(45).dtTransOffset = 44;
	
	  ;% lyfmacnrqu.TakeData_Value
	  section.data(46).logicalSrcIdx = 93;
	  section.data(46).dtTransOffset = 45;
	
	  ;% lyfmacnrqu.ServoandRadioOn_Value
	  section.data(47).logicalSrcIdx = 94;
	  section.data(47).dtTransOffset = 46;
	
	  ;% lyfmacnrqu.MotorControllersOn_Value
	  section.data(48).logicalSrcIdx = 95;
	  section.data(48).dtTransOffset = 47;
	
	  ;% lyfmacnrqu.IMUReset_Value
	  section.data(49).logicalSrcIdx = 96;
	  section.data(49).dtTransOffset = 48;
	
	  ;% lyfmacnrqu.PrinttheregistermapontheTeensy_
	  section.data(50).logicalSrcIdx = 97;
	  section.data(50).dtTransOffset = 49;
	
	  ;% lyfmacnrqu.PrinttheimudataontheTeensy_Valu
	  section.data(51).logicalSrcIdx = 98;
	  section.data(51).dtTransOffset = 50;
	
	  ;% lyfmacnrqu.Printtheradiotranceiverdataonth
	  section.data(52).logicalSrcIdx = 99;
	  section.data(52).dtTransOffset = 51;
	
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
    nTotSects     = 35;
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
    ;% Auto data (a1d1p04q4k0)
    ;%
      section.nData     = 27;
      section.data(27)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.knozaxvl5x
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% a1d1p04q4k0.nd51dyrcig
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% a1d1p04q4k0.atcpui2ro3
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% a1d1p04q4k0.mgnxxmkges
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% a1d1p04q4k0.odmet0m4xw
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% a1d1p04q4k0.durlqyqteg
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% a1d1p04q4k0.imn5rw2fnh
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% a1d1p04q4k0.kito2jp3md
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% a1d1p04q4k0.k3k2mrvedo
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% a1d1p04q4k0.j1l3zcyh3w
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% a1d1p04q4k0.cauhhivbpj
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% a1d1p04q4k0.aszuaqa12b
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% a1d1p04q4k0.fgx2rpql5j
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% a1d1p04q4k0.bqm13rp0o0
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% a1d1p04q4k0.oxqaxv1vq1
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% a1d1p04q4k0.jdfna2x34s
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% a1d1p04q4k0.lwquvw5khh
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% a1d1p04q4k0.iqycbuef3t
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% a1d1p04q4k0.lbiwfgmrdf
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% a1d1p04q4k0.easbm52yss
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% a1d1p04q4k0.gkidso2l4t
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
	  ;% a1d1p04q4k0.mnvrg2vrgo
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 21;
	
	  ;% a1d1p04q4k0.nknmr33oxl
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 22;
	
	  ;% a1d1p04q4k0.ncd4g0bruf
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 23;
	
	  ;% a1d1p04q4k0.nnmfrabgl3
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 24;
	
	  ;% a1d1p04q4k0.pfuxf3gpfs
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 25;
	
	  ;% a1d1p04q4k0.bqmtjbpds1
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 26;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.dbh0f2lzjs
	  section.data(1).logicalSrcIdx = 27;
	  section.data(1).dtTransOffset = 0;
	
	  ;% a1d1p04q4k0.kgqpx2pdgu
	  section.data(2).logicalSrcIdx = 28;
	  section.data(2).dtTransOffset = 1;
	
	  ;% a1d1p04q4k0.frk2hslgez
	  section.data(3).logicalSrcIdx = 29;
	  section.data(3).dtTransOffset = 2;
	
	  ;% a1d1p04q4k0.lh1ukvruso
	  section.data(4).logicalSrcIdx = 30;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 12;
      section.data(12)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.gwxyswpdeu
	  section.data(1).logicalSrcIdx = 31;
	  section.data(1).dtTransOffset = 0;
	
	  ;% a1d1p04q4k0.dikwdqmvcb
	  section.data(2).logicalSrcIdx = 32;
	  section.data(2).dtTransOffset = 1;
	
	  ;% a1d1p04q4k0.jvpsmrh5eb
	  section.data(3).logicalSrcIdx = 33;
	  section.data(3).dtTransOffset = 2;
	
	  ;% a1d1p04q4k0.hzgwxnoi3e
	  section.data(4).logicalSrcIdx = 34;
	  section.data(4).dtTransOffset = 3;
	
	  ;% a1d1p04q4k0.abl5rpdpdw
	  section.data(5).logicalSrcIdx = 35;
	  section.data(5).dtTransOffset = 4;
	
	  ;% a1d1p04q4k0.ejkssl44yn
	  section.data(6).logicalSrcIdx = 36;
	  section.data(6).dtTransOffset = 5;
	
	  ;% a1d1p04q4k0.m4fytuinmt
	  section.data(7).logicalSrcIdx = 37;
	  section.data(7).dtTransOffset = 6;
	
	  ;% a1d1p04q4k0.gzql4u11ms
	  section.data(8).logicalSrcIdx = 38;
	  section.data(8).dtTransOffset = 7;
	
	  ;% a1d1p04q4k0.jmszl3bxly
	  section.data(9).logicalSrcIdx = 39;
	  section.data(9).dtTransOffset = 8;
	
	  ;% a1d1p04q4k0.as5nlbekf2
	  section.data(10).logicalSrcIdx = 40;
	  section.data(10).dtTransOffset = 10;
	
	  ;% a1d1p04q4k0.k2qmcrng5k
	  section.data(11).logicalSrcIdx = 41;
	  section.data(11).dtTransOffset = 12;
	
	  ;% a1d1p04q4k0.nrvonr2ag2
	  section.data(12).logicalSrcIdx = 42;
	  section.data(12).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.dypcawmszf.f15uanuq05
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.hdintiwyu3.btetf1hbsc
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.jmtb2jjbhn.f15uanuq05
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.kl0psmya0z.btetf1hbsc
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.goegdrcwom.f15uanuq05
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.m0ylixn35h.btetf1hbsc
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.kehgcpukfi.f15uanuq05
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.n434inyjhk.btetf1hbsc
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.gm3oic1qfsp.f15uanuq05
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.omjjdp4abzs.btetf1hbsc
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.akm0bipubt.pis0lno5r4
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.f3edlsw3ne.pis0lno5r4
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.izuj1rmxq3.pis0lno5r4
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.f0frxagat4.pis0lno5r4
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.eybxy0ua10.pis0lno5r4
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.jhl3l2f50c.pis0lno5r4
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.pgqliowqgw.pis0lno5r4
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.davvxlo4uo.pis0lno5r4
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.lh3f0yaqrg.pis0lno5r4
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.bzufyicmvi.pis0lno5r4
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.i4k4jqpvbnl.pis0lno5r4
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.evmvwve0pt.pvlwxxuzcd
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.pnl03afvor.pvlwxxuzcd
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.cxw3ayx205.pvlwxxuzcd
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.kajqzqwi00.pvlwxxuzcd
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.m3p0j3duep.pvlwxxuzcd
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.gxddsbsgfq.pvlwxxuzcd
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.d2lbhdzsqn.pvlwxxuzcd
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.pnfg3j0eql.pvlwxxuzcd
	  section.data(1).logicalSrcIdx = 71;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.et0ylvirie.pvlwxxuzcd
	  section.data(1).logicalSrcIdx = 72;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.ipnnrjs0wk.pvlwxxuzcd
	  section.data(1).logicalSrcIdx = 73;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(34) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% a1d1p04q4k0.oe0zobg41jq.pvlwxxuzcd
	  section.data(1).logicalSrcIdx = 74;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(35) = section;
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
    nTotSects     = 26;
    sectIdxOffset = 35;
    
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
    ;% Auto data (iygoqh1vztm)
    ;%
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.c2thmszre5
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% iygoqh1vztm.ivrotn354d
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% iygoqh1vztm.nqs3ygefxa
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% iygoqh1vztm.lqqhybcx50
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% iygoqh1vztm.djlat2s01w
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% iygoqh1vztm.iiediwa42s
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% iygoqh1vztm.nrs54fkjap
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% iygoqh1vztm.nclel02uci
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% iygoqh1vztm.f0aqpa2bpn
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% iygoqh1vztm.mtzatpdzzq
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% iygoqh1vztm.ohrmbqh3fu
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% iygoqh1vztm.p3fvn52vtm
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% iygoqh1vztm.oxsppkdifg
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 22;
      section.data(22)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.jjkaycipoz.LoggedData
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
	  ;% iygoqh1vztm.lzzsuettl2.LoggedData
	  section.data(2).logicalSrcIdx = 14;
	  section.data(2).dtTransOffset = 1;
	
	  ;% iygoqh1vztm.c5vx33pucm.LoggedData
	  section.data(3).logicalSrcIdx = 15;
	  section.data(3).dtTransOffset = 2;
	
	  ;% iygoqh1vztm.owr4fb125y.LoggedData
	  section.data(4).logicalSrcIdx = 16;
	  section.data(4).dtTransOffset = 3;
	
	  ;% iygoqh1vztm.j2o0gcanbn.LoggedData
	  section.data(5).logicalSrcIdx = 17;
	  section.data(5).dtTransOffset = 4;
	
	  ;% iygoqh1vztm.avmlavtics.LoggedData
	  section.data(6).logicalSrcIdx = 18;
	  section.data(6).dtTransOffset = 6;
	
	  ;% iygoqh1vztm.p23u3pinhc.LoggedData
	  section.data(7).logicalSrcIdx = 19;
	  section.data(7).dtTransOffset = 7;
	
	  ;% iygoqh1vztm.jygjt2zv0g.LoggedData
	  section.data(8).logicalSrcIdx = 20;
	  section.data(8).dtTransOffset = 8;
	
	  ;% iygoqh1vztm.mofx5ca0wd.LoggedData
	  section.data(9).logicalSrcIdx = 21;
	  section.data(9).dtTransOffset = 10;
	
	  ;% iygoqh1vztm.htntsl4pfg.LoggedData
	  section.data(10).logicalSrcIdx = 22;
	  section.data(10).dtTransOffset = 11;
	
	  ;% iygoqh1vztm.ckjw01o5vu.LoggedData
	  section.data(11).logicalSrcIdx = 23;
	  section.data(11).dtTransOffset = 12;
	
	  ;% iygoqh1vztm.ecpdxr5wrl.LoggedData
	  section.data(12).logicalSrcIdx = 24;
	  section.data(12).dtTransOffset = 13;
	
	  ;% iygoqh1vztm.l5jg0vv2ih.LoggedData
	  section.data(13).logicalSrcIdx = 25;
	  section.data(13).dtTransOffset = 14;
	
	  ;% iygoqh1vztm.de3veryl1i.LoggedData
	  section.data(14).logicalSrcIdx = 26;
	  section.data(14).dtTransOffset = 16;
	
	  ;% iygoqh1vztm.p1qgr5a2js.LoggedData
	  section.data(15).logicalSrcIdx = 27;
	  section.data(15).dtTransOffset = 17;
	
	  ;% iygoqh1vztm.fq0wkjovyj.LoggedData
	  section.data(16).logicalSrcIdx = 28;
	  section.data(16).dtTransOffset = 18;
	
	  ;% iygoqh1vztm.cmezosrjzi.LoggedData
	  section.data(17).logicalSrcIdx = 29;
	  section.data(17).dtTransOffset = 19;
	
	  ;% iygoqh1vztm.au2t5hkkq4.LoggedData
	  section.data(18).logicalSrcIdx = 30;
	  section.data(18).dtTransOffset = 22;
	
	  ;% iygoqh1vztm.ghnrqhhoaq.LoggedData
	  section.data(19).logicalSrcIdx = 31;
	  section.data(19).dtTransOffset = 23;
	
	  ;% iygoqh1vztm.bv0uoiwoz1.LoggedData
	  section.data(20).logicalSrcIdx = 32;
	  section.data(20).dtTransOffset = 24;
	
	  ;% iygoqh1vztm.hruy5f5fvl.LoggedData
	  section.data(21).logicalSrcIdx = 33;
	  section.data(21).dtTransOffset = 25;
	
	  ;% iygoqh1vztm.lrwhjhrgcu.LoggedData
	  section.data(22).logicalSrcIdx = 34;
	  section.data(22).dtTransOffset = 27;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.pmkh1lkmzv
	  section.data(1).logicalSrcIdx = 35;
	  section.data(1).dtTransOffset = 0;
	
	  ;% iygoqh1vztm.ozixgh3dhk
	  section.data(2).logicalSrcIdx = 36;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.e5oxqzotjq
	  section.data(1).logicalSrcIdx = 37;
	  section.data(1).dtTransOffset = 0;
	
	  ;% iygoqh1vztm.fwafyt2qx5
	  section.data(2).logicalSrcIdx = 38;
	  section.data(2).dtTransOffset = 1;
	
	  ;% iygoqh1vztm.k2sz010kho
	  section.data(3).logicalSrcIdx = 39;
	  section.data(3).dtTransOffset = 2;
	
	  ;% iygoqh1vztm.lmqci1t0oe
	  section.data(4).logicalSrcIdx = 40;
	  section.data(4).dtTransOffset = 3;
	
	  ;% iygoqh1vztm.fne54idmgv
	  section.data(5).logicalSrcIdx = 41;
	  section.data(5).dtTransOffset = 4;
	
	  ;% iygoqh1vztm.obhefh10sz
	  section.data(6).logicalSrcIdx = 42;
	  section.data(6).dtTransOffset = 5;
	
	  ;% iygoqh1vztm.phtuoumx1p
	  section.data(7).logicalSrcIdx = 43;
	  section.data(7).dtTransOffset = 6;
	
	  ;% iygoqh1vztm.nlamzn3btt
	  section.data(8).logicalSrcIdx = 44;
	  section.data(8).dtTransOffset = 7;
	
	  ;% iygoqh1vztm.fto4wqcm5h
	  section.data(9).logicalSrcIdx = 45;
	  section.data(9).dtTransOffset = 8;
	
	  ;% iygoqh1vztm.c5xbu5ceay
	  section.data(10).logicalSrcIdx = 46;
	  section.data(10).dtTransOffset = 9;
	
	  ;% iygoqh1vztm.hkrndi2spc
	  section.data(11).logicalSrcIdx = 47;
	  section.data(11).dtTransOffset = 10;
	
	  ;% iygoqh1vztm.nlhgconbaz
	  section.data(12).logicalSrcIdx = 48;
	  section.data(12).dtTransOffset = 11;
	
	  ;% iygoqh1vztm.hdpmm1gagk
	  section.data(13).logicalSrcIdx = 49;
	  section.data(13).dtTransOffset = 12;
	
	  ;% iygoqh1vztm.d2nbbnuwjo
	  section.data(14).logicalSrcIdx = 50;
	  section.data(14).dtTransOffset = 13;
	
	  ;% iygoqh1vztm.bbzole4ler
	  section.data(15).logicalSrcIdx = 51;
	  section.data(15).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.evmvwve0pt.krgbi3mirt
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.evmvwve0pt.hodmfufukb
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.pnl03afvor.krgbi3mirt
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.pnl03afvor.hodmfufukb
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.cxw3ayx205.krgbi3mirt
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.cxw3ayx205.hodmfufukb
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.kajqzqwi00.krgbi3mirt
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.kajqzqwi00.hodmfufukb
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.m3p0j3duep.krgbi3mirt
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.m3p0j3duep.hodmfufukb
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.gxddsbsgfq.krgbi3mirt
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.gxddsbsgfq.hodmfufukb
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.d2lbhdzsqn.krgbi3mirt
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.d2lbhdzsqn.hodmfufukb
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.pnfg3j0eql.krgbi3mirt
	  section.data(1).logicalSrcIdx = 66;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.pnfg3j0eql.hodmfufukb
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.et0ylvirie.krgbi3mirt
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.et0ylvirie.hodmfufukb
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.ipnnrjs0wk.krgbi3mirt
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.ipnnrjs0wk.hodmfufukb
	  section.data(1).logicalSrcIdx = 71;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.oe0zobg41jq.krgbi3mirt
	  section.data(1).logicalSrcIdx = 72;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% iygoqh1vztm.oe0zobg41jq.hodmfufukb
	  section.data(1).logicalSrcIdx = 73;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(26) = section;
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


  targMap.checksum0 = 3986138662;
  targMap.checksum1 = 1637004445;
  targMap.checksum2 = 3351761946;
  targMap.checksum3 = 860978934;

