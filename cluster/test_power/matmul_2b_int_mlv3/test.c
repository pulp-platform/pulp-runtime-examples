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
  uint32_t * im2col_1               = &buffer_im2col[0];
  uint32_t * im2col_2               = &buffer_im2col[0 + IFM_CH_NN * DIM_KER_NN * DIM_KER_NN];
  int32_t * filter_1               = &filters_3d[0];
  int32_t * filter_2               = &filters_3d[0 + IFM_CH_NN * DIM_KER_NN * DIM_KER_NN];
  int32_t * filter_3               = &filters_3d[0 + 2 *IFM_CH_NN * DIM_KER_NN * DIM_KER_NN];
  int32_t * filter_4               = &filters_3d[0 + 3 *IFM_CH_NN * DIM_KER_NN * DIM_KER_NN];
  int32_t * filter_1_copy1         = &filters_3d[0];
  int32_t * filter_2_copy1         = &filters_3d[0 + IFM_CH_NN * DIM_KER_NN * DIM_KER_NN];
  int32_t * filter_3_copy1         = &filters_3d[0 + 2 *IFM_CH_NN * DIM_KER_NN * DIM_KER_NN];
  int32_t * filter_4_copy1         = &filters_3d[0 + 3 *IFM_CH_NN * DIM_KER_NN * DIM_KER_NN];
  int32_t * gold_matmul            = &golden_matmul_out[0];
  int32_t * res_matmul             = &matmul_out[0];

  int32_t temp0 = 0;
  int32_t temp1 = 0;
  int32_t temp2 = 0;
  int32_t temp3 = 0;
  int32_t temp4 = 0;
  int32_t temp5 = 0;
  int32_t temp6 = 0;
  int32_t temp7 = 0;

  

  im2col_1 = __builtin_pulp_mlinitspr_v3(0,1,0,0,im2col_1); // update SPRA[0]    
  filter_1 = __builtin_pulp_mlinitspr_v3(1,0,0,0,filter_1); // update SPRW[0]
  filter_2 = __builtin_pulp_mlinitspr_v3(1,0,1,0,filter_2); // update SPRW[1]
  filter_3 = __builtin_pulp_mlinitspr_v3(1,0,2,0,filter_3); // update SPRW[2]
  filter_4 = __builtin_pulp_mlinitspr_v3(1,0,3,0,filter_4); // update SPRW[3]
  
  asm volatile("":::"memory");
  synch_barrier();
  // synch_barrier();
    if(get_core_id() == 0) {
       *(int*)(REG_CORESTATUS) = 0xABBAABBA;
  }
  synch_barrier();
  asm volatile("":::"memory");
   for(int i=0 ; i < ((IFM_CH * DIM_KER_NN * DIM_KER_NN) >> 4); i++) {
      // temp0 = __builtin_pulp_mlsdotsup8_v3(1,0, 0, 0, filter_1, temp0);
      // filter_1 = __builtin_pulp_mlupdatespr_v3(im2col_1);
      // fake =  __builtin_pulp_mlsdotsup8_v3(0,1, 0, 0, im2col_1, fake);
      // im2col_1 = __builtin_pulp_mlupdatespr_v3(filter_1);
      im2col_2 = __builtin_pulp_mlinitspr_v3(0,1,0,1,im2col_2); // update SPRA[1]
      temp0 = __builtin_pulp_mlsdotsup8_v3(0,0, 0, 0, filter_1, temp0);
      temp1 = __builtin_pulp_mlsdotsup8_v3(0,0, 1, 0, filter_2, temp1);
      temp2 = __builtin_pulp_mlsdotsup8_v3(0,0, 2, 0, filter_3, temp2);
      temp3 = __builtin_pulp_mlsdotsup8_v3(0,1, 3, 0, im2col_1, temp3); // update SPRA[0] with new im2col_1 element
      im2col_1 = __builtin_pulp_mlupdatespr_v3(im2col_1);
      temp4 = __builtin_pulp_mlsdotsup8_v3(1,0, 0, 1, filter_1, temp4); // update SPRW[0] with new filter_1 element
      filter_1 = __builtin_pulp_mlupdatespr_v3(filter_1);
      temp5 = __builtin_pulp_mlsdotsup8_v3(1,0, 1, 1, filter_2, temp5); // update SPRW[1] with new filter_2 element
      filter_2 = __builtin_pulp_mlupdatespr_v3(filter_2);
      temp6 = __builtin_pulp_mlsdotsup8_v3(1,0, 2, 1, filter_3, temp6); // update SPRW[2] with new filter_3 element
      filter_3 = __builtin_pulp_mlupdatespr_v3(filter_3);
      temp7 = __builtin_pulp_mlsdotsup8_v3(1,0, 3, 1, filter_4, temp7); // update SPRW[3] with new filter_4 element
      filter_4 = __builtin_pulp_mlupdatespr_v3(filter_4);
      // fake  = __builtin_pulp_mlsdotsup8_v3(1,0, 3, 1, im2col_2, fake);  // fake MAC to update SPRA[1] with new im2col_2 element
      // im2col_2 = __builtin_pulp_mlupdatespr_v3(im2col_2);
    }



  synch_barrier();
    if(get_core_id() == 0) {
       *(int*)(REG_CORESTATUS) = 0xDEADCACA;  
  }

    res_matmul[0] = temp0;
    res_matmul[1] = temp1;
    res_matmul[2] = temp2;
    res_matmul[3] = temp3;
    res_matmul[4] = temp4;
    res_matmul[5] = temp5;
    res_matmul[6] = temp6;
    res_matmul[7] = temp7;

  
    //synch_barrier();
  
  return 1;
  
}

int main()
{
  
  cluster_start(0, cluster_entry);
  
  int retval = cluster_wait(0);
  
  return 0;
  
}
