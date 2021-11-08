#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

//#define DEBUG
//#define LARGE			// needed for large networks with A>65

#define NNUCMAX 26         // 26 elements in bbn.c
#define NNUCREACMAX 100	// 100 nuclear reactions in bbnrate.c

#ifndef LARGE

#define NELEMENTS 1000  // max number of elements
#define NREAC 10000     // max number of reactions

#else

#define NELEMENTS 8000  // max number of elements
#define NREAC 90000     // max number of reactions

#endif

#define K9_to_MeV     8.617330637338339e-02 /* conversion factor T(10**9 K) * K9_to_MeV = T(MeV) */
#define M_u           931.4940954 /* MeV */

/*----------------------------------------------------*/

void remove_spaces(char str[]);
int find_element(char str[], char list[][6], int nnuc);
int find_type(int number[]);
void type_to_numbers(int type, int rn[]);
double factorial(int n);
double rate(double T9, double af[]);
void swap_quicksort(char nuclist[][6], double Am[], double Zm[], double Dm[], double spin[], int ie, int je);
int random_quicksort(int ie, int je);
void quicksort(char nuclist[][6], double Am[], double Zm[], double Dm[], double spin[], int left, int right);
void swap_quicksort_reac(int reac[][6], int numnuc[][6], double Crev[], double Qf[], int reactype[], double af[][7], int ie, int je);
void quicksort_reac(int reac[][6], int numnuc[][6], double Crev[], double Qf[], int reactype[], double af[][7], int left, int right);

