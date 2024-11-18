#include "cfetch.h"

#define HAS_LOGO 1

struct block blocks[] = {
	{ user,		USERNAME | HOSTNAME		},
	{ os,		0						},
    { kernel,	0						},
    { shell,	0 						},
	{ memory,	0						},
};
