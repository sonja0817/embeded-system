#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define ACCELPATH "/sys/class/misc/FreescaleAccelerometer/"
#define MAGNEPATH "/sys/class/misc/FreescaleMagnetometer/"
#define GYROPATH "/sys/class/misc/FreescaleGyroscope/"

int Accel(int*x,int*y,int*z){
	int fd = 0;
	FILE *fp = NULL;

	fd = open(ACCELPATH "enable", O_WRONLY);
	dprintf(fd,"1");
	close(fd);
	fp = fopen(ACCELPATH "data","rt");
	fscanf(fp,"%d, %d,%d",x,y,z);
	fclose(fp);
	return 0;
}

int Mag(int*x,int*y,int*z){
	int fd= 0;
	FILE *fp = NULL;
	
	fd = open(MAGNEPATH "enable", O_WRONLY);
	dprintf(fd,"1");
	close(fd);
	fp =fopen(MAGNEPATH "data","rt");
	fscanf(fp,"%d,%d,%d", x,y,z);
	fclose(fp);
	return 0;
}

int Gyro(int *x,int *y,int *z){
	int fd=0;
	FILE *fp =NULL;

	fd = open(GYROPATH "enable",O_WRONLY);
	dprintf(fd,"1");
	close(fd);
	fp =fopen(GYROPATH"data","rt");
	fscanf(fp,"%d,%d,%d",x,y,z);
	fclose(fp);
	return 0;
}

