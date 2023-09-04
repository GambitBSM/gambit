dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([softsusy],[3.5.1],[softsusy@projects.hepforge.org],[softsusy])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_AUX_DIR([Config])
AC_CONFIG_HEADERS([Config/config.h])
AC_CONFIG_MACRO_DIR([m4])

dnl Put default fortran compiler for this variable
# F77=gfortran
dnl === disable debug symbols by default =====
if test "x$CXXFLAGS" = "x"; then
    CXXFLAGS="-O2 -Wall"
fi
if test "x$FFLAGS" = "x"; then
    FFLAGS="-O2 -Wall"
fi
dnl ==========================================

AC_LANG(C++)

AM_INIT_AUTOMAKE([1.9 foreign])
dnl Checks for programs.
AC_PROG_CXX

if test x"$CXX" = x; then
 AC_MSG_ERROR([could not find C++ compiler])
fi

AC_PROG_INSTALL
AC_PROG_MAKE_SET

## needed for twoloophiggs
AC_PROG_F77
AC_F77_LIBRARY_LDFLAGS
##

## If you want shared libraries, configure with --enable-shared
AC_PROG_LIBTOOL

AC_ARG_ENABLE([three-loop-rge-compilation], 
               AC_HELP_STRING([--enable-three-loop-rge-compilation],[Compile three-loop RGEs]), 
 	      AC_DEFINE([COMPILE_THREE_LOOP_RGE],[1],[Complile 3-loop RGE]),[])

AC_ARG_ENABLE([full-susy-threshold-compilation], 
               AC_HELP_STRING([--enable-full-susy-threshold-compilation],[Compile two-loop SUSY thresholds to the third generation fermionic Yukawa couplings and the strong gauge coupling]),
             [AC_DEFINE([COMPILE_FULL_SUSY_THRESHOLD],[1],[Compile leading two-loop SUSY threshold corrections to fermionic third generation Yukawa couplings]),
              case "${enableval}" in
              yes) full_susy_threshold_compilation=true ;;
              no)  full_susy_threshold_compilation=false ;;
              *) AC_MSG_ERROR([bad value ${enableval} for --enable-full_susy_threshold_compilation]) ;;
              esac],[full_susy_threshold_compilation=false])

AM_CONDITIONAL(COMPILE_FULL_SUSY_THRESHOLD, [test x$full_susy_threshold_compilation = xtrue])

AC_ARG_ENABLE([looptools], 
               AC_HELP_STRING([--enable-looptools],[Looptools evaluation of Pasarino-Veltman functions]),
             [AC_DEFINE([LOOPTOOLS],[1],[Looptools evaluation of Pasarino-Veltman functions]),
              case "${enableval}" in
              yes) looptools_compilation=true ;;
              no)  looptools_compilation=false ;;
              *) AC_MSG_ERROR([bad value ${enableval} for --enable-looptools]) ;;
              esac],[looptools_compilation=false])

AM_CONDITIONAL(LOOPTOOLS, [test x$looptools_compilation = xtrue])

AC_ARG_ENABLE([debug], 
               AC_HELP_STRING([--enable-debug],[enables debug printing in two-loop threshold corrections]), 
 	      AC_DEFINE([DEBUG],[1],[Threshold correction debugging output]),[])

#Autogen
#AG_PATH_AUTOOPTS([5.17], [], [AC_MSG_ERROR([No suitable version of AutoGen could be found])])

# GiNaC/cln for two-loop decoupling corrections
if test x"$enable_full_susy_threshold_compilation" = x"yes"; then
 PKG_CHECK_MODULES([CLN], cln >= 1.3.1)  
 PKG_CHECK_MODULES([GINAC], ginac >= 1.3.5)  

 LIBS="$LIBS $CLN_LIBS $GINAC_LIBS"
 CPPFLAGS="$CPPFLAGS $CLN_CFLAGS $GINAC_CFLAGS"
fi

AC_SUBST(FLIBS)

AC_CONFIG_FILES([Makefile])

AC_OUTPUT

# To run with looptools, run: ./configure --enable-looptools CPPFLAGS=-I/home/bca20/code/looptools/LoopTools/install/include LDFLAGS=-L/home/bca20/code/looptools/LoopTools/install/lib/ and add -looptools to src/softsusy.amk libs


