#include "ESP_BAT.h"
#include <TFT_eSPI.h>

ESP_BAT bat;
TFT_eSPI tft = TFT_eSPI();

boolean statusBat;
float voltagebat;
String msg;
float porcentbat;



void setup() {
  Serial.begin(9600);
  tft.init();  
  tft.setRotation(1);
  tft.fillScreen(TFT_RED);
  tft.setTextColor(TFT_WHITE, TFT_RED);
}

void loop() {
  //statusBat = bat.isCharging();
  voltagebat = bat.get_voltage();
  porcentbat = (76.9*voltagebat)-230.7;
  msg = String(porcentbat) + " %";
  Serial.println(voltagebat);
  tft.drawString(msg, 60, 25, 6); 
}
