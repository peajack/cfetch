#include "user.h"
#include "../util.h"
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
    char username[USERNAME_LEN + 1];
    char hostname[HOSTNAME_LEN + 1];

    if (data->flags & USERNAME) {
        strncpy(username, getlogin(), sizeof(char) * USERNAME_LEN);
		username[USERNAME_LEN] = '\0';
    }
    if (data->flags & HOSTNAME) {
        struct utsname name;
        uname(&name);
        strncpy(hostname, name.nodename, sizeof(char) * HOSTNAME_LEN);
		hostname[HOSTNAME_LEN] = '\0';
    }

    if (data->flags & HOSTNAME && data->flags & USERNAME) {
        int buflen = sizeof(char) * (USERNAME_LEN + HOSTNAME_LEN + 2);
        char buf[buflen];
        snprintf(buf, buflen, "%s@%s", username, hostname);
        data->result = strdup(buf);
    } else if (data->flags & HOSTNAME) {
        data->result = strdup(hostname);
    } else {
        data->result = strdup(username);
    }
    return 0;
}
