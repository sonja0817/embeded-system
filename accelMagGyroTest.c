#include <stdio.h>
#include <stdlib.h>
#include "accelMagGyro.h"

int main(void){
	int accel[3];
	int mag[3];
	int gyro[3];


	while(1){
	Accel(&accel[0],&accel[1],&accel[2]);
	Mag(&mag[0],&mag[1],&mag[2]);
	Gyro(&gyro[0],&gyro[1],&gyro[2]);

	printf("accel x:%d, y:%d, z:%d\n\r",accel[0],accel[1],accel[2]);
	printf("Mag x:%d, y:%d, z:%d\n\r",mag[0],mag[1],mag[2]);
	printf("Gyro x:%d, y:%d, z:%d\n\r",gyro[0],gyro[1],gyro[2]);

	sleep(3);
	}
}
