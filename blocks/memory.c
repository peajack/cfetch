#include "memory.h"
#include "../util.h"
#include <stdio.h>
#ifdef __OpenBSD__
#include <sys/types.h>
#include <sys/sysctl.h>
#include <uvm/uvmexp.h>
#include <unistd.h>
#include <strings.h>
#endif

void *memory(void *args) {
	struct data *data = (struct data *)args;
	data->label = "MEMORY";
	data->result = "undefined/null MB (NaN%)";

	unsigned long mem_total = 0;
	unsigned long mem_used = 0;
	unsigned int used_percent = 0;

#if defined(__linux__)

	FILE *meminfo = fopen("/proc/meminfo", "r");

#define LINESIZE 100
	char line[LINESIZE];

	unsigned long mem_available = 0;
	while (fgets(line, LINESIZE, meminfo)) {
		sscanf(line, "MemTotal: %lu kB", &mem_total);
		sscanf(line, "MemAvailable: %lu kB", &mem_available);
		if (mem_total && mem_available) {
			break;
		}
	}
	fclose(meminfo);

	mem_total = mem_total / 1024;
	mem_available = mem_available / 1024;
	mem_used = mem_total - mem_available;
	

#elif defined(__OpenBSD__)

	int mib[] = {CTL_VM, VM_UVMEXP};
	struct uvmexp uvmexp;
	size_t size = sizeof(uvmexp);
	if (sysctl(mib, 2, &uvmexp, &size, NULL, 0) == -1) {
		bzero(&uvmexp, size);
		return 0;
	}
	mem_total = (uvmexp.npages << uvmexp.pageshift) / 1024 / 1024;
	mem_used = (uvmexp.active << uvmexp.pageshift) / 1024 / 1024;

#endif

	if (mem_total && mem_used)
		used_percent = ((double)(mem_used) / (double)(mem_total)) * 100;

#define BUFSIZE 100
	char buf[BUFSIZE];
	snprintf(buf, BUFSIZE, "%lu/%lu MB (%d%%)", mem_used, mem_total, used_percent);
	data->result = buf;

	data->result = strdup(data->result);
	return 0;
}

