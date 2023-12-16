all:libMyPeri.a
libMyPeri.a:led.o buzzer.o button.o fnd.o lcdtext.o temperature.o accelMagGyro.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o buzzer.o button.o fnd.o lcdtext.o temperature.o accelMagGyro.o

accelMagGyro.o: accelMagGyro.h accelMagGyro.c
	arm-linux-gnueabi-gcc -c accelMagGyro.c -o accelMagGyro.o
accelMagGyroTest: accelMagGyroTest.c
	arm-linux-gnueabi-gcc -o accelMagGyroTest accelMagGyroTest.c -lMyPeri -L.
temperature.o: temperature.h temperature.c
	arm-linux-gnueabi-gcc -c temperature.c -o temperature.o
temperatureTest: temperatureTest.c
	arm-linux-gnueabi-gcc -o temperatureTest temperatureTest.c -lMyPeri -L.
lcdtext.o: lcdtext.h lcdtext.c
	arm-linux-gnueabi-gcc -c lcdtext.c -o lcdtext.o
textlcdtest: textlcdtest.c
	arm-linux-gnueabi-gcc -o textlcdtest textlcdtest.c -lMyPeri -L.

fnd.o: fnd.h fnd.c
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o

led.o: led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o
	
ledtest: ledtest.c
	arm-linux-gnueabi-gcc -o ledtest ledtest.c -lMyPeri -L.
	
button.o: button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o -pthread

buttontest: buttontest.c
	arm-linux-gnueabi-gcc -pthread -o buttontest buttontest.c -lMyPeri -L.

fndtest: fndtest.c
	arm-linux-gnueabi-gcc -o fndtest fndtest.c -lMyPeri -L.

buzzertest: buzzertest.c
	arm-linux-gnueabi-gcc -o buzzertest buzzertest.c -lMyPeri -L.

buzzer.o: buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o

final.elf : main.c 1.o 2.o 3.o
	 gcc -o final.elf main.c 1.o 2.o 3.o

1.o : 1.c myProject.h
	gcc -o 1.o -c 1.c

2.o : 2.c myProject.h
	gcc -o 2.o -c 2.c

3.o : 3.c myProject.h
	gcc -o 3.o -c 3.c

