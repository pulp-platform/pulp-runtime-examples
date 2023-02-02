#include "pulp.h"
#include "stdio.h"



static int cluster_entry()
{
  printf("Core %d getting to barrier\n", get_core_id());

  hmr_tmr_barrier_setup_all();

  printf("Core %d crossed the barrier\n", get_core_id());

  return 1;
}



int main()
{
  hmr_set_dmr_config_all(0, true); // Configuring fast recovery for DMR
  printf("indiv. available: %x\nDMR available:    %x\nTMR available:    %x\nRapidRecovery av: %x\n",
      hmr_get_available_config(0) & 0x1,
      (hmr_get_available_config(0) & 0x2) >> 0x1,
      (hmr_get_available_config(0) & 0x4) >> 0x2,
      (hmr_get_available_config(0) & 1<<8) >> 8 );
  hmr_enable_all_dmr(0);
  
  printf("Entering main controller\n");

  cluster_start(0, cluster_entry);

  int retval = cluster_wait(0);

  printf("Got retval from cluster %d\n", retval);

  return 0;
}
