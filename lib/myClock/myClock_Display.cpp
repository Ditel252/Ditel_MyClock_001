#include "myClock_Display.h"

void My_Clock_Display::init(){
    My_Clock_Display::display.init();
    My_Clock_Display::display.clearDisplay();
    My_Clock_Display::display.setTextColor(TFT_WHITE, TFT_BLACK);
    My_Clock_Display::display.setBrightness(128);
    My_Clock_Display::display.setCursor(M5DIAL_DISPLAY_WIDETH / 2, M5DIAL_DISPLAY_HEIGHT / 2);
}

void My_Clock_Display::print(String _str, uint8_t _x, uint8_t _y, float _size, uint8_t _datum, uint32_t _textColor, int64_t _backgroundColor){
    if(_backgroundColor < 0)
        My_Clock_Display::display.setTextColor(_textColor);
    else
        My_Clock_Display::display.setTextColor(_textColor, (uint32_t)_backgroundColor);

    My_Clock_Display::display.setTextDatum(_datum);

    if(_size < 2){
        My_Clock_Display::display.setTextSize(_size);
        My_Clock_Display::display.drawString(_str, _x, _y, &lgfx::fonts::lgfxJapanGothic_20);
    }else{
        My_Clock_Display::display.setTextSize(_size - 1);
        My_Clock_Display::display.drawString(_str, _x, _y, &lgfx::fonts::lgfxJapanGothic_40);
    }
}

void My_Clock_Display::printb(String _str, uint8_t _x, uint8_t _y, float _size, uint8_t _datum, uint32_t _textColor, int64_t _backgroundColor){
    if(_backgroundColor < 0)
        My_Clock_Display::display.setTextColor(_textColor);
    else
        My_Clock_Display::display.setTextColor(_textColor, (uint32_t)_backgroundColor);
    
    My_Clock_Display::display.setTextDatum(_datum);
    My_Clock_Display::display.setTextSize(_size);
    My_Clock_Display::display.drawString(_str, _x, _y, &lgfx::fonts::FreeSansBold24pt7b);
}

int64_t My_Clock_Display::color(uint8_t _r, uint8_t _g, uint8_t _b){
    return (int64_t)My_Clock_Display::display.color888(_r, _g, _b);
}