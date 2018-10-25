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
    ;% Auto data (pcaxm4wxrf)
    ;%
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% pcaxm4wxrf.FixPtBitwiseOperator1_BitMask
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% pcaxm4wxrf.FixPtBitwiseOperator_mhhzho00zb
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% pcaxm4wxrf.FixPtBitwiseOperator_iuw2zv1xh4
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% pcaxm4wxrf.FixPtBitwiseOperator_i0arpehpbb
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% pcaxm4wxrf.FixPtBitwiseOperator_ikm2prctc4
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% pcaxm4wxrf.BitwiseAND_BitMask
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 27;
      section.data(27)  = dumData; %prealloc
      
	  ;% pcaxm4wxrf._Value
	  section.data(1).logicalSrcIdx = 6;
	  section.data(1).dtTransOffset = 0;
	
	  ;% pcaxm4wxrf._Value_bbqtwjbdzi
	  section.data(2).logicalSrcIdx = 7;
	  section.data(2).dtTransOffset = 1;
	
	  ;% pcaxm4wxrf.ConstMotTorquemNm_Value
	  section.data(3).logicalSrcIdx = 8;
	  section.data(3).dtTransOffset = 2;
	
	  ;% pcaxm4wxrf.Gain_Gain
	  section.data(4).logicalSrcIdx = 9;
	  section.data(4).dtTransOffset = 3;
	
	  ;% pcaxm4wxrf.bitsmNm1_Gain
	  section.data(5).logicalSrcIdx = 10;
	  section.data(5).dtTransOffset = 4;
	
	  ;% pcaxm4wxrf.bitsmNm1_Gain_ocumkexdek
	  section.data(6).logicalSrcIdx = 11;
	  section.data(6).dtTransOffset = 5;
	
	  ;% pcaxm4wxrf.ConstMotTorquemNm1_Value
	  section.data(7).logicalSrcIdx = 12;
	  section.data(7).dtTransOffset = 6;
	
	  ;% pcaxm4wxrf.Gain1_Gain
	  section.data(8).logicalSrcIdx = 13;
	  section.data(8).dtTransOffset = 7;
	
	  ;% pcaxm4wxrf.bitsmNm1_Gain_kazywep0pm
	  section.data(9).logicalSrcIdx = 14;
	  section.data(9).dtTransOffset = 8;
	
	  ;% pcaxm4wxrf.bitsmNm2_Gain
	  section.data(10).logicalSrcIdx = 15;
	  section.data(10).dtTransOffset = 9;
	
	  ;% pcaxm4wxrf.TriggerValueRequiredforSubsyste
	  section.data(11).logicalSrcIdx = 16;
	  section.data(11).dtTransOffset = 10;
	
	  ;% pcaxm4wxrf.TriggerSwitch_Threshold
	  section.data(12).logicalSrcIdx = 17;
	  section.data(12).dtTransOffset = 11;
	
	  ;% pcaxm4wxrf.TimeallottedforSSIVtoinitialize
	  section.data(13).logicalSrcIdx = 18;
	  section.data(13).dtTransOffset = 12;
	
	  ;% pcaxm4wxrf.Compensatesfordirectionofspinwa
	  section.data(14).logicalSrcIdx = 19;
	  section.data(14).dtTransOffset = 13;
	
	  ;% pcaxm4wxrf.Compensatesfordirect_i5o2fzex5c
	  section.data(15).logicalSrcIdx = 20;
	  section.data(15).dtTransOffset = 14;
	
	  ;% pcaxm4wxrf.EulerInttoDoubleScaleFactor_Gai
	  section.data(16).logicalSrcIdx = 21;
	  section.data(16).dtTransOffset = 15;
	
	  ;% pcaxm4wxrf.EulerInttoDoubleScaleFactor1_Ga
	  section.data(17).logicalSrcIdx = 22;
	  section.data(17).dtTransOffset = 16;
	
	  ;% pcaxm4wxrf.EulerInttoDoubleScaleFactor2_Ga
	  section.data(18).logicalSrcIdx = 23;
	  section.data(18).dtTransOffset = 17;
	
	  ;% pcaxm4wxrf.AccelerationInttoDoubleScaleFac
	  section.data(19).logicalSrcIdx = 24;
	  section.data(19).dtTransOffset = 18;
	
	  ;% pcaxm4wxrf.GyroscopeInttoDoubleScaleFactor
	  section.data(20).logicalSrcIdx = 25;
	  section.data(20).dtTransOffset = 19;
	
	  ;% pcaxm4wxrf.AccelerationInttoDou_gxoyxbctvl
	  section.data(21).logicalSrcIdx = 26;
	  section.data(21).dtTransOffset = 20;
	
	  ;% pcaxm4wxrf.GyroscopeInttoDouble_b3uzo31i4w
	  section.data(22).logicalSrcIdx = 27;
	  section.data(22).dtTransOffset = 21;
	
	  ;% pcaxm4wxrf.AccelerationInttoDou_felr2o3vjy
	  section.data(23).logicalSrcIdx = 28;
	  section.data(23).dtTransOffset = 22;
	
	  ;% pcaxm4wxrf.GyroscopeInttoDouble_msa2vzmmf0
	  section.data(24).logicalSrcIdx = 29;
	  section.data(24).dtTransOffset = 23;
	
	  ;% pcaxm4wxrf.Constant1_Value
	  section.data(25).logicalSrcIdx = 30;
	  section.data(25).dtTransOffset = 24;
	
	  ;% pcaxm4wxrf.TimeZero_Value
	  section.data(26).logicalSrcIdx = 31;
	  section.data(26).dtTransOffset = 25;
	
	  ;% pcaxm4wxrf.Constant2_Value
	  section.data(27).logicalSrcIdx = 32;
	  section.data(27).dtTransOffset = 26;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 53;
      section.data(53)  = dumData; %prealloc
      
	  ;% pcaxm4wxrf.DeadSwitch_Value
	  section.data(1).logicalSrcIdx = 33;
	  section.data(1).dtTransOffset = 0;
	
	  ;% pcaxm4wxrf.InitializeMotorControllersComma
	  section.data(2).logicalSrcIdx = 34;
	  section.data(2).dtTransOffset = 1;
	
	  ;% pcaxm4wxrf.IMUReset_Value
	  section.data(3).logicalSrcIdx = 35;
	  section.data(3).dtTransOffset = 2;
	
	  ;% pcaxm4wxrf.radio_throttleAddressNumber_Val
	  section.data(4).logicalSrcIdx = 36;
	  section.data(4).dtTransOffset = 3;
	
	  ;% pcaxm4wxrf.radio_throttleAddres_exvfxpj3wb
	  section.data(5).logicalSrcIdx = 37;
	  section.data(5).dtTransOffset = 4;
	
	  ;% pcaxm4wxrf.euler_headingAddressNumber_Valu
	  section.data(6).logicalSrcIdx = 38;
	  section.data(6).dtTransOffset = 5;
	
	  ;% pcaxm4wxrf.uint8_t1_Value
	  section.data(7).logicalSrcIdx = 39;
	  section.data(7).dtTransOffset = 6;
	
	  ;% pcaxm4wxrf.uint8_t2_Value
	  section.data(8).logicalSrcIdx = 40;
	  section.data(8).dtTransOffset = 7;
	
	  ;% pcaxm4wxrf.uint8_t3_Value
	  section.data(9).logicalSrcIdx = 41;
	  section.data(9).dtTransOffset = 8;
	
	  ;% pcaxm4wxrf.uint8_t4_Value
	  section.data(10).logicalSrcIdx = 42;
	  section.data(10).dtTransOffset = 9;
	
	  ;% pcaxm4wxrf.uint8_t5_Value
	  section.data(11).logicalSrcIdx = 43;
	  section.data(11).dtTransOffset = 10;
	
	  ;% pcaxm4wxrf.uint8_t6_Value
	  section.data(12).logicalSrcIdx = 44;
	  section.data(12).dtTransOffset = 11;
	
	  ;% pcaxm4wxrf.uint8_t7_Value
	  section.data(13).logicalSrcIdx = 45;
	  section.data(13).dtTransOffset = 12;
	
	  ;% pcaxm4wxrf.uint8_t8_Value
	  section.data(14).logicalSrcIdx = 46;
	  section.data(14).dtTransOffset = 13;
	
	  ;% pcaxm4wxrf.uint8_t9_Value
	  section.data(15).logicalSrcIdx = 47;
	  section.data(15).dtTransOffset = 14;
	
	  ;% pcaxm4wxrf.uint8_t10_Value
	  section.data(16).logicalSrcIdx = 48;
	  section.data(16).dtTransOffset = 15;
	
	  ;% pcaxm4wxrf.uint8_t11_Value
	  section.data(17).logicalSrcIdx = 49;
	  section.data(17).dtTransOffset = 16;
	
	  ;% pcaxm4wxrf.uint8_t12_Value
	  section.data(18).logicalSrcIdx = 50;
	  section.data(18).dtTransOffset = 17;
	
	  ;% pcaxm4wxrf.uint8_t13_Value
	  section.data(19).logicalSrcIdx = 51;
	  section.data(19).dtTransOffset = 18;
	
	  ;% pcaxm4wxrf.uint8_t14_Value
	  section.data(20).logicalSrcIdx = 52;
	  section.data(20).dtTransOffset = 19;
	
	  ;% pcaxm4wxrf.uint8_t15_Value
	  section.data(21).logicalSrcIdx = 53;
	  section.data(21).dtTransOffset = 20;
	
	  ;% pcaxm4wxrf.uint8_t16_Value
	  section.data(22).logicalSrcIdx = 54;
	  section.data(22).dtTransOffset = 21;
	
	  ;% pcaxm4wxrf.uint8_t17_Value
	  section.data(23).logicalSrcIdx = 55;
	  section.data(23).dtTransOffset = 22;
	
	  ;% pcaxm4wxrf.uint8_t18_Value
	  section.data(24).logicalSrcIdx = 56;
	  section.data(24).dtTransOffset = 23;
	
	  ;% pcaxm4wxrf.uint8_t19_Value
	  section.data(25).logicalSrcIdx = 57;
	  section.data(25).dtTransOffset = 24;
	
	  ;% pcaxm4wxrf.rpmfrontrightAddressNumber_Valu
	  section.data(26).logicalSrcIdx = 58;
	  section.data(26).dtTransOffset = 25;
	
	  ;% pcaxm4wxrf.uint8_t1_Value_d3wn2yyjzm
	  section.data(27).logicalSrcIdx = 59;
	  section.data(27).dtTransOffset = 26;
	
	  ;% pcaxm4wxrf.uint8_t2_Value_j2y15wjrqh
	  section.data(28).logicalSrcIdx = 60;
	  section.data(28).dtTransOffset = 27;
	
	  ;% pcaxm4wxrf.uint8_t3_Value_lxavvruaw5
	  section.data(29).logicalSrcIdx = 61;
	  section.data(29).dtTransOffset = 28;
	
	  ;% pcaxm4wxrf.uint8_t4_Value_b1f0txivbu
	  section.data(30).logicalSrcIdx = 62;
	  section.data(30).dtTransOffset = 29;
	
	  ;% pcaxm4wxrf.uint8_t5_Value_kv3uibmfz0
	  section.data(31).logicalSrcIdx = 63;
	  section.data(31).dtTransOffset = 30;
	
	  ;% pcaxm4wxrf.uint8_t6_Value_c5i4cobbcu
	  section.data(32).logicalSrcIdx = 64;
	  section.data(32).dtTransOffset = 31;
	
	  ;% pcaxm4wxrf.uint8_t7_Value_hwfockydxs
	  section.data(33).logicalSrcIdx = 65;
	  section.data(33).dtTransOffset = 32;
	
	  ;% pcaxm4wxrf.uint8_t8_Value_isngtq2z1j
	  section.data(34).logicalSrcIdx = 66;
	  section.data(34).dtTransOffset = 33;
	
	  ;% pcaxm4wxrf.uint8_t9_Value_adm2byqpjc
	  section.data(35).logicalSrcIdx = 67;
	  section.data(35).dtTransOffset = 34;
	
	  ;% pcaxm4wxrf.node_errors0AddressNumber_Value
	  section.data(36).logicalSrcIdx = 68;
	  section.data(36).dtTransOffset = 35;
	
	  ;% pcaxm4wxrf.uint8_t1_Value_osffxyz322
	  section.data(37).logicalSrcIdx = 69;
	  section.data(37).dtTransOffset = 36;
	
	  ;% pcaxm4wxrf.uint8_t2_Value_be1gslf0db
	  section.data(38).logicalSrcIdx = 70;
	  section.data(38).dtTransOffset = 37;
	
	  ;% pcaxm4wxrf.uint8_t3_Value_ij0jf4g5dq
	  section.data(39).logicalSrcIdx = 71;
	  section.data(39).dtTransOffset = 38;
	
	  ;% pcaxm4wxrf.uint8_t4_Value_lcbb3njbqj
	  section.data(40).logicalSrcIdx = 72;
	  section.data(40).dtTransOffset = 39;
	
	  ;% pcaxm4wxrf.uint8_t5_Value_crdeyu0jn1
	  section.data(41).logicalSrcIdx = 73;
	  section.data(41).dtTransOffset = 40;
	
	  ;% pcaxm4wxrf.uint8_t6_Value_ctvwon1ehz
	  section.data(42).logicalSrcIdx = 74;
	  section.data(42).dtTransOffset = 41;
	
	  ;% pcaxm4wxrf.uint8_t7_Value_bqwaa044go
	  section.data(43).logicalSrcIdx = 75;
	  section.data(43).dtTransOffset = 42;
	
	  ;% pcaxm4wxrf.uint8_t8_Value_oldziuby0p
	  section.data(44).logicalSrcIdx = 76;
	  section.data(44).dtTransOffset = 43;
	
	  ;% pcaxm4wxrf.uint8_t9_Value_bwzvycrqy5
	  section.data(45).logicalSrcIdx = 77;
	  section.data(45).dtTransOffset = 44;
	
	  ;% pcaxm4wxrf.uint8_t1_Value_ia4e5oaw1u
	  section.data(46).logicalSrcIdx = 78;
	  section.data(46).dtTransOffset = 45;
	
	  ;% pcaxm4wxrf.uint8_t2_Value_naxjt0rvcp
	  section.data(47).logicalSrcIdx = 79;
	  section.data(47).dtTransOffset = 46;
	
	  ;% pcaxm4wxrf.uint8_t3_Value_fyilwaxi5e
	  section.data(48).logicalSrcIdx = 80;
	  section.data(48).dtTransOffset = 47;
	
	  ;% pcaxm4wxrf.uint8_t4_Value_duovhn5e5i
	  section.data(49).logicalSrcIdx = 81;
	  section.data(49).dtTransOffset = 48;
	
	  ;% pcaxm4wxrf.uint8_t5_Value_dzou0vne3f
	  section.data(50).logicalSrcIdx = 82;
	  section.data(50).dtTransOffset = 49;
	
	  ;% pcaxm4wxrf.uint8_t1_Value_m2yjzgvvms
	  section.data(51).logicalSrcIdx = 83;
	  section.data(51).dtTransOffset = 50;
	
	  ;% pcaxm4wxrf.uint8_t2_Value_fnasbuyxyr
	  section.data(52).logicalSrcIdx = 84;
	  section.data(52).dtTransOffset = 51;
	
	  ;% pcaxm4wxrf.uint8_t3_Value_lyjhgytxlw
	  section.data(53).logicalSrcIdx = 85;
	  section.data(53).dtTransOffset = 52;
	
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
    nTotSects     = 28;
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
    ;% Auto data (efg3yf0kkem)
    ;%
      section.nData     = 27;
      section.data(27)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.oxxrbeznlg
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% efg3yf0kkem.mvldy4raul
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% efg3yf0kkem.i3lpxpz1iu
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% efg3yf0kkem.cxbvppvblw
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% efg3yf0kkem.evo23m2zyk
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% efg3yf0kkem.pkvdvdqylq
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% efg3yf0kkem.bea3rrlx5f
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% efg3yf0kkem.dmkenq54t4
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% efg3yf0kkem.g4031elx14
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% efg3yf0kkem.npdmyfitxw
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% efg3yf0kkem.lyc11jjn54
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% efg3yf0kkem.ons0tuomyx
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% efg3yf0kkem.gxvyyhaj4x
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% efg3yf0kkem.n0nwdqbbdg
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% efg3yf0kkem.n033owscd3
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% efg3yf0kkem.f30qldohip
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% efg3yf0kkem.pqbyuvs0eb
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% efg3yf0kkem.kz4m3lnity
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% efg3yf0kkem.aelpuscuwz
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% efg3yf0kkem.gzjsdcipnk
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% efg3yf0kkem.aaf0vx42qy
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
	  ;% efg3yf0kkem.ifptvcr51f
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 21;
	
	  ;% efg3yf0kkem.at0f2lo51s
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 22;
	
	  ;% efg3yf0kkem.no4lm45uu3
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 23;
	
	  ;% efg3yf0kkem.bttzfeovqe
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 24;
	
	  ;% efg3yf0kkem.ipsmi4etic
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 25;
	
	  ;% efg3yf0kkem.alsp1b5agc
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 26;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.kdnkbjzo05
	  section.data(1).logicalSrcIdx = 27;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.muzj0v5d1p
	  section.data(1).logicalSrcIdx = 28;
	  section.data(1).dtTransOffset = 0;
	
	  ;% efg3yf0kkem.ctgzebo4np
	  section.data(2).logicalSrcIdx = 29;
	  section.data(2).dtTransOffset = 10;
	
	  ;% efg3yf0kkem.jlzl0duh10
	  section.data(3).logicalSrcIdx = 30;
	  section.data(3).dtTransOffset = 12;
	
	  ;% efg3yf0kkem.ezuwvy50yh
	  section.data(4).logicalSrcIdx = 31;
	  section.data(4).dtTransOffset = 13;
	
	  ;% efg3yf0kkem.bcqaexy5ui
	  section.data(5).logicalSrcIdx = 32;
	  section.data(5).dtTransOffset = 14;
	
	  ;% efg3yf0kkem.ifesh0umtt
	  section.data(6).logicalSrcIdx = 33;
	  section.data(6).dtTransOffset = 34;
	
	  ;% efg3yf0kkem.bcwbgize1i
	  section.data(7).logicalSrcIdx = 34;
	  section.data(7).dtTransOffset = 44;
	
	  ;% efg3yf0kkem.mst5t0v3mh
	  section.data(8).logicalSrcIdx = 35;
	  section.data(8).dtTransOffset = 50;
	
	  ;% efg3yf0kkem.alc5srf00r
	  section.data(9).logicalSrcIdx = 36;
	  section.data(9).dtTransOffset = 51;
	
	  ;% efg3yf0kkem.gdc5hyagb5
	  section.data(10).logicalSrcIdx = 37;
	  section.data(10).dtTransOffset = 52;
	
	  ;% efg3yf0kkem.j5rhnhgv54
	  section.data(11).logicalSrcIdx = 38;
	  section.data(11).dtTransOffset = 53;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.bajc5j45db
	  section.data(1).logicalSrcIdx = 39;
	  section.data(1).dtTransOffset = 0;
	
	  ;% efg3yf0kkem.irdl43xnjm
	  section.data(2).logicalSrcIdx = 40;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.pvh32djgqx.idunxy05fq
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.jgyuqgymlz.idunxy05fq
	  section.data(1).logicalSrcIdx = 42;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.gonc2iiqr0.idunxy05fq
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.krbvhpkm1o.idunxy05fq
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.fuzhfqxrqq.idunxy05fq
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.djyvlidvz2.idunxy05fq
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.d4wephnez5.idunxy05fq
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.eaxjdnb10f.idunxy05fq
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.kixmi0rwyx.idunxy05fq
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.erfb5lzm4e.idunxy05fq
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.ezirojod0l.idunxy05fq
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.iwijz5y4dk.idunxy05fq
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.oaakluhtjp.idunxy05fq
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.ds4gitu0kc.idunxy05fq
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.hzdhzzfctv.idunxy05fq
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.oljsomiosq.jgjntlwrpw
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.npituv3xy0.f5xsicn2zz
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.ghaasdhvrt.jgjntlwrpw
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.i2aolan4xy.f5xsicn2zz
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.h2nzozcowo.jgjntlwrpw
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.j3rnvpxcbc.f5xsicn2zz
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.kspygeeshxd.jgjntlwrpw
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.aygci1b5zn4.f5xsicn2zz
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% efg3yf0kkem.m4qpcq4wpr2.idunxy05fq
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(28) = section;
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
    nTotSects     = 5;
    sectIdxOffset = 28;
    
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
    ;% Auto data (o1zpb2d2p4d)
    ;%
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% o1zpb2d2p4d.ni0j2dmvkt
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% o1zpb2d2p4d.pyqbt0nwcv
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% o1zpb2d2p4d.oy5xzc0nkd
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% o1zpb2d2p4d.p5tvytbxda
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% o1zpb2d2p4d.ant5eero0k
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% o1zpb2d2p4d.mrs4gisuqh
	  section.data(1).logicalSrcIdx = 5;
	  section.data(1).dtTransOffset = 0;
	
	  ;% o1zpb2d2p4d.oggxsmpr34
	  section.data(2).logicalSrcIdx = 6;
	  section.data(2).dtTransOffset = 1;
	
	  ;% o1zpb2d2p4d.fr2q4jozym
	  section.data(3).logicalSrcIdx = 7;
	  section.data(3).dtTransOffset = 2;
	
	  ;% o1zpb2d2p4d.ldo0z4zmg3
	  section.data(4).logicalSrcIdx = 8;
	  section.data(4).dtTransOffset = 3;
	
	  ;% o1zpb2d2p4d.acitmktthx
	  section.data(5).logicalSrcIdx = 9;
	  section.data(5).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% o1zpb2d2p4d.lvfsvmsv3b.LoggedData
	  section.data(1).logicalSrcIdx = 10;
	  section.data(1).dtTransOffset = 0;
	
	  ;% o1zpb2d2p4d.didmnk0lte.LoggedData
	  section.data(2).logicalSrcIdx = 11;
	  section.data(2).dtTransOffset = 1;
	
	  ;% o1zpb2d2p4d.h54z20zfxx.LoggedData
	  section.data(3).logicalSrcIdx = 12;
	  section.data(3).dtTransOffset = 3;
	
	  ;% o1zpb2d2p4d.hc4whpxuyy.LoggedData
	  section.data(4).logicalSrcIdx = 13;
	  section.data(4).dtTransOffset = 4;
	
	  ;% o1zpb2d2p4d.mcbtfqmcfx.LoggedData
	  section.data(5).logicalSrcIdx = 14;
	  section.data(5).dtTransOffset = 5;
	
	  ;% o1zpb2d2p4d.j2t1pfikep.LoggedData
	  section.data(6).logicalSrcIdx = 15;
	  section.data(6).dtTransOffset = 6;
	
	  ;% o1zpb2d2p4d.fqjve1gxux.LoggedData
	  section.data(7).logicalSrcIdx = 16;
	  section.data(7).dtTransOffset = 7;
	
	  ;% o1zpb2d2p4d.onudfxanmw.LoggedData
	  section.data(8).logicalSrcIdx = 17;
	  section.data(8).dtTransOffset = 8;
	
	  ;% o1zpb2d2p4d.isd1kt55gh.LoggedData
	  section.data(9).logicalSrcIdx = 18;
	  section.data(9).dtTransOffset = 9;
	
	  ;% o1zpb2d2p4d.e1db1xagfv.LoggedData
	  section.data(10).logicalSrcIdx = 19;
	  section.data(10).dtTransOffset = 11;
	
	  ;% o1zpb2d2p4d.a3oxdsyoj4.LoggedData
	  section.data(11).logicalSrcIdx = 20;
	  section.data(11).dtTransOffset = 15;
	
	  ;% o1zpb2d2p4d.d2mkf3fff4.LoggedData
	  section.data(12).logicalSrcIdx = 21;
	  section.data(12).dtTransOffset = 18;
	
	  ;% o1zpb2d2p4d.ncdg2ynxyc.LoggedData
	  section.data(13).logicalSrcIdx = 22;
	  section.data(13).dtTransOffset = 20;
	
	  ;% o1zpb2d2p4d.khgucp4dhk.LoggedData
	  section.data(14).logicalSrcIdx = 23;
	  section.data(14).dtTransOffset = 22;
	
	  ;% o1zpb2d2p4d.bqo5itgler.LoggedData
	  section.data(15).logicalSrcIdx = 24;
	  section.data(15).dtTransOffset = 24;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% o1zpb2d2p4d.d4urq1qub2
	  section.data(1).logicalSrcIdx = 25;
	  section.data(1).dtTransOffset = 0;
	
	  ;% o1zpb2d2p4d.lvqjcvz2i5
	  section.data(2).logicalSrcIdx = 26;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 12;
      section.data(12)  = dumData; %prealloc
      
	  ;% o1zpb2d2p4d.nnmzrgywv5
	  section.data(1).logicalSrcIdx = 27;
	  section.data(1).dtTransOffset = 0;
	
	  ;% o1zpb2d2p4d.pacrao3xr0
	  section.data(2).logicalSrcIdx = 28;
	  section.data(2).dtTransOffset = 1;
	
	  ;% o1zpb2d2p4d.b1fq0awd25
	  section.data(3).logicalSrcIdx = 29;
	  section.data(3).dtTransOffset = 2;
	
	  ;% o1zpb2d2p4d.gft25z0qdo
	  section.data(4).logicalSrcIdx = 30;
	  section.data(4).dtTransOffset = 3;
	
	  ;% o1zpb2d2p4d.en54jff4bo
	  section.data(5).logicalSrcIdx = 31;
	  section.data(5).dtTransOffset = 4;
	
	  ;% o1zpb2d2p4d.bcgpss1nan
	  section.data(6).logicalSrcIdx = 32;
	  section.data(6).dtTransOffset = 5;
	
	  ;% o1zpb2d2p4d.iuboi3qrhj
	  section.data(7).logicalSrcIdx = 33;
	  section.data(7).dtTransOffset = 6;
	
	  ;% o1zpb2d2p4d.j2jcdwwefo
	  section.data(8).logicalSrcIdx = 34;
	  section.data(8).dtTransOffset = 7;
	
	  ;% o1zpb2d2p4d.elldto2m5j
	  section.data(9).logicalSrcIdx = 35;
	  section.data(9).dtTransOffset = 8;
	
	  ;% o1zpb2d2p4d.pecubnlofk
	  section.data(10).logicalSrcIdx = 36;
	  section.data(10).dtTransOffset = 9;
	
	  ;% o1zpb2d2p4d.iyhuag24od
	  section.data(11).logicalSrcIdx = 37;
	  section.data(11).dtTransOffset = 10;
	
	  ;% o1zpb2d2p4d.enmoxxy3yx
	  section.data(12).logicalSrcIdx = 38;
	  section.data(12).dtTransOffset = 11;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
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


  targMap.checksum0 = 1699688787;
  targMap.checksum1 = 1055233492;
  targMap.checksum2 = 897736183;
  targMap.checksum3 = 1510604557;

