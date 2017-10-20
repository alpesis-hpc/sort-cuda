#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>

void array_generator (int * A, int n)
{
  int i;
  for (i = 0; i < n; ++i)
  {
    A[i] = rand() % n;
  }
}


void array_printer (int * A, int n)
{
  int i;
  for (i = 0; i < n; ++i)
  {
    printf("%d ", A[i]);
  }
}


#endif
