#include <WiFi.h>
#include <FirebaseESP32.h>
#include <HCSR04.h>
#include "DHT.h"

#define DHTTYPE DHT11
#define FIREBASE_HOST "https://mini-project-4-5c843.firebaseio.com/"
#define FIREBASE_AUTH "Cz3ii6OemI15whuSijdY5KYIj1heVQOHbCB29cJU"
#define WIFI_SSID "BALE"
#define WIFI_PASSWORD "nutrijerukpakaies"

int dhtPin = 23;
int trig = 12;
int echo = 14;

UltraSonicDistanceSensor distanceSensor(trig,echo);
DHT dht(dhtPin,DHTTYPE);

FirebaseData firebaseData;

double oldDistance;
double newDistance;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);

  initWifi();
  dht.begin();
  oldDistance = distanceSensor.measureDistanceCm();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  
  float t=dht.readTemperature();;
  float h=dht.readHumidity();
  if (isnan(t) || isnan(h)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }  
  Firebase.setFloat(firebaseData ,"/data/temperature" , t);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  Firebase.setFloat(firebaseData ,"/data/humidity" , h);
  Serial.print(F("%  Humadity: "));
  Serial.println(h);

  newDistance = distanceSensor.measureDistanceCm();
  if(newDistance != oldDistance){
    Firebase.setInt (firebaseData ,"/data/distance" , newDistance*100); // krn volt nya kurang 
    oldDistance = newDistance;
  }  
Serial.println(oldDistance);
}

void initWifi(){

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setMaxRetry(firebaseData,3);
  Firebase.setMaxErrorQueue(firebaseData,30); 
  Firebase.setReadTimeout(firebaseData,1000*60);
  Firebase.setwriteSizeLimit(firebaseData , "tiny");
}
