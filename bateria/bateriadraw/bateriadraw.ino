#include <TFT_eSPI.h> // Incluye la biblioteca TFT_eSPI

TFT_eSPI tft = TFT_eSPI(); // Inicializa la pantalla TFT

void setup() {
  tft.init();
  tft.setRotation(0); // Ajusta la orientación de la pantalla si es necesario
}

void loop() {
  int nivelBateria = random(0, 5);
  dibujarBateria(nivelBateria);
  delay(2000); 
}

void dibujarBateria(int nivel) {
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(10, 10, 110, 180, TFT_WHITE);
  //tft.drawRect(10, 10, 110, 180, TFT_WHITE);
  tft.fillRect(35, 180, 55, 25, TFT_WHITE); 
  for(int i = 0; i < nivel; i++) {
    tft.fillRect(12, 12 + i*44, 107, 43, TFT_GREEN); 
  }
}

