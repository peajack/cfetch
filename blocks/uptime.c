#ifndef __linux__
#include <time.h>
#endif
#include "../util.h"
#include "uptime.h"
#include <stdio.h>

void *uptime(void *args) {
#define BUFSIZE 50
    int days, hours, minutes = 0;
    unsigned int sec = 0;
    char buf[BUFSIZE];
#if defined(__linux__)
#define LINESIZE 100
    FILE *uptime_file;
    char line[LINESIZE];
#else
    struct timespec timespec;
#endif

    struct data *data = (struct data *)args;
    data->label = "UPTIME";
    data->result = "n/a";

#if defined(__linux__)

    uptime_file = fopen("/proc/uptime", "r");
    if (uptime_file == NULL) {
        goto end;
    }
    fgets(line, 100, uptime_file);
    sscanf(line, "%u %*d", &sec);
    fclose(uptime_file);

#else

    clock_gettime(CLOCK_UPTIME, &timespec);
    sec = (unsigned int)timespec.tv_sec;

#endif

    days = sec / 86400;
    sec = sec % 86400;
    hours = sec / 3600;
    sec = sec % 3600;
    minutes = sec / 60;

    snprintf(buf, 50, "%dd %dh %dm", days, hours, minutes);
    data->result = buf;

    goto end;
end:
    data->result = strdup(data->result);
    return 0;
}
