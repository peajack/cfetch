#ifndef CFETCH_H
#define CFETCH_H

#include <stddef.h>

struct data {
    unsigned int flags;
    char *result;
    char *label;
};

struct block {
    void *(*func)(void *);
    char *format;
    unsigned int flags;
};

#include "blocks/kernel.h"
#include "blocks/os.h"
#include "blocks/shell.h"
#include "blocks/uptime.h"
#include "blocks/user.h"

int main(void);
#endif // CFETCH_H
