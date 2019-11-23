#include <Joystick.h>
#include "GamePadOld.h"
//#include "Nes.h"
//#include "Genesis.h"

//#include "FlightStick.h"
Nes nes(10,16,14);
Gamepad gamepad(); 
//Gamepad gamepad;

void setup() {
  Serial.begin(9600); 
  //Nes *nes = new Nes(10,16,14);
  //Genesis *genesis = new Genesis(3, 4, 5, 6, 7, 8, 9);
  //gamepad = new Gamepad(&nes);
  gamepad.Init();
}

void loop() {
  gamepad.Tick();
  
  //Serial.println(gameController->Read());
  delay(20);
}
