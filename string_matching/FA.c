#include "FA.h"

#ifndef A_NEXT
#define A_NEXT(n) (n+1)
#endif

typedef struct automata {
    int prev;
} automata;

int fa_process(FILE *f, char *regex) {
    char buff[BUFF_SIZE + 1];
    int const regex_size = strlen(regex);
    automata fa[regex_size];
    if (regex_size >= 2) {
        fa[0].prev = 0;
        fa[1].prev = 0;

        for (int i=2, j=0; i<regex_size; ) {
            if (regex[i-1] == regex[j]) {
                fa[i].prev = ++j;
                ++i;
            } else {
                if (j>0) {
                    j = fa[j].prev;
                } else {
                    fa[i].prev = 0;
                    ++i;
                }
            }
        }
    } else {
        fa[0].prev = 0;
    }

    int buffor_acc = 0, state = 0;

    while (fgets(buff, BUFF_SIZE + 1, f)) {
        int checked_index_buff = 0;

        while (buff[checked_index_buff] != '\0') {
            if (regex[state] == buff[checked_index_buff]) {
                ++checked_index_buff;
                state = A_NEXT(state);
                if (state >= regex_size) {
                    return buffor_acc + checked_index_buff - state;
                }
            } else if (state > 0) {
                state = fa[state].prev;
            } else {
                ++checked_index_buff;
            }
        }

        buffor_acc += BUFF_SIZE;
    }

    return -1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Bad amount of arguments.\n");
        exit(1);
    } else {
        FILE *f = fopen(argv[2], "r");
        if (f == NULL) {
            fprintf(stderr, "File doesn't exist.\n");
            exit(1);
        } else {
            printf("%d\n", fa_process(f, argv[1]));
        }
    }
}
