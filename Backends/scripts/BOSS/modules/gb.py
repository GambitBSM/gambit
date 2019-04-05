###############################
#                             #
#  Global variables for BOSS  #
#                             #
###############################


from collections import OrderedDict
import os

import modules.active_cfg as active_cfg
exec("import configs." + active_cfg.module_name + " as cfg")


# ~~~~~ BOSS global variables and containers ~~~~~

gambit_backend_namespace    = 'CAT_3(BACKENDNAME,_,SAFE_VERSION)'
gambit_backend_safeversion  = cfg.gambit_backend_version.replace('.','_')
gambit_backend_name_full    = cfg.gambit_backend_name + '_' + gambit_backend_safeversion

boss_dir = os.path.dirname(os.path.abspath(__file__))+'/..'
boss_temp_dir = 'BOSS_temp/' + gambit_backend_name_full
boss_output_dir = 'BOSS_output/' + gambit_backend_name_full

has_castxml_system = True
has_castxml_local = True

# boss_reset_dir = 'BOSS_reset_info'

debug_mode = False

new_code                = OrderedDict()
xml_file_name           = ''

id_dict                 = OrderedDict()
all_id_dict             = OrderedDict()
name_dict               = OrderedDict()
all_name_dict           = OrderedDict()

parents_of_loaded_classes = []
contains_pure_virtual_members = []

file_dict               = OrderedDict()
std_types_dict          = OrderedDict()
typedef_dict            = OrderedDict()
loaded_classes_in_xml   = OrderedDict()
func_dict               = OrderedDict()
new_header_files        = OrderedDict()
accepted_types          = []
std_headers_used        = []
original_file_paths     = OrderedDict()
std_include_paths       = []

functions_done          = []
classes_done            = []
wr_func_names           = []

factory_info            = OrderedDict()
class_factory_file_dict = OrderedDict()

function_file_dict      = OrderedDict()

symbol_name_counter     = 1
function_name_counter   = 1



backend_types_basedir = 'backend_types'
backend_types_dir_complete = os.path.join(boss_output_dir, backend_types_basedir, gambit_backend_name_full)

for_gambit_basedir = 'for_gambit'
for_gambit_backend_types_dir_complete = os.path.join(boss_output_dir, for_gambit_basedir, backend_types_basedir, gambit_backend_name_full)

frontend_base_dir = 'frontends'
frontend_dir_complete = os.path.join(boss_output_dir, frontend_base_dir)

gambit_backend_incl_dir = 'gambit/Backends/'
gambit_utils_incl_dir   = 'gambit/Utils/'

code_suffix          = '__BOSS'
abstr_class_prefix   = 'Abstract_'
wrapper_class_prefix = 'Wrapper_'

abstr_header_prefix     = 'abstract_'
wrapper_header_prefix   = 'wrapper_'
general_src_file_prefix = 'BOSS_'
factory_file_prefix     = general_src_file_prefix + 'factory_'
function_files_prefix   = general_src_file_prefix + 'func_'
func_return_utils_fname = general_src_file_prefix + 'function_return_utils'
wrapper_utils_fname     = general_src_file_prefix + 'wrapperutils'
frwd_decls_abs_fname    = 'forward_decls_abstract_classes'
frwd_decls_wrp_fname    = 'forward_decls_wrapper_classes'
wrapper_typedefs_fname  = 'wrappertypedefs'
abstract_typedefs_fname = 'abstracttypedefs'
enum_decls_wrp_fname    = 'enum_decl_copies'

frontend_fname          = gambit_backend_name_full + '.hpp'
frontend_path           = os.path.join(frontend_dir_complete, frontend_fname)

# Text modifications
textmods = {
    'blue'      : '\033[34m',
    'green'     : '\033[32m',
    'yellow'    : '\033[33m',
    'red'       : '\033[31m',
    'magenta'   : '\033[35m',
    'cyan'      : '\033[36m',
    'white'     : '\033[37m',
    'bold'      : '\033[1m',
    'underline' : '\033[4m',
    'end'       : '\033[0m',
}


# Dictionary of what names to use for various operator symbols
operator_names = {
          "="   : "equal",
          "+"   : "plus",
          "-"   : "minus",
          "*"   : "asterix",
          "/"   : "slash",
          "%"   : "percent",
          "&"   : "ampersand",
          "++"  : "plus_plus",
          "--"  : "minus_minus",
          "+="  : "plus_equal",
          "-="  : "minus_equal",
          "*="  : "asterix_equal",
          "/="  : "slash_equal",
          "%="  : "percent_equal",
          "&="  : "ampersand_equal",
          "|="  : "bar_equal",
          "^="  : "caret_equal",
         "<<="  : "double_angle_bracket_left_equal",
         ">>="  : "double_angle_bracket_right_equal",
          "[]"  : "square_bracket_pair",
          "()"  : "round_bracket_pair",
          "=="  : "double_equal",
          "!="  : "exclamation_equal",
          ">"   : "angle_bracket_right",
          "<"   : "angle_bracket_left",
          ">="  : "angle_bracket_right_equal",
          "<="  : "angle_bracket_left_equal",
          "!"   : "exclamation",
          "&&"  : "double_ampersand",
          "|"   : "bar",
          "^"   : "caret",
          "<<"  : "double_angle_bracket_left",
          ">>"  : "double_angle_bracket_right",
          "->"  : "arrow",
         "->*"  : "arrow_asterix",
          ","   : "comma",
         "new"  : "new",
       "new[]"  : "new_square_bracket_pair",
      "delete"  : "delete",
    "delete[]"  : "delete_square_bracket_pair",
}


# Standard library classes and headers
std_headers = {
    # "div_t"                 : "<cstdlib>",
    # "ldiv_t"                : "<cstdlib>",
    # "lldiv_t"               : "<cstdlib>",
    # "size_t"                : "<cstdlib>",
    # "jmp_buf"               : "<csetjmp>",
    # "va_list"               : "<cstdarg>",
    "std::type_info"        : "<typeinfo>",
    "std::bad_typeid"       : "<typeinfo>",
    "std::bad_cast"         : "<typeinfo>",
    "std::type_index"       : "<typeindex>",
    "std::integral_constant"    : "<type_traits>",
    "std::is_void"              : "<type_traits>",
    "std::is_null_pointer"      : "<type_traits>",
    "std::is_integral"          : "<type_traits>",
    "std::is_floating_point"    : "<type_traits>",
    "std::is_array"             : "<type_traits>",
    "std::is_pointer"           : "<type_traits>",
    "std::is_lvalue_reference"  : "<type_traits>",
    "std::is_rvalue_reference"  : "<type_traits>",
    "std::is_member_object_pointer"     : "<type_traits>",
    "std::is_member_function_pointer"   : "<type_traits>",
    "std::is_enum"              : "<type_traits>",
    "std::is_union"             : "<type_traits>",
    "std::is_class"             : "<type_traits>",
    "std::is_function"          : "<type_traits>",
    "std::is_reference"         : "<type_traits>",
    "std::is_arithmetic"        : "<type_traits>",
    "std::is_fundamental"       : "<type_traits>",
    "std::is_object"            : "<type_traits>",
    "std::is_scalar"            : "<type_traits>",
    "std::is_compound"          : "<type_traits>",
    "std::is_member_pointer"    : "<type_traits>",
    "std::is_const"             : "<type_traits>",
    "std::is_volatile"          : "<type_traits>",
    "std::is_trivial"           : "<type_traits>",
    "std::is_trivially_copyable"    : "<type_traits>",
    "std::is_standard_layout"       : "<type_traits>",
    "std::is_pod"               : "<type_traits>",
    "std::is_literal_type"      : "<type_traits>",
    "std::is_empty"             : "<type_traits>",
    "std::is_polymorphic"       : "<type_traits>",
    "std::is_abstract"          : "<type_traits>",
    "std::is_signed"            : "<type_traits>",
    "std::is_unsigned"          : "<type_traits>",
    "std::is_constructible"     : "<type_traits>",
    "std::is_default_constructible"     : "<type_traits>",
    "std::is_copy_constructible"        : "<type_traits>",
    "std::is_move_constructible"        : "<type_traits>",
    "std::is_assignable"                : "<type_traits>",
    "std::is_copy_assignable"           : "<type_traits>",
    "std::is_move_assignable"           : "<type_traits>",
    "std::is_destructible"              : "<type_traits>",
    "std::is_trivially_constructible"           : "<type_traits>",
    "std::is_trivially_default_constructible"   : "<type_traits>",
    "std::is_trivially_copy_constructible"      : "<type_traits>",
    "std::is_trivially_move_constructible"      : "<type_traits>",
    "std::is_trivially_assignable"              : "<type_traits>",
    "std::is_trivially_copy_assignable"         : "<type_traits>",
    "std::is_trivially_move_assignable"         : "<type_traits>",
    "std::is_trivially_destructible"            : "<type_traits>",
    "std::is_nothrow_constructible"             : "<type_traits>",
    "std::is_nothrow_default_constructible"     : "<type_traits>",
    "std::is_nothrow_copy_constructible"        : "<type_traits>",
    "std::is_nothrow_move_constructible"        : "<type_traits>",
    "std::is_nothrow_assignable"                : "<type_traits>",
    "std::is_nothrow_copy_assignable"           : "<type_traits>",
    "std::is_nothrow_move_assignable"           : "<type_traits>",
    "std::is_nothrow_destructible"              : "<type_traits>",
    "std::has_virtual_destructor"               : "<type_traits>",
    "std::alignment_of"             : "<type_traits>",
    "std::rank"                     : "<type_traits>",
    "std::extent"                   : "<type_traits>",
    "std::is_same"                  : "<type_traits>",
    "std::is_base_of"               : "<type_traits>",
    "std::is_convertible"           : "<type_traits>",
    "std::remove_const"             : "<type_traits>",
    "std::remove_volatile"          : "<type_traits>",
    "std::remove_cv"                : "<type_traits>",
    "std::add_const"                : "<type_traits>",
    "std::add_volatile"             : "<type_traits>",
    "std::add_cv"                   : "<type_traits>",
    "std::remove_const"             : "<type_traits>",
    "std::remove_volatile"          : "<type_traits>",
    "std::remove_cv"                : "<type_traits>",
    "std::add_const"                : "<type_traits>",
    "std::add_volatile"             : "<type_traits>",
    "std::add_cv"                   : "<type_traits>",
    "std::remove_reference"         : "<type_traits>",
    "std::add_lvalue_reference"     : "<type_traits>",
    "std::add_rvalue_reference"     : "<type_traits>",
    "std::remove_reference"         : "<type_traits>",
    "std::add_lvalue_reference"     : "<type_traits>",
    "std::add_rvalue_reference"     : "<type_traits>",
    "std::make_signed"              : "<type_traits>",
    "std::make_unsigned"            : "<type_traits>",
    "std::make_signed"              : "<type_traits>",
    "std::make_unsigned"            : "<type_traits>",
    "std::remove_extent"            : "<type_traits>",
    "std::remove_all_extents"       : "<type_traits>",
    "std::remove_extent"            : "<type_traits>",
    "std::remove_all_extents"       : "<type_traits>",
    "std::remove_pointer"           : "<type_traits>",
    "std::add_pointer"              : "<type_traits>",
    "std::remove_pointer"           : "<type_traits>",
    "std::add_pointer"              : "<type_traits>",
    "std::aligned_storage"          : "<type_traits>",
    "std::decay"                    : "<type_traits>",
    "std::enable_if"                : "<type_traits>",
    "std::conditional"              : "<type_traits>",
    "std::common_type"              : "<type_traits>",
    "std::underlying_type"          : "<type_traits>",
    "std::result_of"                : "<type_traits>",
    "std::aligned_storage"          : "<type_traits>",
    "std::aligned_union"            : "<type_traits>",
    "std::decay"                    : "<type_traits>",
    "std::enable_if"                : "<type_traits>",
    "std::conditional"              : "<type_traits>",
    "std::common_type"              : "<type_traits>",
    "std::underlying_type"          : "<type_traits>",
    "std::result_of"                : "<type_traits>",
    "std::bitset"                   : "<bitset>",
    "std::function"                 : "<functional>",
    "std::mem_fn"                   : "<functional>",
    "std::bad_function_call"        : "<functional>",
    "std::is_bind_expression"       : "<functional>",
    "std::is_placeholder"           : "<functional>",
    "std::reference_wrapper"        : "<functional>",
    "std::pair"                     : "<utility>",
    "std::piecewise_construct_t"    : "<utility>",
    "std::integer_sequence"         : "<utility>",
    # "clock_t"                       : "<ctime>",
    # "time_t"                        : "<ctime>",
    # "tm"                            : "<ctime>",
    "std::chrono::duration"                 : "<chrono>",
    "std::chrono::system_clock"             : "<chrono>",
    "std::chrono::steady_clock"             : "<chrono>",
    "std::chrono::high_resolution_clock"    : "<chrono>",
    "std::chrono::time_point"               : "<chrono>",
    "std::chrono::treat_as_floating_point"  : "<chrono>",
    "std::chrono::duration_values"          : "<chrono>",
    # "size_t"                        : "<cstddef>",
    # "ptrdiff_t"                     : "<cstddef>",
    # "nullptr_t"                     : "<cstddef>",
    # "max_align_t"                   : "<cstddef>",
    "std::initializer_list"         : "<initializer_list>",
    "std::tuple"                    : "<tuple>",
    "std::tuple_size"               : "<tuple>",
    "std::tuple_element"            : "<tuple>",
    "std::bad_alloc"                : "<new>",
    "std::bad_array_new_length"     : "<new>",
    "std::nothrow_t"                : "<new>",
    "std::unique_ptr"               : "<memory>",
    "std::shared_ptr"               : "<memory>",
    "std::weak_ptr"                 : "<memory>",
    "std::auto_ptr"                 : "<memory>",
    "std::owner_less"               : "<memory>",
    "std::enable_shared_from_this"  : "<memory>",
    "std::bad_weak_ptr"             : "<memory>",
    "std::default_delete"           : "<memory>",
    "std::allocator"                : "<memory>",
    "std::allocator_traits"         : "<memory>",
    "std::allocator_arg_t"          : "<memory>",
    "std::allocator_arg"            : "<memory>",
    "std::uses_allocator"           : "<memory>",
    "std::pointer_safety"           : "<memory>",
    "std::pointer_traits"           : "<memory>",
    "std::scoped_allocator_adaptor" : "<scoped_allocator>",
    "std::exception"                : "<exception>",
    "std::nested_exception"         : "<exception>",
    "std::bad_exception"            : "<exception>",
    "std::logic_error"              : "<stdexcept>",
    "std::invalid_argument"         : "<stdexcept>",
    "std::domain_error"             : "<stdexcept>",
    "std::length_error"             : "<stdexcept>",
    "std::out_of_range"             : "<stdexcept>",
    "std::runtime_error"            : "<stdexcept>",
    "std::range_error"              : "<stdexcept>",
    "std::overflow_error"           : "<stdexcept>",
    "std::underflow_error"          : "<stdexcept>",
    "std::error_category"           : "<system_error>",
    "std::generic_category"         : "<system_error>",
    "std::system_category"          : "<system_error>",
    "std::error_condition"          : "<system_error>",
    "std::errc"                     : "<system_error>",
    "std::error_code"               : "<system_error>",
    "std::system_error"             : "<system_error>",
    "std::is_error_code_enum"       : "<system_error>",
    "std::is_error_condition_enum"  : "<system_error>",
    "std::mbstate_t"                : "<cwchar>",
    "std::char_traits"              : "<string>",
    "std::basic_string"             : "<string>",
    "std::string"                   : "<string>",
    "std::wstring"                  : "<string>",
    "std::u16string"                : "<string>",
    "std::u32string"                : "<string>",
    "std::array"                    : "<array>",
    "std::vector"                   : "<vector>",
    "std::deque"                    : "<deque>",
    "std::list"                     : "<list>",
    "std::forward_list"             : "<forward_list>",
    "std::set"                      : "<set>",
    "std::multiset"                 : "<set>",
    "std::map"                      : "<map>",
    "std::multimap"                 : "<map>",
    "std::unordered_set"            : "<unordered_set>",
    "std::unordered_multiset"       : "<unordered_set>",
    "std::unordered_map"            : "<unordered_map>",
    "std::unordered_multimap"       : "<unordered_map>",
    "std::stack"                    : "<stack>",
    "std::queue"                    : "<queue>",
    "std::priority_queue"           : "<queue>",
    "std::iterator_traits"               : "<iterator>",
    "std::input_iterator_tag"            : "<iterator>",
    "std::output_iterator_tag"           : "<iterator>",
    "std::forward_iterator_tag"          : "<iterator>",
    "std::bidirectional_iterator_tag"    : "<iterator>",
    "std::random_access_iterator_tag"    : "<iterator>",
    "std::iterator"                      : "<iterator>",
    "std::reverse_iterator"              : "<iterator>",
    "std::move_iterator"                 : "<iterator>",
    "std::back_insert_iterator"          : "<iterator>",
    "std::front_insert_iterator"         : "<iterator>",
    "std::insert_iterator"               : "<iterator>",
    "std::istream_iterator"              : "<iterator>",
    "std::ostream_iterator"              : "<iterator>",
    "std::istreambuf_iterator"           : "<iterator>",
    "std::ostreambuf_iterator"           : "<iterator>",
    "std::complex"       : "<complex>",
    "std::valarray"          : "<valarray>",
    "std::slice"             : "<valarray>",
    "std::slice_array"       : "<valarray>",
    "std::gslice"            : "<valarray>",
    "std::gslice_array"      : "<valarray>",
    "std::mask_array"        : "<valarray>",
    "std::indirect_array"    : "<valarray>",
    "std::linear_congruential_engine"        : "<random>",
    "std::mersenne_twister_engine"           : "<random>",
    "std::subtract_with_carry_engine"        : "<random>",
    "std::discard_block_engine"              : "<random>",
    "std::independent_bits_engine"           : "<random>",
    "std::shuffle_order_engine"              : "<random>",
    "std::seed_seq"                          : "<random>",
    "std::uniform_int_distribution"          : "<random>",
    "std::uniform_real_distribution"         : "<random>",
    "std::bernoulli_distribution"            : "<random>",
    "std::binomial_distribution"             : "<random>",
    "std::negative_binomial_distribution"    : "<random>",
    "std::geometric_distribution"            : "<random>",
    "std::poisson_distribution"              : "<random>",
    "std::exponential_distribution"          : "<random>",
    "std::gamma_distribution"                : "<random>",
    "std::weibull_distribution"              : "<random>",
    "std::extreme_value_distribution"        : "<random>",
    "std::normal_distribution"               : "<random>",
    "std::lognormal_distribution"            : "<random>",
    "std::chi_squared_distribution"          : "<random>",
    "std::cauchy_distribution"               : "<random>",
    "std::fisher_f_distribution"             : "<random>",
    "std::student_t_distribution"            : "<random>",
    "std::discrete_distribution"             : "<random>",
    "std::piecewise_constant_distribution"   : "<random>",
    "std::piecewise_linear_distribution"     : "<random>",
    "std::ratio"                 : "<ratio>",
    "std::ratio_add"             : "<ratio>",
    "std::ratio_subtract"        : "<ratio>",
    "std::ratio_multiply"        : "<ratio>",
    "std::ratio_divide"          : "<ratio>",
    "std::ratio_equal"           : "<ratio>",
    "std::ratio_not_equal"       : "<ratio>",
    "std::ratio_less"            : "<ratio>",
    "std::ratio_less_equal"      : "<ratio>",
    "std::ratio_greater"         : "<ratio>",
    "std::ratio_greater_equal"   : "<ratio>",
    "std::ios_base"              : "<ios>",
    "std::basic_ios"             : "<ios>",
    "std::fpos"                  : "<ios>",
    "std::io_errc"               : "<ios>",
    "std::iostream_category"     : "<ios>",
    "std::basic_istream"         : "<istream>",
    "std::istream"               : "<istream>",
    "std::wistream"              : "<istream>",
    "std::basic_iostream"        : "<istream>",
    "std::iostream"              : "<istream>",
    "std::wiostream"             : "<istream>",
    "std::basic_ostream"         : "<ostream>",
    "std::ostream"               : "<ostream>",
    "std::wostream"              : "<ostream>",
    "std::basic_filebuf"         : "<fstream>",
    "std::basic_ifstream"        : "<fstream>",
    "std::basic_ofstream"        : "<fstream>",
    "std::basic_fstream"         : "<fstream>",
    "std::basic_stringbuf"       : "<sstream>",
    "std::basic_istringstream"   : "<sstream>",
    "std::basic_ostringstream"   : "<sstream>",
    "std::basic_stringstream"    : "<sstream>",
    "std::strstreambuf"          : "<strstream>",
    "std::istrstream"            : "<strstream>",
    "std::ostrstream"            : "<strstream>",
    "std::strstream"             : "<strstream>",
    "std::basic_streambuf"       : "<streambuf>",
    "std::locale"                : "<locale>",
    "std::wstring_convert"       : "<locale>",
    "std::wbuffer_convert"       : "<locale>",
    "std::ctype_base"            : "<locale>",
    "std::codecvt_base"          : "<locale>",
    "std::messages_base"         : "<locale>",
    "std::time_base"             : "<locale>",
    "std::money_base"            : "<locale>",
    "std::ctype"                 : "<locale>",
    "std::codecvt"               : "<locale>",
    "std::collate"               : "<locale>",
    "std::messages"              : "<locale>",
    "std::time_get"              : "<locale>",
    "std::time_put"              : "<locale>",
    "std::num_get"               : "<locale>",
    "std::num_put"               : "<locale>",
    "std::numpunct"              : "<locale>",
    "std::money_get"             : "<locale>",
    "std::money_put"             : "<locale>",
    "std::moneypunct"            : "<locale>",
    "std::ctype_byname"          : "<locale>",
    "std::codecvt_byname"        : "<locale>",
    "std::messages_byname"       : "<locale>",
    "std::collate_byname"        : "<locale>",
    "std::time_get_byname"       : "<locale>",
    "std::time_put_byname"       : "<locale>",
    "std::numpunct_byname"       : "<locale>",
    "std::moneypunct_byname"     : "<locale>",
    "std::lconv"                 : "<clocale>",
    "std::codecvt_utf8"          : "<codecvt>",
    "std::codecvt_utf16"         : "<codecvt>",
    "std::codecvt_utf8_utf16"    : "<codecvt>",
    "std::codecvt_mode"          : "<codecvt>",
    "std::basic_regex"           : "<regex>",
    "std::sub_match"             : "<regex>",
    "std::match_results"         : "<regex>",
    "std::regex_iterator"        : "<regex>",
    "std::regex_token_iterator"  : "<regex>",
    "std::regex_error"           : "<regex>",
    "std::regex_traits"          : "<regex>",
    "std::atomic"                : "<atomic>",
    "std::atomic_flag"           : "<atomic>",
    "std::memory_order"          : "<atomic>",
    "std::thread"                : "<thread>",
    "std::mutex"                     : "<mutex>",
    "std::timed_mutex"               : "<mutex>",
    "std::recursive_mutex"           : "<mutex>",
    "std::recursive_timed_mutex"     : "<mutex>",
    "std::lock_guard"                : "<mutex>",
    "std::unique_lock"               : "<mutex>",
    "std::defer_lock_t"              : "<mutex>",
    "std::try_to_lock_ta"            : "<mutex>",
    "std::dopt_lock_t"               : "<mutex>",
    "std::defer_lock"                : "<mutex>",
    "std::try_to_lock"               : "<mutex>",
    "std::adopt_lock"                : "<mutex>",
    "std::once_flag"                 : "<mutex>",
    "std::shared_mutex"              : "<shared_mutex>",
    "std::shared_timed_mutex"        : "<shared_mutex>",
    "std::shared_lock"               : "<shared_mutex>",
    "std::promise"                   : "<future>",
    "std::packaged_task"             : "<future>",
    "std::future"                    : "<future>",
    "std::shared_future"             : "<future>",
    "std::launch"                    : "<future>",
    "std::future_status"             : "<future>",
    "std::future_error"              : "<future>",
    "std::future_errc"               : "<future>",
    "std::condition_variable"        : "<condition_variable>",
    "std::condition_variable_any"    : "<condition_variable>",
    "std::cv_status"                 : "<condition_variable>",
}

