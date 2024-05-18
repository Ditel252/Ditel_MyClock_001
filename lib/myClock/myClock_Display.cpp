#include "myClock_Display.h"

void My_Clock_Display::init(){
    My_Clock_Display::display.init();
    My_Clock_Display::display.clearDisplay();
    My_Clock_Display::display.setTextColor(WHITE);
    My_Clock_Display::display.setCursor(M5DIAL_DISPLAY_WIDETH / 2, M5DIAL_DISPLAY_HEIGHT / 2);
}

void My_Clock_Display::print(String _str, uint8_t _x, uint8_t _y, uint8_t _size, uint8_t _datum){
    My_Clock_Display::display.setTextSize(_size);
    My_Clock_Display::display.setTextDatum(_datum);
    My_Clock_Display::display.drawString(_str, _x, _y);
}