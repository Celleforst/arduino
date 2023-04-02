#include <LiquidMenu.h>

// Menu
// ----- WELCOME SCREEN -----
LiquidLine lineWelcome(2, 0, "Filament Splicer");
LiquidLine lineRight(7, 1, ">");

// create a screen from the above lines
LiquidScreen screenWelcome(lineWelcome, lineRight);
// --------------------------

// ----- STATUS SCREEN -----
LiquidLine lineTemp(0, 0, "Temp: ", temperature, "C");
LiquidLine lineTune(0, 0, "Tune");
LiquidLine lineAbort(0, 0, "Abort");

LiquidScreen screenStatus(lineTemp, lineTune, lineAbort);
// -------------------------

// ----- SETTINGS SCREEN -----
LiquidLine lineTempSettings(0, 0, "Temperature Settings");
LiquidLine lineMoveSettings(0, 0, "Movement Settings");
LiquidLine linePIDSettings(0, 0, "PID Settings");
LiquidLine lineCool(0, 0, "Cool Down");

LiquidScreen screenSetings(lineTempSettings, lineMoveSettings, linePIDSettings, lineCool);
// -------------------------

// ----- TEMPERATUR SETTINGS SCREEN -----
LiquidLine lineSetTemp(0, 0, "Set Temperature: ", temperature, "C");
LiquidLine lineTempPresets(0, 0, "Temperature Presets");
LiquidLine lineSetFan(0, 0, "Set FanSpeed: ");
LiquidLine lineAutoTune(0, 0, "Autotune PID");
LiquidLine linePIDTune(0, 0, "Set PID Values");

LiquidScreen screenTempSettings(lineSetTemp,lineTempPresets, lineSetFan, lineAutoTune);
// -------------------------

// ----- TEMPERATURE PRESETS SCREEN -----
LiquidLine lineCreatePreset(0, 0, "Create New Preset");
LiquidLine lineModPreset(0, 0, "Modify Preset");

LiquidScreen screenTempPresets(lineCreatePreset, lineModPreset);
// -------------------------

// ----- MOVEMENT SETTINGS SCREEN -----

// -------------------------

// ----- PID SETTINGS SCREEN -----

// -------------------------

// ----- MENU -----
// create a menu from the screens
LiquidMenu menu(lcd, screenWelcome, screenStatus, screenTempPresets, screenTempSettings);
// ----------------

