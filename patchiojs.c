#undef UNICODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int __cdecl main(int argc, char **argv)
{
  FILE *f;
  long fsize;
  char *string;
  char *match;

  // Validate the parameters
  if (argc != 2) {
    printf("usage: %s <iojsexe>\n", argv[0]);
    printf("patchiojs patches the iojs.exe/node.exe to run in a Windows container.\n");
    printf("%s example usage\n", argv[0]);
    printf("   %s \"C:\\Program Files\\iojs\\iojs.exe\"\n", argv[0]);
    return 1;
  }

  f = fopen(argv[1], "rb");
  fseek(f, 0, SEEK_END);
  fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  string = malloc(fsize + 1);
  fread(string, fsize, 1, f);
  fclose(f);

  string[fsize] = 0;

  match = strstr(string, "dnsopts.hints = dns.ADDRCONFIG;");
  if (match) {
    strncpy(match, "dnsopts.hints = 0;//", 20);
  }
  f = fopen(argv[1], "wb");
  fwrite (string , sizeof(char), fsize, f);
  fclose (f);

  return 0;
}
