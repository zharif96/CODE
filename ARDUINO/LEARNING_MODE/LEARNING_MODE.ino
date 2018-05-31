
#include <Servo.h>
#include <SoftwareSerial.h>
#include "RedMP3.h"
#include "SPI.h"
#include "TFT_22_ILI9225.h"

#define sw1_pin 0
#define sw2_pin 1
#define sw3_pin 12
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
#define TFT_CS  A5  // SS
#define TFT_RST A4
#define TFT_RS  A3
#define TFT_SDI A2  // MOSI
#define TFT_CLK A1  // SCK
#define TFT_LED A0   // 0 if wired to +5V directly
#define TFT_BRIGHTNESS 200 // Initial brightness of TFT backlight (optional)
#define MP3_RX 9//RX of Serial MP3 module connect to D7 of Arduino
#define MP3_TX 10//TX to D8, note that D8 can not be used as RX on Mega2560, you should modify this if you donot use Arduino UNO


Servo topServo;
Servo bottomServo;
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_SDI, TFT_CLK, TFT_LED, TFT_BRIGHTNESS);
MP3 mp3(MP3_RX, MP3_TX);

int frequency = 0;
int answer = 0;
int complete = 0;
int color=0;
uint16_t x, y;
boolean flag = false;
int8_t vol = 0x1a;//0~0x1e (30 adjustable level)
int8_t directory = 1;
int8_t angry = 1;
int8_t happy = 2;
int8_t sad = 3;
int8_t incorrect = 6;
int8_t correct = 7;

int  markah = 0;
char mark[12];
int count = 0;
int totalCuba = 3;
char totalTry[12];
int set = 0;
int calibrate = 0;
int redR = 0;
int redG = 0;
int redB = 0;
int yellowR = 0;
int yellowG = 0;
int yellowB = 0;
int blueR = 0;
int blueG = 0;
int blueB = 0;
int again = 0;
volatile boolean sw1 = false;
volatile boolean sw2 = false;
volatile boolean sw3 = false;


uint8_t sw1ButtonState = 0;
uint8_t sw2ButtonState = 0;
uint8_t sw3ButtonState = 0;


uint8_t lastsw1ButtonState = 0;
uint8_t lastsw2ButtonState = 0;
uint8_t lastsw3ButtonState = 0;


void setup() {
  pinMode(sw1_pin, INPUT_PULLUP);
  pinMode(sw2_pin, INPUT_PULLUP);
  pinMode(sw3_pin, INPUT_PULLUP);
  delay(500);
  mp3.setVolume(vol);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  topServo.attach(2);
  bottomServo.attach(3);
  bottomServo.write(85);
  tft.begin();
  tft.setOrientation(3);
  Serial.begin(9600);
}
void loop() {
  do{
  again = 0;
  while(calibrate != 1){
    calibrateSensor(1);
    calibrateSensor(2);
    calibrateSensor(3);
    calibrate = 1;
    }
    
  while(set != 1){
      setIteration();
    }
  while(count != totalCuba){
  topServo.write(68);
  delay(500);
  for(int i = 68; i > 30; i--) {
    topServo.write(i);
    delay(2);
  }
  delay(500);
  
  color = readColor();
  delay(500);  
  switch (color) {
    case 1:
    answer = 170;
    complete = 0;
    mp3.playWithFileName(directory, angry);
    delay(5000);
    count = count + 1;
    drawArahan();
    //bottomServo.write(170);
    break;
    case 2:
    answer = 120;
    complete = 0;
    mp3.playWithFileName(directory, happy);
    delay(7000);
    count = count + 1;
    drawArahan();
    //bottomServo.write(120);
    break;
    case 3:
    answer = 85;
    complete = 0;
    mp3.playWithFileName(directory, sad);
    delay(7000);
    count = count + 1;
    drawArahan();
    //bottomServo.write(90);
    break;    
    case 0:
    count = count;
    topServo.write(8);
    delay(100);
    complete = 1;
    break;
  }
  delay(300);
  while(complete == 0){
     checkIfSw1ButtonIsPressed();
     checkIfSw2ButtonIsPressed();
     checkIfSw3ButtonIsPressed();

     if( sw1){
      if(bottomServo.read() == 170){
      Serial.println("sw1");
       sw1 = false;
       bottomServo.write(120);
       delay(15);
      }
      else if(bottomServo.read() == 120){
       Serial.println("sw1");
       sw1 = false;
       bottomServo.write(85);
       delay(15);
       }
      else if(bottomServo.read() == 85){
       Serial.println("sw1");
       sw1 = false;
       bottomServo.write(85);
       delay(15);
       }
       
     }
     else if( sw2){
      if(bottomServo.read() == 85){
      Serial.println("sw2");
       sw2 = false;
       bottomServo.write(120);
       delay(15);
      }
      else if(bottomServo.read()==120){
       Serial.println("sw2");
       sw2 = false;
       bottomServo.write(170);
       delay(15);
        }
       else if(bottomServo.read()==170){
       Serial.println("sw2");
       sw2 = false;
       bottomServo.write(170);
       delay(15);
        }
     }
     
      else if( sw3){
      if(bottomServo.read() == answer){
      Serial.println("sw3");
       sw3 = false;
       topServo.write(8);
       delay(500);
       tft.clear();
       tft.setBackgroundColor(COLOR_BLACK);
       tft.setFont(Terminal12x16);
       tft.drawText(0, 30, "Jawapan anda", COLOR_GREEN);
       tft.drawText(0, 50, "BETUL", COLOR_GREEN);
       mp3.playWithFileName(directory, correct);
       delay(3000);
       markah = markah + 1;
       complete = 1;
       tft.clear();    
      }
      else{
       Serial.println("sw3");
       sw3 = false;
       topServo.write(8);
       delay(500);
       markah = markah;
       tft.clear();
       tft.setBackgroundColor(COLOR_BLACK);
       tft.setFont(Terminal12x16);
       tft.drawText(0, 30, "Jawapan anda", COLOR_RED);
       tft.drawText(0, 50, "TIDAK TEPAT", COLOR_RED);
       mp3.playWithFileName(directory, incorrect);
       delay(3000);
       complete = 1; 
       tft.clear();
        }         
     }   
    }
  
  for(int i = 8; i < 68; i++) {
    topServo.write(i);
    delay(2);
  }
  color=0;
  }
  drawMarkah(markah);
  while(again != 1){
    checkIfSw3ButtonIsPressed();
    if(sw3){
      sw3 = false;
      set = 0;
      totalCuba = 3;
      markah = 0;
      count = 0;
      again = 1;
      tft.clear();
      }
    }
  }while(again == 1);
}
// Custom Function - readColor()
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(50);
  if(R<(redR+10) & R>(redR-10) & G<(redG+10) & G>(redG-10)){
    color = 1; // RED
  }
  if(R<(yellowR+10) & R>(yellowR-10) & G<(yellowG+10) & G>(yellowG-10)){
    color = 2; // Yellow
  }
  if (R<(blueR+10) & R>(blueR-10) & B<(blueB+10) &B>(blueB-10)){
    color = 3; // Blue
  }
  return color;  
}

void checkIfSw1ButtonIsPressed()
{
    sw1ButtonState   = digitalRead(sw1_pin);
  
    if (sw1ButtonState != lastsw1ButtonState)
  {
    if ( sw1ButtonState == 0)
    {
      sw1=true;
    }
    delay(50);
  }
   lastsw1ButtonState = sw1ButtonState;
 }

void checkIfSw2ButtonIsPressed()
{
    sw2ButtonState   = digitalRead(sw2_pin);
  
    if (sw2ButtonState != lastsw2ButtonState)
  {
    if ( sw2ButtonState == 0)
    {
      sw2=true;
    }
    delay(50);
  }
   lastsw2ButtonState = sw2ButtonState;
 }

 void checkIfSw3ButtonIsPressed()
{
    sw3ButtonState   = digitalRead(sw3_pin);
  
    if (sw3ButtonState != lastsw3ButtonState)
  {
    if ( sw3ButtonState == 0)
    {
      sw3=true;
    }
    delay(50);
  }
   lastsw3ButtonState = sw3ButtonState;
 }

void drawArahan(){ 
  tft.setBackgroundColor(COLOR_BLACK);
  tft.setFont(Terminal12x16);
  tft.drawText(0, 30, "Sila pilih kotak", COLOR_WHITE);
  tft.drawText(0, 50, "yang betul.", COLOR_WHITE);
  }


void drawMarkah(int markah){
  tft.setBackgroundColor(COLOR_YELLOW);
  tft.setFont(Terminal12x16);
  tft.drawText(45, 30, "MARKAH ANDA:", COLOR_RED);
  delay(1000);
  tft.fillRectangle(45, 50, 181, 160, COLOR_RED);
  
  tft.setBackgroundColor(COLOR_RED);
  tft.setFont(Trebuchet_MS16x21);
  sprintf(mark, "%d", markah);
  sprintf(totalTry, "%d", totalCuba);
  tft.drawText(95, 90, mark);
  tft.drawText(114, 90, "/");
  tft.drawText(125, 90, totalTry);
  delay(1000);
  }

 void setIteration(){
  tft.setBackgroundColor(COLOR_YELLOW);
  tft.setFont(Terminal12x16);
  tft.drawText(15, 20, "Jumlah percubaan:", COLOR_RED);
  tft.fillRectangle(15, 40, 207, 160, COLOR_RED);
  tft.setBackgroundColor(COLOR_RED);
  tft.setFont(Trebuchet_MS16x21);
  sprintf(totalTry, "%d", totalCuba);
  tft.drawText(110, 90, totalTry);

  while(set != 1){
     checkIfSw1ButtonIsPressed();
     checkIfSw2ButtonIsPressed();
     checkIfSw3ButtonIsPressed();

     if( sw1){
     if(totalCuba > 0){
      Serial.println("sw1");
      sw1 = false;
      totalCuba = totalCuba - 1;
      tft.fillRectangle(15, 40, 207, 160, COLOR_RED);
      tft.setBackgroundColor(COLOR_RED);
      tft.setFont(Trebuchet_MS16x21);
      sprintf(totalTry, "%d", totalCuba);
      tft.drawText(110, 90, totalTry);
      set = 0;
     }
     else{
      Serial.println("sw1");
      sw1 = false;
      totalCuba = 0;
      tft.fillRectangle(15, 40, 207, 160, COLOR_RED);
      tft.setBackgroundColor(COLOR_RED);
      tft.setFont(Trebuchet_MS16x21);
      sprintf(totalTry, "%d", totalCuba);
      tft.drawText(110, 90, totalTry);
      set = 0;
      }    
     }
     
     else if( sw2){
      Serial.println("sw2");
      sw2 = false;
      totalCuba = totalCuba + 1;
      tft.fillRectangle(15, 40, 207, 160, COLOR_RED);
      tft.setBackgroundColor(COLOR_RED);
      tft.setFont(Trebuchet_MS16x21);
      sprintf(totalTry, "%d", totalCuba);
      tft.drawText(110, 90, totalTry);
      set = 0;
    }

      else if( sw3){
      Serial.println("sw3");
      sw3 = false;
        if(totalCuba > 0){
        set = 1;    
         }
         else{
        tft.fillRectangle(15, 40, 207, 160, COLOR_RED);
        tft.setBackgroundColor(COLOR_RED);
        tft.setFont(Trebuchet_MS16x21);
        sprintf(totalTry, "%d", totalCuba);
        tft.drawText(110, 90, totalTry);   
        set = 0;
         }
      }       
   }
   tft.clear();
 }

 void calibrateSensor(int color){
  int doneCalibrate = 0;
  topServo.write(68);
  delay(500);
  tft.setFont(Terminal12x16);
  switch(color){
  case 1:
  tft.drawText(0, 40, "Letakkan warna", COLOR_RED);
  tft.drawText(0, 60, "MERAH dan tekan OK", COLOR_RED);
  break; 
  case 2:
  tft.drawText(0, 40, "Letakkan warna", COLOR_YELLOW);
  tft.drawText(0, 60, "KUNING dan tekan OK", COLOR_YELLOW); 
  break;
  case 3:
  tft.drawText(0, 40, "Letakkan warna", COLOR_BLUE);
  tft.drawText(0, 60, "BIRU dan tekan OK", COLOR_BLUE);
  break;
  }

  while(doneCalibrate != 1){
  checkIfSw3ButtonIsPressed();
  if( sw3){
  sw3 = false;
  topServo.write(30);
  delay(500);
  switch(color){
    case 1:
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    redR = frequency;
    // Printing the value on the serial monitor
    Serial.print("R= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.print("  ");
    delay(50);
    // Setting Green filtered photodiodes to be read
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    redG = frequency;
    // Printing the value on the serial monitor
    Serial.print("G= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.print("  ");
    delay(50);
    // Setting Blue filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    redB = frequency;
    // Printing the value on the serial monitor
    Serial.print("B= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.println("  ");
    delay(500);
    break;

    case 2:
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    yellowR = frequency;
    // Printing the value on the serial monitor
    Serial.print("R= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.print("  ");
    delay(50);
    // Setting Green filtered photodiodes to be read
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    yellowG = frequency;
    // Printing the value on the serial monitor
    Serial.print("G= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.print("  ");
    delay(50);
    // Setting Blue filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    yellowB = frequency;
    // Printing the value on the serial monitor
    Serial.print("B= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.println("  ");
    delay(500);
    break;
    
    case 3:
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    blueR = frequency;
    // Printing the value on the serial monitor
    Serial.print("R= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.print("  ");
    delay(50);
    // Setting Green filtered photodiodes to be read
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    blueG = frequency;
    // Printing the value on the serial monitor
    Serial.print("G= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.print("  ");
    delay(50);
    // Setting Blue filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    blueB = frequency;
    // Printing the value on the serial monitor
    Serial.print("B= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.println("  ");
    delay(500);
    break;
    }

    switch(color){
      case 1:
      bottomServo.write(170);
      delay(500);
      break;
      case 2:
      bottomServo.write(120);
      delay(500);
      break;
      case 3:
      bottomServo.write(85);
      delay(500);
      break;
      }
    topServo.write(8);
    delay(500);
    topServo.write(68);
    delay(500);
    doneCalibrate = 1;
    tft.clear();
    }  
  }
 }



 

  

