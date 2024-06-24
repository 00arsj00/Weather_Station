class CLOCK.h
{
  private:
  //Librería
  //#include <Wire.h>
  #include "RTClib.h"

  //Variables
  byte myhour;
  byte mymin;
  byte mysec;
  byte myday;
  byte mymonth;
  int myear;
  byte mydayw;
  byte rDate[4];
  String msg;

  //Objeto
  RT_DS1307 rtc;

  public:
  void clock_begin(){
    rtc.begin(); //Inicializamos el RTC
  }

  byte Read_date(){
    DateTime now = rtc.now();
    rDate[0] = now.hour();
    rDate[1] = now.minute();
    rDate[2] = now.day();
    rDate[3] = now.month();
    return rDate[4];
  }
 
};