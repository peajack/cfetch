#include <time.h>
#include <stdio.h>
#include "uptime.h"
#include "../util.h"

void *uptime(void *args) {
    struct data *data = (struct data *)args;
    data->label = "UPTIME";
    data->result = "n/a";

    struct timespec timespec;
    clock_gettime(CLOCK_UPTIME, &timespec);

    long long sec = timespec.tv_sec;
    int days, hours, minutes = 0;
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

