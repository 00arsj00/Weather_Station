#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

int Data[5];
String msg; 

BluetoothSerial SerialBT;
void setup(){
SerialBT.begin("TTgo");
delay(5000);

SerialBT.println(msg);
}

void loop() {
  while (true){}
}

void sendData(){
  msg = "Dato_1,Dato_2,Dato_3,Dato_4,Dato_5";
  SerialBT.println(msg);
  for (int j = 1; j<101; j++){
    for (int i = 0; i<5; i++){
      Data[i] = random(1,100);
    }
    msg = String(Data[0]) + "," + String(Data[1]) + "," + String(Data[2]) + "," + String(Data[3]) + "," + String(Data[4]);
    SerialBT.println(msg);
  }
  
}
