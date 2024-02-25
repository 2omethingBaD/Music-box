#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>

#define sd_card 10
#define sensor 6
bool magnetClose = false;

TMRpcm pcm;


void setup() {
  //Serial.begin(9600);
  
  //CS pin check
  /*if(!SD.begin(sd_card)){
    Serial.println("SD fail");
    return;
  }*/
  SD.begin(sd_card);

  pcm.speakerPin = 9;
  pcm.setVolume(5);
  
  pinMode(sensor, INPUT_PULLUP);
}


void loop() {
  //speaker test tone 
  //tone(9, 1000, 500);

  int proximity = digitalRead(sensor);

  if(pcm.isPlaying() & proximity == LOW){
    // Magnet is close, pause audio
    if (!magnetClose) {
      pcm.pause();
      magnetClose = true;
      //Serial.println("Box is closed, pause audio");
    }
    delay(100);
  }else {
    // Magnet is away, resume audio
    if (magnetClose) {
      pcm.pause();
      magnetClose = false;
      //Serial.println("Box is open, resume audio");
    }
    delay(100);
  }
  
  while(!pcm.isPlaying()){
    pcm.play("N.wav");
  }
}
