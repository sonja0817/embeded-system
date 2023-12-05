#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

int fd,msgID;
pthread_t buttonTh_id;
BUTTON_MSG_T msg_t;

int probeButtonPath(char*newPath){
	int returnValue=0;
	int number=0;
	FILE *fp = fopen(PROBE_FILE,"rt");
	while(!feof(fp))
	{
		char tmpStr[200];
		fgets(tmpStr,200,fp);
		if(strcmp(tmpStr,HAVE_TO_FIND_1)==0)
		{
			printf("YES! I found!: %s \r\n",tmpStr);
			returnValue =1;
		}
		if((returnValue ==1)&&(strncasecmp(tmpStr,HAVE_TO_FIND_2,strlen(HAVE_TO_FIND_2))==0))
		{
			printf("-->%s",tmpStr);
			printf("\t%c\r\n",tmpStr[strlen(tmpStr)-3]);
			number = tmpStr[strlen(tmpStr)-3]-'0';
			break;
		}
	}
	fclose(fp);
	if(returnValue ==1)
		sprintf(newPath,"%s%d",INPUT_DEVICE_LIST,number);
	return returnValue;
}
void*buttonThFunc(void*arg);
int buttonInit(void)
{
	char buttonPath[200]={0,};
	if(probeButtonPath(buttonPath)==0)
		return 0;
	fd =open(buttonPath,O_RDONLY);
	msgID=msgget(MESSAGE_ID,IPC_CREAT|0666);
	pthread_create(&buttonTh_id,NULL,&buttonThFunc,NULL);
	//pthread_join(buttonTh_id,NULL);
	return 1;
}

void* buttonThFunc(void *arg){
	int readSize,inputIndex;
	struct input_event stEvent;
	printf("thread on\n");
    while(1){	
    while(1){
		readSize = read(fd,&stEvent,sizeof(stEvent));
		if(readSize != sizeof(stEvent)){
			continue;
		}
		if(stEvent.type == EV_KEY)
		{
			msg_t.keyInput=stEvent.type;
			printf("EV_KEY(\n");
			switch(stEvent.code)
			{
				case KEY_VOLUMEUP: printf("Volume up Key):\n"); break;
				case KEY_HOME: printf("Home Key):");break;
				case KEY_SEARCH: printf("Search key):");break;
				case KEY_BACK: printf("Back key):");break;
				case KEY_MENU: printf("Menu key):");break;
				case KEY_VOLUMEDOWN:printf("Volume down key):");break;
			}
		if(stEvent.value){
			msg_t.pressed = stEvent.value;
			msgsnd(msgID,&msg_t,sizeof(msg_t),0);
			printf("presed\n");
		}
		else printf("released\n");
		}
		else;
	}
    }
	close(fd);
   
}

int buttonExit(void){
	pthread_exit(buttonTh_id);
	//pthread_join(buttonTh_id,NULL);
	printf("exit\n");
}
