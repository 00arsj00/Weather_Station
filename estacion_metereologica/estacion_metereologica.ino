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
DHT dht(DHTPIN, DHTTYPE,22);

//memoria AT24cx
AT24C256 mem;
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

int direc=32765;
int dir;

String msg;

String meses[] = {" ","Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};

void setup() {
  pinMode(BUTTON_PIN, INPUT);//se configura pin de boton como entrada
  readDate();
  //lectura de direccion 
  dir = mem.readInt(direc); 
   if (digitalRead(BUTTON_PIN) == LOW) {
    // activacion por boton 
    msginicio(5000);
    plantilla();
    readSensors();
    writeDSensors(5000);
  } else if (minn == 10 || minn == 20 || minn == 30 || minn == 40 || minn == 50 || minn == 0 ) {
    msginicio(5000);
    plantilla();
    readSensors();
    writeDSensors(5000);
    saveData(1000);
  }
  esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_PIN, LOW);
  esp_sleep_enable_timer_wakeup(59 * 1000000ULL);
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
void writeDSensors(int tiempo){
  msg = String(day)+"/"+meses[month]+" -- "+String(hour)+":"+String(minn);
  tft.drawString(msg,50,15,2);
  //se escriben los nuevos datos del sensor en la pantalla
  tft.drawString(String(tem), 160,50, 4); 
  tft.drawString(String(hum), 160,75, 4);

  delay(tiempo);
}
void saveData(int tiempo){
  //se escriben los datos en la memoria
  //orden: tem hum mes dia hora minuto 
  mem.write(dir,tem);
  mem.write(dir+1,hum);
  mem.write(dir+2,hour);
  mem.write(dir+3,minn);
  mem.write(dir+4,month);
  mem.write(dir+5,day);
  dir+=6;

  mem.writeInt(direc,dir);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString("datos guardados", 0, 110, 2);
  tft.drawString(String((dir-6)/6), 110, 110, 2);
  delay(tiempo);
}
void msginicio(int tiempo)
  {
  tft.init();  
  tft.setRotation(1);
  tft.fillScreen(TFT_RED);
  tft.setTextColor(TFT_WHITE, TFT_RED);
  tft.drawString("ESTACION ", 60, 25, 4); 
  tft.drawString("METEREOLOGICA ", 15,50, 4); 
  tft.drawString("V0.3", 90, 75, 4); 
  delay(tiempo);
  }
void plantilla(){
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
void inicializar(){

}
void serialmsg(){
  //inicializacion de serial
  Serial.begin(115200);//se uso para verificar su funcionamiento

  msg="Date: "+String(day)+"/"+String(month)+" -- "+String(hour)+":"+String(minn)+" -- Tem="+String(tem)+"°C "+" Hum="+String(hum)+"%RH";
  Serial.println(msg);//para verificacion del codigo
}
