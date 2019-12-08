/********************************************************************
 * All controllers need to have a common map
 * Based on mapping retroPie accepts
 * bit deffinition of ControllerStatus.Buttons
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
 * LTrigger   12
 * RTrigger   13
 * N64_Cup    14  //C vales would be mapped to right analog in retroPie
 * N64_CDown  15
 * N64_CLeft  16
 * N64_CRight 17
 * N64_XAxis  7 bit 19 - 24 // mapped to left analog in retroPie
 * N64_YAxis  7 bit 25 - 31
********************************************************************/
struct ControllerStatus
{
   unsigned long Buttons;
   int XAxis;
   int YAxis;
};
class IGameController{
  public:
    virtual bool HasChanged();
    virtual void Init();
    virtual ControllerStatus Read(); 
};
