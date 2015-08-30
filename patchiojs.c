#undef UNICODE

#include <stdio.h>
#include <stdlib.h>

int __cdecl main(int argc, char **argv)
{

    // Validate the parameters
    if (argc != 2) {
        printf("usage: %s <iojsexe>\n", argv[0]);
        printf("patchiojs patches the iojs.exe/node.exe to run in a Windows container.\n");
        printf("%s example usage\n", argv[0]);
        printf("   %s \"C:\\Program Files\\iojs\\iojs.exe\"\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);

    string[fsize] = 0;

    char *match = strstr('dnsopts.hints = dns.ADDRCONFIG;');
    if (match) {
      strncpy(match, 'dnsopts.hints = 0;//', 20);
    }
    f = fopen(argv[1], "wb");
    fwrite (string , sizeof(char), fsize, f);
    fclose (f);

    return 0;
}
