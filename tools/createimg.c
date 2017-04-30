/**
 * createimg - source file
 *
 * Helper app that combines bootloader and kernel into one binary image, taking
 * care of proper alignment.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argnum, char *args[])
{

  FILE *out, *in;
  char buffer[512];
  int i;

  if (argnum != 4) {
     printf("Error, you need to have exactly 3 additional parameters:\n\n");
     printf("%s [out.img] [bootloader.bin] [kernel.bin]\n", args[0]);
     exit(1);
  }

  out = fopen(args[1], "wb");

  if (out == NULL) {
     printf("Error, something went wrong. \"%s\"", args[1]);
     exit(1);
  }


  in = fopen(args[2], "rb");

  if (in == NULL) {
     printf("Error, could not open the file \"%s\"", args[2]);
     fclose(out);
     exit(1);
  }

  fread(buffer, 1, 512, in);
  fwrite(buffer, 1, 512, out);

  for(i=0;i<512;i++)
     buffer[i] = 0;

  //NULL sector, needed by the OS
  fwrite(buffer, 1, 512, out);

  in = fopen(args[3], "rb");

  if (in == NULL) {
     printf("Error, could not open the file \"%s\"", args[3]);
     fclose(out);
     exit(1);
  }

  int read = 512;

  while(read == 512 && !feof(in)) {

    read = fread(buffer, 1, 512, in);

    if(read == 0)
      break;

    if(read != 512)
      memset(buffer+read, 0, 512-read);

    fwrite(buffer, 1, 512, out);
  }

  fclose(in);
  fclose(out);

  printf("\nDone.\n");

  return 0;
}
