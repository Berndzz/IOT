#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 15

// Define the pins being used
int pin_LED_A =2;
int pin_LED_B = 0;
int pin_LED_C = 4;
int pin_switch = 23;
int test =0;
 
// variables to hold the new and old switch states
boolean lastState = LOW;
boolean currentState = LOW;
 
boolean ledState = LOW;

DHT dht(DHTPIN,DHTTYPE);
 
void setup() 
{
    Serial.begin(115200);   
    pinMode(pin_LED_A, OUTPUT); 
    pinMode(pin_LED_B, OUTPUT);
    pinMode(pin_LED_C, OUTPUT); 
    digitalWrite(pin_LED_A,LOW); 
    digitalWrite(pin_LED_B,LOW);
    digitalWrite(pin_LED_C,LOW);
    
    pinMode(pin_switch, INPUT); 
    Serial.println("DHT Test");
    dht.begin();
}
 
void loop(){

//float h = dht.readTemperature();
float t = dht.readTemperature();
//float f = dht.readTemperature();

 currentState = digitalRead(pin_switch);
  if (currentState == HIGH && lastState == LOW) {
    if (ledState == HIGH) {
      if(t < 35){
      digitalWrite(pin_LED_A, LOW);  
     
      }
      else if(t > 35 && t <=50.00){
      digitalWrite(pin_LED_A, LOW); 
      digitalWrite(pin_LED_B, LOW); 
     
      }
      else if(t > 50.00){
      digitalWrite(pin_LED_A, LOW);
      digitalWrite(pin_LED_B, LOW);
      digitalWrite(pin_LED_C, LOW);
      //Serial.println("Darurat");
      
      }
      test = 0;
      Serial.println("Nyala");
      ledState = LOW;
    } else {
      digitalWrite(pin_LED_A, LOW);
      digitalWrite(pin_LED_B, LOW);
      digitalWrite(pin_LED_C, LOW);
      test = 1;
      Serial.println("Mati");
      ledState = HIGH;
    }
  }
  lastState = currentState;
  while (test < 1 ) {
    if(t < 35){
        digitalWrite(pin_LED_A, HIGH);
        Serial.println("Aman");
        Serial.print(F("%  Temperature: "));
        Serial.print(t);
        Serial.print(F("°C "));
        Serial.println("\n");
        delay(3000);
        turnOFF();
      }
      else if(t > 35 && t <=50.00){
      digitalWrite(pin_LED_A, HIGH);
      digitalWrite(pin_LED_B, HIGH);
      Serial.println("Siaga");
      Serial.print(F("%  Temperature: "));
      Serial.print(t);
      Serial.print(F("°C "));
      Serial.println("\n");
      delay(3000);
      turnOFF();
      }
      else if(t > 50.00){
      digitalWrite(pin_LED_A, HIGH);
      digitalWrite(pin_LED_B, HIGH);
      digitalWrite(pin_LED_C, HIGH);
      Serial.println("Darurat");
      Serial.print(F("%  Temperature: "));
      Serial.print(t);
      Serial.print(F("°C "));
      Serial.println("\n");
      delay(3000);
      turnOFF();
      }  

  
    Serial.print('\n');
    if (test == 0) {
      break;
    }
  } 
}

void turnOFF(){
  digitalWrite(pin_LED_A, LOW);
  digitalWrite(pin_LED_B, LOW);
  digitalWrite(pin_LED_C, LOW);
}
