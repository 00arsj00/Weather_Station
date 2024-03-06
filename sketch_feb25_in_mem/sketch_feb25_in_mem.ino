//librerias
#include <AT24CX.h>
//objetos
//se utiliza lamemoria AT24C256
//tiene 256kbits
//32768 bytes
AT24C256 mem;
//variables
int dir = 32765;//direccion donde se grabara el dato
int dato;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(F("inicializar memoria"));
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(F("dato actual: "));
  dato = mem.readInt(dir);
  Serial.println(String(dato));

  mem.writeInt(dir, 0);

  Serial.print(F("dato guardado: "));
  dato = mem.readInt(dir);
  Serial.println(String(dato));
  while (true) {}
}
