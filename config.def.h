#include "cfetch.h"

#define HAS_LOGO 1

struct block blocks[] = {
	{ user,		"%s",		USERNAME | HOSTNAME		},
	{ os,		"%s",		0						},
    { kernel,	"%s",		0						},
    // { shell,	"%s",		NULL 			}
};
