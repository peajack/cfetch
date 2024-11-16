#include "kernel.h"
#include "../util.h"
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

void *kernel(void *arg) {
    struct data *data = (struct data *)arg;
    data->label = "KERNEL";

    struct utsname name;
    uname(&name);
    data->result = strdup(name.release);

    return 0;
}
