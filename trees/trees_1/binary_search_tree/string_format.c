#include "string_format.h"

char const * prepare_string(char str[]) {
    int size = 0;
    while (*(str+size) != '\0') {
        size++;
    }
    int str_size = size;

    char start = str[0];
    if (!((start >= 'a' && start <= 'z') || (start >= 'A' && start <= 'Z'))) {
        size -= 1;
        str[0] = ';';
    }

    char end = str[str_size-1];
    if (!((end >= 'a' && end <= 'z') || (end >= 'A' && end <= 'Z'))) {
        size -= 1;
        str[str_size-1] = ';';
    }

    char *str_to_add = malloc(sizeof(char)*(size+1));
    int index = 0;

    for (int i=0; i<str_size; i++) {
        if (str[i] != ';') {
            *(str_to_add+index) = *(str+i);
            index++;
        }
    }
    *(str_to_add+index) = '\0';

    return str_to_add;
}