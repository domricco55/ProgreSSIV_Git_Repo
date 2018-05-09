/* 
 *  This .h file defines function and class prototypes that are referenced in the main program file
 *//*
// define colors
#define rgbRED    0x00ff0000
#define rgbGREEN  0x0000ff00
#define rgbBLUE   0x000000ff
#define rgbPURPLE 0x00ff00ff
#define rgbYELLOW 0x00ffff00
#define rgbWHITE  0x00ffffff
#define rgbCYAN   0x0000ffff*/
//define colors part2
#define rgbRED    0x0000ffff
#define rgbGREEN  0x00ff00ff
#define rgbBLUE   0x00ffff00
#define rgbPURPLE 0x0000ff00
#define rgbYELLOW 0x000000ff
#define rgbWHITE  0x00000000
#define rgbCYAN   0x00ff0000
// Fault State Indication  
void initFault();
void detectFault();
void indicatorSet(uint32_t RGBval);
//--------------------------------
