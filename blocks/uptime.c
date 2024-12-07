#if defined(__linux__)
#include <sys/sysinfo.h>
#else
#include <time.h>
#endif
#include "../util.h"
#include "uptime.h"
#include <stdio.h>

void *uptime(void *args) {
#define BUFSIZE 50
    int days, hours, minutes = 0;
    long sec = 0;
    char buf[BUFSIZE];
#if defined(__linux__)
    struct sysinfo info;
#else
    struct timespec timespec;
#endif

    struct data *data = (struct data *)args;
    data->label = "UPTIME";
    data->result = "n/a";

#if defined(__linux__)

    sysinfo(&info);
    sec = info.uptime;

#else

    clock_gettime(CLOCK_UPTIME, &timespec);
    sec = timespec.tv_sec;

#endif

    days = sec / 86400;
    sec = sec % 86400;
    hours = sec / 3600;
    sec = sec % 3600;
    minutes = sec / 60;

    snprintf(buf, 50, "%dd %dh %dm", days, hours, minutes);

    data->result = strdup(buf);
    return 0;
}
