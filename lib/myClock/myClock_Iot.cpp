#include "myClock_Iot.h"
#include <esp_wpa2.h>

int My_Clock_Iot::wifiConnect(NetWork_Info _netWork){
    bool connectToNetwork = false;
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);

    switch(_netWork.securityMode){
    case NETWORK_SECURITY_MODE_NORMAL:
        WiFi.begin(_netWork.ssid, _netWork.password);
        break;
    
    case NETWORK_SECURITY_MODE_WPA2:
        WiFi.begin(_netWork.ssid, WPA2_AUTH_PEAP, "",_netWork.userName, _netWork.password);
        break;
    }

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
    if(WiFi.disconnect(true))
        return MY_CLOCK_IOT_OK;
    else
        return MY_CLOCK_IOT_ERROR_DISCONNECT_FROM_NETWORK;
}

int My_Clock_Iot::saveToSpreadsheet(Subject_And_Time *_saveData, float _readData[][NUMBER_OF_SUBJECTS], uint8_t _numberOfSubject){
    HTTPClient http;
    String sendData = scriptBaseUrl + My_Clock_Iot::scriptUrl(_saveData, _numberOfSubject);
    http.begin(sendData.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    if(http.GET() != HTTP_CODE_OK){
        http.end();
        return MY_CLOCK_IOT_ERROR_UPDATE_DATA;
    }

    My_Clock_Iot::convetStrToFloat(http.getString(), _readData);
    http.end();

    return MY_CLOCK_IOT_OK;
}

String My_Clock_Iot::scriptUrl(Subject_And_Time *_subjectTime, uint8_t _numberOfSubject){
    String resultUrl = String("?") + (_subjectTime + 0)->nameEN + "=" + String((_subjectTime + 0)->time);

    for (uint8_t i = 1; i < _numberOfSubject; i++){
        resultUrl = resultUrl + "&" + (_subjectTime + i)->nameEN + "=" + String((_subjectTime + i)->time);
    }

    return resultUrl;
}

void My_Clock_Iot::convetStrToFloat(String _str, float _outData[][NUMBER_OF_SUBJECTS]){
    char charOfString[512];
    char str_temp[64] = {0};
    uint16_t countOfWord = 0;
    uint16_t countOfOutArray = 0;

    strcpy(charOfString, _str.c_str());

    while(1){
        countOfWord = 0;
        while(1){
            if(charOfString[countOfWord] == ','){
                strncpy(str_temp, charOfString, countOfWord);
                str_temp[countOfWord] = '\0';
                break;
            }else if(charOfString[countOfWord] == '\0'){
                strncpy(str_temp, charOfString, countOfWord);
                str_temp[countOfWord] = '\0';
                break;
            }

            countOfWord++;
        }

        int i = 0;

        while(1){
            charOfString[i] = charOfString[countOfWord + 1 + i];

            if(charOfString[i] == '\0')
                break;
            else
                i++;
        }

        if(countOfOutArray < 10)
            _outData[0][countOfOutArray] = atof(str_temp);
        else
            _outData[1][countOfOutArray % 10] = atof(str_temp);
        
        countOfOutArray++;

        if(charOfString[countOfWord] == '\0')
            break;
    }
}