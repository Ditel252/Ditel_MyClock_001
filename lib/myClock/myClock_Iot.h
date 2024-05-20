#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

#define MY_CLOCK_IOT_OK 0
#define MY_CLOCK_IOT_ERROR_CONNECT_TO_NETWORK -1
#define MY_CLOCK_IOT_ERROR_DISCONNECT_FROM_NETWORK -2
#define MY_CLOCK_IOT_ERROR_UPDATE_DATA  -3

#define NUMBER_OF_SUBJECTS 10

class My_Clock_Iot{
private:
    //設定
    const String scriptBaseUrl = "https://script.google.com/macros/s/AKfycbxi7IOhBD6tGGu3aCOv7Z1XgsEDBp-PBcliaCINOGs-MYQ9eGYyiTwrQrBR5UEz9eKoOw/exec";

    void convetStrToFloat(String _str, float _outData[][NUMBER_OF_SUBJECTS]);
public:
    typedef struct{
        char ssid[32] = {0};
        char password[32] = {0};
    }NetWork_Info;

    typedef struct{
        char nameEN[128] = {0};
        char nameJP[128] = {0};
        float time = 0;
        float todaysTotalTime =0;
        float totalTime =0;
    }Subject_And_Time;

    int wifiConnect(NetWork_Info _netWork);
    int wifiDisconnect();
    int saveToSpreadsheet(Subject_And_Time *_saveData, float _readData[][NUMBER_OF_SUBJECTS], uint8_t _numberOfSubject);

    String scriptUrl(Subject_And_Time *_subjectTime, uint8_t _numberOfSubject);
};