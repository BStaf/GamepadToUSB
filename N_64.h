#include "Nintendo.h"

class N_64 : public IGameController {
  private:
    CN64Controller * _n64Controller;
    ControllerStatus _lastStatus;
    unsigned long mapToCommonWord(N64_Report_t report);
    bool _hasChanged;
  public:
    N_64(int data);
    void Init();
    ControllerStatus Read();
    bool HasChanged();
};

N_64::N_64(int data){
  _n64Controller = new CN64Controller(data);
  _hasChanged = false;
}
void N_64::Init(){
  _n64Controller->begin();
  delayMicroseconds(100);  // Added delay
  
}

bool N_64::HasChanged(){
  Serial.println(_hasChanged);
  return _hasChanged;
}

ControllerStatus N_64::Read(){
  ControllerStatus status;
  //this delay is needed. Not sure why. 
  //read fails without it.
  delay(1);
  if (_n64Controller->read()){
    if ((_n64Controller->getStatus()).device == NINTENDO_DEVICE_N64_WIRED){
      status.Buttons = mapToCommonWord(_n64Controller->getReport());
      status.XAxis = _n64Controller->getReport().xAxis;
      status.YAxis = _n64Controller->getReport().yAxis;
      if ((status.Buttons == _lastStatus.Buttons)&&(status.XAxis == _lastStatus.XAxis)&&(status.YAxis == _lastStatus.YAxis))
        _hasChanged = false;
      else
        _hasChanged = true;
      _lastStatus = status;
    }
  }
  else {
    Serial.println("Read_Fail");
    delay(100);
  }
  return status;
}

unsigned long N_64::mapToCommonWord(N64_Report_t report) {
  unsigned long commonWord = 0;
  unsigned long val = (unsigned long)(report.xAxis + 80) << 18;
  //up
  commonWord |= (unsigned long)((bool)(report.dup) << 0);
  //down
  commonWord |= (unsigned long)((bool)(report.ddown) << 1);
  //left
  commonWord |= (unsigned long)((bool)(report.dleft) << 2);
  //right
  commonWord |= (unsigned long)((bool)(report.dright) << 3);
  //start
  commonWord |= (unsigned long)((bool)(report.start) << 4);
  //select -- no select. always 0
  commonWord |= (unsigned long)((bool)(0) << 5);
  //A -> B
  commonWord |= (unsigned long)((bool)(report.a) << 7);
  //B -> Y
  commonWord |= (unsigned long)((bool)(report.b) << 9);
  //Z -> LeftTrigger
  commonWord |= (unsigned long)((bool)(report.z) << 12);
  //LeftSholder -> LeftSholder
  commonWord |= (unsigned long)((bool)(report.l) << 10);
  //RightSholder -> RightSholder
  commonWord |= (unsigned long)((bool)(report.r) << 11);
  //Cup -> Cup
  commonWord |= (unsigned long)((bool)(report.cup) << 14);
  //Cdown -> A
  commonWord |= (unsigned long)((bool)(report.cdown) << 6);
  //Cleft -> X
  commonWord |= (unsigned long)report.cleft << 8;
  //Cright -> cright
  commonWord |= (unsigned long)report.cright << 17;
  if (commonWord > 0)
    Serial.println(commonWord);
  return commonWord;
}
