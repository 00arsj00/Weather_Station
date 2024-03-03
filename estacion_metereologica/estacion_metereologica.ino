//librerias
//comemtario de prueba
#include "DHT.h"
#include <AT24CX.h>
#include <TFT_eSPI.h>

//objetos
//sensor de temperatura y humedad
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE,22);
//memoria AT24cx
AT24C256 mem;
//display
TFT_eSPI tft = TFT_eSPI();

//variables

byte tem;
byte hum;
int direc=32765;
int dir;
int i=0;

void setup() {
  //inicializacion de sensor de temperatura y humedad
  dht.begin();
  //lectura de direccion 
  dir = mem.readInt(direc);
  //inicializacion de display
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_RED);
  tft.setTextColor(TFT_WHITE, TFT_RED);
  tft.drawString("ESTACION ", 60, 25, 4); 
  tft.drawString("METEREOLOGICA ", 15,50, 4); 
  tft.drawString("V0.1", 90, 75, 4); 
  delay(5000);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("ESTACION METEREOLOGICA V0.1 ", 10, 0, 2);
  tft.drawString("Temperatura: ", 0, 50, 4);
  tft.drawString("°C", 210, 50, 4);
  tft.drawString("Humedad:", 0, 75, 4);
  tft.drawString("%", 210, 75, 4);
}


void loop() {
  //se leen los nuevos datos del sensor 
  hum = byte(dht.readHumidity());
  tem = byte(dht.readTemperature());

  //se escriben los nuevos datos del sensor en la pantalla
  tft.drawString(String(tem), 160,50, 4); 
  tft.drawString(String(hum), 160,75, 4);
  delay(5000);
  //se escriben los datos en la memoria
  mem.write(dir,tem);
  dir+=1;
  mem.write(dir,hum);
  dir+=1;
  //se guarda la direccion de memoria cada 6 mediciones
  mem.writeInt(direc,dir);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString("datos guardados", 0, 110, 2);
  tft.drawString(String(dir-2), 110, 110, 2);
  delay(1000);
  
  esp_sleep_enable_timer_wakeup(590000000);  // Configura el temporizador para despertar después de 10 minutos
  //esp_sleep_enable_timer_wakeup(9500000);  // Configura el temporizador para despertar después de 10 minutos
  esp_deep_sleep_start();
}
