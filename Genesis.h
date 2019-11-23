
#include <SegaController.h>

class Genesis : public IGameController {
  private:
    SegaController * _controller;
    word mapToCommonWord(word readWord);
  public:
    Genesis(int pin1, int pin2, int pin3, int pin4, int pin6, int pin7, int pin9);
    void Init();
    word Read();
};
//DB9 Pin 7, DB9 Pin 1, DB9 Pin 2, DB9 Pin 3, DB9 Pin 4, DB9 Pin 6, DB9 Pin 9
Genesis::Genesis(int pin1, int pin2, int pin3, int pin4, int pin6, int pin7, int pin9){
  //3, 4, 5, 6, 7, 8, 9
  _controller = new SegaController(pin7, pin1, pin2, pin3, pin4, pin6, pin9);
}
void Genesis::Init(){
  //no init needed
}

word Genesis::Read(){
  return  mapToCommonWord(_controller->getState());
}
word Genesis::mapToCommonWord(word readWord) {
  word commonWord = 0;
  //up
  /*commonWord |= (word)((bool)(readWord & (word)8) << 0);
  //down
  commonWord |= (word)((bool)(readWord & (word)4) << 1);
  //left
  commonWord |= (word)((bool)(readWord & (word)2) << 2);
  //right
  commonWord |= (word)((bool)(readWord & (word)1) << 3);
  //start
  commonWord |= (word)((bool)(readWord & (word)16) << 4);
  //select
  commonWord |= (word)((bool)(readWord & (word)32) << 5);
  //A
  commonWord |= (word)((bool)(readWord & (word)128) << 6);
  //B
  commonWord |= (word)((bool)(readWord & (word)64) << 7);
  */
  Serial.println(readWord);
  return commonWord;
}
