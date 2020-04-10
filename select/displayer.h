#include <stdio.h>

/*
// Data to display
*/
int *arr_to_display;
int size_of_display, k_place;
int trans, comp;

/*
// Display full array to File *
*/
void display_arr(FILE *out);

/*
// Display Comparisions, Transpositions and choosen k-place
*/
void display_rest();

/*
// Display pivot value
*/
void display_pivot(int value);

/*
// Diplay compared values
*/
void display_comparision(int f_place, int s_place);

/*
// Display transposed values
*/
void display_transposition(int f_place, int s_place);