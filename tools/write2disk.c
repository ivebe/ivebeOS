/**
 * write2disk - source file
 *
 * Helper app that writes binary image output of "createimg" to the virtual disk
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
     printf("%s [input] [output] [output-offset-in-hexadecimal]\n", args[0]);
     exit(1);
  }

  out = fopen(args[2], "r+b");

  if (out == NULL) {
     printf("Error, something went wrong. \"%s\"", args[1]);
     exit(1);
  }


  in = fopen(args[1], "rb");

  if (in == NULL) {
     printf("Error, could not open the file \"%s\"", args[2]);
     fclose(out);
     exit(1);
  }

  fseek(out, strtol(args[3], NULL, 16), SEEK_SET);

  int read = 512;

  while(read == 512 && !feof(in)) {

    read = fread(buffer, 1, 512, in);

    if(read == 0)
      break;

    fwrite(buffer, 1, 512, out);
  }

  fclose(in);
  fclose(out);

  printf("\nDone.\n");

  return 0;
}
