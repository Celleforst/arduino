#include <AccelStepper.h>
#include <MultiStepper.h>
#include <AccelStepperWithDistance.h>
#include <Encoder.h>
#include <LiquidCrystal.h>

// LCD
#define LCD_RS 37
#define LCD_RW 17
#define LCD_E 35
#define LCD_D0 16
#define LCD_D1 23
#define LCD_D2 25
#define LCD_D3 27
#define LCD_D4 29
#define LCD_D5 33
#define LCD_D6 77
#define LCD_D7 14

// Heater
#define HEATER 8

// Thermistor
#define THERM 68

// Fan
#define FAN 9

// Encoder
#define ENC_P1 28
#define ENC_P2 12
#define ENC_BTN 6

// Beeper
#define BEEPER 67

float temperature = 0.0f;
long newEnc, posEnc = -999;

LiquidCrystal lcd(LCD_RS, LCD_RW, LCD_E, LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

Encoder Knob(ENC_P1, ENC_P2);
