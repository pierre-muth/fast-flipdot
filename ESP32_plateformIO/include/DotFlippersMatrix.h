
#include <Adafruit_GFX.h>


class DotFlippersMatrix : public Adafruit_GFX {
    public:
        DotFlippersMatrix(int16_t w, int16_t h);
        boolean begin();
        void drawPixel(int16_t x, int16_t y, uint16_t color);
        void clear(uint8_t color);
        uint8_t *getBuffer(void);
        uint8_t *getDisplayBuffer(void);
        void display(void);
        void flushDisplayBuffer(void);
        void setDisplayPixelSize(int16_t w, int16_t h);
        void setViewOrigin(int16_t x, int16_t y);

        ~DotFlippersMatrix(void);
    
    private:
        uint8_t *frameBuffer;
        uint8_t *displayBuffer;
        uint16_t pixelWidth = 8;
        uint16_t pixelHeight = 8;
        uint16_t viewOriginX = 0;
        uint16_t viewOriginY = 0;
        

};