#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>

// params processing
struct startpoint
{
    char* name;
    struct startpoint* next;
};

struct params
{
    // option checks
    bool help;

    // files
    struct startpoint* startpoints;
};

static struct startpoint* create_startpoint(char* name);
static void dealloc_startpoints(struct startpoint* sp);
struct params* init_params(void);
bool add_startpoint(struct params** params, char* startpoint);
void print_startpoints(struct startpoint* sp);
void dealloc_params(struct params* opt);

#endif /* !STRUCTS_H */
