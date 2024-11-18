#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cfetch.h"
#include "config.h"
#include "logos.h"
#include "util.h"

int main(void) {
    printf("\n"); // just an empty line okay?

    int blocks_len = sizeof(blocks) / sizeof(struct block);
    char *logo[MAX_LOGO_LINES+1] = {0};
    char *os_name = "";
    pthread_t threads[blocks_len + 1];
    struct data results[blocks_len + 1];

    for (int i = 0; i < blocks_len; i++) {
        struct block block = blocks[i];
        results[i].flags = block.flags;
        if ((pthread_create(&threads[i], NULL, block.func, &results[i])) != 0) {
            threads[i] = (pthread_t)NULL;
        }
        if (block.func == os) {
            pthread_join(threads[i], NULL);
            os_name = results[i].result;
            threads[i] = (pthread_t)NULL;
        }
    }

    if (strlen(os_name) == 0) {
        if ((pthread_create(&threads[blocks_len], NULL, os,
                            &results[blocks_len])) == 0) {
            pthread_join(threads[blocks_len], NULL);
            os_name = results[blocks_len].result;
        }
    }

#if HAS_LOGO == 1
    get_logo(logo, os_name);

	int logo_lines = 0;
	for (int k = 0; k < MAX_LOGO_LINES; k++) {
		if (logo[k] == NULL)
			break;
		logo_lines++;
	}

    int max = (blocks_len > logo_lines) ? blocks_len : logo_lines;

    for (int j = 0; j < max; j++) {
        if (j < blocks_len) {
            if (threads[j]) // 'cause we nulled some field before
                pthread_join(threads[j], NULL);
            if (j == 0) // first field is shown as header
                printf("%s" BOLD " %s\n" RESET, logo[j], results[j].result);
            else {
                if (j < logo_lines) // if we are still showing logo
                    printf("%s" BOLD " %s" RESET "\t%s\n", logo[j],
                           results[j].label, results[j].result);
                else // logo ended, add whitespaces
                    printf("%*c" BOLD " %s" RESET "\t%s\n",
                           (int)(strlen(logo[logo_lines-1])), ' ',
						   results[j].label,
                           results[j].result);
            }
            free(results[j].result);
        } else {
            // no fields left, print only logo
            if (logo[j] == NULL)
                break;
            printf("%s\n", logo[j]);
        }
    }
#else
    for (int j = 0; j < blocks_len; j++) {
        if (threads[j])
            pthread_join(threads[j], NULL);
        if (j == 0)
            printf(BOLD "%s\n" RESET, results[j].result);
        else
            printf(BOLD "%s\t" RESET "%s\n", results[j].label,
                   results[j].result);
    }
#endif // HAS_LOGO
	printf("\n"); // just an empty line
}
