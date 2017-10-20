#include <stdio.h>



// The original array, stored in global memory. The final result will
// eventually overwrite the original and be stored here.
__device__ float* array;
 

/**
 * Applies the bitonic sorting algorithm to each thread. It swaps two
 * elements in the two lists if they are out of place.
 */
__global__ __forceinline__ void bitonic_sort_kernel (int * a, int blocksize) 
{
  int index = threadIdx.x + blockIdx.x * blocksize;
  atomicMin(&a[i + index], atomicMax(&a[i + blockSize + index], a[i + index]));
  __syncthreads();
}

/**
 * Combines two bitonic sequences together to create a new bitonic sequence.
 * @param a Pointer to the start of the bitonic sequence.
 * @param blockSize The size of each sub-array partition.
 * @param t Determines when to switch between ascending and descending.
 */
__global__ __forceinline__ void bitonic_build_kernel(float * a, int blocksize, int t) 
{
  int index = threadIdx.x + blockIdx.x * blocksize;
  int x = 0;
  int asc = 1;

  int * b = a + index + (blocksize / 2);
  while(x > index) 
  {
    x += t;
    asc++;
  }
	
  if(asc % 2 == 1) 
  {
    atomicMin(&a[index], atomicMax(&b, a[index]));
  }
  else 
  {
    atomicMax(&a[index], atomicMin(&b, a[index]));
  }
}


void bitonic_gpu_init (int * A, int n)
{
  int * d_A;
  cudaMalloc (d_A, n*sizeof(int));
  cudaMemcpy (d_A, A, n*sizeof(int), cudaMemcpyHostToDevice);

  int blocks = 1;
  while (blocks != n/2)
  {
    dim3 numBlocks = blocks;
    dim3 threadsPerBlock = n / blocks / 2;
    bitonic_sort_kernel<<<numBlocks, threadsPerBlock>>>(d_A, n/blocks);
    n *= 2;
  }
}


void bitonic_gpu_sort (int * A, int n)
{
  int j;
  int blocks = n / 2;
  while (blocks != 1)
  {
    int i = blocks;
    int blocksize = n * (1 - 1/blocks);
    while (i != 1)
    {
      dim3 numBlocks = i;
      dim3 threadsPerBlock = blocksize;
      for (j = 0; j < n; j += blocksize, A++)
      {
        bitonic_build_kernel<<<numBlocks, threadsPerBlock>>>(A, blocksize, i);
      }
      i /= 2;
    }
    blocks /= 2;
  }
}


void bitonic_sort_cuda (int * A, int n)
{
  bitonic_gpu_init (A, n);
  bitonic_gpu_sort (A, n);
}
