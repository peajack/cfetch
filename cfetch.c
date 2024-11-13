#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cfetch.h"
#include "config.h"
#include "logos.h"

int main() {
    int len = sizeof(blocks) / sizeof(struct data);
    
	char *os_name = "";
	pthread_t threads[len + 1];
    struct data results[len + 1];

    for (int i = 0; i < len; i++) {
        struct block block = blocks[i];
        results[i].flags = block.flags;
        pthread_create(&threads[i], NULL, block.func, &results[i]);
		if (block.func == os) {
			pthread_join(threads[i], NULL);
			threads[i] = (pthread_t)NULL;
		}
    }

	if (strlen(os_name) == 0) {
		pthread_create(&threads[len], NULL, os, &results[len]);
		pthread_join(threads[len], NULL);
		os_name = results[len].result;
	}

#if HAS_LOGO == 1
	char **logo = get_logo(os_name);

	int max = (len > 8) ? len : 8;

    for (int j = 0; j < max; j++) {
		if (j < len) {
			if (threads[j]) // 'cause we nulled some field before
				pthread_join(threads[j], NULL);
			if (j == 0) // first field is shown as header
				printf("%s" BOLD " %s\n" RESET, logo[j], results[j].result);
			else {
				if (j <= 8) // if we are still showing logo
					printf("%s" BOLD " %s" RESET "\t%s\n",
						   logo[j], results[j].label, results[j].result);
				else {
					// logo ended, add whitespaces
					printf("%*c" BOLD " %s" RESET "\t%s\n",
						   (int)(strlen(logo[8])), ' ',
						   results[j].label,
						   results[j].result);
				}
			}
		} else {
			// no fields left, print only logo
			if (logo[j] == NULL)
				break;
			printf("%s\n", logo[j]);
		}
    }
#else
	for (int j = 0; j < len; j++) {
		if (threads[j])
			pthread_join(threads[j], NULL);
		if (j == 0)
			printf("%s\n", results[j].result);
		else
			printf("%s\t%s\n", results[j].label, results[j].result);
	}
#endif // HAS_LOGO

}
