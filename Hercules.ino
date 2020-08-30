#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

AudioPlaySdWav           playWav1;
AudioOutputUSB           audioOutput; // must set Tools > USB Type to Audio
AudioOutputAnalog        dac;
AudioConnection          patchCord1(playWav1, 0, audioOutput, 0);
AudioConnection          patchCord2(playWav1, 1, audioOutput, 1);
AudioConnection          patchCord3(playWav1, 0, dac, 0);

// Use these with the Teensy 3.5 & 3.6 SD card
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used

Bounce pushbutton = Bounce(12, 10);
const int ledPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(A8, INPUT);
  pinMode(15, INPUT);
  pinMode(14, OUTPUT);
  digitalWrite(14, HIGH);
  pinMode(12, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  AudioMemory(20);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}

void playFile(const char *filename)
{
  if(!playWav1.isPlaying()) {
    playWav1.play(filename);
  }
  else {
    playWav1.stop();
    playWav1.play(filename);
  }
}

bool checkButton(int val) {
  if (val == 1023) {
    return true;
  }
  else {
    return false;
  }
}

String getFile (int val) {

  int a = round(val/46.5) + 1;
  return (String(a) + ".WAV");
}

void loop() {
  if (checkButton(analogRead(15))) {
    playFile(getFile(analogRead(A8)).c_str());
    Serial.println(getFile(analogRead(A8)));
  }
  delay(1000);
}
