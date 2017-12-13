// Change PCX Palette - Cyril BARBATO 2017
// * DISCLAIMER OF ALL WARRANTIES *
#include <stdio.h>
typedef struct _PixColorStr
{
   unsigned char r, g, b;
} PixColorStr;

int main(int argc , char **argv) {
	FILE *palfptr, *srcfptr, *destfptr;
	char linebuffer[1024];
	char *destbuffer;
	PixColorStr pixelcolor;
	int n=0;
	long int srcfilesize;
   if (argc!=3) {
		printf("\nChPal for Change PCX Palette (2017) Cyril BARBATO\n\n");
		printf("Usage :\n\n");
		printf("      chpal [palette.txt] [src_image.pcx] > [dest_image.pcx]\n\n");
		return 1;
	   
   }
   // Open pal txt reference
   if ((palfptr = fopen(argv[1],"r")) == NULL){
       printf("Error! opening pal file");
		return(1);
   }
   // Open src file
   if ((srcfptr = fopen(argv[2],"rb")) == NULL){
       printf("Error! opening src file");
		return(1);
   }
	// Calculate size of source file
	fseek(srcfptr, 0, SEEK_END);
	srcfilesize = ftell(srcfptr);
	// return to begin
	fseek(srcfptr, 0, SEEK_SET);
	printf("Src File Size : %d\n", srcfilesize);
	// Reserve buffer memory
	destbuffer = (char*) malloc (sizeof(char)*(srcfilesize+3));
	// Open dest file
	if ((destfptr = fopen("test.pcx","wb")) == NULL){
       printf("Error! opening dest file");
		return(1);
   }
	// Copy file src to dest
    fread(destbuffer, sizeof(char), srcfilesize,  srcfptr);
	printf("Src Ptr : %d\n", ftell(srcfptr));
	fwrite(destbuffer, sizeof(char), srcfilesize, destfptr);
	printf("Dest Ptr : %d\n", ftell(destfptr));
	
	// Rewind from start parlette
	fseek(destfptr, srcfilesize - 256 * sizeof(PixColorStr), SEEK_SET);
	
	// Write palette to dest file
	printf("Write palette\n");
	char *cptr;
	while (fgets(linebuffer, 255, (FILE*) palfptr)) {
		pixelcolor.r = (unsigned char) atoi(linebuffer);
		cptr = linebuffer;
		while (*cptr!=' ') cptr++;
		pixelcolor.g = (unsigned char) atoi(cptr++);
		while (*cptr!=' ') cptr++;
		pixelcolor.b = (unsigned char) atoi(cptr);
		printf("n %d, %d %d %d\n", n++, pixelcolor.r, pixelcolor.g, pixelcolor.b);
		fwrite(&pixelcolor, sizeof(PixColorStr), 1, destfptr);
	}
	printf("Done");
	free(destbuffer);
	fclose(palfptr);
	fclose(srcfptr);
	fclose(destfptr);
  
   return 0;
}
