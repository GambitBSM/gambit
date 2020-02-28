/////////////////////////////////////////
//                                     //
//  BOSS - Backend-On-a-Stick Script   //
//                                     //
/////////////////////////////////////////

// Test class for BOSS
// Declarations for an unspecified class

//#include "Abs_Unspecified_int.hpp"

template <class T>
class Unspecified
{
  private:
    int _myInt;
    double _myDouble;
    T _myTemplatedVar;

  public:
    //Unspecified(int, double, T);
    int myInt();
    double myDouble();
    T myTemplatedVar();
    int doubleToInt(double);
};

typedef Unspecified<int> Unspecified_int;
typedef Unspecified<double> Unspecified_double;
