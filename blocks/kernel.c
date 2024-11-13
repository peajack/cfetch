#include "kernel.h"
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

void *kernel(void *arg) {
    struct data *data = (struct data *)arg;
    data->label = "KERNEL";

    struct utsname name;
    uname(&name);

    char *buf = malloc(sizeof(char) * 100);
    strncpy(buf, name.release, sizeof(buf) * sizeof(char));
    data->result = buf;

    return 0;
}
