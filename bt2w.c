#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


struct mesg_buffer{
	long mes_type;
	char mes[100];

}message;


int main(int argc, char* argv[]){
	
	key_t key;
	int msgid;

	key = ftok("msg.txt",1);

	msgid = msgget(key,0666 | IPC_CREAT);
	
	message.mes_type = 1;
	
	char str[40]="";
	int i;
	for(i = 1; i<argc-1; i++ ){
		strcat(str,argv[i]);
		strcat(str," ");
	}

	strcat(str,argv[i]);

	strncpy(message.mes,str,100);

	msgsnd(msgid, &message, sizeof(message),0);

	printf("Data send: %s\n",message.mes);  // gui du lieu

	msgrcv(msgid, &message, sizeof(message),1,0); //nhan ket qua

	printf("Data recieved: %s\n",message.mes);
	
	msgctl(msgid,IPC_RMID,NULL);

	return 0;
}
