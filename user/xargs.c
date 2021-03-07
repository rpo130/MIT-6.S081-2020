#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("error argument");
		exit(1);
	}

	char *args[argc + 1];

	for(int i=0; i < argc -1; ++i) {
		args[i] = argv[i+1];
	}

	int BUFSIZE = 500;
	char buf[BUFSIZE];

	args[argc-1] = buf;
	args[argc] = 0;

	char c;
	int p = 0;

	while(1) {
		int read_size = read(0, &c, 1);
		
		if(read_size < 0) {
			exit(1);
		}

		if(read_size == 0) {
			printf("\n");
			exit(0);
		}


		if(c == '\n') {
			buf[p] = 0;
			//exec
			if(fork() == 0) {
				exec(argv[1], args);
				exit(0);
			}else {
				wait(0);
				p=0;
			}

		}else {
			buf[p++] = c;
		}


	}

	exit(0);
}
