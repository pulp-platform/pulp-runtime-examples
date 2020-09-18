#include "pulp.h"
#include "stdio.h"
#include "parameters.h"
#include "data_allocation.h"
#define REG_CORESTATUS 0x10000000
typedef signed   char  v4s __attribute__((vector_size (4)));
typedef unsigned char  v4u __attribute__((vector_size (4)));
#define SumDotp4(a, b, c) __builtin_pulp_sdotusp4(a, b, c)


static int cluster_entry()
{
  int32_t * ptr1_8_su   = &X8_su[0];
  int32_t * ptr2_8_su   = &X8_su[0 + IFM_CH * DIM_KER * DIM_KER];
  uint32_t * pW1_8_su   = &W8_su[0];
  uint32_t * pW2_8_su   = &W8_su[0 + IFM_CH * DIM_KER * DIM_KER];
  uint32_t * pW3_8_su   = &W8_su[0 + 2 *IFM_CH * DIM_KER * DIM_KER];
  uint32_t * pW4_8_su   = &W8_su[0 + 3 *IFM_CH * DIM_KER * DIM_KER];
  int32_t * gold_8_su   = &O8_su[0];
  int32_t * res_8_su    = &Y8_su[0];

  v4s vecA;
  v4s vecA2;
  v4s vecA3;
  v4s vecA4;
  v4u vecB;
  v4u vecB2; 


  int32_t sum = 0;
  int32_t sum2 = 0;
  int32_t sum3 = 0;
  int32_t sum4 = 0;
  int32_t sum5 = 0;
  int32_t sum6 = 0;
  int32_t sum7 = 0;
  int32_t sum8 = 0;

  synch_barrier();
    if(get_core_id() == 0) {
       *(int*)(REG_CORESTATUS) = 0xABBAABBA;
  }
  synch_barrier();
  
  for (int i=0 ; i< (IFM_CH * DIM_KER * DIM_KER) >> 2; i++ ) {

    vecA = *((v4s*)pW1_8_su);
    vecA2 = *((v4s*)pW2_8_su);
    vecA3 = *((v4s*)pW3_8_su);
    vecA4 = *((v4s*)pW4_8_su);

    vecB = *((v4u*)ptr1_8_su);
    vecB2 = *((v4u*)ptr2_8_su);

    sum = SumDotp4(vecB, vecA, sum );
    sum2 = SumDotp4(vecB, vecA2, sum2);
    sum3 = SumDotp4 (vecB, vecA3, sum3);
    sum4 = SumDotp4(vecB, vecA4, sum4);

    sum5 = SumDotp4(vecB2, vecA, sum5);
    sum6 = SumDotp4(vecB2, vecA2, sum6);
    sum7 = SumDotp4(vecB2, vecA3, sum7);
    sum8 = SumDotp4(vecB2, vecA4, sum8);

    //printf("veca: %X, veca2: %X ,veca3: %X,veca4: %X \n", vecA, vecA2, vecA3, vecA4);
    //printf("sum: %d, sum2:%d\n", sum, sum2);

    pW1_8_su+=4;
    pW2_8_su+=4;
    pW3_8_su+=4;
    pW4_8_su+=4;

    ptr1_8_su+=4;
    ptr2_8_su+=4;
  }
  
  synch_barrier();
    if(get_core_id() == 0) {
       *(int*)(REG_CORESTATUS) = 0xDEADCACA;  
  }

    res_8_su[0] = sum;
    res_8_su[1] = sum2;
    res_8_su[2] = sum3;
    res_8_su[3] = sum4;
    res_8_su[4] = sum5;
    res_8_su[5] = sum6;
    res_8_su[6] = sum7;
    res_8_su[7] = sum8;

  
  synch_barrier();
  
  return 1;
  
}

int main()
{
  
  cluster_start(0, cluster_entry);
  
  int retval = cluster_wait(0);
  
  return 0;
  
}
