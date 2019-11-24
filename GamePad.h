#include <Joystick.h>


class Gamepad{
  private:
    Joystick_ * _joystick;
    IGameController ** _gameControllers;
    int _controllerIndex;
    int _controllerCount;
    int _changeControllerCntr; //ticks until check for controller change;
    word lastState;
    bool isStateChanged(word currentState, word lastState, word mask);
    void set_Directional(word currentState, word lastState);
    void set_Button(word currentState, word lastState, byte index, word mask);
    void clearDirectional();
    int getCurrentController(int currentIndex);
  public:
    int ChangeControllerTicks = 20; //ticks until check for controller change;
    Gamepad(IGameController **gameControllers, int controllerCount);
    void Init();
    void Tick();
};

Gamepad::Gamepad(IGameController **gameControllers, int controllerCount){
  _controllerCount = controllerCount;
  _gameControllers = gameControllers;
  _controllerIndex = 1;
  _changeControllerCntr = 0;
  _joystick = new Joystick_(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
    32, 0,                  // Button Count, Hat Switch Count
    true, true, false,     // X and Y, but no Z Axis
    false, false, false,   // No Rx, Ry, or Rz
    false, false,          // No rudder or throttle
    false, false, false);  // No accelerator, brake, or steering  
}

void Gamepad::Init(){
  for (int i=0; i<_controllerCount; i++)
    _gameControllers[i]->Init();
  _joystick->begin();
  _joystick->setXAxisRange(-1, 1);
  _joystick->setYAxisRange(-1, 1);
  //for non analog pads. things get wacky if I don't do this
  clearDirectional();
}

void Gamepad::Tick(){
  _controllerIndex = getCurrentController(_controllerIndex);
  word currentState = _gameControllers[_controllerIndex]->Read();
  if (currentState != lastState){
    //Serial.println(currentState);
    set_Button(currentState, lastState, 0, 1);
    set_Button(currentState, lastState, 1, 2);
    set_Button(currentState, lastState, 2, 4);
    set_Button(currentState, lastState, 3, 8);
    set_Button(currentState, lastState, 4, 16);
    set_Button(currentState, lastState, 5, 32);
    set_Button(currentState, lastState, 6, 64);
    set_Button(currentState, lastState, 7, 128);
    set_Button(currentState, lastState, 8, 256);
    set_Button(currentState, lastState, 9, 512);
    set_Button(currentState, lastState, 10, 1024);
    set_Button(currentState, lastState, 11, 2048);
    lastState = currentState;
  }
}
//whatever controller is being used is the winner
int Gamepad::getCurrentController(int currentIndex){
  if (_changeControllerCntr >= ChangeControllerTicks){
    _changeControllerCntr = 0;
    for (int i=0; i<_controllerCount; i++)
      if (_gameControllers[i]->Read() > 0)
        return i;
  }
  else _changeControllerCntr++;
  return currentIndex;
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
}
void Gamepad::clearDirectional(){
  _joystick->setYAxis(0);
  _joystick->setXAxis(0);
}
/*
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
}*/
