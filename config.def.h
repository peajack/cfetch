#include "cfetch.h"

#define HAS_LOGO 1

/**
 * available blocks:
 * user         username, hostname
 *              flags: USERNAME, HOSTNAME
 * os           os name
 *              no flags
 * kernel       kernel version
 *              no flags
 * shell        current shell
 *              no flags
 * memory       memory usage
 *              no flags
 * uptime       machine uptime
 *              no flags
 * cpu          cpu model
 *              no flags
 **/

struct block blocks[] = {
    /* block    flags                  */
    {user, USERNAME | HOSTNAME},
    {os, 0},
    {kernel, 0},
    {shell, 0},
    {uptime, 0},
    {memory, 0},
};
