#include <unistd.h>
#include "cpu.h"
#include "../util.h"
#ifdef __OpenBSD__
#include <sys/types.h>
#include <sys/sysctl.h>
#endif

void *cpu(void *args) {
    struct data *data = (struct data *)args;
    data->label = "CPU";
    data->result = "n/a";
#if defined(__linux__)

#elif defined(__OpenBSD__)

    int mib[2] = {CTL_HW, HW_MODEL};
    char model[200];
    size_t len = sizeof(model);
    if (sysctl(mib, 2, &model, &len, NULL, 0) == -1)
        goto end;
    data->result = model;
    goto end;

#endif

end:
    data->result = strdup(data->result);
    return 0;
}

