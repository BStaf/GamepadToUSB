
#include <SegaController.h>

class Gamepad{
  private:
    Joystick_ * _joystick;
    SegaController * _controller;
    word lastState;
    bool isStateChanged(word currentState, word lastState, word mask);
    void set_Directional(word currentState, word lastState);
    void set_Button(word currentState, word lastState, byte index, word mask);
  public:
    Gamepad();
    void Init();
    void Tick();
};

Gamepad::Gamepad(){
  _joystick = new Joystick_(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
    32, 0,                  // Button Count, Hat Switch Count
    true, true, false,     // X and Y, but no Z Axis
    false, false, false,   // No Rx, Ry, or Rz
    false, false,          // No rudder or throttle
    false, false, false);  // No accelerator, brake, or steering
  
  // DB9 Pin 7, DB9 Pin 1, DB9 Pin 2, DB9 Pin 3, DB9 Pin 4, DB9 Pin 6, DB9 Pin 9
  
   _controller = new SegaController(8, 3, 4, 5, 6, 7, 9);
}
void Gamepad::Init(){
  _joystick->begin();
  _joystick->setXAxisRange(-1, 1);
  _joystick->setYAxisRange(-1, 1);
}

void Gamepad::Tick(){
  word currentState = _controller->getState();
  if (currentState != lastState){
    set_Directional(currentState, lastState);
    if (currentState & SC_CTL_ON){
    }
    set_Button(currentState, lastState, 0, SC_BTN_START);
    set_Button(currentState, lastState, 1, SC_BTN_A);
    set_Button(currentState, lastState, 2, SC_BTN_B);
    set_Button(currentState, lastState, 3, SC_BTN_C);
    set_Button(currentState, lastState, 4, SC_BTN_X);
    set_Button(currentState, lastState, 5, SC_BTN_Y);
    set_Button(currentState, lastState, 6, SC_BTN_Z);
    set_Button(currentState, lastState, 7, SC_BTN_MODE);
    lastState = currentState;
  }
}
void Gamepad::set_Button(word currentState, word lastState, byte index, word mask){
  if (isStateChanged(currentState, lastState, mask) )
    _joystick->setButton(index, (currentState & mask)>0);
}
void Gamepad::set_Directional(word currentState, word lastState){
  //check up down
  if ( (isStateChanged(currentState, lastState, SC_BTN_UP) || (isStateChanged(currentState, lastState, SC_BTN_DOWN) ))){
    if (currentState & SC_BTN_UP)
      _joystick->setYAxis(-1);
    else if (currentState & SC_BTN_DOWN)
      _joystick->setYAxis(1);
    else 
      _joystick->setYAxis(0);    
  }
  if ( (isStateChanged(currentState, lastState, SC_BTN_LEFT) || (isStateChanged(currentState, lastState, SC_BTN_RIGHT) ))){
    if (currentState & SC_BTN_LEFT)
      _joystick->setXAxis(-1);
    else if (currentState & SC_BTN_RIGHT)
      _joystick->setXAxis(1);
    else
      _joystick->setXAxis(0);
  }
}
bool Gamepad::isStateChanged(word currentState, word lastState, word mask){
  if ((currentState & mask) || (lastState & mask)){
    return true;
  }
  return false;
}*/
