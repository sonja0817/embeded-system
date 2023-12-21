#include <stdio.h>
#include "buzzer.h"
#include "lcdtext.h"
#include "fnd.h"
#include <time.h>
#include <stdlib.h>

int clock_1(void){
	int number;
	struct tm *ptmcur;
	time_t tTime;
	while(1){
		if(-1==time(&tTime))
			return -1;
		ptmcur = localtime(&tTime);
		number = ((ptmcur -> tm_hour)+9) *10000;
		if(number>240000){
			number=number-240000;
		}
		number += ptmcur -> tm_min *100;
		number += ptmcur ->tm_sec;
		fndDisp(number,0b1010);
		sleep(1);
	}
}

int buzzer_density(int level){
	if(level<=2){
		//buzzerPlaySong(1);
		//usleep(100);
		buzzerStopSong();
	}
	else if(level <=4){
		buzzerPlaySong(2);
		//usleep(100);
		//buzzerStopSong();
	}
	else if(level <=6){
		buzzerPlaySong(3);
		//usleep(100);
		//buzzerStopSong();
	}
	else {
		buzzerPlaySong(4);
		//usleep(100);
		//buzzerStopSong();
	}
}


int lcdtext_density(int level){
	char mes0[8]="notice";
	char mes1[8]="caution";
	char mes2[8]="warning";
	char mes3[8]="danger";
	if(level==0){
		lcdtextClear();
	}
	else if(level<=2){
		lcdtextClear();
		lcdtextwrite(mes0,1);
	}
	else if(level<=4){
		lcdtextClear();
		lcdtextwrite(mes1,1);
	}
	else if(level<=6){
		lcdtextClear();
		lcdtextwrite(mes2,1);
	}
	else {
		lcdtextClear();
		lcdtextwrite(mes3,1);
	}
}

