#include <Servo_ESP32.h>
#include "DHT.h"
#define DHTTYPE DHT11
#include <WiFi.h>
#include <MQTT.h>

int servoPin =14;
const int dhtPin =23;

const char ssid[] = "Hidden";
const char pass[] = "Englishh";

Servo_ESP32 myServo;
//Servo myServo;
DHT dht(dhtPin,DHTTYPE);
WiFiClient net;
MQTTClient client;


int butt=0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("ESP32", "052b5c8c", "e6d8962dbfe86ce5")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

    client.subscribe("/mini");
    client.subscribe("/miniDegree");
    client.subscribe("/onOff");
    
}


void sensor(){
    float t = dht.readTemperature();
     if(isnan(t)){
    Serial.println("gagal membaca dht Sensor!!");
    return;
  }
  int T = (int) t;
  if(T < 29){ 
      myServo.write(45);
      delay(1);
      myServo.write(0);
      delay(1);
       myServo.write(90);
      delay(1);
      client.publish("/mini",String(T).c_str());
      client.publish("/miniDegree",String(45).c_str());
      delay(1);
      client.publish("/miniDegree",String(0).c_str());
      delay(1);
      client.publish("/miniDegree",String(90).c_str());
      delay(1);
     
  }
  else if(T >30){
    myServo.write(135);
    delay(1);
    myServo.write(180);
    delay(1);
    myServo.write(90);
      client.publish("/mini",String(T).c_str());
      client.publish("/miniDegree",String(135).c_str());
      delay(1);
      client.publish("/miniDegree",String(180).c_str());
      delay(1);
      client.publish("/miniDegree",String(90).c_str());
      delay(1);
     
  }
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if(topic == "/onOff"){
    if(payload == "on"){
      butt=1;
      Serial.println("nyalakan sistem");
    }
    else if(payload == "off"){
      butt=0;
      client.disconnect();
      Serial.println("matikan sistem");
    }
  }
}

void setup() {
  // put your setup code here, to run once: 
  Serial.begin(115200);
  myServo.attach(servoPin);
  dht.begin();
  WiFi.begin(ssid, pass);
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);
  connect();
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
  
  if(butt==1){
    sensor();
  }
  
}
