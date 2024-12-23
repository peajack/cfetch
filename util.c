#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAS_STRDUP
#define strdup(s) strdup(s)
#else
#define strdup(s) polyfill_strdup(s)
#endif

void *die(char *why) {
    perror(why);
    exit(1);
}

char *polyfill_strdup(const char *s) {
    size_t size = strlen(s) + 1;
    char *result = malloc(size);
    if (result == NULL)
        die("malloc");
    memcpy(result, s, size);
    return result;
}

char *basename(char *path) {
    char *s = strrchr(path, '/');
    if (!s)
        return s;
    else
        return s + 1;
}
