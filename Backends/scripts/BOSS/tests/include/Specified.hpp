/////////////////////////////////////////
//                                     //
//  BOSS - Backend-On-a-Stick Script   //
//                                     //
/////////////////////////////////////////

// Test class for BOSS
// Declarations for a specified class

template<class T>
class Specified;

template <>
class Specified<int>
{
  int _myInt;

  int myInt();
};

template<>
class Specified<double>
{
  double _myDouble;

  double myDouble();
};
