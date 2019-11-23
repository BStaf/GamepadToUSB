/********************************************************************
 * All controllers need to have a common map
 * Up     0
 * Down   1
 * Left   2
 * Right  3
 * Start  4
 * Select 5
 * A      6
 * B      7
 * C      8
 * X      9
 * Y      10
 * Z      11
********************************************************************/
class IGameController{
  public:
    virtual void Init();
    virtual word Read();
};
