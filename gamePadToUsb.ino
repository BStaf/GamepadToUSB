#include <Joystick.h>
#include "IGameController.h"
#include "GamePad.h"
#include "Nes.h"
#include "Genesis.h"
#include "N_64.h"


IGameController *gameController[1];
Gamepad *gamepad;

void setup() {
  gameController[0] = new Nes(10,16,14);
  //gameController[1] = new Genesis(3, 4, 5, 6, 7, 8, 9);
  //gameController[0] = new N_64(18);
  gamepad = new Gamepad(gameController, 1);
  Serial.begin(9600); 
  gamepad->Init();

}

void loop() {
  gamepad->Tick();

  delay(5);
}
