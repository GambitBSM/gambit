//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class mathematica_variable, needed to overload
///  constructor and assignment operators to send
///  messages throught WSTP
///
///  ***********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2016 Nov
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Dec
///
///  ***********************************************

#ifndef __mathematica_variable_hpp__
#define __mathematica_variable_hpp__

#include "gambit/Elements/ini_catch.hpp"
#include "gambit/Backends/backend_singleton.hpp"
#include "gambit/cmake/cmake_variables.hpp"
#include <boost/algorithm/string/replace.hpp>

#ifdef HAVE_MATHEMATICA
 #include "gambit/Backends/mathematica_helpers.hpp"
 #include MATHEMATICA_WSTP_H
#endif


namespace Gambit
{

  // Class mathematica_variable
  template <typename TYPE>
  class mathematica_variable
  {

    private:
      #ifdef HAVE_MATHEMATICA
        WSLINK _WSlink;
      #endif
      TYPE _var;
      str _symbol;

    public:

      // Constructor
      mathematica_variable(const str& be, const str& ver, const str& symbol) :  _symbol(symbol)
      {
        #ifdef HAVE_MATHEMATICA

          using namespace Backends;

          try
          {
            /* Extract the backend WSLINK pointer from the backendInfo object */
            if (backendInfo().works.at(be+ver))
            {
              _WSlink = backendInfo().loaded_mathematica_backends.at(be+ver);
            }
            else
            {
              _WSlink = (WSLINK)0;
              return;
            }

            /* If TYPE is a numeric type, send N first */
            if(boost::is_same<TYPE, int>::value or
               boost::is_same<TYPE, float>::value or
               boost::is_same<TYPE, double>::value)
              if(!WSPutFunction(_WSlink, "N", 1))
              {
                math_error(_WSlink, LOCAL_INFO, "Error sending packet through WSTP");
                return ;
              }

            /* Send the variable symbol, preceeded by functions to parse non-alphanumerical chars */
            boost::replace_all(_symbol, "\\[", "\\\\[");
            if(!WSPutFunction(_WSlink, "ToExpression",1) or
               !WSPutString(_WSlink, _symbol.c_str()))
            {
              math_error(_WSlink, LOCAL_INFO, "Error sending packet through WSTP");
              return ;
            }

            /* Mark the end of the message */
            if(!WSEndPacket(_WSlink))
            {
              math_error(_WSlink, LOCAL_INFO, "Error sending packet through WSTP");
              return ;
            }

            /* Wait to receive a packet from the kernel */
            int pkt;
            while( (pkt = WSNextPacket(_WSlink), pkt) && pkt != RETURNPKT)
            {
              WSNewPacket(_WSlink);
              if (WSError(_WSlink))
              {
                math_error(_WSlink, LOCAL_INFO, "Error reading packet from WSTP");
                return ;
              }
            }

            /* Read the received packet into the return value, unless it's void */
            if(!boost::is_same<TYPE, void>::value)
            {
              if(!boost::is_same<TYPE, int>::value and
                 !boost::is_same<TYPE, float>::value and
                 !boost::is_same<TYPE, double>::value and
                 !boost::is_same<TYPE, bool>::value and
                 !boost::is_same<TYPE, char>::value and
                 !boost::is_same<TYPE, str>::value)
                backend_warning().raise(LOCAL_INFO, "Error, WSTP type not recognised");
              else if(!WSGetVariable(_WSlink, &_var))
                math_error(_WSlink, LOCAL_INFO, "Error reading packet from WSTP");
            }

          }
          catch (std::exception& e) { ini_catch(e); }

        #else

          // Avoid compiler warnings
          (void)be;
          (void)ver;

        #endif

      }


      // Assignment operator with TYPE
      mathematica_variable& operator=(const TYPE& val)
      {
        #ifdef HAVE_MATHEMATICA

          using namespace Backends;

          if (_WSlink == (WSLINK)0) backend_error().raise(LOCAL_INFO, "Backend is missing.");

          // Clear the variable that is to be replaced
          if(!WSPutFunction(_WSlink, "Clear", 1) or
             !WSPutFunction(_WSlink, "StringDrop", 2) or
             !WSPutFunction(_WSlink, "StringDrop", 2) or
             !WSPutFunction(_WSlink, "ToString", 1) or
             !WSPutFunction(_WSlink, "ToExpression", 3) or
             !WSPutString(_WSlink, _symbol.c_str()) or
             !WSPutSymbol(_WSlink, "StandardForm") or
             !WSPutSymbol(_WSlink, "Hold") or
             !WSPutInteger(_WSlink, 5) or
             !WSPutInteger(_WSlink, -1) )
          {
            math_error(_WSlink, LOCAL_INFO, "Error sending packet through WSTP");
            return *this;
          }

          // Mark the end of the message
          if(!WSEndPacket(_WSlink))
          {
            math_error(_WSlink, LOCAL_INFO, "Error sending packet through WSTP");
            return *this;
          }

          // Wait to receive a packet from the kernel
          int pkt;
          while( (pkt = WSNextPacket(_WSlink), pkt) && pkt != RETURNPKT)
          {
            WSNewPacket(_WSlink);
            if (WSError(_WSlink))
            {
              math_error(_WSlink, LOCAL_INFO, "Error reading packet from WSTP");
              return *this;
            }
          }
          // Discard it
          WSNewPacket(_WSlink);

          // Send the expression SYMBOL = val
          std::stringstream ss;
          ss << _symbol << " = " << val;
          if(!WSPutFunction(_WSlink, "ToExpression", 1) or
             !WSPutString(_WSlink, ss.str().c_str()))
          {
            math_error(_WSlink, LOCAL_INFO, "Error sending packet through WSTP");
            return *this;
          }

          // Mark the end of the message
          if(!WSEndPacket(_WSlink))
          {
            math_error(_WSlink, LOCAL_INFO, "Error sending packet through WSTP");
            return *this;
          }

          // Wait to receive a packet from the kernel
          while( (pkt = WSNextPacket(_WSlink), pkt) && pkt != RETURNPKT)
          {
            WSNewPacket(_WSlink);
            if (WSError(_WSlink))
            {
              math_error(_WSlink, LOCAL_INFO, "Error reading packet from WSTP");
              return *this;
            }
          }

          // Read the received packet into the return value, unless it's void
          if(!boost::is_same<TYPE, void>::value)
          {
            if(!boost::is_same<TYPE, int>::value and
               !boost::is_same<TYPE, float>::value and
               !boost::is_same<TYPE, double>::value and
               !boost::is_same<TYPE, bool>::value and
               !boost::is_same<TYPE, char>::value and
               !boost::is_same<TYPE, str>::value)
              backend_warning().raise(LOCAL_INFO, "Error, WSTP type not recognised");
            else if(!WSGetVariable(_WSlink, &_var))
            {
              math_error(_WSlink, LOCAL_INFO, "Error reading packet from WSTP");
              return *this;
            }
          }

        #else

          backend_error().raise(LOCAL_INFO, "Attempted to assign a C++ type to a mathematica_variable without Mathematica.");

        #endif

        _var = val;

        return *this;

      }


      // Cast operator for type TYPE
      operator TYPE const()
      {
        #ifdef HAVE_MATHEMATICA

          using namespace Backends;

          if (_WSlink == (WSLINK)0) backend_error().raise(LOCAL_INFO, "Backend is missing.");

          try
          {
            /* If TYPE is a numeric type, send N first */
            if(boost::is_same<TYPE, int>::value or
               boost::is_same<TYPE, float>::value or
               boost::is_same<TYPE, double>::value)
              if(!WSPutFunction(_WSlink, "N", 1))
              {
                math_error(_WSlink, LOCAL_INFO, "Error sending packet through WSTP");
                return _var;
              }

            /* Send the variable symbol */
            if(!WSPutFunction(_WSlink, "ToExpression", 1) or
               !WSPutString(_WSlink, _symbol.c_str()))
            {
              math_error(_WSlink, LOCAL_INFO, "Error sending packet through WSTP");
              return _var;
            }

            /* Mark the end of the message */
            if(!WSEndPacket(_WSlink))
            {
              math_error(_WSlink, LOCAL_INFO, "Error sending packet through WSTP");
              return _var;
            }

            /* Wait to receive a packet from the kernel */
            int pkt;
            while( (pkt = WSNextPacket(_WSlink), pkt) && pkt != RETURNPKT)
            {
              WSNewPacket(_WSlink);
              if (WSError(_WSlink))
              {
                math_error(_WSlink, LOCAL_INFO, "Error reading packet from WSTP");
                return _var;
              }
            }

            /* Read the received packet into the return value, unless it's void */
            if(!boost::is_same<TYPE, void>::value)
            {
              if(!boost::is_same<TYPE, int>::value and
                 !boost::is_same<TYPE, float>::value and
                 !boost::is_same<TYPE, double>::value and
                 !boost::is_same<TYPE, bool>::value and
                 !boost::is_same<TYPE, char>::value and
                 !boost::is_same<TYPE, str>::value)
                backend_warning().raise(LOCAL_INFO, "Error, WSTP type nor recognised");
              else if(!WSGetVariable(_WSlink, &_var))
                math_error(_WSlink, LOCAL_INFO, "Error reading packet from WSTP");

            }
          }
          catch (std::exception &e) { ini_catch(e); }

          return _var;

        #else

          backend_error().raise(LOCAL_INFO, "Attempted to assign a C++ type to a mathematica_variable without Mathematica.");

        #endif

        return _var;
      }

  };

}

#endif /* __mathematica_variable_hpp__ */
