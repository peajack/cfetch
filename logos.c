#include "logos.h"
#include "cfetch.h"
#include <string.h>
#include <stdlib.h>

#define BLUE "\033[1;34m"
#define RESET "\033[0;m"

char **get_logo(char *os) {
	char **logo = malloc(sizeof(char *) * 9);
#ifdef __linux__
	if (strncmp(os, "Arch Linux", 10) == 0) {
		logo[0] = BLUE "      /\\      " RESET;
		logo[1] = BLUE "     /  \\     " RESET;
		logo[2] = BLUE "    /    \\    " RESET;
		logo[3] = BLUE "   /      \\   " RESET;
		logo[4] = BLUE "  /   ,,   \\  " RESET;
		logo[5] = BLUE " /   |  |  -\\ " RESET;
		logo[6] = BLUE "/_-''    ''-_\\" RESET;
		logo[7] = "              ";
		logo[8] = "              ";
	}
#endif // linux
	return logo;
}
