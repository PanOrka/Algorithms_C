#ifndef FA_H
#define FA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUFF_SIZE
#define BUFF_SIZE 512
#endif

int fa_process(FILE *f, char *regex);

#endif
