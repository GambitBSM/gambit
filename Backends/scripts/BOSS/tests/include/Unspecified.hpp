/////////////////////////////////////////
//                                     //
//  BOSS - Backend-On-a-Stick Script   //
//                                     //
/////////////////////////////////////////

// Test class for BOSS
// Declarations for an unspecified class

template <class T>
class Unspecified
{
  private:
    int _myInt;
    double _myDouble;
    T _myTemplatedVar;

  public:
    int myInt();
    double myDouble();
    T myTemplatedVar();
    int doubleToInt(double);
};
