#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define R 0
#define W 1

void redirect(int rw, int fd[]) {
	close(rw);
	dup(fd[rw]);
	close(fd[rw]);
}

int filter(int infd) {
	int p;
	int outfd[2];
	if(read(infd, &p, sizeof(p))) {
		printf("prime %d\n", p);

		pipe(outfd);

		int id=fork();
		if(id == 0) {
			redirect(R, outfd);
			close(outfd[W]);
			filter(R);
		}else {
			int n;
			redirect(W, outfd);
			close(outfd[R]);
			while(read(infd, &n, sizeof(n))) {
				if(n%p != 0) {
					write(W, &n, sizeof(n));
				}
			}
			close(W);
			wait(0);
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	int ffd[2];

	pipe(ffd);

	int id = fork();
	if(id == 0) {
		redirect(R, ffd);
		close(ffd[W]);
		filter(R);
	}else {
		redirect(W, ffd);
		close(ffd[R]);
		for(int i=2; i<36; i++) {
			write(W, &i, sizeof(i));
		}
		close(W);
		wait(0);
	}
	exit(0);
}
