#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<linux/input.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<sys/msg.h>
#include<dirent.h>
#include"buzzer.h"

#define MAX_SCALE_STEP 8
#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"
int buzzerEnablefd=0;
int buzzerFrequencyfd=0;
char buzzerEnablePath[200];
char buzzerFrequencyPath[200];
char gBuzzerBaseSysDir[128];
const int musicScale[MAX_SCALE_STEP]={
	262,294,330,349,392,440,494,523}; //도레미파솔라시도

int findBuzzerSysPath(){
	DIR * dir_info=opendir(BUZZER_BASE_SYS_PATH);
	int ifNotFound=1;
	if(dir_info!=NULL){
		while(1){
			struct dirent *dir_entry;
			dir_entry=readdir(dir_info);
			if(dir_entry==NULL)break;
			if(strncasecmp(BUZZER_FILENAME,dir_entry->d_name,strlen(BUZZER_FILENAME))==0){
				ifNotFound=0;
				sprintf(gBuzzerBaseSysDir,"%s%s/",BUZZER_BASE_SYS_PATH,dir_entry->d_name);
			}
		}
	}
	printf("find%s\n",gBuzzerBaseSysDir);
	return ifNotFound;
}

void buzzerEnable(int bEnable){
	if(bEnable){
		write(buzzerEnablefd,&"1",1);
	}
	else{
		write(buzzerEnablefd,&"0",1);
	}
}

void setFrequency(int frequency){
	dprintf(buzzerFrequencyfd,"%d",frequency);
}

int buzzerInit(void){
	if(findBuzzerSysPath()==0){
		sprintf(buzzerEnablePath,"%s%s",gBuzzerBaseSysDir,BUZZER_ENABLE_NAME);
	        buzzerEnablefd=open(buzzerEnablePath,O_WRONLY);
	        
	        sprintf(buzzerFrequencyPath,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
		buzzerFrequencyfd=open(buzzerFrequencyPath,O_WRONLY);
		printf("buzzerinit끝");
	}
	else{
		printf("error");
	}
	
}

int buzzerPlaySong(int scale){
	setFrequency(musicScale[scale-1]);  //scale-1이 0이면 도,scale-1이 1이면 레 
	buzzerEnable(1);
	
}
int buzzerStopSong(void){
	buzzerEnable(0);
	
}
int buzzerExit(void){
	buzzerEnable(0);
	close(buzzerEnablefd);
	close(buzzerFrequencyfd);

}



