#include "myClock_Iot.h"

int My_Clock_Iot::wifiConnect(NetWork_Info _netWork){
    bool connectToNetwork = false;

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(_netWork.ssid, _netWork.password);

    for(int i  = 0; i <= 100; i++){
        if(WiFi.status() == WL_CONNECTED){
            connectToNetwork = true;
            break;
        }

        delay(100);
    }

    if(connectToNetwork)
        return MY_CLOCK_IOT_OK;
    else
        return MY_CLOCK_IOT_ERROR_CONNECT_TO_NETWORK;
}

int My_Clock_Iot::wifiDisconnect(){
    if(WiFi.disconnect())
        return MY_CLOCK_IOT_OK;
    else
        return MY_CLOCK_IOT_ERROR_DISCONNECT_FROM_NETWORK;
}

int My_Clock_Iot::saveToSpreadsheet(Subject_And_Time *_saveData, int *_readData, uint8_t _numberOfSubject){
    HTTPClient http;
    String sendData = My_Clock_Iot::scriptUrl(_saveData, _numberOfSubject);
    http.begin(sendData.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    http.GET();
    Serial.println(http.getString());
    Serial.println(sendData);
    http.end();

    return MY_CLOCK_IOT_OK;
}

String My_Clock_Iot::scriptUrl(Subject_And_Time *_subjectTime, uint8_t _numberOfSubject){
    String resultUrl = scriptBaseUrl + "?" + (_subjectTime + 0)->name + "=" + String((_subjectTime + 0)->time);

    for (uint8_t i = 1; i < _numberOfSubject; i++){
        resultUrl = resultUrl + "&" + (_subjectTime + i)->name + "=" + String((_subjectTime + i)->time);
    }

    return resultUrl;
}