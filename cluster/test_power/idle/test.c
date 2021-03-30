#include "pulp.h"
#include "stdio.h"

#define VCDADDR 0x10000000
#define REG_CORESTATUS 0x1C000000
#define USE_CLUSTER

static int cluster_entry()
{

  int i;

  i=i*2;
  
  synch_barrier();

  return 1;
}

// executed on FC
static inline void wait_cycles(const unsigned cycles)
{
  /**
   * Each iteration of the loop below will take four cycles on RI5CY (one for
   * `addi` and three for the taken `bnez`; if the instructions hit in the
   * I$).  Thus, we let `i` count the number of remaining loop iterations and
   * initialize it to a fourth of the number of clock cyles.  With this
   * initialization, we must not enter the loop if the number of clock cycles
   * is less than four, because this will cause an underflow on the first
   * subtraction.
   */
  register unsigned threshold;
  asm volatile("li %[threshold], 4" : [threshold] "=r" (threshold));
  asm volatile goto("ble %[cycles], %[threshold], %l2"
          : /* no output */
          : [cycles] "r" (cycles), [threshold] "r" (threshold)
          : /* no clobbers */
          : __wait_cycles_end);
  register unsigned i = cycles >> 2;
__wait_cycles_start:
  // Decrement `i` and loop if it is not yet zero.
  asm volatile("addi %0, %0, -1" : "+r" (i));
  asm volatile goto("bnez %0, %l1"
          : /* no output */
          : "r" (i)
          : /* no clobbers */
          : __wait_cycles_start);
__wait_cycles_end:
  return;
}


int main()
{

  // printf("Entering main controller\n");

  cluster_start(0, cluster_entry);

  int retval = cluster_wait(0);

  *(int*)(REG_CORESTATUS) = 0xABBAABBA;

  wait_cycles(1000); // cluster with en = 0

  *(int*)(VCDADDR) = 0xDEADCACA;
  
  return 0;
}



