#include <Arduino.h>
const unsigned long TIME_WAIT = 5000;
const int LED_R = D6;
const int LED_Y = D7;
const int LED_G = D8;

unsigned long millis_current;
unsigned long millis_previous = 0;
unsigned int state;

void schalteAmpel(bool rot, bool gelb, bool gruen);
void setup() {
  Serial.begin(9600);  
  pinMode(LED_R, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_G, OUTPUT);
  schalteAmpel(LOW, LOW, LOW);
  state = 0;
}

void loop() {
  millis_current = millis();
  if(millis_current - millis_previous >= TIME_WAIT) {
    Serial.printf("Zustand: %i\n", state);
    switch(state){
      case 0: {
        //Rot
        schalteAmpel(HIGH, LOW, LOW);
        state = 1;
        break;
      }
      case 1: {
        //Rot-Gelb
        schalteAmpel(HIGH, HIGH, LOW);
        state = 2;
        break;
      }
      case 2: {
        //Grün
        schalteAmpel(LOW, LOW, HIGH);
        state = 3;
        break;
      }
      case 3: {
        //Gelb
        schalteAmpel(LOW, HIGH, LOW);
        state = 0;
        break;
      }
    }
    millis_previous = millis_current;
  }
}

void schalteAmpel(bool rot, bool gelb, bool gruen) {
  digitalWrite(LED_R, rot);
  digitalWrite(LED_Y, gelb);
  digitalWrite(LED_G, gruen);
}