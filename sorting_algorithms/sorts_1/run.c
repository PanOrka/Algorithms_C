#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

static char *sort_location = "AllSorts";

void run(char *file, char *run, char *stat, char *k) {
    chdir(sort_location);

    char *args[] = {"make",
    file,
    NULL};

    if (fork() == 0) {
        execvp(args[0], args);
    } else {
        wait(NULL);
    }
    char *clean = "clean";
    args[1] = clean;

    if (fork() == 0) {
        execvp(args[0], args);
    } else {
        wait(NULL);
    }

    char *args2[] = {run,
    stat,
    k,
    NULL};

    execvp(args2[0], args2);
}

int main(int argc, char *argv[]) {
    if (argc == 5) {
        char *type = NULL;
        char *comp = NULL;
        for (int i=1; i<=4; i++) {
            if (strcmp(argv[i], "--type") == 0) {
                type = argv[i+1];
            } else if (strcmp(argv[i], "--comp") == 0) {
                comp = argv[i+1];
            }
        }

        if (type == NULL || comp == NULL) {
            fprintf(stderr, "Bad arguments\n");
            exit(1);
        }
        if (strcmp(type, "insert") == 0) {
            if (strcmp(comp, "<=") == 0) {
                run("InsertionSortle", "./InsertionSortle", NULL, NULL);
            } else if (strcmp(comp, ">=") == 0) {
                run("InsertionSortge", "./InsertionSortge", NULL, NULL);
            }
        } else if (strcmp(type, "merge") == 0) {
            if (strcmp(comp, "<=") == 0) {
                run("MergeSortle", "./MergeSortle", NULL, NULL);
            } else if (strcmp(comp, ">=") == 0) {
                run("MergeSortge", "./MergeSortge", NULL, NULL);
            }
        } else if (strcmp(type, "quick") == 0) {
            if (strcmp(comp, "<=") == 0) {
                run("QuickSortle", "./QuickSortle", NULL, NULL);
            } else if (strcmp(comp, ">=") == 0) {
                run("QuickSortge", "./QuickSortge", NULL, NULL);
            }
        } else if (strcmp(type, "dpquick") == 0) {
            if (strcmp(comp, "<=") == 0) {
                run("DPQuickle", "./DPQuickle", NULL, NULL);
            } else if (strcmp(comp, ">=") == 0) {
                run("DPQuickge", "./DPQuickge", NULL, NULL);
            }
        } else if (strcmp(type, "hybridmi") == 0) {
            if (strcmp(comp, "defined") == 0) {
                run("HybridSortMI", "./HybridSortMI", NULL, NULL);
            }
        } else if (strcmp(type, "hybridqi") == 0) {
            if (strcmp(comp, "defined") == 0) {
                run("HybridSortQI", "./HybridSortQI", NULL, NULL);
            }
        } else if (strcmp(type, "hybridmq") == 0) {
            if (strcmp(comp, "defined") == 0) {
                run("HybridSortMQ", "./HybridSortMQ", NULL, NULL);
            }
        } else if (strcmp(type, "hybridqm") == 0) {
            if (strcmp(comp, "defined") == 0) {
                run("HybridSortQM", "./HybridSortQM", NULL, NULL);
            }
        }
    } else if (argc == 8) {
        char *type = NULL;
        char *comp = NULL;
        char *stat = NULL;
        char *k = NULL;
        for (int i=1; i<=7; i++) {
            if (strcmp(argv[i], "--type") == 0) {
                type = argv[i+1];
            } else if (strcmp(argv[i], "--comp") == 0) {
                comp = argv[i+1];
            } else if (strcmp(argv[i], "--stat") == 0) {
                stat = argv[i+1];
                k = argv[i+2];
            }
        }

        if (type == NULL || comp == NULL) {
            fprintf(stderr, "Bad arguments\n");
            exit(1);
        }
        if (strcmp(type, "insert") == 0) {
            if (strcmp(comp, "<=") == 0) {
                run("InsertionSortle", "./InsertionSortle", stat, k);
            } else if (strcmp(comp, ">=") == 0) {
                run("InsertionSortge", "./InsertionSortge", stat, k);
            }
        } else if (strcmp(type, "merge") == 0) {
            if (strcmp(comp, "<=") == 0) {
                run("MergeSortle", "./MergeSortle", stat, k);
            } else if (strcmp(comp, ">=") == 0) {
                run("MergeSortge", "./MergeSortge", stat, k);
            }
        } else if (strcmp(type, "quick") == 0) {
            if (strcmp(comp, "<=") == 0) {
                run("QuickSortle", "./QuickSortle", stat, k);
            } else if (strcmp(comp, ">=") == 0) {
                run("QuickSortge", "./QuickSortge", stat, k);
            }
        } else if (strcmp(type, "dpquick") == 0) {
            if (strcmp(comp, "<=") == 0) {
                run("DPQuickle", "./DPQuickle", stat, k);
            } else if (strcmp(comp, ">=") == 0) {
                run("DPQuickge", "./DPQuickge", stat, k);
            }
        } else if (strcmp(type, "hybridmi") == 0) {
            if (strcmp(comp, "defined") == 0) {
                run("HybridSortMI", "./HybridSortMI", stat, k);
            }
        } else if (strcmp(type, "hybridqi") == 0) {
            if (strcmp(comp, "defined") == 0) {
                run("HybridSortQI", "./HybridSortQI", stat, k);
            }
        } else if (strcmp(type, "hybridmq") == 0) {
            if (strcmp(comp, "defined") == 0) {
                run("HybridSortMQ", "./HybridSortMQ", stat, k);
            }
        } else if (strcmp(type, "hybridqm") == 0) {
            if (strcmp(comp, "defined") == 0) {
                run("HybridSortQM", "./HybridSortQM", stat, k);
            }
        }
    } else {
        fprintf(stderr, "4 or 7 arguments needed. Have %d\n", argc-1);
        exit(1);
    }

    return 0;
}