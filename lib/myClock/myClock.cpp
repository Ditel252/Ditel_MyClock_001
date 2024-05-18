#include "myClock.h"

void My_Clock::init(){
    M5.begin();
    My_Clock::Display.init();
}