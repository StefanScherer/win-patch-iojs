#undef UNICODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Copyright (c) 2005 Pascal Gloor <pascal.gloor@spale.com> */
void *
mymemmem(const void *l, size_t l_len, const void *s, size_t s_len) {
  char *cur, *last;
  const char *cl = (const char *)l;
  const char *cs = (const char *)s;

  if (l_len == 0 || s_len == 0) {
    return NULL;
  }

  if (l_len < s_len) {
    return NULL;
  }

  if (s_len == 1) {
    return memchr(l, (int)*cs, l_len);
  }

  last = (char *)cl + l_len - s_len;

  for (cur = (char *)cl; cur <= last; cur++) {
    if (cur[0] == cs[0] && memcmp(cur, cs, s_len) == 0) {
      return cur;
    }
  }

  return NULL;
}

int __cdecl main(int argc, char **argv)
{
  FILE *f;
  long fsize;
  char *string;
  char *pattern;
  char *match;

  // Validate the parameters
  if (argc != 2) {
    printf("usage: %s <iojsexe>\n", argv[0]);
    printf("patchiojs patches the iojs.exe/node.exe to run in a Windows container.\n");
    printf("%s example usage\n", argv[0]);
    printf("   %s \"C:\\Program Files\\iojs\\iojs.exe\"\n", argv[0]);
    return 1;
  }

  printf("Reading %s\n", argv[1]);
  f = fopen(argv[1], "rb");
  fseek(f, 0, SEEK_END);
  fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  string = malloc(fsize + 1);
  fread(string, fsize, 1, f);
  fclose(f);

  string[fsize] = 0;

  printf("Searching for pattern\n");
  pattern = "dnsopts.hints = dns.ADDRCONFIG;";
  match = mymemmem(string, fsize, pattern, strlen(pattern));
  if (match) {
    printf("Patching dnsopts.hints\n");
    strncpy(match, "dnsopts.hints = 0;//", 20);
  }

  printf("Writing %s\n", argv[1]);
  f = fopen(argv[1], "wb");
  fwrite (string , sizeof(char), fsize, f);
  fclose (f);

  return 0;
}
