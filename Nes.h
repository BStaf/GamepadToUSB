
class Nes : public IGameController {
  private:
    int _latch;
    int _clock;
    int _data;
    byte shift_In(int myDataPin, int myClockPin);
    word mapToCommonWord(word readWord);
  public:
    Nes(int clk, int latch, int data);
    void Init();
    word Read();
};

Nes::Nes(int clk, int latch, int data){
  _latch = latch;
  _clock = clk;
  _data = data;
}
void Nes::Init(){
  pinMode(_latch, OUTPUT);
  pinMode(_clock, OUTPUT);
  pinMode(_data, INPUT);
}

word Nes::Read(){
  //set it to 1 to collect parallel data
  digitalWrite(_latch,1);
  //set it to 1 to collect parallel data, wait
  delayMicroseconds(20);
  //set it to 0 to transmit data serially  
  digitalWrite(_latch,0);

  return  mapToCommonWord(shift_In(_data, _clock));
}

word Nes::mapToCommonWord(word readWord) {
  word commonWord = 0;
  //up
  commonWord |= (word)((bool)(readWord & (word)8) << 0);
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
  //if (commonWord > 0)
  //  Serial.println(commonWord);
  return commonWord;
}
byte Nes::shift_In(int myDataPin, int myClockPin) {
  int i;
  int temp = 0;
  byte myDataIn = 0;

  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, INPUT);
//we will be holding the clock pin high 8 times (0,..,7) at the
//end of each time through the for loop

//at the begining of each loop when we set the clock low, it will
//be doing the necessary low to high drop to cause the shift
//register's DataPin to change state based on the value
//of the next bit in its serial information flow.
//The register transmits the information about the pins from pin 7 to pin 0
//so that is why our function counts down
  for (i=7; i>=0; i--)
  {
    digitalWrite(myClockPin, 0);
    delayMicroseconds(0.2);
    temp = digitalRead(myDataPin);
    if (!temp) {
      myDataIn = myDataIn | (1 << i);
    }

    digitalWrite(myClockPin, 1);

  }
  return myDataIn;
}
