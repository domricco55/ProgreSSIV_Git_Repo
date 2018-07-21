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
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% of4bvhuzsv.FixPtBitwiseOperator1_BitMask
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_gkrh0sae3i
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_e1pefu4111
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_odg5eaiqmz
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_gffhdlcxmr
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_de33jfbtml
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_oqe3n5b5r3
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_crol5h4hkl
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_n1u0kaiggj
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_cwjj4tzqea
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% of4bvhuzsv.FixPtBitwiseOperator_phacg3e2ix
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 18;
      section.data(18)  = dumData; %prealloc
      
	  ;% of4bvhuzsv.Constant_Value
	  section.data(1).logicalSrcIdx = 11;
	  section.data(1).dtTransOffset = 0;
	
	  ;% of4bvhuzsv.SmallDeadZoneForSafety_Start
	  section.data(2).logicalSrcIdx = 12;
	  section.data(2).dtTransOffset = 1;
	
	  ;% of4bvhuzsv.SmallDeadZoneForSafety_End
	  section.data(3).logicalSrcIdx = 13;
	  section.data(3).dtTransOffset = 2;
	
	  ;% of4bvhuzsv.AccelerationInttoDoubleScaleFac
	  section.data(4).logicalSrcIdx = 14;
	  section.data(4).dtTransOffset = 3;
	
	  ;% of4bvhuzsv.GyroscopeInttoDoubleScaleFactor
	  section.data(5).logicalSrcIdx = 15;
	  section.data(5).dtTransOffset = 4;
	
	  ;% of4bvhuzsv.AccelerationInttoDou_b0ntazn1ry
	  section.data(6).logicalSrcIdx = 16;
	  section.data(6).dtTransOffset = 5;
	
	  ;% of4bvhuzsv.GyroscopeInttoDouble_pv021dpztd
	  section.data(7).logicalSrcIdx = 17;
	  section.data(7).dtTransOffset = 6;
	
	  ;% of4bvhuzsv.AccelerationInttoDou_p4tdvqbeab
	  section.data(8).logicalSrcIdx = 18;
	  section.data(8).dtTransOffset = 7;
	
	  ;% of4bvhuzsv.GyroscopeInttoDouble_l25th2m0ko
	  section.data(9).logicalSrcIdx = 19;
	  section.data(9).dtTransOffset = 8;
	
	  ;% of4bvhuzsv.EulerInttoDoubleScaleFactor_Gai
	  section.data(10).logicalSrcIdx = 20;
	  section.data(10).dtTransOffset = 9;
	
	  ;% of4bvhuzsv.EulerInttoDoubleScal_ixdtgj3bni
	  section.data(11).logicalSrcIdx = 21;
	  section.data(11).dtTransOffset = 10;
	
	  ;% of4bvhuzsv.EulerInttoDoubleScal_nev1xqtvdv
	  section.data(12).logicalSrcIdx = 22;
	  section.data(12).dtTransOffset = 11;
	
	  ;% of4bvhuzsv.Constant1_Value
	  section.data(13).logicalSrcIdx = 23;
	  section.data(13).dtTransOffset = 12;
	
	  ;% of4bvhuzsv.Constant_Value_k4pvabrprp
	  section.data(14).logicalSrcIdx = 24;
	  section.data(14).dtTransOffset = 13;
	
	  ;% of4bvhuzsv.Constant2_Value
	  section.data(15).logicalSrcIdx = 25;
	  section.data(15).dtTransOffset = 14;
	
	  ;% of4bvhuzsv.Constant4_Value
	  section.data(16).logicalSrcIdx = 26;
	  section.data(16).dtTransOffset = 15;
	
	  ;% of4bvhuzsv.Constant3_Value
	  section.data(17).logicalSrcIdx = 27;
	  section.data(17).dtTransOffset = 16;
	
	  ;% of4bvhuzsv.Constant5_Value
	  section.data(18).logicalSrcIdx = 28;
	  section.data(18).dtTransOffset = 17;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 52;
      section.data(52)  = dumData; %prealloc
      
	  ;% of4bvhuzsv.euler_headingAddressNumber_Valu
	  section.data(1).logicalSrcIdx = 29;
	  section.data(1).dtTransOffset = 0;
	
	  ;% of4bvhuzsv.uint8_t1_Value
	  section.data(2).logicalSrcIdx = 30;
	  section.data(2).dtTransOffset = 1;
	
	  ;% of4bvhuzsv.uint8_t2_Value
	  section.data(3).logicalSrcIdx = 31;
	  section.data(3).dtTransOffset = 2;
	
	  ;% of4bvhuzsv.uint8_t3_Value
	  section.data(4).logicalSrcIdx = 32;
	  section.data(4).dtTransOffset = 3;
	
	  ;% of4bvhuzsv.euler_rollAddressNumber_Value
	  section.data(5).logicalSrcIdx = 33;
	  section.data(5).dtTransOffset = 4;
	
	  ;% of4bvhuzsv.uint8_t1_Value_ab3z4lzbyh
	  section.data(6).logicalSrcIdx = 34;
	  section.data(6).dtTransOffset = 5;
	
	  ;% of4bvhuzsv.uint8_t2_Value_owbcgov1vj
	  section.data(7).logicalSrcIdx = 35;
	  section.data(7).dtTransOffset = 6;
	
	  ;% of4bvhuzsv.uint8_t3_Value_beyvx2ni4z
	  section.data(8).logicalSrcIdx = 36;
	  section.data(8).dtTransOffset = 7;
	
	  ;% of4bvhuzsv.euler_pitchAddressNumber_Value
	  section.data(9).logicalSrcIdx = 37;
	  section.data(9).dtTransOffset = 8;
	
	  ;% of4bvhuzsv.uint8_t1_Value_ekb21cf5ed
	  section.data(10).logicalSrcIdx = 38;
	  section.data(10).dtTransOffset = 9;
	
	  ;% of4bvhuzsv.uint8_t2_Value_hazd5tqbaw
	  section.data(11).logicalSrcIdx = 39;
	  section.data(11).dtTransOffset = 10;
	
	  ;% of4bvhuzsv.uint8_t3_Value_pnt2y4c2x2
	  section.data(12).logicalSrcIdx = 40;
	  section.data(12).dtTransOffset = 11;
	
	  ;% of4bvhuzsv.gyr_xAddressNumber_Value
	  section.data(13).logicalSrcIdx = 41;
	  section.data(13).dtTransOffset = 12;
	
	  ;% of4bvhuzsv.uint8_t1_Value_m5vrdd0lhv
	  section.data(14).logicalSrcIdx = 42;
	  section.data(14).dtTransOffset = 13;
	
	  ;% of4bvhuzsv.uint8_t2_Value_cx2bvcgjid
	  section.data(15).logicalSrcIdx = 43;
	  section.data(15).dtTransOffset = 14;
	
	  ;% of4bvhuzsv.uint8_t3_Value_dk431xz04t
	  section.data(16).logicalSrcIdx = 44;
	  section.data(16).dtTransOffset = 15;
	
	  ;% of4bvhuzsv.acc_xAddressNumber_Value
	  section.data(17).logicalSrcIdx = 45;
	  section.data(17).dtTransOffset = 16;
	
	  ;% of4bvhuzsv.uint8_t1_Value_hfjdanjjuo
	  section.data(18).logicalSrcIdx = 46;
	  section.data(18).dtTransOffset = 17;
	
	  ;% of4bvhuzsv.uint8_t2_Value_ep2d2khvam
	  section.data(19).logicalSrcIdx = 47;
	  section.data(19).dtTransOffset = 18;
	
	  ;% of4bvhuzsv.uint8_t3_Value_hw231mmgoy
	  section.data(20).logicalSrcIdx = 48;
	  section.data(20).dtTransOffset = 19;
	
	  ;% of4bvhuzsv.gyr_yAddressNumber_Value
	  section.data(21).logicalSrcIdx = 49;
	  section.data(21).dtTransOffset = 20;
	
	  ;% of4bvhuzsv.uint8_t1_Value_baa1n3n0vz
	  section.data(22).logicalSrcIdx = 50;
	  section.data(22).dtTransOffset = 21;
	
	  ;% of4bvhuzsv.uint8_t2_Value_a1qknq4gqc
	  section.data(23).logicalSrcIdx = 51;
	  section.data(23).dtTransOffset = 22;
	
	  ;% of4bvhuzsv.uint8_t3_Value_nsbd5lluip
	  section.data(24).logicalSrcIdx = 52;
	  section.data(24).dtTransOffset = 23;
	
	  ;% of4bvhuzsv.acc_yAddressNumber_Value
	  section.data(25).logicalSrcIdx = 53;
	  section.data(25).dtTransOffset = 24;
	
	  ;% of4bvhuzsv.uint8_t1_Value_f5jgk2qlyk
	  section.data(26).logicalSrcIdx = 54;
	  section.data(26).dtTransOffset = 25;
	
	  ;% of4bvhuzsv.uint8_t2_Value_jbpmt5j5su
	  section.data(27).logicalSrcIdx = 55;
	  section.data(27).dtTransOffset = 26;
	
	  ;% of4bvhuzsv.uint8_t3_Value_kff1fcwqkp
	  section.data(28).logicalSrcIdx = 56;
	  section.data(28).dtTransOffset = 27;
	
	  ;% of4bvhuzsv.gyr_zAddressNumber_Value
	  section.data(29).logicalSrcIdx = 57;
	  section.data(29).dtTransOffset = 28;
	
	  ;% of4bvhuzsv.uint8_t1_Value_bfivb3q1dl
	  section.data(30).logicalSrcIdx = 58;
	  section.data(30).dtTransOffset = 29;
	
	  ;% of4bvhuzsv.uint8_t2_Value_hjxx0o2vjq
	  section.data(31).logicalSrcIdx = 59;
	  section.data(31).dtTransOffset = 30;
	
	  ;% of4bvhuzsv.uint8_t3_Value_mm1shkpugw
	  section.data(32).logicalSrcIdx = 60;
	  section.data(32).dtTransOffset = 31;
	
	  ;% of4bvhuzsv.acc_zAddressNumber_Value
	  section.data(33).logicalSrcIdx = 61;
	  section.data(33).dtTransOffset = 32;
	
	  ;% of4bvhuzsv.uint8_t1_Value_petzhq1hd3
	  section.data(34).logicalSrcIdx = 62;
	  section.data(34).dtTransOffset = 33;
	
	  ;% of4bvhuzsv.uint8_t2_Value_b155xgcwwv
	  section.data(35).logicalSrcIdx = 63;
	  section.data(35).dtTransOffset = 34;
	
	  ;% of4bvhuzsv.uint8_t3_Value_luwir55sww
	  section.data(36).logicalSrcIdx = 64;
	  section.data(36).dtTransOffset = 35;
	
	  ;% of4bvhuzsv.radio_throttleAddressNumber_Val
	  section.data(37).logicalSrcIdx = 65;
	  section.data(37).dtTransOffset = 36;
	
	  ;% of4bvhuzsv.uint8_t1_Value_fnynggjy15
	  section.data(38).logicalSrcIdx = 66;
	  section.data(38).dtTransOffset = 37;
	
	  ;% of4bvhuzsv.uint8_t2_Value_ceciclldde
	  section.data(39).logicalSrcIdx = 67;
	  section.data(39).dtTransOffset = 38;
	
	  ;% of4bvhuzsv.uint8_t3_Value_c5o2g1e4ji
	  section.data(40).logicalSrcIdx = 68;
	  section.data(40).dtTransOffset = 39;
	
	  ;% of4bvhuzsv.radio_steeringAddressNumber_Val
	  section.data(41).logicalSrcIdx = 69;
	  section.data(41).dtTransOffset = 40;
	
	  ;% of4bvhuzsv.uint8_t1_Value_mlrdk44dlr
	  section.data(42).logicalSrcIdx = 70;
	  section.data(42).dtTransOffset = 41;
	
	  ;% of4bvhuzsv.uint8_t2_Value_cchlr1qlpg
	  section.data(43).logicalSrcIdx = 71;
	  section.data(43).dtTransOffset = 42;
	
	  ;% of4bvhuzsv.uint8_t3_Value_bhpkuwxhlv
	  section.data(44).logicalSrcIdx = 72;
	  section.data(44).dtTransOffset = 43;
	
	  ;% of4bvhuzsv.DeadSwitch_Value
	  section.data(45).logicalSrcIdx = 73;
	  section.data(45).dtTransOffset = 44;
	
	  ;% of4bvhuzsv.TakeData_Value
	  section.data(46).logicalSrcIdx = 74;
	  section.data(46).dtTransOffset = 45;
	
	  ;% of4bvhuzsv.ServoandRadioOn_Value
	  section.data(47).logicalSrcIdx = 75;
	  section.data(47).dtTransOffset = 46;
	
	  ;% of4bvhuzsv.MotorControllersOn_Value
	  section.data(48).logicalSrcIdx = 76;
	  section.data(48).dtTransOffset = 47;
	
	  ;% of4bvhuzsv.IMUReset_Value
	  section.data(49).logicalSrcIdx = 77;
	  section.data(49).dtTransOffset = 48;
	
	  ;% of4bvhuzsv.PrinttheregistermapontheTeensy_
	  section.data(50).logicalSrcIdx = 78;
	  section.data(50).dtTransOffset = 49;
	
	  ;% of4bvhuzsv.PrinttheimudataontheTeensy_Valu
	  section.data(51).logicalSrcIdx = 79;
	  section.data(51).dtTransOffset = 50;
	
	  ;% of4bvhuzsv.Printtheradiotranceiverdataonth
	  section.data(52).logicalSrcIdx = 80;
	  section.data(52).dtTransOffset = 51;
	
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
    ;% Auto data (egmb1woemnz)
    ;%
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% egmb1woemnz.dizmaqw4wv
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% egmb1woemnz.ah1wccj0hb
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% egmb1woemnz.i1d5pjzzrk
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% egmb1woemnz.mcrhfteyw1
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% egmb1woemnz.eg4bjnhlbm
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% egmb1woemnz.abnbwzveq1
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% egmb1woemnz.meap5t3xvy
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% egmb1woemnz.mdn1ox2vnu
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% egmb1woemnz.kvnaau3bof
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% egmb1woemnz.p4ufcbqlsf
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% egmb1woemnz.gfubs2qpjy
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% egmb1woemnz.nvepg203g0
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% egmb1woemnz.dpj3e2rl0l
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% egmb1woemnz.gvmg1qccb3
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
	  ;% egmb1woemnz.brsaunpczh
	  section.data(2).logicalSrcIdx = 14;
	  section.data(2).dtTransOffset = 1;
	
	  ;% egmb1woemnz.lwrcj2i15g
	  section.data(3).logicalSrcIdx = 15;
	  section.data(3).dtTransOffset = 2;
	
	  ;% egmb1woemnz.akwe05vquc
	  section.data(4).logicalSrcIdx = 16;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% egmb1woemnz.dasom0iuc4
	  section.data(1).logicalSrcIdx = 17;
	  section.data(1).dtTransOffset = 0;
	
	  ;% egmb1woemnz.orbydnpnuc
	  section.data(2).logicalSrcIdx = 18;
	  section.data(2).dtTransOffset = 1;
	
	  ;% egmb1woemnz.b0gf0kpizg
	  section.data(3).logicalSrcIdx = 19;
	  section.data(3).dtTransOffset = 2;
	
	  ;% egmb1woemnz.ald455nrar
	  section.data(4).logicalSrcIdx = 20;
	  section.data(4).dtTransOffset = 3;
	
	  ;% egmb1woemnz.minzuf0qnk
	  section.data(5).logicalSrcIdx = 21;
	  section.data(5).dtTransOffset = 4;
	
	  ;% egmb1woemnz.m10uyypppj
	  section.data(6).logicalSrcIdx = 22;
	  section.data(6).dtTransOffset = 5;
	
	  ;% egmb1woemnz.ao5unspa12
	  section.data(7).logicalSrcIdx = 23;
	  section.data(7).dtTransOffset = 6;
	
	  ;% egmb1woemnz.olxdp2jbgt
	  section.data(8).logicalSrcIdx = 24;
	  section.data(8).dtTransOffset = 7;
	
	  ;% egmb1woemnz.mzrcel25aj
	  section.data(9).logicalSrcIdx = 25;
	  section.data(9).dtTransOffset = 8;
	
	  ;% egmb1woemnz.efbsdn54ab
	  section.data(10).logicalSrcIdx = 26;
	  section.data(10).dtTransOffset = 10;
	
	  ;% egmb1woemnz.fzdpsrqgns
	  section.data(11).logicalSrcIdx = 27;
	  section.data(11).dtTransOffset = 12;
	
	  ;% egmb1woemnz.jghajepyfr
	  section.data(12).logicalSrcIdx = 28;
	  section.data(12).dtTransOffset = 14;
	
	  ;% egmb1woemnz.cinlx0zlh0
	  section.data(13).logicalSrcIdx = 29;
	  section.data(13).dtTransOffset = 16;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.py2aqyzvgp.eelxesskbk
	  section.data(1).logicalSrcIdx = 30;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.ljd3cccyx0.jv43yy50fr
	  section.data(1).logicalSrcIdx = 31;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.ogumhmbm4q.eelxesskbk
	  section.data(1).logicalSrcIdx = 32;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.f4igx0h30u.jv43yy50fr
	  section.data(1).logicalSrcIdx = 33;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.aagok5grcz.eelxesskbk
	  section.data(1).logicalSrcIdx = 34;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.oh3tmdutyn.jv43yy50fr
	  section.data(1).logicalSrcIdx = 35;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.lwojjodbhe.eelxesskbk
	  section.data(1).logicalSrcIdx = 36;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.prfj5mwafd.jv43yy50fr
	  section.data(1).logicalSrcIdx = 37;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.nswf4ykjydl.eelxesskbk
	  section.data(1).logicalSrcIdx = 38;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.jazxi5h0zh3.jv43yy50fr
	  section.data(1).logicalSrcIdx = 39;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.jyqgjadvdv.cgmoekimxn
	  section.data(1).logicalSrcIdx = 40;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.accayiv5yz.cgmoekimxn
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.d021klicdc.cgmoekimxn
	  section.data(1).logicalSrcIdx = 42;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.i0glmla3mt.cgmoekimxn
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.d25hv52xcl.cgmoekimxn
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.m0rmlqepf2.cgmoekimxn
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.a34o2ccni2.cgmoekimxn
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.kezb0zns1j.cgmoekimxn
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.abeakyzthv.cgmoekimxn
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.pvbhtciekv.cgmoekimxn
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.opaqa4uf1r3.cgmoekimxn
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.jjwbdm32dt.bed2whhgom
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.ap5o1ljg5p.bed2whhgom
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.ntpnjgaxbk.bed2whhgom
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.ltp5v1qb5p.bed2whhgom
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.dhd2bo1xvw.bed2whhgom
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.jvot4d0aks.bed2whhgom
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.addnvjrs50.bed2whhgom
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.bmuonaufob.bed2whhgom
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.dy5xffgu1e.bed2whhgom
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.jei05f3f2n.bed2whhgom
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(34) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% egmb1woemnz.c4w4mthusce.bed2whhgom
	  section.data(1).logicalSrcIdx = 61;
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
	
	  ;% khgsjmcu2zh.ci0oed1q2t
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% khgsjmcu2zh.azmlhjjbeh
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% khgsjmcu2zh.ldxq35z15s
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% khgsjmcu2zh.jjcxbomfb1
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% khgsjmcu2zh.iwwehkf4qo
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ekz5ohvfzj.LoggedData
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
	  ;% khgsjmcu2zh.jd343gxwrq.LoggedData
	  section.data(2).logicalSrcIdx = 14;
	  section.data(2).dtTransOffset = 1;
	
	  ;% khgsjmcu2zh.f0h3hq0wzv.LoggedData
	  section.data(3).logicalSrcIdx = 15;
	  section.data(3).dtTransOffset = 2;
	
	  ;% khgsjmcu2zh.hsokbbw12b.LoggedData
	  section.data(4).logicalSrcIdx = 16;
	  section.data(4).dtTransOffset = 3;
	
	  ;% khgsjmcu2zh.ni5wgnjpzl.LoggedData
	  section.data(5).logicalSrcIdx = 17;
	  section.data(5).dtTransOffset = 5;
	
	  ;% khgsjmcu2zh.eic1rvie00.LoggedData
	  section.data(6).logicalSrcIdx = 18;
	  section.data(6).dtTransOffset = 7;
	
	  ;% khgsjmcu2zh.d04ec25tl0.LoggedData
	  section.data(7).logicalSrcIdx = 19;
	  section.data(7).dtTransOffset = 9;
	
	  ;% khgsjmcu2zh.eryrtxuhs5.LoggedData
	  section.data(8).logicalSrcIdx = 20;
	  section.data(8).dtTransOffset = 11;
	
	  ;% khgsjmcu2zh.cuhz4vep2r.LoggedData
	  section.data(9).logicalSrcIdx = 21;
	  section.data(9).dtTransOffset = 14;
	
	  ;% khgsjmcu2zh.m5ti3l5xpa.LoggedData
	  section.data(10).logicalSrcIdx = 22;
	  section.data(10).dtTransOffset = 15;
	
	  ;% khgsjmcu2zh.c4hl1sbblu.LoggedData
	  section.data(11).logicalSrcIdx = 23;
	  section.data(11).dtTransOffset = 16;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.a5vniid1mf
	  section.data(1).logicalSrcIdx = 24;
	  section.data(1).dtTransOffset = 0;
	
	  ;% khgsjmcu2zh.gwm13mwotc
	  section.data(2).logicalSrcIdx = 25;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ghn2nojvif
	  section.data(1).logicalSrcIdx = 26;
	  section.data(1).dtTransOffset = 0;
	
	  ;% khgsjmcu2zh.ihdwydbhnm
	  section.data(2).logicalSrcIdx = 27;
	  section.data(2).dtTransOffset = 1;
	
	  ;% khgsjmcu2zh.irk2ylhvxt
	  section.data(3).logicalSrcIdx = 28;
	  section.data(3).dtTransOffset = 2;
	
	  ;% khgsjmcu2zh.jtqm1njr1g
	  section.data(4).logicalSrcIdx = 29;
	  section.data(4).dtTransOffset = 3;
	
	  ;% khgsjmcu2zh.f1zj5fzhjo
	  section.data(5).logicalSrcIdx = 30;
	  section.data(5).dtTransOffset = 4;
	
	  ;% khgsjmcu2zh.ljodvfojqz
	  section.data(6).logicalSrcIdx = 31;
	  section.data(6).dtTransOffset = 5;
	
	  ;% khgsjmcu2zh.g514tpjtzd
	  section.data(7).logicalSrcIdx = 32;
	  section.data(7).dtTransOffset = 6;
	
	  ;% khgsjmcu2zh.mginnteowg
	  section.data(8).logicalSrcIdx = 33;
	  section.data(8).dtTransOffset = 7;
	
	  ;% khgsjmcu2zh.iad2ku4q53
	  section.data(9).logicalSrcIdx = 34;
	  section.data(9).dtTransOffset = 8;
	
	  ;% khgsjmcu2zh.k2tg013slg
	  section.data(10).logicalSrcIdx = 35;
	  section.data(10).dtTransOffset = 9;
	
	  ;% khgsjmcu2zh.ghu4c41cfb
	  section.data(11).logicalSrcIdx = 36;
	  section.data(11).dtTransOffset = 10;
	
	  ;% khgsjmcu2zh.g5bngbixma
	  section.data(12).logicalSrcIdx = 37;
	  section.data(12).dtTransOffset = 11;
	
	  ;% khgsjmcu2zh.e1ee3btecf
	  section.data(13).logicalSrcIdx = 38;
	  section.data(13).dtTransOffset = 12;
	
	  ;% khgsjmcu2zh.azxeehreyh
	  section.data(14).logicalSrcIdx = 39;
	  section.data(14).dtTransOffset = 13;
	
	  ;% khgsjmcu2zh.g313j543ib
	  section.data(15).logicalSrcIdx = 40;
	  section.data(15).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.jjwbdm32dt.nwkv0yox3d
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.jjwbdm32dt.mvxxrbnpsa
	  section.data(1).logicalSrcIdx = 42;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ap5o1ljg5p.nwkv0yox3d
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ap5o1ljg5p.mvxxrbnpsa
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ntpnjgaxbk.nwkv0yox3d
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ntpnjgaxbk.mvxxrbnpsa
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ltp5v1qb5p.nwkv0yox3d
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.ltp5v1qb5p.mvxxrbnpsa
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.dhd2bo1xvw.nwkv0yox3d
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.dhd2bo1xvw.mvxxrbnpsa
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.jvot4d0aks.nwkv0yox3d
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.jvot4d0aks.mvxxrbnpsa
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.addnvjrs50.nwkv0yox3d
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.addnvjrs50.mvxxrbnpsa
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.bmuonaufob.nwkv0yox3d
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.bmuonaufob.mvxxrbnpsa
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.dy5xffgu1e.nwkv0yox3d
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.dy5xffgu1e.mvxxrbnpsa
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.jei05f3f2n.nwkv0yox3d
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.jei05f3f2n.mvxxrbnpsa
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.c4w4mthusce.nwkv0yox3d
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% khgsjmcu2zh.c4w4mthusce.mvxxrbnpsa
	  section.data(1).logicalSrcIdx = 62;
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


  targMap.checksum0 = 1859188763;
  targMap.checksum1 = 3865597049;
  targMap.checksum2 = 3062547647;
  targMap.checksum3 = 2036881;

