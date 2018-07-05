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
    ;% Auto data (dkbayjq2ou)
    ;%
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% dkbayjq2ou.FixPtBitwiseOperator1_BitMask
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% dkbayjq2ou.FixPtBitwiseOperator_as2k3qplyw
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% dkbayjq2ou.FixPtBitwiseOperator_nkfjnteeeq
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% dkbayjq2ou.FixPtBitwiseOperator_j5xa4hxjcc
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% dkbayjq2ou.FixPtBitwiseOperator_n3ticzbm0w
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% dkbayjq2ou.FixPtBitwiseOperator_mkysc30z34
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% dkbayjq2ou.FixPtBitwiseOperator_ofi0bcjw10
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% dkbayjq2ou.FixPtBitwiseOperator_hsop4wqw3h
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% dkbayjq2ou.FixPtBitwiseOperator_nltvqamzzv
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% dkbayjq2ou.FixPtBitwiseOperator_kmc03sgzj0
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% dkbayjq2ou.FixPtBitwiseOperator_gd2bxfln3i
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 21;
      section.data(21)  = dumData; %prealloc
      
	  ;% dkbayjq2ou._Value
	  section.data(1).logicalSrcIdx = 11;
	  section.data(1).dtTransOffset = 0;
	
	  ;% dkbayjq2ou.ConstMotVel_Value
	  section.data(2).logicalSrcIdx = 12;
	  section.data(2).dtTransOffset = 1;
	
	  ;% dkbayjq2ou.DeadSwitchValue_Value
	  section.data(3).logicalSrcIdx = 13;
	  section.data(3).dtTransOffset = 2;
	
	  ;% dkbayjq2ou.AccelerationInttoDoubleScaleFac
	  section.data(4).logicalSrcIdx = 14;
	  section.data(4).dtTransOffset = 3;
	
	  ;% dkbayjq2ou.GyroscopeInttoDoubleScaleFactor
	  section.data(5).logicalSrcIdx = 15;
	  section.data(5).dtTransOffset = 4;
	
	  ;% dkbayjq2ou.AccelerationInttoDou_h2nh03n513
	  section.data(6).logicalSrcIdx = 16;
	  section.data(6).dtTransOffset = 5;
	
	  ;% dkbayjq2ou.GyroscopeInttoDouble_hw2tyfthn4
	  section.data(7).logicalSrcIdx = 17;
	  section.data(7).dtTransOffset = 6;
	
	  ;% dkbayjq2ou.AccelerationInttoDou_hkwjyt2xjk
	  section.data(8).logicalSrcIdx = 18;
	  section.data(8).dtTransOffset = 7;
	
	  ;% dkbayjq2ou.GyroscopeInttoDouble_dt33lrcogy
	  section.data(9).logicalSrcIdx = 19;
	  section.data(9).dtTransOffset = 8;
	
	  ;% dkbayjq2ou.EulerInttoDoubleScaleFactor_Gai
	  section.data(10).logicalSrcIdx = 20;
	  section.data(10).dtTransOffset = 9;
	
	  ;% dkbayjq2ou.FlippingSignConvention2_Gain
	  section.data(11).logicalSrcIdx = 21;
	  section.data(11).dtTransOffset = 10;
	
	  ;% dkbayjq2ou.EulerInttoDoubleScal_lopujqi4cg
	  section.data(12).logicalSrcIdx = 22;
	  section.data(12).dtTransOffset = 11;
	
	  ;% dkbayjq2ou.FlippingSignConvention_Gain
	  section.data(13).logicalSrcIdx = 23;
	  section.data(13).dtTransOffset = 12;
	
	  ;% dkbayjq2ou.EulerInttoDoubleScal_nw21yceloc
	  section.data(14).logicalSrcIdx = 24;
	  section.data(14).dtTransOffset = 13;
	
	  ;% dkbayjq2ou.FlippingSignConvention1_Gain
	  section.data(15).logicalSrcIdx = 25;
	  section.data(15).dtTransOffset = 14;
	
	  ;% dkbayjq2ou.Constant1_Value
	  section.data(16).logicalSrcIdx = 26;
	  section.data(16).dtTransOffset = 15;
	
	  ;% dkbayjq2ou.Constant_Value
	  section.data(17).logicalSrcIdx = 27;
	  section.data(17).dtTransOffset = 16;
	
	  ;% dkbayjq2ou.Constant2_Value
	  section.data(18).logicalSrcIdx = 28;
	  section.data(18).dtTransOffset = 17;
	
	  ;% dkbayjq2ou.Constant4_Value
	  section.data(19).logicalSrcIdx = 29;
	  section.data(19).dtTransOffset = 18;
	
	  ;% dkbayjq2ou.Constant3_Value
	  section.data(20).logicalSrcIdx = 30;
	  section.data(20).dtTransOffset = 19;
	
	  ;% dkbayjq2ou.Constant5_Value
	  section.data(21).logicalSrcIdx = 31;
	  section.data(21).dtTransOffset = 20;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 52;
      section.data(52)  = dumData; %prealloc
      
	  ;% dkbayjq2ou.euler_headingAddressNumber_Valu
	  section.data(1).logicalSrcIdx = 32;
	  section.data(1).dtTransOffset = 0;
	
	  ;% dkbayjq2ou.uint8_t1_Value
	  section.data(2).logicalSrcIdx = 33;
	  section.data(2).dtTransOffset = 1;
	
	  ;% dkbayjq2ou.uint8_t2_Value
	  section.data(3).logicalSrcIdx = 34;
	  section.data(3).dtTransOffset = 2;
	
	  ;% dkbayjq2ou.uint8_t3_Value
	  section.data(4).logicalSrcIdx = 35;
	  section.data(4).dtTransOffset = 3;
	
	  ;% dkbayjq2ou.euler_rollAddressNumber_Value
	  section.data(5).logicalSrcIdx = 36;
	  section.data(5).dtTransOffset = 4;
	
	  ;% dkbayjq2ou.uint8_t1_Value_bnexk0rvdq
	  section.data(6).logicalSrcIdx = 37;
	  section.data(6).dtTransOffset = 5;
	
	  ;% dkbayjq2ou.uint8_t2_Value_gn4ieal2dy
	  section.data(7).logicalSrcIdx = 38;
	  section.data(7).dtTransOffset = 6;
	
	  ;% dkbayjq2ou.uint8_t3_Value_i0fec1wvc1
	  section.data(8).logicalSrcIdx = 39;
	  section.data(8).dtTransOffset = 7;
	
	  ;% dkbayjq2ou.euler_pitchAddressNumber_Value
	  section.data(9).logicalSrcIdx = 40;
	  section.data(9).dtTransOffset = 8;
	
	  ;% dkbayjq2ou.uint8_t1_Value_ndti5ul2ir
	  section.data(10).logicalSrcIdx = 41;
	  section.data(10).dtTransOffset = 9;
	
	  ;% dkbayjq2ou.uint8_t2_Value_lqvuywxu0i
	  section.data(11).logicalSrcIdx = 42;
	  section.data(11).dtTransOffset = 10;
	
	  ;% dkbayjq2ou.uint8_t3_Value_lepgvl4yvs
	  section.data(12).logicalSrcIdx = 43;
	  section.data(12).dtTransOffset = 11;
	
	  ;% dkbayjq2ou.gyr_xAddressNumber_Value
	  section.data(13).logicalSrcIdx = 44;
	  section.data(13).dtTransOffset = 12;
	
	  ;% dkbayjq2ou.uint8_t1_Value_kdkvzqxzai
	  section.data(14).logicalSrcIdx = 45;
	  section.data(14).dtTransOffset = 13;
	
	  ;% dkbayjq2ou.uint8_t2_Value_fjb5jcvryv
	  section.data(15).logicalSrcIdx = 46;
	  section.data(15).dtTransOffset = 14;
	
	  ;% dkbayjq2ou.uint8_t3_Value_olsuwridav
	  section.data(16).logicalSrcIdx = 47;
	  section.data(16).dtTransOffset = 15;
	
	  ;% dkbayjq2ou.acc_xAddressNumber_Value
	  section.data(17).logicalSrcIdx = 48;
	  section.data(17).dtTransOffset = 16;
	
	  ;% dkbayjq2ou.uint8_t1_Value_cxtxrspyx2
	  section.data(18).logicalSrcIdx = 49;
	  section.data(18).dtTransOffset = 17;
	
	  ;% dkbayjq2ou.uint8_t2_Value_cnehq0fw23
	  section.data(19).logicalSrcIdx = 50;
	  section.data(19).dtTransOffset = 18;
	
	  ;% dkbayjq2ou.uint8_t3_Value_pdglhcrw0d
	  section.data(20).logicalSrcIdx = 51;
	  section.data(20).dtTransOffset = 19;
	
	  ;% dkbayjq2ou.gyr_yAddressNumber_Value
	  section.data(21).logicalSrcIdx = 52;
	  section.data(21).dtTransOffset = 20;
	
	  ;% dkbayjq2ou.uint8_t1_Value_cm2c0avpfj
	  section.data(22).logicalSrcIdx = 53;
	  section.data(22).dtTransOffset = 21;
	
	  ;% dkbayjq2ou.uint8_t2_Value_lvoif2jzzk
	  section.data(23).logicalSrcIdx = 54;
	  section.data(23).dtTransOffset = 22;
	
	  ;% dkbayjq2ou.uint8_t3_Value_mtqeqchjq3
	  section.data(24).logicalSrcIdx = 55;
	  section.data(24).dtTransOffset = 23;
	
	  ;% dkbayjq2ou.acc_yAddressNumber_Value
	  section.data(25).logicalSrcIdx = 56;
	  section.data(25).dtTransOffset = 24;
	
	  ;% dkbayjq2ou.uint8_t1_Value_olo0yfbjbp
	  section.data(26).logicalSrcIdx = 57;
	  section.data(26).dtTransOffset = 25;
	
	  ;% dkbayjq2ou.uint8_t2_Value_clw2lo3chi
	  section.data(27).logicalSrcIdx = 58;
	  section.data(27).dtTransOffset = 26;
	
	  ;% dkbayjq2ou.uint8_t3_Value_dydix2zbx3
	  section.data(28).logicalSrcIdx = 59;
	  section.data(28).dtTransOffset = 27;
	
	  ;% dkbayjq2ou.gyr_zAddressNumber_Value
	  section.data(29).logicalSrcIdx = 60;
	  section.data(29).dtTransOffset = 28;
	
	  ;% dkbayjq2ou.uint8_t1_Value_fvslqcrdl2
	  section.data(30).logicalSrcIdx = 61;
	  section.data(30).dtTransOffset = 29;
	
	  ;% dkbayjq2ou.uint8_t2_Value_lsv0pyia0r
	  section.data(31).logicalSrcIdx = 62;
	  section.data(31).dtTransOffset = 30;
	
	  ;% dkbayjq2ou.uint8_t3_Value_ddvup1twb3
	  section.data(32).logicalSrcIdx = 63;
	  section.data(32).dtTransOffset = 31;
	
	  ;% dkbayjq2ou.acc_zAddressNumber_Value
	  section.data(33).logicalSrcIdx = 64;
	  section.data(33).dtTransOffset = 32;
	
	  ;% dkbayjq2ou.uint8_t1_Value_bfs2kyqhyj
	  section.data(34).logicalSrcIdx = 65;
	  section.data(34).dtTransOffset = 33;
	
	  ;% dkbayjq2ou.uint8_t2_Value_p1gsoflfkl
	  section.data(35).logicalSrcIdx = 66;
	  section.data(35).dtTransOffset = 34;
	
	  ;% dkbayjq2ou.uint8_t3_Value_jkgzprijvo
	  section.data(36).logicalSrcIdx = 67;
	  section.data(36).dtTransOffset = 35;
	
	  ;% dkbayjq2ou.radio_throttleAddressNumber_Val
	  section.data(37).logicalSrcIdx = 68;
	  section.data(37).dtTransOffset = 36;
	
	  ;% dkbayjq2ou.uint8_t1_Value_fzct0d4u4r
	  section.data(38).logicalSrcIdx = 69;
	  section.data(38).dtTransOffset = 37;
	
	  ;% dkbayjq2ou.uint8_t2_Value_fs3jntlocd
	  section.data(39).logicalSrcIdx = 70;
	  section.data(39).dtTransOffset = 38;
	
	  ;% dkbayjq2ou.uint8_t3_Value_lxeky0iln5
	  section.data(40).logicalSrcIdx = 71;
	  section.data(40).dtTransOffset = 39;
	
	  ;% dkbayjq2ou.radio_steeringAddressNumber_Val
	  section.data(41).logicalSrcIdx = 72;
	  section.data(41).dtTransOffset = 40;
	
	  ;% dkbayjq2ou.uint8_t1_Value_ju0tizjign
	  section.data(42).logicalSrcIdx = 73;
	  section.data(42).dtTransOffset = 41;
	
	  ;% dkbayjq2ou.uint8_t2_Value_gdybbqcsvv
	  section.data(43).logicalSrcIdx = 74;
	  section.data(43).dtTransOffset = 42;
	
	  ;% dkbayjq2ou.uint8_t3_Value_ie1lp0mdke
	  section.data(44).logicalSrcIdx = 75;
	  section.data(44).dtTransOffset = 43;
	
	  ;% dkbayjq2ou.DeadSwitch_Value
	  section.data(45).logicalSrcIdx = 76;
	  section.data(45).dtTransOffset = 44;
	
	  ;% dkbayjq2ou.TakeData_Value
	  section.data(46).logicalSrcIdx = 77;
	  section.data(46).dtTransOffset = 45;
	
	  ;% dkbayjq2ou.ServoandRadioOn_Value
	  section.data(47).logicalSrcIdx = 78;
	  section.data(47).dtTransOffset = 46;
	
	  ;% dkbayjq2ou.MotorControllersOn_Value
	  section.data(48).logicalSrcIdx = 79;
	  section.data(48).dtTransOffset = 47;
	
	  ;% dkbayjq2ou.IMUReset_Value
	  section.data(49).logicalSrcIdx = 80;
	  section.data(49).dtTransOffset = 48;
	
	  ;% dkbayjq2ou.PrinttheregistermapontheTeensy_
	  section.data(50).logicalSrcIdx = 81;
	  section.data(50).dtTransOffset = 49;
	
	  ;% dkbayjq2ou.PrinttheimudataontheTeensy_Valu
	  section.data(51).logicalSrcIdx = 82;
	  section.data(51).dtTransOffset = 50;
	
	  ;% dkbayjq2ou.Printtheradiotranceiverdataonth
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
    ;% Auto data (nttj0ljmf5s)
    ;%
      section.nData     = 16;
      section.data(16)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.hapbkgnn5z
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% nttj0ljmf5s.hyk5krbp03
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% nttj0ljmf5s.m1th2dpeiy
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% nttj0ljmf5s.neifoprkgo
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% nttj0ljmf5s.ndbhhjxjpb
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% nttj0ljmf5s.duh0wdl5em
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% nttj0ljmf5s.kohiihnjq4
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% nttj0ljmf5s.nziu1guii2
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% nttj0ljmf5s.pyt3g0qdwr
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% nttj0ljmf5s.pgzj4scek2
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% nttj0ljmf5s.oei0zgsxjv
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% nttj0ljmf5s.gn4rss15yk
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% nttj0ljmf5s.lebdldz5i5
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% nttj0ljmf5s.ke5y0vgyul
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% nttj0ljmf5s.gep5ypsgcf
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% nttj0ljmf5s.c4ayya4zrb
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.puwzfh2d0n
	  section.data(1).logicalSrcIdx = 16;
	  section.data(1).dtTransOffset = 0;
	
	  ;% nttj0ljmf5s.j0j12qkhkx
	  section.data(2).logicalSrcIdx = 17;
	  section.data(2).dtTransOffset = 1;
	
	  ;% nttj0ljmf5s.njr3qnwaft
	  section.data(3).logicalSrcIdx = 18;
	  section.data(3).dtTransOffset = 2;
	
	  ;% nttj0ljmf5s.kaorwo5w5p
	  section.data(4).logicalSrcIdx = 19;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.cmba4l4nfr
	  section.data(1).logicalSrcIdx = 20;
	  section.data(1).dtTransOffset = 0;
	
	  ;% nttj0ljmf5s.ia3hqikzw2
	  section.data(2).logicalSrcIdx = 21;
	  section.data(2).dtTransOffset = 1;
	
	  ;% nttj0ljmf5s.nh4gndl35t
	  section.data(3).logicalSrcIdx = 22;
	  section.data(3).dtTransOffset = 2;
	
	  ;% nttj0ljmf5s.cbjeejtrvc
	  section.data(4).logicalSrcIdx = 23;
	  section.data(4).dtTransOffset = 3;
	
	  ;% nttj0ljmf5s.k0j200aw0u
	  section.data(5).logicalSrcIdx = 24;
	  section.data(5).dtTransOffset = 4;
	
	  ;% nttj0ljmf5s.prdetbsbpr
	  section.data(6).logicalSrcIdx = 25;
	  section.data(6).dtTransOffset = 5;
	
	  ;% nttj0ljmf5s.pv4tqs2ojn
	  section.data(7).logicalSrcIdx = 26;
	  section.data(7).dtTransOffset = 6;
	
	  ;% nttj0ljmf5s.du2cptgkrf
	  section.data(8).logicalSrcIdx = 27;
	  section.data(8).dtTransOffset = 7;
	
	  ;% nttj0ljmf5s.cdq2gokexd
	  section.data(9).logicalSrcIdx = 28;
	  section.data(9).dtTransOffset = 8;
	
	  ;% nttj0ljmf5s.emtw3geqiu
	  section.data(10).logicalSrcIdx = 29;
	  section.data(10).dtTransOffset = 10;
	
	  ;% nttj0ljmf5s.eisrink3an
	  section.data(11).logicalSrcIdx = 30;
	  section.data(11).dtTransOffset = 12;
	
	  ;% nttj0ljmf5s.n0syb50v4o
	  section.data(12).logicalSrcIdx = 31;
	  section.data(12).dtTransOffset = 14;
	
	  ;% nttj0ljmf5s.bqbrzibojy
	  section.data(13).logicalSrcIdx = 32;
	  section.data(13).dtTransOffset = 16;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.dj33kyktdb.gsij1li2lf
	  section.data(1).logicalSrcIdx = 33;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.f553iievvs.cnedtfyaog
	  section.data(1).logicalSrcIdx = 34;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.cdr354l24z.gsij1li2lf
	  section.data(1).logicalSrcIdx = 35;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.a0nn5wvxnh.cnedtfyaog
	  section.data(1).logicalSrcIdx = 36;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.p3qq5oy3uu.gsij1li2lf
	  section.data(1).logicalSrcIdx = 37;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.ni0bodlsxl.cnedtfyaog
	  section.data(1).logicalSrcIdx = 38;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.hrksk11zlj.gsij1li2lf
	  section.data(1).logicalSrcIdx = 39;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.gfgttddypg.cnedtfyaog
	  section.data(1).logicalSrcIdx = 40;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.jmy30gc5tyh.gsij1li2lf
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.pzn34iqvzio.cnedtfyaog
	  section.data(1).logicalSrcIdx = 42;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.awpn11t2dl.ngb1cxt2yt
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.n0lhpk3zvc.ngb1cxt2yt
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.j3gt3jnxgc.ngb1cxt2yt
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.mol3cwqijz.ngb1cxt2yt
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.denpax2b0b.ngb1cxt2yt
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.njm02vciay.ngb1cxt2yt
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.lj3trkucla.ngb1cxt2yt
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.a0xut11c0n.ngb1cxt2yt
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.kv0fyqcjlu.ngb1cxt2yt
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.lqgdjt1amn.ngb1cxt2yt
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.by1onezzzr3.ngb1cxt2yt
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.o0oo1yiatx.mbm5jwtrtx
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.ig505bxoaf.mbm5jwtrtx
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(26) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.pij3ji32yl.mbm5jwtrtx
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(27) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.hupi3ta3bd.mbm5jwtrtx
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(28) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.gxgp4oxig3.mbm5jwtrtx
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(29) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.fhxr2unipg.mbm5jwtrtx
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(30) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.kczykcqiex.mbm5jwtrtx
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(31) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.fujmpihqhb.mbm5jwtrtx
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(32) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.dwusl4hi0l.mbm5jwtrtx
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(33) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.dtyjbpwyui.mbm5jwtrtx
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(34) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% nttj0ljmf5s.podjxd54grz.mbm5jwtrtx
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
    ;% Auto data (j3kisgy1kpn)
    ;%
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.l1n53r20db
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% j3kisgy1kpn.caqonpq0xm
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% j3kisgy1kpn.hvhqpj5glq
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% j3kisgy1kpn.k3vs5kb5mm
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% j3kisgy1kpn.o5fa1o0vrb
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% j3kisgy1kpn.db0cxvf4b5
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% j3kisgy1kpn.pupbunhq3f
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% j3kisgy1kpn.b25ycnuoei
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% j3kisgy1kpn.bermfqyhwz
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% j3kisgy1kpn.gzjjd0pyel
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% j3kisgy1kpn.n1qfkwn2ly
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% j3kisgy1kpn.fex3naytzp
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% j3kisgy1kpn.jby1xo5cl3
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.e0asdoy1no.LoggedData
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
	  ;% j3kisgy1kpn.bwekcfohx3.LoggedData
	  section.data(2).logicalSrcIdx = 14;
	  section.data(2).dtTransOffset = 1;
	
	  ;% j3kisgy1kpn.ibbfr1eziq.LoggedData
	  section.data(3).logicalSrcIdx = 15;
	  section.data(3).dtTransOffset = 2;
	
	  ;% j3kisgy1kpn.cpevx3dljp.LoggedData
	  section.data(4).logicalSrcIdx = 16;
	  section.data(4).dtTransOffset = 3;
	
	  ;% j3kisgy1kpn.etatx12ot0.LoggedData
	  section.data(5).logicalSrcIdx = 17;
	  section.data(5).dtTransOffset = 4;
	
	  ;% j3kisgy1kpn.c3b5xcc5bl.LoggedData
	  section.data(6).logicalSrcIdx = 18;
	  section.data(6).dtTransOffset = 6;
	
	  ;% j3kisgy1kpn.bco52nrw04.LoggedData
	  section.data(7).logicalSrcIdx = 19;
	  section.data(7).dtTransOffset = 7;
	
	  ;% j3kisgy1kpn.mvyaukfyy2.LoggedData
	  section.data(8).logicalSrcIdx = 20;
	  section.data(8).dtTransOffset = 9;
	
	  ;% j3kisgy1kpn.nfa3knf0mt.LoggedData
	  section.data(9).logicalSrcIdx = 21;
	  section.data(9).dtTransOffset = 11;
	
	  ;% j3kisgy1kpn.cxl12hyoh0.LoggedData
	  section.data(10).logicalSrcIdx = 22;
	  section.data(10).dtTransOffset = 13;
	
	  ;% j3kisgy1kpn.br0sjanqyx.LoggedData
	  section.data(11).logicalSrcIdx = 23;
	  section.data(11).dtTransOffset = 16;
	
	  ;% j3kisgy1kpn.hb0wn0xbzf.LoggedData
	  section.data(12).logicalSrcIdx = 24;
	  section.data(12).dtTransOffset = 17;
	
	  ;% j3kisgy1kpn.fey4teshyo.LoggedData
	  section.data(13).logicalSrcIdx = 25;
	  section.data(13).dtTransOffset = 18;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.dnh5p2lvvm
	  section.data(1).logicalSrcIdx = 26;
	  section.data(1).dtTransOffset = 0;
	
	  ;% j3kisgy1kpn.pcovv3xn1e
	  section.data(2).logicalSrcIdx = 27;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.p1hjdu51vo
	  section.data(1).logicalSrcIdx = 28;
	  section.data(1).dtTransOffset = 0;
	
	  ;% j3kisgy1kpn.mnn2uxst33
	  section.data(2).logicalSrcIdx = 29;
	  section.data(2).dtTransOffset = 1;
	
	  ;% j3kisgy1kpn.dlub5c3wf3
	  section.data(3).logicalSrcIdx = 30;
	  section.data(3).dtTransOffset = 2;
	
	  ;% j3kisgy1kpn.kwaiedcyrm
	  section.data(4).logicalSrcIdx = 31;
	  section.data(4).dtTransOffset = 3;
	
	  ;% j3kisgy1kpn.g25zo0bycb
	  section.data(5).logicalSrcIdx = 32;
	  section.data(5).dtTransOffset = 4;
	
	  ;% j3kisgy1kpn.frnu3ml2kp
	  section.data(6).logicalSrcIdx = 33;
	  section.data(6).dtTransOffset = 5;
	
	  ;% j3kisgy1kpn.ich3tzudt3
	  section.data(7).logicalSrcIdx = 34;
	  section.data(7).dtTransOffset = 6;
	
	  ;% j3kisgy1kpn.cjwiqdvnfv
	  section.data(8).logicalSrcIdx = 35;
	  section.data(8).dtTransOffset = 7;
	
	  ;% j3kisgy1kpn.bray20l45s
	  section.data(9).logicalSrcIdx = 36;
	  section.data(9).dtTransOffset = 8;
	
	  ;% j3kisgy1kpn.pc5vsu0omi
	  section.data(10).logicalSrcIdx = 37;
	  section.data(10).dtTransOffset = 9;
	
	  ;% j3kisgy1kpn.c25yg22tgh
	  section.data(11).logicalSrcIdx = 38;
	  section.data(11).dtTransOffset = 10;
	
	  ;% j3kisgy1kpn.l4uxbrmleo
	  section.data(12).logicalSrcIdx = 39;
	  section.data(12).dtTransOffset = 11;
	
	  ;% j3kisgy1kpn.igsv5kejas
	  section.data(13).logicalSrcIdx = 40;
	  section.data(13).dtTransOffset = 12;
	
	  ;% j3kisgy1kpn.lw1gj5tvbp
	  section.data(14).logicalSrcIdx = 41;
	  section.data(14).dtTransOffset = 13;
	
	  ;% j3kisgy1kpn.cxois2rw1u
	  section.data(15).logicalSrcIdx = 42;
	  section.data(15).dtTransOffset = 14;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.o0oo1yiatx.e2a5ozwqf2
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.o0oo1yiatx.axqhjrjw0v
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.ig505bxoaf.e2a5ozwqf2
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.ig505bxoaf.axqhjrjw0v
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.pij3ji32yl.e2a5ozwqf2
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.pij3ji32yl.axqhjrjw0v
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.hupi3ta3bd.e2a5ozwqf2
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.hupi3ta3bd.axqhjrjw0v
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.gxgp4oxig3.e2a5ozwqf2
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(13) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.gxgp4oxig3.axqhjrjw0v
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.fhxr2unipg.e2a5ozwqf2
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.fhxr2unipg.axqhjrjw0v
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(16) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.kczykcqiex.e2a5ozwqf2
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(17) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.kczykcqiex.axqhjrjw0v
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.fujmpihqhb.e2a5ozwqf2
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(19) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.fujmpihqhb.axqhjrjw0v
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(20) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.dwusl4hi0l.e2a5ozwqf2
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(21) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.dwusl4hi0l.axqhjrjw0v
	  section.data(1).logicalSrcIdx = 60;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(22) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.dtyjbpwyui.e2a5ozwqf2
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(23) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.dtyjbpwyui.axqhjrjw0v
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(24) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.podjxd54grz.e2a5ozwqf2
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(25) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% j3kisgy1kpn.podjxd54grz.axqhjrjw0v
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


  targMap.checksum0 = 4218942326;
  targMap.checksum1 = 1994007386;
  targMap.checksum2 = 2016287264;
  targMap.checksum3 = 232830058;

