#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>


struct mesg_buffer{
	long mes_type;
	int mes;

}message;

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

	
	key_t key;
	int msgid;

	key = ftok("msg.txt",1);

	msgid = msgget(key,0666 | IPC_CREAT);


	msgrcv(msgid, &message, sizeof(message),1,0);
	
	printf("Data recieved: %d\n",message.mes);
	

	int kq = giaithua(message.mes);

	message.mes = kq;

	printf("Data send: %d\n",kq);

	msgsnd(msgid, &message, sizeof(message),0); //gui kq


	return 0;
}
