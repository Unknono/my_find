#include "structs.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static struct startpoint *create_startpoint(char *name)
{
    struct startpoint *sp = malloc(sizeof(struct startpoint));
    if (!sp)
        return NULL;

    // init struct
    sp->name = name;
    sp->next = NULL;

    return sp;
}

static void dealloc_startpoints(struct startpoint *sp)
{
    if (sp)
    {
        while (sp)
        {
            struct startpoint *to_delete = sp;
            sp = sp->next;
            free(to_delete->name);
            free(to_delete);
        }
    }
}

struct params *init_params(void)
{
    struct params *new_params = malloc(sizeof(struct params));
    if (!new_params)
        return NULL;

    // init struct
    new_params->help = false;
    new_params->startpoints = NULL;

    return new_params;
}

bool add_startpoint(struct params **params, char *startpoint)
{
    // startpoint creation
    struct startpoint *sp = create_startpoint(startpoint);
    if (!sp) // failed to add
        return false;

    // either no startpoints (replace null by the elem) ...
    if (!(*params)->startpoints)
    {
        (*params)->startpoints = sp;
    }
    // ... or some (append).
    else // does this method relly modify the "params" parameter ?
    {
        struct startpoint *cur = (*params)->startpoints;
        while (cur->next)
        {
            cur = cur->next;
        }

        cur->next = sp;
    }

    // all clear!
    return true;
}

void print_startpoints(struct startpoint *sp)
{
    if (sp)
    {
        size_t i = 1;
        while (sp)
        {
            printf("Startpoint %zu: %s\n", i, sp->name);
            sp = sp->next;

            i++;
        }
    }
}

void dealloc_params(struct params *params)
{
    dealloc_startpoints(params->startpoints);
    free(params);
}
