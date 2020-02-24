/////////////////////////////////////////
//                                     //
//  BOSS - Backend-On-a-Stick Script   //
//                                     //
/////////////////////////////////////////

// Test class for BOSS
// Definitions for an unspecified class

#include "U.hpp"

template<class T>
int U<T>::myInt() { return _myInt; }

template<class T>
double U<T>::myDouble() { return _myDouble; }

template<class T>
T U<T>::myTemplatedVar() { return _myTemplatedVar; }

template<class T>
int U<T>::doubleToInt(double x) { return int(x); }
