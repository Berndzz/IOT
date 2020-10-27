const int ledBiru_A =2;
const int ledBiru_B =0;
const int ledBiru_C =4;

bool ledState = LOW;

// setiap millis diisi dengan 0
unsigned long prevMillis_A =0;  
unsigned long prevMillis_B =0;
unsigned long prevMillis_C =0;

unsigned long interval_B_A =1000;
unsigned long interval_B_B =2000;
unsigned long interval_B_C =3000;

unsigned long currentMills_ALL =0;

void setup() {
  pinMode(ledBiru_A,OUTPUT); // SET PIN 
  pinMode(ledBiru_B,OUTPUT);
  pinMode(ledBiru_C,OUTPUT);
}

void loop() {
  currentMills_ALL = millis();
  
  proses_Biru_A();
  proses_Biru_B();
  proses_Biru_C();
}

void proses_Biru_A(){
  if(currentMills_ALL - prevMillis_A >= interval_B_A){
    prevMillis_A = currentMills_ALL;
    ledState  = !ledState;
    digitalWrite(ledBiru_A,ledState);
  }
}

void proses_Biru_B(){
  if(currentMills_ALL - prevMillis_B >= interval_B_B){
    prevMillis_B = currentMills_ALL;
    ledState  = !ledState;
    digitalWrite(ledBiru_B,ledState);
  }
}

void proses_Biru_C(){
  if(currentMills_ALL - prevMillis_C >= interval_B_C){
    prevMillis_C = currentMills_ALL;
    ledState  = !ledState;
    digitalWrite(ledBiru_C,ledState);
  }
}
