/*
 * _______
 * \  ___ `'.                                 _..._        .
 *  ' |--.\  \                _.._          .'     '.    .'|
 *  | |    \  '             .' .._|        .   .-.   . .'  |
 *  | |     |  '    __      | '            |  '   '  |<    |
 *  | |     |  | .:--.'.  __| |__  _    _  |  |   |  | |   | ____
 *  | |     ' .'/ |   \ ||__   __|| '  / | |  |   |  | |   | \ .'
 *  | |___.' /' `" __ | |   | |  .' | .' | |  |   |  | |   |/  .
 * /_______.'/   .'.''| |   | |  /  | /  | |  |   |  | |    /\  \
 * \_______|/   / /   | |_  | | |   `'.  | |  |   |  | |   |  \  \
 *              \ \._,\ '/  | | '   .'|  '/|  |   |  | '    \  \  \
 *               `--'  `"   |_|  `-'  `--' '--'   '--''------'  '---'
 *
 *                         daFunk - dynamisch allokierbare Funktionen
 *
 *  v0.1 Dec 2014
 *  v0.2 Mar 2015 - Completely rewritten internal structure
 *  v0.3 May 2016 - Extensions
 *
 *  Christoph Weniger, created Dec 2014, edited until May 2016
 *  <c.weniger@uva.nl>
 *
 *  with contributions related to thread-safety from
 *  Lars A. Dal, Apr, Jun 2015
 *  <l.a.dal@fys.uio.no>
 *
 *
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Christoph Weniger
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __DAFUNK_HPP__
#define __DAFUNK_HPP__

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <stdexcept>

//#define NDEBUG
#include <assert.h>

//#define GAMBIT_DIR

#ifdef GAMBIT_DIR
#include <omp.h>
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/util_macros.hpp"
#endif

#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"

//#include <memory>
//using std::shared_ptr;
//using std::enable_shared_from_this;

namespace daFunk {class FunkPlain;}

#define DEF_FUNKTRAIT(C)                            \
class C {                                           \
    public:                                         \
        static daFunk::FunkPlain* ptr;              \
        static void set(daFunk::FunkPlain* new_ptr) \
        {                                           \
            delete ptr;                             \
            ptr = new_ptr;                          \
        }                                           \
};                                                  \
daFunk::FunkPlain* C::ptr = NULL;

// Extensions
#include <gsl/gsl_integration.h>
#include <gsl/gsl_errno.h>

namespace daFunk
{
    //
    // Type declarations etc.
    //

    using boost::shared_ptr;
    using boost::enable_shared_from_this;
    using boost::dynamic_pointer_cast;
    using boost::static_pointer_cast;

    class FunkBase;
    class FunkBound;
    class FunkIntegrate_gsl1d;

    typedef shared_ptr<FunkBase> Funk;
    typedef shared_ptr<FunkBound> BoundFunk;
    typedef std::vector<std::string> ArgsType;
    typedef std::map<std::string, std::vector<std::pair<Funk, Funk>>> Singularities;

    //template <typename... Args>
    //using PlainPtr = double(*)(Args&...);
    typedef double(*PlainPtr1)(double&);
    typedef double(*PlainPtr2)(double&,double&);
    typedef double(*PlainPtr3)(double&,double&,double&);
    typedef double(*PlainPtr4)(double&,double&,double&,double&);

    //template <typename... Args>
    //using PlainPtrs = std::pair<double(*)(Args...,void*), void*>;
    typedef std::pair<double(*)(double,void*), void*> PlainPtrs1;
    typedef std::pair<double(*)(double,double,void*), void*> PlainPtrs2;
    typedef std::pair<double(*)(double,double,double,void*), void*> PlainPtrs3;
    typedef std::pair<double(*)(double,double,double,double,void*), void*> PlainPtrs4;


    //
    // Vector initialization from argument list
    //
    // Usage: std::vector<T> v = vec<T>(v1, v2, v3, ...);
    //

    template <typename T>
    inline std::vector<T> vec(std::vector<T> vector)
    {
        return vector;
    }
    template <typename T, typename... Args>
    inline std::vector<T> vec(std::vector<T> vector, T value, Args... args)
    {
        vector.push_back(value);
        return vec<T>(vector, args...);
    }
    template <typename T, typename... Args>
    inline std::vector<T> vec(T value, Args... args)
    {
        std::vector<T> vector;
        vector.push_back(value);
        vector = vec<T>(vector, args...);
        return vector;
    }
    template <typename T>
    inline std::vector<T> vec()
    {
        std::vector<T> vector;
        return vector;
    }

    //
    // Math helper functions
    //

    // Generate linear 1-dim grid
    inline std::vector<double> linspace(double x0, double x1, unsigned int n)
    {
        std::vector<double> ret;
        double dx = 0;
        if (n > 1)
            dx = (x1-x0)/(n-1);
            for (unsigned int i = 0; i<n; i++)
            {
                ret.push_back(x0 + i * dx);
            }
        return ret;
    }

    // Generate logarithmic 1-dim grid
    inline std::vector<double> logspace(double x0, double x1, unsigned int n)
    {
        std::vector<double> ret;
        double dx = 0;
        if (n > 1)
            dx = (x1-x0)/(n-1);
            for (unsigned int i = 0; i<n; i++)
            {
                ret.push_back(pow(10, x0 + i * dx));
            }
        return ret;
    }


    //
    // Helper functions for internal calculations
    //

    inline bool args_match(ArgsType args1, ArgsType args2)
    {
        bool m = true;
        for ( auto it = args1.begin(); it!=args1.end(); it++ )
        {
            if ( std::find(args2.begin(), args2.end(), *it) == args2.end() )
                m = false;
        }
        if ( args1.size() != args2.size() ) m = false;
        return m;
    }

    inline std::string args_string(ArgsType args)
    {
        std::string msg = "";
        for ( auto it = args.begin(); it!=args.end(); it++ )
        {
            msg += *it;
            if ( it != args.end() - 1)
                msg += ", ";
        }
        return msg;
    }

    inline ArgsType joinArgs(ArgsType args1, ArgsType args2)
    {
        args1.insert(args1.end(), args2.begin(), args2.end());
        std::set<std::string> argsset(args1.begin(), args1.end());
        args1.assign(argsset.begin(), argsset.end());
        return args1;
    }

    inline ArgsType eraseArg(ArgsType args, std::string arg)
    {
        auto it = std::find(args.begin(), args.end(), arg);
        if (it!=args.end()) args.erase(it);
        return args;
    }

    inline Singularities joinSingl(Singularities s1, Singularities s2)
    {
        for ( auto it = s2.begin(); it != s2.end(); ++it )
        {
            if ( s1.find(it->first) == s1.end() )
                s1[it->first] = it->second;
            else
            {
                for ( auto it2 = it->second.begin(); it2 != it->second.end(); ++it2 )
                {
                    if ( std::find(s1[it->first].begin(), s1[it->first].end(), *it2) == s1[it->first].end() )
                        s1[it->first].push_back(*it2);
                }
            }
        }
        return s1;
    }


    //
    // Index lists (taken from stackoverflow)
    //

    // The structure that encapsulates index lists
    template <size_t... Is>
    struct index_list
    {
    };

    // Collects internal details for generating index ranges [MIN, MAX)
    namespace detail
    {
        // Declare primary template for index range builder
        template <size_t MIN, size_t N, size_t... Is>
        struct range_builder;

        // Base step
        template <size_t MIN, size_t... Is>
        struct range_builder<MIN, MIN, Is...>
        {
            typedef index_list<Is...> type;
        };

        // Induction step
        template <size_t MIN, size_t N, size_t... Is>
        struct range_builder : public range_builder<MIN, N - 1, N - 1, Is...>
        {
        };
    }


    //
    // **** The central virtual base class ****
    //

    class FunkBase: public enable_shared_from_this<FunkBase>
    {
        public:
            FunkBase() {};
            virtual ~FunkBase() {};

            // Standard setting handles
            template <typename... Args> Funk set(std::string arg, Funk g, Args... args);
            template <typename... Args> Funk set(std::string arg, double x, Args... args);
            template <typename... Args> Funk set(std::string arg, std::string arg1, Args... args);
            template <typename... Args> Funk set();

            // Standard binding handles
            template <typename... Args> shared_ptr<FunkBound> bind(Args... args);

            // Convenience functions
            const std::vector<std::string> & getArgs() { return this->arguments; };
            std::size_t getNArgs() {return this->arguments.size();};
            bool hasArg(std::string);
            bool hasArgs();
            Funk help();
            template <typename... Args> bool assert_args(Args... args);

            // Return value & standard resolve
            virtual double value(const std::vector<double> &, size_t bindID) = 0;

            // datamap maps the required function arguments onto the specific
            // entries in the double-valued data array generated by eval().
            // datalen acts like a pointer on the last entry of that array, and
            // can be increased if more workspace is required.  bindID ensures
            // that resolution for various different binds can happen in
            // parallel with the same Funk objects.
            virtual void resolve(std::map<std::string, size_t> datamap, size_t & datalen, size_t bindID, std::map<std::string,size_t> &argmap);


            // Singularities handling
            Singularities getSingl() { return singularities; }
        private:  // Note: This works currently only for constant functions
            Funk set_singularity(std::string arg, Funk pos, Funk width);
            Funk set_singularity(std::string arg, double pos, Funk width);
            Funk set_singularity(std::string arg, Funk pos, double width);
        public:
            Funk set_singularity(std::string arg, double pos, double width);

            // Print message
            Funk print(std::string arg);


            //
            // "External" functions
            //

            // Integration
            template <typename... Args> shared_ptr<FunkIntegrate_gsl1d> gsl_integration(Args... args);

            // Plain function generators
            PlainPtrs1 plain(std::string);
            PlainPtrs2 plain(std::string, std::string);
            PlainPtrs3 plain(std::string, std::string, std::string);
            PlainPtrs4 plain(std::string, std::string, std::string, std::string);
            template <typename T>
            PlainPtr1 plain(std::string);
            template <typename T>
            PlainPtr2 plain(std::string, std::string);
            template <typename T>
            PlainPtr3 plain(std::string, std::string, std::string);
            template <typename T>
            PlainPtr4 plain(std::string, std::string, std::string, std::string);

        protected:
            std::vector<Funk> functions;  // Dependent functions
            ArgsType arguments;  // Argument names
            std::vector<std::vector<size_t> > indices;  // Indices for data object
            size_t datalen;
            Singularities singularities;
    };

    // A vector class with global knowledge about its health status.
    // (BoundFunk objects are occasionally destructed *after* livingVector has
    // been destructed, causing segfaults if not catched properly.)
    class livingVector: public std::vector<size_t>
    {
        public:
            ~livingVector()
            {
                livingVector::is_dead() = true;
            }
            static bool & is_dead()
            {
                static bool dead = false;
                return dead;
            }
    };

    class FunkBound
    {
        public:
            FunkBound(Funk f, size_t datalen, size_t bindID) : f(f), datalen(datalen), bindID(bindID) {};
            ~FunkBound() {bindID_manager(bindID,false);};
            double value(std::vector<double> & map, size_t bindID) {(void)bindID; (void)map; return 0;};

            template <typename... Args> inline double eval(Args... argss)
            {
                auto data = vec<double>(argss...);
                data.resize(datalen);
                return f->value(data, bindID);
            }

            template <typename... Args> inline std::vector<double> vect(Args... argss)
            {
                std::vector<std::vector<double>> coll;
                return this->vect2(coll, argss...);
            }

        private:
            template <typename... Args>
            friend shared_ptr<FunkBound> FunkBase::bind(Args... argss);
            // Function for generating unique bindIDs.
            // IDs are sequential, starting from 0.
            static void bindID_manager(size_t &bindID, bool bind)
            {
              static size_t n_idx = 0;
              static livingVector free;
              if(bind)
              {
                #pragma omp critical (bindID_allocation)
                {
                    if(free.empty())
                    {
                        // Increment after assignment (n_idx++ instead of ++n_idx)
                        bindID = n_idx++;
                    }
                    else
                    {
                        bindID = free.back();
                        free.pop_back();
                    }
                }
              }
              else
              {
                    if ( not livingVector::is_dead() )
                    {
                        #pragma omp critical (bindID_allocation)
                        free.push_back(bindID);
                    }
              }
            }
            template <typename... Args> inline std::vector<double> vect2(std::vector<std::vector<double>> & coll)
            {
                size_t size = 1;
                std::vector<bool> vec_flag;
                for ( auto it = coll.begin(); it != coll.end(); ++it )
                {
                    if ( it->size() == 1 )
                    {
                        vec_flag.push_back(false);
                        continue;
                    }
                    vec_flag.push_back(true);
                    if ( size == 1 ) size = it->size();
                    if ( size != it->size() )
                    {
                        std::cerr << "daFunk::FunkBase WARNING: Inconsistent vector lengths." << std::endl;
                        return vec<double>();
                    }
                }
                auto r = vec<double>();
                auto data = vec<double>();
                data.resize(datalen);
                for ( size_t i = 0; i != size; ++i )
                {
                    for ( size_t j = 0; j != coll.size(); ++j )
                    {
                        if ( vec_flag[j] )
                            data[j] = coll[j][i];
                        else
                            data[j] = coll[j][0];
                    }
                    r.push_back(f->value(data, bindID));
                }
                return r;
            }

            template <typename... Args> inline std::vector<double> vect2(std::vector<std::vector<double>> & coll, double x, Args... argss)
            {
                coll.push_back(vec<double>(x));
                return this->vect2(coll, argss...);
            }

            template <typename... Args> inline std::vector<double> vect2(std::vector<std::vector<double>> & coll, std::vector<double> v, Args... argss)
            {
                coll.push_back(v);
                return this->vect2(coll, argss...);
            }

            Funk f;  // bound function

            // datalen is the length of the double-valued data array that is
            // needed as workspace for function evaluation, and that is created
            // on the heap for each eval separately to ensure thread-safety.
            size_t datalen;

            // bindID has the purpose of allowing bound functions (instances of
            // FunkBase and daughter classes) to be bound by various binding
            // functions simultaneously.
            size_t bindID;
    };


    //
    // Derived class with (templated) static member functions as plain function
    // prototypes.
    //

    class FunkPlain: public FunkBase
    {
        public:
            FunkPlain(Funk fin, std::string arg1) : f(fin->bind(arg1)) {}
            FunkPlain(Funk fin, std::string arg1, std::string arg2) : f(fin->bind(arg1, arg2)) {}
            FunkPlain(Funk fin, std::string arg1, std::string arg2, std::string arg3) : f(fin->bind(arg1, arg2, arg3)) {}
            FunkPlain(Funk fin, std::string arg1, std::string arg2, std::string arg3, std::string arg4) : f(fin->bind(arg1, arg2, arg3, arg4)) {}

            static double plain1p(double x1, void* ptr)
            {
                FunkPlain * funkPtrPtr = static_cast<FunkPlain*>(ptr);
                return funkPtrPtr->f->eval(x1);
            }
            static double plain2p(double x1, double x2, void* ptr)
            {
                FunkPlain * funkPtrPtr = static_cast<FunkPlain*>(ptr);
                return funkPtrPtr->f->eval(x1, x2);
            }
            static double plain3p(double x1, double x2, double x3, void* ptr)
            {
                FunkPlain * funkPtrPtr = static_cast<FunkPlain*>(ptr);
                return funkPtrPtr->f->eval(x1, x2, x3);
            }
            static double plain4p(double x1, double x2, double x3, double x4, void* ptr)
            {
                FunkPlain * funkPtrPtr = static_cast<FunkPlain*>(ptr);
                return funkPtrPtr->f->eval(x1, x2, x3, x4);
            }

            template <typename T>
            static double plain1(double& x1)
            {
                FunkPlain * funkPtrPtr = static_cast<FunkPlain*>(T::ptr);
                return funkPtrPtr->f->eval(x1);
            }
            template <typename T>
            static double plain2(double& x1, double& x2)
            {
                FunkPlain * funkPtrPtr = static_cast<FunkPlain*>(T::ptr);
                return funkPtrPtr->f->eval(x1, x2);
            }
            template <typename T>
            static double plain3(double& x1, double& x2, double& x3)
            {
                FunkPlain * funkPtrPtr = static_cast<FunkPlain*>(T::ptr);
                return funkPtrPtr->f->eval(x1, x2, x3);
            }
            template <typename T>
            static double plain4(double& x1, double& x2, double& x3, double& x4)
            {
                FunkPlain * funkPtrPtr = static_cast<FunkPlain*>(T::ptr);
                return funkPtrPtr->f->eval(x1, x2, x3, x4);
            }

            double value(const std::vector<double> & args, size_t bindID)
            {
                (void)args;
                (void)bindID;
                assert ( 0 == 1 );  // This function should never be called
                return 0;
            }

        private:
            shared_ptr<FunkBound> f;  // bound function
            std::string arg1, arg2, arg3, arg4;
    };

    //
    // Derived class that implements constant
    //

    class FunkConst: public FunkBase
    {
        public:
            template <typename... Args>
            FunkConst(double c, Args ...argss) : c(c) { arguments = vec<std::string>(argss...); }
            FunkConst(double c) : c(c) { arguments.resize(0); }

            double value(const std::vector<double> & data, size_t bindID)
            {
                (void)data;
                (void)bindID;
                return c;
            }

        private:
            double c;
    };
    template <typename... Args>
    inline Funk one(Args... argss) { return Funk(new FunkConst(1., argss...)); }
    template <typename... Args>
    inline Funk zero(Args... argss) { return Funk(new FunkConst(0., argss...)); }
    template <typename... Args>
    inline Funk cnst(double x, Args... argss) { return Funk(new FunkConst(x, argss...)); }


    //
    // Derived class that implements setting of parameters
    //

    class FunkDerived: public FunkBase
    {
        public:
            FunkDerived(Funk f, std::string arg, Funk g) : my_arg(arg)
            {
                setup(f, arg, g);
            };

            FunkDerived(Funk f, std::string arg, double x) : my_arg(arg)
            {
                setup(f, arg, cnst(x));
            }

            // We need to sneak in an additional parameter
            void resolve(std::map<std::string, size_t> datamap, size_t & datalen, size_t bindID, std::map<std::string,size_t> &argmap)
            {
                functions[1]->resolve(datamap, datalen, bindID, argmap);  // resolve g
                // add new slot for result from of g
                if(my_index.size() <= bindID)
                {
                    my_index.resize(bindID+1);
                    // TODO: Introduce informative error message if bind fails
                    // because of inconsistencies, e.g. along the lines:
                    //
                    //    std::cout << "FATAL ERROR: bind() attempts to resolve dependencies for FunkDerived" << std::endl;
                    //    std::cout << "object inconsistently." << std::endl;
                    //    std::cout << "Encountered while resolving " << my_arg << " and:" << std::endl;
                    //    for (auto it = datamap.begin(); it != datamap.end(); it++)
                    //    {
                    //        std::cout << "  " << it->first << std::endl;
                    //    }
                    //    exit(1);
                }
                if ( argmap.find(my_arg) == argmap.end() )
                {
                    if(datamap.find(my_arg) == datamap.end())
                    {
                        my_index[bindID] = datalen;
                        argmap[my_arg]   = datalen;
                        ++datalen;
                    }
                    else
                    {
                        my_index[bindID] = datamap[my_arg];
                    }
                }
                else
                {
                    my_index[bindID] = argmap[my_arg];
                }
                datamap[my_arg]  = my_index[bindID];  // add or overwrite entry in datamap
                functions[0]->resolve(datamap, datalen, bindID, argmap);  // resolve f
            }

            double value(const std::vector<double> & data, size_t bindID)
            {
                std::vector<double> data2(data);
                data2[my_index[bindID]] = functions[1]->value(data, bindID);
                return functions[0]->value(data2, bindID);
            }

        private:
            std::string my_arg;


            void setup(Funk f, std::string arg, Funk g)
            {
                functions = vec(f, g);
                Singularities tmp_singl = f->getSingl();
                if ( tmp_singl.erase(arg) > 0 )
                    std::cout << "daFunk::FunkBase WARNING: Loosing singularity information while setting " << arg << std::endl;
                singularities = joinSingl(g->getSingl(), tmp_singl);
                arguments = joinArgs(eraseArg(f->getArgs(), arg), g->getArgs());
            };
            std::vector<size_t> my_index;
    };


    //
    // Derived class for the import of plain functions
    //

    template <bool threadsafe, typename... funcargs>
    class FunkFunc : public FunkBase
    {
        public:
            template <typename... Args>
            FunkFunc(double (*f)(funcargs...), Args... argss)
            {
                ptr = f;
                digest_input(argss...);
            }

            double value(const std::vector<double> & data, size_t bindID)
            {
                std::tuple<typename std::remove_reference<funcargs>::type...> my_input;
                double result;
                size_t i = 0;
                #pragma omp critical (FunkFunc_setInput)
                {
                    for ( auto f = functions.begin(); f != functions.end(); ++f, ++i)
                    {
                        *map[i] = (*f)->value(data, bindID);
                    }
                    my_input = input;
                }
                if(threadsafe)
                {
                    result = ppp(typename detail::range_builder<0, sizeof...(funcargs)>::type(), my_input);
                }
                else
                {
                    #pragma omp critical (FunkFunc_externalFunctionCall)
                    {
                        result = ppp(typename detail::range_builder<0, sizeof...(funcargs)>::type(), my_input);
                    }
                }
                return result;
            }

            template <size_t... Args>
            double ppp(index_list<Args...>, std::tuple<typename std::remove_reference<funcargs>::type...> & my_input)
            {
                return (*ptr)(std::get<Args>(my_input)...);
            }

        private:
            std::tuple<typename std::remove_reference<funcargs>::type...> input;
            std::vector<double*> map;
            double (*ptr)(funcargs...);

            // Digest input parameters
            // (forwarding everything except daFunk::Funk types, which is mapped onto
            // funktion parameters)
            template<typename T, typename... Args>
            void digest_input(T x, Args... argss)
            {
                const int i = sizeof...(funcargs) - sizeof...(argss) - 1;
                std::get<i>(input) = x;
                digest_input(argss...);
            }
            template<typename... Args>
            void digest_input(Funk f, Args... argss)
            {
                const int i = sizeof...(funcargs) - sizeof...(argss) - 1;
                map.push_back(&std::get<i>(input));
                arguments = joinArgs(arguments, f->getArgs());
                functions.push_back(f);
                singularities = joinSingl(singularities, f->getSingl());
                digest_input(argss...);
            }
            void digest_input() {};
    };

    template <typename... funcargs, typename... Args>
    Funk func(double (*f)(funcargs...), Args... args) {
        return Funk(new FunkFunc<false, funcargs...>(f, args...));
    }
    // Version that assumes the function to be threadsafe
    template <typename... funcargs, typename... Args>
    Funk func_fromThreadsafe(double (*f)(funcargs...), Args... args) {
        return Funk(new FunkFunc<true, funcargs...>(f, args...));
    }


    template <bool threadsafe, typename O, typename... funcargs>
    class FunkFuncM : public FunkBase
    {
        public:
            template <typename... Args>
            FunkFuncM(O* obj, double (O::* f)(funcargs...), Args... argss) : obj(obj)
            {
                ptr = f;
                digest_input(argss...);
            }

            template <typename... Args>
            FunkFuncM(shared_ptr<O> obj, double (O::* f)(funcargs...), Args... argss) : shared_obj(obj), obj(&*obj)
            {
                ptr = f;
                digest_input(argss...);
            }

            double value(const std::vector<double> & data, size_t bindID)
            {
                std::tuple<typename std::remove_reference<funcargs>::type...> my_input;
                double result;
                size_t i = 0;
                #pragma omp critical(FunkFuncM_value)
                {
                    for ( auto f = functions.begin(); f != functions.end(); ++f, ++i)
                    {
                        *map[i] = (*f)->value(data, bindID);
                    }
                    my_input = input;
                }
                if(threadsafe)
                {
                    result = ppp(typename detail::range_builder<0, sizeof...(funcargs)>::type(), my_input);
                }
                else
                {
                    #pragma omp critical (FunkFuncM_objectFunctionCall)
                    {
                        result = ppp(typename detail::range_builder<0, sizeof...(funcargs)>::type(), my_input);
                    }
                }
                return result;
            }

            template <size_t... Args>
            double ppp(index_list<Args...>, std::tuple<typename std::remove_reference<funcargs>::type...> & my_input)
            {
                return (*obj.*ptr)(std::get<Args>(my_input)...);
            }

        private:
            std::tuple<typename std::remove_reference<funcargs>::type...> input;
            std::vector<double*> map;
            double (O::* ptr)(funcargs...);
            shared_ptr<O> shared_obj;
            O* obj;

            // Digest input parameters
            // (forwarding everything except daFunk::Funk types, which is mapped onto
            // funktion parameters)
            template<typename T, typename... Args>
            void digest_input(T x, Args... argss)
            {
                const int i = sizeof...(funcargs) - sizeof...(argss) - 1;
                std::get<i>(input) = x;
                digest_input(argss...);
            }
            template<typename... Args>
            void digest_input(Funk f, Args... argss)
            {
                const int i = sizeof...(funcargs) - sizeof...(argss) - 1;
                map.push_back(&std::get<i>(input));
                arguments = joinArgs(arguments, f->getArgs());
                functions.push_back(f);
                singularities = joinSingl(singularities, f->getSingl());
                digest_input(argss...);
            }
            void digest_input() {};
    };


    template <typename O, typename... funcargs, typename... Args>
    Funk funcM(O* obj, double (O::* f)(funcargs...), Args... args) {
        return Funk(new FunkFuncM<false, O, funcargs...>(obj, f, args...));
    }
    template <typename O, typename... funcargs, typename... Args>
    Funk funcM(shared_ptr<O> obj, double (O::* f)(funcargs...), Args... args) {
        return Funk(new FunkFuncM<false, O, funcargs...>(obj, f, args...));
    }

    // Versions that assume the object to be threadsafe
    template <typename O, typename... funcargs, typename... Args>
    Funk funcM_fromThreadsafe(O* obj, double (O::* f)(funcargs...), Args... args) {
        return Funk(new FunkFuncM<true, O, funcargs...>(obj, f, args...));
    }
    template <typename O, typename... funcargs, typename... Args>
    Funk funcM_fromThreadsafe(shared_ptr<O> obj, double (O::* f)(funcargs...), Args... args) {
        return Funk(new FunkFuncM<true, O, funcargs...>(obj, f, args...));
    }

    //
    // Derived class that implements delta function
    //

    class FunkDelta: public FunkBase
    {
        public:
            FunkDelta(std::string arg, double pos, double width) : pos(pos), width(width)
            {
                arguments = vec(arg);
                this->set_singularity("v", pos, width);
            }

            double value(const std::vector<double> & data, size_t bindID)
            {
                double x = data[indices[bindID][0]];
                return exp(-pow(x-pos,2)/pow(width,2)/2)/sqrt(2*M_PI)/width;
            }

        private:
            double pos, width;
    };
    inline Funk delta(std::string arg, double pos, double width) { return Funk(new FunkDelta(arg, pos, width)); }

    //
    // Derived class that implements simple linear variable
    //

    class FunkVar: public FunkBase
    {
        public:
            FunkVar(std::string arg)
            {
                arguments = vec(arg);
            }

            double value(const std::vector<double> & data, size_t bindID)
            {
                return data[indices[bindID][0]];
            }
    };
    inline Funk var(std::string arg) { return Funk(new FunkVar(arg)); }


    //
    // Definition of FunkBase member functions
    //

    inline Funk FunkBase::set_singularity(std::string arg, Funk pos, Funk width)
    {
        singularities[arg].push_back(std::pair<Funk, Funk>(pos, width));
        return shared_from_this();
    };
    inline Funk FunkBase::set_singularity(std::string arg, double pos, Funk width)
    { return shared_from_this()->set_singularity(arg, cnst(pos), width); }
    inline Funk FunkBase::set_singularity(std::string arg, double pos, double width)
    { return shared_from_this()->set_singularity(arg, cnst(pos), cnst(width)); }
    inline Funk FunkBase::set_singularity(std::string arg, Funk pos, double width)
    { return shared_from_this()->set_singularity(arg, pos, cnst(width)); }

    inline void FunkBase::resolve(std::map<std::string, size_t> datamap, size_t & datalen, size_t bindID, std::map<std::string,size_t> &argmap)
    {
        // Resolve my dependencies
        auto it1 = arguments.begin();
        std::vector<size_t> tmp_indices;
        tmp_indices.resize(arguments.size());
        auto it2 = tmp_indices.begin();
        for (; it1 != arguments.end() && it2 != tmp_indices.end(); ++it1, ++it2 )
        {
            try
            {
                *it2 = datamap.at(*it1);
            }
            catch (std::out_of_range & e)
            {
                std::string msg = "FunkBase::resolve() encountered internal problem when resolving " + *it1 + ".\n";
                            msg+= " --- Actual arguments of object: " + args_string(arguments);
#ifdef GAMBIT_DIR
                Gambit::utils_error().raise(LOCAL_INFO, msg);
#else
                throw std::invalid_argument(msg);
#endif
            }
        }

        // Set indices
        if(indices.size() <= bindID)
        {
            indices.resize(bindID+1);
            // TODO: Throw error if problems are encountered
            //std::cout << "FATAL ERROR: bind() attempts to resolve dependencies of FunkBase" << std::endl;
            //std::cout << "object inconsistently." << std::endl;
            //std::cout << "Encountered while resolving: " << std::endl;
            //for (auto it = datamap.begin(); it != datamap.end(); it++)
            //{
            //    std::cout << "  " << it->first << std::endl;
            //}
            //exit(1);
        }
        indices[bindID] = tmp_indices;

        // Resolve other dependencies
        for (auto it = functions.begin(); it != functions.end(); ++it)
        {
            (*it)->resolve(datamap, datalen, bindID, argmap);
        }

    }

    template <typename... Args> inline bool FunkBase::assert_args(Args... args)
    {
        std::vector<std::vector<std::string>> list = vec<std::vector<std::string>>(args...);
        std::set<std::string> myargs(arguments.begin(), arguments.end());
        for ( auto it = list.begin(); it != list.end(); ++it )
        {
            std::set<std::string> theirargs(it->begin(), it->end());
            if ( myargs == theirargs )
                return true;
        }
        return false;

    }

    template <typename... Args> inline Funk FunkBase::set(std::string arg, Funk g, Args... args)
    {
        Funk f = shared_from_this();
        if ( std::find(arguments.begin(), arguments.end(), arg) != arguments.end() )
        {
            f = Funk(new FunkDerived(f, arg, g));
        }
        else
        {
            std::cout << "daFunk::FunkBase WARNING: Ignoring \"" << arg << "\" = function." << std::endl;
        }
        return f->set(args...);
    }

    template <typename... Args> inline Funk FunkBase::set(std::string arg, std::string arg1, Args... args)
        { return shared_from_this()->set(arg, var(arg1))->set(args...); }

    template <typename... Args> inline Funk FunkBase::set(std::string arg, double x, Args... args)
        { return shared_from_this()->set(arg, cnst(x))->set(args...); }

    template <> inline Funk FunkBase::set()
        { return shared_from_this(); }

    template <typename... Args> inline shared_ptr<FunkBound> FunkBase::bind(Args... argss)
    {
        size_t bindID;
        FunkBound::bindID_manager(bindID,true);
        std::map<std::string, size_t> datamap;
        size_t i;
        auto bound_arguments = vec<std::string>(argss...);
        datalen = bound_arguments.size();
        i = 0;
        for ( auto it = bound_arguments.begin(); it != bound_arguments.end(); ++it, ++i )
        {
            datamap[*it] = i;
        }
        std::map<std::string,size_t> argmap;
        if ( not args_match(arguments, bound_arguments) )
        {
            std::string msg = "FunkBase::bind() tries to resolve wrong arguments.\n";
                        msg+= " --- Arguments that are supposed to be bound: " + args_string(bound_arguments) + "\n";
                        msg+= " --- Actual arguments of object: " + args_string(arguments);
#ifdef GAMBIT_DIR
            Gambit::utils_error().raise(LOCAL_INFO, msg);
#else
            throw std::invalid_argument(msg);
#endif
        }
        this->resolve(datamap, datalen, bindID, argmap);
        return shared_ptr<FunkBound>(new FunkBound(shared_from_this(), datalen, bindID));
    }

    inline bool FunkBase::hasArg(std::string arg)
    {
        return ( std::find(arguments.begin(), arguments.end(), arg) != arguments.end() );
    }

    inline bool FunkBase::hasArgs()
    {
        return ( this->arguments.size() != 0 );
    }

    template <typename... Args> inline shared_ptr<FunkIntegrate_gsl1d> FunkBase::gsl_integration(Args... args)
    {
        return getIntegrate_gsl1d(shared_from_this(), args...);
    }

    inline Funk FunkBase::help()
    {
        std::cout << "Arguments:";
        for ( auto it = arguments.begin(); it != arguments.end(); it++ )
        {
            std::cout << " \"" << *it << "\"";
        }
        if ( arguments.size() == 0 )
            std::cout << " none";
        std::cout << std::endl;
        for ( auto it = singularities.begin() ; it != singularities.end(); ++it )
        {
            std::cout << "Singularities in " << it->first << ": " << it->second.size() << std::endl;
        }
        return shared_from_this();
    }

    inline PlainPtrs1 FunkBase::plain(std::string arg1)
    {
        void* ptr = new FunkPlain(shared_from_this(), arg1);
        return PlainPtrs1(&FunkPlain::plain1p, ptr);
    }
    inline PlainPtrs2 FunkBase::plain(std::string arg1, std::string arg2)
    {
        void* ptr = new FunkPlain(shared_from_this(), arg1, arg2);
        return PlainPtrs2(&FunkPlain::plain2p, ptr);
    }
    inline PlainPtrs3 FunkBase::plain(std::string arg1, std::string arg2, std::string arg3)
    {
        void* ptr = new FunkPlain(shared_from_this(), arg1, arg2, arg3);
        return PlainPtrs3(&FunkPlain::plain3p, ptr);
    }
    inline PlainPtrs4 FunkBase::plain(std::string arg1, std::string arg2, std::string arg3, std::string arg4)
    {
        void* ptr = new FunkPlain(shared_from_this(), arg1, arg2, arg3, arg4);
        return PlainPtrs4(&FunkPlain::plain4p, ptr);
    }

    template <typename T>
    inline PlainPtr1 FunkBase::plain(std::string arg1)
    {
        T::set(new FunkPlain(shared_from_this(), arg1));
        return &FunkPlain::plain1<T>;
    }
    template <typename T>
    inline PlainPtr2 FunkBase::plain(std::string arg1, std::string arg2)
    {
        T::set(new FunkPlain(shared_from_this(), arg1, arg2));
        return &FunkPlain::plain2<T>;
    }
    template <typename T>
    inline PlainPtr3 FunkBase::plain(std::string arg1, std::string arg2, std::string arg3)
    {
        T::set(new FunkPlain(shared_from_this(), arg1, arg2, arg3));
        return &FunkPlain::plain3<T>;
    }
    template <typename T>
    inline PlainPtr4 FunkBase::plain(std::string arg1, std::string arg2, std::string arg3, std::string arg4)
    {
        T::set(new FunkPlain(shared_from_this(), arg1, arg2, arg3, arg4));
        return &FunkPlain::plain4<T>;
    }


    //
    // Mathematical functions from cmath
    //

    // Unary minus sign
    class FunkMath_umin: public FunkBase
    {
        public:
            FunkMath_umin(Funk f)
            {
                functions = vec(f);
                singularities = f->getSingl();
                arguments = f->getArgs();
            }
            double value(const std::vector<double> & data, size_t bindID)
            {
                return -(functions[0]->value(data, bindID));
            }
    };
    inline Funk operator - (Funk f) { return Funk(new FunkMath_umin(f)); }

    // Unary operations
#define MATH_OPERATION(OPERATION)                                                                         \
    class FunkMath_##OPERATION: public FunkBase                                                           \
    {                                                                                                     \
        public:                                                                                           \
            FunkMath_##OPERATION(Funk f)                                                                  \
            {                                                                                             \
                functions = vec(f);                                                                       \
                arguments = f->getArgs();                                                                 \
                singularities = f->getSingl();                                                            \
            }                                                                                             \
            double value(const std::vector<double> & data, size_t bindID)                                       \
            {                                                                                             \
                return OPERATION(functions[0]->value(data, bindID));                                      \
            }                                                                                             \
    };                                                                                                    \
    inline Funk OPERATION (Funk f) { return Funk(new FunkMath_##OPERATION(f)); }
    MATH_OPERATION(cos)
    MATH_OPERATION(sin)
    MATH_OPERATION(tan)
    MATH_OPERATION(acos)
    MATH_OPERATION(asin)
    MATH_OPERATION(atan)
    MATH_OPERATION(cosh)
    MATH_OPERATION(sinh)
    MATH_OPERATION(tanh)
    MATH_OPERATION(acosh)
    MATH_OPERATION(asinh)
    MATH_OPERATION(atanh)
    MATH_OPERATION(exp)
    MATH_OPERATION(log)
    MATH_OPERATION(log10)
    MATH_OPERATION(sqrt)
    MATH_OPERATION(fabs)
#undef MATH_OPERATION

    // Standard binary operations
#define MATH_OPERATION(OPERATION, SYMBOL)                                                                 \
    class FunkMath_##OPERATION: public FunkBase                                                           \
    {                                                                                                     \
        public:                                                                                           \
            FunkMath_##OPERATION(Funk f1, Funk f2)                                                        \
            {                                                                                             \
                functions = vec(f1, f2); \
                arguments = joinArgs(f1->getArgs(), f2->getArgs()); \
                singularities = joinSingl(f1->getSingl(), f2->getSingl());\
            }                                                                                             \
            FunkMath_##OPERATION(double x, Funk f2)                 \
            {                                                                                             \
                auto f1 = cnst(x); \
                functions = vec(f1, f2); \
                arguments = joinArgs(f1->getArgs(), f2->getArgs()); \
                singularities = joinSingl(f1->getSingl(), f2->getSingl());\
            }                                                                                             \
            FunkMath_##OPERATION(Funk f1, double x)              \
            {                                                                                             \
                auto f2 = cnst(x); \
                functions = vec(f1, f2); \
                arguments = joinArgs(f1->getArgs(), f2->getArgs()); \
                singularities = joinSingl(f1->getSingl(), f2->getSingl());\
            }                                                                                             \
            double value(const std::vector<double> & data, size_t bindID)                                 \
            {                                                                                             \
                return functions[0]->value(data, bindID) SYMBOL functions[1]->value(data, bindID);        \
            }                                                                                             \
    };                                                                                                    \
    inline Funk operator SYMBOL (Funk f1, Funk f2) { return Funk(new FunkMath_##OPERATION(f1, f2)); }     \
    inline Funk operator SYMBOL (double x, Funk f) { return Funk(new FunkMath_##OPERATION(x, f)); }       \
    inline Funk operator SYMBOL (Funk f, double x) { return Funk(new FunkMath_##OPERATION(f, x)); }
    MATH_OPERATION(Sum,+)
    MATH_OPERATION(Mul,*)
    MATH_OPERATION(Div,/)
    MATH_OPERATION(Dif,-)
#undef MATH_OPERATION

    // More binary operations
#define MATH_OPERATION(OPERATION)                                                                         \
    class FunkMath_##OPERATION: public FunkBase                                                           \
    {                                                                                                     \
        public:                                                                                           \
            FunkMath_##OPERATION(Funk f1, Funk f2)                                                        \
            {                                                                                             \
                functions = vec(f1, f2);                                                                  \
                arguments = joinArgs(f1->getArgs(), f2->getArgs());                                       \
                singularities = joinSingl(f1->getSingl(), f2->getSingl());                                \
            }                                                                                             \
            FunkMath_##OPERATION(double x, Funk f2)                                                       \
            {                                                                                             \
                auto f1 = cnst(x);                                                                        \
                functions = vec(f1, f2);                                                                  \
                arguments = joinArgs(f1->getArgs(), f2->getArgs());                                       \
                singularities = joinSingl(f1->getSingl(), f2->getSingl());                                \
            }                                                                                             \
            FunkMath_##OPERATION(Funk f1, double x)                                                       \
            {                                                                                             \
                auto f2 = cnst(x);                                                                        \
                functions = vec(f1, f2);                                                                  \
                arguments = joinArgs(f1->getArgs(), f2->getArgs());                                       \
                singularities = joinSingl(f1->getSingl(), f2->getSingl());                                \
            }                                                                                             \
            double value(const std::vector<double> & data, size_t bindID)                                 \
            {                                                                                             \
                return OPERATION(functions[0]->value(data, bindID), functions[1]->value(data, bindID));   \
            }                                                                                             \
    };                                                                                                    \
    inline Funk OPERATION (Funk f1, Funk f2) { return Funk(new FunkMath_##OPERATION(f1, f2)); }           \
    inline Funk OPERATION (double x, Funk f) { return Funk(new FunkMath_##OPERATION(x, f)); }             \
    inline Funk OPERATION (Funk f, double x) { return Funk(new FunkMath_##OPERATION(f, x)); }
    MATH_OPERATION(pow)
    MATH_OPERATION(fmin)
    MATH_OPERATION(fmax)
#undef MATH_OPERATION

    ////////////////////////////////////////
    // *** End of core implementation ***
    ////////////////////////////////////////



    ////////////////////////////////////////
    //        *** Extensions ***
    ////////////////////////////////////////


    //
    // Derived class: 1dim linear or logarithmic interpolation
    //

    class FunkInterp : public FunkBase
    {
        public:
            FunkInterp(Funk f, std::vector<double> & Xgrid, std::vector<double> & Ygrid, std::string mode = "lin")
            {
                setup(f, Xgrid, Ygrid, mode);
            }
            FunkInterp(std::string arg, std::vector<double> & Xgrid, std::vector<double> & Ygrid, std::string mode = "lin")
            {
                setup(var(arg), Xgrid, Ygrid, mode);
            }
            FunkInterp(double x, std::vector<double> & Xgrid, std::vector<double> & Ygrid, std::string mode = "lin")
            {
                setup(cnst(x), Xgrid, Ygrid, mode);
            }

            double value(const std::vector<double> & data, size_t bindID)
            {
                functions[0]->value(data, bindID);
                return (this->*ptr)(data[indices[bindID][0]]);
            }

        private:
            void setup(Funk f, std::vector<double> & Xgrid, std::vector<double> & Ygrid, std::string mode)
            {
                // TODO: Catch invalid setup
                functions = vec(f);
                singularities = f->getSingl();
                arguments = f->getArgs();
                this->Xgrid = Xgrid;
                this->Ygrid = Ygrid;
                if ( mode == "lin" ) this->ptr = &FunkInterp::linearInterp;
                else if ( mode == "log" ) this->ptr = &FunkInterp::logInterp;
            }

            double logInterp(double x)
            {
                // Linear interpolation in log-log space
                int i = 0; int imax = Xgrid.size() - 1;
                if (x<Xgrid[0] or x>Xgrid[imax]) return 0;
                for (; i < imax; i++) {if (Xgrid[i] > x) break;};
                double x0 = Xgrid[i-1];
                double x1 = Xgrid[i];
                double y0 = Ygrid[i-1];
                double y1 = Ygrid[i];
                return y0 * std::exp(std::log(y1/y0) * std::log(x/x0) / std::log(x1/x0));
            }

            double linearInterp(double x)
            {
                // Linear interpolation in lin-lin space
                int i = 0; int imax = Xgrid.size() - 1;
                if (x<Xgrid[0] or x>Xgrid[imax]) return 0;
                for (; i < imax; i++) {if (Xgrid[i] > x) break;};
                double x0 = Xgrid[i-1];
                double x1 = Xgrid[i];
                double y0 = Ygrid[i-1];
                double y1 = Ygrid[i];
                return y0 + (x-x0)/(x1-x0)*(y1-y0);
            }

            double(FunkInterp::*ptr)(double);
            std::vector<double> Xgrid;
            std::vector<double> Ygrid;
            std::string mode;
    };
    template <typename T> inline shared_ptr<FunkInterp> interp(T f, std::vector<double> x, std::vector<double> y) { return shared_ptr<FunkInterp>(new FunkInterp(f, x, y)); }


    //
    // Basic if..else clause
    //

    class FunkIfElse: public FunkBase
    {
        public:
            FunkIfElse(Funk f, Funk g, Funk h)
            {
                functions = vec(f, g, h);
                singularities = joinSingl(joinSingl(f->getSingl(), g->getSingl()), h->getSingl());
                arguments = joinArgs(joinArgs(f->getArgs(), g->getArgs()), h->getArgs());
            }
            double value(const std::vector<double> & data, size_t bindID)
            {
              if ( functions[0]->value(data,bindID) >= 0. )
                return functions[1]->value(data,bindID);
              else
                return functions[2]->value(data,bindID);
            }
    };
    inline Funk ifelse(Funk f, Funk g, Funk h) { return Funk(new FunkIfElse(f, g, h)); }
    inline Funk ifelse(Funk f, double g, Funk h) { return Funk(new FunkIfElse(f, cnst(g), h)); }
    inline Funk ifelse(Funk f, double g, double h) { return Funk(new FunkIfElse(f, cnst(g), cnst(h))); }
    inline Funk ifelse(Funk f, Funk g, double h) { return Funk(new FunkIfElse(f, g, cnst(h))); }


    //
    // Throw errors when called
    //

    class ThrowError: public FunkBase
    {
        public:
            ThrowError(std::string msg) : msg(msg)
            {
            }
            double value(const std::vector<double> & data, size_t bindID)
            {
              (void)bindID;
              (void)data;
#ifdef GAMBIT_DIR
              if ( omp_get_level() == 0 )  // Outside of OMP blocks
              {
                  Gambit::utils_error().raise(LOCAL_INFO, "daFunk::ThrowError says: " + msg);
              }
              else  // Inside of OMP blocks
              {
                  Gambit::piped_errors.request(LOCAL_INFO, "daFunk::ThrowError says: " + msg);
              }
#else
              throw std::invalid_argument("daFunk::ThrowError says: " + msg);
#endif
              return 0;
            }

        private:
            std::string msg;  // Error message to throw when function is called
    };
    inline Funk throwError(std::string msg) { return Funk(new ThrowError(msg)); }

#ifdef GAMBIT_DIR
    class RaiseInvalidPoint: public FunkBase
    {
        public:
            RaiseInvalidPoint(std::string msg) : msg(msg)
            {
            }
            double value(const std::vector<double> & data, size_t bindID)
            {
              (void)bindID;
              (void)data;
              if ( omp_get_level() == 0 )  // Outside of OMP blocks
              {
                  Gambit::utils_warning().raise(LOCAL_INFO, "daFunk::RaiseInvalidPoint says: " + msg);
                  Gambit::invalid_point().raise("daFunk::RaiseInvalidPoint says: " + msg);
              }
              else  // Inside OMP blocks
              {
                  Gambit::utils_warning().raise(LOCAL_INFO, "daFunk::RaisePipedInvalidPoint says: " + msg);
                  Gambit::piped_invalid_point.request("daFunk::RaisePipedInvalidPoint says: " + msg);
              }
              return 0;
            }

        private:
            std::string msg;  // Error message to throw when function is called
    };
    inline Funk raiseInvalidPoint(std::string msg) { return Funk(new RaiseInvalidPoint(msg)); }
#endif


    //
    // Prints message when called
    //

    class Bottle: public FunkBase
    {
        public:
            Bottle(Funk f, std::string msg) : msg(msg)
            {
                functions = vec(f);
                singularities = f->getSingl();
                arguments = f->getArgs();
            }
            double value(const std::vector<double> & data, size_t bindID)
            {
              std::cout << "daFunk::Message says:\n" << msg << std::endl;
              return functions[0]->value(data, bindID);
            }

        private:
            std::string msg;  // Message in a bottle.  Ha!
    };
    //inline Funk print(std::string msg) { return Funk(new Bottle(msg)); }
    inline Funk FunkBase::print(std::string msg)
    { return Funk(new Bottle(shared_from_this(), msg)); };


    //
    // GSL integration
    //

    class FunkIntegrate_gsl1d: public FunkBase, public gsl_function
    {
        public:
            FunkIntegrate_gsl1d(Funk f0, std::string arg, Funk f1, Funk f2)
            {
                setup(f0, arg, f1, f2);
            }
            FunkIntegrate_gsl1d(Funk f0, std::string arg, double x, Funk f)
            {
                setup(f0, arg, cnst(x), f);
            }
            FunkIntegrate_gsl1d(Funk f0, std::string arg, double x, double y)
            {
                setup(f0, arg, cnst(x), cnst(y));
            }
            FunkIntegrate_gsl1d(Funk f0, std::string arg, Funk f, double x)
            {
                setup(f0, arg, f, cnst(x));
            }
            FunkIntegrate_gsl1d(Funk f0, std::string arg, std::string x, Funk f)
            {
                setup(f0, arg, var(x), f);
            }
            FunkIntegrate_gsl1d(Funk f0, std::string arg, std::string x, std::string y)
            {
                setup(f0, arg, var(x), var(y));
            }
            FunkIntegrate_gsl1d(Funk f0, std::string arg, Funk f, std::string x)
            {
                setup(f0, arg, f, var(x));
            }
            FunkIntegrate_gsl1d(Funk f0, std::string arg, std::string x, double y)
            {
                setup(f0, arg, var(x), cnst(y));
            }
            FunkIntegrate_gsl1d(Funk f0, std::string arg, double y, std::string x)
            {
                setup(f0, arg, cnst(y), var(x));
            }

            void resolve(std::map<std::string, size_t> datamap, size_t & datalen, size_t bindID, std::map<std::string,size_t> &argmap)
            {
                functions[1]->resolve(datamap, datalen, bindID, argmap);  // Resolve boundary 0
                functions[2]->resolve(datamap, datalen, bindID, argmap);  // Resolve boundary 1

                // Set indices
                if(index.size() <= bindID)
                {
                    index.resize(bindID+1);
                    // TODO: Throw error if problems are encountered
                    //std::cout << "FATAL ERROR: bind() attempts to resolve dependencies of FunkIntegrate_gsl1d" << std::endl;
                    //std::cout << "object inconsistently." << std::endl;
                    //std::cout << "Encountered while resolving " << arg << " and:" << std::endl;
                    //for (auto it = datamap.begin(); it != datamap.end(); it++)
                    //{
                    //    std::cout << "  " << it->first << std::endl;
                    //}
                    //exit(1);
                }
                if ( argmap.find(arg) == argmap.end() )
                {
                    if(datamap.find(arg) == datamap.end())
                    {
                        index[bindID] = datalen;
                        argmap[arg]   = datalen;
                        ++datalen;
                    }
                    else
                    {
                        index[bindID] = datamap[arg];
                    }
                }
                else
                {
                    index[bindID] = argmap[arg];
                }
                datamap[arg]  = index[bindID];
                functions[0]->resolve(datamap, datalen, bindID, argmap);
                for ( auto it = my_singularities.begin(); it != my_singularities.end(); ++it )
                {
                    it->first->resolve(datamap, datalen, bindID, argmap);
                    it->second->resolve(datamap, datalen, bindID, argmap);
                }
            }

            ~FunkIntegrate_gsl1d()
            {
                gsl_integration_workspace_free(gsl_workspace);
            }

            shared_ptr<FunkIntegrate_gsl1d> set_epsrel(double epsrel)
            { this->epsrel = epsrel; return static_pointer_cast<FunkIntegrate_gsl1d>(this->FunkIntegrate_gsl1d::shared_from_this()); }
            shared_ptr<FunkIntegrate_gsl1d> set_epsabs(double epsabs)
            { this->epsabs = epsabs; return static_pointer_cast<FunkIntegrate_gsl1d>(this->shared_from_this()); }
            shared_ptr<FunkIntegrate_gsl1d> set_limit(size_t limit)
            { this->limit = limit; return static_pointer_cast<FunkIntegrate_gsl1d>(this->shared_from_this()); }
            shared_ptr<FunkIntegrate_gsl1d> set_singularity_factor(double f)
            { this->singl_factor = f; return static_pointer_cast<FunkIntegrate_gsl1d>(this->shared_from_this()); }
            shared_ptr<FunkIntegrate_gsl1d> set_use_log_fallback(bool flag)
            { this->use_log_fallback = flag; return static_pointer_cast<FunkIntegrate_gsl1d>(this->shared_from_this()); }

            double value(const std::vector<double> & data, size_t bindID)
            {
                double result;
                #pragma omp critical(FunkIntegrate_gsl1d_integration)
                {
                    local_data = data;
                    local_bindID = bindID;
                    double error;
                    function=&FunkIntegrate_gsl1d::invoke;
                    params=this;
                    double x0 = functions[1]->value(data, bindID);
                    double x1 = functions[2]->value(data, bindID);
                    gsl_set_error_handler_off();
                    int status = 0;
                    if ( my_singularities.size() == 0 )
                    {
                        status = gsl_integration_qags(this, x0, x1, epsabs, epsrel, limit, gsl_workspace, &result, &error);
                    }
                    else
                    {
                        double s = 0;
                        std::vector<double> ranges;
                        ranges.push_back(x0);
                        ranges.push_back(x1);
                        for ( auto it = my_singularities.begin(); it != my_singularities.end(); ++it )
                        {
                            double mean = it->first->value(data, bindID);
                            double sigma = it->second->value(data, bindID);
                            double z0 = mean - singl_factor*sigma;
                            double z1 = mean + singl_factor*sigma;
                            if ( z0 == z1 )
                                std::cout << "daFunk::FunkBase WARNING: Singularity width is beyond machine precision." << std::endl;
                            if ( z0 > x0 and z0 < x1 ) ranges.push_back(z0);
                            if ( z1 > x0 and z1 < x1 ) ranges.push_back(z1);
                        }
                        std::sort(ranges.begin(), ranges.end());
                        for ( auto it = ranges.begin(); it != ranges.end()-1; ++it )
                        {
                            status = gsl_integration_qags(this, *it, *(it+1), epsabs, epsrel, limit, gsl_workspace, &result, &error);
                            s += result;
                            if (status) break;
                        }
                        result = s;
                    }
                    if (status and this->use_log_fallback)
                    {
                        // The last resort: A cheap integration on log grid, linear interpolation
                        const double N = 300;
                        std::vector<double> Xgrid = 
                            logspace(std::log10(x0), std::log10(x1), N);
                        double sum = 0, y0, y1, dx;
                        local_data[index[bindID]] = Xgrid[0];
                        y0 = functions[0]->value(local_data, bindID);
                        for (size_t i = 0; i<N-1; i++)
                        {
                            local_data[index[bindID]] = Xgrid[i+1];
                            y1 = functions[0]->value(local_data, bindID);
                            dx = Xgrid[i+1]-Xgrid[i];
                            sum += dx*(y0+y1)/2;
                            y0 = y1;
                        }
                        result = sum;
                    }
                    // TODO: Implement flags to optionally throw an error
                    if (status and not this->use_log_fallback)
                    {
                        std::cerr << "daFunk::FunkIntegrate_gsl1d WARNING: " << gsl_strerror(status) << std::endl;
                        std::cerr << "Attempt to integrate from " << x0 << " to " << x1 << std::endl;
                        std::cerr << "Attempt to integrate from " << x0 << " to " << x1 << std::endl;
                        std::cerr << "Details about the integrand:" << std::endl;
                        functions[0]->help();
//                        std::cout << "Dumping integrand:" << std::endl;
//                        for ( double x = x0; x <= x1; x = (x0>0) ? x*1.01 : x+(x1-x0)/1000)
//                            std::cerr << "  " << x << " " << invoke(x, this) << std::endl;
                        std::cerr << "Returning zero." << std::endl;
                        result = 0.;
                    }
                }
                return result;
            }

        private:
            void setup(Funk f0, std::string arg, Funk f1, Funk f2)
            {
                this->functions = vec(f0, f1, f2);

                singularities = joinSingl(f1->getSingl(), f2->getSingl());
                if ( f0->getSingl().find(arg) != f0->getSingl().end() )
                    my_singularities = f0->getSingl()[arg];
                Singularities tmp_singl = f0->getSingl();
                tmp_singl.erase(arg);
                singularities = joinSingl(singularities, tmp_singl);

                arguments = joinArgs(eraseArg(f0->getArgs(), arg), joinArgs(f1->getArgs(), f2->getArgs()));
                gsl_workspace = gsl_integration_workspace_alloc (100000);

                this->arg = arg;
                limit = 100;
                epsrel = 1e-2;
                epsabs = 1e-2;
                use_log_fallback = false;
                singl_factor = 4;
            }

            // Static member function that invokes integrand
            static double invoke(double x, void *params) {
                FunkIntegrate_gsl1d * ptr = static_cast<FunkIntegrate_gsl1d*>(params);
                ptr->local_data[ptr->index[ptr->local_bindID]] = x;
                return ptr->functions[0]->value(ptr->local_data, ptr->local_bindID);
            }

            // Required for rewiring input parameters
            std::vector<double> local_data;
            size_t local_bindID;
            std::vector<std::pair<Funk, Funk>> my_singularities;

            // Integration range and function pointer
            std::string arg;

            // GSL workspace and parameters
            gsl_integration_workspace * gsl_workspace;
            size_t limit;
            std::vector<size_t> index;
            double epsrel;
            double epsabs;
            bool use_log_fallback;

            double singl_factor;
    };

    // Standard behaviour
    template <typename T1, typename T2>
    inline shared_ptr<FunkIntegrate_gsl1d> getIntegrate_gsl1d(Funk fptr, std::string arg, T1 x1, T2 x2) { return shared_ptr<FunkIntegrate_gsl1d>(new FunkIntegrate_gsl1d(fptr, arg, x1, x2)); }

    //
    // Helper function for producing singularity-augmented x-grids
    //

    inline std::vector<double> augmentSingl(const std::vector<double> & xgrid, Funk f, int N = 100, double sigma = 3)
    {
        std::vector<double> result = xgrid;
        double xmin = result.front();
        double xmax = result.back();

        if ( f->getNArgs() != 1 )
        {
            std::string msg = "augment_with_singularities(): takes only functions with one argument.\n";
                        msg+= "  --- Actual arguments are: " + args_string(f->getArgs());
#ifdef GAMBIT_DIR
            Gambit::utils_error().raise(LOCAL_INFO, msg);
#else
            throw std::invalid_argument(msg);
#endif
        }

        std::string arg = f->getArgs()[0];
        Singularities singlsMap = f->getSingl();

        if ( singlsMap.find(arg) != singlsMap.end() )
        {
            auto singls = singlsMap.at(arg);
            for (auto it = singls.begin(); it != singls.end(); it ++)
            {
                double position= it->first->bind()->eval();
                double width = it->second->bind()->eval();
                std::vector<double> singlgrid = linspace(std::max(position-width*sigma, xmin), std::min(position+width*sigma, xmax), N);
                result.insert(result.end(), singlgrid.begin(), singlgrid.end());
            }
            std::sort(result.begin(), result.end());
        }

        return result;
    }
}


#endif  // __DAFUNK_HPP__
