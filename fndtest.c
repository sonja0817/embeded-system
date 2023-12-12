#include "fnd.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int number = 1;
	for(int i=2;i<7;i++){
		fndDisp(number,0b1010);
		printf("%d\n",number);
		number = number + i*10^(i-1);
		sleep(1);
	}	

}

