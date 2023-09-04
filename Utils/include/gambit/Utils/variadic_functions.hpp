//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Variadic utilty functions.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date Feb 2014
//
///  \author Christoph Weniger
///          <c.weniger@uva.nl>
///  \date Dec 2014
///
///  *********************************************

#ifndef VARIADIC_FUNCTIONS_HPP
#define VARIADIC_FUNCTIONS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <type_traits>
#include <cassert>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <array>

namespace Gambit
{
        ///////////////////////////////
        // Lazy vector initialization
        //
        // usage:
        // auto vec = initVector("this", "is", "the", "initializer", "list");
        // auto vec = initVector(2.3, 4.2, 1.3);
        // ...
        //
        ///////////////////////////////

        template <typename T>
        std::vector<T> initVector(std::vector<T> vector)
        {
            return vector;
        }

        template <typename T, typename... Args>
        std::vector<T> initVector(std::vector<T> vector, T value, Args... args)
        {
            vector.push_back(value);
            return initVector(vector, args...);
        }

        // This function causes a (readable) compile-time error when T != U.
        // In case types are convertable, they are converted.
        template <typename T, typename U, typename... Args>
        std::vector<T> initVector(std::vector<T> vector, U value, Args... args)
        {
            T value_converted = value;
            vector.push_back(value_converted);
            return initVector(vector, args...);
        }

        template <typename T, typename... Args>
        std::vector<T> initVector(T value, Args... args)
        {
            std::vector<T> vector;
            vector.push_back(value);
            vector = initVector(vector, args...);
            return vector;
        }

        /// Same as above, but for sets

        template <typename T>
        std::set<T> initSet(std::set<T> set)
        {
            return set;
        }

        template <typename T, typename... Args>
        std::set<T> initSet(std::set<T> set, T value, Args... args)
        {
            set.insert(value);
            return initSet(set, args...);
        }

        // This function causes a (readable) compile-time error when T != U.
        // In case types are convertable, they are converted.
        template <typename T, typename U, typename... Args>
        std::set<T> initSet(std::set<T> set, U value, Args... args)
        {
            T value_converted = value;
            set.insert(value_converted);
            return initSet(set, args...);
        }

        template <typename T, typename... Args>
        std::set<T> initSet(T value, Args... args)
        {
            std::set<T> set;
            set.insert(value);
            set = initSet(set, args...);
            return set;
        }


        //////////////////////
        //div_ints_by_half
        //////////////////////

        template <int low, int hi>
        struct div_ints_by_half
        {
                static const int value = (low + hi) >> 1;
        };

        /////////////////////
        //remove_all
        /////////////////////

        template <typename T>
        struct remove_all
        {
                typedef typename std::remove_cv
                <
                        typename std::remove_volatile
                        <
                                typename std::remove_const
                                <
                                        typename std::remove_reference
                                        <
                                                T
                                        >::type
                                >::type
                        >::type
                >::type type;
        };

        /////////////////////
        //is_container
        /////////////////////

        template <typename T>
        struct __is_container__
        {
                static const bool value = false;
                typedef T type;
        };

        template <typename T>
        struct __is_container__<std::vector<T>>
        {
                static const bool value = true;
                typedef T type;
        };

        template <typename T>
        struct __is_container__<std::set<T>>
        {
                static const bool value = true;
                typedef T type;
        };

        template <typename T>
        struct __is_container__<std::multiset<T>>
        {
                static const bool value = true;
                typedef T type;
        };

        template <typename T1, typename T2>
        struct __is_container__<std::map<T1, T2>>
        {
                static const bool value = true;
                typedef std::pair<T1, T2> type;
        };

        template <typename T1, typename T2>
        struct __is_container__<std::multimap<T1, T2>>
        {
                static const bool value = true;
                typedef std::pair<T1, T2> type;
        };

        template <typename T1, typename T2>
        struct __is_container__<std::unordered_map<T1, T2>>
        {
                static const bool value = true;
                typedef std::pair<T1, T2> type;
        };

        template <typename T1, typename T2>
        struct __is_container__<std::unordered_multimap<T1, T2>>
        {
                static const bool value = true;
                typedef std::pair<T1, T2> type;
        };

        template <typename T>
        struct __is_container__<std::unordered_set<T>>
        {
                static const bool value = true;
                typedef T type;
        };

        template <typename T>
        struct __is_container__<std::unordered_multiset<T>>
        {
                static const bool value = true;
                typedef T type;
        };

        template <typename T>
        struct __is_container__<std::deque<T>>
        {
                static const bool value = true;
                typedef T type;
        };

        template <typename T, size_t N>
        struct __is_container__<std::array<T, N>>
        {
                static const bool value = true;
                typedef T type;
        };

        template <typename T>
        struct __is_container__<std::list<T>>
        {
                static const bool value = true;
                typedef T type;
        };

        template <typename T>
        struct __is_container__<std::forward_list<T>>
        {
                static const bool value = true;
                typedef T type;
        };

        template <typename T>
        struct is_container
        {
                const static bool value = __is_container__<typename remove_all<T>::type>::value;
                typedef typename __is_container__<typename remove_all<T>::type>::type type;
        };

        /////////////////////
        //is_vector
        /////////////////////

        template <typename T>
        struct __is_vector__
        {
                static const bool value = false;
                typedef T type;
        };

        template <typename T>
        struct __is_vector__<std::vector<T>>
        {
                static const bool value = true;
                typedef T type;
        };

        template <typename T>
        struct is_vector
        {
                const static bool value = __is_vector__<typename remove_all<T>::type>::value;
                typedef typename __is_vector__<typename remove_all<T>::type>::type type;
        };

        /////////////////////
        //is_pair
        /////////////////////

        template <typename T>
        struct __is_pair__
        {
                const static bool value = false;
                typedef T first_type;
                typedef T second_type;
        };

        template <typename T1, typename T2>
        struct __is_pair__ <std::pair<T1, T2>>
        {
                const static bool value = true;
                typedef T1 first_type;
                typedef T2 second_type;
        };

        template <typename T>
        struct is_pair
        {
                const static bool value = __is_pair__<typename remove_all<T>::type>::value;
                typedef typename __is_pair__<typename remove_all<T>::type>::first_type first_type;
                typedef typename __is_pair__<typename remove_all<T>::type>::second_type second_type;
        };

        //////////////////////////////////////
        //string functions
        //////////////////////////////////////

        inline const std::string stringifyVariadic() {return "";}

        inline const std::string stringifyVariadic(const std::string &str) {return str;}

        template<typename... args>
        inline const std::string stringifyVariadic(const std::string &str, const args&... strs) {return str + ", " + stringifyVariadic(strs...);}

        ///////////////////////////////
        //mult_types
        ///////////////////////////////

        template <typename... args>
        struct mult_types
        {
                typedef void type (args...);
        };

        ////////////////////////////
        //is_same_type
        ////////////////////////////

        template <typename T, typename type>
        struct is_same_type_internal;

        template <typename type>
        struct is_same_type_internal <void (), type>
        {
               static const bool value = false;
        };

        template <typename T, typename... args>
        struct is_same_type_internal <void (T, args...), T>
        {
                static const bool value = true;
        };

        template <typename type, typename T, typename... args>
        struct is_same_type_internal <void (T, args...), type>
        {
                static const bool value = is_same_type_internal <void (args...), type>::value;
        };

        template <typename type, typename T>
        struct is_same_type
        {
                static const bool value = false;
        };

        template <typename T>
        struct is_same_type <T, T>
        {
                static const bool value = true;
        };

        template <typename T, typename... args>
        struct is_same_type <mult_types<args...>, T>
        {
                static const bool value = is_same_type_internal <typename mult_types<args...>::type, T>::value;
        };

        ///////////////////////////
        //is_one_member
        ///////////////////////////

        template <typename type, typename T>
        struct is_one_member_internal;

        template <typename type>
        struct is_one_member_internal <type, void ()>
        {
                static const bool value = false;
        };

        template <typename type, typename T, typename... args>
        struct is_one_member_internal <type, void (T, args...)>
        {
                static const bool value = is_same_type<type, T>::value || is_one_member_internal<type, void (args...)>::value;
        };

        template <typename type, typename... args>
        struct is_one_member
        {
                static const bool value = is_one_member_internal<type, void (args...)>::value;
        };

        //////////////////////////////
        //is_all_member
        //////////////////////////////

        template <typename type, typename T>
        struct is_all_member_internal;

        template <typename type>
        struct is_all_member_internal <type, void ()>
        {
                static const bool value = true;
        };

        template <typename type, typename T, typename... args>
        struct is_all_member_internal <type, void (T, args...)>
        {
                static const bool value = is_same_type<type, T>::value && is_all_member_internal<type, void (args...)>::value;
        };

        template <typename type, typename... args>
        struct is_all_member
        {
                static const bool value = is_all_member_internal<type, void (args...)>::value;
        };

        ///////////////////////////////////
        //is_one_member_vector
        ///////////////////////////////////

        template <typename T>
        struct is_one_member_vector_internal;

        template <>
        struct is_one_member_vector_internal < void ()>
        {
                static const bool value = false;
        };

        template <typename T, typename... args>
        struct is_one_member_vector_internal <void (std::vector<T>, args...)>
        {
                static const bool value = true;
        };

        template <typename T, typename... args>
        struct is_one_member_vector_internal <void (std::vector<T> &, args...)>
        {
                static const bool value = true;
        };

        template <typename T, typename... args>
        struct is_one_member_vector_internal <void (const std::vector<T> &, args...)>
        {
                static const bool value = true;
        };

        template <typename T, typename... args>
        struct is_one_member_vector_internal <void (T, args...)>
        {
                static const bool value = is_one_member_vector_internal<void (args...)>::value;
        };

        template <typename... args>
        struct is_one_member_vector
        {
                static const bool value = is_one_member_vector_internal<void (args...)>::value;
        };

        //////////////////////////////
        //is_all_member_vector
        //////////////////////////////

        template <typename T>
        struct is_all_member_vector_internal;

        template <>
        struct is_all_member_vector_internal <void ()>
        {
                static const bool value = true;
        };

        template <typename T, typename... args>
        struct is_all_member_vector_internal <void (std::vector<T>, args...)>
        {
                static const bool value = is_all_member_vector_internal<void (args...)>::value;
        };

        template <typename T, typename... args>
        struct is_all_member_vector_internal <void (std::vector<T> &, args...)>
        {
                static const bool value = is_all_member_vector_internal<void (args...)>::value;
        };

        template <typename T, typename... args>
        struct is_all_member_vector_internal <void (const std::vector<T> &, args...)>
        {
                static const bool value = is_all_member_vector_internal<void (args...)>::value;
        };

        template <typename T, typename... args>
        struct is_all_member_vector_internal <void (T, args...)>
        {
                static const bool value = false;
        };

        template <typename... args>
        struct is_all_member_vector
        {
                static const bool value = is_all_member_vector_internal<void (args...)>::value;
        };

        /////////////////////////////
        //enable_if's
        /////////////////////////////

        template <typename T, typename ret, typename... args>
        struct enable_if_one_member
        {
                typedef std::enable_if<is_one_member<T, args...>::value, ret> type;
        };

        template <typename T, typename ret, typename... args>
        struct enable_if_all_member
        {
                typedef std::enable_if<is_all_member<T, args...>::value, ret> type;
        };

        template <typename ret, typename... args>
        struct enable_if_one_member_vector
        {
                typedef std::enable_if<is_one_member_vector<args...>::value, ret> type;
        };

        template <typename ret, typename... args>
        struct enable_if_all_member_vector
        {
                typedef std::enable_if<is_all_member_vector<args...>::value, ret> type;
        };

        //////////////////////////////////////
        //enable_if_not's
        //////////////////////////////////////

        template <typename T, typename ret, typename... args>
        struct enable_if_not_one_member
        {
                typedef std::enable_if<!is_one_member<T, args...>::value, ret> type;
        };

        template <typename T, typename ret, typename... args>
        struct enable_if_not_all_member
        {
                typedef std::enable_if<!is_all_member<T, args...>::value, ret> type;
        };

        template <typename ret, typename... args>
        struct enable_if_not_one_member_vector
        {
                typedef std::enable_if<!is_one_member_vector<args...>::value, ret> type;
        };

        template <typename ret, typename... args>
        struct enable_if_not_all_member_vector
        {
                typedef std::enable_if<!is_all_member_vector<args...>::value, ret> type;
        };
}

#endif
