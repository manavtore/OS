#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int compare(const void* num1, const void* num2){
	int a = *(int*) num1;
	int b = *(int*) num2;
	if(a > b){
		return 1;
	} else if(a < b){
		return -1;
	} else {
		return 0;
	}
}

int main() {

	int a[8],i;
	printf("Enter integers : \n");
	for(i=0; i<8; i++){
		printf("Enter integer %d\n", i+1);
		scanf("%d", &a[i]);
	}

	qsort(a, 8, sizeof(int), compare);

	char str[128];
	int j=0;
	int index=0;
	for(j=0; j<8; j++) {
		index += sprintf(&str[index], "%d ", a[j]);
	}

	char *cmd = "./bina";
	char *argu[3] = {"./bina", str, NULL};

	pid_t pid;

	pid=fork();

	if(pid < 0) {
		fprintf(stderr, "Failed Fork");
	} else if(pid == 0) {
		printf("Child Process : %d\n", getpid());
		sleep(15);
	} else if(pid > 0){
		printf("Parent Process : %d\n", getppid());
		execvp(cmd, argu);
		sleep(15);
	}

	return 0;
}