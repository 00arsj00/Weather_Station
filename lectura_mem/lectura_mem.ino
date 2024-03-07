//librerias
#include <AT24CX.h>
//objetos
//mem
AT24C256 mem;
//variables
int dir=32765;
byte temp;
byte hum;
byte hour;
byte minn;
byte day;
byte month;

int direc;
String msg;

//****************************************************************************
void setup() {
  Serial.begin(115200);
  Serial.println(F("lectura de memoria"));
  direc=mem.readInt(dir);
}

void loop() {
  //lectura de datos en memoria, cadena de temperatura y humedad
  for (int i=0;i<=direc;i+=6)
  {
    //orden:tem hum hora minuto mes dia 
    temp=mem.read(i);
    hum=mem.read(i+1);
    hour=mem.read(i+2);
    minn=mem.read(i+3);
    month=mem.read(i+4);
    day=mem.read(i+5);

    msg="i="+String(i/2)+" Date: "+String(day)+"/"+String(month)+" -- "+String(hour)+":"+String(minn)+" -- Temp="+String(temp)+"°C "+" Hum="+String(hum)+"%RH";
    Serial.println(msg);
  
  }

  while(true){}
}
