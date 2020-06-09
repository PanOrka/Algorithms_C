#include <string.h>
#include <unistd.h>

void run(char *file) {
    char *args[] = {file, NULL};
    execvp(args[0], args);
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (strcmp(argv[1], "--type") == 0) {
            if (strcmp(argv[2], "bst") == 0) {
                run("./binary_search_tree/bst");
            } else if (strcmp(argv[2], "rbt") == 0) {
                run("./red_black_tree/rbt");
            } else if (strcmp(argv[2], "hmap") == 0) {
                run("./hmap/hmap");
            }
        }
    }
}
