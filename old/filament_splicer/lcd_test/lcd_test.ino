#include "/home/bastli/Desktop/blink_arduino/AccelStepper/src/AccelStepper.h"
#include "/home/bastli/Desktop/blink_arduino/AccelStepper/src/AccelStepper.cpp"

#include "/home/bastli/Desktop/blink_arduino/AccelStepper/src/MultiStepper.h"
#include "/home/bastli/Desktop/blink_arduino/AccelStepper/src/MultiStepper.cpp"

#include <LiquidCrystal.h>
#include <LCDMenuLib2>

//cpu frequency
//#define F_CPU 16000000UL

//stepper motors
#define DIR_X A1
#define STEP_X A0
#define EN_X 38

#define DIR_Y A7
#define STEP_Y A6
#define EN_Y A2

//LCD board
#define KILL_PIN 41

 //lcd pins  
#define LCD_PINS_RS 16
#define LCD_PINS_ENABLE 17
#define LCD_PINS_D4 23
#define LCD_PINS_D5 25
#define LCD_PINS_D6 27
#define LCD_PINS_D7 29

 //encoder pins  
#define BTN_EN1 53
#define BTN_EN2 51
#define BTN_ENC 35

 //beeper  
#define BEEPER 37

 //SD card detect pin  
#define SDCARDDETECT 49

int pin = 13;
int number = 0;
uint8_t msg_n = 0;
uint8_t encoder_pos;
uint8_t redraw = 0;

String msg = "NO INPUT";

const int stepsPerRevolution = 200;
        
AccelStepper stepper_X = AccelStepper(1, STEP_X, DIR_X);
AccelStepper stepper_Y = AccelStepper(1, STEP_Y, DIR_Y);

LiquidCrystal lcd(LCD_PINS_RS, LCD_PINS_ENABLE, LCD_PINS_D4, LCD_PINS_D5, LCD_PINS_D6, LCD_PINS_D7);

void setup() {
  
  stepper_X.setMaxSpeed(200);
  stepper_X.setSpeed(5);
  stepper_X.setAcceleration(400);
  stepper_Y.setMaxSpeed(200);
  stepper_Y.setSpeed(5);
  stepper_Y.setAcceleration(400);
  pinMode(pin, OUTPUT);
  pinMode(EN_X, OUTPUT);
  digitalWrite(EN_X, HIGH);
  pinMode(EN_Y, OUTPUT);
  digitalWrite(EN_Y, HIGH);
  
  lcd.begin(20, 4);
  lcd.print("Filament Splicer");
  
  pinMode(BTN_EN1, INPUT_PULLUP);
  pinMode(BTN_EN2, INPUT_PULLUP);
  pinMode(BTN_ENC, INPUT_PULLUP);
  pinMode(KILL_PIN, INPUT_PULLUP);
  
  //attachInterrupt(BTN_EN1, rotary_enc_int_routine(), CHANGE);
  //attachInterrupt(BTN_EN2, rotary_enc_int_routine(), CHANGE);
  
  encoder_pos = 0;
  if(digitalRead(BTN_EN1) == HIGH){
    encoder_pos |= 0x01;
  }
  if(digitalRead(BTN_EN2) == HIGH){
    encoder_pos |= 0x02;
  }
  
  lcd.setCursor(1,0);
  redraw = 1;
}

void loop() {
  /*digitalWrite(EN_X, LOW);
  digitalWrite(pin, HIGH);
  stepper_X.moveTo(600);
  stepper_X.runToPosition();
  delay(1000);
  
  digitalWrite(pin, LOW);
  stepper_X.moveTo(0);
  stepper_X.runToPosition();
  digitalWrite(EN_X, HIGH);
  delay(1000);
  
  digitalWrite(EN_Y, LOW);
  digitalWrite(pin, HIGH);
  stepper_Y.moveTo(600);
  stepper_Y.runToPosition();
  delay(1000);
  
  digitalWrite(pin, LOW);
  stepper_Y.moveTo(0);
  stepper_Y.runToPosition();
  digitalWrite(EN_Y, HIGH);
  delay(1000);
  
  */
  if(redraw){
    lcd.setCursor(0,1);
    lcd.print("        ");
    lcd.setCursor(0,1);
    lcd.print(number);
    
    lcd.setCursor(0,2);
    lcd.print("        ");
    lcd.setCursor(0,2);
    lcd.print(msg);
    redraw = 0;
  }
  if(digitalRead(KILL_PIN) == LOW){
    if(msg_n != 1){
      msg = "KILL";
      redraw = 1;
      msg_n = 1;
    }
  }
  else if(digitalRead(BTN_ENC) == LOW){
    if(msg_n != 2){
      msg = "PRESSED";
      redraw = 1;
      msg_n = 2;
    }
  }
  else if(msg_n != 0){
    msg = "NO_INPUT";
    redraw = 1;
    msg_n = 0;
  }
  
  if(digitalRead(BTN_EN1) == HIGH) encoder_pos |= 0x04;
  else encoder_pos &= ~0x04;
  
  if(digitalRead(BTN_EN2) == HIGH) encoder_pos |= 0x08;
  else encoder_pos &= ~0x08;
  
  if((encoder_pos >> 2 & 0x03) != (encoder_pos & 0x03)){
    rotary_enc_int_routine();
    redraw = 1;
  }
}

void rotary_enc_int_routine(){
  if(((encoder_pos >> 2) & 0x01) ^ (encoder_pos & 0x01)){
    if(!(encoder_pos & 0x03) || !(~encoder_pos & 0x03)) ++number;
    else --number;
  }
  else if(((encoder_pos >> 2) & 0x02) ^ (encoder_pos & 0x02)){
    if(!((encoder_pos >> 2) & 0x03) || !(~(encoder_pos >> 2) & 0x03)) ++number;
    else --number;
  }
  encoder_pos = (encoder_pos >> 2) & 0x03;
}
