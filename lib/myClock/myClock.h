#include "myClock_Display.h"
#include "myClock_Iot.h"

#define POSITION_OF_SETTING     10
#define POSITION_OF_SET_ALARM   11
#define POSITION_OF_UPDATE_DATA 12
#define POSITION_OF_NULL1       13
#define POSITION_OF_TIME        14
#define POSITION_OF_TOTAL_TIME  15

#define NUMBER_OF_REGISTERED_NETWORKS 4

class My_Clock{
private:
    float _timeDataArray[2][NUMBER_OF_SUBJECTS] = {0};
    char temporaryString[32];
public:
    My_Clock_Display Display;
    My_Clock_Iot Iot;
    My_Clock_Iot::Subject_And_Time subjectTime[NUMBER_OF_SUBJECTS];

    void init();
    void startAnimation();
    My_Clock_Iot::NetWork_Info selectNetwork();
    int connectToNetwork(My_Clock_Iot::NetWork_Info _network);
    int homeScreen();
    int updateData();
    void setDataName();
    void setDataTime();
    void timer(My_Clock_Iot::Subject_And_Time *_timer);
};