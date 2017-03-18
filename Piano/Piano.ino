#include "pitches.h"
#include "music01.h"

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
  NOTE_C5,
  NOTE_D5,
  NOTE_E5,
  NOTE_F5,
  NOTE_G5,
  NOTE_A5,
  NOTE_B5,
  NOTE_C6
};

// trueの場合はrunManualMode関数を実行
// falseの場合はrunAutoMode関数を実行
bool isManualMode = true;
int manualModeLimit = 400;

void noToneAll() {
  for (int i = 0; i < keyNums; i++) {
    noTone(speakerPins[i]);
  }
}


// 32分音符のミリ秒
const long tickMillis = 64;

// 32分音符としての単位
const int note32 = 32;
int count = 0;
int musicIndex = 0;
void runAutoMode() {
  if (count <= 0) {
    noToneAll();
    delay(tickMillis / 4); // 切れ目がほしい
    musicIndex = musicIndex % (sizeof(music01) / sizeof(music01[0]));
    int keyIndex = music01[musicIndex][0];
    count = note32 / music01[musicIndex][1];
    if (keyIndex >= 0 && keyIndex < keyNums) {
      tone(speakerPins[keyIndex], notes[keyIndex]);
    }
    musicIndex++;
  } else {
    delay(tickMillis / 4);
    count--;
  }

  // 32分音符を最小単位とする
  delay(tickMillis / 4 * 3);

  // スイッチがどれか押されていたらオートモード終了
  for (int i = 0; i < keyNums; i++) {
    int value = digitalRead(keyPins[i]);
    if (value == LOW) {
      isManualMode = true;
      manualModeLimit = 400;
      noToneAll();
      break;
    }
  }
}

void runManualMode() {
  for (int i = 0; i < keyNums; i++) {
    int value = digitalRead(keyPins[i]);
    if (value == LOW) {
      manualModeLimit = 400;
      tone(speakerPins[i], notes[i]);
    } else {
      noTone(speakerPins[i]);
    }
  }
  delay(50);

  manualModeLimit--;
  if (manualModeLimit < 0) {
    isManualMode = false;
    count = 0;
    musicIndex = 0;
  }
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < keyNums; i++) {
    pinMode(keyPins[i], INPUT_PULLUP);
  }
}

void loop() {
  if (isManualMode) {
    runManualMode();
  } else {
    runAutoMode();
  }
}




