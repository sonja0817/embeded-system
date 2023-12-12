#include "lcdtext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	char a[10]="hi!niceto";
	lcdtextwrite(&a[0],2);
	while(1){}

}
