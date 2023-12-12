#include "lcdtext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	char a[10]="hi!niceto";
	char b[10]="meet you";
	lcdtextwrite(&a[0],2);
	printf("%s\n",a);
	sleep(1);
	lcdtextwrite(&b[0],2);
	printf("%s\n",b);
}
