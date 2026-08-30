#include "args.h"
#include "structs.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
    // skip executable param
    struct params* params = parse_args(argc - 1, argv + 1);
    if (!params)
        return 1;

    printf("Help: %s\n", params->help ? "true" : "false");
    print_startpoints(params->startpoints);

    dealloc_params(params);
    return 0;
}
