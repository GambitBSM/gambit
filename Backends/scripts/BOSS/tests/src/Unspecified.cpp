/////////////////////////////////////////
//                                     //
//  BOSS - Backend-On-a-Stick Script   //
//                                     //
/////////////////////////////////////////

// Test class for BOSS
// Definitions for an unspecified class

#include "Unspecified.hpp"

template<class T>
int Unspecified<T>::myInt() { return _myInt; }

template<class T>
double Unspecified<T>::myDouble() { return _myDouble; }

template<class T>
T Unspecified<T>::myTemplatedVar() { return _myTemplatedVar; }

template<class T>
int Unspecified<T>::doubleToInt(double x) { return int(x); }
