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
		data->result = basename(env);
	}
	//pid_t ppid = getppid();
	//data->result = "idk";
	
	data->result = strdup(data->result);
	return 0;
}
