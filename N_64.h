#include "Nintendo.h"

class N_64 : public IGameController {
  private:
    CN64Controller * _n64Controller;
    word mapToCommonWord(N64_Report_t report);
  public:
    N_64(int data);
    void Init();
    word Read();
};

N_64::N_64(int data){
  _n64Controller = new CN64Controller(data);
}
void N_64::Init(){
  _n64Controller->begin();
  delayMicroseconds(100);  // Added delay
}

word N_64::Read(){
  if (_n64Controller->read()){
    /*if ((_n64Controller->getStatus()).device == NINTENDO_DEVICE_N64_WIRED){
      return mapToCommonWord(_n64Controller->getReport());
    }
    else{
      Serial.println("Status Fail");
    }*/
  }
  else {
    Serial.println("Read_Fail");
  }
  delay(100);
  return 0;
}

word N_64::mapToCommonWord(N64_Report_t report) {
  word commonWord = 0;
  //up
  commonWord |= (word)((bool)(report.dup) << 0);
  //down
  commonWord |= (word)((bool)(report.ddown) << 1);
  //left
  commonWord |= (word)((bool)(report.dleft) << 2);
  //right
  commonWord |= (word)((bool)(report.dright) << 3);
  //start
  commonWord |= (word)((bool)(report.start) << 4);
  //select -- no select. always 0
  commonWord |= (word)((bool)(0) << 5);
  //A
  commonWord |= (word)((bool)(report.a) << 6);
  //B
  commonWord |= (word)((bool)(report.b) << 7);
  if (commonWord > 0)
    Serial.println(commonWord);
  return commonWord;
}
