#include "../lib/myClock/myClock.h"

My_Clock_Iot::NetWork_Info *network;

My_Clock myClock;

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
  int selectMode = myClock.homeScreen() / 4;

  switch(selectMode){
  case POSITION_OF_SETTING:
    break;
  case POSITION_OF_SET_ALARM:
    break;
  case POSITION_OF_UPDATE_DATA:
    myClock.Iot.wifiDisconnect();
    myClock.connectToNetwork(*network);
    if(myClock.updateData() == MY_CLOCK_IOT_OK){
      for(int i = 0; i < NUMBER_OF_SUBJECTS; i++)
        (myClock.subjectTime + i)->time = 0;
        
      myClock.setDataTime();
    }
    break;
    break;
  case POSITION_OF_NULL1:
    break;
  case POSITION_OF_NULL2:
    break;
  case POSITION_OF_TIME:
    break;
  default:
    myClock.timer(&(myClock.subjectTime[selectMode]));
    if(myClock.updateData() == MY_CLOCK_IOT_OK){
      for(int i = 0; i < NUMBER_OF_SUBJECTS; i++)
        (myClock.subjectTime + i)->time = 0;

      myClock.setDataTime();
    }
    break;
  }
}