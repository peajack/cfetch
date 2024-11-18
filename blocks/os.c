#include "os.h"
#include "../util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *os(void *args) {
    struct data *data = (struct data *)args;
    data->label = "OS";
    data->result = strdup("unknown");
#if defined(__linux__)

    FILE *file = fopen("/etc/os-release", "r");
    if (file == NULL) {
        return 0;
    }

#define BUFSIZE 200
#define NAMESIZE 100
    char os_name[NAMESIZE];
    char line[BUFSIZE];
    while ((fgets(line, BUFSIZE, file))) {
        if ((sscanf(line, "NAME=\"%[^\n\"]\"\n", os_name)) == 1) {
            data->result = strdup(os_name);
            break;
        }
    }
	fclose(file);

#elif defined(__FreeBSD__)

    data->result = strdup("FreeBSD");

#elif defined(__OpenBSD__)

    data->result = strdup("OpenBSD");

#elif defined(__NetBSD__)

    data->result = strdup("NetBSD");

#endif
    return 0;
}
