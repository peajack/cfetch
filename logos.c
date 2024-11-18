#include "logos.h"
#include "cfetch.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

void get_logo(char *logo[MAX_LOGO_LINES+1], char *os) {
	if (strncmp(os, "unknown", 7) == 0) {
		logo[0] = "     ___     ";
		logo[1] = " ___/   \\___ ";
		logo[2] = "/   '---'   \\";
		logo[3] = "'--_______--'";
		logo[4] = "     / \\     ";
		logo[5] = "    /   \\    ";
		logo[6] = "    /\\O/\\    ";
		logo[7] = "    / | \\    ";
		logo[8] = "    // \\\\    ";
	} 
#if defined(__linux__)
    if (strncmp(os, "Arch Linux", 10) == 0) {
        logo[0] = BLUE "      /\\      " RESET;
        logo[1] = BLUE "     /  \\     " RESET;
        logo[2] = BLUE "    /    \\    " RESET;
        logo[3] = BLUE "   /      \\   " RESET;
        logo[4] = BLUE "  /   ,,   \\  " RESET;
        logo[5] = BLUE " /   |  |  -\\ " RESET;
        logo[6] = BLUE "/_-''    ''-_\\" RESET;
		logo[7] =      "              ";
    } else if (strncmp(os, "Ubuntu", 6) == 0) {
		
	} else if (strncmp(os, "Void Linux", 10) == 0) {
		
	} else if (strncmp(os, "Android", 7) == 0) {
		logo[0] = GREEN "   -o          o-   " RESET;
		logo[1] = GREEN "    +hydNNNNdyh+    " RESET;
		logo[2] = GREEN "  +mMMMMMMMMMMMMm+  " RESET;
		logo[3] = GREEN " dMMm:NMMMMMMN:mMMd " RESET;
		logo[4] = GREEN "hMMMMMMMMMMMMMMMMMMh" RESET;
		logo[5] =       "                    ";
	}
#elif defined(__FreeBSD__)
	logo[0] = RED "/\\,-'''''-,/\\" RESET;
	logo[1] = RED "\\_)       (_/"  RESET;
	logo[2] = RED "|           |"   RESET;
	logo[3] = RED "|           |"   RESET;
	logo[4] = RED " ;         ; "   RESET;
	logo[5] = RED "  '-_____-'  "   RESET;
	logo[6] = RED "             "   RESET;
#elif defined(__OpenBSD__)
	logo[0] = YELLOW "      _____    "   RESET;
	logo[1] = YELLOW "    \\-     -/  "  RESET;
	logo[2] = YELLOW " \\_/         \\ " RESET;
	logo[3] = YELLOW " |        " BOLD "O O" YELLOW " |" RESET;
	logo[4] = YELLOW " |_  <   )  3 )"   RESET;
	logo[5] = YELLOW " / \\         / "  RESET;
	logo[6] = YELLOW "    /-_____-\\  "  RESET;
	logo[7] =        "               ";
#endif // linux
}
