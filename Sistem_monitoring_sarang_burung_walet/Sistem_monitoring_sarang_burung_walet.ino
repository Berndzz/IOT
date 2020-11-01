
//library
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

//dht 11
#define DHTTYPE DHT11
#define DHTPIN 0

//pin digital
const int LDR_PIN = 36;
const int LED_PIN_ldr = 23;
const int LED_PIN_suhu = 2;

int pinValue;

//led virtual
WidgetLED ledVirt_ldr(V6);  
WidgetLED ledVirt_suhu(V7);

//konversi nilai adc
const double tetap = 0.009768;

//wifi 
char auth[] = "Zqj8ABfzZLBIWLdZU9Ulk-Z9hBcfZ8nf";
char ssid[] = "BALE";
char pass[] = "nutrijerukpakaies";


DHT dht(DHTPIN,DHTTYPE);
BlynkTimer timer;



BLYNK_WRITE(V4){
  int sliderLDR = param.asInt();
  int sliderLDR_value = (int) tetap*sliderLDR+10;
  Serial.print(F("Slider LDR : "));
  Serial.print(sliderLDR_value);
  Serial.print(F(" lux \n"));
  if(sliderLDR_value < 25){
     Blynk.setProperty(V6,"color","#43d381"); //hijau
  }
  else{
    Blynk.setProperty(V6,"color","#d3435c"); // merah
  }
}


void Kirim_Sensor_Cahaya(){

  int  x = analogRead(LDR_PIN);
  /*
   * rumus persamaan lux (pencahayaan)
    Y = 0,009768*X + 10
    Y = tingakat pencahayaan (LUX)
    X = nilai ADC misalnya nilai x 4096
  */
  //nilai adc 0-4095 == dikoversi berdasarkan rumus persamaan lux menjadi 50 
  //dibawa threshold (0-24)
  int y = tetap*x+10;
  int ldrValue = (int) y;
  Blynk.virtualWrite(V0,ldrValue);
  Blynk.virtualWrite(V2,ldrValue);
  Blynk.virtualWrite(V4,ldrValue);
  Blynk.virtualWrite(V6,ldrValue);
  //dibawaah threshold 
  if(ldrValue < 25 ){
    digitalWrite(LED_PIN_ldr,HIGH);
    Serial.print("Kecerahan: "); 
    Serial.print(ldrValue);
    ledVirt_ldr.on();
    Serial.println();
    Blynk.setProperty(V6,"color","#43d381");  //hijau
    delay(1);
  }
  //diatas threshold
  else if(ldrValue > 25 || ldrValue ==50){
    digitalWrite(LED_PIN_ldr,HIGH);
    Serial.print(F("Kecerahan: "));
    Serial.print(ldrValue);
    Serial.print(F(" lux "));
    ledVirt_ldr.on();
    Serial.println();
    Blynk.setProperty(V6,"color","#d3435c"); //merah
    delay(1); 
  }
}



BLYNK_WRITE(V5){
  int sliderSUHU_value = param.asInt();
  Serial.print(F("Slider SUHU : "));
  Serial.print(sliderSUHU_value);
  Serial.print(F(("°C \n")));
  if(sliderSUHU_value < 25){
    Blynk.setProperty(V7,"color","#43d381"); // hijau
  }
  else{
    Blynk.setProperty(V7,"color","#d3435c"); //merah
  }
}



void Kirim_Sensor_Suhu(){
  
  float t=dht.readTemperature();
  if(isnan(t)){
    Serial.println("Gagal membaca DHT Sensor!!");
    return;
  }
  //konversi ke int
  int T = (int) t;
  Blynk.virtualWrite(V1,T);
  Blynk.virtualWrite(V3,T);
  Blynk.virtualWrite(V5,T);
  Blynk.virtualWrite(V7,T);
  //dibawah threshold
  if(T < 25 ){
  Serial.println(F("Temperature: "));
  Serial.print(T);
  Serial.print(F("°C \n"));
  digitalWrite(LED_PIN_suhu,HIGH);
  ledVirt_suhu.on();
  Serial.println();
  Blynk.setProperty(V7,"color","#43d381"); // hijau
  delay(1);
  }
  //diatas threshold
  else if(T > 25 || T ==50){
  Serial.print(F("%  Temperature: "));
  Serial.print(T);
  Serial.print(F("°C "));
  digitalWrite(LED_PIN_suhu,HIGH);
  ledVirt_suhu.on();
  Serial.println();
  Blynk.setProperty(V7,"color","#d3435c"); //merah
  delay(1);
  }
}


BLYNK_WRITE(V8){
  pinValue = param.asInt();
  if(pinValue == 0){
   Serial.println("Button off");
  }
  else{
    Serial.println("Button on");
   }
}

void info(){
   Kirim_Sensor_Cahaya();
   Kirim_Sensor_Suhu();
}

void setup() {
 Serial.begin(115200);
 dht.begin();
 
 pinMode(LED_PIN_ldr,OUTPUT);
 pinMode(LED_PIN_suhu,OUTPUT);
 Blynk.begin(auth, ssid, pass, IPAddress(192,168,18,208), 8080);
 timer.setInterval(1000L,info); 
}



void loop() {
  Blynk.run();
 if(pinValue==1){
  timer.run();
 }
}


/*
credit by Hardus.
*/
