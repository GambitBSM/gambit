/////////////////////////////////////////
//                                     //
//  BOSS - Backend-On-a-Stick Script   //
//                                     //
/////////////////////////////////////////

// Test class for BOSS
// Declarations for a specified class

template<class T>
class S;

template <>
class S<int>
{
  int _myInt;

  int myInt();
};

template<>
class S<double>
{
  double _myDouble;

  double myDouble();
};
