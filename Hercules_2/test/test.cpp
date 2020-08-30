#include <Arduino.h>
#include <unity.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

# define BUTTON 37
int poten = 38;

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14
// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=2001,301
AudioOutputI2S           i2s1;           //xy=2588,291
AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWav1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=2361,373
// GUItool: end automatically generated code


void setup() {
  Serial.begin(115200);
  pinMode(BUTTON,INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  AudioMemory(8);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  playSdWav1.play("20.WAV");
}

void change(const char *filename) {
  if (playSdWav1.isPlaying()) {
    playSdWav1.stop();
  }
  else {
    Serial.println(filename);
    playSdWav1.play(filename);
  }
}

String getFile (int val) {
  int a = round(val/40.92) + 1;
  return (String(a) + ".WAV");
}

void loop() {
  if (analogRead(BUTTON) > 1010) {
    change(getFile(analogRead(38)).c_str());
  }
  Serial.print("Button: ");
  Serial.println(analogRead(37));
  Serial.print("Poten: ");
  Serial.println(analogRead(38));
  delay(200);
}
