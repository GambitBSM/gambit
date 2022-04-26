####################################
#                                  #
#  Utility functions for handling  # 
#  C++ enums with BOSS             #
#                                  #
####################################

from __future__ import print_function
from collections import OrderedDict
import os

# import modules.cfg as cfg
import modules.active_cfg as active_cfg
exec("import configs." + active_cfg.module_name + " as cfg")
import modules.gb as gb
import modules.utils as utils
import modules.exceptions as exceptions
import modules.infomsg as infomsg



# ====== findEnumNamePosition ========

# Find the position of a enum name  

def findEnumNamePosition(enum_el, file_content_nocomments):

    # Find the line the member is at
    file_content_list = file_content_nocomments.split('\n')
    enum_line = int(enum_el.get('line')) - 1

    # Get the position in the file contents
    enum_name_pos = file_content_nocomments.find(file_content_list[enum_line])

    return enum_name_pos

# ====== END: findEnumNamePosition ========



