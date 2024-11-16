#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *die(char *why) {
    perror(why);
    exit(1);
}

char *strdup(const char *s) {
    char *result = malloc(strlen(s) + 1);
    if (result == NULL)
        die("malloc");
    strcpy(result, s);
    return result;
}

char *basename(char *path) {
	char *s = strrchr(path, '/');
	if (!s)
		return s;
	else
		return s + 1;
}

