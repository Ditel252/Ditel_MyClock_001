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
//   strcpy(_network->ssid, "elecom-9fde2b");
//   strcpy(_network->password, "ymkfc33rnd7u");

//   strcpy(_network->ssid, "SD_Card");
//   strcpy(_network->password, "dssd05140520");
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

void My_Clock::setDataName(){
    strcpy((subjectTime + 0)->nameEN, "Control_Engineering");
    strcpy((subjectTime + 0)->nameJP, "制御工学");

    strcpy((subjectTime + 1)->nameEN, "Applied_Mathematics_B");
    strcpy((subjectTime + 1)->nameJP, "応用数学B");

    strcpy((subjectTime + 2)->nameEN, "Kinematics_Of_Kachines_II");
    strcpy((subjectTime + 2)->nameJP, "機械運動学II");

    strcpy((subjectTime + 3)->nameEN, "Electrodynamics_And_Magnetics_II");
    strcpy((subjectTime + 3)->nameJP, "電機磁気学II");

    strcpy((subjectTime + 4)->nameEN, "Applied_Physics_I");
    strcpy((subjectTime + 4)->nameJP, "応用物理I");

    strcpy((subjectTime + 5)->nameEN, "Applied_Mathematics_D");
    strcpy((subjectTime + 5)->nameJP, "応用数学D");

    strcpy((subjectTime + 6)->nameEN, "Measurement_Engineering");
    strcpy((subjectTime + 6)->nameJP, "計測工学");

    strcpy((subjectTime + 7)->nameEN, "German");
    strcpy((subjectTime + 7)->nameJP, "ドイツ語");

    strcpy((subjectTime + 8)->nameEN, "Synthetic_Japanese");
    strcpy((subjectTime + 8)->nameJP, "総合国語");

    strcpy((subjectTime + 9)->nameEN, "Information_Processing_III");
    strcpy((subjectTime + 9)->nameJP, "情報処理III");
}

void My_Clock::setDataTime(){
    for(int i = 0; i < NUMBER_OF_SUBJECTS; i++)
        (subjectTime + i)->totalTime = _timeDataArray[0][i];

    for(int i = 0; i < NUMBER_OF_SUBJECTS; i++)
        (subjectTime + i)->todaysTotalTime = _timeDataArray[1][i];
}

int My_Clock::homeScreen(){
    My_Clock::Display.display.clearDisplay(My_Clock::Display.color(MC_BLACK));

    int nowPosition, lastPosition;

    lastPosition = -999;
    nowPosition = 0;

    while(true){
        M5.update();

        nowPosition = M5Dial.Encoder.read();
        nowPosition = (nowPosition < 0) ? (64 - ((-1 *nowPosition) % 64)) : (nowPosition % 64);

        if(nowPosition != lastPosition){
            My_Clock::Display.printb("  " + String(nowPosition / 4) + "  ", 240 / 2, 240 / 2 - 50, 
                                    1, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));

            switch(nowPosition / 4){
            case POSITION_OF_SETTING:
                My_Clock::Display.print("　　　設定　　　", 240 / 2, 240 / 2, 
                                    2, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                My_Clock::Display.printb("          ", 240 / 2, 240 / 2 + 50, 
                                    0.8, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                My_Clock::Display.printb("          ", 240 / 2, 240 / 2 + 90, 
                                    0.6, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                break;
            case POSITION_OF_SET_ALARM:
                My_Clock::Display.print("　　アラーム設定　　", 240 / 2, 240 / 2, 
                                    2, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                My_Clock::Display.printb("          ", 240 / 2, 240 / 2 + 50, 
                                    0.8, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                My_Clock::Display.printb("          ", 240 / 2, 240 / 2 + 90, 
                                    0.6, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                break;
            case POSITION_OF_UPDATE_DATA:
                My_Clock::Display.print("　　データ更新　　", 240 / 2, 240 / 2, 
                                    2, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                My_Clock::Display.printb("          ", 240 / 2, 240 / 2 + 50, 
                                    0.8, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                My_Clock::Display.printb("          ", 240 / 2, 240 / 2 + 90, 
                                    0.6, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                break;
            case POSITION_OF_NULL1:
                My_Clock::Display.print("　　　NULL　　　", 240 / 2, 240 / 2, 
                                    2, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                My_Clock::Display.printb("          ", 240 / 2, 240 / 2 + 50, 
                                    0.8, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                My_Clock::Display.printb("          ", 240 / 2, 240 / 2 + 90, 
                                    0.6, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                break;
            case POSITION_OF_NULL2:
                My_Clock::Display.print("　　　NULL　　　", 240 / 2, 240 / 2, 
                                    2, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                My_Clock::Display.printb("          ", 240 / 2, 240 / 2 + 50, 
                                    0.8, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                My_Clock::Display.printb("          ", 240 / 2, 240 / 2 + 90, 
                                    0.6, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                break;
            case POSITION_OF_TIME:
                My_Clock::Display.print("　　　時計　　　", 240 / 2, 240 / 2, 
                                    2, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                My_Clock::Display.printb("          ", 240 / 2, 240 / 2 + 50, 
                                    0.8, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                My_Clock::Display.printb("          ", 240 / 2, 240 / 2 + 90, 
                                    0.6, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                break;
            default:
                My_Clock::Display.print("　　" + String((subjectTime + nowPosition / 4)->nameJP) + "　　", 240 / 2, 240 / 2, 
                                    2, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));

                sprintf(My_Clock::temporaryString, "%02d:%02d", (int)(subjectTime + nowPosition / 4)->totalTime, 
                        (int)((float)((float)((subjectTime + nowPosition / 4)->totalTime) - (int)((subjectTime + nowPosition / 4)->totalTime)) * 60.0));
                My_Clock::Display.printb("  " + String(My_Clock::temporaryString) + "  ", 240 / 2, 240 / 2 + 50, 
                                        0.8, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));

                sprintf(My_Clock::temporaryString, "%02d:%02d", (int)(subjectTime + nowPosition / 4)->todaysTotalTime, 
                        (int)((float)((float)((subjectTime + nowPosition / 4)->todaysTotalTime) - (int)((subjectTime + nowPosition / 4)->todaysTotalTime)) * 60.0));
                My_Clock::Display.printb("  " + String(My_Clock::temporaryString) + "  ", 240 / 2, 240 / 2 + 90, 
                                        0.6, middle_center, My_Clock::Display.color(MC_WHITE), My_Clock::Display.color(MC_BLACK));
                break;
            }
        }

        lastPosition = nowPosition;

        if(M5.BtnA.wasClicked())
            break;
    }

    return lastPosition;
}

int My_Clock::updateData(){
    My_Clock::Display.display.clearDisplay(My_Clock::Display.color(MC_WHITE));
    My_Clock::Display.printb("Update Data", 240 / 2, 240 / 2, 0.5, middle_center, My_Clock::Display.color(MC_ORANGE), -1);

    delay(100);

    int functionResult = My_Clock::Iot.saveToSpreadsheet(subjectTime, _timeDataArray, NUMBER_OF_SUBJECTS);

    if(functionResult == MY_CLOCK_IOT_OK){
        My_Clock::Display.printb("Updated!!", 240 / 2, 240 / 2 + 30, 0.5, middle_center, My_Clock::Display.color(MC_LAUN_GREEN), -1);
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

void My_Clock::timer(My_Clock_Iot::Subject_And_Time *_timer){
    My_Clock::Display.display.clear(My_Clock::Display.display.color888(MC_WHITE));

    My_Clock::Display.display.setTextColor(My_Clock::Display.display.color888(MC_ORANGE), My_Clock::Display.display.color888(MC_WHITE));
    My_Clock::Display.display.setTextDatum(middle_center);
    My_Clock::Display.display.setTextSize(1);
    My_Clock::Display.display.setCursor(120, 120);
    My_Clock::Display.display.setTextColor(TFT_BLACK, TFT_WHITE);

    My_Clock::Display.print(String(_timer->nameJP), 240 / 2, 240 / 2 - 30, 2, middle_center, My_Clock::Display.color(MC_LAUN_GREEN), My_Clock::Display.color(MC_WHITE));

    My_Clock::Display.display.setTextColor(My_Clock::Display.display.color888(MC_ORANGE), My_Clock::Display.display.color888(MC_WHITE));
    My_Clock::Display.display.setTextDatum(middle_center);
    My_Clock::Display.display.setTextSize(1);
    My_Clock::Display.display.drawString("00:00:00", 240 / 2, 240 / 2 + 17, &fonts::Font7);

    My_Clock::Display.display.setColor(My_Clock::Display.display.color888(MC_LIME));
    My_Clock::Display.display.fillRect(0, 170, 240, 240 - 170);
    My_Clock::Display.printb("Start", 240 / 2, 202, 1, middle_center, My_Clock::Display.display.color888(MC_WHITE), -1);

    unsigned long int startTime, stopTime = 0, lastReadTime = 0;

    bool isThisFirstTime = true;
    bool wasRequestedFinish = false;

    while(true){
        My_Clock::Display.display.setColor(My_Clock::Display.display.color888(MC_LIME));
        My_Clock::Display.display.fillRect(0, 170, 240, 240 - 170);
        My_Clock::Display.printb("Start", 240 / 2, 202, 1, middle_center, My_Clock::Display.display.color888(MC_WHITE), -1);

        while(true){
            M5Dial.update();
            auto touchStatus = M5Dial.Touch.getDetail();

            if(touchStatus.state != 0 && touchStatus.y > 170)
                break;

            delay(1);
            
            if(M5.BtnA.wasClicked()){
                wasRequestedFinish = true;
                break;
            }
        }

        if(wasRequestedFinish)
            break;

        while(true){
            M5Dial.update();
            auto touchStatus = M5Dial.Touch.getDetail();

            if(touchStatus.state == 0)
                break;

            delay(1);
        }

        if(isThisFirstTime){
            startTime = millis();
            isThisFirstTime = false;
        }else{
            startTime = millis() - stopTime;
        }

        My_Clock::Display.display.setColor(My_Clock::Display.display.color888(MC_RED));
        My_Clock::Display.display.fillRect(0, 170, 240, 240 - 170);
        My_Clock::Display.printb("Stop", 240 / 2, 202, 1, middle_center, My_Clock::Display.display.color888(MC_WHITE), -1);
        lastReadTime = millis();
        My_Clock::Display.display.setTextColor(My_Clock::Display.display.color888(MC_ORANGE), My_Clock::Display.display.color888(MC_WHITE));
        sprintf(My_Clock::temporaryString, "%02d:%02d:%02d", 
                (millis() - startTime) / (60 * 60 * 1000), 
                ((millis() - startTime) / (60 * 1000)) % 60, 
                ((millis() - startTime) / 1000) % 60);
        My_Clock::Display.display.drawString(My_Clock::temporaryString, 240 / 2, 240 / 2 + 17, &fonts::Font7);

        while(true){
            if((lastReadTime / 1000) != (millis() / 1000)){
                My_Clock::Display.display.setTextColor(My_Clock::Display.display.color888(MC_ORANGE), My_Clock::Display.display.color888(MC_WHITE));
                sprintf(My_Clock::temporaryString, "%02d:%02d:%02d", 
                        (millis() - startTime) / (60 * 60 * 1000), 
                        ((millis() - startTime) / (60 * 1000)) % 60, 
                        ((millis() - startTime) / 1000) % 60);
                My_Clock::Display.display.drawString(My_Clock::temporaryString, 240 / 2, 240 / 2 + 17, &fonts::Font7);
                lastReadTime = millis();
            }
            
            M5Dial.update();
            auto touchStatus = M5Dial.Touch.getDetail();

            if(touchStatus.state != 0 && touchStatus.y > 170)
                break;

            delay(1);
        }

        stopTime = millis() - startTime;

        while(true){
            M5Dial.update();
            auto touchStatus = M5Dial.Touch.getDetail();

            if(touchStatus.state == 0)
                break;

            delay(1);
        }
    }

    _timer->time = (float)((int)stopTime / 1000) / (float)(60 * 60);
}