#include "/home/bastli/Desktop/blink_arduino/AccelStepper/src/AccelStepper.h"
#include "/home/bastli/Desktop/blink_arduino/AccelStepper/src/AccelStepper.cpp"

#include "/home/bastli/Desktop/blink_arduino/AccelStepper/src/MultiStepper.h"
#include "/home/bastli/Desktop/blink_arduino/AccelStepper/src/MultiStepper.cpp"

#define F_CPU 16000000UL

#define DIR_X A1
#define STEP_X A0
#define EN_X 38

#define DIR_Y A7
#define STEP_Y A6
#define EN_Y A2

int pin = 13;

const int stepsPerRevolution = 200;
        
AccelStepper stepper_X = AccelStepper(1, STEP_X, DIR_X);
AccelStepper stepper_Y = AccelStepper(1, STEP_Y, DIR_Y);

void setup() {
  //DDRB |= (1<<PB7);
  stepper_X.setMaxSpeed(200);
  stepper_X.setSpeed(5);
  stepper_X.setAcceleration(400);
  stepper_Y.setMaxSpeed(200);
  stepper_Y.setSpeed(5);
  stepper_Y.setAcceleration(400);
  pinMode(pin, OUTPUT);
  pinMode(EN_X, OUTPUT);
  digitalWrite(EN_X, LOW);
  pinMode(EN_Y, OUTPUT);
  digitalWrite(EN_Y, LOW);
}

void loop() {
  digitalWrite(EN_X, LOW);
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

}
