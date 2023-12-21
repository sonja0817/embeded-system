#include "button.h"
#include "buzzer.h"
#include "fnd.h"
#include "led.h"
#include "lcdtext.h"
#include "projectheader.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include "jpgViewer.h"
//#include <pthread.h>
//#define MUTEX_ENABLE 0

//pthread_mutex_t lock;
pthread_t tid[2];

int main(void){
	//buttonInit();
	pthread_create(&tid[0],NULL,&jpgViewer,NULL);
	pthread_create(&tid[1],NULL,&clock_1,NULL);
	BuzzerInit();
	ledLibInit();
	//int msgID = msgget (MESSAGE_ID, IPC_CREAT | 0666);
	//BUTTON_MSG_T recvdMsg;
	int level;
	int check;
	int beforelevel=100;
	char c='1';
	int fp;
	int fp2;
	int cnt=0;
	while(1)
	{	fp2=open("/home/ecube/level.txt",O_RDWR|O_CREAT,0666);
		read(fp2,&level,4);
		close(fp2);
		printf("%d",level);
	//	if(level == 8){
	//		if(check == 0)
	//		{
	//			ledOnOff_1(8);
	//			buzzer_density(level);
	//			check = 1;
	//		}
	//		else if(check == 1)
	//		{
	//			ledOnOff_1(0);
	//			buzzer_density(level);
	//			check = 0;
	//		}		
			
	//	}
	//	else{
		ledOnOff_1(level);
	//	}
		buzzer_density(level);
		if(level!=beforelevel){
			lcdtext_density(level);
		//	buzzer_density(level);
		}
		if(level >=2){
			if(level!=beforelevel || cnt == 10){
				fp = open("/home/ecube/check.txt",O_RDWR|O_CREAT,0666);
                       		        write(fp,&c,sizeof(c));
                        	        //printf("check write complete");
                 	      	        close (fp);
					cnt = 0;
			}
			else cnt++;
		}
		beforelevel=level;
		
		//if(msgrcv(msgID,&recvdMsg,sizeof(BUTTON_MSG_T)-sizeof(long int),0,IPC_NOWAIT)>=0)
		//{
			//if(recvdMsg.keyInput == 102){
				//printf("before open level.txt");
				//fp = open("/home/ecube/level.txt",O_RDWR|O_CREAT,0666);
				//read(fp,&level,4);
				//close(fp);
				//printf("level.txt<-leadcomplete");
				//ledOnOff_1(level);
				//buzzer_density(level);
				//lcdtext_density(level);
		usleep(1000);
	}
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	//pthread_join(tid[2],NULL);
	ledLibExit();
	BuzzerExit();
	buttonExit();

}
