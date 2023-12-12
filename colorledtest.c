#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main(int argc, char *argv[]){
	pwmLedInit();
	pwmSetPercent(20,0);
	printf("pwmSetPercent(20,0)\n");
	sleep(3);
	pwmSetPercent(40,1);
	printf("pwmSetPercent(40,1)\n");
	sleep(3);
	pwmSetPercent(60,2);
	printf("pwmSetPercent(60,2)\n");
	sleep(3);
	pwmInactiveAll();
	return 0;
}
