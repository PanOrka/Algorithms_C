#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "pcg_basic.h"

/*
// Random permutation of set {1, ..., size}
*/
int * random_permutation(int size);

/*
// Random array of given size, int values in range (-INT32_MAX, INT32_MAX)
*/
int * random_data(int size);