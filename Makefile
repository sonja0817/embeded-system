final.elf : main.c 1.o 2.o 3.o
	gcc -o final.elf main.c 1.o 2.o 3.o

1.o : 1.c myProject.h
	gcc -o 1.o -c 1.c

2.o : 2.c myProject.h
	gcc -o 2.o -c 2.c

3.o : 3.c myProject.h
	gcc -o 3.o -c 3.c
