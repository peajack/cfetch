#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *die(char *why) {
    perror(why);
    exit(1);
}

char *strdup(const char *s) {
#ifndef HAS_STRDUP
    size_t size = strlen(s) + 1;
    char *result = malloc(size);
    if (result == NULL)
        die("malloc");
    memcpy(result, s, size);
    return result;
#else
    return strdup(s);
#endif /* HAS_STRDUP */
}

char *basename(char *path) {
	char *s = strrchr(path, '/');
	if (!s)
		return s;
	else
		return s + 1;
}

