
#include "t3spi.h"
#include "mk20dx128.h"
#include "core_pins.h"
#include "arduino.h"

//#define MASTER      1
//#define SLAVE       0

T3SPI::T3SPI() {
    SIM_SCGC6 |= SIM_SCGC6_SPI0;    // enable clock to SPI.
    dataPointer=0;
    dataPointer2=0;
    packetCT=0;
    ctar=0;
    delay(1000);
}


void T3SPI::begin_SLAVE() {//BEGIN SLAVE MODE DEFAULT PINS
    setMCR(SLAVE);
    setCTAR_SLAVE(8, SPI_MODE0);
    SPI0_RSER = 0x00020000;
    enablePins_SLAVE(SCK, MOSI, MISO, CS0);
}

void T3SPI::begin_SLAVE(uint8_t sck, uint8_t mosi, uint8_t miso, uint8_t cs) {//BEGIN SLAVE MODE WITH OPTION FOR ALTERNATIVE PINS
    setMCR(SLAVE);
    setCTAR_SLAVE(8, SPI_MODE0);
    SPI0_RSER = 0x00020000;
    enablePins_SLAVE(sck, mosi, miso, cs);
}

void T3SPI::setMCR(bool mode){
    stop();
    if (mode==MASTER){
        SPI0_MCR=0x80000000;}
    else{
        SPI0_MCR=0x00000000;}
    start();
}

void T3SPI::setCTAR_SLAVE(uint8_t size, uint8_t dataMode){
    SPI0_CTAR0_SLAVE=0;
    setFrameSize(CTAR_SLAVE, (size - 1));
    setMode(CTAR_SLAVE, dataMode);
}

void T3SPI::enablePins_SLAVE(uint8_t sck, uint8_t mosi, uint8_t miso, uint8_t cs) {
    if (sck == SCK){
        CORE_PIN13_CONFIG = PORT_PCR_MUX(2);}
    if (sck == ALT_SCK){
        CORE_PIN14_CONFIG = PORT_PCR_MUX(2);}
    if (mosi == MOSI){
        CORE_PIN11_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);}
    if (mosi == ALT_MOSI){
        CORE_PIN7_CONFIG  = PORT_PCR_DSE | PORT_PCR_MUX(2);}
    if (miso == MISO){
        CORE_PIN12_CONFIG = PORT_PCR_MUX(2);}
    if (miso == ALT_MISO){
        CORE_PIN8_CONFIG  = PORT_PCR_MUX(2);}
    if (cs == CS0){
        CORE_PIN10_CONFIG = PORT_PCR_MUX(2);}
    if (cs == ALT_CS0){
        CORE_PIN2_CONFIG  = PORT_PCR_MUX(2);}
}

void T3SPI::setCS_ActiveLOW(uint32_t pin){
    stop();
    SPI0_MCR |= (pin);
    start();
}

void T3SPI::setFrameSize(uint8_t CTARn, uint8_t size) {
    stop();
    if (CTARn==0){
        SPI0_CTAR0 |= SPI_CTAR_FMSZ(size);}
    if (CTARn==1){
        SPI0_CTAR1 |= SPI_CTAR_FMSZ(size);}
    if (CTARn==2){
        SPI0_CTAR0_SLAVE |= SPI_CTAR_FMSZ(size);}
    start();
}
//(((size) & 31) << 27);

void T3SPI::setMode(uint8_t CTARn, uint8_t dataMode) {
    stop();
    if (CTARn==0){
        SPI0_CTAR0 = SPI0_CTAR0 & ~(SPI_CTAR_CPOL | SPI_CTAR_CPHA) | dataMode << 25;}//USING THIS!!
    if (CTARn==1){
        SPI0_CTAR1 = SPI0_CTAR1 & ~(SPI_CTAR_CPOL | SPI_CTAR_CPHA) | dataMode << 25;}
    if (CTARn==2){
        SPI0_CTAR0_SLAVE = SPI0_CTAR0_SLAVE & ~(SPI_CTAR_CPOL | SPI_CTAR_CPHA) | dataMode << 25;}
    start();
}

void T3SPI::start() {
    SPI0_MCR &= ~SPI_MCR_HALT & ~SPI_MCR_MDIS;
}

void T3SPI::stop() {
    SPI0_MCR |= SPI_MCR_HALT | SPI_MCR_MDIS;
}

void T3SPI::end() {
    SPI0_SR &= ~SPI_SR_TXRXS;
    stop();
}

void T3SPI::rxtx8(volatile uint8_t *dataIN, volatile uint8_t *dataOUT, int length){
    dataIN[dataPointer] = SPI0_POPR;
    dataPointer++;
    if (dataPointer == length){
        dataPointer=0;
        packetCT++;}
    SPI0_PUSHR_SLAVE = dataOUT[dataPointer];  
    SPI0_SR |= SPI_SR_RFDF;
}


