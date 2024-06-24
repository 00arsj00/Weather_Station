class TEM_HUM.h
{
  private:
  //librerias
  #include "DHT.h" //tem hum
  //objeto
  #define DHTPIN 15
  #define DHTTYPE DHT22
  #define BUTTON_PIN 0
  #define RAIN_PIN 33
  DHT dht(DHTPIN, DHTTYPE,22);
  
  //variables
  byte tem;
  byte hum;
  
  public:
  //---------------------------------------------------------
  //inicializar sensores
  void sensor_begin(){
    dht.begin();

  }
  //---------------------------------------------------------
  //sensor de temperatura y humedad
  byte Read_Tem(){
    tem = byte(dht.readTemperature());
    return tem;
  }
  byte Read_Hum(){
    hum = byte(dht.readHumidity());
    return hum;
  }

  //---------------------------------------------------------
  //sensor de pm2.5

  //---------------------------------------------------------
  //sensor de lluvia

 
};