#include "../cfetch.h"

#ifndef CFETCH_USER_H
#define CFETCH_USER_H
enum { USERNAME = 1 << 0, HOSTNAME = 1 << 1 };

void *user(void *);
#endif // CFETCH_USER_H
