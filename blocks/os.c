#include "os.h"

void *os(void *args) {
	struct data *data = (struct data *)args;
	data->label = "OS";
	data->result = "Arch Linux";	
	return 0;
}
