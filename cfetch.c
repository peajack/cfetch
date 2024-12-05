#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cfetch.h"
#include "config.h"
#include "logos.h"

#define BLOCKS_LEN sizeof(blocks) / sizeof(struct block)

int main(void) {
    int i, j, k;
    int label_length = 0;
    char *os_name;
    pthread_t threads[BLOCKS_LEN + 1];
    struct data results[BLOCKS_LEN + 1];
#if HAS_LOGO == 1
    int l;
    int logo_lines = 0;
    int line_length;
    int max;
    char *logo[MAX_LOGO_LINES + 1] = {0};
#endif
    os_name = "";

    printf("\n"); /* just an empty line okay? */

    for (i = 0; i < BLOCKS_LEN; i++) {
        struct block block = blocks[i];
        results[i].flags = block.flags;
        if ((pthread_create(&threads[i], NULL,
                            block.func, &results[i])) != 0) {
            threads[i] = (pthread_t)NULL;
        }
        if (block.func == os) {
            pthread_join(threads[i], NULL);
            os_name = results[i].result;
            threads[i] = (pthread_t)NULL;
        }
    }

    if (!os_name) {
        if ((pthread_create(&threads[BLOCKS_LEN], NULL,
                            os, &results[BLOCKS_LEN])) == 0) {
            pthread_join(threads[BLOCKS_LEN], NULL);
            os_name = results[BLOCKS_LEN].result;
        }
    }

    for (k = 0; k < BLOCKS_LEN; k++) {
        if (threads[k]) {
            pthread_join(threads[k], NULL);
            if (label_length < strlen(results[k].label))
                label_length = strlen(results[k].label);
        }
    }

#if HAS_LOGO == 1
    get_logo(logo, os_name);

    for (l = 0; l < MAX_LOGO_LINES; l++) {
        if (logo[l] == NULL)
            break;
        logo_lines++;
    }

    line_length = (int)strlen(logo[logo_lines - 1]);
    max = (BLOCKS_LEN > logo_lines) ? BLOCKS_LEN : logo_lines;

    for (j = 0; j < max; j++) {
        if (j < BLOCKS_LEN) {
            if (j == 0) {
                /* first field is shown as header */
                printf("%s" BOLD " %s\n" RESET,
                       logo[j],
                       results[j].result);
            } else {
                int spaces = label_length - strlen(results[j].label) + 1;
                if (j < logo_lines) /* if we are still showing logo */
                    printf("%s" BOLD " %s" RESET "%*c%s\n",
                           logo[j],
                           results[j].label,
                           spaces, ' ',
                           results[j].result);
                else /* logo ended, add whitespaces */
                    printf("%*c" BOLD " %s" RESET "%*c%s\n",
                           line_length, ' ',
                           results[j].label,
                           spaces, ' ',
                           results[j].result);
            }
            free(results[j].result);
        } else {
            /* no fields left, print only logo */
            if (logo[j] == NULL)
                break;
            printf("%s\n", logo[j]);
        }
    }
#else
    for (j = 0; j < BLOCKS_LEN; j++) {
        if (threads[j])
            pthread_join(threads[j], NULL);
        if (j == 0)
            printf(BOLD "%s\n" RESET, results[j].result);
        else {
            int spaces = label_length - strlen(results[j].label) + 1;
            printf(BOLD "%s" RESET "%*c%s\n",
                   results[j].label,
                   spaces, ' ',
                   results[j].result);
        }
    }
#endif /* HAS_LOGO */
    printf("\n");
    return 0;
}
