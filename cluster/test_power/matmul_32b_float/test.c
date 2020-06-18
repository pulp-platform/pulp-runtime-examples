#include <stdio.h>
#include "pulp.h"

#define REG_CORESTATUS 0x10000000

#define USE_CLUSTER

#define MAESTRO_REG_0 0x

#define NUM_CORES 16
#define SIZE 16

#define PARALLEL

L1_DATA float matA[SIZE*SIZE] __attribute__ ((aligned (4)));
L1_DATA float matB[SIZE*SIZE] __attribute__ ((aligned (4)));
L1_DATA float matC[SIZE*SIZE] __attribute__ ((aligned (4)));

int main()
{
  
#ifdef USE_CLUSTER
  if (rt_cluster_id() != 0){
    return bench_cluster_forward(0);
  }
#endif
  
  int32_t *A = matA;
  int32_t *B = matB;
  int32_t *C = matC;
  uint32_t M = SIZE;
  uint32_t N = SIZE;
  
  if(get_core_id() == 0) {
    
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        A[i*SIZE+j] = j+1;
        B[i*SIZE+j] = i+1;
        C[i*SIZE+j] = 0;
      }
    }
    
  }
  
  int blockSize = (SIZE+NUM_CORES-1) / NUM_CORES;
  int start = get_core_id()*blockSize;
  
  for (int i =0; i<2; i++) {
    
    if (get_core_id() == 0 && i == 1)
      *(int*)(REG_CORESTATUS) = 0xABBAABBA;
    synch_barrier();
    
    for (int i=start; i < start+blockSize; i++) {
      for (int j = 0; j < M; j++) {
	C[i*N+j] = 0;
	for (int k = 0; k < N; k+=1) {
	  C[i*N+j] += A[i*N+k] * B[k*N+j];
	}
      }
    }
      
    synch_barrier();
    if(get_core_id() == 0 && i == 1) {
      *(int*)(REG_CORESTATUS) = 0xDEADCACA;  
    }
    
  }

  return 0;
}
