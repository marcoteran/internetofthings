// Pines a utilizar
#define DHTPIN 14

boolean estado = true;
// Librerías
#include "DHT.h"

//configuraciones iniciales del DHT11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Inicio");

  pinMode(LED,OUTPUT);
  pinMode(BUTTON,INPUT);

  dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  if(estado){
    float humedad = dht.readHumidity();
    float temperatura = dht.readTemperature();
    Serial.println(humedad);
    Serial.println(temperatura);       
  }
  delay(2000);
}