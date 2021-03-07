#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
	if(argc != 2) {
		printf("please input one argument\n");
		exit(1);
	}

	char *time = argv[1];

	int timeInt = atoi(time);

	sleep(timeInt);
	exit(0);
}
