#define BLYNK_PRINT Serial

#include <DHT.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define BUTTON 15
#define LED 22
#define DHTPIN 13

// Instancias
DHT dht(DHTPIN,DHT11);
BlynkTimer timer;
WidgetLED appled(V1);

char token[]="w02JA60KsAY_LAoH58BQQHUMzKLlaVLf";

bool ext_intFlag = 0;
bool pinChanged = 0;

//Funciones
// Downstream
BLYNK_WRITE(V0){
  int V0data = param.asInt(); // param.asString param.asDouble
  Serial.print("Valor de V0: ");
  Serial.println(V0data);
  digitalWrite(LED,V0data);
}

// Upstream
void sendSensor(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Humedad: ");
  Serial.println(h);
  Serial.print("Temperatura: ");
  Serial.println(t);

  Blynk.virtualWrite(V2,h);
  Blynk.virtualWrite(V3,t);
}

void checkbutton(){
  ext_intFlag = !ext_intFlag;
  pinChanged = true;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(BUTTON,INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON),checkbutton,RISING);
  pinMode(LED,OUTPUT);

  digitalWrite(LED,LOW);

  dht.begin();
  timer.setInterval(2000L,sendSensor);

  Blynk.begin(token,"VIRUS_DETECTED","marco2016");
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();

  if(pinChanged){
    if(ext_intFlag){
      appled.on();
    }else{
      appled.off();
    }
    pinChanged=0;
  }
}
