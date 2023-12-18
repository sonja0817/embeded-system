#include "lcdtext.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define LINE_NUM 2
#define COLUMN_NUM 16
#define LINE_BUFF_NUM (COLUMN_NUM +4)
#define MODE_CMD 0
#define MODE_DATA 1
#define TEXTLCD_DRIVER_NAME "/dev/peritextlcd"

#define CMD_DISPLAY_MODE 0x10

#define CMD_WRITE_STRING 0x20
#define CMD_DATA_WRITE_BOTH_LINE 0
#define CMD_DATA_WRITE_LINE_1 1
#define CMD_DATA_WRITE_LINE_2 2

typedef struct TextLCD_tag
{
	unsigned char cmd;
	unsigned char cmdData;
	unsigned char reserved[2];
	char TextData[LINE_NUM][LINE_BUFF_NUM];
}stTextLCD,*pStTextLCD;

int lcdtextClear(void){
	stTextLCD stlcd;
	int fd;
	memset(&stlcd,0,sizeof(stTextLCD));
	stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
	stlcd.cmd = CMD_WRITE_STRING;
	fd=open(TEXTLCD_DRIVER_NAME,O_RDWR);
	if(fd<0){
		perror("driver open error\n");
		return 1;
	}
	write(fd,&stlcd,sizeof(stTextLCD));
	stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
	stlcd.cmd = CMD_WRITE_STRING;
	write(fd,&stlcd,sizeof(stTextLCD));
	close(fd);
	return 0;
}

int lcdtextwrite(const char *str, int lineFlag){
	stTextLCD stlcd;
	int fd;
	int len;
	memset(&stlcd,0,sizeof(stTextLCD));
	if(lineFlag == 1)
		stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
	else if (lineFlag ==2)
		stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
	else {
		printf("WRONG LINE\n\r");
		return 1;
	}
	len = strlen(str);
	if (len > COLUMN_NUM)
		memcpy(stlcd.TextData[stlcd.cmdData -1],str,COLUMN_NUM);
	else
		memcpy(stlcd.TextData[stlcd.cmdData -1],str,len);

	stlcd.cmd = CMD_WRITE_STRING;
	fd =open(TEXTLCD_DRIVER_NAME,O_RDWR);
	if(fd<0){
		perror("driver open error\n");
		return 1;
	}
	write(fd,&stlcd,sizeof(stTextLCD));
	close(fd);
	return 0;
}


