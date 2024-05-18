#include <myClock.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

char *ssid = "elecom-9fde2b";
char *password = "ymkfc33rnd7u";
String host = "https://script.google.com/macros/s/AKfycbw-WPlHv_OJB4XCexAf9h2VX3uoAzlZ-TWt6zokJYp43k9Ur2wJz9e8Q_NGfxdQ4I6w/exec";

//https://script.google.com/macros/s/AKfycbw-WPlHv_OJB4XCexAf9h2VX3uoAzlZ-TWt6zokJYp43k9Ur2wJz9e8Q_NGfxdQ4I6w/exec

String PostRequest(String url, float temperature, float humidity)
{
    Serial.println("Start");
    HTTPClient http;
    Serial.println("OK1");
    String data = url + "?temperature=" + String(temperature) + "&humidity=" + String(humidity);
    Serial.println("OK2");
    http.begin(data.c_str());
    Serial.println("OK3");
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    Serial.println("OK4");
    http.GET();
    Serial.println("OK5");
    Serial.println(http.getString());
    Serial.println("OK6");
    Serial.println(data);
    Serial.println("OK7");
    http.end();
    Serial.println("Finish");

    /*
    //リダイレクトして、データを送る
    const char *headerNames[] = {"Location"}; // Locationをとる
    http.collectHeaders(headerNames, sizeof(headerNames) / sizeof(headerNames[0]));

    Serial.print("[HTTP POST] ...\n");
    int httpCode = http.POST(data);
    int status_code = http.GET();
    Serial.println("OK4");
    Serial.printf("\npost request: status code = %d\n", httpCode);
    Serial.printf("\nget request: status code = %d\n", status_code);

    if (status_code == HTTP_CODE_FOUND)
    {
        //リダイレクトされた 302
        String payload = http.getString();
        Serial.println(payload);

        // ヘッダのLocation（リダイレクト先URL）を取り出す
        Serial.println("Location");
        Serial.println(http.header("Location"));

        // リダイレクト先にGetリクエスト
        String redirect_url = http.header("Location");
        http.begin(redirect_url); // HTTP
        int httpCode = http.GET();

        if (httpCode == HTTP_CODE_OK)
        {
        String res = http.getString(); //目的のレスポンスが得られる
        Serial.println("GET RESPONSE!");
        Serial.println(res);
        return res;
        }
    }
    */

    return "0";
}

void setup(){
    Serial.begin(9600);

    delay(1000);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop(){
    Serial.println(PostRequest(host, 100, 100.1));
    

    delay(1000);
}

/*
void loop(){

  StaticJsonDocument<500> doc;
  char pubMessage[256];

  M5.update();
  
  if(M5.BtnA.wasPressed()){
 
    M5.Lcd.setCursor(0, 0, 1);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.println("Sending...");
    
    // JSONメッセージの作成
    JsonArray idValues = doc.createNestedArray("ID");
    idValues.add("12345");

    JsonArray dataValues = doc.createNestedArray("temp");
    dataValues.add("temp value");

    serializeJson(doc, pubMessage);

    // HTTP通信開始
    HTTPClient http;

    Serial.print(" HTTP通信開始　\n");
    http.begin(published_url);
   
    Serial.print(" HTTP通信POST　\n");
    int httpCode = http.POST(pubMessage);
   
    if(httpCode > 0){
      M5.Lcd.printf(" HTTP Response:%d\n", httpCode);
   
      if(httpCode == HTTP_CODE_OK){
        M5.Lcd.println(" HTTP Success!!");
        String payload = http.getString();
        Serial.println(payload);
      }
    }else{
      M5.Lcd.println(" FAILED");
      Serial.printf("　HTTP　failed,error: %s\n", http.errorToString(httpCode).c_str());
    }
   
    http.end();

    M5.Lcd.print("Please push button A \n");
   
  }
}
*/