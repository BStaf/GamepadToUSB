#include <Joystick.h>
#include "IGameController.h"
#include "GamePad.h"
#include "Nes.h"
#include "Genesis.h"

IGameController *gameController[2];
//*gameController = new Genesis(3, 4, 5, 6, 7, 8, 9);
//Nes *nes = new Nes(10,16,14);
//Genesis *genesis;// = new Genesis(3, 4, 5, 6, 7, 8, 9);
//genesis = new Genesis(3, 4, 5, 6, 7, 8, 9);
Gamepad *gamepad;// = new Gamepad(nes);
 
//Gamepad gamepad;

void setup() {
  gameController[0] = new Nes(10,16,14);
  gameController[1] = new Genesis(3, 4, 5, 6, 7, 8, 9);
  gamepad = new Gamepad(gameController);
  //Serial.begin(9600); 
  //Nes *nes = new Nes(10,16,14);
  //Genesis *genesis = new Genesis(3, 4, 5, 6, 7, 8, 9);
  //gamepad = new Gamepad(&nes);
  gamepad->Init();
}

void loop() {
  gamepad->Tick();
  
  //Serial.println(gameController->Read());
  delay(10);
}
