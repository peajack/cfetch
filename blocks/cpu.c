#include "cpu.h"
#include "../util.h"
#include <unistd.h>
#ifdef __OpenBSD__
#include <sys/sysctl.h>
#include <sys/types.h>
#endif

void *cpu(void *args) {
#if defined(__linux__)
    /* TODO */
#elif defined(__OpenBSD__)
#define MODELSIZE 200
    int mib[2];
    char model[MODELSIZE];
    size_t len;
#endif

    struct data *data = (struct data *)args;
    data->label = "CPU";
    data->result = "n/a";

#if defined(__linux__)

    goto end;

#elif defined(__OpenBSD__)

    mib[0] = CTL_HW;
    mib[1] = HW_MODEL;
    len = sizeof(model);
    if (sysctl(mib, 2, &model, &len, NULL, 0) == -1)
        goto end;
    data->result = model;
    goto end;

#endif

end:
    data->result = strdup(data->result);
    return 0;
}
