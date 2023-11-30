all:libMyPeri.a
libMyPeri.a:led.o buzzer.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o buzzer.o

led.o: led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o
buzzertest:buzzer.h buzzer.c buzzertest.c
	arm-linux-gnueabi-gcc -o buzzertest buzzertest.c buzzer.c -Wall

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

