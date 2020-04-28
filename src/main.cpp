#include <Arduino.h>
const unsigned long TIME_WAIT = 5000;

const int LEDS[3] = {D6, D7, D8}; //rot, gelb, gruen

unsigned long millis_current;
unsigned long millis_previous = 0;
unsigned int state;

void schalteAmpel(bool led_states[3]);

void setup() {
  bool led_states[3] = {LOW, LOW, LOW};
  Serial.begin(9600); 
  Serial.printf("Anzahl Felder in LEDS: %i\n", sizeof(LEDS)/sizeof(int)); 
  for(unsigned int i = 0; i < sizeof(LEDS)/sizeof(int); i++) {
    pinMode(LEDS[i], OUTPUT);
  }
  schalteAmpel(led_states);
  state = 0;
}

void loop() {
  bool led_states[3];
  millis_current = millis();
  if(millis_current - millis_previous >= TIME_WAIT) {
    Serial.printf("Zustand: %i\n", state);
    switch(state){
      case 0: {
        //Rot
        led_states[0] = HIGH;
        led_states[1] = LOW;
        led_states[2] = LOW;
        schalteAmpel(led_states);
        state = 1;
        break;
      }
      case 1: {
        //Rot-Gelb
        schalteAmpel(led_states);
        state = 2;
        break;
      }
      case 2: {
        //Grün
        schalteAmpel(led_states);
        state = 3;
        break;
      }
      case 3: {
        //Gelb
        schalteAmpel(led_states);
        state = 0;
        break;
      }
    }
    millis_previous = millis_current;
  }
}

void schalteAmpel(bool led_states[3]) {
  for(unsigned int i = 0; i < sizeof(LEDS)/sizeof(int); i++) {
    digitalWrite(LEDS[i], led_states[i]);
  }
}