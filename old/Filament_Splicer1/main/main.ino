#include "definitions.h"
#include "menu.h"

void setup() {
  lcd.begin(20,4);
}

void loop() {
  
  newEnc = Knob.read();
    
  if(newEnc != posEnc){
    posEnc = newEnc;
    menu.update();
  }

}
