#include "myClock_Display.h"
#include "myClock_Iot.h"

class My_Clock{
private:
public:
    My_Clock_Display Display;
    My_Clock_Iot Iot;

    void init();
    void startAnimation();
    void selectNetwork(My_Clock_Iot::NetWork_Info *_network);
    int connectToNetwork(My_Clock_Iot::NetWork_Info _network);
};