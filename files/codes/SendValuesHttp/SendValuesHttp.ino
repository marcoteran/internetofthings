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

  float value = random(0, 9) * 10;
  
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.print("Temperatura: ");
  Serial.println(t);
  Serial.print("Humedad: ");
  Serial.println(h);
    
  ubidots.add("temperatura_marco", t);  // Change for your variable name
  ubidots.add("humedad_marco", h);

  /* Hardcoded Coordinates */
  float latitude = 4.660984864922051;
  float longitude = -74.05983339924464;

  /* Reserves memory to store context key values, add as much as you need */
  char* str_lat = (char*)malloc(sizeof(char) * 10);
  char* str_lng = (char*)malloc(sizeof(char) * 10);

  /* Saves the coordinates as char */
  sprintf(str_lat, "%f", latitude);
  sprintf(str_lng, "%f", longitude);

  /* Reserves memory to store context array */
  char* context = (char*)malloc(sizeof(char) * 30);

  /* Adds context key-value pairs */
  ubidots.addContext("lat", str_lat);
  ubidots.addContext("lng", str_lng);

  /* Builds the context with the coordinates to send to Ubidots */
  ubidots.getContext(context);

  /* Sends the position */
  ubidots.add("position", value, context);  // Change for your variable name

  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }

  delay(5000);
}
