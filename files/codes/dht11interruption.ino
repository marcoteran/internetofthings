#include <DHT.h>

#define BUTTON 15
#define LED 22
#define DHTPIN 13

// Instancias
DHT dht(DHTPIN,DHT11);  // Creats a DHT object
bool ext_intFlag = 0;
bool pinChanged = 0;

// Upstream
void sendSensor(){
	float h = dht.readHumidity();
	float t = dht.readTemperature();
	Serial.print("Humedad: ");
  	Serial.print(h);
  	Serial.println(" % ");

  	Serial.print("Temperatura: ");
  	Serial.println(t);
  	Serial.print(" ");
	Serial.print((char)176);//shows degrees character
	Serial.println("C");
}

void checkbutton(){
  ext_intFlag = !ext_intFlag;
  pinChanged = true;
}

void setup()
{
	Serial.begin(115200);
	pinMode(BUTTON,INPUT);
	attachInterrupt(digitalPinToInterrupt(BUTTON),checkbutton,RISING);
	pinMode(LED,OUTPUT);
  	digitalWrite(LED,LOW);

  	pinMode(DHTPIN, INPUT);
  	dht.begin();
}


void loop() 
{
	// put your main code here, to run repeatedly:
	if(pinChanged){
		if(ext_intFlag){
			digitalWrite(LED,HIGH);
			sendSensor();
		}else{
			digitalWrite(LED,LOW);
		}
		pinChanged=0;
	}
}