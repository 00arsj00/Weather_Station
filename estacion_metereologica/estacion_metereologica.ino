//librerias
#include "DHT.h"
#include <AT24CX.h>
#include <TFT_eSPI.h>
#include "RTClib.h"

//objetos
//sensor de temperatura y humedad
#define DHTPIN 15
#define DHTTYPE DHT22
#define BUTTON_PIN 0
#define RAIN_PIN 33
DHT dht(DHTPIN, DHTTYPE,22);

//memoria AT24cx
AT24C256 memory;
//display
TFT_eSPI tft = TFT_eSPI();
//reloj
RTC_DS1307 rtc;

//variables

byte tem;
byte hum;

byte hour;
byte minn;
byte day;
byte month;

//DateTime now;

int lastDirection=32765;
int flag= lastDirection - 1;
int direction;

String msg;

String months[] = {" ","Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};

void setup() {
  pinMode(BUTTON_PIN, INPUT);//se configura pin de boton como entrada
  readDate();
  //lectura de direccion 
  direction = memory.readInt(lastDirection); 
   if (digitalRead(BUTTON_PIN) == LOW) {
    // activacion por boton 
    startMsg(5000);
    homeTemplate();
    readSensors();
    writeDSensors(5000);
  } else if (minn % 5 == 0) {
    startMsg(5000);
    homeTemplate();
    readSensors();
    writeDSensors(5000);
    saveData(1000);
  }
  esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_PIN, LOW);
  esp_sleep_enable_timer_wakeup(59 * 1000000ULL);
  attachInterrupt(digitalPinToInterrupt(RAIN_PIN), RainIterrupt, CHANGE);
  esp_deep_sleep_start();
}


void loop() {

}

void readDate(){
  rtc.begin(); //Inicializamos el RTC
  //se lee la hora actual del reloj 
  DateTime now = rtc.now();
  hour = now.hour();
  minn = now.minute();
  day = now.day();
  month = now.month();
}
void readSensors(){
  //inicializacion de sensor de temperatura y humedad
  dht.begin();
   //se leen los nuevos datos del sensor 
  hum = byte(dht.readHumidity());
  tem = byte(dht.readTemperature());

}
void writeDSensors(int time){
  msg = String(day)+"/"+months[month]+" -- "+String(hour)+":"+String(minn);
  tft.drawString(msg,50,15,2);
  //se escriben los nuevos datos del sensor en la pantalla
  tft.drawString(String(tem), 160,50, 4); 
  tft.drawString(String(hum), 160,75, 4);

  delay(time);
}
void saveData(int time){
  //se escriben los datos en la memoria
  //orden: tem hum mes dia hora minuto 
  memory.write(direction,tem);
  memory.write(direction+1,hum);
  memory.write(direction+2,hour);
  memory.write(direction+3,minn);
  memory.write(direction+4,month);
  memory.write(direction+5,day);
  direction+=6;

  memory.writeInt(lastDirection,direction);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString("datos guardados", 0, 110, 2);
  tft.drawString(String((direction-6)/6), 110, 110, 2);
  delay(time);
}
  void startMsg(int time)
  {
  tft.init();  
  tft.setRotation(1);
  tft.fillScreen(TFT_RED);
  tft.setTextColor(TFT_WHITE, TFT_RED);
  tft.drawString("ESTACION ", 60, 25, 4); 
  tft.drawString("METEREOLOGICA ", 15,50, 4); 
  tft.drawString("V0.3", 90, 75, 4); 
  delay(time);
  }
  void msgRainDetected(int time)
  {
  tft.setRotation(1);
  tft.fillScreen(TFT_BLUE);
  //forma de gota
  tft.fillCircle(64, 45, 10, TFT_BLUE); // Parte superior de la gota
  tft.fillTriangle(64, 55, 54, 75, 74, 75, TFT_BLUE); // Parte inferior de la gota
  
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.drawString("Lluvia Detectada", 60, 25, 2); 
  delay(time);
  }
  void msgRainUndetected(int time)
  {
  tft.setRotation(1);
  tft.fillScreen(TFT_BLUE);
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.drawString("Fin de lluvia", 60, 25, 2); 
  delay(time);
  }
void homeTemplate(){
  //plantilla
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("ESTACION METEREOLOGICA H0Pe.3 ", 10, 0, 2);
  tft.drawString("Date:", 10, 15, 2);
  tft.drawString("Temperatura: ", 0, 50, 4);
  tft.drawString("°C", 210, 50, 4);
  tft.drawString("Humedad:", 0, 75, 4);
  tft.drawString("%", 210, 75, 4);
}

void serialmsg(){
  //inicializacion de serial
  Serial.begin(115200);//se uso para verificar su funcionamiento

  msg="Date: "+String(day)+"/"+String(month)+" -- "+String(hour)+":"+String(minn)+" -- Tem="+String(tem)+"°C "+" Hum="+String(hum)+"%RH";
  Serial.println(msg);//para verificacion del codigo
}
void RainIterrupt(){
  if (digitalRead(RAIN_PIN) == LOW) {
    // activacion por boton
    msgRainUndetected(5000);
  } else if (digitalRead(RAIN_PIN) == HIGH) {
    msgRainDetected(5000);
  }
}
