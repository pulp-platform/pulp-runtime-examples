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
  uint32_t * ptr1_8_su   = &X8_su[0];
  uint32_t * ptr2_8_su   = &X8_su[0 + IFM_CH * DIM_KER * DIM_KER];
  int32_t * pW1_8_su   = &W8_su[0];
  int32_t * pW2_8_su   = &W8_su[0 + IFM_CH * DIM_KER * DIM_KER];
  int32_t * pW3_8_su   = &W8_su[0 + 2 *IFM_CH * DIM_KER * DIM_KER];
  int32_t * pW4_8_su   = &W8_su[0 + 3 *IFM_CH * DIM_KER * DIM_KER];
  int32_t * gold_8_su   = &O8_su[0];
  int32_t * res_8_su    = &Y8_su[0];

  int32_t *  ptrA      = pW1_8_su;
  int32_t *  ptrA2     = ( ptrA + ((IFM_CH * DIM_KER * DIM_KER) >> 2)); 
  int32_t *  ptrA3     = ( ptrA2 + ((IFM_CH * DIM_KER * DIM_KER) >> 2)); 
  int32_t *  ptrA4     = ( ptrA3 + ((IFM_CH * DIM_KER * DIM_KER) >> 2)); 
  int32_t *ptrB        = ptr1_8_su; 
  int32_t *ptrB2       = ptrB + ((IFM_CH * DIM_KER * DIM_KER) >> 2); 

  ptrA    = __builtin_pulp_mlinitspr_v3(1,0,0,0,ptrA);
  ptrA2   = __builtin_pulp_mlinitspr_v3(1,0,1,0,ptrA2);
  ptrA3   = __builtin_pulp_mlinitspr_v3(1,0,2,0,ptrA3);
  ptrA4   = __builtin_pulp_mlinitspr_v3(1,0,3,0,ptrA4);
  ptrB    = __builtin_pulp_mlinitspr_v3(0,1,0,0, ptrB);

  int32_t sum = 0;
  int32_t sum2 = 0;
  int32_t sum3 = 0;
  int32_t sum4 = 0;
  int32_t sum5 = 0;
  int32_t sum6 = 0;
  int32_t sum7 = 0;
  int32_t sum8 = 0;

  // synch_barrier();
    if(get_core_id() == 0) {
       *(int*)(REG_CORESTATUS) = 0xABBAABBA;
  }
  synch_barrier();
  
  for (int i=0 ; i< (IFM_CH * DIM_KER * DIM_KER) >> 2; i++ ) {
    ptrB2   = __builtin_pulp_mlinitspr_v3(0,1,0,1, ptrB2);
    /* Compute SPRA[0] * SPRW[0] + sum */
    sum  = __builtin_pulp_mlsdotsup4_v3(0,0, 0, 0, ptrA, sum);
    //printf("ptrB: %d, pinbuffer: %d , ptrA: %d, sum:%d\n ", *ptrB, *pInBuffer, *ptrA, sum);
    /* Compute SPRA[0] * SPRW[1] + sum2 */
    sum2 = __builtin_pulp_mlsdotsup4_v3(0,0, 1, 0, ptrA2, sum2);
    // /* Compute SPRA[0] * SPRW[2] + sum3 */
     sum3 = __builtin_pulp_mlsdotsup4_v3(0,0, 2, 0, ptrA3, sum3);
    // /* Compute SPRA[0] * SPRW[3] + sum4 */
    // /* update SPRA[1] with new im2col1 element (ptrB) */
     sum4 = __builtin_pulp_mlsdotsup4_v3(0,1, 3, 0, ptrB, sum4);
     ptrB = __builtin_pulp_mlupdatespr_v3(ptrB);
    // /* Compute SPRA[1] * SPRW[0] + sum5*/
    // /* update SPRW[0] with new ptrA element (weights) */
     sum5 = __builtin_pulp_mlsdotsup4_v3(1,0, 0, 1, ptrA, sum5);
     ptrA = __builtin_pulp_mlupdatespr_v3(ptrA);
    //  Compute SPRA[1] * SPRW[1] + sum6 
    // /* update SPRW[1] with new filter_2 element (weights) */
     sum6 = __builtin_pulp_mlsdotsup4_v3(1,0, 1, 1, ptrA2, sum6);
     ptrA2 = __builtin_pulp_mlupdatespr_v3(ptrA2);
    // /* Compute SPRA[1] * SPRW[2] + sum7 */
    // /* update SPRW[2] with new filter_3 element (weights) */
     sum7 = __builtin_pulp_mlsdotsup4_v3(1,0, 2, 1, ptrA3, sum7);
     ptrA3 = __builtin_pulp_mlupdatespr_v3(ptrA3);
    // /* Compute SPRA[1] * SPRW[3] + sum8 */
    // /* update SPRW[3] with new filter_4 element (weights) */
     sum8 = __builtin_pulp_mlsdotsup4_v3(1,0, 3, 1, ptrA4, sum8);
     ptrA4 = __builtin_pulp_mlupdatespr_v3(ptrA4);

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

  
    //synch_barrier();
  
  return 1;
  
}

int main()
{
  
  cluster_start(0, cluster_entry);
  
  int retval = cluster_wait(0);
  
  return 0;
  
}
