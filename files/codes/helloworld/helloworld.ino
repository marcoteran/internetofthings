#define LED 2
#define BUTTON 7
#define SENSOR 0
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  
  digitalWrite(LED, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Enviar datos por el puerto serial
    int lum = analogRead(SENSOR);
    Serial.print("dato lum sensado: ");
    Serial.println(lum);
    if(digitalRead(BUTTON)==LOW){
      Serial.println("Se presiono el boton");
      digitalWrite(LED, HIGH);
      delay(2000);
      digitalWrite(LED, LOW);
    }else{
      Serial.print("no pasa nada");
      delay(1000);
    }

}
