/********************************************************************
 * All controllers need to have a common map
 * Based on mapping retroPie accepts
 * Up         0
 * Down       1
 * Left       2
 * Right      3
 * Start      4
 * Select     5
 * A          6
 * B          7
 * X          8
 * Y          9
 * LShoulder  10
 * RShoulder  11
********************************************************************/
class IGameController{
  public:
    virtual void Init();
    virtual word Read();
};
