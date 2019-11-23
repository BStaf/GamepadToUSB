#include <Joystick.h>

class FlightStick{
  private:
    Joystick_ * _joystick;
    int AI_XAxis;
    int AI_YAxis;
    int AI_Wheel;
    //word lastState;
    //bool isStateChanged(word currentState, word lastState, word mask);
    //void set_Directional(word currentState, word lastState);
    //void set_Button(word currentState, word lastState, byte index, word mask);
  public:
    FlightStick();
    void Init();
    void Tick();
};

FlightStick::FlightStick(){
  _joystick = new Joystick_(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
    2, 0,                  // Button Count, Hat Switch Count
    true, true, false,     // X and Y, but no Z Axis
    false, false, false,   // No Rx, Ry, or Rz
    false, true,          // No rudder or throttle
    false, false, false);  // No accelerator, brake, or steering
  
  AI_XAxis = A9;
  AI_YAxis = A8;
  AI_Wheel = A7;
   
}
void FlightStick::Init(){
  _joystick->begin();
  //set analog spans from joystick0
  _joystick->setXAxisRange(370, 940);
  _joystick->setYAxisRange(380, 1020);
  _joystick->setThrottleRange(370, 1022);
}

void FlightStick::Tick(){
  Serial.println("-");
  Serial.println(analogRead(AI_XAxis));
  Serial.println(analogRead(AI_YAxis));
  Serial.println(analogRead(AI_Wheel));
  /*word currentState = _controller->getState();
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
  }*/
}
/*void FlightStick::set_Button(word currentState, word lastState, byte index, word mask){
  if (isStateChanged(currentState, lastState, mask) )
    _joystick->setButton(index, (currentState & mask)>0);
}
void FlightStick::set_Directional(word currentState, word lastState){
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
bool FlightStick::isStateChanged(word currentState, word lastState, word mask){
  if ((currentState & mask) || (lastState & mask)){
    return true;
  }
  return false;
}

*/
