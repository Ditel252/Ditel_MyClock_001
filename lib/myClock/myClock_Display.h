#include <Arduino.h>
#include <M5GFX.h>
#include <M5Dial.h>

#define M5DIAL_DISPLAY_WIDETH 240
#define M5DIAL_DISPLAY_HEIGHT 240 

class My_Clock_Display{
private:
    M5GFX display;
public:
    void init();
    void print(String _str, uint8_t _x, uint8_t _y, uint8_t _size = 1, uint8_t _datum  = top_left);
};