#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

#define MY_CLOCK_IOT_OK 0
#define MY_CLOCK_IOT_ERROR_CONNECT_TO_NETWORK -1
#define MY_CLOCK_IOT_ERROR_DISCONNECT_FROM_NETWORK -2

#define SIZE_OF_SAVE_DATA 9

class My_Clock_Iot{
private:
    //設定
    const String scriptBaseUrl = "https://script.google.com/macros/s/AKfycbz-bfnWkn8lsAudq1v1u8KZVCDFQix4DtGWurQD1IzetLIj2rTqStgtt61yHLN44AhN/exec";
public:
    typedef struct{
        char ssid[32] = {0};
        char password[32] = {0};
    }NetWork_Info;

    typedef struct{
        char name[128] = {0};
        float time = 0;
    }Subject_And_Time;

    int saveDataToSpreadsheet[SIZE_OF_SAVE_DATA] = {0};

    int wifiConnect(NetWork_Info _netWork);
    int wifiDisconnect();
    int saveToSpreadsheet(Subject_And_Time *_saveData, int *_readData, uint8_t _numberOfSubject);

    String scriptUrl(Subject_And_Time *_subjectTime, uint8_t _numberOfSubject);
};