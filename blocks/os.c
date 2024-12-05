#include "os.h"
#include "../util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *os(void *args) {
#if defined(__linux__) && !defined(__ANDROID__)
    FILE *file;
#define NAMESIZE 100
#define LINESIZE 200
    char os_name[NAMESIZE];
    char line[LINESIZE];
#endif
    struct data *data = (struct data *)args;
    data->label = "OS";
    data->result = "unknown";
#if defined(__linux__) && !defined(__ANDROID__)

	data->result = "Linux";
    file = fopen("/etc/os-release", "r");
    if (file == NULL) {
        return 0;
    }

    while ((fgets(line, LINESIZE, file))) {
        if ((sscanf(line, "NAME=\"%[^\n\"]\"\n", os_name)) == 1) {
            data->result = os_name;
            break;
        }
    }
	fclose(file);

#elif defined(__ANDROID__)

	data->result = "Android";

#elif defined(__FreeBSD__)

    data->result = "FreeBSD";

#elif defined(__OpenBSD__)

    data->result = "OpenBSD";

#elif defined(__NetBSD__)

    data->result = "NetBSD";

#endif

	data->result = strdup(data->result);
    return 0;
}
