#include"buzzer.h"
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
int main (void){
	buzzerInit();
    printf("\n");
	for(int i=1;i<9;i++){ //도레미파솔라시도순으로 부저울림 각각1초씩
        printf("for\n");
		 buzzerPlaySong(i);
	        sleep(1);	
	}
	buzzerStopSong();
    printf("stopsongend\n");
	buzzerExit();
    printf("종료");
	return 0;
}
