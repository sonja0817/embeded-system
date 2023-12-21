all:libProject.a
libProject.a:led.o buzzer.o button.o fnd.o lcdtext.o projectheader.o jpgViewer.o
	ar rc libProject.a led.o buzzer.o button.o fnd.o lcdtext.o projectheader.o jpgViewer.o

jpgViewer.o:jpgViewer.h jpgViewer.c jconfig.h jmorecfg.h jpeglib.h libfbdev.h
	gcc --static -c -o jpgViewer.o jpgViewer.c -l mylib -L. -l jpeg -L.
projectheader.o: projectheader.h projectheader.c
	gcc --static -c -o projectheader.o projectheader.c
led.o: led.h led.c
	gcc --static -c -o led.o led.c
buzzer.o: buzzer.h buzzer.c
	gcc --static -c -o buzzer.o buzzer.c
button.o: button.h button.c
	gcc --static -c -o button.o button.c
fnd.o:fnd.h fnd.c
	gcc --static -c -o fnd.o fnd.c
lcdtext.o: lcdtext.c lcdtext.h
	gcc --static -c -o lcdtext.o lcdtext.c

