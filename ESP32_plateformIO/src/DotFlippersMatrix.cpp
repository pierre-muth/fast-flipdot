
#include <Adafruit_GFX.h>
#include "DotFlippersMatrix.h"
#include <SPI.h>

#define DATAPIN    26
#define CLOCKPIN   27

static const int spiClk = 200000; 

SPIClass * hspi = NULL; //uninitalised pointers to SPI object
 

DotFlippersMatrix::DotFlippersMatrix(int16_t w, int16_t h) : 
    Adafruit_GFX(w, h) {

    // SPI init
    hspi = new SPIClass(HSPI);
    hspi->begin(CLOCKPIN, 12, DATAPIN, 14); //SCLK, MISO, MOSI, SS

}

boolean DotFlippersMatrix::begin() {
    if((!frameBuffer) && !(frameBuffer = (uint8_t *)malloc(WIDTH * HEIGHT))) {
        return false;
    }

    if((!displayBuffer) && !(displayBuffer = (uint8_t *)malloc(pixelWidth * ((pixelHeight+6)/7) ))) {
        return false;
    }

    clear(0x00);
    display();

    return true;
}

void DotFlippersMatrix::setDisplayPixelSize(int16_t w, int16_t h){
    pixelHeight = h;
    pixelWidth = w;
}

void DotFlippersMatrix::setViewOrigin(int16_t x, int16_t y){
    viewOriginX = x;
    viewOriginY = y;
}

void DotFlippersMatrix::clear(uint8_t color) {
    for (int i=0; i<(WIDTH * HEIGHT); i++) {
        frameBuffer[i] = color;
    }
    for (int i=0; i<pixelWidth * ((pixelHeight+6)/7); i++) {
        displayBuffer[i] = color;
    }
}

void DotFlippersMatrix::drawPixel(int16_t x, int16_t y, uint16_t color) {
    // Serial.printf("x=%d, y=%d, c=%d\n", x, y, color);
    if (x>=WIDTH || y>=HEIGHT) return;
    if (x<0 || y<0) return;
    frameBuffer[ (y*WIDTH)+x ] = color;

}

void DotFlippersMatrix::display() {
    uint16_t index=0;
    uint16_t laneIndex=0;
    uint16_t dispSize = pixelWidth * ((pixelHeight+6)/7);
    uint8_t mask = 0x00;
    for(int x=viewOriginX; x<viewOriginX+pixelWidth; x++) {
        for(int y=viewOriginY; y<viewOriginY+pixelHeight; y++){
            laneIndex = (y-viewOriginY)/7;
            index = (x-viewOriginX)+(laneIndex*pixelWidth);
            index = dispSize - index - 1;
            mask = 0x01 << ((y-viewOriginY)%7);
            if (frameBuffer[((y%HEIGHT)*WIDTH) + (x%WIDTH)] != 0) {
                displayBuffer[ index ] |= mask;
            } else {
                displayBuffer[ index ] &= ~mask;
            }
            // Serial.print(index);
            // Serial.print(" ");
        }
    }
    // Serial.println(" ");
    // for (int i=0; i<dispSize; i++) {
    //     Serial.print(displayBuffer[i], HEX);
    //     Serial.print(" ");
    // }

    hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
    hspi->transferBytes(displayBuffer , NULL, dispSize);
    hspi->endTransaction();
}

void DotFlippersMatrix::flushDisplayBuffer() {
    uint16_t dispSize = pixelWidth * ((pixelHeight+6)/7);
    hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
    hspi->transferBytes(displayBuffer , NULL, dispSize);
    hspi->endTransaction();
}

uint8_t *DotFlippersMatrix::getBuffer() { return frameBuffer; }
uint8_t *DotFlippersMatrix::getDisplayBuffer() { return displayBuffer; }

DotFlippersMatrix::~DotFlippersMatrix(void) {
    if(frameBuffer) {
        free(frameBuffer);
        frameBuffer = NULL;
    }
    if (displayBuffer) {
        free(displayBuffer);
        displayBuffer = NULL;
    }
}