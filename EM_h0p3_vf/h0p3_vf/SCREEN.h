class CLOCK.h
{
  private:
  #include <TFT_eSPI.h>
  //display
  TFT_eSPI tft = TFT_eSPI();


  public:
  
  
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
void Template_one(byte tem, byte hum){
  //plantilla
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("ESTACION METEREOLOGICA H0P3 vf ", 10, 0, 2);
  tft.drawString("Date:", 10, 15, 2);
  tft.drawString("Temperatura: ", 0, 50, 4);
  tft.drawString("°C", 210, 50, 4);
  tft.drawString("Humedad:", 0, 75, 4);
  tft.drawString("%", 210, 75, 4);
}
void Template_PM_2_5(){
  //plantilla
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("ESTACION METEREOLOGICA H0P3 vf ", 10, 0, 2);
  tft.drawString("Date:", 10, 15, 2);
  tft.drawString("Temperatura: ", 0, 50, 4);
  tft.drawString("°C", 210, 50, 4);
  tft.drawString("Humedad:", 0, 75, 4);
  tft.drawString("%", 210, 75, 4);
}
};