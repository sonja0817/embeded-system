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

pthread_t tid[2];

int main(void){
	pthread_create(&tid[0],NULL,&jpgViewer,NULL);
	pthread_create(&tid[1],NULL,&clock_1,NULL);
	buttonInit();
	BuzzerInit();
	ledLibInit();
	int msgID = msgget (MESSAGE_ID, IPC_CREAT | 0666);
	BUTTON_MSG_T recvdMsg;
	int level;
	int c=1;
	int fp;

	while(1)
	{
		if(msgrcv(msgID,&recvdMsg,sizeof(BUTTON_MSG_T)-sizeof(long int),0,IPC_NOWAIT)>=0)
		{
			if(recvdMsg.keyInput == 102){
				fp = open("/home/ecube/level.txt",O_RDWR|O_CREAT,0666);
				read(fp,&level,4);
				close(fp);
				ledOnOff_1(level);
				buzzer_density(level);
				lcdtext_density(level);
				fp = open("/home/eucbe/check.txt",O_RDWR|O_CREAT,0666);
				write(fp,&c,4);
				close (fp);
			}//very left
			else if(recvdMsg.keyInput == 158){
				break;
			}
		}
		usleep(1000);
	}
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	ledLibExit();
	BuzzerExit();
	buttonExit();

}
