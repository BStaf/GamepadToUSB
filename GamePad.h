#include <Joystick.h>


class Gamepad{
  private:
    Joystick_ * _joystick;
    IGameController ** _gameControllers;
    int _controllerIndex;
    int _controllerCount;
    int _changeControllerCntr; //ticks until check for controller change;
    ControllerStatus _lastState;
    bool isStateChanged(unsigned long currentState, unsigned long lastState, unsigned long mask);
    void set_Directional(ControllerStatus currentState, ControllerStatus lastState);
    void set_Button(unsigned long currentState, unsigned long lastState, byte index, unsigned long mask);
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
  _controllerIndex = 0;
  _changeControllerCntr = 0;
  //_lastState = 0;
  _joystick = new Joystick_(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
    32, 0,                  // Button Count, Hat Switch Count
    true, true, false,     // X and Y, but no Z Axis
    true, true, false,   //  Rx and Ry, but no  Rz
    false, false,          // No rudder or throttle
    false, false, false);  // No accelerator, brake, or steering  
}

void Gamepad::Init(){
  for (int i=0; i<_controllerCount; i++)
    _gameControllers[i]->Init();
  _joystick->begin();
  _joystick->setXAxisRange(-80, 80);
  _joystick->setYAxisRange(-80, 80);
  /*_joystick->setRxAxisRange(-1, 1);
  _joystick->setRyAxisRange(-1, 1);*/
  //for non analog pads. things get wacky if I don't do this
  clearDirectional();
}

void Gamepad::Tick(){
  _controllerIndex = getCurrentController(_controllerIndex);
 IGameController * controller = _gameControllers[_controllerIndex];
 ControllerStatus currentState = controller->Read();
  if (controller->HasChanged()){
    //update buttons if changed state
    for (int i=0;i<=17;i++)
      set_Button(currentState.Buttons, _lastState.Buttons, i, (unsigned long)1 << i);
    //update analog
    set_Directional(currentState, _lastState);
    _lastState = currentState;
  }
}
//whatever controller is being used is the winner
int Gamepad::getCurrentController(int currentIndex){
  if (_changeControllerCntr >= ChangeControllerTicks){
    _changeControllerCntr = 0;
    for (int i=0; i<_controllerCount; i++)
      if (_gameControllers[i]->Read().Buttons > 0)
        return i;
  }
  else _changeControllerCntr++;
  return currentIndex;
}
void Gamepad::set_Button(unsigned long currentState, unsigned long lastState, byte index, unsigned long mask){
  if (isStateChanged(currentState, lastState, mask) ){
    _joystick->setButton(index, (currentState & mask)>0);

  }
}
bool Gamepad::isStateChanged(unsigned long currentState, unsigned long lastState, unsigned long mask){
  if ((currentState & mask) || (lastState & mask)){
    return true;
  }
  return false;
}
void Gamepad::clearDirectional(){
  _joystick->setYAxis(0);
  _joystick->setXAxis(0);
}

void Gamepad::set_Directional(ControllerStatus currentState, ControllerStatus lastState){
  if (currentState.XAxis != lastState.XAxis)
    _joystick->setXAxis(currentState.XAxis);
  if (currentState.YAxis != lastState.YAxis)
    _joystick->setYAxis(currentState.YAxis * -1);//reverse y axis
}
