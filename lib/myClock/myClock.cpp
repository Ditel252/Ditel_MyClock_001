#include "myClock.h"

void My_Clock::init(){
    M5.begin();
    auto cfg = M5.config();
    M5Dial.begin(cfg, true, false);
    My_Clock::Display.init();
}

void My_Clock::startAnimation(){
    for (uint8_t i = 0; i < 127; i++){
        My_Clock::Display.printb("My Clock", 240 / 2, 240 / 2, 0.9, middle_center, My_Clock::Display.color(i*2, i*2, i*2), My_Clock::Display.color(MC_BLACK));
        delay(15);
    }

    delay(100);
    My_Clock::Display.printb("Ditel252", 240 / 2, 240 / 2 + 50, 0.6, middle_center, My_Clock::Display.color(MC_AQUA), My_Clock::Display.color(MC_BLACK));

    while(true){
        M5.update();
        if(M5.BtnA.wasClicked())
            break;
    }
}

void My_Clock::selectNetwork(My_Clock_Iot::NetWork_Info *_network){
  strcpy(_network->ssid, "elecom-9fde2b");
  strcpy(_network->password, "ymkfc33rnd7u");
}

int My_Clock::connectToNetwork(My_Clock_Iot::NetWork_Info _network){
    My_Clock::Display.display.clearDisplay(My_Clock::Display.color(MC_WHITE));
    My_Clock::Display.printb("Connect to Network", 240 / 2, 240 / 2, 0.5, middle_center, My_Clock::Display.color(MC_ORANGE), -1);

    delay(100);

    int functionResult = My_Clock::Iot.wifiConnect(_network);

    if(functionResult == MY_CLOCK_IOT_OK){
        My_Clock::Display.printb("WiFi Connected!!", 240 / 2, 240 / 2 + 30, 0.5, middle_center, My_Clock::Display.color(MC_LAUN_GREEN), -1);
    }else{
        My_Clock::Display.printb("Error", 240 / 2, 240 / 2 + 30, 0.5, middle_center, My_Clock::Display.color(MC_RED), -1);
    }

    while(true){
        M5.update();
        if(M5.BtnA.wasClicked())
            break;
    }

    return functionResult;
}

