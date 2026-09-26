#include <stdio.h>

#include "args.h"
#include "display_files.h"
#include "error.h"
#include "structs.h"

static void print_help_msg(void)
{
    printf(
        "my_find command help:\n"
        "    It is a minimalist version of the original 'find' UNIX Command.\n"
        "    ./my_find [startpoints...] [options...]\n\n"
        "    If no \"startpoints\" are found before options (beginning with "
        "the '-' character),\n"
        "    the command will find all files and directories from the current "
        "directory.\n\n"
        "    Options:\n"
        "        -help, --help: Display this help message.\n"
        "        -name [regex]: Show paths from startpoints of all the files "
        "matching the regex case-sensitively.\n"
        "        -iname [regex]: Show paths from startpoints of all the files "
        "matching the regex case-insensitively.\n");
}

int main(int argc, char *argv[])
{
    // extract startpoints
    struct params *params =
        parse_args(argc - 1, argv + 1); // skip executable param
    if (!params)
        return throw_error("main: parse_args() failed.");

    // DEBUG
    printf("Help: %s\n", params->help ? "true" : "false");
    print_startpoints(params->startpoints);

    // first check if help is true
    if (params->help)
        print_help_msg();
    else // "find" is now active
    {
        if (display_files(params->startpoints) != 0)
            return throw_error("main: display_files() failed.");
    }

    dealloc_params(params);
    return 0;
}
