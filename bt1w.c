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

	if(atoi(argv[1]) <=3 || argc > 2){
		printf("Doi so khong phu hop\n");
		return;
	}
	
	key_t key;
	int msgid;

	key = ftok("msg.txt",1);

	msgid = msgget(key,0666 | IPC_CREAT);
	
	message.mes_type = 1;
	message.mes = atoi(argv[1]);

	msgsnd(msgid, &message, sizeof(message),0);
	
	printf("Data send: %d\n",message.mes);

	msgrcv(msgid, &message, sizeof(message),1,0); // nhan kq

	printf("%d! = %d\n",atoi(argv[1]),message.mes);

	msgctl(msgid,IPC_RMID,NULL);

	return 0;
}
