//librerias
#include <AT24CX.h>
//objetos
//mem
AT24C256 mem;
//variables
int dir=32765;
byte temp;
byte hum;
int direc;

//****************************************************************************
void setup() {
  Serial.begin(115200);
  Serial.println(F("lectura de memoria"));
  direc=mem.readInt(dir);
}

void loop() {
  //lectura de datos en memoria, cadena de temperatura y humedad
  for (int i=0;i<=direc;i+=2)
  {
    temp=mem.read(i);
    hum=mem.read(i+1);

    String msg="i="+String(i/2)+" Temp="+String(temp)+"°C "+" Hum="+String(hum)+"%RH";
    Serial.println(msg);
  
  }

  while(true){}
}
