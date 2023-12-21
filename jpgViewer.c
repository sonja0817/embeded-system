#include <stdio.h>
#include <stdlib.h>
#include <sys/kd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <pthread.h>
#include "./libfbdev.h"
#include "./jpeglib.h"
#include "jpgViewer.h"

int jpgViewer(void)
{
    int screen_width;
    int screen_height;
    int bits_per_pixel;
    int line_length;
    int cols = 0, rows = 0;
	char *data;
	FILE *fp;
	int fp2;	
	int imagesavecheck=1;
//FrameBuffer init
    if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
	{
		printf ("FrameBuffer Init Failed\r\n");
		return 0;
	}
	
	int conFD = open ("/dev/tty0", O_RDWR);
	ioctl(conFD, KDSETMODE, KD_GRAPHICS);
	close (conFD);
	
	//Clear FB.
	fb_clear();
	int count=0;
	while(1){
	//FileRead
	int error=0;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
 	cinfo.err = jpeg_std_error(&jerr);
	
	jpeg_create_decompress(&cinfo);
	while(1){
	//#if MUTEX_ENABLE
	//pthread_mutex_lock(&lock);
	//#endif
	fp2=open("/home/ecube/imgsavecheck.txt",O_RDWR);
	read(fp2,&imagesavecheck,4);
	close(fp2);
	if(imagesavecheck==1)break;
	}
	
	
	fp = fopen("/home/ecube/Coin1.jpg", "rb");
	if(fp==NULL){
		fclose(fp);
		continue;
	}
//	fseek(fp,0,SEEK_END);
//	long file_size=ftell(fp);
//	if(file_size==0){
//		fclose(fp);
//		continue;
//	}
//	fseek(fp,0,SEEK_SET);
	jpeg_stdio_src(&cinfo, fp);
	jpeg_read_header(&cinfo, TRUE); 
	//printf ("JPG %d by %d by %d, %d\n",
	//	cinfo.image_width,cinfo.image_height,cinfo.num_components, cinfo.output_scanline);
	cols = cinfo.image_width;
	rows = cinfo.image_height;
	if(count==0){
		data = malloc(cols*rows*3);
		count++;
	}
	int currPoint = 0;
	jpeg_start_decompress(&cinfo);
	while(cinfo.output_scanline < cinfo.output_height) 
	{
		//printf ("CInfoScanlines:%d\r\n",cinfo.output_scanline);
		char *tempPtr=&data[currPoint];
		jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&tempPtr, 1);
		currPoint+=cols*3;
	}
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(fp);

	fb_write_reverse(data, cols,rows);
	//free(data);
	usleep(10);
//	#if MUTEX_ENABLE
	//pthread_mutex_unlock(&lock);
	//#endif

}
	free(data);
	fb_close();

    return 0;
}
