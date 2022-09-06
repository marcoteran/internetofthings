#include <dht.h>

#define BUTTON 15
#define LED 22
#define DHTPIN 13

// Instancias
DHT dht(DHTPIN,DHT11);  // Creats a DHT object

void setup()
{
	Serial.begin(115200);
	delay(100);
	
	pinMode(DHTPIN, INPUT);
  	dht.begin();

}
void loop() 
{

	float h = dht.readHumidity();
  	float t = dht.readTemperature();

	// Printing the results on the serial monitor
	Serial.print("Humedad: ");
  	Serial.print(h);
  	Serial.println(" % ");

  	Serial.print("Temperatura: ");
  	Serial.println(t);
  	Serial.print(" ");
	Serial.print((char)176);//shows degrees character
	Serial.println("C");

	delay(2000); // Delays 2 secods
}


