#include "pitches.h"

const int keyNums = 8;

const int keyPin0 = 2;
const int keyPin1 = 3;
const int keyPin2 = 4;
const int keyPin3 = 5;
const int keyPin4 = 6;
const int keyPin5 = 7;
const int keyPin6 = 8;
const int keyPin7 = 9;

const int speaker0 = A3;
const int speaker1 = A2;
const int speaker2 = A1;
const int speaker3 = A0;
const int speaker4 = 13;
const int speaker5 = 12;
const int speaker6 = 11;
const int speaker7 = 10;

const int keyPins[keyNums] = {
  keyPin0, keyPin1, keyPin2, keyPin3, keyPin4, keyPin5, keyPin6, keyPin7
};

const int speakerPins[keyNums] = {
  speaker0, speaker1, speaker2, speaker3, speaker4, speaker5, speaker6, speaker7
};

const int notes[keyNums] = {
  NOTE_A4,
  NOTE_B4,
  NOTE_C5,
  NOTE_D5,
  NOTE_E5,
  NOTE_F5,
  NOTE_G5,
  NOTE_A5
};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < keyNums; i++) {
    pinMode(keyPins[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < keyNums; i++) {
    int value = digitalRead(keyPins[i]);
    if (value == LOW) {
      tone(speakerPins[i], notes[i]);
    } else {
      noTone(speakerPins[i]);
    }
  }
  delay(50);
}

