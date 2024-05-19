#include <Arduino.h>
#include <M5Unified.h>
#include <M5Dial.h>

#define M5DIAL_DISPLAY_WIDETH 240
#define M5DIAL_DISPLAY_HEIGHT 240 
#define baseDisplay Display.display

#define MC_WHITE        255,255,255
#define MC_BLACK        0,0,0
#define MC_ORANGE       255,165,0
#define MC_AQUA         0,255,255
#define MC_RED          255,0,0
#define MC_LAUN_GREEN   154,205,50
#define MC_LIME         0,200,0

class My_Clock_Display{
private:
public:
    M5GFX display;
    void init();
    void print(String _str, uint8_t _x, uint8_t _y, float _size = 2, uint8_t _datum  = top_left, uint32_t _textColor = TFT_WHITE, int64_t _backgroundColor = TFT_BLACK);
    void printb(String _str, uint8_t _x, uint8_t _y, float _size, uint8_t _datum, uint32_t _textColor, int64_t _backgroundColor);
    int64_t color(uint8_t _r, uint8_t _g, uint8_t _b);
};