#include <LiquidCrystal.h>

 #include "/home/bastli/Desktop/blink_arduino/AccelStepper/src/AccelStepper.h"
#include "/home/bastli/Desktop/blink_arduino/AccelStepper/src/AccelStepper.cpp"

#include "/home/bastli/Desktop/blink_arduino/AccelStepper/src/MultiStepper.h"
#include "/home/bastli/Desktop/blink_arduino/AccelStepper/src/MultiStepper.cpp"

#include <LiquidMenu.h>

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

//temp sensor (Bed)
#define TS 68

//heater
#define HEATER 8

//fan
#define FAN 9

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

const int stepsPerRevolution = 200;
        
AccelStepper stepper_X = AccelStepper(1, STEP_X, DIR_X);
AccelStepper stepper_Y = AccelStepper(1, STEP_Y, DIR_Y);

LiquidCrystal lcd(LCD_PINS_RS, LCD_PINS_ENABLE, LCD_PINS_D4, LCD_PINS_D5, LCD_PINS_D6, LCD_PINS_D7);

// a variable that will be updated periodically somewhere in our code
float temperature = 0.0f;

// ----- WELCOME SCREEN -----
// a line of one string literal
LiquidLine lineHello(2, 0, "Hello world!");
LiquidLine lineRight(7, 1, ">");

// create a screen from the above lines
LiquidScreen screenMain(lineHello, lineRight);
// --------------------------

// ----- STATUS SCREEN -----
// a line of two string literals and a float variable
LiquidLine lineTemp(0, 0, "Temp: ", temperature, "C");
LiquidScreen screenStatus(lineTemp);
// -------------------------

// ----- MENU -----
// create a menu from the screens
LiquidMenu menu(lcd, screenMain, screenStatus);

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
}

void loop() {
  temperature = number;
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
if(digitalRead(BTN_ENC) == LOW){
      redraw = 1;
      menu.next_screen();
    }
    if(redraw){
       menu.update();
       delay(500);
       redraw=0;
    }
        
    
  
  if(digitalRead(BTN_EN1) == HIGH) encoder_pos |= 0x04;
  else encoder_pos &= ~0x04;
  
  if(digitalRead(BTN_EN2) == HIGH) encoder_pos |= 0x08;
  else encoder_pos &= ~0x08;
  
  if((encoder_pos >> 2 & 0x03) != (encoder_pos & 0x03)){
    rotary_enc_int_routine();
    redraw=1;
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
