#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SIZE 256

int giaithua(int n){
	int res = 1;
	if(n==0){
		return 1;
	}
	
	int i;

	for(i =1; i<=n; i++){
		res = res * i;
	}

	return res;
}



int main(int argc, char* argv[]){


	int *shm, shmid,k,pid;

	key_t key;

	if((key =ftok(".",1)) == -1){
		
		perror("Key created.\n");
		return 1;
	}

	shmid = shmget(key, SIZE, IPC_CREAT | 0666);
	if(shmid == -1){
		perror ("Shared memory created.\n");
		return 2;

	}
	
	shm = (int *) shmat(shmid, 0,0);

	pid = fork();

	if(pid == 0){
		sleep(2);
		
		int temp= shm[0];		

		printf("Doc data: %d\n",temp);

		shm[1] = giaithua(temp);
		
		shmdt((void*) shm);
		sleep(5);
		return 0; 

	}
	else{
		if(pid > 0){
			shm[0] = atoi(argv[1]);
			sleep(3);
			printf("%d! = %d\n",atoi(argv[1]), shm[1]);
			shmdt((void*) shm);
			shmctl(shmid, IPC_RMID,(struct shmid_ds*)0);
			return 0;
			
		}

	}
	
	return 0;
}

