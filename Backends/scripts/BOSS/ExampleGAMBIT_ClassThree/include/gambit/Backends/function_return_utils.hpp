#ifndef __FUNCTION_RETURN_UTILS_HPP__
#define __FUNCTION_RETURN_UTILS_HPP__

// Function used to return pointer-to-wrapper
template<typename U, typename V>
U* pointer_returner(V* ptr);

// Function used to return reference-to-wrapper
template<typename U, typename V>
U& reference_returner(V* ptr);

// Version of the above function taking a const input
template<typename U, typename V>
U& reference_returner(const V* ptr);

#endif