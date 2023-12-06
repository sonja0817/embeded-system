#include "led.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
	ledLibInit();
	for(int i=0;i<8;i++){
		ledOnOff(i,1);
		printf("%d on\r\n",i);
		sleep(1);
	}

	ledStatus();
	ledLibExit();
	return 0;
}
