#include "memory.h"
#include "../util.h"
#include <stdio.h>
#ifdef __OpenBSD__
#include <strings.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <uvm/uvmexp.h>
#endif

void *memory(void *args) {
#if defined(__OpenBSD__)
    int mib[2];
    struct uvmexp uvmexp;
    size_t size = sizeof(uvmexp);
#elif defined(__linux__)
#define LINESIZE 100
    FILE *meminfo;
    char line[LINESIZE] = {0};
    unsigned long mem_available = 0;
#endif
#define BUFSIZE 100
    char buf[BUFSIZE];
    unsigned long mem_total = 0;
    unsigned long mem_used = 0;
    unsigned int used_percent = 0;

    struct data *data = (struct data *)args;
    data->label = "MEMORY";
    data->result = "undefined/null MB (NaN%)";

#if defined(__linux__)

    meminfo = fopen("/proc/meminfo", "r");
    if (meminfo == NULL) {
        goto end;
    }
    while (fgets(line, LINESIZE, meminfo)) {
        sscanf(line, "MemTotal: %lu kB", &mem_total);
        sscanf(line, "MemAvailable: %lu kB", &mem_available);
        if (mem_total && mem_available) {
            break;
        }
    }
    fclose(meminfo);

    mem_used = (mem_total - mem_available) / 1024;
    mem_total = mem_total / 1024;

#elif defined(__OpenBSD__)

    mib[0] = CTL_VM;
    mib[1] = VM_UVMEXP;
    if (sysctl(mib, 2, &uvmexp, &size, NULL, 0) == -1) {
        bzero(&uvmexp, size);
        goto end;
    }

    mem_total = ((int64_t)uvmexp.npages << uvmexp.pageshift) / 1024 / 1024;
    mem_used = (uvmexp.active << uvmexp.pageshift) / 1024 / 1024;

#endif

    if (mem_total && mem_used)
        used_percent = ((double)(mem_used) / (double)(mem_total)) * 100;

    snprintf(buf, BUFSIZE, "%lu/%lu MB (%d%%)", mem_used, mem_total,
             used_percent);
    goto end;

end:
    data->result = strdup(buf);
    return 0;
}
