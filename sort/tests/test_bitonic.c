#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "bitonic.h"

#define N 10


int main (int argc, char ** argv)
{
  int * A = (int *)malloc(N*sizeof(int));
  array_generator (A, N);
  array_printer (A, N); printf("\n");

  bitonic_sort (A, N);
  array_printer (A, N); printf("\n");
}
