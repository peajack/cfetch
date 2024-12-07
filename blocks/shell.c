#include "shell.h"
#include "../util.h"
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void *shell(void *arg) {
    char *env;
    struct data *data = (struct data *)arg;
    data->label = "SHELL";

    if ((env = getenv("SHELL")) != NULL) {
        data->result = basename(env);
    }

    data->result = strdup(data->result);
    return 0;
}
