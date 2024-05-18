#include "../lib/myClock/myClock.h"

My_Clock_Iot::NetWork_Info *network;
My_Clock_Iot::Subject_And_Time subjectTime[2];

My_Clock myClock;

int *a;

//https://script.google.com/macros/s/AKfycbw-WPlHv_OJB4XCexAf9h2VX3uoAzlZ-TWt6zokJYp43k9Ur2wJz9e8Q_NGfxdQ4I6w/exec

void setup(){
  network = (My_Clock_Iot::NetWork_Info *)malloc(sizeof(My_Clock_Iot::NetWork_Info));

  myClock.init();

  myClock.startAnimation();

  myClock.selectNetwork(network);

  myClock.connectToNetwork(*network);

  myClock.Display.display.clearDisplay(myClock.Display.color(MC_BLACK));

  delay(1000);

  strcpy((subjectTime + 0)->name, "Synthetic_Japanese");
  subjectTime[0].time = 123.4;

  strcpy((subjectTime + 1)->name, "Applied_Mathematics_D");
  subjectTime[1].time = 567.89;

}

void loop(){
  M5.update();

  myClock.Display.printb("  " + String(M5Dial.Encoder.read()) + "  ", 240/2, 240/2, 1, middle_center, myClock.Display.color(MC_AQUA), TFT_BLACK);

  delay(10);

  // if(myClock.Iot.saveToSpreadsheet(subjectTime, a, 2) == MY_CLOCK_IOT_OK){
  //   Serial.println("Send OK!!");
  // }    

  //   delay(1000);

  //   Serial.print("Done");
}