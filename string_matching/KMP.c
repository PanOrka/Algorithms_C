#include "KMP.h"

int kmp_process(FILE *f, char *regex) {
    char buff[BUFF_SIZE + 1];
    int const regex_size = strlen(regex);
    int look_up_table[regex_size];
    if (regex_size >= 2) {
        look_up_table[0] = -1;
        look_up_table[1] = 0;

        for (int i=2, j=0; i<regex_size; ) {
            if (regex[i-1] == regex[j]) {
                look_up_table[i] = ++j;
                ++i;
            } else {
                if (j>0) {
                    j = look_up_table[j];
                } else {
                    look_up_table[i] = 0;
                    ++i;
                }
            }
        }
    }

    int buffor_acc = 0, checked_index_regex = 0;

    while (fgets(buff, BUFF_SIZE + 1, f)) {
        int checked_index_buff = 0;

        while (buff[checked_index_buff] != '\0') {
            if (regex[checked_index_regex] == buff[checked_index_buff]) {
                ++checked_index_buff;
                ++checked_index_regex;
                if (checked_index_regex >= regex_size) {
                    return buffor_acc + checked_index_buff - checked_index_regex;
                }
            } else if (checked_index_regex > 0) {
                checked_index_regex = look_up_table[checked_index_regex];
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
            printf("%d\n", kmp_process(f, argv[1]));
        }
    }
}
