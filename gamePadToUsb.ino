#include <Joystick.h>
#include "IGameController.h"
#include "GamePad.h"
#include "Nes.h"
#include "Genesis.h"
#include "N_64.h"


IGameController *gameController[3];
Gamepad *gamepad;

void setup() {
  gameController[0] = new Nes(10,16,14);
  gameController[1] = new Genesis(3, 4, 5, 6, 7, 8, 9);
  gameController[2] = new N_64(18);
  gamepad = new Gamepad(gameController, 3);
  //Serial.begin(9600); 
  gamepad->Init();
  delay(100);
}

void loop() {
  gamepad->Tick();
  //some googling told me a genesis will poll the controller 60 times per second
  //so I'm going with 15 ms
  delay(15);
}
