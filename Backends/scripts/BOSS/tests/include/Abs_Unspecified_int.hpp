/////////////////////////////////////////
//                                     //
//  BOSS - Backend-On-a-Stick Script   //
//                                     //
/////////////////////////////////////////

// Test class for BOSS
// Declarations for an unspecified class

class Abs_Unspecified_int
{
  public:
    virtual int myInt() = 0;
    virtual double myDouble() = 0;
    virtual int myTemplatedVar() = 0;
    virtual int doubleToInt(double) = 0;

    virtual ~Abs_Unspecified_int() = 0;
};
