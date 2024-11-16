#include "shell.h"
#include "../util.h"
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

void *shell(void *arg) {
	struct data *data = (struct data *)arg; 
	data->label = "SHELL";
	
	char *env;
	if ((env = getenv("SHELL")) != NULL) {
		data->result = strdup(basename(env));
		return 0;
	}
	//pid_t ppid = getppid();
	//data->result = "idk";
	return 0;
}
