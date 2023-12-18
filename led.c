#include "led.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static unsigned int ledValue =0;
static int fd =0;
int ledOnOff(int ledNum,int onOff)
{
	int i=1;
	i=i<<ledNum;
	ledValue =ledValue & (~i);
	if(onOff != 0) ledValue |= i;
	write (fd,&ledValue,4);
}

int ledOnOff_1(int Num){
	int j=1;
	if(Num==0)j=0;
	else{
		for(int i=1;i<Num;i++){
			j=(j<<1)+1;
		}
	}
	ledValue = j;
	write(fd,&ledValue,4);
}

int ledLibInit(void)
{
	fd=open("/dev/periled",O_WRONLY);
	ledValue=0;
}
int ledLibExit(void)
{
	ledValue = 0;
	ledOnOff(0,0);
	close(fd);
}

int ledStatus(void)
{
	printf("%d",ledValue);
}
