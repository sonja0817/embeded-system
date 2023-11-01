final.elf : 1.o 2.o 3.o
gcc -o final.elf 1.o 2.o 3.o

1.o : 1.c myProject.h
gcc -c -o 1.o 1.c

2.o : 2.c myProject.h
gcc -c -o 2.o 2.c

1.o : 1.c myProject.h
gcc -c -o 3.o 3.c
