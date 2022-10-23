#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SIZE 256


int dem(int n){
	if(n<10){
		return 1;
	}
	int d = 10;
	while(n>100){
		d=d*10;
		n=n/10;
	}
	
	return d;

}

int main(int argc, char* argv[]){


	int  shmid,k,pid;
	char *shm;

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
	
	shm = (char *) shmat(shmid, 0,0);

	pid = fork();

	if(pid == 0){
		    sleep(3);

		    int a,b;
		    int kq;
		    char tmp,c;
		    char str1[10], str2[10],str3[10];
		    
		   char *p;
		   p = strtok(shm," ");
		   strcpy(str1,p);
		   p = strtok(NULL," ");
		   strcpy(str2,p);
		   p = strtok(NULL," ");
		   strcpy(str3,p);

                   a = atoi(str1);
		
		   b = atoi(str2);

                   c  = str3[0];
           	
  
		  switch(c){
			case '+':
				kq = a + b;
				break;	

			case '-':
				kq = a-b;
				break;
			case 'x':
				kq = a*b;
				break;
			case '/':
				kq = a/b;
				break;
		}

		int flag = 1;
		
		if(kq<0){
			kq = kq*(-1);
			flag = 0;
			
		}

		char res[100];
		char s[20];
		
		
		int j = 0;
		int i = dem(kq);
		while(kq>10){	
			char temp = kq/i + 48;
			s[j] = temp;
			j++;
			kq = kq%i;
			i = i/10;
		}
		char temp = kq + 48;
		
		s[j] = temp;
		
		if(flag == 0){
			sprintf(res,"%s %s %s = %s%s",str1,str3,str2,"-",s);
		}
		else{
			sprintf(res,"%s %s %s = %s",str1,str3,str2,s);
		}
		strncpy(shm,res,SIZE);

		shmdt((void*) shm);
		sleep(3);
		return 0; 
	}
	else{
		if(pid > 0){
			char str[40]="";
			int i;
			for(i = 1; i<argc-1; i++ ){
				strcat(str,argv[i]);
				strcat(str," ");
			}

			strcat(str,argv[i]);

			strncpy(shm,str,SIZE);	

			sleep(5);
			
			printf("Ket qua: %s\n", shm);
			shmdt((void*) shm);
			shmctl(shmid, IPC_RMID,(struct shmid_ds*)0);
			return 0;
			
		}
	}

	return 0;
}

