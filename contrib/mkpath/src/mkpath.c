// From: http://nion.modprobe.de/blog/archives/357-Recursive-directory-creation.html
// Author: Nico Golde (2005)

#include "mkpath/mkpath.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void recursive_mkdir(const char *path)
{
        char opath[256];
        char *p;
        size_t len;

        strncpy(opath, path, sizeof(opath));
        len = strlen(opath);
        if(opath[len - 1] == '/')
                opath[len - 1] = '\0';
        for(p = opath; *p; p++)
                if(*p == '/') {
                        *p = '\0';
                        if(access(opath, F_OK))
                                mkdir(opath, ACCESSPERMS);
                        *p = '/';
                }
        if(access(opath, F_OK))         /* if path is not terminated with / */
                mkdir(opath, ACCESSPERMS);
}

