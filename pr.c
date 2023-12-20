#include "button.h"
#include "buzzer.h"
#include "fnd.h"
#include "led.h"
#include "lcdtext.h"
#include "projectheader.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>

int main(void){
	buttonInit();
	buzzerInit();
	ledLibInit();
	int a=1234;
	char b[10]= "hello";
	int msgID = msgget (MESSAGE_ID, IPC_CREAT | 0666);
	BUTTON_MSG_T recvdMsg;
	int level;
	int c=1;

	while(1)
	{
		if(msgrcv(msgID,&recvdMsg,sizeof(BUTTON_MSG_T)-sizeof(long int),0,IPC_NOWAIT)>=0)
		{
			if(recvdMsg.keyInput == 102){
				//stop and transform
				ledOnOff_1(level);
				buzzer_density(level);
				lcdtext_density(level);
				fp = open("/home/ecube/check.txt",O_RDWR|O_CREAT,0666);
				write(fp,&c,4);
				close (fp);
				fp = open("/home/eucbe/level.txt",O_RDWR|O_CREAT,0666);
				write(fp,&level,4);
				close (fp);
			}//very left
			else if(recvdMsg.keyInput == 158){
				//play
			}
		}
		usleep(1000);
	}
	ledLibExit();
	buzzerExit();
	buttonExit();

}
