#include "../lib/myClock/myClock.h"

My_Clock_Iot::NetWork_Info *network;

My_Clock myClock;

int *a;

//https://script.google.com/macros/s/AKfycbw-WPlHv_OJB4XCexAf9h2VX3uoAzlZ-TWt6zokJYp43k9Ur2wJz9e8Q_NGfxdQ4I6w/exec

void setup(){
  Serial.begin(9600);

  network = (My_Clock_Iot::NetWork_Info *)malloc(sizeof(My_Clock_Iot::NetWork_Info));

  myClock.init();

  myClock.startAnimation();

  myClock.selectNetwork(network);

  myClock.connectToNetwork(*network);

  myClock.setDataName();

  myClock.updateData();

  myClock.setDataTime();
}

void loop(){
  for(int i = 0; i < NUMBER_OF_SUBJECTS; i++)
    (myClock.subjectTime + i)->time = 0;

  int selectMode = myClock.homeScreen() / 4;

  myClock.timer(&(myClock.subjectTime[selectMode]));

  myClock.updateData();

  myClock.setDataTime();
}