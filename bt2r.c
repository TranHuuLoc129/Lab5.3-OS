#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


struct mesg_buffer{
	long mes_type;
	char mes[100];

}message;

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

	
	key_t key;
	int msgid;

	key = ftok("msg.txt",1);

	msgid = msgget(key,0666 | IPC_CREAT);

	msgrcv(msgid, &message, sizeof(message),1,0); //nhan du lieu
	
	printf("Data recieved: %s\n",message.mes);

	//tinh toan
	int a,b;
	int kq;
	char tmp,c;
	char str1[10], str2[10],str3[10];
		    
	char *p;
	p = strtok(message.mes," ");
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
			if(b==0){
			      kq = 0;	
			}
			else{
		             kq = a/b;
			}
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
	while(kq>=10){	
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

	strncpy(message.mes,res,100); 
					
	msgsnd(msgid, &message, sizeof(message),0); // gui kq

	printf("Data send: %s\n",res);

	return 0;
}
