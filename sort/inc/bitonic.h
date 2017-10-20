#ifndef BITONIC_H
#define BITONIC_H

void bitonic_mergeup (int * A, int n)
{
  int step = n/2;
  int i, j, k;
  int temp;

  while (step > 0)
  {
    for (i = 0; i < n; i += step*2)
    {
      for (j = i, k = 0; k < step; j++, k++)
      {
        if (A[j] > A[j+step])
        {
          temp = A[j];
          A[j] = A[j+step];
          A[j+step] = temp;
        }
      }
    }
    step /= 2;
  }
}


void bitonic_mergedown (int * A, int n)
{
  int step = n/2;
  int i, j, k;
  int temp;
  while (step > 0)
  {
    for (i = 0; i < n; i += step*2)
    {
      for (j = i, k = 0; k < step; j++, k++)
      {
        if (A[j] < A[j+step])
        {
          temp = A[j];
          A[j] = A[j+step];
          A[j+step] = temp;
        }
      }
    }
    step /= 2;
  }
}


void bitonic_sort (int * A, int n)
{
  int i, j;
  for (i = 2; i < n; i *= 2)
  {
    for (j = 0; j < n; j += i*2)
    {
      bitonic_mergeup ((A+j), i);
      bitonic_mergedown ((A+i+j), i);
    }
  }
}


#endif
