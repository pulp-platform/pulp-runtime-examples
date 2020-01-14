#include "pulp.h"
#include "stdio.h"



static int cluster_entry()
{
  printf("Entered cluster on cluster %d core %d\n", get_cluster_id(), get_core_id());

  synch_barrier();

  return 1;
}



int main()
{
  printf("Entering main controller\n");

  cluster_start(0, cluster_entry);

  int retval = cluster_wait(0);

  printf("Got retval from cluster %d\n", retval);

  return 0;
}
