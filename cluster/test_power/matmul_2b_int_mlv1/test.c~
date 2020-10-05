#include "pulp.h"
#include "stdio.h"
#include "parameters.h"
#include "data_allocation.h"
#define REG_CORESTATUS 0x10000000
typedef signed   char  v4s __attribute__((vector_size (4)));
typedef unsigned char  v4u __attribute__((vector_size (4)));
#define SumDotp4(a, b, c) __builtin_pulp_sdotusp4(a, b, c)

#pragma GCC push_options
#pragma GCC optimize ("-fno-tree-loop-optimize")
static int cluster_entry()
{
  uint32_t * ptr1_4_su   = &X4_su[0];
  uint32_t * ptr2_4_su   = &X4_su[0 + IFM_CH * DIM_KER * DIM_KER];
  int32_t *   pW1_4_su   = &W4_su[0];
  int32_t *   pW2_4_su   = &W4_su[0 + IFM_CH * DIM_KER * DIM_KER];
  int32_t *   pW3_4_su   = &W4_su[0 + 2 *IFM_CH * DIM_KER * DIM_KER];
  int32_t *   pW4_4_su   = &W4_su[0 + 3 *IFM_CH * DIM_KER * DIM_KER];
  int32_t *  gold_4_su   = &O4_su[0];
  int32_t *   res_4_su    = &Y4_su[0];

  int32_t *  ptrA      = pW1_4_su;
  int32_t *  ptrA2     = ( ptrA + ((IFM_CH * DIM_KER * DIM_KER) >> 2)); 
  int32_t *  ptrA3     = ( ptrA2 + ((IFM_CH * DIM_KER * DIM_KER) >> 2)); 
  int32_t *  ptrA4     = ( ptrA3 + ((IFM_CH * DIM_KER * DIM_KER) >> 2)); 
  int32_t *  ptrA_2    = pW1_4_su;
  int32_t *  ptrA2_2   = ( ptrA_2 +  ((IFM_CH * DIM_KER * DIM_KER) >> 2)); 
  int32_t *  ptrA3_2   = ( ptrA2_2 +  ((IFM_CH * DIM_KER * DIM_KER) >> 2)); 
  int32_t *  ptrA4_2   = ( ptrA3_2 +  ((IFM_CH * DIM_KER * DIM_KER) >> 2));
  int32_t *ptrB        = ptr1_4_su; //((int32_t*) pB);
  int32_t *ptrB2       = ptrB + ((IFM_CH * DIM_KER * DIM_KER) >> 2); //((int32_t*) pB2);  

  ptrA    = __builtin_pulp_mlinitspr(ptrA, 0);
  ptrA2   = __builtin_pulp_mlinitspr(ptrA2, 1);
  ptrA_2  = __builtin_pulp_mlinitspr(ptrA_2, 2);
  ptrA2_2 = __builtin_pulp_mlinitspr(ptrA2_2, 3);

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
  
  for (int i=0 ; i< (IFM_CH * DIM_KER * DIM_KER) >> 3; i++ ) {
    int act1 = *((int *)ptrB);
    int act2 = *((int *)ptrB2);
    ptrB++;
    ptrB2++;
    sum = __builtin_pulp_mlsdotsup4(ptrA3, act1, sum, 0);
    ptrA3 = __builtin_pulp_mlupdatespr();
    sum2 = __builtin_pulp_mlsdotsup4(ptrA4, act1, sum2, 1);
    ptrA4 = __builtin_pulp_mlupdatespr();
    sum3 = __builtin_pulp_mlsdotsup4(ptrA, act1, sum3, 0);
    ptrA = __builtin_pulp_mlupdatespr();
    sum4 = __builtin_pulp_mlsdotsup4(ptrA2, act1, sum4, 1);
    ptrA2 = __builtin_pulp_mlupdatespr();
    sum5 = __builtin_pulp_mlsdotsup4((ptrA3_2), act2, sum5, 2);
    ptrA3_2 = __builtin_pulp_mlupdatespr();
    sum6 = __builtin_pulp_mlsdotsup4((ptrA4_2), act2, sum6, 3);
    ptrA4_2 = __builtin_pulp_mlupdatespr();
    sum7 = __builtin_pulp_mlsdotsup4((ptrA_2), act2, sum7, 2);
    ptrA_2 = __builtin_pulp_mlupdatespr();
    sum8 = __builtin_pulp_mlsdotsup4((ptrA2_2), act2, sum8, 3);
    ptrA2_2 = __builtin_pulp_mlupdatespr();

  }
  
  synch_barrier();
    if(get_core_id() == 0) {
       *(int*)(REG_CORESTATUS) = 0xDEADCACA;  
  }

    res_4_su[0] = sum;
    res_4_su[1] = sum2;
    res_4_su[2] = sum3;
    res_4_su[3] = sum4;
    res_4_su[4] = sum5;
    res_4_su[5] = sum6;
    res_4_su[6] = sum7;
    res_4_su[7] = sum8;

  
  synch_barrier();
  
  return 1;
  
}
#pragma GCC pop_options
int main()
{
  
  cluster_start(0, cluster_entry);
  
  int retval = cluster_wait(0);
  
  return 0;
  
}
