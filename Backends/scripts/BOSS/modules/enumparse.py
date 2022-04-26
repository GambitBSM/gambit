###########################
#                         #
#  Enum parsing for BOSS  #
#                         #
###########################

from __future__ import print_function
from collections import OrderedDict
import os

import modules.active_cfg as active_cfg
exec("import configs." + active_cfg.module_name + " as cfg")

import modules.gb as gb
import modules.utils as utils
import modules.enumutils as enumutils
import modules.infomsg as infomsg


#
# Module-level globals
#

includes = OrderedDict()



# ====== run ========

# Main function for parsing enums

def run():


    # Clear the module-level dict that keeps track of include statements
    includes.clear()


    #
    # Loop over all enums
    #
    
    for enum_name_full, enum_el in gb.enum_dict.items():

        # Clear all info messages
        infomsg.clearInfoMessages()

        # Number of enums done
        enum_i = len(gb.enums_done)

        # Generate dict with different variations of the enum name
        enum_name = utils.getEnumNameDict(enum_el)


        # Print current enum
        print()
        print('  ' + utils.modifyText('Enum:','underline') + ' ' + enum_name['long'])


        # Enum namespace
        namespaces = utils.getNamespaces(enum_el)
        has_namespace = bool(len(namespaces))

        # Set original file variables 
        original_enum_file_el   = gb.id_dict[enum_el.get('file')]
        original_file_name       = original_enum_file_el.get('name')
        original_file_name_base  = os.path.basename(original_file_name)
        original_class_file_dir  = os.path.split(original_file_name)[0]

        # Register paths of original files in global dict
        gb.original_file_paths[original_file_name_base] = original_file_name

        # Read content of original enum file
        f = open(original_file_name, 'r')
        original_file_content = f.read()
        f.close()
        original_file_content_nocomments = utils.removeComments(original_file_content, insert_blanks=True)

        # Prepare entries in gb.new_code and includes
        if original_file_name not in gb.new_code.keys():
            gb.new_code[original_file_name] = {'code_tuples':[], 'add_include_guard':False}
        if original_file_name not in includes.keys():
            includes[original_file_name] = []


        # Generate code for #include statements, declarations of enum values
        # and comments in orginal header/source file 
        #

        addIncludesDeclAndCommentsToOriginalEnumFile(enum_el, enum_name,
                                       namespaces, original_file_name,
                                       original_file_content_nocomments, original_file_content)

        #
        # Keep track of enums done
        #

        gb.enums_done.append(enum_name)


        print()


    #
    # End loop over enums
    #

# ====== END: run ========



# ====== addIncludesDeclAndCommentsToOriginalEnumFile ========

# Generate code for #include statements in orginal header/source file

def addIncludesDeclAndCommentsToOriginalEnumFile(enum_el, enum_name, namespaces, original_file_name,
                                   original_file_content_nocomments, original_file_content) :

    # Generate include statement for enum declaration header
    include_line = '#include "' + os.path.join(gb.backend_types_basedir, gb.gambit_backend_name_full, gb.enum_decls_wrp_fname + cfg.header_extension ) + '"'

    # Check that we haven't included that statement already
    if include_line in includes[original_file_name]:
        add_include_line = False
    else:
        add_include_line = True

    # Check for namespace
    has_namespace = bool(len(namespaces))

    # Find enum name position in the original file
    enum_name_pos = enumutils.findEnumNamePosition(enum_el, original_file_content_nocomments)

    # Find insert position
    #insert_pos = original_file_content_nocomments[:enum_name_pos].rfind('enum')
    insert_pos = enum_name_pos
    # - Adjust for the indentation
    use_indent = ''
    while insert_pos > 0:
        char = original_file_content[insert_pos-1]
        if char in [' ','\t']:
            use_indent += char
            insert_pos -= 1
        else:
            break

    # Construct code
    include_code = ''
    include_code += use_indent

    if add_include_line :
        for ns in namespaces:
            include_code += '} '
        include_code += '\n'*has_namespace
        include_code += use_indent + include_line + '\n'

        include_code += use_indent

        for ns in namespaces:
            include_code += 'namespace ' + ns + ' { '

        include_code += '\n'*has_namespace

    # Add typedef and constexpr for the values
    include_code += 'typedef ' + gb.gambit_backend_name_full + '::' + enum_name['long'] + ' ' + enum_name['short'] + ';\n'
    for val in enum_name['enum_values'] :
       include_code += 'constexpr ' + enum_name['short'] + ' ' + val + ' = ' + gb.gambit_backend_name_full + '::' + enum_name['long'] + '::' + val + ';\n'

    # Find where to add the comment tags
    rel_pos_start, rel_pos_end = utils.getBracketPositions(original_file_content_nocomments[insert_pos:], delims=['{','}'])
 
    # Add comments
    include_code += '/*'
    comment_end = insert_pos + rel_pos_end + 2

    # Register code
    gb.new_code[original_file_name]['code_tuples'].append( (insert_pos, include_code) )
    gb.new_code[original_file_name]['code_tuples'].append( (comment_end, '*/') )

    # Register include line
    if add_include_line : 
        includes[original_file_name].append(include_line)



# ====== END: addIncludesDeclAndCommentsToOriginalEnumFile ========

