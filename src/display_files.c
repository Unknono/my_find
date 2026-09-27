#include "display_files.h"

#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "error.h"
#include "structs.h"

static char *extend_dirname(char *dir, char *suffix)
{
    size_t len_dir = strlen(dir);

    size_t slash_for_dot = 0;
    if (dir[len_dir - 1] != '/')
        slash_for_dot = 1;

    size_t nd_len = len_dir + slash_for_dot + strlen(suffix);
    char *new_dir = malloc(nd_len + 1);
    if (!new_dir)
        return NULL;
    new_dir[nd_len] = '\0';

    strcpy(new_dir, dir);
    if (slash_for_dot)
        strcpy(new_dir + len_dir, "/");
    strcpy(new_dir + len_dir + slash_for_dot, suffix);

    return new_dir;
}

static int get_display_dir_content_rec(char *dir)
{
    struct dirent *de;

    DIR *dr = opendir(dir);
    if (!dr)
        return throw_error(
            "get_display_dir_content_rec: could not open directory");

    while ((de = readdir(dr)))
    {
        if (strcmp(de->d_name, "..") != 0 && strcmp(de->d_name, ".") != 0)
        {
            if (dir[strlen(dir) - 1] != '/')
                printf("%s/%s\n", dir, de->d_name);
            else
                printf("%s%s\n", dir, de->d_name);
        }

        // detect if file is a directory
        // 1- Updating file path
        char *new_dir = extend_dirname(dir, de->d_name);
        if (!new_dir)
            return throw_error(
                "get_display_dir_content_rec: extend_dirname() failed.");

        struct stat s;
        stat(new_dir, &s);

        if (S_ISDIR(s.st_mode) && strcmp(de->d_name, ".") != 0
            && strcmp(de->d_name, "..") != 0)
            get_display_dir_content_rec(new_dir);

        free(new_dir);
    }

    closedir(dr);
    return 0;
}

int display_files(struct startpoint *sps)
{
    // no startpoints: default behavior (".")
    if (!sps)
    {
        puts(".");
        if (get_display_dir_content_rec(".") != 0)
            return throw_error("display_files: recursive call failed.");

        return 0;
    }

    struct startpoint *curr = sps;
    while (curr)
    {
        printf("%s\n", sps->name);
        if (get_display_dir_content_rec(curr->name) != 0)
            return throw_error("display_files: recursive call failed.");
        curr = curr->next;
    }

    return 0;
}
