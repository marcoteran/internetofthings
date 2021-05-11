#define LED 22
#define BUTTON 15
#define SENSOR GPIO_NUM_4ardui
#include "Ubidots.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  digitalWrite(LED, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Enviar datos por el puerto serial
    int lum = analogRead(SENSOR);
    int brightness = map(lum, 2330, 3727, 0, 100);
    Serial.print("dato lum sensado: ");
    Serial.println(lum);
  
    if(digitalRead(BUTTON)==LOW){
      Serial.println("Se presiono el boton");
      digitalWrite(LED, HIGH);
      delay(2000);
      digitalWrite(LED, LOW);
    }else{
      Serial.println("no pasa nada");
      delay(1000);
    }
}
