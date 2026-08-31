#include "structs.h"

#include <string.h>

struct params* parse_args(int argc, char** argv)
{
    struct params* params = init_params();
    if (!params)
        return NULL;

    // parse startpoints
    int i = 0;
    while (i < argc && argv[i][0] != '-')
    {
        if (!add_startpoint(&params, argv[i]))
        {
            dealloc_params(params);
            return NULL;
        }

        i++;
    }

    // parse options
    while (i < argc && argv[i][0] == '-')
    {
        if (strcmp(argv[i], "-help") == 0 || strcmp(argv[i], "--help") == 0)
            params->help = true;

        i++;
    }

    return params;
}
