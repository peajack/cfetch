#ifndef CFETCH_LOGOS_H
#define CFETCH_LOGOS_H

#define MAX_LOGO_LINES 9
#define BLUE  "\033[1;34m"
#define RED   "\033[1;31m"
#define RESET "\033[0;m"
#define BOLD  "\033[1;37m"

void get_logo(char *logo[MAX_LOGO_LINES], char *os);

#endif // CFETCH_LOGOS_H
