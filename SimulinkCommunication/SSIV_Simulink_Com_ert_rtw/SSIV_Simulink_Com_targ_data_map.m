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
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% audekaprdr.FixPtBitwiseOperator1_BitMask
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% audekaprdr.FixPtBitwiseOperator_as2k3qplyw
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% audekaprdr.FixPtBitwiseOperator_nkfjnteeeq
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% audekaprdr.FixPtBitwiseOperator_j5xa4hxjcc
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% audekaprdr.FixPtBitwiseOperator_n3ticzbm0w
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% audekaprdr.FixPtBitwiseOperator_mkysc30z34
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% audekaprdr.FixPtBitwiseOperator_ofi0bcjw10
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% audekaprdr.FixPtBitwiseOperator_hsop4wqw3h
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% audekaprdr.FixPtBitwiseOperator_nltvqamzzv
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% audekaprdr.FixPtBitwiseOperator_kmc03sgzj0
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% audekaprdr.FixPtBitwiseOperator_gd2bxfln3i
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 21;
      section.data(21)  = dumData; %prealloc
      
	  ;% audekaprdr._Value
	  section.data(1).logicalSrcIdx = 11;
	  section.data(1).dtTransOffset = 0;
	
	  ;% audekaprdr.ConstMotVel_Value
	  section.data(2).logicalSrcIdx = 12;
	  section.data(2).dtTransOffset = 1;
	
	  ;% audekaprdr.DeadSwitchValue_Value
	  section.data(3).logicalSrcIdx = 13;
	  section.data(3).dtTransOffset = 2;
	
	  ;% audekaprdr.AccelerationInttoDoubleScaleFac
	  section.data(4).logicalSrcIdx = 14;
	  section.data(4).dtTransOffset = 3;
	
	  ;% audekaprdr.GyroscopeInttoDoubleScaleFactor
	  section.data(5).logicalSrcIdx = 15;
	  section.data(5).dtTransOffset = 4;
	
	  ;% audekaprdr.AccelerationInttoDou_h2nh03n513
	  section.data(6).logicalSrcIdx = 16;
	  section.data(6).dtTransOffset = 5;
	
	  ;% audekaprdr.GyroscopeInttoDouble_hw2tyfthn4
	  section.data(7).logicalSrcIdx = 17;
	  section.data(7).dtTransOffset = 6;
	
	  ;% audekaprdr.AccelerationInttoDou_hkwjyt2xjk
	  section.data(8).logicalSrcIdx = 18;
	  section.data(8).dtTransOffset = 7;
	
	  ;% audekaprdr.GyroscopeInttoDouble_dt33lrcogy
	  section.data(9).logicalSrcIdx = 19;
	  section.data(9).dtTransOffset = 8;
	
	  ;% audekaprdr.EulerInttoDoubleScaleFactor_Gai
	  section.data(10).logicalSrcIdx = 20;
	  section.data(10).dtTransOffset = 9;
	
	  ;% audekaprdr.FlippingSignConvention2_Gain
	  section.data(11).logicalSrcIdx = 21;
	  section.data(11).dtTransOffset = 10;
	
	  ;% audekaprdr.EulerInttoDoubleScal_lopujqi4cg
	  section.data(12).logicalSrcIdx = 22;
	  section.data(12).dtTransOffset = 11;
	
	  ;% audekaprdr.FlippingSignConvention_Gain
	  section.data(13).logicalSrcIdx = 23;
	  section.data(13).dtTransOffset = 12;
	
	  ;% audekaprdr.EulerInttoDoubleScal_nw21yceloc
	  section.data(14).logicalSrcIdx = 24;
	  section.data(14).dtTransOffset = 13;
	
	  ;% audekaprdr.FlippingSignConvention1_Gain
	  section.data(15).logicalSrcIdx = 25;
	  section.data(15).dtTransOffset = 14;
	
	  ;% audekaprdr.Constant1_Value
	  section.data(16).logicalSrcIdx = 26;
	  section.data(16).dtTransOffset = 15;
	
	  ;% audekaprdr.Constant_Value
	  section.data(17).logicalSrcIdx = 27;
	  section.data(17).dtTransOffset = 16;
	
	  ;% audekaprdr.Constant2_Value
	  section.data(18).logicalSrcIdx = 28;
	  section.data(18).dtTransOffset = 17;
	
	  ;% audekaprdr.Constant4_Value
	  section.data(19).logicalSrcIdx = 29;
	  section.data(19).dtTransOffset = 18;
	
	  ;% audekaprdr.Constant3_Value
	  section.data(20).logicalSrcIdx = 30;
	  section.data(20).dtTransOffset = 19;
	
	  ;% audekaprdr.Constant5_Value
	  section.data(21).logicalSrcIdx = 31;
	  section.data(21).dtTransOffset = 20;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 52;
      section.data(52)  = dumData; %prealloc
      
	  ;% audekaprdr.euler_headingAddressNumber_Valu
	  section.data(1).logicalSrcIdx = 32;
	  section.data(1).dtTransOffset = 0;
	
	  ;% audekaprdr.uint8_t1_Value
	  section.data(2).logicalSrcIdx = 33;
	  section.data(2).dtTransOffset = 1;
	
	  ;% audekaprdr.uint8_t2_Value
	  section.data(3).logicalSrcIdx = 34;
	  section.data(3).dtTransOffset = 2;
	
	  ;% audekaprdr.uint8_t3_Value
	  section.data(4).logicalSrcIdx = 35;
	  section.data(4).dtTransOffset = 3;
	
	  ;% audekaprdr.euler_rollAddressNumber_Value
	  section.data(5).logicalSrcIdx = 36;
	  section.data(5).dtTransOffset = 4;
	
	  ;% audekaprdr.uint8_t1_Value_bnexk0rvdq
	  section.data(6).logicalSrcIdx = 37;
	  section.data(6).dtTransOffset = 5;
	
	  ;% audekaprdr.uint8_t2_Value_gn4ieal2dy
	  section.data(7).logicalSrcIdx = 38;
	  section.data(7).dtTransOffset = 6;
	
	  ;% audekaprdr.uint8_t3_Value_i0fec1wvc1
	  section.data(8).logicalSrcIdx = 39;
	  section.data(8).dtTransOffset = 7;
	
	  ;% audekaprdr.euler_pitchAddressNumber_Value
	  section.data(9).logicalSrcIdx = 40;
	  section.data(9).dtTransOffset = 8;
	
	  ;% audekaprdr.uint8_t1_Value_ndti5ul2ir
	  section.data(10).logicalSrcIdx = 41;
	  section.data(10).dtTransOffset = 9;
	
	  ;% audekaprdr.uint8_t2_Value_lqvuywxu0i
	  section.data(11).logicalSrcIdx = 42;
	  section.data(11).dtTransOffset = 10;
	
	  ;% audekaprdr.uint8_t3_Value_lepgvl4yvs
	  section.data(12).logicalSrcIdx = 43;
	  section.data(12).dtTransOffset = 11;
	
	  ;% audekaprdr.gyr_xAddressNumber_Value
	  section.data(13).logicalSrcIdx = 44;
	  section.data(13).dtTransOffset = 12;
	
	  ;% audekaprdr.uint8_t1_Value_kdkvzqxzai
	  section.data(14).logicalSrcIdx = 45;
	  section.data(14).dtTransOffset = 13;
	
	  ;% audekaprdr.uint8_t2_Value_fjb5jcvryv
	  section.data(15).logicalSrcIdx = 46;
	  section.data(15).dtTransOffset = 14;
	
	  ;% audekaprdr.uint8_t3_Value_olsuwridav
	  section.data(16).logicalSrcIdx = 47;
	  section.data(16).dtTransOffset = 15;
	
	  ;% audekaprdr.acc_xAddressNumber_Value
	  section.data(17).logicalSrcIdx = 48;
	  section.data(17).dtTransOffset = 16;
	
	  ;% audekaprdr.uint8_t1_Value_cxtxrspyx2
	  section.data(18).logicalSrcIdx = 49;
	  section.data(18).dtTransOffset = 17;
	
	  ;% audekaprdr.uint8_t2_Value_cnehq0fw23
	  section.data(19).logicalSrcIdx = 50;
	  section.data(19).dtTransOffset = 18;
	
	  ;% audekaprdr.uint8_t3_Value_pdglhcrw0d
	  section.data(20).logicalSrcIdx = 51;
	  section.data(20).dtTransOffset = 19;
	
	  ;% audekaprdr.gyr_yAddressNumber_Value
	  section.data(21).logicalSrcIdx = 52;
	  section.data(21).dtTransOffset = 20;
	
	  ;% audekaprdr.uint8_t1_Value_cm2c0avpfj
	  section.data(22).logicalSrcIdx = 53;
	  section.data(22).dtTransOffset = 21;
	
	  ;% audekaprdr.uint8_t2_Value_lvoif2jzzk
	  section.data(23).logicalSrcIdx = 54;
	  section.data(23).dtTransOffset = 22;
	
	  ;% audekaprdr.uint8_t3_Value_mtqeqchjq3
	  section.data(24).logicalSrcIdx = 55;
	  section.data(24).dtTransOffset = 23;
	
	  ;% audekaprdr.acc_yAddressNumber_Value
	  section.data(25).logicalSrcIdx = 56;
	  section.data(25).dtTransOffset = 24;
	
	  ;% audekaprdr.uint8_t1_Value_olo0yfbjbp
	  section.data(26).logicalSrcIdx = 57;
	  section.data(26).dtTransOffset = 25;
	
	  ;% audekaprdr.uint8_t2_Value_clw2lo3chi
	  section.data(27).logicalSrcIdx = 58;
	  section.data(27).dtTransOffset = 26;
	
	  ;% audekaprdr.uint8_t3_Value_dydix2zbx3
	  section.data(28).logicalSrcIdx = 59;
	  section.data(28).dtTransOffset = 27;
	
	  ;% audekaprdr.gyr_zAddressNumber_Value
	  section.data(29).logicalSrcIdx = 60;
	  section.data(29).dtTransOffset = 28;
	
	  ;% audekaprdr.uint8_t1_Value_fvslqcrdl2
	  section.data(30).logicalSrcIdx = 61;
	  section.data(30).dtTransOffset = 29;
	
	  ;% audekaprdr.uint8_t2_Value_lsv0pyia0r
	  section.data(31).logicalSrcIdx = 62;
	  section.data(31).dtTransOffset = 30;
	
	  ;% audekaprdr.uint8_t3_Value_ddvup1twb3
	  section.data(32).logicalSrcIdx = 63;
	  section.data(32).dtTransOffset = 31;
	
	  ;% audekaprdr.acc_zAddressNumber_Value
	  section.data(33).logicalSrcIdx = 64;
	  section.data(33).dtTransOffset = 32;
	
	  ;% audekaprdr.uint8_t1_Value_bfs2kyqhyj
	  section.data(34).logicalSrcIdx = 65;
	  section.data(34).dtTransOffset = 33;
	
	  ;% audekaprdr.uint8_t2_Value_p1gsoflfkl
	  section.data(35).logicalSrcIdx = 66;
	  section.data(35).dtTransOffset = 34;
	
	  ;% audekaprdr.uint8_t3_Value_jkgzprijvo
	  section.data(36).logicalSrcIdx = 67;
	  section.data(36).dtTransOffset = 35;
	
	  ;% audekaprdr.radio_throttleAddressNumber_Val
	  section.data(37).logicalSrcIdx = 68;
	  section.data(37).dtTransOffset = 36;
	
	  ;% audekaprdr.uint8_t1_Value_fzct0d4u4r
	  section.data(38).logicalSrcIdx = 69;
	  section.data(38).dtTransOffset = 37;
	
	  ;% audekaprdr.uint8_t2_Value_fs3jntlocd
	  section.data(39).logicalSrcIdx = 70;
	  section.data(39).dtTransOffset = 38;
	
	  ;% audekaprdr.uint8_t3_Value_lxeky0iln5
	  section.data(40).logicalSrcIdx = 71;
	  section.data(40).dtTransOffset = 39;
	
	  ;% audekaprdr.radio_steeringAddressNumber_Val
	  section.data(41).logicalSrcIdx = 72;
	  section.data(41).dtTransOffset = 40;
	
	  ;% audekaprdr.uint8_t1_Value_ju0tizjign
	  section.data(42).logicalSrcIdx = 73;
	  section.data(42).dtTransOffset = 41;
	
	  ;% audekaprdr.uint8_t2_Value_gdybbqcsvv
	  section.data(43).logicalSrcIdx = 74;
	  section.data(43).dtTransOffset = 42;
	
	  ;% audekaprdr.uint8_t3_Value_ie1lp0mdke
	  section.data(44).logicalSrcIdx = 75;
	  section.data(44).dtTransOffset = 43;
	
	  ;% audekaprdr.DeadSwitch_Value
	  section.data(45).logicalSrcIdx = 76;
	  section.data(45).dtTransOffset = 44;
	
	  ;% audekaprdr.TakeData_Value
	  section.data(46).logicalSrcIdx = 77;
	  section.data(46).dtTransOffset = 45;
	
	  ;% audekaprdr.ServoandRadioOn_Value
	  section.data(47).logicalSrcIdx = 78;
	  section.data(47).dtTransOffset = 46;
	
	  ;% audekaprdr.MotorControllersOn_Value
	  section.data(48).logicalSrcIdx = 79;
	  section.data(48).dtTransOffset = 47;
	
	  ;% audekaprdr.IMUReset_Value
	  section.data(49).logicalSrcIdx = 80;
	  section.data(49).dtTransOffset = 48;
	
	  ;% audekaprdr.PrinttheregistermapontheTeensy_
	  section.data(50).logicalSrcIdx = 81;
	  section.data(50).dtTransOffset = 49;
	
	  ;% audekaprdr.PrinttheimudataontheTeensy_Valu
	  section.data(51).logicalSrcIdx = 82;
	  section.data(51).dtTransOffset = 50;
	
	  ;% audekaprdr.Printtheradiotranceiverdataonth
	  section.data(52).logicalSrcIdx = 83;
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
    ;% Auto data (clyvxiydarg)
    ;%
      section.nData     = 16;
      section.data(16)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ic0gfcapnp
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% clyvxiydarg.lbyt1socd0
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% clyvxiydarg.is3mfmejaj
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% clyvxiydarg.jdwodkrquc
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% clyvxiydarg.edx4yqi2ih
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% clyvxiydarg.pamo5zphih
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% clyvxiydarg.leiowqqml1
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% clyvxiydarg.g4olebtl1k
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% clyvxiydarg.dg2znq5ace
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% clyvxiydarg.mcst0p3jo5
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% clyvxiydarg.okkoynnpgr
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% clyvxiydarg.cgnmkxqhhv
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% clyvxiydarg.cj4nyatvun
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% clyvxiydarg.bfc3tnu2kj
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% clyvxiydarg.eakdh1el1e
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% clyvxiydarg.dz1sbdawm1
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% clyvxiydarg.i31zz442cl
	  section.data(1).logicalSrcIdx = 16;
	  section.data(1).dtTransOffset = 0;
	
	  ;% clyvxiydarg.fasvywqxca
	  section.data(2).logicalSrcIdx = 17;
	  section.data(2).dtTransOffset = 1;
	
	  ;% clyvxiydarg.kxmv5d3vq5
	  section.data(3).logicalSrcIdx = 18;
	  section.data(3).dtTransOffset = 2;
	
	  ;% clyvxiydarg.fkthmbj4r0
	  section.data(4).logicalSrcIdx = 19;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% clyvxiydarg.alpabwxe2w
	  section.data(1).logicalSrcIdx = 20;
	  section.data(1).dtTransOffset = 0;
	
	  ;% clyvxiydarg.nsazlii4tl
	  section.data(2).logicalSrcIdx = 21;
	  section.data(2).dtTransOffset = 1;
	
	  ;% clyvxiydarg.bwa40grhig
	  section.data(3).logicalSrcIdx = 22;
	  section.data(3).dtTransOffset = 2;
	
	  ;% clyvxiydarg.obom5x3d5k
	  section.data(4).logicalSrcIdx = 23;
	  section.data(4).dtTransOffset = 3;
	
	  ;% clyvxiydarg.blslpvafaj
	  section.data(5).logicalSrcIdx = 24;
	  section.data(5).dtTransOffset = 4;
	
	  ;% clyvxiydarg.bhdmoiwfl2
	  section.data(6).logicalSrcIdx = 25;
	  section.data(6).dtTransOffset = 5;
	
	  ;% clyvxiydarg.mzc2e1h4xa
	  section.data(7).logicalSrcIdx = 26;
	  section.data(7).dtTransOffset = 6;
	
	  ;% clyvxiydarg.n30ajead0c
	  section.data(8).logicalSrcIdx = 27;
	  section.data(8).dtTransOffset = 7;
	
	  ;% clyvxiydarg.fisez1w02x
	  section.data(9).logicalSrcIdx = 28;
	  section.data(9).dtTransOffset = 8;
	
	  ;% clyvxiydarg.pzzkogkfuo
	  section.data(10).logicalSrcIdx = 29;
	  section.data(10).dtTransOffset = 10;
	
	  ;% clyvxiydarg.ellnmxuy5c
	  section.data(11).logicalSrcIdx = 30;
	  section.data(11).dtTransOffset = 12;
	
	  ;% clyvxiydarg.ehp13vk0yn
	  section.data(12).logicalSrcIdx = 31;
	  section.data(12).dtTransOffset = 14;
	
	  ;% clyvxiydarg.gvjctcpowu
	  section.data(13).logicalSrcIdx = 32;
	  section.data(13).dtTransOffset = 16;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.eb1nhjuy1x.hhotcsy3bn
	  section.data(1).logicalSrcIdx = 33;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.k224rszcix.mrw5fwnggh
	  section.data(1).logicalSrcIdx = 34;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.hgb50qrnyj.hhotcsy3bn
	  section.data(1).logicalSrcIdx = 35;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.hh4ml53bpz.mrw5fwnggh
	  section.data(1).logicalSrcIdx = 36;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.n0jtma5pzh.hhotcsy3bn
	  section.data(1).logicalSrcIdx = 37;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.drlrlfvubb.mrw5fwnggh
	  section.data(1).logicalSrcIdx = 38;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.e1burdxknc.hhotcsy3bn
	  section.data(1).logicalSrcIdx = 39;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.fkncya0tdv.mrw5fwnggh
	  section.data(1).logicalSrcIdx = 40;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.oenkj4342dw.hhotcsy3bn
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.a5srnfhi1at.mrw5fwnggh
	  section.data(1).logicalSrcIdx = 42;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.i2xz03n3pw.nwuhzt10m1
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.bytsoxyczf.nwuhzt10m1
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.mgokahjc0n.nwuhzt10m1
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.mxyoyiansk.nwuhzt10m1
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ibzhds0qj5.nwuhzt10m1
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.h2yf3rw5nw.nwuhzt10m1
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.awlchvsvng.nwuhzt10m1
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ihvxd4puwn.nwuhzt10m1
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.eev5qhucri.nwuhzt10m1
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.g2rdn4odoc.nwuhzt10m1
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.nv4dwlub3kk.nwuhzt10m1
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.o3brjlgfg1.ill2vas24l
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.nbm22evv0g.ill2vas24l
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ebil10nhgi.ill2vas24l
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.imtastcd1c.ill2vas24l
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.mal2e4bwfg.ill2vas24l
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.fsgkfn1wuo.ill2vas24l
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.judnob4hwn.ill2vas24l
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.nq4cmgm03a.ill2vas24l
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.ix1ebopk11.ill2vas24l
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.op2jvp5kgr.ill2vas24l
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(34) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% clyvxiydarg.kfxzmrhmete.ill2vas24l
	  section.data(1).logicalSrcIdx = 64;
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
	
	  ;% kmoqdzazlbs.iotuvc5rce
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% kmoqdzazlbs.k3q4jgrib1
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% kmoqdzazlbs.bk0erbqhjp
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% kmoqdzazlbs.olxbga3aem
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% kmoqdzazlbs.pok1xmp430
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
	
	  ;% kmoqdzazlbs.fsrarqxqo0.LoggedData
	  section.data(3).logicalSrcIdx = 15;
	  section.data(3).dtTransOffset = 2;
	
	  ;% kmoqdzazlbs.avxg25dwsu.LoggedData
	  section.data(4).logicalSrcIdx = 16;
	  section.data(4).dtTransOffset = 3;
	
	  ;% kmoqdzazlbs.prd3a3wnci.LoggedData
	  section.data(5).logicalSrcIdx = 17;
	  section.data(5).dtTransOffset = 4;
	
	  ;% kmoqdzazlbs.jvltu450sg.LoggedData
	  section.data(6).logicalSrcIdx = 18;
	  section.data(6).dtTransOffset = 6;
	
	  ;% kmoqdzazlbs.j2kovuleuw.LoggedData
	  section.data(7).logicalSrcIdx = 19;
	  section.data(7).dtTransOffset = 7;
	
	  ;% kmoqdzazlbs.a3g0mtsnf5.LoggedData
	  section.data(8).logicalSrcIdx = 20;
	  section.data(8).dtTransOffset = 9;
	
	  ;% kmoqdzazlbs.cxtxz3djin.LoggedData
	  section.data(9).logicalSrcIdx = 21;
	  section.data(9).dtTransOffset = 11;
	
	  ;% kmoqdzazlbs.cfkhnfdexp.LoggedData
	  section.data(10).logicalSrcIdx = 22;
	  section.data(10).dtTransOffset = 13;
	
	  ;% kmoqdzazlbs.ltmcpazioy.LoggedData
	  section.data(11).logicalSrcIdx = 23;
	  section.data(11).dtTransOffset = 16;
	
	  ;% kmoqdzazlbs.grthygqduu.LoggedData
	  section.data(12).logicalSrcIdx = 24;
	  section.data(12).dtTransOffset = 17;
	
	  ;% kmoqdzazlbs.jvliboeki1.LoggedData
	  section.data(13).logicalSrcIdx = 25;
	  section.data(13).dtTransOffset = 18;
	
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
	
	  ;% kmoqdzazlbs.aat5rcexcc
	  section.data(9).logicalSrcIdx = 36;
	  section.data(9).dtTransOffset = 8;
	
	  ;% kmoqdzazlbs.k3hs4pzowf
	  section.data(10).logicalSrcIdx = 37;
	  section.data(10).dtTransOffset = 9;
	
	  ;% kmoqdzazlbs.gb24fmruvs
	  section.data(11).logicalSrcIdx = 38;
	  section.data(11).dtTransOffset = 10;
	
	  ;% kmoqdzazlbs.m0iknry4j5
	  section.data(12).logicalSrcIdx = 39;
	  section.data(12).dtTransOffset = 11;
	
	  ;% kmoqdzazlbs.lna0jonxup
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
      
	  ;% kmoqdzazlbs.o3brjlgfg1.cenwn3kkmq
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.o3brjlgfg1.jxe2llqi4c
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.nbm22evv0g.cenwn3kkmq
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.nbm22evv0g.jxe2llqi4c
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.ebil10nhgi.cenwn3kkmq
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.ebil10nhgi.jxe2llqi4c
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.imtastcd1c.cenwn3kkmq
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.imtastcd1c.jxe2llqi4c
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.mal2e4bwfg.cenwn3kkmq
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.mal2e4bwfg.jxe2llqi4c
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.fsgkfn1wuo.cenwn3kkmq
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.fsgkfn1wuo.jxe2llqi4c
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.judnob4hwn.cenwn3kkmq
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.judnob4hwn.jxe2llqi4c
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.nq4cmgm03a.cenwn3kkmq
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.nq4cmgm03a.jxe2llqi4c
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.ix1ebopk11.cenwn3kkmq
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.ix1ebopk11.jxe2llqi4c
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.op2jvp5kgr.cenwn3kkmq
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.op2jvp5kgr.jxe2llqi4c
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.kfxzmrhmete.cenwn3kkmq
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% kmoqdzazlbs.kfxzmrhmete.jxe2llqi4c
	  section.data(1).logicalSrcIdx = 64;
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


  targMap.checksum0 = 3269004534;
  targMap.checksum1 = 4233354009;
  targMap.checksum2 = 1910561963;
  targMap.checksum3 = 2531096517;

