// This example sends data to multiple variables to
// Ubidots through HTTP protocol.

/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"
#include <DHT.h>

/****************************************
 * Define Instances and Constants
 ****************************************/
#define INTPIN 15
#define LED 22
#define DHTPIN 13
#define SENSOR GPIO_NUM_4
DHT dht(DHTPIN,DHT11); //instancia

bool ext_intFlag = 0;
bool pinChanged = 0;

const char* UBIDOTS_TOKEN = "BBFF-RWFlY7GGLfXunm0MZSXLo2mbmsgiRP";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "VIRUS_DETECTED";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "marco2016";      // Put here your Wi-Fi password
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

/****************************************
 * Auxiliar Functions
 ****************************************/

void readSensor(){
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.print("Temperatura: ");
  Serial.println(t);
  Serial.print("Humedad: ");
  Serial.println(h);
}

void checkPin(){
  ext_intFlag = !ext_intFlag;
  pinChanged = true;
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  ubidots.setDebug(true);  // Uncomment this line for printing debug messages

  pinMode(INTPIN,INPUT);
  pinMode(LED,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(INTPIN),checkPin,RISING);
  digitalWrite(LED,LOW);

  dht.begin();
}

void loop() {

  readSensor();
  
  float value1 = random(0, 9) * 10;
  float value2 = random(0, 9) * 100;
  float value3 = random(0, 9) * 1000;
  ubidots.add("Variable_Name_One", value1);  // Change for your variable name
  ubidots.add("Variable_Name_Two", value2);
  ubidots.add("Variable_Name_Three", value3);

  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }

  delay(5000);
}
