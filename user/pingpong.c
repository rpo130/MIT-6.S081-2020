#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
	int ppf[2];
	int cpf[2];
	
	if(pipe(ppf) != 0) {
		printf("pipe(ppf) error");
		exit(1);
	}
	if(pipe(cpf) != 0) {
		printf("pipe(cfp) error");
	}


	int id = fork();
	if(id == 0) {
		int pid = getpid();

		char buf;
		if(read(cpf[0], &buf, 1) > 0) {
			printf("%d: received ping\n", pid);
		}else {
			exit(1);
		}
		if(write(ppf[1], "p", 1) <= 0) {
			exit(1);
		}
	}else {
		int pid = getpid();

		char buf;
		if(write(cpf[1], "p", 1)<=0) {
			exit(1);
		}
		if(read(ppf[0], &buf, 1) > 0) {
			printf("%d: received pong\n", pid);
		}else {
			exit(1);
		}

	}
	exit(0);
}
