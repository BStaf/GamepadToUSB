#include <SegaController.h>
#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  32, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

// DB9 Pin 7, DB9 Pin 1, DB9 Pin 2, DB9 Pin 3, DB9 Pin 4, DB9 Pin 6, DB9 Pin 9

SegaController controller(8, 3, 4, 5, 6, 7, 9);



void setup() {
  Serial.begin(9600);
  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
}

// Last state of the buttons
//int lastButtonState[5] = {0,0,0,0,0};
word lastState = 0;

void loop() {
  word currentState = controller.getState();
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
    /*set_Button(0, (currentState & SC_BTN_START)>0);
    set_Button(1, (currentState & SC_BTN_A)>0);
    set_Button(2, (currentState & SC_BTN_B)>0);
    set_Button(3, (currentState & SC_BTN_C)>0);
    set_Button(4, (currentState & SC_BTN_X)>0);
    set_Button(5, (currentState & SC_BTN_Y)>0);
    set_Button(6, (currentState & SC_BTN_Z)>0);
    set_Button(7, (currentState & SC_BTN_MODE)>0);*/
    lastState = currentState;
  }
  delay(1);
}
void set_Button(word currentState, word lastState, byte index, word mask){
  if (isStateChanged(currentState, lastState, mask) )
    setButton(index, (currentState & mask)>0);
}
void set_Directional(word currentState, word lastState){
  //check up down
  if ( (isStateChanged(currentState, lastState, SC_BTN_UP) || (isStateChanged(currentState, lastState, SC_BTN_DOWN) ))){
    if (currentState & SC_BTN_UP)
      setYAxis(-1);
    else if (currentState & SC_BTN_DOWN)
      setYAxis(1);
    else 
      setYAxis(0);    
  }
  if ( (isStateChanged(currentState, lastState, SC_BTN_LEFT) || (isStateChanged(currentState, lastState, SC_BTN_RIGHT) ))){
    if (currentState & SC_BTN_LEFT)
      setXAxis(-1);
    else if (currentState & SC_BTN_RIGHT)
      setXAxis(1);
    else
      setXAxis(0);
  }
}
bool isStateChanged(word currentState, word lastState, word mask){
  if ((currentState & mask) || (lastState & mask)){
    return true;
  }
  return false;
}
void setYAxis(int val){
  Serial.print("Y-");
  Serial.println(val);
  Joystick.setYAxis(val);
}
void setXAxis(int val){
  Serial.print("X-");
  Serial.println(val);
  Joystick.setXAxis(val);
}
void setButton(int index, bool state){
  //Serial.print("button call");
  Joystick.setButton(index, state);
  if (state){
    Serial.print(index);
    Serial.println("On");
  }
  else{
    Serial.print(index);
    Serial.println("Off");
  }
}
