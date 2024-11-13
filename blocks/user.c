#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>

void *user(void *arg) {
#define USERNAME_LEN 50
#define HOSTNAME_LEN 50
    struct data *data = (struct data *)arg;
    data->label = "USER";
    char *username = malloc(sizeof(char) * (USERNAME_LEN + 1));
    char *hostname = malloc(sizeof(char) * (HOSTNAME_LEN + 1));

    if (data->flags & USERNAME) {
        strncpy(username, getlogin(), sizeof(char) * sizeof(username));
    }
    if (data->flags & HOSTNAME) {
        struct utsname name;
        uname(&name);
        strncpy(hostname, name.nodename, sizeof(char) * sizeof(hostname));
    }

    if (data->flags & HOSTNAME && data->flags & USERNAME) {
        int buflen = sizeof(char) * (sizeof(username) + sizeof(hostname));
        char *buf = malloc(buflen);
        snprintf(buf, buflen, "%s@%s", username, hostname);
        free(username);
        free(hostname);
        data->result = buf;
    } else if (data->flags & HOSTNAME) {
        data->result = hostname;
        free(username);
    } else {
        data->result = username;
        free(hostname);
    }
    return 0;
}
