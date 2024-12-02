#ifndef __linux__
#include <time.h>
#endif
#include <stdio.h>
#include "uptime.h"
#include "../util.h"

void *uptime(void *args) {
    struct data *data = (struct data *)args;
    data->label = "UPTIME";
    data->result = "n/a";

    int days, hours, minutes = 0;
    long long sec = 0;
#if defined(__linux__)

    FILE *uptime_file = fopen("/proc/uptime", "r");
    char line[100];
    fgets(line, 100, uptime_file);
    sscanf(line, "%lld %[]", sec);
    fclose(uptime_file);

#else

    struct timespec timespec;
    clock_gettime(CLOCK_UPTIME, &timespec);
    sec = timespec.tv_sec;

#endif

    days = sec / 86400;
    sec = sec % 86400;
    hours = sec / 3600;
    sec = sec % 3600;
    minutes = sec / 60;
    
    char buf[50];
    snprintf(buf, 50, "%dd %dh %dm", days, hours, minutes);
    data->result = buf;

    data->result = strdup(data->result);
    return 0;
}

