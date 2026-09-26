#include "display_files.h"

#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "error.h"
#include "structs.h"

static int get_display_dir_content(char *dir)
{
    struct dirent *de;

    DIR *dr = opendir(".");
    if (!dr)
        return throw_error("get_display_dir_content: could not open directory");

    while ((de = readdir(dr)))
    {
        if (strcmp(de->d_name, "..") != 0)
        {
            if (strcmp(dir, ".") == 0)
            {
                if (strcmp(de->d_name, ".") == 0)
                    printf("%s\n", de->d_name);
                else
                    printf("%s/%s\n", dir, de->d_name);
            }
            else
                printf("%s%s\n", dir, de->d_name);
        }
    }

    closedir(dr);
    return 0;
}

int display_files(struct startpoint *sps)
{
    // no startpoints: default behavior (".")
    if (!sps)
    {
        if (get_display_dir_content(".") != 0)
            return throw_error("display_files: recursive call failed.");

        return 0;
    }

    struct startpoint *curr = sps;
    while (curr)
    {
        if (get_display_dir_content(curr->name) != 0)
            return throw_error("display_files: recursive call failed.");
        curr = curr->next;
    }

    return 0;
}
