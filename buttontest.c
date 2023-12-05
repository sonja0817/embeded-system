#include "button.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	printf("start");
	buttonInit();
	for(int i=0;i<1000;i++){
		printf("%d",i);
		sleep(1);
	}
	buttonExit();
}
