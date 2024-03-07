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
  String msg;
  String mymonthName;
  String mydayname;
  char *myStrings[] = {"","lunes","martes","miercoles","jueves","viernes","sabado","domingo"};

//Objeto
RTC_DS1307 rtc;

void setup () {
  Serial.begin(9600);
  rtc.begin(); //Inicializamos el RTC
  Serial.println("Estableciendo Hora y fecha...");
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("DS1307 actualizado con la hora y fecha que se compilo este programa:");
  Serial.print("Fecha = ");
  Serial.print(__DATE__);
  Serial.print("  Hora = ");
  Serial.println(__TIME__);
}

void loop () {
 
    DateTime now = rtc.now();
    myhour=now.hour();
    mymin=now.minute();
    mysec=now.second();
    myday=now.day();
    mymonth=now.month();
    myear=now.year();
    mydayw=now.dayOfTheWeek();

    msg = String(myear)+"-"+mymonthName+"-"+String(myday)+"   "+String(myhour)+":"+String(mymin)+":"+String(mysec)+"   "+myStrings[mydayw];
    Serial.println(msg);

    delay(1000);
}
