#,
#   =================================
#   |                               |
#   |   Global variables for CBGB   |
#   |                               |
#   =================================
#

output_file_path_be_types = 'backend_types_header_code.hpp'
output_file_path_frontend = 'frontend_header_code.hpp'

alphabet = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']


# Type translations from Fortran to C (using GAMBIT typedefs)
type_translation_dict = {
                          'character'        : 'Fcharacter',
                          'complex'          : 'Fcomplex',
                          'complex*8'        : 'Fcomplex8',
                          'complex*16'       : 'Fcomplex16',
                          'doublecomplex'    : 'Fdouble_complex',
                          'doubleprecision'  : 'Fdouble',
                          'integer'          : 'Finteger',
                          'integer*2'        : 'Finteger2',
                          'integer*4'        : 'Finteger4',
                          'integer*8'        : 'Finteger8',
                          'logical'          : 'Flogical',
                          'logical*1'        : 'Flogical1',
                          'real'             : 'Freal',
                          'real*4'           : 'Freal4',
                          'real*8'           : 'Freal8',
                          'real*16'          : 'Freal16',
                        }


# Default Fortran implicit types, to be used if there are no 'implicit' statements.
default_implicit_types = { 
                           'a': ('real',1),
                           'b': ('real',1),
                           'c': ('real',1),
                           'd': ('real',1),
                           'e': ('real',1),
                           'f': ('real',1),
                           'g': ('real',1),
                           'h': ('real',1),
                           'i': ('integer',1),
                           'j': ('integer',1),
                           'k': ('integer',1),
                           'l': ('integer',1),
                           'm': ('integer',1),
                           'n': ('integer',1),
                           'o': ('real',1),
                           'p': ('real',1),
                           'q': ('real',1),
                           'r': ('real',1),
                           's': ('real',1),
                           't': ('real',1),
                           'u': ('real',1),
                           'v': ('real',1),
                           'w': ('real',1),
                           'x': ('real',1),
                           'y': ('real',1),
                           'z': ('real',1)
                         }



# Type translations if the GAMBIT Fortran typedefs are not used
# type_translation_dict = {
#                           'character'        : 'char',
#                           'doubleprecision'  : 'double',
#                           'integer'          : 'int',
#                           'integer*2'        : 'short',
#                           'integer*4'        : 'long int',
#                           'integer*8'        : 'long long int',
#                           'logical'          : 'long int',
#                           'logical*1'        : 'bool',
#                           'logical*2'        : 'unsigned short int',
#                           'logical*4'        : 'unsigned long int',
#                           'logical*8'        : 'unsigned long long int',
#                           'real'             : 'float',
#                           'real*4'           : 'float',
#                           'real*8'           : 'double',
#                           'real*16'          : 'long double',
#                         }

