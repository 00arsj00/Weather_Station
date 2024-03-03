//librerias
#include <AT24CX.h>
//objetos
AT24C256 mem;
//variables
int dir = 32765;
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
