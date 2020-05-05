#include "pulp.h"
#include "stdio.h"

static int cluster_entry()
{
  
  *(int*)(REG_CORESTATUS) = 0xABBAABBA;
  
  for (int i = 0; i<100; i++)
    wait++;
  
  *(int*)(REG_CORESTATUS) = 0xDEADCACA;
  
  synch_barrier();
  
  return 1;
  
}

int main()
{
  
  cluster_start(0, cluster_entry);
  
  int retval = cluster_wait(0);
  
  return 0;
  
}
