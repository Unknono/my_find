#include "structs.h"

#include <string.h>

struct params* parse_args(int argc, char** argv)
{
    struct params* params = init_params();
    if (!params)
        return NULL;

    // parse startpoints
    int i = 0;
    while (i < argc && argv[i][0] == '-')
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
        if (strstr(argv[i], "help"))
            params->help = true;
    }

    return params;
}
