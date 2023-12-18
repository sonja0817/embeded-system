#include <stdio.h>
#include "buzzer.h"
#include "lcdtext.h"
#include <stdlib.h>



int buzzer_density(int level){
	if(level<3){
		buzzerStopSong();
	}
	else if(level >=3){
		buzzerPlaySong(1);
	}
	else if(level >=6){
		buzzerPlaySong(2);
	}
}

int lcdtext_density(int level){
	char mes1[8]="warning";
	char mes2[8]="danger";
	if(level<3){
		lcdtextClear();
	}
	else if(level>=3){
		lcdtextClear();
		lcdtextwrite(mes1,1);
	}
	else if(level>=6){
		lcdtextClear();
		lcdtextwrite(mes2,1);
	}
}

