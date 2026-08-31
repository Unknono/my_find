#include "args.h"
#include "structs.h"

#include <stdio.h>

static void print_help_msg(void)
{
    printf("my_find command help:\n"
            "    It is a minimalist version of the original 'find' UNIX Command.\n"
            "    ./my_find [startpoints...] [options...]\n\n"
            "    If no \"startpoints\" are found before options (beginning with the '-' character),\n"
            "    the command will find all files and directories from the current directory.\n\n"
            "    Options:\n"
            "        -help, --help: Display this help message.\n"
            "        -name [regex]: Show paths from startpoints of all the files matching the regex case-sensitively.\n"
            "        -iname [regex]: Show paths from startpoints of all the files matching the regex case-insensitively.\n");
}

int main(int argc, char* argv[])
{
    // extract startpoints
    struct params* params = parse_args(argc - 1, argv + 1); // skip executable param
    if (!params)
        return 1;

    // DEBUG
    printf("Help: %s\n", params->help ? "true" : "false");
    print_startpoints(params->startpoints);

    // first check if help is true
    if (params->help)
        print_help_msg();
    else // "find" is now active
    {

    }

    dealloc_params(params);
    return 0;
}
