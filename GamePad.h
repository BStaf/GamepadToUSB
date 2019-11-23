/*#include <Joystick.h>
#include "IGameController.h"

class Gamepad{
  private:
    Joystick_ * _joystick;
    IGameController * _gameController;
    word lastState;
    bool isStateChanged(word currentState, word lastState, word mask);
    void set_Directional(word currentState, word lastState);
    void set_Button(word currentState, word lastState, byte index, word mask);
  public:
    Gamepad(IGameController *gameController);
    void Init();
    void Tick();
};

Gamepad::Gamepad(IGameController *gameController){
  _joystick = new Joystick_(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
    32, 0,                  // Button Count, Hat Switch Count
    true, true, false,     // X and Y, but no Z Axis
    false, false, false,   // No Rx, Ry, or Rz
    false, false,          // No rudder or throttle
    false, false, false);  // No accelerator, brake, or steering
  
  // DB9 Pin 7, DB9 Pin 1, DB9 Pin 2, DB9 Pin 3, DB9 Pin 4, DB9 Pin 6, DB9 Pin 9
  _gameController = gameController;
  gameController->Init();
}
void Gamepad::Init(){
  _joystick->begin();
  _joystick->setXAxisRange(-1, 1);
  _joystick->setYAxisRange(-1, 1);
}

void Gamepad::Tick(){
  word currentState = _gameController->Read();
  if (currentState != lastState){
    Serial.println(currentState);
    set_Button(currentState, lastState, 0, 1);
    set_Button(currentState, lastState, 1, 2);
    set_Button(currentState, lastState, 2, 4);
    set_Button(currentState, lastState, 3, 8);
    set_Button(currentState, lastState, 4, 16);
    set_Button(currentState, lastState, 5, 32);
    set_Button(currentState, lastState, 6, 64);
    set_Button(currentState, lastState, 7, 128);
    /*set_Button(currentState, lastState, 8, 256);
    set_Button(currentState, lastState, 9, 512);
    set_Button(currentState, lastState, 10, 1024);
    set_Button(currentState, lastState, 11, 2048);*/
/*    lastState = currentState;
  }
}
void Gamepad::set_Button(word currentState, word lastState, byte index, word mask){
  if (isStateChanged(currentState, lastState, mask) ){
    _joystick->setButton(index, (currentState & mask)>0);

  }
}
bool Gamepad::isStateChanged(word currentState, word lastState, word mask){
  if ((currentState & mask) || (lastState & mask)){
    return true;
  }
  return false;
}*/
